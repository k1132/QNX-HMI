/**
* \file
* Specifies a render pass structure. Render pass specifies one stage of rendering with specified characteristics,
* defined by render pass properties (and filter). Sets of render passes are piped via composer.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_RENDER_PASS_H
#define KZU_RENDER_PASS_H


#include "kzu_composer_base.h"
#include "kzu_renderer_types.h"

#include <user/resource/kzu_resource_common.h>

#include <core/util/math/kzc_matrix4x4.h>
#include <core/util/color/kzc_color.h>

#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/** Composer type identifier for render pass. */
extern const KzuResourceType KZU_COMPOSER_TYPE_RENDER_PASS;


/** Default value for renderpass depth clear. */
#define KZU_RENDER_PASS_DEFAULT_DEPTH_CLEAR_VALUE 1.0f


/* Forward declarations */
struct KzcDynamicArray;
struct KzcFrameBuffer;
struct KzcHashMap;
struct KzcInputStream;
struct KzcMemoryManager;
struct KzcRenderer;
struct KzuBinaryFileInfo;
struct KzuCameraNode;
struct KzuComposer;
struct KzuFactory;
struct KzuLightNode;
struct KzuMaterial;
struct KzuObjectSource;
struct KzuUIDomain;
struct KzuPropertyType;
struct KzuRenderer;
struct KzuTransformedObjectNode;
struct KzuTransformedScene;


/**
 * \struct KzuRenderPass
 * Render pass passes set of objects to be rendered down to renderer. Rendering
 * attributes are selected from render pass properties, that includes view port, clear color,
 * depth & stencil buffer and other characteristics. Inherited from KzuComposer.
 */
struct KzuRenderPass;


/** Registers render pass to the factory. */
kzsError kzuRenderPassRegisterToFactory(const struct KzuFactory* factory);


/** Creates a render pass. */
kzsError kzuRenderPassCreate(const struct KzcMemoryManager* memoryManager, kzString name, struct KzuUIDomain* uiDomain,
                             struct KzuRenderPass** out_renderPass);

/** Check if a composer (by the requirement of render passes) requires a depth buffer to render correctly. */
void kzuComposerRequiresDepthBuffer(const struct KzuComposer* composer, kzBool* out_allowDepthClear, kzBool* out_requiresDepth);

/** Sets an object source for render pass. */
kzsError  kzuRenderPassSetObjectSource(struct KzuRenderPass* renderPass, struct KzuObjectSource* objectSource);
/** Gets object source from render pass. */
struct KzuObjectSource* kzuRenderPassGetObjectSource(const struct KzuRenderPass* renderPass);
/** Sets a color buffer for render pass. */
kzsError kzuRenderPassSetColorBuffer(const struct KzuRenderPass* renderPass, kzBool clearEnabled, struct KzcColorRGBA clearColor, 
                                     enum KzuColorWriteMode writeMode);


/** Sets color buffer clear enabled for render pass. */
kzsError kzuRenderPassSetColorBufferClearEnabled(const struct KzuRenderPass* renderPass, kzBool enabled);
/** Returns the current clear color. */
struct KzcColorRGBA kzuRenderPassGetClearColor(const struct KzuRenderPass* renderPass);
/** Returns the current clear color. */
enum KzuColorWriteMode kzuRenderPassGetColorWriteMode(const struct KzuRenderPass* renderPass);
/** Returns KZ_TRUE if color buffer clear is enabled. */
kzBool kzuRenderPassGetColorClearEnabled(const struct KzuRenderPass* renderPass);

/** Sets a depth buffer for render pass.
* \param renderPass renderPass to be applied.
* \param depthClearEnabled Is depth buffer cleared on beginning of this renderpass.
* \param clearValue clearValue clear value used if clearing enabled, use KZU_RENDER_PASS_DEFAULT_DEPTH_CLEAR_VALUE by default.
* \param depthTestEnabled Depth testing enabled / disabled.
* \param depthWriteEnabled Writing to depth buffer enabled / disabled.
*/
kzsError kzuRenderPassSetDepthBuffer(const struct KzuRenderPass* renderPass, kzBool depthClearEnabled, kzFloat clearValue,
                                     kzBool depthTestEnabled, kzBool depthWriteEnabled);
