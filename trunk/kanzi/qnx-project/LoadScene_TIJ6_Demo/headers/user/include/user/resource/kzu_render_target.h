/**
 * \file
 * Render target.
 * 
 * Copyright 2008-2014 by Rightware. All rights reserved.
 */
#ifndef KZU_RENDER_TARGET_H
#define KZU_RENDER_TARGET_H


#include <system/debug/kzs_error.h>
#include <system/kzs_types.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations */
struct KzuRenderer;


/**
 * \struct KzuRenderTarget
 * Render target.
 */
struct KzuRenderTarget;


/** Binds a render target for rendering. */
kzsError kzuRenderTargetBind(struct KzuRenderTarget* renderTarget, struct KzuRenderer* renderer);

/** Binds a render target for rendering. */
kzsError kzuRenderTargetUnbind(struct KzuRenderTarget* renderTarget, struct KzuRenderer* renderer);

/** Gets the width of a render target. */
kzUint kzuRenderTargetGetWidth(const struct KzuRenderTarget* renderTarget);

/** Gets the height of a render target. */
kzUint kzuRenderTargetGetHeight(const struct KzuRenderTarget* renderTarget);


KZ_HEADER_END


#endif
