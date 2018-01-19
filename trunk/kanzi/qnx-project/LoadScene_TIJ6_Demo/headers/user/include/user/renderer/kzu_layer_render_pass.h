/**
* \file
* Specifies a layer render pass. Layer render pass is used to render layers, rendering individual scenes still uses their
* individual render passes.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_LAYER_RENDER_PASS_H
#define KZU_LAYER_RENDER_PASS_H


#include "kzu_composer_base.h"

#include <user/resource/kzu_resource_common.h>

#include <core/util/math/kzc_vector2.h>

#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/** Composer type identifier for layer render pass. */
extern const KzuResourceType KZU_COMPOSER_TYPE_LAYER_RENDER_PASS;

/** Composer class for layer render pass. */
extern const struct KzuComposerClass KZU_COMPOSER_LAYER_RENDER_PASS_CLASS;


/* Forward declaration structures */
struct KzcMemoryManager;
struct KzuCanvas;
struct KzuRenderContextStack;
struct KzuPropertyManager;
struct KzuUIDomain;
struct KzuTransformedObjectNode;

/**
 * \struct KzuLayerRenderPass
 * Layer render pass.
 */
struct KzuLayerRenderPass;


/** Creates a layer render pass. */
kzsError kzuLayerRenderPassCreate(const struct KzuUIDomain* uiDomain, kzString name, struct KzuLayerRenderPass** out_layerRenderPass);
/** Deletes layer render pass. */
kzsError kzuLayerRenderPassDelete(struct KzuComposer* layerRenderPassComposer);


/** Cast into layer render pass from composer. */
struct KzuLayerRenderPass* kzuLayerRenderPassFromComposer(const struct KzuComposer* composer);
/** Cast layer render pass into composer. */
struct KzuComposer* kzuLayerRenderPassToComposer(const struct KzuLayerRenderPass* layerRenderPass);


/** Set layer rendering area. */
void kzuLayerRenderPassSetRenderingArea(struct KzuLayerRenderPass* layerRenderPass, kzFloat offsetX, kzFloat offsetY, kzFloat sizeX,
                                        kzFloat sizeY, const struct KzuCanvas* canvas);
/** Get debug composer. */
struct KzuComposer* kzuLayerRenderPassGetDebugComposer(const struct KzuLayerRenderPass* layerRenderPass);
/** Set debug composer. Layer render pass will not own the debug composer. */
void kzuLayerRenderPassSetDebugComposer(struct KzuLayerRenderPass* layerRenderPass, struct KzuComposer* debugComposer);
/** Get layer rendering limits. */
struct KzcVector2 kzuLayerRenderPassGetLimits(const struct KzuLayerRenderPass* layerRenderPass);
/** Get layer rendering offset. */
struct KzcVector2 kzuLayerRenderPassGetOffset(const struct KzuLayerRenderPass* layerRenderPass);

/** Applies a render pass for rendering. */
kzsError kzuLayerRenderPassApply(struct KzuComposer* layerRenderPassComposer, struct KzuRenderer* renderer, const struct KzuTransformedScene* transformedScene,
                                 struct KzuRenderContextStack* renderContextStack);


KZ_HEADER_END


#endif
