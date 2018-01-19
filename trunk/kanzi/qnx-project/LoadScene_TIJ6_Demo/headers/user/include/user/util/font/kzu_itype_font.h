/**
* \file
* Monotype's iType font.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_ITYPE_FONT_H
#define KZU_ITYPE_FONT_H


#include "kzu_font_common.h"

#include <core/util/color/kzc_color.h>

#include <system/debug/kzs_error.h>
#include <system/wrappers/kzs_opengl_base.h>
#include <system/kzs_types.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declaration structures. */
struct KzuFont;
struct KzcInputStream;
struct KzcMemoryManager;
struct KzcRectangle;
struct KzcRenderer;
struct KzuBinaryFileInfo;
struct KzuResourceManager;
struct KzuShader;
struct KzuUIDomain;
struct KzuTextLayout;
struct KzuTruetypeSystem;


/** Font type identifier for font iType fonts. */
extern const KzuFontType KZU_FONT_TYPE_ITYPE;


/**
 * \struct KzuItypeSystem
 * Structure for iType font system. This system is needed for iType fonts.
 * Usually one iType font system per application is enough, but more can be used if needed.
 */
struct KzuItypeSystem;

/**
* \struct KzuItypeFont
* Font structure for rendering text with iType.
*/
struct KzuItypeFont;



/** Creates an iType font system. */
kzsError kzuItypeSystemCreate(const struct KzcMemoryManager* memoryManager, struct KzuUIDomain* uiDomain,
                              struct KzuItypeSystem** out_itypeSystem);

/** Deletes an iType font system. */
kzsError kzuItypeSystemDelete(struct KzuItypeSystem* itypeSystem);

/** Sets shader for iType system. */
void kzuItypeSystemSetShader(struct KzuItypeSystem* itypeSystem, kzBool useDistanceField, struct KzuShader* shader);

/** Type casts a generic TrueType font system to more specific iType font system. */
struct KzuItypeSystem* kzuItypeSystemFromTruetypeSystem(struct KzuTruetypeSystem* truetypeSystem);

/** Type casts an iType font system to more generic TrueType font system. */
struct KzuTruetypeSystem* kzuItypeSystemToTruetypeSystem(struct KzuItypeSystem* itypeSystem);


/** Creates new iType font. */
kzsError kzuItypeFontCreate(const struct KzcMemoryManager* memoryManager, struct KzuItypeSystem* itypeSystem,
                            kzString name, struct KzuItypeFont** out_itypeFont);

/** Creates new iType font from resource. */
kzsError kzuItypeFontCreateFromResource(const struct KzcMemoryManager* memoryManager, struct KzuItypeSystem* itypeSystem,
                                        kzString resourcePath, struct KzuItypeFont** out_itypeFont);

/** Creates new iType font from file. */
kzsError kzuItypeFontCreateFromFile(const struct KzcMemoryManager* memoryManager, struct KzuItypeSystem* itypeSystem,
                                    kzString filePath, struct KzuItypeFont** out_itypeFont);

/** Creates new iType font from memory. */
kzsError kzuItypeFontCreateFromMemory(const struct KzcMemoryManager* memoryManager, struct KzuItypeSystem* itypeSystem,
                                      kzString name, const kzByte* data, kzUint size, struct KzuItypeFont** out_itypeFont);

/** Deletes the give iType font. */
kzsError kzuItypeFontDelete(struct KzuItypeFont* itypeFont);

/** Loads iType font from KZB. */
kzsError kzuItypeFontLoadFromKZB(struct KzuItypeFont* itypeFont, struct KzcInputStream* inputStream, const struct KzuBinaryFileInfo* file);


/** Type casts generic font structure to iType font structure. */
struct KzuItypeFont* kzuItypeFontFromFont(struct KzuFont* font);
/** Type casts iType font structure to generic font structure. */
struct KzuFont* kzuItypeFontToFont(struct KzuItypeFont* itypeFont);


/** Sets the size of iType font (in pixels). */
kzsError kzuItypeFontSetSize(struct KzuItypeFont* itypeFont, kzFloat size);
/** Returns the size of iType font. */
kzFloat kzuItypeFontGetSize(const struct KzuItypeFont* itypeFont);

/** Sets the color of the font. */
void kzuItypeFontSetColor(struct KzuItypeFont* itypeFont, struct KzcColorRGBA color);
/** Gets the color of the font. */
struct KzcColorRGBA kzuItypeFontGetColor(const struct KzuItypeFont* itypeFont);


/** Returns the line height of iType font. */
kzFloat kzuItypeFontGetLineHeight(const struct KzuItypeFont* itypeFont);
/** Returns the ascender of iType font. */
kzFloat kzuItypeFontGetAscender(const struct KzuItypeFont* itypeFont);


/** Returns the advance of given character using iType font. */
kzsError kzuItypeFontGetCharacterMetrics(const struct KzuItypeFont* itypeFont, kzUnicodeChar character,
                                         kzFloat* out_advanceX, kzFloat* out_advanceY, struct KzcRectangle* out_boundingBox);
/** Returns the kerning of given character pair using iType font. */
kzsError kzuItypeFontGetKerning(const struct KzuItypeFont* itypeFont, kzUnicodeChar previousCharacter, kzUnicodeChar character,
                                kzFloat* out_kerningX, kzFloat* out_kerningY);


/**
 * Draws a character at given coordinates. The coordinates indicate the character left point on the baseline.
 * This function is meant for debugging purposes only. For real text rendering, use KzcTextLayouter.
 */
kzsError kzuItypeFontDrawCharacter(const struct KzuItypeFont* itypeFont, struct KzcRenderer* renderer,
                                   kzUnicodeChar character, kzFloat x, kzFloat y);


/** Prepares the given pre-layouted text for fast rendering using iType. */
kzsError kzuItypeFontPrepareTextLayout(struct KzuTextLayout* textLayout, struct KzcRenderer* renderer);

/** Draw the given pre-layouted text using iType. */
kzsError kzuItypeFontDrawTextLayout(struct KzuTextLayout* textLayout, struct KzcRenderer* renderer, kzFloat x, kzFloat y);

/** Draw the given pre-layouted text in 3D space using iType. */
kzsError kzuItypeFontDrawTextLayout3D(struct KzuTextLayout* textLayout, struct KzcRenderer* renderer);

/** Frees the data and resources created by the prepare function. */
kzsError kzuItypeFontFreeTextLayoutData(struct KzuTextLayout* textLayout);

/**
 * Loads a bitmap data for a single character glyph. The returned character glyph needs to be released with a call to release.
 * The bitmap data is returned as a greyscale image with 8 bits per pixel.
 */
kzsError kzuItypeFontLoadCharacterGlyph(const struct KzuItypeFont* itypeFont, kzUnicodeChar character, kzUint* out_width,
                                        kzUint* out_height, const kzByte** out_bitmapData, void** out_characterGlyph);
/** Releases a loaded character glyph. */
kzsError kzuItypeFontReleaseCharacterGlyph(const struct KzuItypeFont* itypeFont, void* characterGlyph);


/** Returns the FS_STATE* object from iType font. */
void* kzuItypeFontGetState(const struct KzuItypeFont* itypeFont);


KZ_HEADER_END


#endif
