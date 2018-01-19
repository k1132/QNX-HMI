/**
* \file
* Layer base class.
*
* KzuLayer is the base class for 2D user interface elements. KzuLayer inherits from KzuObjectNode.
*
* Layer Messages
* ----
* KzuLayer does not send or receive any messages.
*
* Layer Properties
* ----
* ::KZU_PROPERTY_TYPE_LAYER_MATERIAL resource ID property specifying a ::KzuMaterial used for rendering the layer as a texture.
* The default value is ::KZ_NULL.
*
* ::KZU_PROPERTY_TYPE_LAYER_COMPOSITION_MATERIAL resource ID property specifying a ::KzuMaterial used for rendering a layer that has been rendered into an FBO.
* The default value is ::KZ_NULL.
*
* ::KZU_PROPERTY_TYPE_LAYER_BACKGROUND_MATERIAL resource ID property specifying a ::KzuMaterial used for rendering the layer background.
* The default value is ::KZ_NULL.
*
* ::KZU_PROPERTY_TYPE_LAYER_RENDER_TARGET resource ID property specifies the render target texture for the layer. The default value is ::KZ_NULL.
*
* ::KZU_PROPERTY_TYPE_LAYER_RENDER_TARGET_REALLOCATION_LIMIT float property specifies a relative size limit where a layer render target is shrunk.
* The default value is 0.25.
*
* ::KZU_PROPERTY_TYPE_LAYER_RENDER_TARGET_MINIMUM_WIDTH float property specifies the minimum width of the render target. The default value is 0.
*
* ::KZU_PROPERTY_TYPE_LAYER_RENDER_TARGET_MINIMUM_HEIGHT float property specifies the minimum height of the render target. The default value is 0.
*
* ::KZU_PROPERTY_TYPE_LAYER_ASPECT_RATIO float property specifies the proportion width/height that is used when either the width or the height
* is specified to calculate the missing one. The default value is 1.0.
*
* ::KZU_PROPERTY_TYPE_LAYOUT_HEIGHT float property specifies the height of the layer when used in a layout. The default value is 0.
*
* ::KZU_PROPERTY_TYPE_LAYOUT_WIDTH float property specifies the width of the layer when used in a layout. The default value is 0.
*
* ::KZU_PROPERTY_TYPE_CLIP_CHILDREN Boolean property specifies whether or not the children should be clipped. Children whose bounding box is completely outside the
* bounding box of the parent are clipped. The children should only use a transformation that contains only translation. The default value is ::KZ_TRUE.
*
* ::KZU_PROPERTY_TYPE_LAYER_DISABLE_RENDER_TARGET_CLEAR Boolean property whether the layer should not clear the final render target before rendering into it even 
* if it would be deemed necessary. The default value is ::KZ_FALSE.
*
* ::KZU_PROPERTY_TYPE_LAYER_RENDER_SELF Boolean property specifies whether the layer itself and the children should be rendered (::KZ_TRUE) or just the children (::KZ_FALSE).
* 
* ::KZU_PROPERTY_TYPE_LAYER_CACHE_CHILDREN Boolean property specifies whether the layer's children should be rendered to a texture, caching the result, and then
* rendering the texture to the final render target (::KZ_TRUE), or if the children should be rendered directly to the final render target (::KZ_FALSE).
* The default value is ::KZ_TRUE.
*
* ::KZU_PROPERTY_TYPE_LAYER_CACHE_RESULT Boolean property specifies whether the layer and its children should be rendered to a texture, caching the result,
* and then rendering the texture to the final render target (::KZ_TRUE), or if the layer should be rendered directly to the final render target (::KZ_FALSE).
* The default value is ::KZ_TRUE.
*
* ::KZU_PROPERTY_TYPE_LAYER_CACHE_SELF Boolean property specifies whether the layer (without the children) should be rendered to a texture, caching the result, and
* then rendering the texture to the final render target (::KZ_TRUE), or if the layer should be rendered directly to the final render target (::KZ_FALSE).
* The default value is ::KZ_TRUE.
*
* ::KZU_PROPERTY_TYPE_LAYER_OPACITY float property specifies the layer's opacity. The value should be in the range [0, 1]. The default value is 1.0, i.e. fully opaque.
*
* ::KZU_PROPERTY_TYPE_LAYER_FOREGROUND_HINT integer property provides a hint of the type of the foreground provided by (viewport) layers. The value should
* be one of ::KzuLayerForegroundHint values. The default value is ::KZU_LAYER_FOREGROUND_HINT_NONE.
*
* ::KZU_PROPERTY_TYPE_LAYER_BACKGROUND_BRUSH_TEXTURE resource ID property specifies the texture used to render the layer's background. The default value is ::KZ_NULL.
*
* ::KZU_PROPERTY_TYPE_LAYER_BACKGROUND_BRUSH_COLOR ::KzcColorRGBA property specifies the layer's background color. The default value is {1.0, 1.0, 1.0, 1.0}.
*
* ::KZU_PROPERTY_TYPE_LAYER_PIXEL_FORMAT integer property specifies the layer's pixel format. The value should be one of ::KzuLayerPixelFormat values. The
* default value is ::KZU_LAYER_PIXEL_FORMAT_RGB.
*
* ::KZU_PROPERTY_TYPE_LAYER_OFFSCREEN_RENDERING Boolean property specifies whether the layer should be rendered off-screen and not onto the screen.
* The default value is ::KZ_FALSE.
*
* ::KZU_PROPERTY_TYPE_LAYOUT_HORIZONTAL_MARGIN ::KzcVector2 property specifies the margin in horizontal direction the layer should use when it resides under a layout.
* The two floats specify the margin for the left and right side of the layer respectively. The default value is {0, 0}.
*
* ::KZU_PROPERTY_TYPE_LAYOUT_VERTICAL_MARGIN ::KzcVector2 property specifies the margin in vertical direction the layer should use when it resides under a layout.
* The two floats specify the margin for the bottom and top side of the layer respectively. The default value is {0, 0}.
*
* ::KZU_PROPERTY_TYPE_LAYER_LAYOUT_TRANSFORMATION ::KzcMatrix3x3 property specifies a 2D transformation to be applied before layouting. The default value is
* {1, 0, 0, 0, 1, 0, 0, 0, 1}.
*
* ::KZU_PROPERTY_TYPE_LAYER_RENDER_ON_DEMAND Boolean property specifies if the layer and its children are only rendered when needed. The default value is ::KZ_FALSE.
*
* ::KZU_PROPERTY_TYPE_LAYER_RENDER_TRANSFORMATION ::KzcMatrix3x3 property specifies a 2D transformation to be applied after layouting. The default value is
* {1, 0, 0, 0, 1, 0, 0, 0, 1}.
*
* ::KZU_PROPERTY_TYPE_LAYER_RENDER_TRANSFORMATION_ORIGIN ::KzcVector2 property specifies the render transformation origin in layer-relative coordinates.
* The default value is {0, 0}.
*
* ::KZU_PROPERTY_TYPE_LAYER_SNAP_TO_PIXEL Boolean property specifies whether to snap the layer's translation and actual size into the closest pixel boundary.
* The default value is ::KZ_FALSE.
*
* ::KZU_PROPERTY_TYPE_LAYER_CONTENT_STRETCH integer property specifies how the content of this layer is stretched. The value should be one of
* ::KzuLayerContentStretch values. The default value is ::KZU_LAYER_CONTENT_STRETCH_UNIFORM.
*
* ::KZU_PROPERTY_TYPE_LAYER_COMPOSITION_TEXTURE is an internal property used by Kanzi.
*
* ::KZU_PROPERTY_TYPE_LAYER_RENDER_OPACITY is an internal property used by Kanzi.
*
* ::KZU_PROPERTY_TYPE_LAYER_RENDER_BACKGROUND_COLOR is an internal property used by Kanzi.
*
* ::KZU_PROPERTY_TYPE_LAYER_RENDER_BACKGROUND_TEXTURE is an internal property used by Kanzi.
*
* \see \ref kzu_object.h for KzuObjectNode documentation.
*
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_LAYER_H
#define KZU_LAYER_H


#include <user/common/kzu_user.h>
#include <user/scene_graph/kzu_object_base.h>

#include <core/util/math/kzc_vector2.h>
#include <core/util/math/kzc_matrix3x3.h>


KZ_HEADER_BEGIN


/** Profiling constant string for layouting total time. */
#define KZU_LAYER_PROFILING_LAYOUT "kzuLayerLayout"
/** Profiling constant string for layouting measure time. */
#define KZU_LAYER_PROFILING_LAYOUT_MEASURE "kzuLayerLayoutMeasure"
/** Profiling constant string for layouting arrange time. */
#define KZU_LAYER_PROFILING_LAYOUT_ARRANGE "kzuLayerLayoutArrange"
/** Profiling constant string for layouting scene marking iteration. */
#define KZU_LAYER_PROFILING_LAYOUT_MARK_SCENE_LAYERS "kzuLayerLayoutMarkSceneLayers"

