/**
* \file
* Image component. Handles loading and saving images.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZC_IMAGE_H
#define KZC_IMAGE_H


#include "kzc_etc.h"

#include <system/kzs_types.h>
#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declaration structures. */
struct KzcInputStream;
struct KzcOutputStream;
struct KzcMemoryManager;


/** List of data formats image may have. */
enum KzcImageDataFormat
{
    KZC_IMAGE_DATA_FORMAT_INVALID, /**< Invalid data format. */
    KZC_IMAGE_DATA_FORMAT_RGB_565, /**< RGB565 format. */
    KZC_IMAGE_DATA_FORMAT_RGB_888, /**< RGB 8 bit format. */
    KZC_IMAGE_DATA_FORMAT_RGBA_8888, /**< RGBA 8 bit format. */
    KZC_IMAGE_DATA_FORMAT_RGB_FLOAT, /**< RGB float format. */
    KZC_IMAGE_DATA_FORMAT_RGBA_FLOAT, /**< RGBA float format. */
    KZC_IMAGE_DATA_FORMAT_RGB_FLOAT16, /**< RGB half float format. */
    KZC_IMAGE_DATA_FORMAT_RGBA_FLOAT16, /**< RGBA half float format. */
    KZC_IMAGE_DATA_FORMAT_ALPHA_8, /**< Alpha 8 bit image. */
    KZC_IMAGE_DATA_FORMAT_ALPHA_FLOAT, /**< Alpha float image. */
    KZC_IMAGE_DATA_FORMAT_GRAYSCALE_8, /**< Grayscale 8 bit image. */
    KZC_IMAGE_DATA_FORMAT_GRAYSCALE_FLOAT, /**< Grayscale float image. */
    KZC_IMAGE_DATA_FORMAT_GRAYSCALE_ALPHA_8, /**< Grayscale alpha 8 bit image. */
    KZC_IMAGE_DATA_FORMAT_ETC, /**< Ericsson texture compressed image. */
    KZC_IMAGE_DATA_FORMAT_DXT3, /**< DXT3 compressed image. */
    KZC_IMAGE_DATA_FORMAT_DXT5, /**< DXT5 compressed image. */
    KZC_IMAGE_DATA_FORMAT_ATC, /**< ATC compressed image. */
    KZC_IMAGE_DATA_FORMAT_ATC_EXPLICIT_ALPHA, /**< ATC compressed image with explicit alpha. */
    KZC_IMAGE_DATA_FORMAT_ATC_INTERPOLATED_ALPHA, /**< ATC compressed image with interpolated alpha. */
    KZC_IMAGE_DATA_FORMAT_PVRTC1_RGB_4BPP, /**< RGB PVRTC1 4 bits per pixel compressed image. */
    KZC_IMAGE_DATA_FORMAT_PVRTC1_RGBA_4BPP, /**< RBGA PVRTC1 4 bits per pixel compressed image. */
    KZC_IMAGE_DATA_FORMAT_PVRTC1_RGB_2BPP, /**< RGB PVRTC1 2 bits per pixel compressed image. */
    KZC_IMAGE_DATA_FORMAT_PVRTC1_RGBA_2BPP, /**< RGBA PVRTC1 2 bits per pixel compressed image. */
    KZC_IMAGE_DATA_FORMAT_PVRTC2_RGBA_4BPP,  /**< RGBA PVRTC2 4 bits per pixel compressed image. */
    KZC_IMAGE_DATA_FORMAT_PVRTC2_RGBA_2BPP  /**< RGBA PVRTC2 2 bits per pixel compressed image. */
};

/** List of possible resizing filters. */
enum KzcImageResizeFilter
{
    KZC_IMAGE_RESIZE_FILTER_NEAREST_NEIGHBOR,   /**< Nearest neighbor filter. */
    KZC_IMAGE_RESIZE_FILTER_BILINEAR,           /**< Bilinear filter. */
    KZC_IMAGE_RESIZE_FILTER_WEIGHTED_AVERAGE    /**< Weighted average filter. */
};


/**
* \struct KzcImage
* Structure for image utility.
*/
struct KzcImage;


