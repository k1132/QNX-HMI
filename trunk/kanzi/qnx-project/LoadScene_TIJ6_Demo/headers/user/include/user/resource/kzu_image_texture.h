/**
 * \file
 * 2D image texture.
 * 
 * Copyright 2008-2014 by Rightware. All rights reserved.
 */
#ifndef KZU_IMAGE_TEXTURE_H
#define KZU_IMAGE_TEXTURE_H


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
 * \struct KzuImageTexture
 * 2D Image texture.
 */
struct KzuImageTexture;


/** Resource type identifier for 2D image texture. */
extern const KzuResourceType KZU_RESOURCE_TYPE_IMAGE_TEXTURE;


/** Creates a 2D image texture that loads the data when needed using the given resource loader.
 * The new image texture starts with reference count of one, use ::kzuResourceRelease to free the resource.
 * \param resourceManager The resource manager to use.
 * \param name Name of the new image texture.
 * \param loader Resource loader to use for loading the resource.
 * \param out_imageTexture A pointer that is set to point to the new image texture.
 */
kzsError kzuImageTextureCreate(const struct KzuResourceManager* resourceManager, kzString name, struct KzuResourceLoader* loader,
                               struct KzuImageTexture** out_imageTexture);

/** Registers image texture type to the factory.
 * This is normally called from ::kzaApplicationCreate and needs to be done before calling any of the creation functions.
 * \param factory The factory to use.
 */
kzsError kzuImageTextureRegisterToFactory(const struct KzuFactory* factory);

/**
 * Creates a 2D image texture from the given image. The created texture takes ownership of the image.
 * If this is not desired, use kzcImageCopy to create a copy of the image before passing it to the texture.
 *
 * @param resourceManager The resource manager to use.
 * @param name Name of the new image texture.
 * @param image The image (data) to use in the texture. The created texture takes ownership of the image.
 * @param filter Texture filter to use. See ::KzuTextureFilter.
 * @param wrap Texture wrapping mode to use. See ::KzuTextureWrap.
 * @param anisotropy Set anisotropic filtering level of texture. Values <= 1.0f disable the feature.
 * @param out_imageTexture A pointer that is set to point to the new image texture.
 */
kzsError kzuImageTextureCreateFromImage(const struct KzuResourceManager* resourceManager, kzString name, const struct KzcImage* image,
                                        enum KzuTextureFilter filter, enum KzuTextureWrap wrap, kzFloat anisotropy,
                                        struct KzuImageTexture** out_imageTexture);

/**
 * Creates a 2D image texture from a byte array.
 *
 * @param resourceManager The resource manager to use.
 * @param name Name of the new image texture.
 * @param channels The channels contained in the data. See ::KzuTextureChannels.
 * @param width The width of the image.
 * @param height The height of the image.
 * @param data Pointer to the byte array of channel_count * width * height bytes.
 * @param filter Texture filter to use. See ::KzuTextureFilter.
 * @param wrap Texture wrapping mode to use. See ::KzuTextureWrap.
 * @param anisotropy Set anisotropic filtering level of texture. Values <= 1.0f disable the feature.
 * @param out_imageTexture A pointer that is set to point to the new image texture.
 */
kzsError kzuImageTextureCreateFromMemory(const struct KzuResourceManager* resourceManager, kzString name, enum KzuTextureChannels channels,
                                         kzUint width, kzUint height, const kzByte* data, enum KzuTextureFilter filter,
                                         enum KzuTextureWrap wrap, kzFloat anisotropy, struct KzuImageTexture** out_imageTexture);

/**
 * Initializes a 2D image texture from an image with the given arguments. The texture takes ownership of the image.
 *
 * \see kzuImageTextureCreate for creating the 2D image texture.
 *
 * @param imageTexture An image texture previously created with e.g. ::kzuImageTextureCreate.
 * @param image The image (data) to use in the texture. The texture takes ownership of the image.
 * @param filter Texture filter to use. See ::KzuTextureFilter.
 * @param wrap Texture wrapping mode to use. See ::KzuTextureWrap.
 * @param anisotropy Set anisotropic filtering level of texture. Values <= 1.0f disable the feature.
 */
kzsError kzuImageTextureInitializeFromImage(struct KzuImageTexture* imageTexture, const struct KzcImage* image,
                                            enum KzuTextureFilter filter, enum KzuTextureWrap wrap, kzFloat anisotropy);
/**
 * Initializes a 2D image texture from memory with the given arguments.
 *
 * \see kzuImageTextureCreate for creating the 2D image texture.
 *
 * @param imageTexture An image texture previously created with e.g. ::kzuImageTextureCreate.
 * @param channels The channels contained in the data. See ::KzuTextureChannels.
 * @param width The width of the image.
 * @param height The height of the image.
 * @param data Pointer to the byte array of channel_count * width * height bytes.
 * @param filter Texture filter to use. See ::KzuTextureFilter.
 * @param wrap Texture wrapping mode to use. See ::KzuTextureWrap.
 * @param anisotropy Set anisotropic filtering level of texture. Values <= 1.0f disable the feature.
 */
kzsError kzuImageTextureInitializeFromMemory(struct KzuImageTexture* imageTexture, enum KzuTextureChannels channels,
                                             kzUint width, kzUint height, const kzByte* data, enum KzuTextureFilter filter,
                                             enum KzuTextureWrap wrap, kzFloat anisotropy);


/** Converts 2D image texture to texture. */
struct KzuTexture* kzuImageTextureToTexture(const struct KzuImageTexture* imageTexture);
/** Converts texture to 2D image texture. */
struct KzuImageTexture* kzuImageTextureFromTexture(const struct KzuTexture* texture);
/** Converts 2D image texture to GPU resource. */
struct KzuGPUResource* kzuImageTextureToGPUResource(const struct KzuImageTexture* imageTexture);
/** Converts GPU resource to 2D image texture. */
struct KzuImageTexture* kzuImageTextureFromGPUResource(const struct KzuGPUResource* gpuResource);
/** Converts 2D image texture to resource. */
struct KzuResource* kzuImageTextureToResource(const struct KzuImageTexture* imageTexture);
/** Converts resource to 2D image texture. */
struct KzuImageTexture* kzuImageTextureFromResource(const struct KzuResource* resource);


/** Gets the image data of a 2D image texture. Returns the base mipmap level only. */
void* kzuImageTextureGetData(const struct KzuImageTexture* imageTexture);

/** Updates a part of the image texture's data. Updates the base mipmap level only. Not effective on compressed textures.
 * @param imageTexture An image texture previously created with e.g. ::kzuImageTextureCreate.
 * @param data Pointer to the byte array of channel_count * width * height bytes.
 * @param x The x-coordinate of the part to update.
 * @param y The y-coordinate of the part to update.
 * @param width Width of the part to update.
 * @param height Height of the part to update.
 */
kzsError kzuImageTextureUpdateSubData(const struct KzuImageTexture* imageTexture, const kzByte* data,
                                      kzUint x, kzUint y, kzUint width, kzUint height);


KZ_HEADER_END


#endif
