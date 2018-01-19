/**
 * \file
 * Cubemap render target texture.
 * 
 * Copyright 2008-2014 by Rightware. All rights reserved.
 */
#ifndef KZU_CUBEMAP_RENDER_TARGET_TEXTURE_H
#define KZU_CUBEMAP_RENDER_TARGET_TEXTURE_H


#include "kzu_resource_common.h"
#include "kzu_texture_base.h"

#include <system/debug/kzs_error.h>
#include <system/kzs_types.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations */
struct KzuGPUResource;
struct KzuCubemapRenderTarget;
struct KzuResourceLoader;
struct KzuResourceManager;
struct KzuTexture;
struct KzuFactory;


/**
 * \struct KzuCubemapRenderTargetTexture
 * Cubemap render target texture.
 */
struct KzuCubemapRenderTargetTexture;


/** Resource type identifier for cubemap render target texture. */
extern const KzuResourceType KZU_RESOURCE_TYPE_CUBEMAP_RENDER_TARGET_TEXTURE;


/** Creates a cube map render target texture that loads the data when needed using the given resource loader. */
kzsError kzuCubemapRenderTargetTextureCreate(const struct KzuResourceManager* resourceManager, kzString name, struct KzuResourceLoader* loader,
                                             struct KzuCubemapRenderTargetTexture** out_cubemapRenderTargetTexture);

/** Registers cubemap render target texture type to factory. */
kzsError kzuCubemapRenderTargetTextureRegisterToFactory(const struct KzuFactory* factory);

/** Creates a cube map render target texture from memory. */
kzsError kzuCubemapRenderTargetTextureCreateFromMemory(const struct KzuResourceManager* resourceManager, kzString name,
                                                       enum KzuTextureDataType dataType, enum KzuTextureChannels channels,
                                                       enum KzuTextureFilter filter, enum KzuTextureWrap wrap,
                                                       kzUint size, struct KzuCubemapRenderTargetTexture** out_cubemapRenderTargetTexture);

/**
 * Initializes a cubemap render target texture with the given arguments.
 * Calling this function is safe only from a resource loader passed as an argument to kzuCubemapRenderTargetTextureCreate().
 *
 * \see kzuCubemapRenderTargetTextureCreate for creating the cubemap render target texture.
 */
kzsError kzuCubemapRenderTargetTextureInitializeFromMemory(struct KzuCubemapRenderTargetTexture* cubemapRenderTargetTexture,
                                                           enum KzuTextureDataType dataType, enum KzuTextureChannels channels,
                                                           enum KzuTextureFilter filter, enum KzuTextureWrap wrap, kzUint size);


/** Converts cubemap render target texture to texture. */
struct KzuTexture* kzuCubemapRenderTargetTextureToTexture(const struct KzuCubemapRenderTargetTexture* cubemapRenderTargetTexture);
/** Converts texture to cubemap render target texture. */
struct KzuCubemapRenderTargetTexture* kzuCubemapRenderTargetTextureFromTexture(const struct KzuTexture* texture);
/** Converts cubemap render target texture to GPU resource. */
struct KzuGPUResource* kzuCubemapRenderTargetTextureToGPUResource(const struct KzuCubemapRenderTargetTexture* cubemapRenderTargetTexture);
/** Converts GPU resource to cubemap render target texture. */
struct KzuCubemapRenderTargetTexture* kzuCubemapRenderTargetTextureFromGPUResource(const struct KzuGPUResource* gpuResource);
/** Converts cubemap render target texture to resource. */
struct KzuResource* kzuCubemapRenderTargetTextureToResource(const struct KzuCubemapRenderTargetTexture* cubemapRenderTargetTexture);
/** Converts resource to cubemap render target texture. */
struct KzuCubemapRenderTargetTexture* kzuCubemapRenderTargetTextureFromResource(const struct KzuResource* resource);


/** Gets the render target of a cube map render target texture. */
struct KzuRenderTarget* kzuCubemapRenderTargetTextureGetRenderTarget(const struct KzuCubemapRenderTargetTexture* cubemapRenderTargetTexture,
                                                                     kzUint face);


KZ_HEADER_END


#endif
