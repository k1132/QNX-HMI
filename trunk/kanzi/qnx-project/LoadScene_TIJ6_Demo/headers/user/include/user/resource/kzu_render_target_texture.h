/**
 * \file
 * 2D render target texture.
 * 
 * Copyright 2008-2014 by Rightware. All rights reserved.
 */
#ifndef KZU_RENDER_TARGET_TEXTURE_H
#define KZU_RENDER_TARGET_TEXTURE_H


#include "kzu_resource_common.h"
#include "kzu_texture_base.h"

#include <system/debug/kzs_error.h>
#include <system/kzs_types.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations */
struct KzuGPUResource;
struct KzuRenderTarget;
struct KzuResourceLoader;
struct KzuResourceManager;
struct KzuTexture;
struct KzuFactory;


/**
 * \struct KzuRenderTargetTexture
 * 2D render target texture.
 */
struct KzuRenderTargetTexture;


/** Resource type identifier for 2D render target texture. */
extern const KzuResourceType KZU_RESOURCE_TYPE_RENDER_TARGET_TEXTURE;


/** Creates a 2D render target texture that loads the data when needed using the given resource loader. */
kzsError kzuRenderTargetTextureCreate(const struct KzcMemoryManager* memoryManager, const struct KzuResourceManager* resourceManager, kzString name, struct KzuResourceLoader* loader,
                                      struct KzuRenderTargetTexture** out_renderTargetTexture);

/** Registers image texture type to factory. */
kzsError kzuRenderTargetTextureRegisterToFactory(const struct KzuFactory* factory);

/** Creates a 2D render target texture from memory. */
kzsError kzuRenderTargetTextureCreateFromMemory(const struct KzcMemoryManager* memoryManager, const struct KzuResourceManager* resourceManager, kzString name,
                                                enum KzuTextureDataType dataType, enum KzuTextureChannels channels,
                                                enum KzuTextureFilter filter, enum KzuTextureWrap wrap,
                                                kzUint width, kzUint height, kzBool depthRenderBuffer, kzBool stencilRenderBuffer,
                                                kzUint multisamples, struct KzuRenderTargetTexture** out_renderTargetTexture);

/**
 * Initializes a render target texture with the given arguments.
 * Calling this function is safe only from a resource loader passed as an argument to kzuRenderTargetTextureCreate().
 *
 * \see kzuRenderTargetTextureCreate for creating the render target texture.
 */
kzsError kzuRenderTargetTextureInitializeFromMemory(struct KzuRenderTargetTexture* renderTargetTexture,
                                                    enum KzuTextureDataType dataType, enum KzuTextureChannels channels,
                                                    enum KzuTextureFilter filter, enum KzuTextureWrap wrap,
                                                    kzUint width, kzUint height, kzBool depthRenderBuffer,
                                                    kzBool stencilRenderBuffer, kzUint multisamples);


/** Converts 2D render target texture to texture. */
struct KzuTexture* kzuRenderTargetTextureToTexture(const struct KzuRenderTargetTexture* renderTargetTexture);
/** Converts texture to 2D render target texture. */
struct KzuRenderTargetTexture* kzuRenderTargetTextureFromTexture(const struct KzuTexture* texture);
/** Converts 2D render target texture to GPU resource. */
struct KzuGPUResource* kzuRenderTargetTextureToGPUResource(const struct KzuRenderTargetTexture* renderTargetTexture);
/** Converts GPU resource to 2D render target texture. */
struct KzuRenderTargetTexture* kzuRenderTargetTextureFromGPUResource(const struct KzuGPUResource* gpuResource);
/** Converts 2D render target texture to resource. */
struct KzuResource* kzuRenderTargetTextureToResource(const struct KzuRenderTargetTexture* renderTargetTexture);
/** Converts resource to 2D render target texture. */
struct KzuRenderTargetTexture* kzuRenderTargetTextureFromResource(const struct KzuResource* resource);

/** Returns if render target texture is valid after its deployment. */
kzBool kzuRenderTargetTextureIsValid(const struct KzuRenderTargetTexture* renderTargetTexture);

/** Gets the render target of a 2D render target texture. */
struct KzuRenderTarget* kzuRenderTargetTextureGetRenderTarget(const struct KzuRenderTargetTexture* renderTargetTexture);


/** Checks if the render target texture has depth render buffer. */
kzBool kzuRenderTargetTextureHasDepthRenderBuffer(const struct KzuRenderTargetTexture* renderTargetTexture);
/** Checks if render target texture has stencil render buffer. */
kzBool kzuRenderTargetTextureHasStencilRenderBuffer(const struct KzuRenderTargetTexture* renderTargetTexture);


KZ_HEADER_END


#endif