#define KZU_LAYER_TEXTURE_COLOR_BUFFER 0x01   /**< Layer texture flag - color buffer. */
#define KZU_LAYER_TEXTURE_COLOR_ALPHA 0x02    /**< Layer texture flag - alpha channel. */
#define KZU_LAYER_TEXTURE_COLOR_HDR 0x04      /**< Layer texture flag - HDR color. */
#define KZU_LAYER_TEXTURE_DEPTH_BUFFER 0x08   /**< Layer texture flag - depth buffer. */
#define KZU_LAYER_TEXTURE_STENCIL_BUFFER 0xA0 /**< Layer texture flag - stencil buffer. */


/** Layer content fill. */
enum KzuLayerContentStretch
{
    KZU_LAYER_CONTENT_STRETCH_NONE,            /**< Content is displayed unstretched in the middle of layer area. */
    KZU_LAYER_CONTENT_STRETCH_FILL,            /**< Content encompasses full layer area. */
    KZU_LAYER_CONTENT_STRETCH_UNIFORM,         /**< Content stretched to fill as much of layer area as possible. If aspect ratios do not match, leave area undrawn. */
    KZU_LAYER_CONTENT_STRETCH_UNIFORM_TO_FILL, /**< Content stretched to fill full layer area. If aspect ratios do not match, clip excess area. */
    KZU_LAYER_CONTENT_STRETCH_WRAP,            /**< Content is repeated over the whole layer area unstretched. */
    KZU_LAYER_CONTENT_STRETCH_COUNT            /**< Last enum value for validity checks. */
};

