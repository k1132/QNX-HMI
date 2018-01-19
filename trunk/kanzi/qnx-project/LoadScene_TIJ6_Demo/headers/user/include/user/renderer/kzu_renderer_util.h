/**
* \file
* User renderer utilities, e.g. wireframe grid, axes, debug.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_RENDERER_UTIL_H
#define KZU_RENDERER_UTIL_H


#include "kzu_renderer_types.h"

#include <core/renderer/kzc_renderer.h>
#include <core/util/math/kzc_matrix4x4.h>
#include <core/util/math/kzc_vector2.h>
#include <core/util/math/kzc_vector3.h>

#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations */
struct KzsEventQueue;
struct KzcColorRGBA;
struct KzcDynamicArray;
struct KzuTrajectory;
struct KzuBoundingVolume;
struct KzuCameraNode;
struct KzuCanvas;
struct KzuLightNode;
struct KzuMaterial;
struct KzuRenderer;
struct KzuMesh;
struct KzuRenderContextStack;
struct KzuTexture;
struct KzuTransformedBoundingVolume;
struct KzuTransformedObjectNode;
struct KzuUiComponentNode;
struct KzuUiGridLayout;
struct KzuGridLayer;
struct KzuUiListBox;
struct KzuUiGridListBox;


/** Enumeration for polygon fill mode. Used in visualization functions. */
enum KzuFillMode
{
    KZU_FILL_MODE_SOLID = 0,
    KZU_FILL_MODE_WIREFRAME
};


/** Sets solid color for rendering. Has to be called after material has been applied. */
kzsError kzuRendererSetSolidColor(const struct KzuRenderer* renderer, const struct KzcColorRGBA* color);

/**
* Applies a material with the given solid color for rendering.
* Parameter out_isValid will be KZ_TRUE if drawing can continue, otherwise KZ_FALSE.
*/
kzsError kzuRendererApplySolidColorMaterial(struct KzuRenderer* renderer, const struct KzcColorRGBA* color, kzBool* out_isValid);

/**
* Applies a material with the given debug color for rendering.
* Parameter out_isValid will be KZ_TRUE if drawing can continue, otherwise KZ_FALSE.
*/
kzsError kzuRendererApplyDebugLightMaterial(struct KzuRenderer* renderer, const struct KzcColorRGBA* color, kzBool* out_isValid);

/** Draws a box with the default parameters for layout visualization. */
kzsError kzuRendererDrawLayoutBox(struct KzuRenderer* renderer, const struct KzcVector3* backBottomLeft, const struct KzcVector3* frontTopRight,
                                  const struct KzcMatrix4x4* transform, const struct KzcColorRGBA* color);

/**
* Draws a bounding volume.
* Uses the default color. The box is transformed with the given matrix before drawing.
*/
kzsError kzuRendererDrawBoundingVolume(struct KzuRenderer* renderer, const struct KzuBoundingVolume* boundingVolume,
                                       const struct KzcMatrix4x4* worldTransformation, enum KzuFillMode fillMode);
/**
* Draws a bounding volume.
* Uses the given color. The box is transformed with the given matrix before drawing.
*/
kzsError kzuRendererDrawBoundingVolumeColor(struct KzuRenderer* renderer, const struct KzuBoundingVolume* boundingVolume,
                                            const struct KzcMatrix4x4* worldTransformation, enum KzuFillMode fillMode, const struct KzcColorRGBA* color);
/**
* Draws a bounding volume.
* Uses the current settings. The box is transformed with the given matrix before drawing.
*/
kzsError kzuRendererDrawBoundingVolumeRaw(struct KzuRenderer* renderer, const struct KzuBoundingVolume* boundingVolume,
                                          const struct KzcMatrix4x4* worldTransformation, enum KzuFillMode fillMode);

/** Draws a transformed bounding volume. Uses the default color. */
kzsError kzuRendererDrawTransformedBoundingVolume(struct KzuRenderer* renderer, const struct KzuTransformedBoundingVolume* volume,
                                                  enum KzuFillMode fillMode);
/** Draws a transformed bounding volume. Uses the given color. */
kzsError kzuRendererDrawTransformedBoundingVolumeColor(struct KzuRenderer* renderer, const struct KzuTransformedBoundingVolume* volume,
                                                       enum KzuFillMode fillMode, const struct KzcColorRGBA* color);
/** Draws a transformed bounding volume. Uses the current settings. */
kzsError kzuRendererDrawTransformedBoundingVolumeRaw(struct KzuRenderer* renderer, const struct KzuTransformedBoundingVolume* volume,
                                                     enum KzuFillMode fillMode);
/** Draws a selection indicator, resembles a bounding volume. */
kzsError kzuRendererDrawSelectionIndicator(struct KzuRenderer* renderer, const struct KzuBoundingVolume* boundingVolume,
                                           const struct KzcMatrix4x4* worldTransformation, const struct KzcColorRGBA* color);

