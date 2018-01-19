/**
 * \file
 * Abstract texture.
 * 
 * Copyright 2008-2014 by Rightware. All rights reserved.
 */
#ifndef KZU_TEXTURE_H
#define KZU_TEXTURE_H


#include "kzu_resource_common.h"

#include <system/debug/kzs_error.h>
#include <system/kzs_types.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations */
struct KzuGPUResource;
struct KzuPropertyType;
struct KzuResourceManager;
struct KzuStructPropertyType;


/**
 * \struct KzuTexture
 * Abstract texture.
 */
struct KzuTexture;


/** Resource type identifier for texture. */
extern const KzuResourceType KZU_RESOURCE_TYPE_TEXTURE;


/** Data type of texture data. */
enum KzuTextureDataType
{
    KZU_TEXTURE_DATA_TYPE_INVALID, /**< Invalid texture data type. */
    KZU_TEXTURE_DATA_TYPE_UNKNOWN, /**< Unknown texture data type, e.g. due to compression. */
    KZU_TEXTURE_DATA_TYPE_U8, /**< 8-bit integer data type. */
    KZU_TEXTURE_DATA_TYPE_U16, /**< 16-bit integer data type. */
    KZU_TEXTURE_DATA_TYPE_U24, /**< 24-bit integer data type. */
    KZU_TEXTURE_DATA_TYPE_U32, /**< 32-bit integer data type. */
    KZU_TEXTURE_DATA_TYPE_565, /**< RGB565 packed data type. */
    KZU_TEXTURE_DATA_TYPE_F16, /**< 16-bit floating point data type (half-float). */
    KZU_TEXTURE_DATA_TYPE_F32 /**< 32-bit floating point data type. */
};

/** Channels of texture data. */
enum KzuTextureChannels
{
    KZU_TEXTURE_CHANNELS_INVALID, /**< Invalid texture channels. */
    KZU_TEXTURE_CHANNELS_RGB, /**< Red, Green and Blue channels. */
    KZU_TEXTURE_CHANNELS_RGBA, /**< Red, Green, Blue and Alpha channels. */
    KZU_TEXTURE_CHANNELS_LUMINANCE, /**< Luminance channel only. */
    KZU_TEXTURE_CHANNELS_ALPHA, /**< Alpha channel only. */
    KZU_TEXTURE_CHANNELS_LUMINANCE_ALPHA, /**< Luminance and Alpha channels. */
    KZU_TEXTURE_CHANNELS_DEPTH /**< Depth channel only. */
};

/** Compression of texture data. */
enum KzuTextureCompression
{
    KZU_TEXTURE_COMPRESSION_NONE, /**< No compression. */
    KZU_TEXTURE_COMPRESSION_ETC, /**< ETC compression (no alpha). */
    KZU_TEXTURE_COMPRESSION_DXT3, /**< DXT3 compression (with alpha). */
    KZU_TEXTURE_COMPRESSION_DXT5, /**< DXT5 compression (with alpha). */
    KZU_TEXTURE_COMPRESSION_ATC, /**< ATC compression without alpha. */
    KZU_TEXTURE_COMPRESSION_ATC_EXPLICIT_ALPHA, /**< ATC compression with explicit alpha. */
    KZU_TEXTURE_COMPRESSION_ATC_INTERPOLATED_ALPHA, /**< ATC compression with interpolated alpha. */
    KZU_TEXTURE_COMPRESSION_PVRTC1_RGB_2BPP, /**< PVRTC1 compression, 2 bits per pixel */
    KZU_TEXTURE_COMPRESSION_PVRTC1_RGBA_2BPP, /**< PVRTC1 compression, 2 bits per pixel */
    KZU_TEXTURE_COMPRESSION_PVRTC1_RGB_4BPP, /**< PVRTC1 compression, 4 bits per pixel */
    KZU_TEXTURE_COMPRESSION_PVRTC1_RGBA_4BPP, /**< PVRTC1 compression, 4 bits per pixel */
    KZU_TEXTURE_COMPRESSION_PVRTC2_RGBA_2BPP, /**< PVRTC2 compression, 2 bits per pixel */
    KZU_TEXTURE_COMPRESSION_PVRTC2_RGBA_4BPP  /**< PVRTC2 compression, 4 bits per pixel */
};