/** Sets a stencil buffer for render pass. */
kzsError kzuRenderPassSetStencilBuffer(const struct KzuRenderPass* renderPass, kzBool stencilClearEnabled, kzInt clearValue,
                                       kzBool stencilTestEnabled, enum KzuStencilOperation stencilModeSfail,
                                       enum KzuStencilOperation stencilModeDPfail, enum KzuStencilOperation stencilModeDPpass,
                                       enum KzuStencilFunction stencilFunction);
/** Sets a cull mode for render pass. */
kzsError kzuRenderPassSetCullMode(const struct KzuRenderPass* renderPass, enum KzuCullMode mode);


/** Sets the view port's size in absolute coordinates (pixels) */
void kzuRenderPassSetViewportAbsolute(struct KzuRenderPass* renderPass, kzUint x, kzUint y, kzUint width, kzUint height);
/** Sets the view port's size in coordinates relative to screen size (0.f = left, 1.f = right) (0.f = top, 1.f = bottom) */
void kzuRenderPassSetViewportRelative(struct KzuRenderPass* renderPass, kzFloat x, kzFloat y, kzFloat width, kzFloat height);


/** Sets render pass to state where it gets rendered once and is disabled after that. */
void kzuRenderPassSetRenderOnce(struct KzuRenderPass* renderPass, kzBool renderOnce);
/** Sets camera for render pass. */
kzsError kzuRenderPassSetCamera(const struct KzuRenderPass* renderPass, struct KzuCameraNode* cameraNode);

/** Sets frustum culling enabled / disabled. */
kzsError kzuRenderPassSetFrustumCulling(const struct KzuRenderPass* renderPass, kzBool enabled);


/** Sets stencil test enabled for render pass. */
kzsError kzuRenderPassSetStencilTestEnabled(const struct KzuRenderPass* renderPass, kzBool enabled);
/** Sets stencil fail operation for render pass. */
kzsError kzuRenderPassSetStencilFailOperation(const struct KzuRenderPass* renderPass, enum KzuStencilOperation stencilOp);
/** Sets stencil pass depth fail operation for render pass. */
kzsError kzuRenderPassSetStencilPassDepthFailOperation(const struct KzuRenderPass* renderPass, enum KzuStencilOperation stencilOp);
/** Sets stencil pass depth pass operation for render pass. */
kzsError kzuRenderPassSetStencilPassDepthPassOperation(const struct KzuRenderPass* renderPass, enum KzuStencilOperation stencilOp);
/** Sets stencil reference value for render pass. */
kzsError kzuRenderPassSetStencilReferenceValue(const struct KzuRenderPass* renderPass, kzInt stencilValue);
/** Sets stencil reference value for render pass. */
kzsError kzuRenderPassSetStencilMaskValue(const struct KzuRenderPass* renderPass, kzInt maskValue);
/** Returns if stencil test is enabled for render pass. */
kzBool kzuRenderPassIsStencilTestEnabled(const struct KzuRenderPass* renderPass);
/** Returns stencil fail operation from render pass. */
enum KzuStencilOperation kzuRenderPassGetStencilFailOperation(const struct KzuRenderPass* renderPass);
/** Returns stencil pass depth fail operation from render pass. */
enum KzuStencilOperation kzuRenderPassGetStencilPassDepthFailOperation(const struct KzuRenderPass* renderPass);
/** Returns stencil pass depth pass operation from render pass. */
enum KzuStencilOperation kzuRenderPassGetStencilPassDepthPassOperation(const struct KzuRenderPass* renderPass);
/** Gets stencil reference value from render pass. */
kzInt kzuRenderPassGetStencilReferenceValue(const struct KzuRenderPass* renderPass);
/** Gets stencil mask value from render pass. */
kzInt kzuRenderPassGetStencilMaskValue(const struct KzuRenderPass* renderPass);


/** Casts render pass to composer. */
struct KzuComposer* kzuRenderPassToComposer(const struct KzuRenderPass* renderPass);
/** Casts composer to render pass */
struct KzuRenderPass* kzuRenderPassFromComposer(const struct KzuComposer* composer);


KZ_HEADER_END


#endif
