/**
* \file
* Configured font. This font implementation wraps an existing font with given font configuration (size, color).
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_CONFIGURED_FONT_H
#define KZU_CONFIGURED_FONT_H


#include "kzu_font_common.h"

#include <core/util/color/kzc_color.h>

#include <system/debug/kzs_error.h>
#include <system/kzs_types.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations */
struct KzuFont;
struct KzuTextLayout;
struct KzuUIDomain;
struct KzcMemoryManager;
struct KzcRenderer;
struct KzcRectangle;


/**
* \struct KzuConfiguredFont
* Font structure for rendering text.
*/
struct KzuConfiguredFont;


/** Font type identifier for configured font objects. */
extern const KzuFontType KZU_FONT_TYPE_CONFIGURED;


/** Creates new configured font wrapping the given target font. */
kzsError kzuConfiguredFontCreate(const struct KzcMemoryManager* memoryManager, struct KzuFont* targetFont,
                                 kzFloat size, struct KzcColorRGBA color, const struct KzuUIDomain* uiDomain, struct KzuConfiguredFont** out_configuredFont);


/** Type cast from generic font to configured font. */
struct KzuConfiguredFont* kzuConfiguredFontFromFont(struct KzuFont* font);
/** Type cast from configured font to generic font. */
struct KzuFont* kzuConfiguredFontToFont(struct KzuConfiguredFont* configuredFont);


/** Sets the size of configured font. */
kzsError kzuConfiguredFontSetSize(struct KzuConfiguredFont* configuredFont, kzFloat size);
/** Returns the size of configured font. */
kzFloat kzuConfiguredFontGetSize(const struct KzuConfiguredFont* configuredFont);

/** Sets the color of the font. */
kzsError kzuConfiguredFontSetColor(struct KzuConfiguredFont* configuredFont, struct KzcColorRGBA color);
/** Gets the color of the font. */
struct KzcColorRGBA kzuConfiguredFontGetColor(const struct KzuConfiguredFont* configuredFont);


/** Returns the line height of configured font. */
kzsError kzuConfiguredFontGetLineHeight(const struct KzuConfiguredFont* configuredFont, kzFloat* out_lineHeight);
/** Returns the ascender of configured font. */
kzsError kzuConfiguredFontGetAscender(const struct KzuConfiguredFont* configuredFont, kzFloat* out_ascender);


/** Returns the advance of given character using configured font. */
kzsError kzuConfiguredFontGetCharacterMetrics(const struct KzuConfiguredFont* configuredFont, kzUnicodeChar character,
                                              kzFloat* out_advance, struct KzcRectangle* out_boundingBox);
/** Returns the kerning of given character pair using configured font. */
kzsError kzuConfiguredFontGetKerning(const struct KzuConfiguredFont* configuredFont, kzUnicodeChar previousCharacter,
                                     kzUnicodeChar character, kzFloat* out_kerning);

/** Loads a bitmap data for a single character glyph using configured font. */
kzsError kzuConfiguredFontLoadCharacterGlyph(const struct KzuConfiguredFont* configuredFont, kzUnicodeChar character, kzUint* out_width,
                                             kzUint* out_height, const kzByte** out_bitmapData, void** out_characterGlyph);
/** Releases a loaded character glyph using configured font. */
kzsError kzuConfiguredFontReleaseCharacterGlyph(const struct KzuConfiguredFont* configuredFont, void* characterGlyph);

/**
 * Draws a character at given coordinates. The coordinates indicate the character left point on the baseline.
 * This function is meant for debugging purposes only. For real text rendering, use KzcTextLayouter.
 */
kzsError kzuConfiguredFontDrawCharacter(const struct KzuConfiguredFont* configuredFont, struct KzcRenderer* renderer,
                                        kzUnicodeChar character, kzFloat x, kzFloat y);


/** Prepares the given pre-layouted text for fast rendering using configured font. */
kzsError kzuConfiguredFontPrepareTextLayout(struct KzuTextLayout* textLayout, struct KzcRenderer* renderer);
 
/** Draw the given pre-layouted text using configured font. */
kzsError kzuConfiguredFontDrawTextLayout(struct KzuTextLayout* textLayout, struct KzcRenderer* renderer, kzFloat x, kzFloat y);

/** Draw the given pre-layouted text in 3D space using configured font. */
kzsError kzuConfiguredFontDrawTextLayout3D(struct KzuTextLayout* textLayout, struct KzcRenderer* renderer);

/** Frees the data and resources created by the prepare function. */
kzsError kzuConfiguredFontFreeTextLayoutData(struct KzuTextLayout* textLayout);


KZ_HEADER_END


#endif
