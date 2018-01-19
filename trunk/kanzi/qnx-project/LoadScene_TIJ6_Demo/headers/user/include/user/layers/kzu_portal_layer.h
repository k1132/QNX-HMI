/**
* \file
* Portal layer class.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_PORTAL_LAYER_H
#define KZU_PORTAL_LAYER_H


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
extern const KzuObjectType KZU_OBJECT_TYPE_PORTAL_LAYER;


/** Convert layer to portal layer. */
struct KzuPortalLayer* kzuPortalLayerFromLayer(const struct KzuLayer* layer);
/** Convert portal layer to layer. */
struct KzuLayer* kzuPortalLayerToLayer(const struct KzuPortalLayer* portalLayer);
/** Tell if a layer is a portal layer. */
kzBool kzuLayerIsPortal(const struct KzuLayer* layer);
/** Tell if an object node is a portal layer. */
kzBool kzuObjectNodeIsPortalLayer(const struct KzuObjectNode* objectNode);

/** Create a portal layer. */
kzsError kzuPortalLayerCreate(const struct KzcMemoryManager* memoryManager, kzString name, struct KzuUIDomain* uiDomain,
                              struct KzuPortalLayer** out_portalLayer);
/** Register portal layer to the factory. */
kzsError kzuPortalLayerRegisterToFactory(const struct KzuFactory* factory);

/** Get the scene associated with this portal layer. */
struct KzuScene* kzuPortalLayerGetScene(const struct KzuPortalLayer* portalLayer);


KZ_HEADER_END


#endif
