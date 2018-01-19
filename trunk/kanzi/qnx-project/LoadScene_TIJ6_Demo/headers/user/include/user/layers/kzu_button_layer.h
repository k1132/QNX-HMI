/**
 * \file
 * Button layer class.
 *
 * \see \ref kzu_ui_button.h for documentation concerning all Kanzi buttons, including ::KzuButtonLayer.
 *
 * Copyright 2008-2014 by Rightware. All rights reserved.
 */
#ifndef KZU_BUTTON_LAYER_H
#define KZU_BUTTON_LAYER_H


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
 * \struct KzuButtonLayer
 * Button layer.
 *
 * \see \ref kzu_ui_button.h for documentation concerning all Kanzi buttons.
 */
struct KzuButtonLayer;

/** Object type for button layers. */
extern const KzuObjectType KZU_OBJECT_TYPE_BUTTON_LAYER;


/** Creates a button layer. */
kzsError kzuButtonLayerCreate(const struct KzcMemoryManager* memoryManager, kzString name, struct KzuUIDomain* uiDomain,
                              struct KzuButtonLayer** out_buttonLayer);
/** Registers button layer to the factory. */
kzsError kzuButtonLayerRegisterToFactory(const struct KzuFactory* factory);

/** Converts a layer into a button layer. */
struct KzuButtonLayer* kzuButtonLayerFromLayer(const struct KzuLayer* layer);
/** Converts a button layer into a layer. */
struct KzuLayer* kzuButtonLayerToLayer(const struct KzuButtonLayer* buttonLayer);

/** Gets the long press interval property of a button layer.
 *  The value is the same as the (default) value of the property KZU_PROPERTY_TYPE_BUTTON_LONG_PRESS_INTERVAL.
 *  When the value is greater than zero, the KZU_MESSAGE_BUTTON_LONG_PRESS message is generated.
 */
kzFloat kzuButtonLayerGetLongPressInterval(const struct KzuButtonLayer* buttonLayer);

/** Gets the repeat interval property of a button layer. */
kzFloat kzuButtonLayerGetRepeatInterval(const struct KzuButtonLayer* buttonLayer);


KZ_HEADER_END


#endif
