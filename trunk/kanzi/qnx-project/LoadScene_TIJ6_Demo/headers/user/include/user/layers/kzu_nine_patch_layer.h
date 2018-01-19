/**
 * \file
 * Nine-patch layer class.
 *
 * A Nine-patch layer is a 3x3 grid of image layers. The center image is framed by the other eight images.
 * The textures in the four corners of the frame determine the thickness of the frame textures on the sides. The center image and the frame
 * are scaled according to the ::KZU_PROPERTY_TYPE_LAYOUT_WIDTH and ::KZU_PROPERTY_TYPE_LAYOUT_HEIGHT properties.
 *
 * Nine-Patch Layer Messages
 * ----
 * KzuNinePatchLayer does not send or receive any messages.
 *
 * Nine-Patch Layer Properties
 * ----
 * ::KZU_PROPERTY_TYPE_NINE_PATCH_LAYER_TEXTURE_TOP_LEFT resource ID property specifies the top-left texture.
 *
 * ::KZU_PROPERTY_TYPE_NINE_PATCH_LAYER_TEXTURE_TOP resource ID property specifies the top (center) texture.
 *
 * ::KZU_PROPERTY_TYPE_NINE_PATCH_LAYER_TEXTURE_TOP_RIGHT resource ID property specifies the top-right texture.
 *
 * ::KZU_PROPERTY_TYPE_NINE_PATCH_LAYER_TEXTURE_LEFT resource ID property specifies the left texture.
 *
 * ::KZU_PROPERTY_TYPE_NINE_PATCH_LAYER_TEXTURE_CENTER resource ID property specifies the center texture.
 *
 * ::KZU_PROPERTY_TYPE_NINE_PATCH_LAYER_TEXTURE_RIGHT resource ID property specifies the right texture.
 *
 * ::KZU_PROPERTY_TYPE_NINE_PATCH_LAYER_TEXTURE_BOTTOM_LEFT resource ID property specifies the bottom-left texture.
 *
 * ::KZU_PROPERTY_TYPE_NINE_PATCH_LAYER_TEXTURE_BOTTOM resource ID property specifies the bottom (center) texture.
 *
 * ::KZU_PROPERTY_TYPE_NINE_PATCH_LAYER_TEXTURE_BOTTOM_RIGHT resource ID property specifies the bottom-right texture.
 *
 * ::KZU_PROPERTY_TYPE_LAYOUT_WIDTH float property specifies the width of the KzuNinePatchLayer.
 *
 * ::KZU_PROPERTY_TYPE_LAYOUT_HEIGHT float property specifies the height of the KzuNinePatchLayer.
 *
 * Copyright 2013-2014 by Rightware. All rights reserved.
 */
#ifndef KZU_NINE_PATCH_LAYER_H
#define KZU_NINE_PATCH_LAYER_H


#include <user/scene_graph/kzu_object_common.h>

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
 * \struct KzuNinePatchLayer
 * A 9-patch layer is a 3x3 grid of image layers. The center image is framed by the other images which all stretch according to the layout size.
 */
struct KzuNinePatchLayer;

/** Object type for button layers. */
extern const KzuObjectType KZU_OBJECT_TYPE_NINE_PATCH_LAYER;


/** Creates a 9-patch layer. */
kzsError kzuNinePatchLayerCreate(const struct KzcMemoryManager* memoryManager, kzString name, struct KzuUIDomain* uiDomain,
                              struct KzuNinePatchLayer** out_9PatchLayer);
/** Registers 9-patch layer to the factory. */
kzsError kzuNinePatchLayerRegisterToFactory(const struct KzuFactory* factory);

/** Converts a layer into a 9-patch layer. */
struct KzuNinePatchLayer* kzuNinePatchLayerFromLayer(const struct KzuLayer* layer);
/** Converts a 9-patch layer into a layer. */
struct KzuLayer* kzuNinePatchLayerToLayer(const struct KzuNinePatchLayer* buttonLayer);


KZ_HEADER_END


#endif
