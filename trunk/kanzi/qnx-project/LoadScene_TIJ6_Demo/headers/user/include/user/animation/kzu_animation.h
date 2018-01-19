/**
* \file
* Animation containing the animation key frames and the calculated target value for the animation. KzuAnimation inherits from KzuAnimationItem.
* KzuAnimation can contain other KzuAnimation animations as child animations which are applied and prepared at the same time with the parent.
* 
* KzuAnimation can directly set a property of an object to the animation target value. This target property is specified on creation time using the following
* string format. Here the format is expressed as a regular expression, where <code>PropertyType</code> denotes a (float) property type name, <code>StructPropertyType</code>
* a struct property type name, <code>Index</code> an array index number, and <code>IndexOrName</code> an array index number or a name of an animation clip
* (e.g. <code><TimeLineSequence>["MyClip"]</code>).
*
* \code
* (PropertyType(\[Index\])?((\.StructPropertyType)*\.PropertyType)?)|(<MorphTarget>\[Index\])|(<TimeLineSequence>\[IndexOrName\])
* \endcode
*
* In the case an animation clip name is specified, the target property is always assumed to be ::KZU_PROPERTY_TYPE_TIMELINE_ENTRY_WEIGHT.
* In the case the string is of the format <code>"<MorphTarget>[N]"</code>, the string will be first transformed to
* <code>"MeshMorphTargets[N].MeshWeightedMorphTarget.MeshMorphTargetWeight"</code> and then resolved.
* The object which property is specified with the string is the context object of the current KzuTimeLineEntry of the KzuAnimationPlayer.
* The KzuTimeLineSequence corresponding to the <code>"<TimeLineSequence>"</code> format is the current KzuTimeLineSequence of the KzuAnimationPlayer.
*
* The target property can also be set after creation using ::kzuAnimationSetTargetPropertyType() but then the special string format cannot be used.
*
* Animation Example Code
* ----
* The following code shows how to animate the X translation value of a sphere. The animation starts when the animation is added to the
* task scheduler with ::kzuObjectNodeAddAnimationItem().
\code{.c}
    kzsError result;
    // Key frame data in (time, value) pairs.
    kzFloat timesAndValues[10] = { 0.0f, 0.1f,
                                   0.1f, 0.5f,
                                   0.2f, 1.0f,
                                   0.3f, 0.5f,
                                   0.4f, 0.1f };
    struct KzuAnimation* animation;
    kzUint i;
    struct KzuObjectNode* objectNode;

    result = kzuAnimationCreateFloatTarget(memoryManager, uiDomain, kzuPropertyTypeGetName(KZU_PROPERTY_TYPE_TRANSFORMATION),
                                           KZU_PROPERTY_FIELD_TRANSLATION_X, &animation);
    kzsErrorForward(result);

    // Add key frames to the animation.
    for (i = 0; i < 10; i += 2)
    {
        struct KzuAnimationKeyFloat* key;
        struct KzuAnimationKey* animationKey;

        result = kzuAnimationKeyFloatCreate(memoryManager, timesAndValues[i], timesAndValues[i + 1],
                                            KZU_ANIMATION_INTERPOLATION_LINEAR, &key);
        kzsErrorForward(result);

        animationKey = kzuAnimationKeyFloatToAnimationKey(key);
        result = kzuAnimationAddKeyFrame(animation, animationKey);
        kzsErrorForward(result);
    }

    // Create a sphere to animate.
    {
        struct KzuMesh* mesh;
        struct KzuMeshNode* meshNode;

        result = kzuMeshCreateSphere(kzuUIDomainGetResourceManager(uiDomain), "Sphere", 7.0f, 32, 32, KZ_NULL, &mesh);
        kzsErrorForward(result);

        result = kzuMeshNodeCreate(memoryManager, "mesh node", uiDomain, mesh, &meshNode);
        kzsErrorForward(result);

        result = kzuResourceRelease(kzuMeshToResource(mesh));
        kzsErrorForward(result);

        objectNode = kzuMeshNodeToObjectNode(meshNode);
        result = kzuObjectNodeAddChild(kzuSceneToObjectNode(scene), objectNode);
        kzsErrorForward(result);
    }

    // Add the animation to the sphere object node and add the animation to the root animation player from the task scheduler.
    // This will also start the animation.
    result = kzuObjectNodeAddAnimationItem(objectNode, kzuAnimationToAnimationItem(animation), KZ_FALSE, 1, KZ_NULL);
    kzsErrorForward(result);
\endcode
*
* \see The Transition_layer example project for more example code.
*
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_ANIMATION_H
#define KZU_ANIMATION_H


#include "kzu_animation_key.h"
#include <user/properties/kzu_property_common.h>

#include <core/util/collection/kzc_dynamic_array.h>

#include <system/kzs_types.h>
#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations */
struct KzcInputStream;
struct KzcMemoryManager;
struct KzuAnimationItem;
struct KzuAnimationKey;
struct KzuAnimationPlayer;
struct KzuBinaryFileInfo;
struct KzuObjectNode;
struct KzuResource;
struct KzuPropertyManager;
struct KzuPropertyType;
struct KzuUIDomain;


