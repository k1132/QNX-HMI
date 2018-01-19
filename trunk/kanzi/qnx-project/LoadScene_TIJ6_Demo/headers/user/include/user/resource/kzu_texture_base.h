/**
 * \file
 * Texture base definitions.
 * 
 * Copyright 2008-2014 by Rightware. All rights reserved.
 */
#ifndef KZU_TEXTURE_BASE_H
#define KZU_TEXTURE_BASE_H


#include "kzu_texture.h"
#include "kzu_gpu_resource_base.h"

#include <core/renderer/kzc_renderer.h>
#include <core/util/image/kzc_image.h>

#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations */
struct KzcImage;
struct KzuUIDomain;


/** Defines functions for different texture types. */
struct KzuTextureClass
{
    struct KzuGPUResourceClass base; /**< Inherited from KzuGPUResourceClass. */

    enum KzcRendererTextureType rendererType; /**< Texture type for binding to OpenGL. */

    /** Bind function for applying texture for rendering. */
    kzsError (*bind)(struct KzuTexture* texture);

    /** Unbind function for detaching the texture from rendering. */
    kzsError (*unbind)(struct KzuTexture* texture);
};


/** Texture class. */
extern const struct KzuTextureClass KZU_TEXTURE_CLASS;


struct KzuTexture
{
    struct KzuGPUResource gpuResource; /**< Inherited from KzuGPUResource. */

    enum KzuTextureDataType dataType; /**< Data type. */
    enum KzuTextureChannels channels; /**< Channels. */
    enum KzuTextureCompression compression; /**< Compression. */

    enum KzuTextureFilter filter; /**< Filter. */
    enum KzuTextureWrap wrap; /**< Wrap mode. */
    kzFloat anisotropy; /**< Maximum anisotropy to use if possible. */

    kzUint width; /**< Width of the texture. */
    kzUint height; /**< Height of the texture. */

    kzUint textureHandle; /**< Texture handle. This is 0 if the texture is invalid. */
};


/**
 * Base function for creating textures. All texture sub type constructors should call this first. 
 * \param KzuResourceLoader Resource loader for loading resource data. Can be KZ_NULL, in which case the constructor should call kzuResourceStaticDataSet_protected after the data has been initialized.
 */
kzsError kzuTextureCreate_protected(struct KzuTexture* texture, const struct KzuTextureClass* textureClass,
                                    struct KzuResourceManager* resourceManager, kzString name, struct KzuResourceLoader* loader);

/**
 * Base function for initializing a texture. 
 *
 * @param anisotropy Set anisotropic filtering level of texture. Values <= 1.0f disable the feature.
 */
kzsError kzuTextureInitialize_protected(struct KzuTexture* texture, enum KzuTextureFilter filter, enum KzuTextureWrap wrap,
                                        kzFloat anisotropy);

/** Base destructor for textures. */
kzsError kzuTextureDestructor_protected(struct KzuResource* resource);

/** Base function for loading textures from .KZB. */
kzsError kzuTextureLoadFromKZB_protected(struct KzuResource* resource, const struct KzuResourceLoaderThreadContext* threadContext,
                                         struct KzcInputStream* inputStream, struct KzuBinaryFileInfo* file);

/** Base function for finishing the loading of textures. */
kzsError kzuTextureFinishLoading_protected(struct KzuResource* resource, const struct KzuResourceLoaderThreadContext* threadContext);

/** Base function for unloading textures. */
kzsError kzuTextureUnload_protected(struct KzuResource* resource);

/** Base function for getting CPU memory usage of textures. */
kzUint kzuTextureGetCPUMemoryUsage_protected(const struct KzuResource* resource);

/** Base function for deploying textures. */
kzsError kzuTextureDeploy_protected(struct KzuGPUResource* gpuResource);

/** Base function for undeploying textures. */
kzsError kzuTextureUndeploy_protected(struct KzuGPUResource* gpuResource);

/** Base function for freeing RAM of textures. */
kzsError kzuTextureFreeCommonData_protected(struct KzuGPUResource* gpuResource);

/** Base function for invalidating textures. */
kzsError kzuTextureInvalidate_protected(struct KzuGPUResource* gpuResource);

/** Base function for getting GPU memory usage of textures. */
kzUint kzuTextureGetGPUMemoryUsage_protected(const struct KzuGPUResource* gpuResource);

/** Gets core renderer texture format from texture format (data type + channels + compression). */
enum KzcRendererTextureFormat kzuTextureFormatToRendererFormat_protected(enum KzuTextureDataType dataType,
                                                                         enum KzuTextureChannels channels,
                                                                         enum KzuTextureCompression compression);

/** Converts image format to texture format (data type + channels + compression). */
void kzuTextureFormatFromImageFormat_protected(enum KzcImageDataFormat imageFormat, enum KzuTextureDataType* out_dataType,
                                               enum KzuTextureChannels* out_channels, enum KzuTextureCompression* out_compression);

/** Gets image format from texture format (data type + channels + compression). */
enum KzcImageDataFormat kzuTextureFormatToImageFormat_protected(enum KzuTextureDataType dataType,
                                                                enum KzuTextureChannels channels,
                                                                enum KzuTextureCompression compression);

/** Gets the number of channels from channels enumeration. */
kzUint kzuTextureGetChannelCount_protected(enum KzuTextureChannels channels);

/** Gets bytes per pixel from texture format (data type + channels). Does not support compressed formats. */
kzUint kzuTextureFormatGetBytesPerPixel_protected(enum KzuTextureDataType dataType, enum KzuTextureChannels channels);

/** Gets renderer texture compression from texture compression. */
enum KzcRendererTextureCompression kzuTextureCompressionToRendererCompression_protected(enum KzuTextureCompression compression);

/** Loads a texture image from given path. */
kzsError kzuTextureGetImageFromPath_protected(const struct KzcMemoryManager* memoryManager, struct KzuBinaryDirectory* directory, kzString imagePath,
                                              kzUint maximumTextureSize, kzString defaultImagePath,
                                              struct KzcImage** out_image, kzBool* out_defaultImageUsed);

/** Ensures that the given image is in requested and supported format. */
kzsError kzuTextureValidateImageFormat_protected(const struct KzcMemoryManager* memoryManager, struct KzuTexture* texture, struct KzcImage* image, 
                                                 struct KzcRenderer* renderer, enum KzcImageDataFormat requestedImageFormat);

/** Checks if the given texture needs mipmap data. */
kzBool kzuTextureRequiresMipmaps_protected(const struct KzuTexture* texture);


KZ_HEADER_END


#endif
