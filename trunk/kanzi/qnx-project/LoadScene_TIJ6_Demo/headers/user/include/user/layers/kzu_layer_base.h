/**
* \file
* Private layer data.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_LAYER_BASE_H
#define KZU_LAYER_BASE_H


#include <user/layers/kzu_layer.h>
#include <user/scene_graph/kzu_object_base.h>
#include <user/scene_graph/bounding_volume/kzu_bounding_volume.h>

#include <core/util/math/kzc_rectangle.h>


KZ_HEADER_BEGIN


/** Index of final render target among layer render targets. */
#define KZU_LAYER_RENDER_TARGET_FINAL 0
/** Index of cache self render target among layer render targets. */
#define KZU_LAYER_RENDER_TARGET_CACHE_SELF 1
/** Index of cache children render target among layer render targets. */
#define KZU_LAYER_RENDER_TARGET_CACHE_CHILDREN 2

/** Layer rendering mask - center area. */
#define KZU_LAYER_CLIPPING_RESULT_CENTER (1 << 0)
/** Layer rendering mask - bottom part. */
#define KZU_LAYER_CLIPPING_RESULT_BOTTOM (1 << 1)
/** Layer rendering mask - left part. */
#define KZU_LAYER_CLIPPING_RESULT_LEFT (1 << 2)
/** Layer rendering mask - right part. */
#define KZU_LAYER_CLIPPING_RESULT_RIGHT (1 << 3)
/** Layer rendering mask - top part. */
#define KZU_LAYER_CLIPPING_RESULT_TOP (1 << 4)
/** Layer clipping result - outside areas. */
#define KZU_LAYER_CLIPPING_RESULT_OUTSIDE (2 + 4 + 8 + 16)


/* Forward declarations */
struct KzuMessage;
struct KzuUIDomain;


/** Layer node's object node class. */
extern const struct KzuObjectNodeClass KZU_LAYER_CLASS;


/** Function pointer for specifying layer occlusion mask rendering for intersecting background layer. */
typedef kzsError (*KzuLayerOcclusionMaskFunction)(const struct KzuLayer* sourceLayer, struct KzuLayer* maskLayer, struct KzuRenderer* renderer, struct KzuRenderContextStack* renderContextStack);


/** Layer rendering type. */
enum KzuLayerRenderType
{
    KZU_LAYER_RENDER_TYPE_PROVIDE_NONE,    /**< Will not render itself except for its children. */
    KZU_LAYER_RENDER_TYPE_PROVIDE_TEXTURE, /**< Layer will provide texture(d material). */
    KZU_LAYER_RENDER_TYPE_PROVIDE_VIEWPORT /**< Never clear composing target. */
};

/** Layer rendering restrictions. */
enum KzuLayerRenderingRestrictions
{
    KZU_LAYER_RENDERING_RESTRICTIONS_NONE,
    KZU_LAYER_RENDERING_RESTRICTIONS_ONLY_RENDER_CONTENT,
    KZU_LAYER_RENDERING_RESTRICTIONS_ONLY_BLIT_CONTENT
};

/** Layer render target override. */
enum KzuLayerRenderTargetOverride
{
    KZU_LAYER_RENDER_TARGET_OVERRIDE_NONE = 0,  /**< Let layer decide whether to render to render target (default). */
    KZU_LAYER_RENDER_TARGET_OVERRIDE_FORCE = 1, /**< Force render to render target. */
    KZU_LAYER_RENDER_TARGET_OVERRIDE_DENY = 2,  /**< Deny render to render target. */
    KZU_LAYER_RENDER_TARGET_OVERRIDE_COUNT = 3  /**< Last enum value for validity checks. */
};


/** Layer quad rendering data. */
struct KzuLayerQuadParameters
{
    struct KzcVector2 offset;        /**< Offset used for rendering the quad. */
    struct KzcVector2 size;          /**< Size used for rendering the quad. */
    struct KzcVector2 textureOffset; /**< Texture offset for rendering. */
    struct KzcVector2 textureSize;   /**< Texture size for rendering. */
};

