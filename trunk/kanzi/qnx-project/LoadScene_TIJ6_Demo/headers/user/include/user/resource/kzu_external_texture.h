/**
 * \file
 * External texture. The texture is managed outside Kanzi, but can be bound as a texture like any other texture.
 * 
 * Copyright 2008-2014 by Rightware. All rights reserved.
 */
#ifndef KZU_EXTERNAL_TEXTURE_H
#define KZU_EXTERNAL_TEXTURE_H


#include "kzu_resource_common.h"
#include "kzu_texture_base.h"

#include <system/debug/kzs_error.h>
#include <system/kzs_types.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations */
struct KzuGPUResource;
struct KzuResource;
struct KzuResourceManager;
struct KzuTexture;


/**
 * \struct KzuExternalTexture
 * External texture.
 */
struct KzuExternalTexture;


/** Resource type identifier for external texture. */
extern const KzuResourceType KZU_RESOURCE_TYPE_EXTERNAL_TEXTURE;


/** Creates an external 2D texture. textureHandle is the OpenGL texture name. */
kzsError kzuExternalTextureCreate2D(struct KzuResourceManager* resourceManager, kzString name,
                                    enum KzuTextureChannels channels, kzUint width, kzUint height, kzUint textureHandle,
                                    struct KzuExternalTexture** out_externalTexture);

/** Creates an external cubemap texture. textureHandle is the OpenGL texture name. */
kzsError kzuExternalTextureCreateCubemap(struct KzuResourceManager* resourceManager, kzString name,
                                         enum KzuTextureChannels channels, kzUint size, kzUint textureHandle,
                                         struct KzuExternalTexture** out_externalTexture);


/** Converts external texture to texture. */
struct KzuTexture* kzuExternalTextureToTexture(const struct KzuExternalTexture* externalTexture);
/** Converts texture to external texture. */
struct KzuExternalTexture* kzuExternalTextureFromTexture(const struct KzuTexture* texture);
/** Converts external texture to GPU resource. */
struct KzuGPUResource* kzuExternalTextureToGPUResource(const struct KzuExternalTexture* externalTexture);
/** Converts GPU resource to external texture. */
struct KzuExternalTexture* kzuExternalTextureFromGPUResource(const struct KzuGPUResource* gpuResource);
/** Converts external texture to resource. */
struct KzuResource* kzuExternalTextureToResource(const struct KzuExternalTexture* externalTexture);
/** Converts resource to external texture. */
struct KzuExternalTexture* kzuExternalTextureFromResource(const struct KzuResource* resource);


KZ_HEADER_END


#endif
