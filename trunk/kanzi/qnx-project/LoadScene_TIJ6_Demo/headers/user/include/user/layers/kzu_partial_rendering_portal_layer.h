/**
* \file
* Partial rendering portal layer class.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_PARTIAL_RENDERING_PORTAL_LAYER_H
#define KZU_PARTIAL_RENDERING_PORTAL_LAYER_H

#include <user/scene_graph/kzu_object_base.h>


KZ_HEADER_BEGIN


/* Forward declaration. */
struct KzcMemoryManager;
struct KzuFactory;
struct KzuLayer;
struct KzuObjectNode;
struct KzuPortalLayer;
struct KzuUIDomain;


/** Object type for portal layers. */
extern const KzuObjectType KZU_OBJECT_TYPE_PARTIAL_RENDERING_PORTAL_LAYER;


/** Convert layer to portal layer. */
struct KzuPartialRenderingPortalLayer* kzuPartialRenderingPortalLayerFromLayer(const struct KzuLayer* layer);
/** Convert portal layer to layer. */
struct KzuLayer* kzuPartialRenderingPortalLayerToLayer(const struct KzuPartialRenderingPortalLayer* partialRenderingPortalLayer);
/** Tell if a layer is a portal layer. */
kzBool kzuLayerIsPartialRenderingPortal(const struct KzuLayer* layer);
/** Tell if an object node is a portal layer. */
kzBool kzuObjectNodeIsPartialRenderingPortalLayer(const struct KzuObjectNode* objectNode);

/** Create a portal layer. */
kzsError kzuPartialRenderingPortalLayerCreate(const struct KzcMemoryManager* memoryManager, kzString name, struct KzuUIDomain* uiDomain,
                                              struct KzuPartialRenderingPortalLayer** out_partialRenderingPortalLayer);
/** Register portal layer to the factory. */
kzsError kzuPartialRenderingPortalLayerRegisterToFactory(const struct KzuFactory* factory);

/** Invalidate all current partial rendering data and start over. */
kzsError kzuPartialRenderingPortalLayerRefresh(struct KzuPartialRenderingPortalLayer* partialRenderingPortalLayer);


KZ_HEADER_END


#endif