/** Layer foreground hint. */
enum KzuLayerForegroundHint
{
    KZU_LAYER_FOREGROUND_HINT_NONE,        /**< No hint given, assumed the background of a layer can be rendered after content. */
    KZU_LAYER_FOREGROUND_HINT_TRANSLUCENT, /**< Some elements rendered within the layer are translucent over the layer background. */
    KZU_LAYER_FOREGROUND_HINT_OPAQUE,      /**< Layer content is assumed to be fully opaque thus, that background does not need to be rendered. */
    KZU_LAYER_FOREGROUND_HINT_COUNT        /**< Last enum value for validity checks. */
};

/** Layer pixel formats. */
enum KzuLayerPixelFormat
{
    KZU_LAYER_PIXEL_FORMAT_RGB, /**< Managed render targets use RGB format. */
    KZU_LAYER_PIXEL_FORMAT_RGBA /**< Managed render targets use RGBA format. */
};


/** Object type identifier for component objects. */
extern const KzuObjectType KZU_OBJECT_TYPE_LAYER;


/* Forward declaration. */
struct KzcInputStream;
struct KzcRay;
struct KzcVector2;
struct KzuBinaryFileInfo;
struct KzuComposer;
struct KzuEngine;
struct KzuImageTexture;
struct KzuRenderContextStack;
struct KzuObjectNode;
struct KzuRenderer;
struct KzuRenderTargetTexture;
struct KzuResourceManager;
struct KzuMaterial;
struct KzuBoundingVolume;


