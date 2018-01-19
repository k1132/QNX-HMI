/**
 * \file
 * Toggle Button layer class.
 *
 * KzuToggleButtonLayer is a 2D button layout that has ::KZU_PROPERTY_TYPE_BUTTON_TOGGLE_STATE_COUNT set to 2 by default. The documentation
 * in \ref kzu_ui_button.h is valid for this component also.
 *
 * \see \ref kzu_ui_toggle_button.h for the 3D version of this layer, \ref kzu_ui_button.h for documentation concerning all Kanzi buttons.
 *
 * Copyright 2013-2014 by Rightware. All rights reserved.
 */
#ifndef KZU_TOGGLE_BUTTON_LAYER_H
#define KZU_TOGGLE_BUTTON_LAYER_H


#include <user/scene_graph/kzu_object_common.h>
#include <user/scene_graph/kzu_object.h>

#include <system/kzs_types.h>
#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations. */
struct KzcMemoryManager;
struct KzuFactory;
struct KzuLayer;
struct KzuUIDomain;

/**
 * \struct KzuToggleButtonLayer
 * Toggle button layer class struct.
 *
 * \see \ref kzu_ui_button.h for documentation concerning all Kanzi buttons.
 */
struct KzuToggleButtonLayer;

/** Object type for button layers. */
extern const KzuObjectType KZU_OBJECT_TYPE_TOGGLE_BUTTON_LAYER;


/** Creates a toggle button layer. */
kzsError kzuToggleButtonLayerCreate(const struct KzcMemoryManager* memoryManager, kzString name, struct KzuUIDomain* uiDomain,
                              struct KzuToggleButtonLayer** out_buttonLayer);
/** Registers toggle button layer to the factory. */
kzsError kzuToggleButtonLayerRegisterToFactory(const struct KzuFactory* factory);

/** Converts a layer into a toggle button layer. */
struct KzuToggleButtonLayer* kzuToggleButtonLayerFromLayer(const struct KzuLayer* layer);
/** Converts a toggle button layer into a layer. */
struct KzuLayer* kzuToggleButtonLayerToLayer(const struct KzuToggleButtonLayer* buttonLayer);


KZ_HEADER_END


#endif
