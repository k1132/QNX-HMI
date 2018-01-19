/**
* \file
* TrueType font interface.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_TRUETYPE_FONT_H
#define KZU_TRUETYPE_FONT_H


#include <system/debug/kzs_error.h>
#include <system/kzs_types.h>
#include <system/wrappers/kzs_opengl_base.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations. */
struct KzuFont;
struct KzcMemoryManager;
struct KzuUIDomain;
struct KzuShader;

/**
 * \struct KzuTruetypeSystem
 * Font system base for truetype font implementations.
 */
struct KzuTruetypeSystem;


/** Deletes a TrueType font system. */
kzsError kzuTruetypeSystemDelete(struct KzuTruetypeSystem* truetypeSystem);

/** Creates a TrueType font using the given TrueType font system. */
kzsError kzuTruetypeSystemCreateFont(const struct KzcMemoryManager* memoryManager, struct KzuTruetypeSystem* truetypeSystem,
                                     kzString name, struct KzuFont** out_font);

/** Creates a TrueType font from file using the given TrueType font system. */
kzsError kzuTruetypeSystemCreateFontFromFile(const struct KzcMemoryManager* memoryManager,
                                             struct KzuTruetypeSystem* truetypeSystem,
                                             kzString filePath, struct KzuFont** out_font);

/** Creates a TrueType font from memory using the given TrueType font system. */
kzsError kzuTruetypeSystemCreateFontFromMemory(const struct KzcMemoryManager* memoryManager,
                                               struct KzuTruetypeSystem* truetypeSystem, kzString name,
                                               const kzByte* data, kzUint size, struct KzuFont** out_font);

/** Sets shader for Truetype system. */
kzsError kzuTruetypeSystemSetShader(struct KzuTruetypeSystem* truetypeSystem, struct KzuShader* shader);


KZ_HEADER_END


#endif
