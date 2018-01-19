/**
* \file
* Animation clip provides a start and end time and the target KzuObjectNode or KzuResource for a group of animations.
* Animating a KzuResource allows animating a KzuMaterial, such as shader attributes.
* The start and end time are defined on KzuAnimationClip creation time and cannot be changed later.
*
* A KzuAnimationClip can include other animation clips as child clips. The child clips are played at the same time with
* the parent clip.
*
* Animation Clip Example Code
* ----
* The following example code shows how to use an animation clip to play a part of a KzuAnimation.
\code{.c} 
    kzsError result;
    kzFloat timesAndValues[10] = { 0.0f, 0.0f,
                                   1.0f, 2.0f,
                                   2.0f, 10.0f,
                                   3.0f, 2.0f,
                                   4.0f, 0.0f };
    struct KzuAnimation* animation;
    kzUint i;
    struct KzuObjectNode* objectNode;
    struct KzuAnimationClip* animationClip;

    result = kzuAnimationCreateFloatTarget(memoryManager, uiDomain, kzuPropertyTypeGetName(KZU_PROPERTY_TYPE_TRANSFORMATION),
                                           KZU_PROPERTY_FIELD_TRANSLATION_X, &animation);
    kzsErrorForward(result);

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
    // Clip away 0.5 seconds from the beginning and end of the animation.
    result = kzuAnimationClipCreate(memoryManager, uiDomain, 0.5f, kzuAnimationGetEndTime(animation) - 0.5f,
                                    KZU_ANIMATION_CLIP_TYPE_ROOT_CLIP, &animationClip);
    kzsErrorForward(result);
    result = kzuAnimationClipAddAnimation(animationClip, animation);
    kzsErrorForward(result);

    // Add the animation to the sphere object node and to the root animation player from the task scheduler.
    // This will also start the animation.
    result = kzuObjectNodeAddAnimationItem(objectNode, kzuAnimationClipToAnimationItem(animationClip), KZ_FALSE, 1, KZ_NULL);
    kzsErrorForward(result);
\endcode
*
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_ANIMATION_CLIP_H
#define KZU_ANIMATION_CLIP_H


#include <system/kzs_types.h>
#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations. */
struct KzcDynamicArray;
struct KzcInputStream;
struct KzcMemoryManager;
struct KzuAnimation;
struct KzuAnimationPlayer;
struct KzuBinaryFileInfo;
struct KzuUIDomain;


/** Animation clip type. */
enum kzuAnimationClipType
{
    KZU_ANIMATION_CLIP_TYPE_ROOT_CLIP = 0, /**< Root animation clip, can be used in entries and "play animation" actions. */
    KZU_ANIMATION_CLIP_TYPE_CHILD_CLIP     /**< Child animation clip. */
};


/**
 * \struct KzuAnimationClip
 * Animation clip structure.
 * Animation clip allows users to run sections of animations from requested time.
 * The time in animation clip is relative to animation time line.
 */
struct KzuAnimationClip;


/** Creates a new animation clip.
 * There are two types of animation clips: ::KZU_ANIMATION_CLIP_TYPE_ROOT_CLIP and ::KZU_ANIMATION_CLIP_TYPE_CHILD_CLIP.
 * Root animation clips have start time, end time, duration, and relative (::kzuAnimationClipSetRelative()) flag.
 * Child animation clips are children of root animation clips or other child animation clips. Child animations have a target
 * object or resource. Each animation clip can include zero or more ::KzuAnimation objects.
 * \param memoryManager The memory manager to use for allocating the clip.
 * \param uiDomain The UI domain to use.
 * \param startTime The start time of the clip in seconds in animation player time.
 * \param endTime The end time of the clip in seconds in animation player time.
 * \param clipType ::KZU_ANIMATION_CLIP_TYPE_ROOT_CLIP or ::KZU_ANIMATION_CLIP_TYPE_CHILD_CLIP.
 * \param out_animationClip A pointer that is set to point to the new animation clip.
 * \return ::KZS_SUCCESS on success.
 */
kzsError kzuAnimationClipCreate(const struct KzcMemoryManager* memoryManager, struct KzuUIDomain* uiDomain, kzFloat startTime, kzFloat endTime, 
                                enum kzuAnimationClipType clipType, struct KzuAnimationClip** out_animationClip);

/** Creates new animation clip which contains given animation. */
kzsError kzuAnimationClipCreateFromAnimation(const struct KzcMemoryManager* memoryManager, struct KzuUIDomain* uiDomain, const struct KzuAnimation* animation, 
                                             struct KzuAnimationClip** out_animationClip);

/** Removes animation clip from parent, if there is such.
 * \return ::KZC_ERROR_ELEMENT_NOT_FOUND if the child does not exist, otherwise ::KZS_SUCCESS.
 */
kzsError kzuAnimationClipRemoveFromParent(struct KzuAnimationClip* animationClip);

