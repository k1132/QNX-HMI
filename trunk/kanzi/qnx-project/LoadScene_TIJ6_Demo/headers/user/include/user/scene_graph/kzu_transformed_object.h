/**
* \file
* Transformed object node. KzuTransformedObjectNode is created from a scene graph object node (KzuObjectNode).
* It contains all the same characteristics as the KzuObjectNode, as the transformed object node keeps a pointer to the KzuObjectNode.
* The world transformation matrix returned by ::kzuTransformedObjectNodeGetMatrix() is calculated on-demand from the KzuObjectNode's
* ::KZU_PROPERTY_TYPE_TRANSFORMATION, layout and ::KZU_PROPERTY_TYPE_RENDER_TRANSFORMATION matrix when the transformed object node is
* created and whenever ::kzuTransformedObjectNodeRefreshChildren() is called for its parent. The calculated matrix is also stored to
* the referenced KzuObjectNode and can be obtained by calling ::kzuObjectNodeGetFinalTransformation().
*
* \see \ref kzu_object.h, kzu_scene.h.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_TRANSFORMED_OBJECT_H
#define KZU_TRANSFORMED_OBJECT_H


#include <core/util/collection/kzc_dynamic_array.h>
#include <core/util/math/kzc_matrix4x4.h>
#include <core/util/math/kzc_vector2.h>

#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declaration structures. */
struct KzcDynamicArray;
struct KzcMemoryManager;
struct KzcVector2;
struct KzcVector3;
struct KzcVolume;
struct KzuLayer;
struct KzuObjectNode;
struct KzuPropertyType;


/** 
* \struct KzuTransformedObjectNode
* Structure for transformed object node that contains reference to original object in scene graph and transformation
* in calculated world coordinates (affected by hierarchy).
*/
struct KzuTransformedObjectNode;


/** Creates new Transformed object node from regular scene graph object. Saves the reference to original scene graph object and copies the matrix data. */
kzsError kzuTransformedObjectNodeCreate(const struct KzcMemoryManager* memoryManager, struct KzuObjectNode* object, 
                                        const struct KzcMatrix4x4* parentTransform, kzBool parentTransformChanged,
                                        kzBool visible, kzBool instanciated, kzBool* out_transformChanged, struct KzuTransformedObjectNode** out_object);
/** Creates new transformed object node from a layer. */
kzsError kzuTransformedObjectNodeCreateFromLayer(const struct KzcMemoryManager* memoryManager, struct KzuObjectNode* objectNode,
                                                 kzBool visible, struct KzuTransformedObjectNode** out_transformedObjectNode);

/** Refreshes transformed object node's children to contain matrices from new matrix values in scene graph. */
kzsError kzuTransformedObjectNodeRefreshChildren(const struct KzuTransformedObjectNode* transformedObjectNode);

/** Adds a child transformed object for parent. */
struct KzuTransformedObjectNode* kzuTransformedObjectNodeGetParent(const struct KzuTransformedObjectNode* transformedObjectNode);
/** Adds a child transformed object for parent. */
kzsError kzuTransformedObjectNodeAddChildNode(struct KzuTransformedObjectNode* parentObject, 
                                              struct KzuTransformedObjectNode* childNode);
/** Removes transformed object node from parent and moves its children upper in hierarchy. */
kzsError kzuTransformedObjectNodeRemove(struct KzuTransformedObjectNode* parentObject, 
                                        const struct KzuTransformedObjectNode* destObject);
/** Copies a object without children to the new node. */
kzsError kzuTransformedObjectNodeCopyWithoutChildren(const struct KzcMemoryManager* memoryManager, 
                                                     const struct KzuTransformedObjectNode* sourceObject, 
                                                     struct KzuTransformedObjectNode** out_object);
