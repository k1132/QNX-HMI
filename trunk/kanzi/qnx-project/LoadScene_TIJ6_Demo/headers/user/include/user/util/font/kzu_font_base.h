/**
* \file
* Font private members.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_FONT_BASE_H
#define KZU_FONT_BASE_H

#include <user/resource/kzu_resource_base.h>

#include <system/debug/kzs_error.h>
#include <system/kzs_types.h>
#include <system/wrappers/kzs_opengl_base.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations */
struct KzcColorRGBA;
struct KzcInputStream;
struct KzcMemoryManager;
struct KzcRectangle;
struct KzcRenderer;
struct KzuBinaryFileInfo;
struct KzuShader;
struct KzuUIDomain;
struct KzuTextLayout;
struct KzuTruetypeSystem;


/** Function definition for deleting TrueType font system. */
typedef kzsError (*KzuTruetypeSystemDeletor)(struct KzuTruetypeSystem* truetypeSystem);
/** Function definition for creating TrueType fonts. */
typedef kzsError (*KzuTruetypeFontCreator)(const struct KzcMemoryManager* memoryManager, struct KzuTruetypeSystem* truetypeSystem,
                                           kzString name, struct KzuFont** out_font);
/** Function definition for creating TrueType fonts from file. */
typedef kzsError (*KzuTruetypeFontFileCreator)(const struct KzcMemoryManager* memoryManager, struct KzuTruetypeSystem* truetypeSystem,
                                               kzString filePath, struct KzuFont** out_font);
/** Function definition for creating TrueType fonts from memory. */
typedef kzsError (*KzuTruetypeFontMemoryCreator)(const struct KzcMemoryManager* memoryManager, struct KzuTruetypeSystem* truetypeSystem,
                                                 kzString name, const kzByte* data, kzUint size, struct KzuFont** out_font);


struct KzuTruetypeSystem
{
    struct KzuUIDomain* uiDomain; /**< UI domain. */
    KzuTruetypeSystemDeletor systemDeletor; /**< Function for deleting the font system. */
    KzuTruetypeFontCreator fontCreator; /**< Function for creating a font. */
    KzuTruetypeFontFileCreator fontFileCreator; /**< Function for creating a font from file. */
    KzuTruetypeFontMemoryCreator fontMemoryCreator; /**< Function for creating a font from memory. */
    struct KzuShader* fontShader; /**< Shader for rendering truetype fonts. */
};


/** Defines functions for different font implementations. */
struct KzuFontClass
{
    /** Frees memory allocated for given font. */
    kzsError (*destructor)(struct KzuFont* font);

    /** Loads font from .KZB. */
    kzsError (*loadfromKZB)(struct KzuFont* font, struct KzcInputStream* inputStream, const struct KzuBinaryFileInfo* file);

    /** Sets the size of the font (in pixels). */
    kzsError (*setSize)(struct KzuFont* font, kzFloat size);
    /** Returns the size of the font. */
    kzsError (*getSize)(struct KzuFont* font, kzFloat* out_size);

    /** Sets the color of the font. */
    kzsError (*setColor)(struct KzuFont* font, struct KzcColorRGBA color);
    /** Gets the color of the font. */
    kzsError (*getColor)(struct KzuFont* font, struct KzcColorRGBA* out_color);

    /** Returns the line height of the font. */
    kzsError (*getLineHeight)(struct KzuFont* font, kzFloat* out_lineHeight);

    /** Returns the ascender of the font. */
    kzsError (*getAscender)(struct KzuFont* font, kzFloat* out_ascender);

    /** Returns the advance of given character using. */
    kzsError (*getCharacterMetrics)(struct KzuFont* font, kzUnicodeChar character, kzFloat* out_advance, struct KzcRectangle* out_boundingBox);

    /** Returns the kerning of given character pair using. */
    kzsError (*getKerning)(struct KzuFont* font, kzUnicodeChar previousCharacter, kzUnicodeChar character, kzFloat* out_kerning);

    /** Loads a bitmap data for a single character glyph. */
    kzsError (*loadCharacterGlyph)(struct KzuFont* font, kzUnicodeChar character, kzUint* out_width,
                                          kzUint* out_height, const kzByte** out_bitmapData, void** out_characterGlyph);

    /** Releases a loaded character glyph. */
    kzsError (*releaseCharacterGlyph)(struct KzuFont* font, void* characterGlyph);

    /** Prepares the given pre-layouted text for fast rendering. */
    kzsError (*prepareTextLayout)(struct KzuTextLayout* textLayout, struct KzcRenderer* renderer);

    /** Draw the given pre-layouted text. */
    kzsError (*drawTextLayout)(struct KzuTextLayout* textLayout, struct KzcRenderer* renderer, kzFloat x, kzFloat y);

    /** Draw the given pre-layouted text in 3D space. */
    kzsError (*drawTextLayout3D)(struct KzuTextLayout* textLayout, struct KzcRenderer* renderer);

    /** Frees the data and resources created by the prepare function. */
    kzsError (*freeTextLayoutData)(struct KzuTextLayout* textLayout);
};

struct KzuFont
{
    struct KzuResource resource; /**< Inherited from resource. */
    const struct KzuFontClass* fontClass; /**< Class of the font. */
};


/** Initializes the base of a TrueType font system. */
kzsError kzuTruetypeSystemInitialize_protected(struct KzuTruetypeSystem* truetypeSystem, struct KzuUIDomain* uiDomain, KzuTruetypeSystemDeletor systemDeletor,
                                               KzuTruetypeFontCreator fontCreator, KzuTruetypeFontFileCreator fontFileCreator,
                                               KzuTruetypeFontMemoryCreator fontMemoryCreator);


/** Creates a font. */
kzsError kzuFontCreate_protected(const struct KzuFontClass* fontClass, const struct KzuUIDomain* uiDomain, kzString name, struct KzuFont* font);


KZ_HEADER_END


#endif
