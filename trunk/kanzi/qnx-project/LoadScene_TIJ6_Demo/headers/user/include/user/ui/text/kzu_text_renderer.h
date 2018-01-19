/**
 * \file
 * Text Renderer.
 *
 * Copyright 2008-2014 by Rightware. All rights reserved.
 */
#ifndef KZU_TEXT_RENDERER_H
#define KZU_TEXT_RENDERER_H

#include <user/util/font/kzu_text_layouter.h>

#include <system/kzs_types.h>
#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations */
struct KzcMemoryManager;
struct KzuFont;
struct KzuMaterial;
struct KzuRenderer;
struct KzcRectangle;
struct KzuResourceManager;
struct KzuBitmapFontSystem;
struct KzuTruetypeSystem;


/**
 * \struct KzuTextRenderer
 * Text renderer creates and renders text layouts.
 */
struct KzuTextRenderer;


/**
 * \struct KzuTextFormat
 * Text format combines the data that is needed for text layouting and the data that is needed for rendering the text.
 */
struct KzuTextFormat;


/** Pointer to a function that creates a text layouter. */
typedef kzsError (*kzuTextRendererCreateTextLayouterFunction)(const struct KzcMemoryManager* memoryManager, struct KzuFont* font,
                                                              void* userData, struct KzuTextLayouter** out_textLayouter);


/** Creates a text renderer. */
kzsError kzuTextRendererCreate(const struct KzcMemoryManager* memoryManager, struct KzuResourceManager* resourceManager,
                               struct KzuTextRenderer** out_textRenderer);

/** Deletes a text renderer. */
kzsError kzuTextRendererDelete(struct KzuTextRenderer* textRenderer);

/** Sets the default font material and acquires the material. */
kzsError kzuTextRendererSetDefaultFontMaterial(struct KzuTextRenderer* textRenderer, struct KzuMaterial* material);

/** Returns a valid font material. */
struct KzuMaterial* kzuTextRendererGetValidFontMaterial(const struct KzuTextRenderer* textRenderer, const struct KzuRenderer* renderer, struct KzuMaterial* material);

/** Creates a text layout. The text layout specifies the maximum area which can be used to layout text. The width and height are specified in pixels and they can be KZS_INFINITY for an unbounded area. */
kzsError kzuTextRendererCreateTextFormat(const struct KzuTextRenderer* textRenderer, struct KzuFont* font, kzFloat fontSize, kzFloat width, kzFloat height, struct KzuTextFormat** out_textFormat);

/** Deletes a text layout. */
kzsError kzuTextRendererDeleteTextFormat(struct KzuTextFormat* textFormat);


/** Sets the horizontal alignment of the text. */
void kzuTextFormatSetTextHorizontalAlignment(struct KzuTextFormat* textFormat, enum KzuTextHorizontalAlignment alignment);

/** Sets the vertical alignment of the text. */
void kzuTextFormatSetTextVerticalAlignment(struct KzuTextFormat* textFormat, enum KzuTextVerticalAlignment alignment);

/** Sets the line spacing of the text. The line spacing is specified in multiples of the normal line height which is specified by the font. */
void kzuTextFormatSetLineSpacing(const struct KzuTextFormat* textFormat, kzFloat lineSpacing);

/** Sets the character spacing of the text. The character spacing is specified in multiples of the normal character spacing which is specified by the font. */
void kzuTextFormatSetCharacterSpacing(const struct KzuTextFormat* textFormat, kzFloat characterSpacing);

/** Sets the fixed character width of the text. The character width is specified in pixels. */
void kzuTextFormatSetFixedCharacterWidth(const struct KzuTextFormat* textFormat, kzFloat fixedCharacterWidth);

/** Sets the overflow text that is displayed when the text doesn't fit to the layout. */
kzsError kzuTextFormatSetOverflow(const struct KzuTextFormat* textFormat, kzString overflowText);


/** Calculates the text layout. */
kzsError kzuTextFormatCalculateLayout(struct KzuTextFormat* textFormat, kzString text);