/** Function type definition for function that can load an image reference from .KZB input stream. */
typedef kzsError (*KzuImageLoadImageCallback)(struct KzcInputStream* inputStream, void* userData, struct KzcImage** out_image);


/** Creates an image with no data. */
kzsError kzcImageCreate(const struct KzcMemoryManager* memoryManager, struct KzcImage** out_image);
/**
 * Loads image from PNG file. Color format is output in either RGB8 or RGBA8.
 * The image is optionally flipped on load (to conform with OpenGL default texture coordinates).
 */
kzsException kzcImageLoadPNG(const struct KzcMemoryManager* memoryManager, struct KzcInputStream* inputStream,
                             kzBool flipInternally, struct KzcImage** out_image);
/**
 * Loads image from JPEG file. Color format is output in RGB8.
 * The image is optionally flipped on load (to conform with OpenGL default texture coordinates).
 */
kzsException kzcImageLoadJPEG(const struct KzcMemoryManager* memoryManager, struct KzcInputStream* inputStream,
                              kzBool flipInternally, struct KzcImage** out_image);
/**
 * Loads image from RAW format. Width, height and format needs to be specified manually. Throws error if dimension and format mismatches the RAW file size.
 * The image is optionally flipped on load (to conform with OpenGL default texture coordinates).
 */
kzsError kzcImageLoadRAW(const struct KzcMemoryManager* memoryManager, struct KzcInputStream* inputStream,
                         kzBool flipInternally, kzUint width, kzUint height, enum KzcImageDataFormat colorFormat,
                         struct KzcImage** out_image);
/** Loads image from memory. Data is copied. */
kzsError kzcImageLoadMemory(const struct KzcMemoryManager* memoryManager, kzUint width, kzUint height,
                            enum KzcImageDataFormat colorFormat, const void* data, struct KzcImage** out_image);
/** Creates image from data, data not copied. */
kzsError kzcImageLoadMemoryAssignData(const struct KzcMemoryManager* memoryManager, kzUint width, kzUint height,
                                      enum KzcImageDataFormat colorFormat, void* data, struct KzcImage** out_image);
/** Loads image from resource. PNG and JPEG are supported. If the image will be used as a 2D texture, consider using kzcImageLoadResourceFlipped instead. */
kzsException kzcImageLoadResource(const struct KzcMemoryManager* memoryManager, kzString resourcePath, struct KzcImage** out_image);
/** Loads image from file. PNG and JPEG are supported. If the image will be used as a 2D texture, consider using kzcImageLoadFileFlipped instead. */
kzsException kzcImageLoadFile(const struct KzcMemoryManager* memoryManager, kzString filePath, struct KzcImage** out_image);
/**
 * Loads image from resource. PNG and JPEG are supported. This function flips the image data vertically while loading
 * to make it compatible with OpenGL 2D textures. If this function is used instead of kzcImageLoadResource, deploying the image
 * to a 2D texture will be faster and use less memory.
 */
kzsException kzcImageLoadResourceFlipped(const struct KzcMemoryManager* memoryManager, kzString resourcePath, struct KzcImage** out_image);
/**
 * Loads image from file. PNG and JPEG are supported. This function flips the image data vertically while loading
 * to make it compatible with OpenGL 2D textures. If this function is used instead of kzcImageLoadFile, deploying the image
 * to a 2D texture will be faster and use less memory.
 */
kzsException kzcImageLoadFileFlipped(const struct KzcMemoryManager* memoryManager, kzString filePath, struct KzcImage** out_image);

/** Creates mipmap image out of list of mipmap images. */
kzsError kzcImageCreateMipmapImage(const struct KzcMemoryManager* memoryManager, kzUint levelCount, struct KzcImage* const* mipmapImages,
                                   struct KzcImage** out_image);


/** Deletes image. */
kzsError kzcImageDelete(struct KzcImage* image);