/** Loads an animation clip and any of its child clips and animations from the KZB file. */
kzsError kzuAnimationClipLoadFromKZB(struct KzuAnimationClip* animationClip, struct KzcInputStream* inputStream, const struct KzuBinaryFileInfo* file);

/** Loads a child animation clip and any of its child clips and animations from the KZB file. */
kzsError kzuAnimationClipLoadChildClipFromKZB(struct KzuAnimationClip* animationClip, struct KzcInputStream* inputStream, const struct KzuBinaryFileInfo* file);

/** Sets whether or not the animation clip is relative to the original value.
 * Being relative means that the animation value of the clip is added to the original animated value, instead of it replacing the original value.
 * The clip type must be ::KZU_ANIMATION_CLIP_TYPE_ROOT_CLIP.
 */
void kzuAnimationClipSetRelative(struct KzuAnimationClip* animationClip, kzBool relative);

/** Adds given animation as target for this animation clip. */
kzsError kzuAnimationClipAddAnimation(const struct KzuAnimationClip* animationClip, const struct KzuAnimation* animation);
/** Adds new child clip for the animation clip. */
kzsError kzuAnimationClipAddAnimationClip(struct KzuAnimationClip* animationClip, struct KzuAnimationClip* childClip);
/** Removes animation from animation clip. */
kzsError kzuAnimationClipRemoveAnimation(const struct KzuAnimationClip* animationClip, const struct KzuAnimation* animation);
/** Removes child clip from animation clip. */
kzsError kzuAnimationClipRemoveAnimationClip(const struct KzuAnimationClip* animationClip, struct KzuAnimationClip* childClip);


/** Gets starting time of the animation sequence. Returned time is relative to animation time line.
 * The clip type must be ::KZU_ANIMATION_CLIP_TYPE_ROOT_CLIP.
 */
kzFloat kzuAnimationClipGetStartTime(const struct KzuAnimationClip* animationClip);

/** Gets ending time of the animation sequence. Returned time is relative to animation time line.
 * The clip type must be ::KZU_ANIMATION_CLIP_TYPE_ROOT_CLIP.
 */
kzFloat kzuAnimationClipGetEndTime(const struct KzuAnimationClip* animationClip);

/** Gets duration of the animation sequence stored in animation clip.
 * The clip type must be ::KZU_ANIMATION_CLIP_TYPE_ROOT_CLIP.
 */
kzFloat kzuAnimationClipGetDuration(const struct KzuAnimationClip* animationClip);

/**
* Animates given animations clip targeting specified property.
* \param time Time of animation in seconds, relative to the beginning of the animation clip.
*/
kzsError kzuAnimationClipAnimate(struct KzuAnimationPlayer* player, struct KzuAnimationClip* animationClip, kzFloat time);

/** Prepares animation clip target properties for animation. Resets states and values. */
kzsError kzuAnimationClipPrepare(struct KzuAnimationPlayer* player, struct KzuAnimationClip* animationClip);


/** Gets animations from animation clip. */
struct KzcDynamicArray* kzuAnimationClipGetAnimations(const struct KzuAnimationClip* animationClip);
/** Gets children from animation clip. */
struct KzcDynamicArray* kzuAnimationClipGetChildren(const struct KzuAnimationClip* animationClip);


/** Sets name for the animation clip. */
kzsError kzuAnimationClipSetName(struct KzuAnimationClip* animationClip, kzString name);
/** Gets name from the animation clip. */
kzString kzuAnimationClipGetName(const struct KzuAnimationClip* animationClip);

/** Cast from animation clip to animation item. */
struct KzuAnimationItem* kzuAnimationClipToAnimationItem(const struct KzuAnimationClip* animationClip);
/** Cast from animation item to animation clip. */
struct KzuAnimationClip* kzuAnimationClipFromAnimationItem(const struct KzuAnimationItem* animationItem);

/** Sets the target object path. The path should point to a ::KzuObjectNode only.
 * The path can be absolute or relative to the context object path of the time line entry containing this clip
 * (see ::kzuTimeLineEntrySetContextObjectPath()).
 */
kzsError kzuAnimationClipSetTargetObjectPath(struct KzuAnimationClip* animationClip, kzString path);
/** Gets target object path. */
kzString kzuAnimationClipGetTargetObjectPath(const struct KzuAnimationClip* animationClip);
/** Gets target resource (pointer to KzuResource) from animation clip. */
void* kzuAnimationClipGetTargetResource(const struct KzuAnimationClip* animationClip);

/** \return The parent animation clip or ::KZ_NULL if it has none. */
struct KzuAnimationClip* kzuAnimationClipGetParentClip(const struct KzuAnimationClip* animationClip);
/** Gets the root clip from the animation clip, which is the last clip in the chain of parent clips the animation clip has. */
struct KzuAnimationClip* kzuAnimationClipGetRootClip(struct KzuAnimationClip* animationClip);


KZ_HEADER_END


#endif