/** Background quad data. */
struct KzuLayerBackgroundQuadParameters
{
    struct KzcVector2 floorOffset;        /**< Offset to the beginning of top left quad. */
    struct KzcVector2 floorSize;          /**< Size of the top left quad. */
    struct KzcVector2 floorTextureOffset; /**< Texture offset of the top left quad. */
    struct KzcVector2 floorTextureSize;   /**< Texture size of the top left quad. */
    struct KzcVector2 ceilOffset;         /**< Offset to the beginning of bottom right quad. */
    struct KzcVector2 ceilSize;           /**< Size of the bottom right quad. */
    struct KzcVector2 ceilTextureOffset;  /**< Texture offset of the bottom right quad. */
    struct KzcVector2 ceilTextureSize;    /**< Texture size of the bottom right quad. */
};

/** Clipping information carried from parents. */
struct KzuLayerClippingParameters
{
    struct KzcRectangle area;           /**< Rectangular clipping area. */
    struct KzcRectangle previousArea;   /**< Previous rectangular clipping area. */
    kzBool enabled;                     /**< Is clipping enabled for this layer? */
    kzBool propagateClipping;           /**< Is clipping propagated from this layer onwards? */
};

KZ_INLINE kzBool KzuLayerClippingParametersIsEqual(const struct KzuLayerClippingParameters* a, const struct KzuLayerClippingParameters* b)
{
    return kzcRectangleIsEqual(&a->area, &b->area) && kzcRectangleIsEqual(&a->previousArea, &b->previousArea) &&
        (a->enabled == b->enabled) && (a->propagateClipping == b->propagateClipping);
}

/** Layer layouting information separated onto a structure of its own. */
struct KzuLayerLayoutingParameters
{
    struct KzcVector2 contentDesiredSize;    /**< Desired size from content. */
    struct KzcVector2 userDesiredSize;       /**< Desired size modified by user width / height properties. */
    struct KzcVector2 desiredSize;           /**< Desired size after properties, transformations and margins. */
    struct KzcVector2 desiredMin;            /**< Minimum point of node desired size quad. */
    struct KzcVector2 desiredMax;            /**< Maximum point of node desired size quad. */
    struct KzcVector2 allocatedSize;         /**< Size available for this layer (from parent). */
    struct KzcVector2 actualSize;            /**< Actual size (allocated size minus margins). */
    struct KzcVector2 compositionTargetSize; /**< Size limit for composition texture. */

    struct KzcMatrix3x3 layoutTransform;     /**< Layout transform. Set by layouts controlling the layer. */
    struct KzcMatrix3x3 tempLayoutTransform; /**< A temporary transform used to pass a partially calculated layout transform from arrange pass to transform pass. */
    struct KzcMatrix3x3 parentTransform;     /**< Transformation in regard to parent layer, calculated during layout, used for clipping. */
    struct KzcMatrix3x3 propagateTransform;  /**< Render quad transform passed to children. */
    struct KzcMatrix3x3 renderQuadTransform; /**< Transform in current render target space (same as worldTransform if rendering to screen). */
    struct KzcMatrix3x3 worldTransform;      /**< World transform, composite of all other transforms. */

    struct KzcColorRGBA backgroundColor;  /**< Color for background brush. */
    struct KzuTexture* backgroundTexture; /**< Texture for background brush. */

    kzUint clippingResult;                                  /**< Clipping result mask. */
    enum KzuLayerContentStretch contentStretch;             /**< Layer content stretch. */
    enum KzuLayerForegroundHint foregroundHint;             /**< Layer foreground hint. */
    enum KzuLayerRenderTargetOverride renderTargetOverride; /**< Render target override. */
    kzUint logicalChildCount;                               /**< Child count used for calculations of layouting logic. Defaults to actual child count, but can be overridden. */
    kzFloat opacity;                                        /**< Opacity, determined during the layout phase. */