/**
 * \struct KzuAnimation
 * Animation structure.
 */
struct KzuAnimation;

/**
* \struct KzuAnimationData
* Animation data.
*/
struct KzuAnimationData;


/** Allocates memory for animation structure without specifying the target or target type. */
kzsError kzuAnimationCreate(const struct KzcMemoryManager* memoryManager, struct KzuUIDomain* uiDomain, struct KzuAnimation** out_animation);

/** Allocates memory for animation structure for animating given float property.
* \param memoryManager The memory manager to use.
* \param uiDomain The UI domain to use.
* \param propertyTypePath String specifying the target property. See the top of the page for the format.
* \param out_animation Pointer that is set to point to the new KzuAnimation.
*/
kzsError kzuAnimationCreateFloatTarget(const struct KzcMemoryManager* memoryManager, struct KzuUIDomain* uiDomain,
                                       kzString propertyTypePath, enum KzuPropertyField propertyField,
                                       struct KzuAnimation** out_animation);

/** Allocates memory for animation structure for animating given matrix property.
* \param memoryManager The memory manager to use.
* \param uiDomain The UI domain to use.
* \param propertyTypePath String specifying the target property. See the top of the page for the format.
* \param out_animation Pointer that is set to point to the new KzuAnimation.
*/
kzsError kzuAnimationCreateMatrix(const struct KzcMemoryManager* memoryManager, struct KzuUIDomain* uiDomain,
                                  kzString propertyTypePath, struct KzuAnimation** out_animation);

/** Allocates memory for animation structure for animating given texture property.
* \param memoryManager The memory manager to use.
* \param uiDomain The UI domain to use.
* \param propertyTypePath String specifying the target property. See the top of the page for the format.
* \param out_animation Pointer that is set to point to the new KzuAnimation.
*/
kzsError kzuAnimationCreateTexture(const struct KzcMemoryManager* memoryManager, struct KzuUIDomain* uiDomain,
                                   kzString propertyTypePath, struct KzuAnimation** out_animation);

/** Loads animation from KZB. */
kzsError kzuAnimationLoadFromKZB(struct KzuAnimation* animation, struct KzcInputStream* inputStream, const struct KzuBinaryFileInfo* file);

/** Add child animation to given animation. */
kzsError kzuAnimationAddChild(const struct KzuAnimation* parent, const struct KzuAnimation* child);

/** Removes child from animation. */
kzsError kzuAnimationRemoveChild(const struct KzuAnimation* parent, const struct KzuAnimation* child);

/** Gets iterator for animations children. */
struct KzcDynamicArrayIterator kzuAnimationGetChildIterator(const struct KzuAnimation* parent);


