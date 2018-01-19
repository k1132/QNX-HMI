/**
* \file
* Step rendering layer.
*
* Extension on viewport layer rendering, perform double-buffered rendering in steps, one render pass at a time.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_STEP_RENDERING_LAYER_H
#define KZU_STEP_RENDERING_LAYER_H


#include <user/scene_graph/kzu_object_base.h>


KZ_HEADER_BEGIN


/* Forward declaration. */
struct KzcMemoryManager;
struct KzuFactory;
struct KzuLayer;
struct KzuMessageDispatcher;
struct KzuObjectNode;
struct KzuUIDomain;
struct KzuPropertyManager;
struct KzuStepRenderingLayer;


/** Object type identifier for step rendering layers. */
extern const KzuObjectType KZU_OBJECT_TYPE_STEP_RENDERING_LAYER;


/** Convert layer to partial rendering layer layer. */
struct KzuStepRenderingLayer* kzuStepRenderingLayerFromLayer(const struct KzuLayer* layer);
/** Convert partial rendering layer to layer. */
struct KzuLayer* kzuStepRenderingLayerToLayer(const struct KzuStepRenderingLayer* stepRenderingLayer);
/** Tells if specified layer is partial rendering layer. */
kzBool kzuLayerIsStepRenderingLayer(const struct KzuLayer* layer);

/** Create an image layer. */
kzsError kzuStepRenderingLayerCreate(const struct KzcMemoryManager* memoryManager, kzString name, struct KzuUIDomain* uiDomain,
                                     struct KzuStepRenderingLayer** out_stepRenderingLayer);
/** Register partial rendering layer layer to the factory. */
kzsError kzuStepRenderingLayerRegisterToFactory(const struct KzuFactory* factory);

/** Tells if rendering queue of the layer is empty after the layer was rendered last time. */
kzBool kzuStepRenderingLayerIsRenderingQueueEmpty(const struct KzuStepRenderingLayer* stepRenderingLayer);

/** If set to TRUE, this flag will force layer to render all operations from current queue, flip the targets and finish rendering. */
void kzuStepRenderingLayerSetIsLastRenderingRound(struct KzuStepRenderingLayer* stepRenderingLayer, kzBool isLastRound);


KZ_HEADER_END


#endif