    kzBool allowComposingClearColor; /**< Allow clearing of potential composing target color channel (normally yes). */
    kzBool allowComposingClearDepth; /**< Allow clearing of potential composing target depth channel (normally yes). */
    kzBool allowRenderSelf;          /**< Does the layer render itself? */
    kzBool cacheChildren;            /**< Does the layer cache its children? */
    kzBool cacheResult;              /**< Does the layer cache its rendering result (itself and its children). */
    kzBool cacheSelf;                /**< Does the layer cache itself? */
    kzBool childrenRequireExtract;   /**< Does the layer have children that need extract? */
    kzBool composingRequiresAlpha;   /**< Is alpha required for render targets? */
    kzBool composingRequiresDepth;   /**< Is depth required for managed render targets? */
    kzBool foregroundRequiresAlpha;  /**< Is alpha required for rendering the layer itself? */
    kzBool offscreenRendering;       /**< Should the layer only be rendered off-screen (and not flipped onto the screen). */
    kzBool requiresBackgroundQuad;   /**< Does the layer require a background. Default: yes, but may be disabled by implementations. */
    kzBool requiresComposingTarget;  /**< Set during layout if this layer requires an intermediate composing target. */
    kzBool requiresStencil;          /**< Is stencil required in managed render targets. */
    kzBool supportsStencil;          /**< Is stencil for the layer supported, by default true unless creating texture failed. */
};

/** Layer rendering information separated onto a structure of its own. */
struct KzuLayerRenderingParameters
{
    struct KzuRenderTarget* renderContentRenderTarget;     /**< Stored rendered content texture. */
    struct KzcVector2 renderContextLimits;                 /**< Stored render context limits. */
    struct KzuRenderTarget* quadBlitRenderTarget;          /**< Texture for blitting the quad. */
    struct KzcVector2 quadBlitLimits;                      /**< Limits for blitting the layer quad. */

    struct KzcRectangle axisAlignedMask;                   /**< Axis-aligned bounding box for later, contains x, y, width and height in its components. */
    struct KzcRectangle worldSpaceMask;                    /**< World-space mask for reliably detecting whether two layers collide.*/
    struct KzcRectangle previousFrameAxisAlignedMask;      /**< Axis-aligned bounding box for previous frame. */
    struct KzcRectangle previousFrameWorldSpaceMask;       /**< World-space mask for reliably detecting whether two layers collided last frame.*/

    struct KzcDynamicArray* foregroundLayers;              /**< Foreground layers, KZ_NULL if none. */
    struct KzcDynamicArray* backgroundLayers;              /**< Background layers, KZ_NULL if none. */
    struct KzcDynamicArray* previousFrameBackgroundLayers; /**< Previous frame background layers, needed for algorithm to re-render the layers that were on background last frame. */

    enum KzuLayerRenderingRestrictions restrictions;       /**< Rendering restrictions, i.e. shall only content be generated but not off-screen rendered. */
    kzUint renderIndex;                                    /**< Rendering index, specifies the render order when using renderIndividually. */

    kzBool childrenIteratedIndividually;                   /**< Are children iterated individually. */
    kzBool layerRenderQuadTransformChanged;                /**< Boolean indicating if layer render quad transform was changed. */
    kzBool parentRenderQuadTransformChanged;               /**< Boolean indicating if layer render quad transform was changed in parent context. */
    kzBool renderOnDemand;                                 /**< Specifies if layer is only rendered when render flag is triggered */
    kzBool individualRenderSupported;                      /**< Specifies if layer supports individual render. */
    kzBool transparent;                                    /**< Belongs to transparent layers list? */

    struct KzcRectangle subAreaMask; /**< Subarea mask for layer, defined if layer rerender is triggered from other layer. */
};


struct KzuLayer
{
    struct KzuObjectNode objectNode;                        /**< Inherited from object node. */

    const struct KzuLayerClass* layerClass;                 /**< Layer class. */

    struct KzuRenderTargetTexture* managedRenderTargets[3];    /**< Frame buffer texture(s) created by this layer (if needed). */
    struct KzuRenderTargetTexture* userRenderTarget;           /**< Forced render target (from properties). */
    struct KzuRenderTargetTexture* cachedRenderTargetChildren; /**< Cached render target of the layer's children. */
    struct KzuRenderTargetTexture* cachedRenderTargetFinal;    /**< Combined cached render target, used when both cache self and cache children are on. */
    struct KzuRenderTargetTexture* cachedRenderTargetSelf;     /**< Cached render target of the layer itself. */

    struct
    {
        struct KzuMaterial* material; /**< Material. */
        struct KzuMaterial* compositionMaterial; /**< Composition material. */
        struct KzuMaterial* backgroundMaterial; /**< Background material. */
    } materials; /**< Specifies material resources for layer. */

    struct KzuRenderTargetTexture* renderTargetTexture; /**< Render target texture for the layer. */

