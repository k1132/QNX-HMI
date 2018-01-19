/**
* \file
* Bitmap font.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_BITMAP_FONT_H
#define KZU_BITMAP_FONT_H


#include "kzu_font_common.h"

#include <core/util/color/kzc_color.h>

#include <system/debug/kzs_error.h>
#include <system/wrappers/kzs_opengl_base.h>
#include <system/kzs_types.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations */
struct KzcInputStream;
struct KzcMemoryManager;
struct KzcRectangle;
struct KzcRenderer;
struct KzuBinaryFileInfo;
struct KzuFont;
struct KzuResourceManager;
struct KzuShader;
struct KzuTextLayout;
struct KzuTexture;
struct KzuUIDomain;


/**
 * \struct KzuBitmapFontSystem
 * Structure for bitmap font system. This system is needed for bitmap fonts.
 * Usually one bitmap font system per application is enough, but more can be used if needed.
 */
struct KzuBitmapFontSystem;

/**
* \struct KzuBitmapFont
* Font structure for rendering text.
*/
struct KzuBitmapFont;


/** Font type identifier for bitmap font objects. */
extern const KzuFontType KZU_FONT_TYPE_BITMAP;


/** Creates a bitmap font system. */
kzsError kzuBitmapFontSystemCreate(const struct KzcMemoryManager* memoryManager, struct KzuBitmapFontSystem** out_bitmapSystem);

/** Deletes a bitmap font system. */
kzsError kzuBitmapFontSystemDelete(struct KzuBitmapFontSystem* bitmapSystem);

/** Sets shader for bitmap font system. */
kzsError kzuBitmapFontSystemSetShader(struct KzuBitmapFontSystem* bitmapSystem, struct KzuShader* shader);


/** Creates new font without any data. */
kzsError kzuBitmapFontCreate(const struct KzcMemoryManager* memoryManager, struct KzuBitmapFontSystem* bitmapSystem,
                             const struct KzuUIDomain* uiDomain, kzString name, struct KzuBitmapFont** out_bitmapFont);
/** Creates new font from file. */
kzsError kzuBitmapFontCreateFromFile(const struct KzcMemoryManager* memoryManager, struct KzuBitmapFontSystem* bitmapSystem,
                                     const struct KzuUIDomain* uiDomain, kzString filePath,
                                     struct KzuBitmapFont** out_bitmapFont);
/** Creates new font from resource. */
kzsError kzuBitmapFontCreateFromResource(const struct KzcMemoryManager* memoryManager, struct KzuBitmapFontSystem* bitmapSystem,
                                         const struct KzuUIDomain* uiDomain, kzString resourcePath,
                                         struct KzuBitmapFont** out_bitmapFont);
/** Creates new font from preloaded resources. */
kzsError kzuBitmapFontCreateFromMemory(const struct KzcMemoryManager* memoryManager, struct KzuBitmapFontSystem* bitmapSystem,
                                       const struct KzuUIDomain* uiDomain, kzString name, kzString fntFileContent,
                                       struct KzuBitmapFont** out_bitmapFont);

                                       /** Frees memory allocated for given bitmap font. */
kzsError kzuBitmapFontDelete(struct KzuBitmapFont* bitmapFont);

/** Loads font from KZB. */
kzsError kzuBitmapFontLoadFromKZB(struct KzuBitmapFont* bitmapFont, struct KzcInputStream* inputStream, const struct KzuBinaryFileInfo* file);


/** Type cast from generic font to bitmap font. */
struct KzuBitmapFont* kzuBitmapFontFromFont(struct KzuFont* font);
/** Type cast from bitmap font to generic font. */
struct KzuFont* kzuBitmapFontToFont(struct KzuBitmapFont* bitmapFont);


/** Gets font texture names from font. */
struct KzcDynamicArrayIterator kzuBitmapFontGetFontTextureNames(const struct KzuBitmapFont* bitmapFont);
/** Sets texture to given slot in font. The font takes ownership of the font after the operation and releases the texture when font is released. */
kzsError kzuBitmapFontSetTexture(const struct KzuBitmapFont* bitmapFont, struct KzuTexture* texture, kzUint slot);


/** Sets the size of bitmap font (in pixels). */
void kzuBitmapFontSetSize(struct KzuBitmapFont* bitmapFont, kzUint size);
/** Sets the scale (relative size) of bitmap font. */
void kzuBitmapFontSetScale(struct KzuBitmapFont* bitmapFont, kzFloat scale);
/** Returns the size of bitmap font. */
kzFloat kzuBitmapFontGetSize(const struct KzuBitmapFont* bitmapFont);

/** Sets the color of the font. */
void kzuBitmapFontSetColor(struct KzuBitmapFont* bitmapFont, struct KzcColorRGBA color);
/** Gets the color of the font. */
struct KzcColorRGBA kzuBitmapFontGetColor(const struct KzuBitmapFont* bitmapFont);


/** Returns the line height of bitmap font. */
kzFloat kzuBitmapFontGetLineHeight(const struct KzuBitmapFont* bitmapFont);
/** Returns the ascender of bitmap font. */
kzFloat kzuBitmapFontGetAscender(const struct KzuBitmapFont* bitmapFont);


/** Returns the advance of given character using bitmap font. */
void kzuBitmapFontGetCharacterMetrics(const struct KzuBitmapFont* bitmapFont, kzUnicodeChar character,
                                      kzFloat* out_advance, struct KzcRectangle* out_boundingBox);
/** Returns the kerning of given character pair using bitmap font. */
kzFloat kzuBitmapFontGetKerning(const struct KzuBitmapFont* bitmapFont, kzUnicodeChar previousCharacter, kzUnicodeChar character);


/**
 * Draws a character at given coordinates. The coordinates indicate the character left point on the baseline.
 * This function is meant for debugging purposes only. For real text rendering, use KzcTextLayouter.
 */
kzsError kzuBitmapFontDrawCharacter(const struct KzuBitmapFont* bitmapFont, struct KzcRenderer* renderer,
                                    kzUnicodeChar character, kzFloat x, kzFloat y);


/** Prepares the given pre-layouted text for fast rendering using bitmap font. */
kzsError kzuBitmapFontPrepareTextLayout(struct KzuTextLayout* textLayout, struct KzcRenderer* renderer);
 
/** Draw the given pre-layouted text using bitmap font. */
kzsError kzuBitmapFontDrawTextLayout(struct KzuTextLayout* textLayout, struct KzcRenderer* renderer, kzFloat x, kzFloat y);

/** Draw the given pre-layouted text in 3D space using bitmap font. */
kzsError kzuBitmapFontDrawTextLayout3D(struct KzuTextLayout* textLayout, struct KzcRenderer* renderer);

/** Frees the data and resources created by the prepare function. */
kzsError kzuBitmapFontFreeTextLayoutData(struct KzuTextLayout* textLayout);


KZ_HEADER_END


#endif