/** 
 * \struct KzuLayer
 * Layer object. Needs to inherit object node to gain property system.
 */
struct KzuLayer;


/** Hit test visitor function. */
typedef kzsError (*KzuLayerHitTestVisitor)(const struct KzuLayer* layer, const struct KzcVector2* layerPoint, void* userData,
                                           struct KzuObjectNode** out_objectNode);


/** Converts to layer from object node. */
struct KzuLayer* kzuLayerFromObjectNode(const struct KzuObjectNode* objectNode);
/** Converts to object node from layer. */
struct KzuObjectNode* kzuLayerToObjectNode(const struct KzuLayer* layer);

/**
 * Create a layer render target.
 * Creates a layer render target using the given requirement flags. The specific data storage of the render target
 * is determined based on the platform.
 */
kzsError kzuLayerCreateRenderTarget(const struct KzuResourceManager* resourceManager, kzUint width, kzUint height,
                                    kzUint flags, struct KzuRenderTargetTexture** out_renderTarget);
/**
 * Create a layer texture.
 * Creates a layer texture using the given requirement flags. The specific data storage of the texture is determined
 * based on the platform.
 */
kzsError kzuLayerCreateTexture(const struct KzuResourceManager* renderer, kzUint width, kzUint height, kzUint flags,
                               const void* data, struct KzuImageTexture** out_texture);

/** Gets the actual size of this layer. */
struct KzcVector2 kzuLayerGetActualSize(const struct KzuLayer* layer);
/**
 * Sets the allocated size for this layer.
 * Called internally by layer layouting. Invalidates arrange if the size differs from previous one and the layer
 * needs to be rearranged.
 */
void kzuLayerSetAllocatedSize(struct KzuLayer* layer, struct KzcVector2 allocatedSize);
/**
 * Sets the layout transform for this layer.
 * Called internally by layer layouting. Invalidates arrange if the transform differs from previous one and the
 * layer needs to be rearranged.
 */
void kzuLayerSetLayoutTransform(struct KzuLayer* layer, const struct KzcMatrix3x3* layoutTransform);
/** Gets the material used for rendering this layer. */
struct KzuMaterial* kzuLayerGetMaterial(const struct KzuLayer* layer);
/** Gets the background material used for rendering the background of this layer. */
struct KzuMaterial* kzuLayerGetBackgroundMaterial(const struct KzuLayer* layer);
/** Gets the composition material used for rendering this layer. */
struct KzuMaterial* kzuLayerGetCompositionMaterial(const struct KzuLayer* layer);
/** Set the material used for rendering this layer. */
kzsError kzuLayerSetMaterial(struct KzuLayer* layer, struct KzuMaterial* material);
/** Set the background material used for rendering the background of this layer. */
kzsError kzuLayerSetBackgroundMaterial(struct KzuLayer* layer, struct KzuMaterial* material);
/** Set the composition material used for rendering this layer. */
kzsError kzuLayerSetCompositionMaterial(struct KzuLayer* layer, struct KzuMaterial* material);
/** Gets the parent space transform of this layer. */
struct KzcMatrix3x3 kzuLayerGetRenderTransform(const struct KzuLayer* layer);
/** Gets the world space transform of this layer. */
struct KzcMatrix3x3 kzuLayerGetWorldTransform(const struct KzuLayer* layer);

/** Invalidate cached render target of children, if it exists. */
void kzuLayerInvalidateCacheChildren(struct KzuLayer* layer);
/** Invalidate cached render target of final composition of the layer, if it exists. */
void kzuLayerInvalidateCacheResult(struct KzuLayer* layer);
/** Invalidate cached render target of the layer itself, if it exists. */
void kzuLayerInvalidateCacheSelf(struct KzuLayer* layer);

