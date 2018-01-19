/**
 * \file
 * Base structure for scene graph nodes. KzuObjectNode contains information of the node type (mesh, light, camera, ...), transformation,
 * list of child object nodes and set of properties.
 *
 * Object Node Messages
 * ----
 * KzuObjectNode does not send or receive any (public) messages.
 *
 * Object Node Properties
 * ----
 * ::KZU_PROPERTY_TYPE_STATE_MANAGER resource ID property specifies the ::KzuStateManager applied to the object node.
 *
 * ::KZU_PROPERTY_TYPE_GESTURE_RECOGNIZER__CLICK Boolean property specifies whether or not the node should recognize clicks. The default value is ::KZ_FALSE.
 *
 * ::KZU_PROPERTY_TYPE_STYLE_NAME resource ID property specifies a ::KzuStyle that will be applied to the node.
 *
 * ::KZU_PROPERTY_TYPE_OBJECT_EXTERNAL_OWNERSHIP Boolean property specifies whether or not the node is owned by something else but its parent. If ::KZ_TRUE,
 * the parent will not delete the child when the parent is deleted. The default value is ::KZ_FALSE.
 *
 * ::KZU_PROPERTY_TYPE_TRANSFORMATION ::KzcMatrix4x4 property specifies the transformation matrix for the node. This property has no effect if
 * the node is a ::KzuScene, then the identity matrix is used. The transformation matrix specifies the location, orientation and scale of the node relative
 * to its parent node. This transformation is applied before the layout transformation set by the parent. The default value is the identity matrix.
 *
 * ::KZU_PROPERTY_TYPE_RENDER_TRANSFORMATION ::KzcMatrix4x4 property specifies the render transformation matrix for the node. This transformation is
 * applied after the ::KZU_PROPERTY_TYPE_TRANSFORMATION and layout transformation. The default value is the identity matrix.
 *
 * ::KZU_PROPERTY_TYPE_LAYOUT_WIDTH float property specifies the width of the node when used in a layout. The default value is 0.
 *
 * ::KZU_PROPERTY_TYPE_LAYOUT_HEIGHT float property specifies the height of the node when used in a layout. The default value is 0.
 *
 * ::KZU_PROPERTY_TYPE_LAYOUT_DEPTH float property specifies the depth of the node when used in a layout. The default value is 0.
 *
 * ::KZU_PROPERTY_TYPE_LAYOUT_HORIZONTAL_ALIGNMENT integer property specifies the alignment in horizontal direction the node should use when it resides
 * under a layout. The value should be one of ::KzuObjectNodeHorizontalAlignment values. The default value is ::KZU_OBJECT_NODE_HORIZONTAL_ALIGNMENT_CENTER.
 *
 * ::KZU_PROPERTY_TYPE_LAYOUT_VERTICAL_ALIGNMENT integer property specifies the alignment in vertical direction the node should use when it resides
 * under a layout. The value should be one of ::KzuObjectNodeVerticalAlignment values. The default value is ::KZU_OBJECT_NODE_VERTICAL_ALIGNMENT_CENTER.
 *
 * ::KZU_PROPERTY_TYPE_LAYOUT_DEPTH_ALIGNMENT integer property specifies the alignment in depth direction the node should use when it resides
 * under a layout. The value should be one of ::KzuObjectNodeDepthAlignment values. The default value is ::KZU_OBJECT_NODE_DEPTH_ALIGNMENT_CENTER.
 *
 * ::KZU_PROPERTY_TYPE_LAYOUT_HORIZONTAL_MARGIN ::KzcVector2 property specifies the margin in horizontal direction the node should use when it resides
 * under a layout. The two floats specify the margin for the left and right side of the object respectively. The default value is {0, 0}.
 *
 * ::KZU_PROPERTY_TYPE_LAYOUT_VERTICAL_MARGIN ::KzcVector2 property specifies the margin in vertical direction the node should use when it resides
 * under a layout. The two floats specify the margin for the bottom and top side of the object respectively. The default value is {0, 0}.
 *
 * ::KZU_PROPERTY_TYPE_LAYOUT_DEPTH_MARGIN ::KzcVector2 property specifies the margin in depth direction the node should use when it resides
 * under a layout. The two floats specify the margin for the back and front side of the object respectively. The default value is {0, 0}.
 *
 * ::KZU_PROPERTY_TYPE_HIT_TESTABLE Boolean property specifies whether or not the node can be picked and is sensitive to user input in the 3D scene.
 * The default value is ::KZ_FALSE.
 *
 * ::KZU_PROPERTY_TYPE_HIT_TESTABLE_CONTAINER Boolean property specifies whether or not the actual size (from ::kzuObjectNodeGetActualSize)
 * of the node is used for hit testing. If the property is ::KZ_FALSE, the bounding box (from ::kzuObjectNodeGetBoundingVolume) of the node is used
 * instead if available. The default value is ::KZ_FALSE.
 *
 * ::KZU_PROPERTY_TYPE_VISIBLE Boolean property specifies whether or not the node should be rendered. The default value is ::KZ_TRUE.
 *
 * ::KZU_PROPERTY_TYPE_FRUSTUM_CULL_MARGIN float property specifies the margin of the frustum cull radius of the node. Useful when, for example, vertex shaders
 * modify the geometry and frustum culling would interfere with that. The default value is 0.
 *
 * ::KZU_PROPERTY_TYPE_ENABLED Boolean property specifies whether or not the node receives input but ignores it. I.e. if the value is ::KZ_FALSE, the node receives
 * input but does not handle it. The default value is ::KZ_TRUE.
 *
 * ::KZU_PROPERTY_TYPE_FOCUSABLE Boolean property specifies whether or not the node accepts focus. The default value is ::KZ_TRUE.
 *
 * ::KZU_PROPERTY_TYPE_FOCUSED Boolean property is set ::KZ_TRUE when the node has the focus, otherwise it is ::KZ_FALSE. Key events are delivered first to the
 * focused node.
 *
 * ::KZU_PROPERTY_TYPE_PARTIAL_RENDERING_FORCE_RENDER Boolean property specifies whether or not to force partial rendering update even if object
 * was not otherwise changed. This property has an effect only when using a ::KzuPartialRenderingComposer to render the node. The default value is ::KZ_FALSE.
 *
 * ::KZU_PROPERTY_TYPE_PARTIAL_RENDERING_STENCIL_OBJECT pointer property specifies a subtree of nodes used as the stencil mesh for the object node in partial rendering.
 * This property has an effect only when using a ::KzuPartialRenderingComposer to render the node. The default value is ::KZ_NULL.
 *
 * ::KZU_PROPERTY_TYPE_CONSTRAINT_POSITION pointer property specifies a target KzuObjectNode which translation is used for this object node.
 *
 * ::KZU_PROPERTY_TYPE_CONSTRAINT_IN_WORLD_COORDINATES Boolean property specifies whether or not the ::KZU_PROPERTY_TYPE_CONSTRAINT_POSITION and
 * ::KZU_PROPERTY_TYPE_CONSTRAINT_ORIENTATION properties' corresponding KzuTransformedObjectNode (::KZ_TRUE) or the target KzuObjectNode itself 
 * (::KZ_FALSE) is used for getting the transformation matrix.
 *
 * ::KZU_PROPERTY_TYPE_CONSTRAINT_ORIENTATION pointer property specifies a target KzuObjectNode which rotation is used for this object node.
 *
 * ::KZU_PROPERTY_TYPE_LOOK_AT pointer property specifies a target KzuObjectNode that the KzuTransformedObjectNode corresponding to the object node
 * having the property will be made to "look at" by changing its orientation. The final transformation of the KzuObjectNode having this property is not changed.
 *
 * ::KZU_PROPERTY_TYPE_OBJECT__PATH is an internal property used by Kanzi.
 *
 * ::KZU_PROPERTY_TYPE_OBJECT_NODE_PREFAB_TEMPLATE_SOURCE is an internal property used by Kanzi.
 * 
 * Copyright 2008-2014 by Rightware. All rights reserved.
 */
