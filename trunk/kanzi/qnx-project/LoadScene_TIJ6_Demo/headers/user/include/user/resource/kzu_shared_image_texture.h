/**
 * \file
 * Shared 2D image texture.
 * 
 * Copyright 2008-2014 by Rightware. All rights reserved.
 */
#ifndef KZU_SHARED_IMAGE_TEXTURE_H
#define KZU_SHARED_IMAGE_TEXTURE_H


#include "kzu_resource_common.h"
#include "kzu_texture_base.h"

#include <system/debug/kzs_error.h>
#include <system/kzs_types.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations */
struct KzcImage;
struct KzuGPUResource;
struct KzuResourceLoader;
struct KzuResourceManager;
struct KzuTexture;
struct KzuFactory;


/**
 * \struct KzuSharedImageTexture
 * Shared 2D Image texture.
 */
struct KzuSharedImageTexture;


/** Resource type identifier for shared 2D image texture. */
extern const KzuResourceType KZU_RESOURCE_TYPE_SHARED_IMAGE_TEXTURE;

/** Callback for creating external texture. On Android, OpenGL context is recreated when resumed. */
typedef kzsError (*kzuSharedImageTextureExternalTextureCreateFunction)(struct KzuSharedImageTexture* imageTexture, kzUint* out_textureHandle);


/** Creates a shared 2D image texture that can perform data updates asynchronously. It's by default an RGBA8 texture, unless otherwise specified in client buffer.
 * \param width Width of the texture.
 * \param height Height of the texture.
 * \param clientBuffer Client buffer to perform the data upload, for example Android GraphicBuffer. When KZ_NULL, ignored.
 * \param userData Platform specific user data of the client buffer, directly EGL config when utilizing. When KZ_NULL, ignored.
 * \param isExternalTexture Is texture external, can be utilized when retrieving data non-RGB format such as YUV and doing the conversion on GPU via EXTERNAL_TEXTURE_OES extension. 
                            When using external textures in OpenGL shader, user must make sure that sampler uniform is type of samplerExternalOES instead of sampler2D and extension
                            #extension GL_OES_EGL_image_external : require has been specified.
*/
kzsError kzuSharedImageTextureCreate(const struct KzuResourceManager* resourceManager, kzString name, enum KzuTextureChannels channels,
                                     kzUint width, kzUint height, void* clientBuffer, void* userData, kzBool isExternalTexture, 
                                     struct KzuSharedImageTexture** out_imageTexture);

/** Creates a shared 2D image texture that shares texture data with a texture created in the same or another OpenGL context. 
 *  When using external textures in OpenGL shader, user must make sure that sampler uniform is type of samplerExternalOES instead of sampler2D and extension
 *  #extension GL_OES_EGL_image_external : require has been specified.
 * \param externalTextureHandle Texture handle of the texture being shared.
 */
kzsError kzuSharedImageTextureCreateExternal(const struct KzuResourceManager* resourceManager, kzString name, kzUint width, kzUint height, void* userData, 
                                             kzUint externalTextureHandle, kzuSharedImageTextureExternalTextureCreateFunction externalTextureCreator,
                                             struct KzuSharedImageTexture** out_imageTexture);

/** Registers shared image texture type to factory. */
kzsError kzuSharedImageTextureRegisterToFactory(const struct KzuFactory* factory);


/** Converts 2D image texture to texture. */
struct KzuTexture* kzuSharedImageTextureToTexture(const struct KzuSharedImageTexture* imageTexture);
/** Converts texture to 2D image texture. */
struct KzuSharedImageTexture* kzuSharedImageTextureFromTexture(const struct KzuTexture* texture);
/** Converts 2D image texture to GPU resource. */
struct KzuGPUResource* kzuSharedImageTextureToGPUResource(const struct KzuSharedImageTexture* imageTexture);
/** Converts GPU resource to 2D image texture. */
struct KzuSharedImageTexture* kzuSharedImageTextureFromGPUResource(const struct KzuGPUResource* gpuResource);
/** Converts 2D image texture to resource. */
struct KzuResource* kzuSharedImageTextureToResource(const struct KzuSharedImageTexture* imageTexture);
/** Converts resource to 2D image texture. */
struct KzuSharedImageTexture* kzuSharedImageTextureFromResource(const struct KzuResource* resource);


/** Locks data update. When locked, data can be safely updated in separate thread / process. */
kzsError kzuSharedImageTextureLock(struct KzuSharedImageTexture* imageTexture);
/** Performs the data update for image texture. Must be called between Lock and Unlock. */
kzsError kzuSharedImageTextureUpdate(struct KzuSharedImageTexture* imageTexture, void* data, kzUint dataSize);
/** Unlocks data update for image texture. When unlocked, main thread can safely take the data into use. */
kzsError kzuSharedImageTextureUnlock(struct KzuSharedImageTexture* imageTexture);

/** Gets user data. */
void* kzuSharedImageTextureGetUserData(const struct KzuSharedImageTexture* imageTexture);


KZ_HEADER_END


#endif