    enum KzuLayerRenderType renderType;                     /**< Which kind of rendering layer will provide. */
    kzBool allowRenderChildren;                             /**< Are children rendered for this layer or are they handled in a special manner? */
    kzBool requiresExtract;                                 /**< Does the layer need extract called? */

    KzuLayerOcclusionMaskFunction occlusionMaskFunction;    /**< Occlusion mask function for layer, if KZ_NULL uses the default implementation for layer area quad. */
    struct KzuLayerLayoutingParameters layouting;           /**< Layouting parameters. */
    struct KzuLayerClippingParameters clipping;             /**< Clipping parameters. */
    struct KzuLayerQuadParameters quad;                     /**< Layer quad parameters. Combination of layouting and clipping. */
    struct KzuLayerBackgroundQuadParameters backgroundQuad; /**< Layer background quad parameters. Combination of layouting and clipping. */
    struct KzuLayerQuadParameters compositionQuad;          /**< Composition quad. */
    struct KzuLayerRenderingParameters rendering;           /**< Rendering parameters. */
    struct KzuBoundingVolume* boundingVolume;               /**< Bounding volume. */
};

/** Layer class. */
struct KzuLayerClass
{
    /** Inherited from object node. */
    struct KzuObjectNodeClass objectNodeClass;

    /** Internal hit test function. Given point is in the layer space. */
    kzsError (*hitTestContentsFunction)(const struct KzuLayer* layer, const struct KzcVector2* point, struct KzuObjectNode** out_objectNode,
                                        struct KzcRay* out_ray, kzFloat* out_distance);
    /** Render a layer. */
    kzsError (*renderFunction)(struct KzuLayer* layer, struct KzuRenderer* renderer, struct KzuRenderContextStack* renderContextStack,
                               struct KzuMaterial** out_material);
    /** Layer measure function. */
    kzsError (*measureFunction)(struct KzuLayer* layer, const struct KzcVector2* availableSize, struct KzcVector2* out_measuredSize);
    /** Layer arrange function. */
    kzsError (*arrangeFunction)(struct KzuLayer* layer);
    /** Layer extract function. */
    kzsError (*extractFunction)(const struct KzuLayer* layer);
};


/** Initializes default layer data. Performs the actual object node creation. */
kzsError kzuLayerCreate_protected(const struct KzcMemoryManager* memoryManager, kzString name, struct KzuUIDomain* uiDomain,
                                const struct KzuLayerClass* layerClass, struct KzuLayer* layer);
/** Default initialize implementation. */
kzsError kzuLayerInitialize_protected(struct KzuObjectNode* objectNode);
/** Default uninitialize implementation. */
kzsError kzuLayerUninitialize_protected(struct KzuObjectNode* objectNode);

/** Called when a layer becomes attached. */
kzsError kzuLayerOnAttached_protected(struct KzuObjectNode* objectNode);

/** Called when a layer becomes detached. */
kzsError kzuLayerOnDetached_protected(struct KzuObjectNode* objectNode);

/** Implementation of layer property change callback. */
kzsError kzuLayerOnPropertyChanged_protected(struct KzuObjectNode* objectNode, const struct KzuPropertyType* propertyType, enum KzuPropertyNotificationReason reason);
/** Implementation of layer copying for object node class. */
kzsError kzuLayerCopy_protected(const struct KzuObjectNode* sourceObjectNode, struct KzuObjectNode* targetObjectNode);

/** Loads layer from binary. */
kzsError kzuLayerLoadFromKZB_protected(struct KzuObjectNode* objectNode, struct KzcInputStream* inputStream,
                                       const struct KzuBinaryFileInfo* file);

/**
 * Get aspect ratio property assigned to the layer.
 * Aspect ratio of 0 or smaller equals no aspect ratio set.
 */
kzBool kzuLayerGetUserAspectRatio_protected(const struct KzuLayer* layer, kzFloat* out_aspectRatio);
/**
 * Get layout height property assigned to the layer.
 * Having an offscreen render target overrides the layer's default size.
 * @return True if property was set.
 */
kzBool kzuLayerGetUserHeight_protected(const struct KzuLayer* layer, kzFloat* out_height);
/**
 * Get layout width property assigned to the layer.
 * Having an offscreen render target overrides the layer's default size.
 * @return True if property was set.
 */