/** Adds new animation key to animation. Takes ownership of animationKey. */
kzsError kzuAnimationAddKeyFrame(struct KzuAnimation* animation, const struct KzuAnimationKey* animationKey);

/** Removes animation key from animation. */
kzsError kzuAnimationRemoveKeyFrame(const struct KzuAnimation* animation, const struct KzuAnimationKey* animationKey);

/** Sets value source for animation key frame. */
kzsError kzuAnimationSetKeyFrameValueSource(struct KzuAnimation* animation, struct KzuAnimationKey* key, enum KzuAnimationKeyValueSource source, struct KzuResource* resource);

/** Gets animation key frames as dynamic array. */
struct KzcDynamicArray* kzuAnimationGetKeyFrames(const struct KzuAnimation* animation);

/** 
* Gets nearest smaller and bigger available animation keys for given animation.
* The nearest smaller key is returned in out_animationKey1 and nearest higher key is returned in out_animationKey2. 
* If there are no keys at some direction the corresponding out_animationKey is set to KZ_NULL.
*/
kzsError kzuAnimationGetKeysAtTime(const struct KzuAnimation* animation, kzFloat time, 
                                   struct KzuAnimationKey** out_animationKey1, struct KzuAnimationKey** out_animationKey2);
/** Returns effective value of the animation at given time. 
 * \param out_value Output value evaluated from animation. KZ_NULL for ignoring the return value.
 * \param out_valueFound Returns if value was found at all, for example if sampling outside keyframes value is not found. KZ_NULL for ignoring the return value.
 */
kzsError kzuAnimationGetValueAtTime(struct KzuAnimation* animation, kzFloat time, kzFloat* out_value, kzBool* out_valueFound);

/** 
* Applies given animation and its children at given time for the target specified by parameter property.
* \param time Time of animation. If out of range [0, (endTime - startTime)] the first or last key value is used. 
* If animation targets scale or rotation components of matrix, the transformations from the target matrix is set to identity.
*/
kzsError kzuAnimationApply(struct KzuAnimationPlayer* player, const struct KzuAnimation* animation, kzFloat time);

/** Gets the starting time of the animation and its children. */
kzFloat kzuAnimationGetStartTime(const struct KzuAnimation* animation);

/** Gets the ending time of the animation and its children. */
kzFloat kzuAnimationGetEndTime(const struct KzuAnimation* animation);

/** Prepares animations target properties for animation update. Resets states and values. */
kzsError kzuAnimationPrepare(struct KzuAnimationPlayer* player, const struct KzuAnimation* animation);

/** Gets animation target property type to animate. */
const struct KzuPropertyType* kzuAnimationGetTargetPropertyType(const struct KzuAnimation* animation);
/** Gets target attribute from animation. */
enum KzuPropertyField kzuAnimationGetTargetAttribute(const struct KzuAnimation* animation);

/** Cast from animation to animation item. */
struct KzuAnimationItem* kzuAnimationToAnimationItem(const struct KzuAnimation* animation);
/** Cast from animation item to animation. */
struct KzuAnimation* kzuAnimationFromAnimationItem(const struct KzuAnimationItem* animationItem);

/** Resolves object from given path. */
kzsError kzuAnimationResolveObjectFromPath(struct KzuUIDomain* uiDomain, struct KzuObjectNode* parentObjectNode,
                                           kzString path, struct KzuObjectNode** out_objectNode, struct KzuResource** out_resource);

/** Private function for setting property manager for animation. */
void kzuAnimationSetPropertyManager(struct KzuAnimation* animation, struct KzuPropertyManager* propertyManager);

/** Sets target property type for animation. */
kzsError kzuAnimationSetTargetPropertyType(struct KzuAnimation* animation, const struct KzuPropertyType* targetPropertyType);


KZ_HEADER_END


#endif
