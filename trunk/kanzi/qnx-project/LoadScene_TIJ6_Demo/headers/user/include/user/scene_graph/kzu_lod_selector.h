/**
* \file
* Level of detail selector node and data. Node inherited from KzuObjectNode.
* LOD selector node is pipeline element for selecting level of detail depending on camera distance / perspective size.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_LOD_SELECTOR_H
#define KZU_LOD_SELECTOR_H


#include <user/scene_graph/kzu_object_common.h>

#include <system/debug/kzs_error.h>
#include <system/kzs_types.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations. */
struct KzcInputStream;
struct KzcMemoryManager;
struct KzuBinaryFileInfo;
struct KzuObjectNode;
struct KzuUIDomain;
struct KzuFactory;


/**
* \struct KzuLODSelectorNode
* Structure for level of detail selector node, inherited from KzuObjectNode.
*/
struct KzuLODSelectorNode;


/** List of available LOD types. */
enum KzuLODType
{
    KZU_LOD_TYPE_INVALID, /**< Invalid LOD type. */
    KZU_LOD_TYPE_DISTANCE, /**< Distance LOD, z distance from camera. */
    KZU_LOD_TYPE_SCREEN_AREA /**< Screen area LOD, size in screen space in percentages. */
};


/** Object type identifier for LOD selector objects. */
extern const KzuObjectType KZU_OBJECT_TYPE_LOD_SELECTOR;


/** Registers LOD selector node type to factory. */
kzsError kzuLODSelectorNodeRegisterToFactory(const struct KzuFactory* factory);

/** Creates a new level of detail selector node. */
kzsError kzuLODSelectorNodeCreate(const struct KzcMemoryManager* memoryManager, kzString name, 
                                  struct KzuUIDomain* uiDomain, struct KzuLODSelectorNode** out_lodNode);


/** Returns LOD selector node from object node. */
struct KzuLODSelectorNode* kzuLODSelectorNodeFromObjectNode(const struct KzuObjectNode* objectNode);
/** Returns an object node from LOD selector node. */
struct KzuObjectNode* kzuLODSelectorNodeToObjectNode(const struct KzuLODSelectorNode* lodNode);


/** Gets LOD type from LOD selector object. */
enum KzuLODType kzuLODSelectorGetLODType(const struct KzuLODSelectorNode* lodSelectorNode);
/** Sets LOD type for LOD selector object. */
void kzuLODSelectorSetLODType(struct KzuLODSelectorNode* lodSelectorNode, enum KzuLODType lodType);


/** Gets number of LOD levels in this object. */
kzUint kzuLODSelectorNodeGetLevelCount(const struct KzuLODSelectorNode* lodSelectorNode);

/** Gets LOD level object with given constraint (distance, perspective size). */
struct KzuObjectNode* kzuLODSelectorNodeGetObjectAtConstraint(const struct KzuLODSelectorNode* lodSelectorNode, kzFloat constraint);

/** Gets object node at given index from LOD selector node. */
struct KzuObjectNode* kzuLODSelectorGetObjectNodeAtLevel(const struct KzuLODSelectorNode* lodSelectorNode, kzUint index);


KZ_HEADER_END


#endif