#ifndef KZU_OBJECT_H
#define KZU_OBJECT_H


#include <user/scene_graph/kzu_object_common.h>
#include <user/properties/kzu_property_manager.h>

#include <core/util/collection/kzc_dynamic_array.h>
#include <core/util/math/kzc_matrix4x4.h>
#include <core/util/math/kzc_vector3.h>

#include <system/kzs_types.h>
#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/** Object type identifier for all renderable object types. */
extern const KzuObjectType KZU_OBJECT_TYPE_RENDERABLE;


/* Forward declarations. */
struct KzcInputStream;
struct KzcMemoryManager;
struct KzcVolume;
struct KzuAnimationItem;
struct KzuAnimationPlayer;
struct KzuBinaryFileInfo;
struct KzuBindingRule;
struct KzuBoundingVolume;
struct KzcDynamicArray;
struct KzuMaterial;
struct KzuMessageDispatcher;
struct KzuPropertyManager;
struct KzuUIDomain;
struct KzuPropertyType;
struct KzuResource;
struct KzuRenderer;
struct KzuScreen;
struct KzuStyle;
struct KzuTimeLineEntry;
struct KzuInputManipulator;
struct KzuTransformedObjectNode;
struct KzuTrigger;
struct KzuObjectNodeResourceDictionary;


/** Horizontal alignment. */
enum KzuObjectNodeHorizontalAlignment
{
    KZU_OBJECT_NODE_HORIZONTAL_ALIGNMENT_LEFT = 0,
    KZU_OBJECT_NODE_HORIZONTAL_ALIGNMENT_RIGHT = 1,
    KZU_OBJECT_NODE_HORIZONTAL_ALIGNMENT_CENTER = 2,
    KZU_OBJECT_NODE_HORIZONTAL_ALIGNMENT_STRETCH = 3,
    KZU_OBJECT_NODE_HORIZONTAL_ALIGNMENT_COUNT  /**< Last enum value for validity checks. */
};

/** Vertical alignment. */
enum KzuObjectNodeVerticalAlignment
{
    KZU_OBJECT_NODE_VERTICAL_ALIGNMENT_BOTTOM = 0,
    KZU_OBJECT_NODE_VERTICAL_ALIGNMENT_TOP = 1,
    KZU_OBJECT_NODE_VERTICAL_ALIGNMENT_CENTER = 2,
    KZU_OBJECT_NODE_VERTICAL_ALIGNMENT_STRETCH = 3,
    KZU_OBJECT_NODE_VERTICAL_ALIGNMENT_COUNT  /**< Last enum value for validity checks. */
};

/** Depth alignment. */
enum KzuObjectNodeDepthAlignment
{
    KZU_OBJECT_NODE_DEPTH_ALIGNMENT_BACK = 0,
    KZU_OBJECT_NODE_DEPTH_ALIGNMENT_FRONT = 1,
    KZU_OBJECT_NODE_DEPTH_ALIGNMENT_CENTER = 2,
    KZU_OBJECT_NODE_DEPTH_ALIGNMENT_STRETCH = 3,
    KZU_OBJECT_NODE_DEPTH_ALIGNMENT_COUNT  /**< Last enum value for validity checks. */
};


