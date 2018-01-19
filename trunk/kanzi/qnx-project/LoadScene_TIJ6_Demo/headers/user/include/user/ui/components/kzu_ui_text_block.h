/**
 * \file
 * User interface text block component.
 * 
 * KzuUiTextBlock is used to display a small amount of text.
 *
 * Text Block Messages
 * ----
 * KzuUiTextBlock does not send or receive any messages.
 *
 * Text Block Properties
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
 * ::KZU_PROPERTY_TYPE_TEXT_BLOCK__TEXT string property contains the text string to render. The default value is "<Text>".
 *
 * ::KZU_PROPERTY_TYPE_TEXT__LINE_SPACING float property sets the line spacing of the text. The line spacing is specified in multiples
 * of the normal line height of the font. The default value is 1.
 *
 * ::KZU_PROPERTY_TYPE_TEXT__CHARACTER_SPACING float property sets the character spacing of the text. The character spacing is specified
 * in device independent pixels (DIP). The default value is 0.
 *
 * ::KZU_PROPERTY_TYPE_TEXT_BLOCK__LINE_HEIGHT float property specifies the line height in 3D space units. The default value is 1.25.
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
#ifndef KZU_UI_TEXT_BLOCK_H
#define KZU_UI_TEXT_BLOCK_H


#include <user/scene_graph/kzu_object_common.h>
#include <user/ui/kzu_layout.h>


KZ_HEADER_BEGIN


/* Forward declarations. */
struct KzcMemoryManager;
struct KzcHashMap;
struct KzuObjectNode;
struct KzuUiComponentNode;
struct KzuPropertyManager;
struct KzuMessageDispatcher;
struct KzuFactory;
struct KzuUIDomain;


/**
 * \struct KzuUiTextBlock
 * Text block user interface component. Displays small amount of text.
 */
struct KzuUiTextBlock;


/** Object type for text block. */
extern const KzuObjectType KZU_OBJECT_TYPE_UI_TEXT_BLOCK;


/** Creates a text block with default settings. */
kzsError kzuUiTextBlockCreate(const struct KzcMemoryManager* memoryManager, kzString name, struct KzuUIDomain* uiDomain, struct KzuUiTextBlock** out_textBlock);

/** Registers component type to factory. */
kzsError kzuUiTextBlockRegisterToFactory(const struct KzuFactory* factory);

/** Casts to UiComponentNode. */
struct KzuUiComponentNode* kzuUiTextBlockToUiComponentNode(const struct KzuUiTextBlock* textBlock);

/** Casts to UiStackLayout. */
struct KzuUiTextBlock* kzuUiTextBlockFromUiComponentNode(const struct KzuUiComponentNode* component);


KZ_HEADER_END


#endif
