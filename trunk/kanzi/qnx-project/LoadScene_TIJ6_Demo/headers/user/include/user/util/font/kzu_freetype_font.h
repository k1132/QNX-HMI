/**
* \file
* FreeType font.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_FREETYPE_FONT_H
#define KZU_FREETYPE_FONT_H


#include "kzu_font_common.h"

#include <core/util/color/kzc_color.h>

#include <system/debug/kzs_error.h>
#include <system/wrappers/kzs_opengl_base.h>
#include <system/kzs_types.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations */
struct KzuFont;
struct KzcInputStream;
struct KzcMemoryManager;
struct KzcRectangle;
struct KzcRenderer;
struct KzuBinaryFileInfo;
struct KzuResourceManager;
struct KzuTextLayout;
struct KzuUIDomain;
struct KzuTruetypeSystem;


/**
 * \struct KzuFreetypeSystem
 * Structure for FreeType font system. This system is needed for FreeType fonts.
 * Usually one FreeType font system per application is enough, but more can be used if needed.
 */
struct KzuFreetypeSystem;

/**
* \struct KzuFreetypeFont
* Font structure for rendering text with FreeType.
*/
struct KzuFreetypeFont;


/** Font type identifier for font FreeType fonts. */
extern const KzuFontType KZU_FONT_TYPE_FREETYPE;


/** Creates an FreeType font system. */
kzsError kzuFreetypeSystemCreate(const struct KzcMemoryManager* memoryManager, struct KzuUIDomain* uiDomain,
                                 struct KzuFreetypeSystem** out_freetypeSystem);

/** Deletes an FreeType font system. */
kzsError kzuFreetypeSystemDelete(struct KzuFreetypeSystem* freetypeSystem);

/** Type casts a generic TrueType font system to more specific FreeType font system. */
struct KzuFreetypeSystem* kzuFreetypeSystemFromTruetypeSystem(struct KzuTruetypeSystem* truetypeSystem);

/** Type casts a FreeType font system to more generic TrueType font system. */
struct KzuTruetypeSystem* kzuFreetypeSystemToTruetypeSystem(struct KzuFreetypeSystem* freetypeSystem);


/** Creates new FreeType font. */
kzsError kzuFreetypeFontCreate(const struct KzcMemoryManager* memoryManager, struct KzuFreetypeSystem* freetypeSystem,
                               kzString name, struct KzuFreetypeFont** out_freetypeFont);

/** Creates new FreeType font from resource. */
kzsError kzuFreetypeFontCreateFromResource(const struct KzcMemoryManager* memoryManager, struct KzuFreetypeSystem* freetypeSystem,
                                           kzString resourcePath, struct KzuFreetypeFont** out_freetypeFont);


/** Creates new FreeType font from file. */
kzsError kzuFreetypeFontCreateFromFile(const struct KzcMemoryManager* memoryManager, struct KzuFreetypeSystem* freetypeSystem,
                                       kzString filePath, struct KzuFreetypeFont** out_freetypeFont);

/** Creates new FreeType font from memory. */
kzsError kzuFreetypeFontCreateFromMemory(const struct KzcMemoryManager* memoryManager, struct KzuFreetypeSystem* freetypeSystem,
                                         kzString name, const kzByte* data, kzUint size, struct KzuFreetypeFont** out_freetypeFont);

/** Deletes the give FreeType font. */
kzsError kzuFreetypeFontDelete(struct KzuFreetypeFont* freetypeFont);

/** Loads FreeType font from KZB. */
kzsError kzuFreetypeFontLoadFromKZB(struct KzuFreetypeFont* freetypeFont, struct KzcInputStream* inputStream, const struct KzuBinaryFileInfo* file);



/** Type casts generic font structure to FreeType font structure. */
struct KzuFreetypeFont* kzuFreetypeFontFromFont(struct KzuFont* font);
/** Type casts FreeType font structure to generic font structure. */
struct KzuFont* kzuFreetypeFontToFont(struct KzuFreetypeFont* freetypeFont);


/** Sets the size of FreeType font (in pixels). */
kzsError kzuFreetypeFontSetSize(struct KzuFreetypeFont* freetypeFont, kzFloat size);
/** Returns the size of FreeType font. */
kzFloat kzuFreetypeFontGetSize(const struct KzuFreetypeFont* freetypeFont);

/** Sets the color of the font. */
void kzuFreetypeFontSetColor(struct KzuFreetypeFont* freetypeFont, struct KzcColorRGBA color);
/** Gets the color of the font. */
struct KzcColorRGBA kzuFreetypeFontGetColor(const struct KzuFreetypeFont* freetypeFont);


/** Returns the line height of FreeType font. */
kzFloat kzuFreetypeFontGetLineHeight(const struct KzuFreetypeFont* freetypeFont);
/** Returns the ascender of FreeType font. */
kzFloat kzuFreetypeFontGetAscender(const struct KzuFreetypeFont* freetypeFont);


/** Returns the advance of given character using FreeType font. */
kzsError kzuFreetypeFontGetCharacterMetrics(const struct KzuFreetypeFont* freetypeFont, kzUnicodeChar character,
                                            kzFloat* out_advanceX, kzFloat* out_advanceY, struct KzcRectangle* out_boundingBox);
/** Returns the kerning of given character pair using FreeType font. */
kzsError kzuFreetypeFontGetKerning(const struct KzuFreetypeFont* freetypeFont, kzUnicodeChar previousCharacter,
                                   kzUnicodeChar character, kzFloat* out_kerningX, kzFloat* out_kerningY);


/** Prepares the given pre-layouted text for fast rendering using FreeType. */
kzsError kzuFreetypeFontPrepareTextLayout(struct KzuTextLayout* textLayout, struct KzcRenderer* renderer);

/** Draw the given pre-layouted text using FreeType. */
kzsError kzuFreetypeFontDrawTextLayout(struct KzuTextLayout* textLayout, struct KzcRenderer* renderer, kzFloat x, kzFloat y);

/** Draw the given pre-layouted text in 3D space using FreeType. */
kzsError kzuFreetypeFontDrawTextLayout3D(struct KzuTextLayout* textLayout, struct KzcRenderer* renderer);

/** Frees the data and resources created by the prepare function. */
kzsError kzuFreetypeFontFreeTextLayoutData(struct KzuTextLayout* textLayout);

/**
 * Loads a bitmap data for a single character glyph. The data doesn't need to be released, but it is valid only until prepare text
 * layout, draw text layout or this function gets called again. The data is returned as a greyscale image with 8 bits per pixel,
 * with the first scanline being the bottom line of the image.
 */
kzsError kzuFreetypeFontLoadCharacterGlyph(const struct KzuFreetypeFont* freetypeFont, kzUnicodeChar character, kzUint* out_width,
                                           kzUint* out_height, const kzByte** out_data);


KZ_HEADER_END


#endif