/**
* \struct KzuObjectNode
* Base structure for object node. Contains information of node type (mesh, light, camera, ...), transformation,
* list of child object nodes and set of properties.
*/
struct KzuObjectNode;


/** Read-only iterator for object node tree. */
struct KzuObjectNodeTreeIterator
{
    struct KzuObjectNode* rootObjectNode_private; /**< Root node where the iteration started from. */
    struct KzuObjectNode* currentObjectNode_private; /**< Current node in the iteration. */
    struct KzuObjectNode* nextObjectNode_private; /**< Next node in the iteration. */
};

/** Iterator for object node children that supports removing the current child. */
struct KzuObjectNodeChildIterator
{
    struct KzuObjectNode* objectNode_private;  /**< Reference to the object node accessed by this iterator. */
    kzInt currentIndex_private; /**< Current index in the iterator. */
};


/** Initializes an object node. */
kzsError kzuObjectNodeInitialize(struct KzuObjectNode* objectNode);

/** Uninitializes an object node. */
kzsError kzuObjectNodeUninitialize(struct KzuObjectNode* objectNode);

/** Loads object node from binary. */
kzsError kzuObjectNodeLoadFromKZB(struct KzuObjectNode* objectNode, struct KzcInputStream* inputStream,
                                  const struct KzuBinaryFileInfo* file);


/**
 * Deletes an object node and all its children recursively. *
 * Traverses the tree depth-first. Objects are uninitialized before deletion.
 * Removes all deleted object nodes from their parents.
 */
kzsError kzuObjectNodeDelete(struct KzuObjectNode* objectNode);

/** Deletes an object node and all its children in the idle loop. */
kzsError kzuObjectNodeDeleteAsync(struct KzuObjectNode* object);

/** Get the property manager associated with an object node. */
struct KzuPropertyManager* kzuObjectNodeGetPropertyManager(const struct KzuObjectNode* objectNode);
/** Get the message dispatcher associated with an object node. */
struct KzuMessageDispatcher* kzuObjectNodeGetMessageDispatcher(const struct KzuObjectNode* objectNode);
/** Get the UIDomain associated with an object node. */
struct KzuUIDomain* kzuObjectNodeGetUIDomain(const struct KzuObjectNode* objectNode);

/** Destroys all object node data loaded from KZB, including properties, bindings, triggers, resources etc. */
kzsError kzuObjectNodeRemoveKZBData(const struct KzuObjectNode* objectNode);

/** 
* Creates a copy of given object node without any of its descendants. All properties in the objects are also copied. 
* New nodes will contain references to the data of the source objects. Copying attached nodes is not supported.
*/
kzsError kzuObjectNodeCopy(const struct KzcMemoryManager* memoryManager, const struct KzuObjectNode* sourceObject,
                           struct KzuObjectNode** out_objectNode);

/** 
* Creates a copy of given object node and all its descendants. All properties in the objects are also copied. 
* New nodes will contain references to the data of the source objects. Copying attached nodes is not supported.
*/
kzsError kzuObjectNodeCopyWithChildren(const struct KzcMemoryManager* memoryManager, const struct KzuObjectNode* sourceObject,
                                       struct KzuObjectNode** out_objectNode);

/** Gets the parent of an object node. */
struct KzuObjectNode* kzuObjectNodeGetParent(const struct KzuObjectNode* objectNode);
/** Removes object from parent, if there is such. */
kzsError kzuObjectNodeRemoveFromParent(struct KzuObjectNode* objectNode);
/**
 * Returns whether the parent node is the parent of the child node at any level in the scene graph hierarchy.
 * \param parentNode Object node to check whether it is the ancestor of `childNode`.
 * \param childNode Object node to check whether it is the descendant of `parentNode`.
 * \return Returns `KZ_TRUE` if `parentNode` is the parent of `childNode` at any level, otherwise returns `KZ_FALSE`.
 */
kzBool kzuObjectNodeIsAncestorOf(const struct KzuObjectNode* parentNode, const struct KzuObjectNode* childNode);


/** Sets whether the object node is renderable. */
void kzuObjectNodeSetIsRenderable(struct KzuObjectNode* objectNode, kzBool state);

/** Returns whether given object node is renderable. */
kzBool kzuObjectTypeIsRenderable(const struct KzuObjectNode* objectNode);

/** Gets the scene object node that contains the given object node. */
struct KzuObjectNode* kzuObjectNodeGetSceneObject(const struct KzuObjectNode* objectNode);
/** As kzuObjectNodeGetSceneObject, but return as scene. */
struct KzuScene* kzuObjectNodeGetScene(const struct KzuObjectNode* objectNode);

/** Gets the closest layer that is a parent of the given object node. */
struct KzuLayer* kzuObjectNodeGetParentLayer(const struct KzuObjectNode* objectNode);
/** Gets the root layer that contains the given object node. */
struct KzuLayer* kzuObjectNodeGetRootLayer(struct KzuObjectNode* objectNode);
/** Gets the root object node from the given object, i.e. such parent node that doesn't contain parent anymore, can be any type (e.g. screen, scene, layer, empty node). */
struct KzuObjectNode* kzuObjectNodeGetRoot(struct KzuObjectNode* objectNode);
/** Gets the root screen object from the given object. If the object node is not attached to a screen, returns KZ_NULL. */
struct KzuScreen* kzuObjectNodeGetScreen(struct KzuObjectNode* objectNode);
/** Returns KZ_TRUE if the object node is attached to a screen or one of its descendants. */
kzBool kzuObjectNodeIsAttached(const struct KzuObjectNode* objectNode);
/** Returns KZ_TRUE during the call to virtual kzuObjectNodeOnDetached and KZ_FALSE otherwise. */
kzBool kzuObjectNodeIsDetaching(const struct KzuObjectNode* objectNode);

