/**
 * \file
 * Glyph cache.
 *
 * Copyright 2008-2014 by Rightware. All rights reserved.
 */
#ifndef KZU_GLYPH_CACHE_H
#define KZU_GLYPH_CACHE_H


#include <system/kzs_types.h>
#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations */
struct KzcMemoryManager;
struct KzcRenderer;
struct KzuFont;
struct KzuImageTexture;
struct KzuPropertyManager;
struct KzuResourceManager;

/**
 * \struct KzuGlyphCache
 */
struct KzuGlyphCache;

/** Creates a glyph cache. The texture should be in alpha_8 format. */
kzsError kzuGlyphCacheCreate(const struct KzcMemoryManager* memoryManager, const struct KzuResourceManager* resourceManager,
                             struct KzuImageTexture* texture, struct KzuFont* font, kzFloat glyphSize, struct KzuGlyphCache** out_glyphCache);

/** Deletes a glyph cache. */
kzsError kzuGlyphCacheDelete(struct KzuGlyphCache* glyphCache);

/** Removes all stored glyphs from the cache. */
kzsError kzuGlyphCacheClear(struct KzuGlyphCache* glyphCache);

/** Removes a stored glyph from the cache. */
kzsError kzuGlyphCacheRemove(struct KzuGlyphCache* glyphCache, kzUnicodeChar glyph);

/**
 * Retrieves texture coordinates for a given glyph. If the glyph is not in the glyph cache texture, it is rendered there using
 * the font that was given when creating the glyph cache. In this case, if there is no more empty space left in the glyph cache
 * for the new glyph, then no texture coordinates are written and KZ_FALSE is written to the output parameter 'success'.
 */
kzsError kzuGlyphCacheRetrieveTextureCoordinates(struct KzuGlyphCache* glyphCache, kzUnicodeChar glyph, kzBool* out_success,
                                                 kzFloat* out_leftU, kzFloat* out_topV, kzFloat* out_rightU, kzFloat* out_bottomV);

/**
 * Retrieves texture coordinates for a given glyph. If the glyph is not in the glyph cache texture, it is rendered there using
 * the font that was given when creating the glyph cache. In this case, if there is no more empty space left in the glyph cache
 * for the new glyph, then old glyphs are recycled in the least recently used order.
 */
kzsError kzuGlyphCacheRetrieveTextureCoordinatesRecycling(struct KzuGlyphCache* glyphCache, kzUnicodeChar glyph,
                                                          kzFloat* out_leftU, kzFloat* out_topV, kzFloat* out_rightU, kzFloat* out_bottomV);

/**
 * Retrieves texture coordinates for multiple glyphs. If a glyph is not found in the glyph cache texture, it is rendered there using
 * the font that was given when creating the glyph cache. The 12 texture coordinates of a glyph are written to the output parameter 'data'.
 * If there is no more empty space left in the glyph cache for a new glyph,
 * then that glyph and the following glyphs are not written. The amount of glyphs written is returned in the 'count' output parameter.
 */
kzsError kzuGlyphCacheRetrieveMultipleTextureCoordinates(struct KzuGlyphCache* glyphCache, const kzUnicodeChar* glyphs, kzUint glyphCount,
                                                         kzUint stride, kzUint* out_count, kzByte* out_data);

/**
 * Retrieves texture coordinates for multiple glyphs that might be partially clipped. 
 */
kzsError kzuGlyphCacheRetrieveMultipleTextureCoordinatesWithClipping(struct KzuGlyphCache* glyphCache, const kzUnicodeChar* glyphs, kzUint glyphCount,
                                                                     kzUint stride, const kzFloat* clippingCoordinates, kzUint* out_count, kzByte* out_data);

/** Returns the texture that the cache was created with. */
struct KzuImageTexture* kzuGlyphCacheGetTexture(const struct KzuGlyphCache* glyphcache);


KZ_HEADER_END


#endif
