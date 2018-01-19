/**
* \file
* Font handling interface.
* This interface provides functionality for measuring font related information and for drawing pre-layeted text.
* To draw arbitrary strings with this interface, the text must be first layed out with kzu_text_layouter.h.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_FONT_H
#define KZU_FONT_H


#include "kzu_font_common.h"

#include <user/resource/kzu_resource_common.h>

#include <core/util/color/kzc_color.h>

#include <system/debug/kzs_error.h>
#include <system/kzs_types.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


#define KZ_TRUETYPE_SYSTEM_FREETYPE 1 /**< Truetype support with Freetype. */
#define KZ_TRUETYPE_SYSTEM_ITYPE    2 /**< Truetype support with iType. */
#define KZ_TRUETYPE_SYSTEM_DUMMY    3 /**< No Truetype support. */

#ifndef KZ_TRUETYPE_SYSTEM_DEFAULT
/** Default truetype font system. */
#define KZ_TRUETYPE_SYSTEM_DEFAULT KZ_TRUETYPE_SYSTEM_FREETYPE
#endif


/* Forward declarations */
struct KzuBinaryFileInfo;
struct KzuTextLayout;
struct KzuResource;
struct KzcMemoryManager;
struct KzcRenderer;
struct KzcRectangle;
struct KzcInputStream;


/**
* \struct KzuFont
* Font structure for rendering text.
*/
struct KzuFont;


/** Resource type identifier for font. */
extern const KzuResourceType KZU_RESOURCE_TYPE_FONT;


/** Frees memory allocated for given font. */
kzsError kzuFontDelete(struct KzuFont* font);

/** Loads font from KZB. */
kzsError kzuFontLoadFromKZB(struct KzuFont* font, struct KzcInputStream* inputStream, const struct KzuBinaryFileInfo* file);


/** Sets the size of the font. */
kzsError kzuFontSetSize(struct KzuFont* font, kzFloat size);
/** Returns the height of the font. */
kzsError kzuFontGetSize(struct KzuFont* font, kzFloat* out_size);

/** Sets the color of the font. */
kzsError kzuFontSetColor(struct KzuFont* font, struct KzcColorRGBA color);
/** Gets the color of the font. */
kzsError kzuFontGetColor(struct KzuFont* font, struct KzcColorRGBA* out_color);

/** Returns the fonts preferred line height. */
kzsError kzuFontGetLineHeight(struct KzuFont* font, kzFloat* out_lineHeight);

/** Returns the fonts ascender. This is how much the font ascends below the baseline. */
kzsError kzuFontGetAscender(struct KzuFont* font, kzFloat* out_baseline);

/** Gets the number of units that the cursor should move after given character. */
kzsError kzuFontGetCharacterMetrics(struct KzuFont* font, kzUnicodeChar character, kzFloat* out_advance, struct KzcRectangle* out_boundingBox);

/** Gets the kerning between two given characters. */
kzsError kzuFontGetKerning(struct KzuFont* font, kzUnicodeChar previousCharacter, kzUnicodeChar character, kzFloat* out_kerning);

/**
 * Loads the bitmap data for a single character glyph. The returned character glyph needs to be released with a call to release,
 * and the next glyph can't be loaded before the previous glyph has been released.
 * The bitmap data is returned as a greyscale image with 8 bits per pixel.
 */
kzsError kzuFontLoadCharacterGlyph(struct KzuFont* font, kzUnicodeChar character, kzUint* out_width,
                                   kzUint* out_height, const kzByte** out_bitmapData, void** out_characterGlyph);
/** Releases a loaded character glyph. */
kzsError kzuFontReleaseCharacterGlyph(struct KzuFont* font, void* characterGlyph);

/** Prepares the given text layout for rendering. This step is automatically done when drawing for the first time if not already prepared before. */
kzsError kzuFontPrepareTextLayout(struct KzuTextLayout* textLayout, struct KzcRenderer* renderer);

/** Draws the given text layout to given 2D position on the screen. */
kzsError kzuFontDrawTextLayout(struct KzuTextLayout* textLayout, struct KzcRenderer* renderer, kzFloat x, kzFloat y);

/** Draws the given text layout to 3D world with the current transformation. */
kzsError kzuFontDrawTextLayout3D(struct KzuTextLayout* textLayout, struct KzcRenderer* renderer);

/** Frees the data allocated in the prepare. This is automatically done when deleting the text layout if needed. */
kzsError kzuFontFreeTextLayoutData(struct KzuTextLayout* textLayout);

/** Returns font's type */ 
KzuFontType kzuFontGetType(const struct KzuFont* font);

/** Converts font to resource. */
struct KzuResource* kzuFontToResource(const struct KzuFont* font);
/** Converts font from resource. */
struct KzuFont* kzuFontFromResource(const struct KzuResource* resource);
/** Casts font from resource, KZ_NULL if invalid type. */
struct KzuFont* kzuFontCastFromResource(const struct KzuResource* resource);


KZ_HEADER_END


#endif