/** Helper function for observing if layerA intersects with layerB. */
kzBool kzuLayerAABBIntersects(const struct KzuLayer* layerA, const struct KzuLayer* layerB);
/** Helper function for observing if layerA intersects with layerB last frame. */
kzBool kzuLayerAABBIntersectsPreviousFrame(const struct KzuLayer* layerA, const struct KzuLayer* layerB);

/** Returns if layer render on demand is enabled. */
kzBool kzuLayerIsRenderOnDemand(const struct KzuLayer* layer);

/**
 * Tell if a layer contains a point (defined in screen space). *
 * If true, the layer-space coordinates have been written into outgoing point.
 */
kzBool kzuLayerContainsPoint(const struct KzuLayer* layer, const struct KzcVector2* point, struct KzcVector2* out_point);
/** Converts point in layer's space to a point in another layer's space. */
void kzuLayerPointToLayerPoint(const struct KzuLayer* sourceLayer, const struct KzcVector2* point, const struct KzuLayer* targetLayer,
                               struct KzcVector2* out_point);
/** Converts a point from screen space into layer space. */
void kzuScreenPointToLayerPoint(const struct KzuLayer* layer, const struct KzcVector2* point, struct KzcVector2* out_point);

/**
 * Performs a hit test to a layer and all sub-layers.
 * Pickable attribute nor layer internal hit testing has no factor for this function, it simply returns the topmost
 * layer of given type at given point. Use KZU_OBJECT_TYPE_LAYER as layer type to match any layer.
 */
kzsError kzuLayerHitTest(const struct KzuLayer* layer, const struct KzcVector2* point, KzuObjectType type, struct KzuObjectNode** out_objectNode);
/**
 * Iterate layers and call visitor function.
 * Used for specific implementations of hit testing.
 */
kzsError kzuLayerHitTestIterate(const struct KzuLayer* layer, const struct KzcVector2* point, KzuLayerHitTestVisitor visitor,
                                void* userData, struct KzuObjectNode** out_objectNode);

/** Extract scenes in layers. */
kzsError kzuLayerExtract(const struct KzuLayer* layer);
/** Lays out the layer and any of its children if they require layout. */
kzsError kzuLayerLayout(struct KzuLayer* layer, const struct KzcMatrix3x3* rootTransform);

/** Repositions the layer to the beginning of its parent's children, so that it is drawn first. */
kzsError kzuLayerMoveToBack(const struct KzuLayer* layer);
/** Repositions the layer to the end of its parent's children, so that it is drawn last. */
kzsError kzuLayerMoveToFront(const struct KzuLayer* layer);

/** Renders a layer. */
kzsError kzuLayerRender(struct KzuLayer* layer, struct KzuRenderer* renderer, struct KzuRenderContextStack* renderContextStack);

/** Renders a layer individually, without it children, using the render parameters from extract. */
kzsError kzuLayerRenderIndividually(struct KzuLayer* layer, struct KzuRenderer* renderer, struct KzuRenderContextStack* renderContextStack);

/** Tells if an object node is a layer. */
kzBool kzuObjectNodeIsLayer(const struct KzuObjectNode* objectNode);

/** Gets the UI domain for the layer. */
struct KzuUIDomain* kzuLayerGetUIDomain(const struct KzuLayer* layer);

/** Calls the measure function of the layer. */
kzsError kzuLayerMeasure(struct KzuLayer* layer, const struct KzcVector2* availableSize, struct KzcVector2* out_desiredSize);
/** Calls the arrange function of the layer. */
kzsError kzuLayerArrange(struct KzuLayer* layer);

/** Bounding volume getter implementation. */
kzsError kzuLayerGetBoundingVolume_protected(const struct KzuObjectNode* objectNode, struct KzuBoundingVolume** out_boundingVolume);

KZ_HEADER_END


#include "kzu_layer_properties.h"


#endif