/** Adds a child node for object node.
* Adding a 3D object node as a child of a 2D object node is only allowed when adding a scene to a viewport layer.
* Screens can have only one child which is a layer.
* \return KZS_SUCCESS on success. KZU_EXCEPTION_INVALID_ADD_CHILD_OPERATION if the above rules are violated.
*/
kzsException kzuObjectNodeAddChild(struct KzuObjectNode* parentObject, struct KzuObjectNode* childNode);
/** Adds a child node for object node to given index.
* Adding a 3D object node as a child of a 2D object node is only allowed when adding a scene to a viewport layer.
* Screens can have only one child which is a layer.
* \return KZS_SUCCESS on success. KZU_EXCEPTION_INVALID_ADD_CHILD_OPERATION if the above rules are violated.
*/
kzsException kzuObjectNodeAddChildAtIndex(struct KzuObjectNode* parentObject, kzUint index, struct KzuObjectNode* childNode);
/** Removes child node from parent object. */
kzsError kzuObjectNodeRemoveChild(struct KzuObjectNode* parentObject, struct KzuObjectNode *childObject);
/** Removes child node from parent object node at specified index. */
kzsError kzuObjectNodeRemoveChildByIndex(struct KzuObjectNode* parentObject, kzUint index);
/** Removes all child nodes from parent object. */
kzsError kzuObjectNodeRemoveAllChildren(struct KzuObjectNode* parentObject);
/** Checks if parent object node contains child object node. */
kzBool kzuObjectNodeHasChild(const struct KzuObjectNode* parentObjectNode, const struct KzuObjectNode* childObjectNode);
/** Checks if parent object node contains child object node. It's safe to use this function even if the child node may not be valid. */
kzBool kzuObjectNodeHasChildSafe(const struct KzuObjectNode* parentObjectNode, const struct KzuObjectNode* childObjectNode);
/** Gets child count from object. */
kzUint kzuObjectNodeGetChildCount(const struct KzuObjectNode* parentObject);
/** Returns child objects as iterator from object node */
struct KzcDynamicArrayIterator kzuObjectNodeGetChildren(const struct KzuObjectNode* objectNode);
/** Returns a child from given index from object node. */
struct KzuObjectNode* kzuObjectNodeGetChildAtIndex(const struct KzuObjectNode* objectNode, kzUint index);
/** Returns the index of a child in an object node. */
kzsError kzuObjectNodeGetIndexOfChild(const struct KzuObjectNode* parentObjectNode, const struct KzuObjectNode* childObjectNode, kzUint *out_index);


/** Sets a name for object node */
kzsError kzuObjectNodeSetName(struct KzuObjectNode* objectNode, kzString name);
/** Returns an object node's name. */
kzString kzuObjectNodeGetName(const struct KzuObjectNode* objectNode);
/** Returns the full path to this object node. The returned string must be freed with kzcStringDelete. */
kzsError kzuObjectNodeGetPath(const struct KzuObjectNode* objectNode, kzMutableString* out_path);
/** Returns a studio-friendly (not including nodes that studio does not know about) full path to this object node.
 * The returned string must be freed with kzcStringDelete. */
kzsError kzuObjectNodeGetPathForStudio(const struct KzuObjectNode* objectNode, kzMutableString* out_path);
/** Gets tree height from the object node to the parent, if no parents, height = 1, if single parent, and parent's parent = NULL, height = 2 and so on. */
kzUint kzuObjectNodeGetTreeHeight(struct KzuObjectNode* objectNode);
/** Returns the relative path from base object node to target object node, KZ_NULL if not found. The returned string must be freed with kzcStringDelete. */
kzsError kzuObjectNodeGetRelativePath(struct KzuObjectNode* targetObjectNode, struct KzuObjectNode* baseObjectNode, kzMutableString* out_path);


/** Returns whether object node or one of its base types is of the given type. */
kzBool kzuObjectNodeIsTypeOf(const struct KzuObjectNode* objectNode, const KzuObjectType objectType);
/** Returns object node's type, KZU_OBJECT_TYPE_X. */ 
KzuObjectType kzuObjectNodeGetType(const struct KzuObjectNode* objectNode);

/** Returns the position of the object node as vector3. */
struct KzcVector3 kzuObjectNodeGetPositionVector(const struct KzuObjectNode* objectNode);


/** Sets an identity matrix for object node. */
kzsError kzuObjectNodeSetIdentityTransformation(const struct KzuObjectNode* objectNode);
/** Sets a top left 3x3 part of object node transformation as identity (clear rotation & scaling). 
    Leaves other parts of matrix untouched. */
kzsError kzuObjectNodeSetIdentity3x3Transformation(const struct KzuObjectNode* objectNode);
/** Translates object node. */
kzsError kzuObjectNodeTranslate(const struct KzuObjectNode* objectNode, kzFloat x, kzFloat y, kzFloat z);
/** Sets position for object node. */
kzsError kzuObjectNodeSetPosition(const struct KzuObjectNode* objectNode, kzFloat x, kzFloat y, kzFloat z);
/** Rotates object node by specific axis, rotation angle in degrees. */
kzsError kzuObjectNodeRotate(const struct KzuObjectNode* objectNode, kzFloat angleInDegrees, kzFloat x, kzFloat y, kzFloat z);
/** Scales object node uniformly. */
kzsError kzuObjectNodeScale(const struct KzuObjectNode* objectNode, kzFloat scale);
/** Scales object node non-uniformly. */
kzsError kzuObjectNodeScaleXYZ(const struct KzuObjectNode* objectNode, kzFloat scaleX, kzFloat scaleY, kzFloat scaleZ);