/**
* Draws a box given by two opposing corner points.
* Uses the given color. The box is transformed with the given matrix before drawing.
*/
kzsError kzuRendererDrawBoxColor(struct KzuRenderer* renderer, const struct KzcVector3* backBottomLeft, const struct KzcVector3* frontTopRight,
                                 const struct KzcMatrix4x4* transform, enum KzuFillMode fillMode, const struct KzcColorRGBA* color);

/** Draws solid bounding volume using currently bound material. */
kzsError kzuRendererDrawBoundingVolumeSolid(const struct KzuRenderer* renderer, struct KzuBoundingVolume* boundingVolume,
                                            const struct KzcMatrix4x4* worldTransformation);

/** Visualizes all cells in a grid layout or layer. */
kzsError kzuRendererDrawGridLayoutCells(struct KzuRenderer* renderer, const struct KzcVector3* backBottomLeft, const struct KzcVector3 *frontTopRight,
                                        const struct KzcMatrix4x4* transform, const struct KzcMatrix4x4* camera,
                                        const struct KzuUiGridLayout* gridLayout, const struct KzuGridLayer* gridLayer, const struct KzcColorRGBA* color);

/**
* Draws primitives of the given type.
* Takes vertex position data as a parameter.
*/
kzsError kzuRendererDrawPrimitives(const struct KzuRenderer* renderer, const kzFloat* vertexList, kzUint vertexCount,
                                   enum KzcPrimitiveType type, const struct KzcMatrix4x4* worldTransformation);

/**
* Draws primitives of the given type.
* Takes vertex position and normal data as parameters.
* When kzuRendererIsMeshVertexCombiningEnabled returns true, draws nothing but populates renderer combined vertex array.
*/
kzsError kzuRendererDrawPrimitivesNormal(struct KzuRenderer* renderer, const kzFloat* vertexList, const kzFloat* normalList, kzUint vertexCount,
                                         enum KzcPrimitiveType type, const struct KzcMatrix4x4* worldTransformation);

/** Draws a point list with current settings. Handles only position data. */
kzsError kzuRendererDrawPointList(const struct KzuRenderer* renderer, const kzFloat* pointList, kzUint pointCount, const struct KzcMatrix4x4* worldTransformation);
/** Draws a line list with current settings. Handles only position data. */
kzsError kzuRendererDrawLineList(const struct KzuRenderer* renderer, const kzFloat* lineList, kzUint lineCount, const struct KzcMatrix4x4* worldTransformation);
/** Draws a triangle fan with current settings. Handles only position data. */
kzsError kzuRendererDrawTriangleFan(const struct KzuRenderer* renderer, const kzFloat* triangleList, kzUint triangleCount, const struct KzcMatrix4x4* worldTransformation);
/** Draws a triangle strip with current settings. Handles only position data. */
kzsError kzuRendererDrawTriangleStrip(const struct KzuRenderer* renderer, const kzFloat* vertexList, kzUint vertexCount, const struct KzcMatrix4x4* worldTransformation);

/** Draws a quad using solid color. */
kzsError kzuRendererDrawQuad(struct KzuRenderer* renderer, const struct KzcVector3* p1, const struct KzcVector3* p2, const struct KzcVector3* p3,
                             const struct KzcVector3* p4, const struct KzcColorRGBA* color, const struct KzcMatrix4x4* worldTransformation);
/** Render a layer quad. Z axis assumed to be zero. */
kzsError kzuRendererDrawLayerQuad(struct KzuRenderer* renderer, const struct KzuMaterial* material, const struct KzcVector2* renderOffset,
                                  const struct KzcVector2* renderSize, const struct KzcVector2* contentOffset,
                                  const struct KzcVector2* contentSize, kzFloat depth, const struct KzcMatrix3x3* renderTransform);
/** As rendering a layer quad, but omit everything concerning texture coordinates.
    When kzuRendererIsMeshVertexCombiningEnabled returns true, draws nothing but populates the vertex array.
*/
kzsError kzuRendererDrawUntexturedLayerQuad(struct KzuRenderer* renderer, const struct KzcVector2* renderOffset,
                                            const struct KzcVector2* renderSize, const struct KzuMaterial* material,
                                            const struct KzcMatrix4x4* worldTransformation);
/** Render a layer outline quad. Z axis assumed to be zero. */
kzsError kzuRendererDrawLayerOutlineQuad(struct KzuRenderer* renderer, kzFloat width, kzFloat height, const struct KzuMaterial* material,
                                         const struct KzuTexture* texture, kzFloat textureOffset, const struct KzcColorRGBA* color,
                                         const struct KzcMatrix4x4* worldTransformation);
/** Draws a quad using specified material. */
kzsError kzuRendererDrawQuadWithMaterial(struct KzuRenderer* renderer, const struct KzcVector3* p1, const struct KzcVector3* p2, const struct KzcVector3* p3,
                                         const struct KzcVector3* p4, const struct KzuMaterial* material, const struct KzcMatrix4x4* worldTransformation);