/** Gets the width of the area that the text layout actually used. The width is returned in pixels. The text layout must be calculated before calling this function. */
kzFloat kzuTextFormatGetWidth(const struct KzuTextFormat* textFormat);

/** Gets the height of the area that the text layout actually used. The height is returned in pixels. The text layout must be calculated before calling this function. */
kzFloat kzuTextFormatGetHeight(const struct KzuTextFormat* textFormat);

/**
 * Prepares a text layout for rendering in 3d space, where x-coordinates increase to the right and y-coordinates increase going upward. The z-coordinate of the text is always 0.0f.
 * The pixel size of the text font is multiplied by the scale to get the size of the text in the 3d space. The text offsets given in 3d space units are used calculate
 * proper horizontal aligning. They should be set to half of the width and height of the whole text format.
 */
kzsError kzuTextFormatPrepareForRendering3D(struct KzuTextFormat* textFormat, kzFloat unitScale, kzFloat offsetX, kzFloat offsetY);

/**
 * Prepares a text layout for rendering in 2d space, where x-coordinates increase to the right and y-coordinates increase going downward. The pixel size of the text font is multiplied by
 * the scale to get the size of the text in the 2d space.
 */
kzsError kzuTextFormatPrepareForRendering2D(struct KzuTextFormat* textFormat, kzFloat unitScale, kzFloat offsetX, kzFloat offsetY);

/**
 * Prepares a text layout for rendering in a bounded 2d space. Generates unclipped vertex positions and bounding box coordinates for the clipping function to use.
 */
kzsError kzuTextFormatPrepareForRendering2DWithClipping(struct KzuTextFormat* textFormat, kzFloat unitScale, const struct KzcRectangle* clippingArea, kzFloat offsetX, kzFloat offsetY);

/**
 * Calculates clipped vertex coordinates from the bounding coordinates generated in the preparation function. Characters that are outside the bounded area are clipped completely, and 
 * characters that are on the border of area are clipped so that only part of the character is visible.
 */
kzsError kzuTextFormatCalculateClipping(struct KzuTextFormat* textFormat, const struct KzcRectangle* clippingArea);

/**
 * Renders a text format. The text format must be calculated and prepared for rendering before calling this function.
 * If the material is KZ_NULL, uses the default font material.
 */
kzsError kzuTextRendererDrawTextFormat(const struct KzuTextRenderer* textRenderer, struct KzuRenderer* renderer, const struct KzuTextFormat* textFormat, struct KzuMaterial* material);

/**
 * Renders a text format. The text format must be calculated and prepared for rendering before calling this function.
 * If the material is KZ_NULL, uses the default font material.
 * This function renders the text in two passes. First all color information is written with depth write disabled and then
 * in the second pass depth information is written with color write disabled. This is slower than kzuTextRendererDrawTextFormat,
 * but needed for correct rendering result when glyph bounds are overlapping.
 */
kzsError kzuTextRendererDrawTextFormatTwoPass(const struct KzuTextRenderer* textRenderer, struct KzuRenderer* renderer, const struct KzuTextFormat* textFormat, struct KzuMaterial* material);


/** Gets a bitmap font system. It is created and deleted automatically if necessary. */
kzsError kzuTextRendererGetBitmapFontSystem(struct KzuTextRenderer* textRenderer, struct KzuBitmapFontSystem** out_bitmapFontSystem);

/** Gets a TrueType font system. It is created and deleted automatically if necessary. */
kzsError kzuTextRendererGetTruetypeSystem(struct KzuTextRenderer* textRenderer, struct KzuTruetypeSystem** out_truetypeSystem);
/** Sets a TrueType font system, which overrides the default TrueType system. */
kzsError kzuTextRendererSetTruetypeSystem(struct KzuTextRenderer* textRenderer, struct KzuTruetypeSystem* truetypeSystem);

/** Sets a creator function for creating text layouters. Pass KZ_NULL as the function to reset to the default implementation. */
kzsError kzuTextRendererSetTextLayouterCreator(struct KzuTextRenderer* textRenderer, kzuTextRendererCreateTextLayouterFunction createFunction, void* userData);


KZ_HEADER_END


#endif