/** Finds first object node of given type from root nodes' hierarchy. */
struct KzuObjectNode* kzuObjectNodeFindFirstChildOfType(struct KzuObjectNode* rootObjectNode, KzuObjectType objectType);
/** Finds object node from root nodes' hierarchy by object name. KZ_NULL if no object was found. */
struct KzuObjectNode* kzuObjectNodeFindObjectNodeByName(struct KzuObjectNode* rootObjectNode, kzString objectName);
/** Finds first object node from root nodes' hierarchy. KZ_NULL if no object was found. */
struct KzuObjectNode* kzuObjectNodeFindObjectNodeContainingPropertyType(struct KzuObjectNode* rootObjectNode, const struct KzuPropertyType* propertyType);

/** Notifies the object node about a changed property. */
kzsError kzuObjectNodeOnPropertyChanged(struct KzuObjectNode* objectNode, const struct KzuPropertyType* propertyType, enum KzuPropertyNotificationReason reason);

/** Gets bounding volume from object node. Returns KZ_NULL if the object is not renderable. */
kzsError kzuObjectNodeGetBoundingVolume(const struct KzuObjectNode* objectNode, struct KzuBoundingVolume** out_boundingVolume);

/** Renders the object if the object type has specified a renderer function. */
kzsError kzuObjectNodeRender(struct KzuRenderer* renderer, const struct KzuObjectNode* objectNode,
                             const struct KzuTransformedObjectNode* transformedObjectNode,
                             struct KzcMatrix4x4* worldTransformation);

/** Returns the size of given object node. */
kzsError kzuObjectNodeGetSize(const struct KzuObjectNode* objectNode, struct KzcVector3* out_size);
/** Returns the minimum coordinates for given object nodes bounding volume. */
kzsError kzuObjectNodeGetMaximumBoundingBoxCoordinates(const struct KzuObjectNode* objectNode, struct KzcVector3* out_size);
/** Returns the maximum coordinates for given object nodes bounding volume. */
kzsError kzuObjectNodeGetMinimumBoundingBoxCoordinates(const struct KzuObjectNode* objectNode, struct KzcVector3* out_size);

/** Adds a resource manager resource to an object node. If resourceID already exists in object, removes the existing entry. If resourceURL is NULL, error is thrown. */
kzsError kzuObjectNodeAddResource(const struct KzuObjectNode* objectNode, kzString resourceId, kzString resourceUrl);
/** Removes a resource with given ID from object node resource dictionary. Does not do anything if resourceID was not found. */
kzsError kzuObjectNodeRemoveResource(const struct KzuObjectNode* objectNode, kzString resourceId);
/** Returns if object node resource dictionary contains the resource with given ID. Resource can be any type: style, alias or resource manager resource. */
kzBool kzuObjectNodeContainsResource(const struct KzuObjectNode* objectNode, kzString resourceID);
/** Adds anonymous resource (such as style) for object node resources. */
kzsError kzuObjectNodeAddAnonymousResource(struct KzuObjectNode* objectNode, struct KzuResource* resource);
/** Removes anonymous resource from object node resources. */
kzsError kzuObjectNodeRemoveAnonymousResource(struct KzuObjectNode* objectNode, struct KzuResource* resource);
/** Adds anonymous resource (such as style) acquired from the given URL for object node resources. */
kzsError kzuObjectNodeAddAnonymousResourceURL(struct KzuObjectNode* objectNode, kzString resourceURL);
/** Removes anonymous resource from the given URL from object node resources. */
kzsError kzuObjectNodeRemoveAnonymousResourceURL(struct KzuObjectNode* objectNode, kzString resourceURL);

/** Adds alias resource to an object node. */
kzsError kzuObjectNodeAddAliasResource(const struct KzuObjectNode* objectNode, kzString resourceId, kzString targetPath);
/** Removes alias resource from an object node. */
kzsError kzuObjectNodeRemoveAliasResource(const struct KzuObjectNode* objectNode, kzString resourceId);


/** Acquires a resource from the object node or the node's closest ancestor having the resource.
 *  Acquiring a resource increases its reference count by one. The caller should call kzuResourceRelease to decrease the reference count
 *  by one after she is done with it.
 * \param objectNode The search of the resource resourceId starts from this object node and continues to the node's ancestors.
 * \param resourceId Name of the resource.
 * \param out_resource A pointer that is set to point to the resource if it is found or KZ_NULL.
 */
kzsException kzuObjectNodeAcquireResource(const struct KzuObjectNode* objectNode, kzString resourceId, struct KzuResource** out_resource);

/** Copy resources from one object node to another. 
* \param preserveTarget Flag indicates whether preserve resource in resource dictionary of target node.
*/
kzsError kzuObjectNodeCopyResources(const struct KzuObjectNode* sourceObjectNode, struct KzuObjectNode* targetObjectNode, kzBool preserveTarget);

/** Gets all resources of the object node. */
struct KzcDynamicArrayIterator kzuObjectNodeGetResources(const struct KzuObjectNode* objectNode);

/** Gets all resources of the object node. */
const struct KzuObjectNodeResourceDictionary* kzuObjectNodeGetResourceDictionary(const struct KzuObjectNode* objectNode);

