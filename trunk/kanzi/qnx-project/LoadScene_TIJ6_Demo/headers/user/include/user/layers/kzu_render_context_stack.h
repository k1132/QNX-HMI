/**
* \file
* Render context stack used in layers and composers.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_RENDER_CONTEXT_STACK_H
#define KZU_RENDER_CONTEXT_STACK_H


#include <user/renderer/kzu_renderer_types.h>
#include <user/layers/kzu_layer.h>


KZ_HEADER_BEGIN


/* Forward declaration. */
struct KzuCanvas;
struct KzuRenderContextStack;
struct KzuRenderTarget;
struct KzuTexture;


/** Create a new render context stack.
*
* Should be done anew for each frame - use quick memory manager. */
kzsError kzuRenderContextStackCreate(const struct KzcMemoryManager* memoryManager, struct KzuRenderContextStack** out_renderContextStack);
/** Delete a render context stack.
*
* Note that if using a quick memory manager, this isn't even necessary. */
kzsError kzuRenderContextStackDelete(struct KzuRenderContextStack* renderContextStack);

/** Set the active canvas to be used by this render context stack. */
void kzuRenderContextStackSetActiveCanvas(struct KzuRenderContextStack* renderContextStack, const struct KzuCanvas* activeCanvas);
/** Get the active canvas used by this render context stack. */
const struct KzuCanvas* kzuRenderContextStackGetActiveCanvas(const struct KzuRenderContextStack* renderContextStack);
/** Set the debug composer to be used by this render context stack. */
void kzuRenderContextStackSetDebugComposer(struct KzuRenderContextStack* renderContextStack, struct KzuComposer* debugComposer);
/** Get the debug composer used by this render context stack. */
struct KzuComposer* kzuRenderContextStackGetDebugComposer(const struct KzuRenderContextStack* renderContextStack);
/** Get active screen width. */
kzUint kzuRenderContextStackGetActiveScreenWidth(const struct KzuRenderContextStack* renderContextStack);
/** Get active screen height. */
kzUint kzuRenderContextStackGetActiveScreenHeight(const struct KzuRenderContextStack* renderContextStack);

/** Push a framebuffer into the stack. */
kzsError kzuRenderContextStackPush(const struct KzuRenderContextStack* renderContextStack, struct KzuRenderTarget* renderTarget,
                                   struct KzcVector2 limits);
/** Peeks render context stack topmost element, containing render target and size. */
kzsError kzuRenderContextStackPeek(const struct KzuRenderContextStack* renderContextStack, struct KzuRenderTarget** out_renderTarget,
                                   struct KzcVector2* out_size);
/** Pop a framebuffer from the stack.
*
* If out_renderTarget is non-null, write the popped element into it. */
kzsError kzuRenderContextStackPop(const struct KzuRenderContextStack* renderContextStack, struct KzuRenderTarget** out_renderTarget);

/**
 * Apply the topmost render target for 2D rendering.
 * Shorthand for kzuRenderContextStackApplyPropertiesEffectively, should normally not be called in favor of it.
 */
kzsError kzuRenderContextStackApply(const struct KzuRenderContextStack* renderContextStack, struct KzuRenderer* renderer,
                                    kzBool enableDepth);
/** Applies properties effectively. */
kzsError kzuRenderContextStackApplyPropertiesEffectively(struct KzuRenderer* renderer, struct KzuRenderTarget* frameBufferTexture,
                                                         const struct KzcVector2* limits, kzBool enableDepth);
/** Detaches the render target from render context stack. */
kzsError kzuRenderContextStackDetach(const struct KzuRenderContextStack* renderContextStack, struct KzuRenderer* renderer);

/** Applies the composer with render context stack. */
kzsError kzuRenderContextStackComposerApply(const struct KzuRenderContextStack* renderContextStack, struct KzuRenderer* renderer,
                                            struct KzuComposer* composer);
/** Restores the composer from render context stack. */
kzsError kzuRenderContextStackComposerRestore(const struct KzuRenderContextStack* renderContextStack, struct KzuRenderer* renderer,
                                              const struct KzuComposer* composer);
/** Applies the viewport layer for the stack. */
kzsError kzuRenderContextStackViewportApply(const struct KzuRenderContextStack* renderContextStack, kzFloat viewportX,
                                            kzFloat viewportY, kzFloat viewportWidth, kzFloat viewportHeight,
                                            kzBool scissorEnabled, kzFloat scissorX, kzFloat scissorY, kzFloat scissorWidth,
                                            kzFloat scissorHeight);

/** Downsamples source texture to target texture. */
kzsError kzuRenderContextStackDownsample(const struct KzuTexture* sourceTexture, struct KzuRenderTarget* renderTarget, struct KzuRenderer* renderer);

/** Sets viewport for topmost render context stack. */
kzsError kzuRenderContextStackSetViewport(const struct KzuRenderContextStack* renderContextStack, const struct KzcVector4* viewport);
/** Gets viewport from render context stack. */
kzsError kzuRenderContextStackGetViewport(const struct KzuRenderContextStack* renderContextStack, struct KzcVector4* out_viewport);
/** Gets rendering viewport from render context stack. Can vary from context stack size for example if stereoscopic rendering has been enabled. */
kzsError kzuRenderContextStackGetRenderingViewport(const struct KzuRenderContextStack* renderContextStack, const struct KzuRenderer* renderer, struct KzcVector4* out_viewport);
/** Gets scissor from render context stack. */
kzsError kzuRenderContextStackGetScissor(const struct KzuRenderContextStack* renderContextStack, kzBool* out_enabled, struct KzcVector4* out_scissor);
/** Get render context stack current texture. */
kzsError kzuRenderContextStackGetTexture(const struct KzuRenderContextStack* renderContextStack, struct KzuRenderTarget** out_renderTarget);
/** Get render context stack current size. */
kzsError kzuRenderContextStackGetSize(const struct KzuRenderContextStack* renderContextStack, struct KzcVector2* out_size);


KZ_HEADER_END


#endif