/** Draws screen quad with specified material, potential texture fills the screen rectangle. */
kzsError kzuRendererDrawScreenQuad(struct KzuRenderer* renderer, const struct KzuRenderContextStack* renderContextStack, const struct KzuMaterial* material,
                                   kzBool useOverrideTexture);
/** Draws viewport quad, fills with given pattern. If texture is non-null, use texture span from it. */
kzsError kzuRendererDrawViewportQuad(struct KzuRenderer* renderer, const struct KzcVector2* offset, const struct KzcVector2* limits,
                                         const struct KzuMaterial* material, const struct KzuTexture* texture);
/** Sets renderer stencil test and write. */
void kzuRendererSetStencilTestEnabled(const struct KzuRenderer* userRenderer, kzBool stencilTestEnabled);

/** Applies stencil settings with overrides for rendering. */
void kzuRendererApplyStencilSettings(const struct KzuRenderer* userRenderer, kzBool stencilTestEnabled, kzUint stencilRef, kzUint stencilMask,
                                             enum KzuStencilFunction stencilFunction, enum KzuStencilOperation stencilOperationStencilFail,
                                             enum KzuStencilOperation stencilOperationStencilPassDepthFail, enum KzuStencilOperation stencilOperationStencilPassDepthPass);
/** Gets stencil settings from renderer. */
void kzuRendererGetStencilSettings(const struct KzuRenderer* userRenderer, kzBool* out_stencilTestEnabled, kzUint* out_stencilRef, kzUint* out_stencilMask,
                                    enum KzuStencilFunction* out_stencilFunction, enum KzuStencilOperation* out_stencilOperationStencilFail,
                                    enum KzuStencilOperation* out_stencilOperationStencilPassDepthFail, enum KzuStencilOperation* out_stencilOperationStencilPassDepthPass);


/** Sets default orthogonal projection and viewport for renderer. */
void kzuRendererSetDefaultOrthoProjection(const struct KzuRenderer* renderer);

/** Draws a wire frame grid with default colors. */
kzsError kzuRendererDrawWireframeGrid(struct KzuRenderer* renderer, kzFloat spacing);

/** Function for drawing wire frame box. Useful for debugging. */
kzsError kzuRendererDrawWireframeBox(struct KzuRenderer* renderer, const struct KzcVector3* boundingBoxMin,
                                     const struct KzcVector3* boundingBoxMax);
/** Draws a bone identifier. */
kzsError kzuRendererDrawBoneIdentifier(struct KzuRenderer* renderer, const struct KzcVector3* position, const struct KzcMatrix4x4* orientation);

/** Draws a wire frame light symbol. */
kzsError kzuRendererDrawLight(struct KzuRenderer* renderer, const struct KzuLightNode* lightNode,
                              const struct KzcMatrix4x4* worldTransformation);
/** Draws an empty object symbol with wire frame lines. */
kzsError kzuRendererDrawEmptyObject(struct KzuRenderer* renderer, const struct KzcMatrix4x4* worldTransformation);

/** Draws a wire frame camera symbol. */
kzsError kzuRendererDrawCamera(struct KzuRenderer* renderer, const struct KzuCameraNode* cameraNode,
                               const struct KzcMatrix4x4* worldTransformation);
/** Draws skeleton with wire frame lines. */
kzsError kzuRendererDrawSkeleton(struct KzuRenderer* renderer, const struct KzuMesh* mesh);
/** Draws a trajectory with wire frame lines. */
kzsError kzuRendererDrawTrajectory(struct KzuRenderer* renderer, const struct KzuTrajectory* trajectory,
                                   const struct KzcMatrix4x4* worldTransformation);

/** Draws item area for a grid list box. */
kzsError kzuRendererDrawGridListBoxItemArea(struct KzuRenderer* renderer, const struct KzuUiGridListBox* gridListBox,
                                            const struct KzcMatrix4x4* worldTransformation);

/** Draws a trajectory list box's selector with wire frame lines. */
kzsError kzuRendererDrawTrajectoryListBoxSelector(struct KzuRenderer* renderer, const struct KzuTrajectory* trajectory,
                                                  kzFloat selectorOffsetProportional, const struct KzcMatrix4x4* worldTransformation);
/** Draws a trajectory list box's clip offset visualizer with wire frame lines. */
kzsError kzuRendererDrawTrajectoryListBoxClipVisualizer(struct KzuRenderer* renderer, const struct KzuTrajectory* trajectory,
                                                        kzFloat clipOffsetProportional, const struct KzcMatrix4x4* worldTransformation);

/** Add object bounding volume to renderer vertex array. */
void kzuPartialRenderingAddObjectBoundingVolume(struct KzuRenderer* renderer, const struct KzuBoundingVolume* boundingVolume,
                                                const struct KzcMatrix4x4* worldTransformation);
/** Add layer quad to renderer vertex array. */
void kzuPartialRenderingAddLayerQuad(struct KzuRenderer* renderer, const struct KzcVector2* renderOffset,
                                     const struct KzcVector2* renderSize, const struct KzcMatrix3x3* worldTransformation);


KZ_HEADER_END


#endif