kzBool kzuLayerGetUserWidth_protected(const struct KzuLayer* layer, kzFloat* out_width);
/**
 * Get material from layer with fallback to default.
 * Revert to 'safe' default material from renderer if no specific material set.
 */
struct KzuMaterial* kzuLayerGetMaterialSafe_protected(const struct KzuLayer* layer, const struct KzuRenderer* renderer,
                                                      kzBool requiresAdditionalBlending);
/** 
 * Get backgroun material from layer with fallback to default.
 * Revert to 'safe' default material from renderer if no specific material set.
 */
struct KzuMaterial* kzuLayerGetBackgroundMaterialSafe_protected(const struct KzuLayer* layer, const struct KzuRenderer* renderer,
                                                                kzBool requiresAdditionalOpacity);
/**
 * Get composition material from layer with fallback to default.
 * Revert to 'safe' default material from renderer if no specific material set.
 */
struct KzuMaterial* kzuLayerGetCompositionMaterialSafe_protected(const struct KzuLayer* layer, const struct KzuRenderer* renderer,
                                                                 kzBool requiresAdditionalBlending);

/**
 * Set layer composition texture.
 * Avoids potentially expensive property set if the value would not change.
 * Sets composition texture size for cases where render area does not actually encompass whole render target.
 */
kzsError kzuLayerSetCompositionTexture_protected(struct KzuLayer* layer, struct KzuRenderTargetTexture* renderTargetTexture);
/**
 * Get framebuffer texture.
 * The pointer to the framebuffer texture to modify is passed to the function.
 * If the framebuffer texture does not exist or the framebuffer settings for the layer have been changed,
 * it is (re)created.
 * Recreating the texture may invalidate the former reference to the texture, it's safer to call this function before
 * accessing the framebuffer than storing the value.
 */
kzsError kzuLayerGetRenderTarget_protected(struct KzuLayer* layer, kzBool forceAlpha, struct KzuRenderTargetTexture** inout_renderTargetTexture);
/** Get cache render target for layer's children. */
kzsError kzuLayerGetRenderTargetChildren_protected(struct KzuLayer* layer, struct KzuRenderTargetTexture** out_renderTargetTexture);
/** Get a combined, single render target the layer should output. */
kzsError kzuLayerGetRenderTargetFinal_protected(struct KzuLayer* layer, struct KzuRenderTargetTexture** out_renderTargetTexture);
/** Get cache render target for layer itself. */
kzsError kzuLayerGetRenderTargetSelf_protected(struct KzuLayer* layer, struct KzuRenderTargetTexture** out_renderTargetTexture);
/**
* Set layer render target to given texture, this texture is not managed by the layer itself.
* If layer already has a render target used for caching the final result, it is destroyed. Render targets used
* for caching of render self or render children are not affected.
* If called with KZ_NULL, do the reverse, and clear the assigned render target.
*/
kzsError kzuLayerSetUserRenderTarget_protected(struct KzuLayer* layer, struct KzuRenderTargetTexture* layerRenderTargetTexture);

/** Default implementation of layer content hit test. Just returns the layer itself. */
kzsError kzuLayerHitTestContent_protected(const struct KzuLayer* layer, const struct KzcVector2* point, struct KzuObjectNode** out_objectNode,
                                          struct KzcRay* out_ray, kzFloat* out_distance);

/** Default implementation of layer arrange. */
kzsError kzuLayerArrange_protected(struct KzuLayer* layer);
/**
 * Default assignment of layer actual size.
 * Also assigns allocated sizes of children. Should be called in the arrange functions of non-layouts.
 */
void kzuLayerAssignActualSizeDefault_protected(struct KzuLayer* layer, kzFloat sizeX, kzFloat sizeY);
/** Default implementation of layer extract. */
kzsError kzuLayerExtract_protected(const struct KzuLayer* layer);
/** Extract children of layer, called from layer extraction implementations. */
kzsError kzuLayerExtractChildren_protected(const struct KzuLayer* layer);
/** Default implementation of layer size calculation. */
kzsError kzuLayerMeasure_protected(struct KzuLayer* layer, const struct KzcVector2* availableSize, struct KzcVector2* out_measuredSize);