/** Loads PNG image from KZB. */
kzsException kzcImageLoadPNGFromKZB(struct KzcImage* image, struct KzcInputStream* inputStream, kzBool flipInternally);
/** Loads JPEG image from KZB. */
kzsError kzcImageLoadJPEGFromKZB(struct KzcImage* image, struct KzcInputStream* inputStream, kzBool flipInternally);
/** Loads ETC image from KZB. */
kzsError kzcImageLoadETCFromKZB(struct KzcImage* image, struct KzcInputStream* inputStream, kzBool flippedInternally);
/** Loads DXT image from KZB. */
kzsError kzcImageLoadDXTFromKZB(struct KzcImage* image, struct KzcInputStream* inputStream, kzBool flippedInternally);
/** Loads ATC compressed image from KZB. */
kzsError kzcImageLoadATCFromKZB(struct KzcImage* image, struct KzcInputStream* inputStream, kzBool flippedInternally);
/** Loads PVRTC compressed image from KZB. */
kzsError kzcImageLoadPVRTCFromKZB(struct KzcImage* image, struct KzcInputStream* inputStream, kzBool flippedInternally);
/** Loads RAW 2D image from KZB. */
kzsError kzcImageLoadRaw2DFromKZB(struct KzcImage* image, struct KzcInputStream* inputStream, kzBool flipInternally);


/** 
* Copies data from sourceImage to targetImage. 
* Data is copied from sourceImage area [sourceRectX, sourceRectY, sourceRectX + width, sourceRectY + height]
* to targetImage area [targetRectX, targetRectY, targetRectX + width, targetRectY + height]
* Error is returned if area is out of bounds of image.
*/
kzsError kzcImageCopySubImage(const struct KzcImage* targetImage, const struct KzcImage* sourceImage, 
                              kzUint targetRectX, kzUint targetRectY, kzUint sourceRectX, kzUint sourceRectY, 
                              kzUint width, kzUint height);
/** 
* Copies sourceImage data to targetImage. 
*/
kzsError kzcImageCopySubImageData(const struct KzcImage* targetImage, void* sourceData, 
                                  kzUint targetRectX, kzUint targetRectY, kzUint sourceRectX, kzUint sourceRectY,
                                  kzUint sourceImageWidth, kzUint width, kzUint height);

/**
* Saves an image to an output stream in the PNG format.
* The only supported image formats are KZC_IMAGE_DATA_FORMAT_RGB_888 and KZC_IMAGE_DATA_FORMAT_RGBA_8888.
* Output stream must be closed manually.
*/
kzsError kzcImageSavePNG(const struct KzcImage* image, struct KzcOutputStream* outputStream);
/** Saves an image to an output stream in the JPEG format. Output stream must be closed manually. Quality within range [0,1]*/
kzsError kzcImageSaveJPEG(const struct KzcImage* image, struct KzcOutputStream* outputStream, kzFloat quality);
/** Saves raw image to specific output stream. Output image will be in raw byte format. */
kzsError kzcImageSaveRAW(const struct KzcImage* image, struct KzcOutputStream* outputStream);


/** Returns image width. */
kzUint kzcImageGetWidth(const struct KzcImage* image);
/** Returns image height. */
kzUint kzcImageGetHeight(const struct KzcImage* image);

/** Sets a flag to indicate that the data in the image is vertically flipped. */
void kzcImageSetFlippedInternally(struct KzcImage* image, kzBool flipped);
/** Returns the flag which indicates if the data in the image is vertically flipped or not. */
kzBool kzcImageIsFlippedInternally(const struct KzcImage* image);

/** Sets a flag to indicate that the RGB data in the image has premultiplied alpha. */
void kzcImageSetPremultipliedAlpha(struct KzcImage* image, kzBool premultipliedAlpha);
/** Returns the flag which indicates if the RGB data in the image has premultiplied alpha. */
kzBool kzcImageIsPremultipliedAlpha(const struct KzcImage* image);