/** Sets transformed object node instanciated from given node. */
void kzuTransformedObjectNodeSetInstanciated(struct KzuTransformedObjectNode* node, struct KzuTransformedObjectNode* instanciatorNode);
/** Gets instanciator from given node. */
struct KzuTransformedObjectNode* kzuTransformedObjectNodeGetInstanciatorNode(const struct KzuTransformedObjectNode* node);

/** Creates an array from tree. */
kzsError kzuTransformedObjectTreeToDynamicArray(const struct KzcMemoryManager* memoryManager, const struct KzuTransformedObjectNode* rootNode, 
                                                struct KzcDynamicArray** out_dynamicArray);

/** Returns a children of transformed object node as iterator (list of KzuTransformedObjectNode:s). */
struct KzcDynamicArrayIterator kzuTransformedObjectNodeGetChildren(const struct KzuTransformedObjectNode* transformedObjectNode);
/** Returns the child count. */
kzUint kzuTransformedObjectNodeGetChildCount(const struct KzuTransformedObjectNode* transformedObjectNode);
/** Returns a child from given index from object node. */
struct KzuTransformedObjectNode* kzuTransformedObjectNodeGetChildAtIndex(const struct KzuTransformedObjectNode* transformedObjectNode, kzUint index);
/** Returns a KzuObjectNode owned by transformed object node. */
struct KzuObjectNode* kzuTransformedObjectNodeGetObjectNode(const struct KzuTransformedObjectNode* transformedObjectNode);
/** Finds transformed object node from destination object node's direct children. NULL if nothing was found. */
struct KzuTransformedObjectNode* kzuTransformedObjectNodeFindChildObjectNode(const struct KzuTransformedObjectNode* transformedObjectNode,
                                                                             const struct KzuObjectNode* objectToFind);
/** Finds transformed object node from destination object node's direct descendants. NULL if nothing was found. */
struct KzuTransformedObjectNode* kzuTransformedObjectNodeFindChildObjectNodeFromDescendants(const struct KzuTransformedObjectNode* transformedObjectNode,
                                                                                            const struct KzuObjectNode* objectToFind);
/** Finds given transformed object node from destination transformed object node's descendants. Returns KZ_NULL if nothing was found. */
struct KzuTransformedObjectNode* kzuTransformedObjectNodeFindChildTransformedObjectNodeFromDescendants(const struct KzuTransformedObjectNode* transformedObjectNode,
                                                                                                       const struct KzuTransformedObjectNode* transformedObjectNodeToFind);
/** Gets bounding volume union from transformed object node and its children. */
kzsError kzuTransformedObjectNodeGetBoundingVolumeUnionWorld(const struct KzuTransformedObjectNode* transformedObjectNode, struct KzcVolume* out_volume);
/** Gets bounding volume union from transformed object node without children taken into account. */
kzsError kzuTransformedObjectNodeGetBoundingVolumeWorld(const struct KzuTransformedObjectNode* transformedObjectNode, struct KzcVolume* out_volume);

/** Sets the world matrix for transformed object node. */
void kzuTransformedObjectNodeSetMatrix(struct KzuTransformedObjectNode* transformedObjectNode, const struct KzcMatrix4x4* matrix);
/** Returns the world matrix of transformed object node. */
struct KzcMatrix4x4 kzuTransformedObjectNodeGetMatrix(const struct KzuTransformedObjectNode* transformedObjectNode);


/** Returns a position of this transformed object node */
void kzuTransformedObjectNodeGetPosition(const struct KzuTransformedObjectNode* transformedObjectNode, struct KzcVector3* out_position);
/** Finds transformed object node from object list. */
struct KzuTransformedObjectNode* kzuTransformedObjectListFindObject(const struct KzcDynamicArray* objectList,
                                                                    const struct KzuObjectNode* objectToFind);

/** Returns visibility of a transformed object node. */
kzBool kzuTransformedObjectNodeIsVisible(const struct KzuTransformedObjectNode* transformedObjectNode);


KZ_HEADER_END


#endif