/** Clear render context stack area (if meaningful). */
kzsError kzuLayerClearRenderTarget_protected(const struct KzuLayer* layer, struct KzuRenderer* renderer, const struct KzuRenderContextStack* renderContextStack,
                                             kzBool requiresAdditionalBlending);
/** Clears render target area with properties instead of context stack. */
kzsError kzuLayerClearRenderTargetWithProperties_protected(const struct KzuLayer* layer, struct KzuRenderer* renderer,
                                                           kzBool requiresAdditionalBlending, struct KzuRenderTarget* renderTarget, const struct KzcVector2* limits);
/** Default layer render implementation. Does nothing. */
kzsError kzuLayerRender_protected(struct KzuLayer* layer, struct KzuRenderer* renderer, struct KzuRenderContextStack* renderContextStack,
                                  struct KzuMaterial** out_material);
/** Render background quad. */
kzsError kzuLayerRenderBackgroundQuad_protected(const struct KzuLayer* layer, struct KzuRenderer* renderer, const struct KzuRenderContextStack* renderContextStack,
                                                kzBool requiresAdditionalOpacity);
/** Render all children of a layer. */
kzsError kzuLayerRenderChildren_protected(struct KzuLayer* layer, struct KzuRenderer* renderer, struct KzuRenderContextStack* renderContextStack,
                                        kzBool externalRenderTarget);
/** Render layer quad. */
kzsError kzuLayerRenderQuad_protected(const struct KzuLayer* layer, struct KzuRenderer* renderer, const struct KzuRenderContextStack* renderContextStack,
                                      const struct KzuLayerQuadParameters* quad, const struct KzcMatrix3x3* renderTransform,
                                      const struct KzuMaterial* material, kzBool isCompositionMaterial);
/** Render layer quad with properties. */
kzsError kzuLayerRenderQuadWithProperties_protected(const struct KzuLayer* layer, struct KzuRenderer* renderer,
                                                    const struct KzuLayerQuadParameters* quad, const struct KzcMatrix3x3* renderTransform,
                                                    const struct KzuMaterial* material, kzBool isCompositionMaterial,
                                                    struct KzuRenderTarget* renderTarget, const struct KzcVector2* limits);

/** Implementation of layer rendering for object node class. Returns an error. */
kzsError kzuLayerRenderObjectNode_protected(const struct KzuObjectNode* objectNode, struct KzuRenderer* renderer,
                                            const struct KzuTransformedObjectNode* transformedObjectNode,
                                            struct KzcMatrix4x4* worldTransformation);

/** Handler for animation player play animation message. */
kzsError kzuLayerHandleAnimationPlayerPlayAnimation_protected(struct KzuMessage* message, void* userData);


/** Sets occlusion mask function for layer, if not set uses default mask generating function that is stencil quad from layer area when opaque layer. */
void kzuLayerSetOcclusionMaskFunction_protected(struct KzuLayer* layer, KzuLayerOcclusionMaskFunction occlusionMaskFunction);
/** Returns mask quad specific properties from the layer. */
void kzuLayerGetMaskQuadProperties_protected(const struct KzuLayer* layer, struct KzcVector2* out_offset, struct KzcVector2* out_size, struct KzcMatrix4x4* out_transformation);

/** Begins extraction of layer, returns render target for which the content is generated and the size. */
kzsError kzuLayerExtractLayerGraphBegin_protected(struct KzuLayer* layer, const struct KzuRenderContextStack* renderContextStack, struct KzuRenderTarget** out_renderTarget,
                                                  struct KzcVector2* out_limits);
/** Ends extraction of layer, returns render target for which the blitting of quad is performed and the size. */
kzsError kzuLayerExtractLayerGraphEnd_protected(const struct KzuLayer* layer, const struct KzuRenderContextStack* renderContextStack, struct KzuRenderTarget** out_blitQuadTexture,
                                                struct KzcVector2* out_blitQuadLimits);
/** Returns if layer can be invalidated when rendering individually. */
kzBool kzuLayerCanBeInvalidated_private(const struct KzuLayer* layer);

/** Measure one layer. */
kzsError kzuLayerMeasureSingle_protected(struct KzuLayer* layer, const struct KzcVector2* availableSize, kzBool handleStretch, kzBool* out_propagateMeasure);


KZ_HEADER_END


#endif
