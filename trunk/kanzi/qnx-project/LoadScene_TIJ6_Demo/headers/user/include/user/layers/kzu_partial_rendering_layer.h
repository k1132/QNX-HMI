/**
* \file
* Partial rendering layer.
*
* Extension on viewport layer rendering.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_PARTIAL_RENDERING_LAYER_H
#define KZU_PARTIAL_RENDERING_LAYER_H


#include <user/scene_graph/kzu_object_base.h>


KZ_HEADER_BEGIN


/* Forward declaration. */
struct KzcMemoryManager;
struct KzuPartialRenderingLayer;
struct KzuFactory;
struct KzuLayer;
struct KzuMessageDispatcher;
struct KzuUIDomain;
struct KzuPropertyManager;


/** Partial rendering debug visualizations. */
enum KzuPartialRenderingDebugVisualization
{
    KZU_PARTIAL_RENDERING_DEBUG_VISUALIZATION_NONE = 0,
    KZU_PARTIAL_RENDERING_DEBUG_VISUALIZATION_STENCILS = 1,
    KZU_PARTIAL_RENDERING_DEBUG_VISUALIZATION_COLOR_BUFFER_CHANGES
};


/** Object type identifier for partial rendering layers. */
extern const KzuObjectType KZU_OBJECT_TYPE_PARTIAL_RENDERING_LAYER;


/** Convert layer to partial rendering layer layer. */
struct KzuPartialRenderingLayer* kzuPartialRenderingLayerFromLayer(const struct KzuLayer* layer);
/** Convert partial rendering layer to layer. */
struct KzuLayer* kzuPartialRenderingLayerToLayer(const struct KzuPartialRenderingLayer* partialRenderingLayer);
/** Tells if specified layer is partial rendering layer. */
kzBool kzuLayerIsPartialRenderingLayer(const struct KzuLayer* layer);

/** Create a partial rendering layer. */
kzsError kzuPartialRenderingLayerCreate(const struct KzcMemoryManager* memoryManager, kzString name, struct KzuUIDomain* uiDomain,
                                        struct KzuPartialRenderingLayer** out_partialRenderingLayer);
/** Register partial rendering layer to the factory. */
kzsError kzuPartialRenderingLayerRegisterToFactory(const struct KzuFactory* factory);

/** Invalidate all current partial rendering data and start over. */
kzsError kzuPartialRenderingLayerRefresh(struct KzuPartialRenderingLayer* partialRenderingLayer);

/** Turn on 'only content changed -flag.
 * 
 * If this flag is on, the PR layer knows the whole layer content does not need rendering, and it's enough to only
 * stencil the objects within the viewport.
 *
 * Flagged on extract, if the layer itself was not flagged for rendering when extracting the scene.
 *
 * \param partialLayer Partial rendering layer to flag.
 */
void kzuPartialRenderingLayerSetContentOnly(struct KzuPartialRenderingLayer* partialLayer);


KZ_HEADER_END


#endif