/** Returns color format from image. */
enum KzcImageDataFormat kzcImageGetDataFormat(const struct KzcImage* image);
/** Returns image data from image. */
void* kzcImageGetData(const struct KzcImage* image);
/** Returns the size of the image data from image. */
kzUint kzcImageGetDataSize(const struct KzcImage* image);
/** Gets bytes per pixel from data format. */
kzUint kzcImageGetBytesPerPixelFromFormat(enum KzcImageDataFormat dataFormat);
/** Gets mipmap level count from image. */
kzUint kzcImageGetMipmapLevelCount(const struct KzcImage* image);
/** Gets mipmap level from image. */
struct KzcImage* kzcImageGetMipmapLevel(const struct KzcImage* image, kzUint mipmapLevelIndex);
/** Returns if this image is mipmap image. */
kzBool kzcImageIsMipmapImage(const struct KzcImage* image);


/** Copy operator for image. */
kzsError kzcImageCopy(const struct KzcMemoryManager* memoryManager, const struct KzcImage* sourceImage, struct KzcImage** out_targetImage);
/** Converts an image to the specified image data format.
* \param sourceImage The image to convert.
* \param colorFormat The image data format to convert to. Compressed formats are not supported.
* \return KZS_SUCCESS on success.
*/
kzsException kzcImageConvert(struct KzcImage* sourceImage, enum KzcImageDataFormat colorFormat);


/**
 * Converts an image to the ETC compressed format.
 * \param sourceImage The image to convert.
 * \param[in] compressionMode mode to use for compression. See kzc_etc.h for possible values.
 * \return KZS_SUCCESS on success.
 */
kzsError kzcImageConvertToETC(struct KzcImage* sourceImage, enum KzcEtcCompressionMode compressionMode);


/** Sets name for the image. */
kzsError kzcImageSetName(struct KzcImage* image, kzString name);
/** Gets name of the image. KZ_NULL if not assigned. */
kzString kzcImageGetName(const struct KzcImage* image);


/** Blit an image into another. The images must have the same format.
* Only the image data format KZC_IMAGE_DATA_FORMAT_RGBA_8888 is supported.
* \param destination The image to write to.
* \param source The image to read from.
* \param sourceOffsetX X offset to the source.
* \param sourceOffsetY Y offset to the source.
* \param destOffsetX X offset to the destination.
* \param destOffsetY Y offset to the destination.
* \param width The width (in pixels) to blit.
* \param height The height (in pixels) to blit.
* \return KZS_SUCCESS on success.
*/
kzsException kzcImageBlit(const struct KzcImage* destination, const struct KzcImage* source, kzUint sourceOffsetX, kzUint sourceOffsetY,
                          kzUint destOffsetX, kzUint destOffsetY, kzUint width, kzUint height);
/** Resizes image by specified parameters.
* If the image is a mipmap image, all the mipmap levels are lost.
*/
kzsError kzcImageResize(struct KzcImage* image, kzUint newWidth, kzUint newHeight, enum KzcImageResizeFilter resizeFilter);
/** Crops image by using (x, y, width, height) area. */
kzsError kzcImageCrop(struct KzcImage* image, kzUint x, kzUint y, kzUint width, kzUint height);
/** Flips image horizontally. */
kzsError kzcImageFlipHorizontally(const struct KzcImage* image);
/** Flips image vertically. */
kzsError kzcImageFlipVertically(const struct KzcImage* image);

/** Pre-multiplies the RGB data of the image with the alpha component. */
kzsError kzcImagePremultiplyAlpha(const struct KzcImage* image);


/** Creates mipmap levels for the given image. */
kzsError kzcImageCreateMipmapLevels(struct KzcImage* image);

/** Assigns mipmap levels for the given images. */
kzsError kzcImageAssignMipmapLevels(struct KzcImage* image, kzUint levelCount, struct KzcImage* const* mipmapImages);

/** Creates mipmap images from source image and returns them. */
kzsError kzcImageCreateMipmapImages(const struct KzcMemoryManager* memoryManager, const struct KzcImage* image, struct KzcImage*** out_mipmapImages);


/** Returns is image is in compressed format. */
kzBool kzcImageIsCompressedFormat(const struct KzcImage* image);
/** Returns if image data format is in compressed format. */
kzBool kzcImageIsDataFormatCompressed(enum KzcImageDataFormat dataFormat);


KZ_HEADER_END


#endif