/** Transfers the ownership and attaches an input manipulator to an object node. */
kzsError kzuObjectNodeAttachInputManipulator(struct KzuObjectNode* objectNode, struct KzuInputManipulator* inputManipulator);
/** Removes the ownership and detaches an input manipulator from an object node. */
kzsError kzuObjectNodeDetachInputManipulator(const struct KzuObjectNode* objectNode, struct KzuInputManipulator* inputManipulator);
/** Gets the input manipulator iterator. */
struct KzcDynamicArrayIterator kzuObjectNodeGetInputManipulators(const struct KzuObjectNode* objectNode);

/** Transfers the ownership of a binding rule to an object node. */
kzsError kzuObjectNodeAddBinding(struct KzuObjectNode* objectNode, struct KzuBindingRule* rule);
/** Transfers the ownership of a binding rule to an object node and sets the owner of binding rule. */
kzsError kzuObjectNodeAddBindingWithOwner(struct KzuObjectNode* objectNode, struct KzuBindingRule* rule, const void* owner);
/** Removes the ownership and detaches a binding rule from an object node. */
kzsError kzuObjectNodeRemoveBinding(const struct KzuObjectNode* objectNode, struct KzuBindingRule* rule);
/** Gets the bindings iterator. */
struct KzcDynamicArrayIterator kzuObjectNodeGetBindings(const struct KzuObjectNode* objectNode);

/** Transfers the ownership of a trigger to an object node. */
kzsError kzuObjectNodeAddTrigger(struct KzuObjectNode* objectNode, struct KzuTrigger* trigger);
/** Transfers the ownership of a trigger to an object node and sets the owner of the trigger. */
kzsError kzuObjectNodeAddTriggerWithOwner(struct KzuObjectNode* objectNode, struct KzuTrigger* trigger, const void* owner);
/** Removes the ownership of a trigger from an object node. */
kzsError kzuObjectNodeRemoveTrigger(const struct KzuObjectNode* objectNode, struct KzuTrigger* trigger);
/** Gets the trigger iterator. */
struct KzcDynamicArrayIterator kzuObjectNodeGetTriggers(const struct KzuObjectNode* objectNode);

/** Sets object node transformation from matrix. */
kzsError kzuObjectNodeSetTransformation(const struct KzuObjectNode* objectNode, const struct KzcMatrix4x4* value);
/**
 * Calculates the node transformation from scaling, rotation, and translation properties.
 * For KzuScene this always returns an identity matrix regardless what SRT values have been set.
 * This simplifies calculations relative to the scene (e.g. bounding boxes).
 */
struct KzcMatrix4x4 kzuObjectNodeGetTransformation(const struct KzuObjectNode* objectNode);

/** Sets the layout transformation of the object. */
kzsError kzuObjectNodeSetLayoutTransformation(struct KzuObjectNode* objectNode, const struct KzcMatrix4x4* value);
/** Gets the layout transformation of the object. */
kzsError kzuObjectNodeGetLayoutTransformation(struct KzuObjectNode* objectNode, struct KzcMatrix4x4* out_value);

/** Sets the final transformation of the object. */
void kzuObjectNodeSetFinalTransformation(struct KzuObjectNode* objectNode, const struct KzcMatrix4x4* value);
/** Gets the final transformation of the object. */
void kzuObjectNodeGetFinalTransformation(const struct KzuObjectNode* objectNode, struct KzcMatrix4x4* out_value);

/** Calculates the node base transformation from scaling, rotation, and translation properties. */
struct KzcMatrix4x4 kzuObjectNodeGetBaseTransformationDefaultFromSRT(const struct KzuObjectNode* objectNode);

/** Checks if the node and all of its ancestors are visible. */
kzBool kzuObjectNodeIsEffectivelyVisible(const struct KzuObjectNode* objectNode);
/** Checks if the node and all of its ancestors are enabled. */
kzBool kzuObjectNodeIsEffectivelyEnabled(const struct KzuObjectNode* objectNode);

/** Set a change flag. */
void kzuObjectNodeSetChangeFlag(struct KzuObjectNode* objectNode, kzU32 flag);
/** Clear a change flag. */
void kzuObjectNodeClearChangeFlag(struct KzuObjectNode* objectNode, kzU32 flag);
/** Check if a change flag is set. */
kzBool kzuObjectNodeIsChangeFlagSet(const struct KzuObjectNode* objectNode, kzU32 flag);

/** Set an child change flag. */
void kzuObjectNodeSetChildChangeFlag(struct KzuObjectNode* objectNode, kzU32 flag);
/** Clear an child change flag. */
void kzuObjectNodeClearChildChangeFlag(struct KzuObjectNode* objectNode, kzU32 flag);
/** Check if child change flags match. */
kzBool kzuObjectNodeIsChildChangeFlagSet(const struct KzuObjectNode* objectNode, kzU32 flag);
/** Check if any child change flags (corresponding to given mask) are set. */
kzBool kzuObjectNodeIsAnyChildChangeFlagSet(const struct KzuObjectNode* objectNode, kzU32 flag);

/** Check if layout is invalid for a node. */
kzBool kzuObjectNodeIsInvalidLayout(const struct KzuObjectNode* objectNode);
/** Invalidate layout for an object node. */
void kzuObjectNodeInvalidateLayout(struct KzuObjectNode* objectNode);
/** Invalidate layout for an object node and all of its children. */
void kzuObjectNodeInvalidateLayoutRecursive(struct KzuObjectNode* objectNode);
/** Validate layout for an object node. */
void kzuObjectNodeValidateLayout(struct KzuObjectNode* objectNode);