/** Supported texture filters. */
enum KzuTextureFilter
{
    KZU_TEXTURE_FILTER_INVALID, /**< Invalid texture filter. */
    KZU_TEXTURE_FILTER_POINT_SAMPLE, /**< Point sample filter. */
    KZU_TEXTURE_FILTER_BILINEAR, /**< Bilinear filter. */
    KZU_TEXTURE_FILTER_TRILINEAR, /**< Trilinear filter. */
    KZU_TEXTURE_FILTER_MIPMAP /**< Mipmap point sample filter. */
};

/** Supported texture wrapping modes. */
enum KzuTextureWrap
{
    KZU_TEXTURE_WRAP_INVALID, /**< Invalid texture wrap mode. */
    KZU_TEXTURE_WRAP_REPEAT, /**< Repeating texture, maps points outside [0, 1] inside the ares by repeating texture. */
    KZU_TEXTURE_WRAP_CLAMP /**< Clamp texture, points outside [0, 1] are sampled from texture edges. */
};


/** Converts texture to GPU resource. */
struct KzuGPUResource* kzuTextureToGPUResource(const struct KzuTexture* texture);
/** Converts GPU resource to texture. */
struct KzuTexture* kzuTextureFromGPUResource(const struct KzuGPUResource* gpuResource);
/** Converts texture to resource. */
struct KzuResource* kzuTextureToResource(const struct KzuTexture* texture);
/** Converts resource to texture. */
struct KzuTexture* kzuTextureFromResource(const struct KzuResource* resource);
/** Casts texture from resource, KZ_NULL if invalid type. */
struct KzuTexture* kzuTextureCastFromResource(const struct KzuResource* resource);

/** Gets the data type of a texture. */
enum KzuTextureDataType kzuTextureGetDataType(const struct KzuTexture* texture);

/** Gets the channels of a texture. */
enum KzuTextureChannels kzuTextureGetChannels(const struct KzuTexture* texture);

/** Gets the compression of a texture. */
enum KzuTextureCompression kzuTextureGetCompression(const struct KzuTexture* texture);

/** Checks if a texture has an alpha channel. */
kzBool kzuTextureHasAlphaChannel(const struct KzuTexture* texture);


/** Gets the width of a texture. */
kzUint kzuTextureGetWidth(const struct KzuTexture* texture);

/** Gets the height of a texture. */
kzUint kzuTextureGetHeight(const struct KzuTexture* texture);


/** Sets the filter of a texture. */
void kzuTextureSetFilter(struct KzuTexture* texture, enum KzuTextureFilter filter);

/** Gets the filter of a texture. */
enum KzuTextureFilter kzuTextureGetFilter(const struct KzuTexture* texture);

/** Sets the wrap mode of a texture. */
void kzuTextureSetWrap(struct KzuTexture* texture, enum KzuTextureWrap wrap);

/** Gets the wrap mode of a texture. */
enum KzuTextureWrap kzuTextureGetWrap(const struct KzuTexture* texture);

/**
 * Set maximum texture anisotropy.
 *
 * This specifies the amount of anisotropy to improve image quality on surfaces angled obliquely away from the
 * viewer. In this case, 1.0f would be the default, isotropic texture for cases where projection of pixel
 * filter footprint into texture space is square.
 * Values of 1.0f and smaller turn off the anisotropy completely (this is the default mode of operation).
 */
void kzuTextureSetAnisotropy(struct KzuTexture* texture, kzFloat anisotropy);

/** Get desired texture anisotropy. */
kzFloat kzuTextureGetAnisotropy(const struct KzuTexture* texture);

/** Returns true if the texture is deployed and valid. */
kzBool kzuTextureIsRenderable(const struct KzuTexture* texture);

/** Binds the texture for rendering. */
kzsError kzuTextureBind(struct KzuTexture* texture);

/** Unbinds the texture from rendering. */
kzsError kzuTextureUnbind(struct KzuTexture* texture);


KZ_HEADER_END


#endif
