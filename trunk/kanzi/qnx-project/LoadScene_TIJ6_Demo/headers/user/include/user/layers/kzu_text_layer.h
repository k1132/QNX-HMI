/**
 * \file
 * Text layer class. KzuTextLayer is used to display a small amount of text.
 *
 * Text Layer Messages
 * ----
 * KzuTextLayer does not send or receive any messages.
 *
 * Text Layer Properties
 * ----
 * ::KZU_PROPERTY_TYPE_FONT_MATERIAL string property specifies the resource ID of the font material (::KzuMaterial).
 *
 * ::KZU_PROPERTY_TYPE_FONT string property specifies the resource ID of the font (::KzuFont).
 *
 * ::KZU_PROPERTY_TYPE_FONT_SIZE float property specifies the font size in device independent pixels (DIP). The default value is 36.
 *
 * ::KZU_PROPERTY_TYPE_FONT_COLOR ::KzcColorRGBA property specifies the font color. This property works with the default font material and
 * with any material that has a fragment shader with a uniform named "FontColor". The default value is {1, 1, 1, 1}.
 *
 * ::KZU_PROPERTY_TYPE_TEXT_LAYER__TEXT string property contains the text string to render. The default value is "<Text>".
 *
 * ::KZU_PROPERTY_TYPE_TEXT__LINE_SPACING float property sets the line spacing of the text. The line spacing is specified in multiples
 * of the normal line height of the font. The default value is 1.
 *
 * ::KZU_PROPERTY_TYPE_TEXT__CHARACTER_SPACING float property sets the character spacing of the text. The character spacing is specified
 * in device independent pixels (DIP). The default value is 0.
 *
 * ::KZU_PROPERTY_TYPE_TEXT__HORIZONTAL_ALIGNMENT integer property specifies the horizontal alignment of the text. The value should be one of
 * ::KzuTextHorizontalAlignment values. The default value is ::KZU_TEXT_HORIZONTAL_ALIGNMENT_LEFT.
 *
 * ::KZU_PROPERTY_TYPE_TEXT__VERTICAL_ALIGNMENT integer property specifies the vertical alignment of the text. The value should be one of
 * ::KzuTextVerticalAlignment values. The default value is ::KZU_TEXT_VERTICAL_ALIGNMENT_TOP.
 *
 * ::KZU_PROPERTY_TYPE_TEXT__OVERFLOW string property specifies the last characters of the rendered text when the text is truncated. The default
 * value is "...".
 *
 * Copyright 2008-2014 by Rightware. All rights reserved.
 */
#ifndef KZU_TEXT_LAYER_H
#define KZU_TEXT_LAYER_H


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
 * \struct KzuTextLayer
 * Displays text.
 */
struct KzuTextLayer;

/** Object type for text layers. */
extern const KzuObjectType KZU_OBJECT_TYPE_TEXT_LAYER;


/** Creates a text layer. */
kzsError kzuTextLayerCreate(const struct KzcMemoryManager* memoryManager, kzString name, struct KzuUIDomain* uiDomain,
                            struct KzuTextLayer** out_textLayer);
/** Registers text layer to the factory. */
kzsError kzuTextLayerRegisterToFactory(const struct KzuFactory* factory);

/** Converts a layer into a text layer. */
struct KzuTextLayer* kzuTextLayerFromLayer(const struct KzuLayer* layer);
/** Converts a text layer into a layer. */
struct KzuLayer* kzuTextLayerToLayer(const struct KzuTextLayer* textLayer);

/** Forces rendering preparation on next render call. */
void kzuTextLayerInvalidateRendering(struct KzuTextLayer* textLayer);


KZ_HEADER_END


#endif
