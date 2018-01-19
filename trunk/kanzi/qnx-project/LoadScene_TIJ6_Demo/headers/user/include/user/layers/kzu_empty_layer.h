/**
* \file
* Empty layer class.
*
* The empty layer is a ::KzuLayer without any functionality except that it has a transparent background color and can act as the parent
* of other layers. The 3D counterpart is ::KzuUiPlaceholder or \ref kzu_empty_node.h.
*
* \see \ref kzu_empty_node.h, \ref kzu_ui_placeholder.h.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_EMPTY_LAYER_H
#define KZU_EMPTY_LAYER_H


#include <user/scene_graph/kzu_object_base.h>


KZ_HEADER_BEGIN


/* Forward declaration. */
struct KzcMemoryManager;
/** \struct KzuEmptyLayer
 * The empty layer is a ::KzuLayer without any functionality except that it has a transparent background color
 * and can act as the parent of other layers.
 */
struct KzuEmptyLayer;
struct KzuFactory;
struct KzuLayer;
struct KzuMessageDispatcher;
struct KzuUIDomain;
struct KzuPropertyManager;


/** Object type for empty layers. */
extern const KzuObjectType KZU_OBJECT_TYPE_EMPTY_LAYER;


/** Registers empty layer to the factory. */
kzsError kzuEmptyLayerRegisterToFactory(const struct KzuFactory* factory);

/** Creates an empty layer. */
kzsError kzuEmptyLayerCreate(const struct KzcMemoryManager* memoryManager, kzString name, struct KzuUIDomain* uiDomain,
                             struct KzuEmptyLayer** out_emptyLayer);


/** Converts layer to empty layer. */
struct KzuEmptyLayer* kzuEmptyLayerFromLayer(const struct KzuLayer* layer);
/** Converts empty layer to layer. */
struct KzuLayer* kzuEmptyLayerToLayer(const struct KzuEmptyLayer* emptyLayer);


KZ_HEADER_END


#endif
