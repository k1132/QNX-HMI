/**
 * \file
 * Empty object node.
 * 
 * The empty node is a ::KzuObjectNode that behaves differently when its parent is a ::KzuUiComponentNode. When the parent is not a ::KzuUiComponentNode,
 * the empty node does not layout its children in any way, but when the parent is a ::KzuUiComponentNode, the empty node acts as if it calculates
 * a center point of the children and causes the children's transformation be relative to the point.
 *
 * Copyright 2008-2014 by Rightware. All rights reserved.
 */
#ifndef KZU_EMPTY_NODE_H
#define KZU_EMPTY_NODE_H


#include <user/scene_graph/kzu_object_common.h>

#include <system/kzs_types.h>
#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/** Object type identifier for empty objects. */
extern const KzuObjectType KZU_OBJECT_TYPE_EMPTY;


/* Forward declarations. */
struct KzcInputStream;
struct KzcMemoryManager;
struct KzuBinaryFileInfo;
struct KzuObjectNode;
struct KzuUIDomain;
struct KzuFactory;


/** Registers empty node type to factory. */
kzsError kzuEmptyNodeRegisterToFactory(const struct KzuFactory* factory);

/** Creates an empty object node. */
kzsError kzuEmptyNodeCreate(const struct KzcMemoryManager* memoryManager, kzString name, 
                            struct KzuUIDomain* uiDomain, struct KzuObjectNode** out_emptyObjectNode);


KZ_HEADER_END


#endif