/** Check if a node needs arrange. */
kzBool kzuObjectNodeIsInvalidArrange(const struct KzuObjectNode* objectNode);
/** Invalidate arrange. */
void kzuObjectNodeInvalidateArrange(struct KzuObjectNode* objectNode);
/** Validate arrange. */
void kzuObjectNodeValidateArrange(struct KzuObjectNode* objectNode);

/** Returns if object node render flag is invalid. */
kzBool kzuObjectNodeIsInvalidRender(const struct KzuObjectNode* objectNode);
/** Validates render for object node. */
void kzuObjectNodeValidateRender(struct KzuObjectNode* objectNode);
/** Invalidates render for object node. */
void kzuObjectNodeInvalidateRender(struct KzuObjectNode* objectNode);
/** Invalidates render recursively for object node. */
void kzuObjectNodeInvalidateRenderRecursive(struct KzuObjectNode* objectNode);

/** Returns if object node render tree flag is invalid. */
kzBool kzuObjectNodeIsInvalidRenderTree(const struct KzuObjectNode* objectNode);
/** Validates render tree flag of object node. */
void kzuObjectNodeValidateRenderTree(struct KzuObjectNode* objectNode);
/** Invalidates render tree flag of object node. */
void kzuObjectNodeInvalidateRenderTree(struct KzuObjectNode* objectNode);


/** Returns if object render sub mask flag is invalid. */
kzBool kzuObjectNodeIsInvalidRenderSubmask(const struct KzuObjectNode* objectNode);
/** Invalidates render submask for object node. Can be validated with */
void kzuObjectNodeInvalidateRenderSubmask(struct KzuObjectNode* objectNode);

/** Helper function for observing if object is invalid partial rendering object (needs re-render). */
kzBool kzuObjectNodeIsInvalidPartialRenderingObject(const struct KzuObjectNode* objectNode);
/** Helper function for invalidating partial rendering object (rerender will be required with partial rendering). */
void kzuObjectNodeInvalidatePartialRenderingObject(struct KzuObjectNode* objectNode);
/** Helper function for invvalidating partial rendering object recursively (rerender will be required with partial rendering). */
void kzuObjectNodeIsInvalidPartialRenderingObjectRecursive(struct KzuObjectNode* objectNode);
/** Helper function for validating partial rendering object (no more rerender is required). */
void kzuObjectNodeValidatePartialRenderingObject(struct KzuObjectNode* objectNode);

/** Helper function for observing if object triee is invalid for partial rendering (needs re-render). */
kzBool kzuObjectNodeIsInvalidPartialRenderingTree(const struct KzuObjectNode* objectNode);
/** Helper function for invalidating partial rendering tree (rerender will be required). */
void kzuObjectNodeInvalidatePartialRenderingTree(struct KzuObjectNode* objectNode);
/** Helper function for validating partial rendering tree (no more rerender is required). */
void kzuObjectNodeValidatePartialRenderingTree(struct KzuObjectNode* objectNode);

/** Set content desired size for an object. */
kzsError kzuObjectNodeSetContentDesiredSize(struct KzuObjectNode* objectNode, const struct KzcVector3* contentDesiredSize);
/** Get content desired size of an object. */
kzsError kzuObjectNodeGetContentDesiredSize(struct KzuObjectNode* objectNode, struct KzcVector3* contentDesiredSize);
/** Set core desired size for an object. */
kzsError kzuObjectNodeSetCoreDesiredSize(struct KzuObjectNode* objectNode, const struct KzcVector3* coreDesiredSize);
/** Get core desired size of an object. */
kzsError kzuObjectNodeGetCoreDesiredSize(struct KzuObjectNode* objectNode, struct KzcVector3* coreDesiredSize);
/** Set desired size for an object. */
kzsError kzuObjectNodeSetDesiredSize(struct KzuObjectNode* objectNode, const struct KzcVector3* desiredSize);
/** Get desired size for of object. */
kzsError kzuObjectNodeGetDesiredSize(struct KzuObjectNode* objectNode, struct KzcVector3* desiredSize);
/** Set allocated size for an object. */
kzsError kzuObjectNodeSetAllocatedSize(struct KzuObjectNode* objectNode, const struct KzcVector3* layoutSize);
/** Get allocated size of an object. */
kzsError kzuObjectNodeGetAllocatedSize(struct KzuObjectNode* objectNode, struct KzcVector3* layoutSize);
/** Set actual size for an object. */
kzsError kzuObjectNodeSetActualSize(struct KzuObjectNode* objectNode, const struct KzcVector3* actualSize);
/** Get actual size of an object. */
kzsError kzuObjectNodeGetActualSize(struct KzuObjectNode* objectNode, struct KzcVector3* actualSize);
/** Set bounding box size for an object. */
kzsError kzuObjectNodeSetLayoutBoundingBoxSize(struct KzuObjectNode* objectNode, const struct KzcVector3* bboxMin, const struct KzcVector3* bboxMax);
/** Get bounding box size for an object. */
kzsError kzuObjectNodeGetLayoutBoundingBoxSize(struct KzuObjectNode* objectNode, struct KzcVector3* out_bboxMin, struct KzcVector3* out_bboxMax);
/** Set allocated offset for an object. */
kzsError kzuObjectNodeSetAllocatedOffset(struct KzuObjectNode* objectNode, const struct KzcVector3* allocatedOffset);
/** Get allocated offset of an object. */
kzsError kzuObjectNodeGetAllocatedOffset(struct KzuObjectNode* objectNode, struct KzcVector3* allocatedOffset);
/** Set stretch scale for an object. */
kzsError kzuObjectNodeSetStretchScale(struct KzuObjectNode* objectNode, const struct KzcVector3* stretchScale);
/** Get stretch scale of an object. */
kzsError kzuObjectNodeGetStretchScale(struct KzuObjectNode* objectNode, struct KzcVector3* stretchScale);
/** Set pivot offset for an object. */
kzsError kzuObjectNodeSetPivotOffset(struct KzuObjectNode* objectNode, const struct KzcVector3* pivotOffset);
/** Get pivot offset of an object. */
kzsError kzuObjectNodeGetPivotOffset(struct KzuObjectNode* objectNode, struct KzcVector3* pivotOffset);

