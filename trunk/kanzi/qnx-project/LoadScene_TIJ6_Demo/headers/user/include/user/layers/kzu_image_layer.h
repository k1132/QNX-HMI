/**
* \file
* Image layer class.
* 
* KzuImageLayer is used to display a texture.
*
* Image Layer Messages
* ----
* KzuImageLayer does not send or receive any messages.
*
* Image Layer Properties
* ----
* ::KZU_PROPERTY_TYPE_IMAGE_LAYER_TEXTURE string property specifies a resource ID for the texture to display. The ::kzuImageLayerSetTexture
* function can be used to override the texture set by this property.
*
* Image Layer Example Code
* ----
* The following code shows one way of displaying a PNG image with Kanzi.
*
* \code {.c}
*     kzsError result;
*     struct KzcImage* image;
*     struct KzuImageTexture* texture;
*     struct KzuImageLayer* imageLayer;
*
*     result = kzcImageLoadFileFlipped(memoryManager, "testImage.png", &image);
*     kzsErrorForward(result);
*
*     result = kzuImageTextureCreateFromImage(resourceManager, "image name", image, KZU_TEXTURE_FILTER_BILINEAR,
*                                             KZU_TEXTURE_WRAP_CLAMP, 0.0f, &texture);
*     kzsErrorForward(result);
*
*     result = kzuImageLayerCreate(memoryManager, "image layer", uiDomain, &imageLayer);
*     kzsErrorForward(result);
*
*     result = kzuImageLayerSetTexture(imageLayer, kzuImageTextureToTexture(texture));
*     kzsErrorForward(result);
*
*     // Add imageLayer to a viewport such as the one returned by kzaApplicationGetRootLayer() to display the texture.
*     result = kzuObjectNodeAddChild(kzuLayerToObjectNode(rootLayer), kzuLayerToObjectNode(kzuImageLayerToLayer(imageLayer)));
*     kzsErrorForward(result);
*
*     // Do something else...
*
*     // Free texture and the image data.
*     result = kzuResourceRelease(kzuTextureToResource(kzuImageTextureToTexture(texture)));
*     kzsErrorForward(result);
*
*     // Destroy the image layer. 
*     result = kzuObjectNodeDelete(kzuLayerToObjectNode(kzuImageLayerToLayer(imageLayer)));
*     kzsErrorForward(result);
* \endcode
*
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_IMAGE_LAYER_H
#define KZU_IMAGE_LAYER_H


#include <user/scene_graph/kzu_object_base.h>

#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declaration. */
struct KzcImage;
struct KzcMemoryManager;
struct KzuFactory;
struct KzuImageLayer;
struct KzuLayer;
struct KzuMessageDispatcher;
struct KzuTexture;
struct KzuUIDomain;
struct KzuPropertyManager;


/** Object type for image layers. */
extern const KzuObjectType KZU_OBJECT_TYPE_IMAGE_LAYER;


/** Convert from layer to image layer. */
struct KzuImageLayer* kzuImageLayerFromLayer(const struct KzuLayer* layer);
/** Convert from image layer to layer. */
struct KzuLayer* kzuImageLayerToLayer(const struct KzuImageLayer* imageLayer);
/** Returns KZ_TRUE if the layer is an image layer.
  * \param layer The layer.
  * \return KZ_TRUE if the layer is an image layer, otherwise KZ_FALSE.
  */
kzBool kzuLayerIsImageLayer(const struct KzuLayer* layer);

/** Create an image layer.
 * \param memoryManager Memory manager to use.
 * \param name Name of the new image layer.
 * \param uiDomain The UI domain.
 * \param out_imageLayer A pointer that is set to point to the new image layer.
 * \return KZS_SUCCESS on success.
 */
kzsError kzuImageLayerCreate(const struct KzcMemoryManager* memoryManager, kzString name, struct KzuUIDomain* uiDomain,
                             struct KzuImageLayer** out_imageLayer);
/** Register image layer to the factory.
  * This is normally called from ::kzaApplicationCreate and needs to be done before calling any of the creation functions.
  * \param factory The factory to use.
  * \return KZS_SUCCESS on success.
  */
kzsError kzuImageLayerRegisterToFactory(const struct KzuFactory* factory);

/** Return the texture of an image layer.
 * \param layer The image layer.
 * \return The texture.
 */
struct KzuTexture* kzuImageLayerGetTexture(const struct KzuImageLayer* layer);

/** Set the texture for this image layer.
  * \param imageLayer The image layer.
  * \param texture The texture resource.
  * \return KZS_SUCCESS on success.
  */
kzsError kzuImageLayerSetTexture(struct KzuImageLayer* imageLayer, struct KzuTexture* texture);


KZ_HEADER_END


#endif
