/**
 * \file
 * Application framework watermark.
 * 
 * Copyright 2008-2014 by Rightware. All rights reserved.
 */
#ifndef KZA_WATERMARK_H
#define KZA_WATERMARK_H


#include <system/kzs_types.h>
#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations */
struct KzcMemoryManager;
struct KzcRenderer;
struct KzuCanvas;
struct KzuResourceManager;


/**
 * \struct KzaWatermark
 * Watermark structure.
 */
struct KzaWatermark;


/** Creates watermark structure. */
kzsError kzaWatermarkCreate(const struct KzcMemoryManager* memoryManager, const struct KzuResourceManager* resourceManager,
                            struct KzaWatermark** out_watermark);

/** Deletes watermark structure. */
kzsError kzaWatermarkDelete(struct KzaWatermark* watermark, struct KzcRenderer* renderer);

/** Renders watermark. */
kzsError kzaWatermarkRender(const struct KzaWatermark* watermark, struct KzcRenderer* renderer, const struct KzuCanvas* canvas);


KZ_HEADER_END


#endif