/** Perform the default measure step. */
kzsError kzuObjectNodeDefaultMeasure(struct KzuObjectNode* objectNode);
/** Perform the default arrange step. */
kzsError kzuObjectNodeDefaultArrange(struct KzuObjectNode* objectNode);

/** Get an object node by another node and a relative path. */
struct KzuObjectNode* kzuObjectNodeGetRelative(struct KzuObjectNode* objectNode, kzString relativePath);

/**
 * Adds timeline entry for object's animation player.
 * \param timeLineEntry Animation entry launched. KZ_NULL just to create the animation player.
 */
kzsError kzuObjectNodeAddTimeLineEntry(struct KzuObjectNode* objectNode, struct KzuTimeLineEntry* timeLineEntry);
/**
 * Adds animation item for object's animation player.
 * \param out_timeLineEntry Resulting timeline entry. KZ_NULL if not wanted to use.
 */
kzsError kzuObjectNodeAddAnimationItem(struct KzuObjectNode* objectNode, struct KzuAnimationItem* animationItem, kzBool reverse, kzInt repeatCount,
                                       struct KzuTimeLineEntry** out_timeLineEntry);
/** Set animation player time in an object and all of its children. */
void kzuObjectNodeSetAnimationPlayerTimeRecursive(const struct KzuObjectNode* objectNode, kzFloat currentTime);

/** Create an animation player that references this object node, attach to an animation player in parent node. */
kzsError kzuObjectCreateAnimationPlayerAttachToParentPlayer(struct KzuObjectNode* objectNode, struct KzuAnimationPlayer** out_animationPlayer);
/** Create an animation player that references this object node, attach to the master animation player in task scheduler. */
kzsError kzuObjectNodeCreateAnimationPlayerAttachToTaskScheduler(struct KzuObjectNode* objectNode, struct KzuAnimationPlayer** out_animationPlayer);
/** Attach given animation player to the task scheduler acquired via the object node. */
kzsError kzuObjectNodeAnimationPlayerAttachToTaskScheduler(const struct KzuObjectNode* objectNode, struct KzuAnimationPlayer* animationPlayer);
/** Returns animation player from object node. */
struct KzuAnimationPlayer* kzuObjectNodeGetAnimationPlayer(const struct KzuObjectNode* objectNode);

/** Gets first material from given object node tree. */
struct KzuMaterial* kzuObjectNodeGetFirstMaterial(const struct KzuObjectNode* objectNode);


/**
 * Returns a tree iterator to object node graph. The iterator traverses the sub-tree from the given object node.
 * Call kzuObjectNodeTreeIterate before accessing the first and any subsequent entries.
 */
struct KzuObjectNodeTreeIterator kzuObjectNodeGetTreeIterator(struct KzuObjectNode* rootObjectNode);

/** Finds the next entry in the object node tree iterator. Returns KZ_TRUE if next entry is found, otherwise KZ_FALSE. */
#define kzuObjectNodeTreeIterate(iterator_param) kzuObjectNodeTreeIterate_private(&iterator_param)
/** Returns the current object node in the object node tree iterator. */
#define kzuObjectNodeTreeIteratorGetValue(iterator_param) kzuObjectNodeTreeIteratorGetValue_private(&iterator_param)

/** \see kzuObjectNodeTreeIterate */
kzBool kzuObjectNodeTreeIterate_private(struct KzuObjectNodeTreeIterator* iterator);
/** \see kzuObjectNodeTreeIteratorGetValue */
struct KzuObjectNode* kzuObjectNodeTreeIteratorGetValue_private(const struct KzuObjectNodeTreeIterator* iterator);


/**
 * Returns an object node child iterator. The iterator returns each child of the object node.
 * Call kzuObjectNodeChildIterate before accessing the first and any subsequent entries.
 */
struct KzuObjectNodeChildIterator kzuObjectNodeGetChildIterator(struct KzuObjectNode* objectNode);

/** Finds the next entry in the object node child iterator. Returns KZ_TRUE if next entry is found, otherwise KZ_FALSE. */
#define kzuObjectNodeChildIterate(iterator_param) kzuObjectNodeChildIterate_private(&iterator_param)
/** Returns the current object node in the object node child iterator. */
#define kzuObjectNodeChildIteratorGetValue(iterator_param) kzuObjectNodeChildIteratorGetValue_private(&iterator_param)
/** Removes the current child object node from the iterated object node. */
#define kzuObjectNodeChildIteratorRemove(iterator_param) kzuObjectNodeChildIteratorRemove_private(&iterator_param)

/** \see kzuObjectNodeChildIterate */
kzBool kzuObjectNodeChildIterate_private(struct KzuObjectNodeChildIterator* iterator);
/** \see kzuObjectNodeChildIteratorGetValue */
struct KzuObjectNode* kzuObjectNodeChildIteratorGetValue_private(const struct KzuObjectNodeChildIterator* iterator);
/** \see kzuObjectNodeChildIteratorRemove */
kzsError kzuObjectNodeChildIteratorRemove_private(struct KzuObjectNodeChildIterator* iterator);


KZ_HEADER_END


#include "kzu_object_properties.h"


#endif
