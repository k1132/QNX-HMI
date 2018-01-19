/**
 * \file
 * Text Manager.
 *
 * Copyright 2008-2014 by Rightware. All rights reserved.
 */
#ifndef KZU_TEXT_MANAGER_H
#define KZU_TEXT_MANAGER_H


#include <system/kzs_types.h>
#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations */
struct KzcMemoryManager;
struct KzuFont;
struct KzuGlyphCache;
struct KzuResourceManager;

/**
 * \struct KzuTextManager
 */
struct KzuTextManager;

/** Creates a text manager. */
kzsError kzuTextManagerCreate(const struct KzcMemoryManager* memoryManager, struct KzuResourceManager* resourceManager, struct KzuTextManager** out_textManager);

/** Deletes a text manager. */
kzsError kzuTextManagerDelete(struct KzuTextManager* textManager);

/** Retrieves the glyph cache associated with the given font and font size. */
kzsError kzuTextManagerGetGlyphCache(const struct KzuTextManager* textManager, struct KzuFont* font, kzFloat fontSize, struct KzuGlyphCache** out_glyphCache);


KZ_HEADER_END


#endif
