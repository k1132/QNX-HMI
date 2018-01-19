/**
* \file
* Group layer class.
* 
* The group layer behaves like the empty layer but it propagates the ::KZU_PROPERTY_TYPE_LAYER_OPACITY property downward to its children instead of being
* affected by it itself.
* 
* \see \ref kzu_empty_layer.h.
*
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_GROUP_LAYER_H
#define KZU_GROUP_LAYER_H


#include <user/scene_graph/kzu_object_base.h>


KZ_HEADER_BEGIN


/* Forward declaration. */
struct KzcMemoryManager;
struct KzuGroupLayer;
struct KzuFactory;
struct KzuLayer;
struct KzuMessageDispatcher;
struct KzuUIDomain;
struct KzuPropertyManager;


/** Object type for empty layers. */
extern const KzuObjectType KZU_OBJECT_TYPE_GROUP_LAYER;


/** Creates an empty layer. */
kzsError kzuGroupLayerCreate(const struct KzcMemoryManager* memoryManager, kzString name, struct KzuUIDomain* uiDomain,
                             struct KzuGroupLayer** out_emptyLayer);
/** Registers empty layer to the factory. */
kzsError kzuGroupLayerRegisterToFactory(const struct KzuFactory* factory);

/** Converts layer to empty layer. */
struct KzuGroupLayer* kzuGroupLayerFromLayer(const struct KzuLayer* layer);
/** Converts empty layer to layer. */
struct KzuLayer* kzuGroupLayerToLayer(const struct KzuGroupLayer* emptyLayer);


KZ_HEADER_END


#endif
