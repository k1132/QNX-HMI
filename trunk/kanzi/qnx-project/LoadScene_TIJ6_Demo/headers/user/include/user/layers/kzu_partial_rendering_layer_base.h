/**
* \file
* Private layer data.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_PARTIAL_RENDERING_LAYER_BASE_H
#define KZU_PARTIAL_RENDERING_LAYER_BASE_H


#include <user/layers/kzu_viewport_layer_base.h>


KZ_HEADER_BEGIN


/** Partial rendering layer. */
struct KzuPartialRenderingLayer
{
    struct KzuViewportLayer viewportLayer; /**< Inherited from viewport layer. */ /*lint -esym(754, KzuPartialRenderingLayer::viewportLayer) Suppressed as this member is required but not referenced. */

    struct KzcVector2 previousActualSize; /**< Earlier actual size. */

    kzUint currentFrame;                  /**< Current frame. */
    kzBool onlyContentInvalid;            /**< Only content within invalid, not whole layer. */
};


/** Partial rendering layer class. */
extern const struct KzuLayerClass KZU_PARTIAL_RENDERING_LAYER_CLASS;


/** Render partial rendering debug visualizations. */
kzsError kzuPartialRenderingLayerRenderDebugVisualizations_protected(const struct KzuLayer* layer, struct KzuRenderer* renderer,
                                                                     const struct KzuRenderContextStack* renderContextStack);


KZ_HEADER_END


#endif
