/**
 * \file
 * Render target base definitions.
 * 
 * Copyright 2008-2014 by Rightware. All rights reserved.
 */
#ifndef KZU_RENDER_TARGET_BASE_H
#define KZU_RENDER_TARGET_BASE_H


#include <system/debug/kzs_error.h>
#include <system/kzs_types.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations */
struct KzcMemoryManager;
struct KzuRenderer;
struct KzuRenderTarget;


/** Function definition for render target binding. */
typedef kzsError (*KzuRenderTargetBindFunction)(struct KzuRenderTarget* renderTarget, struct KzuRenderer* renderer, void* userData);
/** Function definition for render target unbinding. */
typedef kzsError (*KzuRenderTargetUnbindFunction)(struct KzuRenderTarget* renderTarget, struct KzuRenderer* renderer, void* userData);
/** Function definition for querying render target size. */
typedef void (*KzuRenderTargetGetSizeFunction)(const struct KzuRenderTarget* renderTarget, void* userData, kzUint* out_width, kzUint* out_height);


/** Creates a render target. */
kzsError kzuRenderTargetCreate_protected(const struct KzcMemoryManager* memoryManager, kzString name,
                                         KzuRenderTargetBindFunction bindFunction, KzuRenderTargetUnbindFunction unbindFunction,
                                         KzuRenderTargetGetSizeFunction getSizeFunction, void* userData,
                                         struct KzuRenderTarget** out_renderTarget);

/** Deletes a render target. */
kzsError kzuRenderTargetDelete_protected(struct KzuRenderTarget* renderTarget);


KZ_HEADER_END


#endif
