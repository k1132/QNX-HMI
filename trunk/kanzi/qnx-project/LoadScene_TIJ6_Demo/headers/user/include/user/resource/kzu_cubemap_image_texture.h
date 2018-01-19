/**
 * \file
 * Cubemap image texture.
 * 
 * Copyright 2008-2014 by Rightware. All rights reserved.
 */
#ifndef KZU_CUBEMAP_IMAGE_TEXTURE_H
#define KZU_CUBEMAP_IMAGE_TEXTURE_H


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
 * \struct KzuCubemapImageTexture
 * 2D Image texture.
 */
struct KzuCubemapImageTexture;


/** Resource type identifier for cubemap image texture. */
extern const KzuResourceType KZU_RESOURCE_TYPE_CUBEMAP_IMAGE_TEXTURE;


/** Creates a cubemap image texture that loads the data when needed using the given resource loader. */
kzsError kzuCubemapImageTextureCreate(const struct KzuResourceManager* resourceManager, kzString name, struct KzuResourceLoader* loader,
                                      struct KzuCubemapImageTexture** out_cubemapImageTexture);

/** Registers image texture type to factory. */
kzsError KzuCubemapImageTextureRegisterToFactory(const struct KzuFactory* factory);

/**
 * Creates an cubemap image texture from the given cube map image.
 * Images should be given in order: positive-X, negagitve-X, positive-Y, negative-Y, positive-Z, negative-Z.
 */
kzsError kzuCubemapImageTextureCreateFromImages(const struct KzuResourceManager* resourceManager, kzString name,
                                                const struct KzcImage* images[6], enum KzuTextureFilter filter,
                                                enum KzuTextureWrap wrap, struct KzuCubemapImageTexture** out_cubemapImageTexture);

/**
 * Initializes a cubemap image texture from an array of images with the given arguments.
 * Calling this function is safe only from a resource loader passed as an argument to kzuCubemapImageTextureCreate().
 *
 * \see kzuCubemapImageTextureCreate for creating the cubemap image texture.
 */
kzsError kzuCubemapImageTextureInitializeFromImages(const struct KzcMemoryManager* memoryManager, struct KzuCubemapImageTexture* cubemapImageTexture,
                                                    const struct KzcImage* images[6], enum KzuTextureFilter filter,
                                                    enum KzuTextureWrap wrap);


/** Converts cubemap image texture to texture. */
struct KzuTexture* kzuCubemapImageTextureToTexture(const struct KzuCubemapImageTexture* cubemapImageTexture);
/** Converts texture to cubemap image texture. */
struct KzuCubemapImageTexture* kzuCubemapImageTextureFromTexture(const struct KzuTexture* texture);
/** Converts cubemap image texture to GPU resource. */
struct KzuGPUResource* kzuCubemapImageTextureToGPUResource(const struct KzuCubemapImageTexture* cubemapImageTexture);
/** Converts GPU resource to cubemap image texture. */
struct KzuCubemapImageTexture* kzuCubemapImageTextureFromGPUResource(const struct KzuGPUResource* gpuResource);
/** Converts cubemap image texture to resource. */
struct KzuResource* kzuCubemapImageTextureToResource(const struct KzuCubemapImageTexture* cubemapImageTexture);
/** Converts resource to cubemap image texture. */
struct KzuCubemapImageTexture* kzuCubemapImageTextureFromResource(const struct KzuResource* resource);


KZ_HEADER_END


#endif
