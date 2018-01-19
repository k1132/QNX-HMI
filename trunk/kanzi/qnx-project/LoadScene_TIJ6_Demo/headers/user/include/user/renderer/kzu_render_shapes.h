/**
* \file
* Shape drawing utilities, e.g. wireframe grid, axes, debug.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_RENDER_SHAPES_H
#define KZU_RENDER_SHAPES_H


#include <core/util/math/kzc_matrix4x4.h>
#include <core/util/math/kzc_vector3.h>

#include <system/debug/kzs_error.h>
#include <system/input/kzs_input.h>
#include <system/kzs_types.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations */
struct KzuRenderer;

struct KzuCameraNode;
struct KzuCanvas;
struct KzuTransformedBoundingVolume;
struct KzuTransformedObjectNode;
struct KzuUiComponentNode;
struct KzuUiGridLayout;
struct KzuGridLayer;
struct KzuTrajectory;

struct KzcColorRGBA;
struct KzcDynamicArray;


struct KzsEventQueue;



/** Draws a wireframe grid with the given colors. Uses the current rendering settings. */
kzsError kzuRenderShapesDrawWireframeGrid(struct KzuRenderer* renderer, kzFloat spacing,
                                          const struct KzcColorRGBA* gridColor, const struct KzcColorRGBA* centerLinesColor);

/** Draws an axis shape in the origin with the given colors. Uses the current rendering settings.  */
kzsError kzuRenderShapesDrawCoordinateSystemAxes(struct KzuRenderer* renderer, const struct KzcColorRGBA* axisXColor,
                                                 const struct KzcColorRGBA* axisYColor, const struct KzcColorRGBA* axisZColor);

/**
* Draws a wireframe box given by two opposite corner points.
* The corner points are assumed axis-aligned and are transformed with the given transform before drawing.
* Uses the current rendering settings. 
*/
kzsError kzuRenderShapesDrawBoxWireframe(const struct KzuRenderer* renderer,
                                         const struct KzcVector3* backBottomLeft,
                                         const struct KzcVector3* frontTopRight,
                                         const struct KzcMatrix4x4* transform);
/**
* Draws a solid box given by two opposite corner points.
* The corner points are assumed axis-aligned and are transformed with the given transform before drawing.
* Uses the current rendering settings. 
*/
kzsError kzuRenderShapesDrawBoxSolidNormal(struct KzuRenderer* renderer,
                                           const struct KzcVector3* backBottomLeft, const struct KzcVector3* frontTopRight,
                                           const struct KzcMatrix4x4* worldTransform);

/**
* Draws a transformed wireframe bounding volume with the current rendering settings.
* Draws with only vertex positions.
*/
kzsError kzuRenderShapesDrawTransformedBoundingVolumeWireframe(const struct KzuRenderer* renderer, const struct KzuTransformedBoundingVolume* volume);

/**
* Draws a transformed solid bounding volume with the current rendering settings.
* Draws with vertex positions and normals.
*/
kzsError kzuRenderShapesDrawTransformedBoundingVolumeSolidNormal(struct KzuRenderer* renderer, const struct KzuTransformedBoundingVolume* volume);


/**
* Visualizes all cells in a grid layout or layer with the current rendering settings.
*/
kzsError kzuRenderShapesDrawGridLayoutCells(const struct KzuRenderer* renderer, const struct KzcVector3* backBottomLeft, const struct KzcVector3 *frontTopRight,
                                            const struct KzcMatrix4x4* transform, const struct KzcMatrix4x4* camera,
                                            const struct KzuUiGridLayout* gridLayout, const struct KzuGridLayer* gridLayer);

/** Visualizes a trajectory. */
kzsError kzuRenderShapesDrawTrajectory(const struct KzuRenderer* renderer, const struct KzuTrajectory* trajectory, const struct KzcMatrix4x4* worldTransformation);
/** Visualizes selector location of a trajectory layout. */
kzsError kzuRenderShapesDrawTrajectoryLayoutSelector(const struct KzuRenderer* renderer, const struct KzuTrajectory* trajectory, kzFloat selectorOffsetProportional,
                                                     const struct KzcMatrix4x4* worldTransformation);
/** Visualizes clip offset of a trajectory list box. */
kzsError kzuRenderShapesDrawTrajectoryClipVisualizer(const struct KzuRenderer* renderer, const struct KzuTrajectory* trajectory, kzFloat clipOffsetProportional,
                                                     const struct KzcMatrix4x4* worldTransformation);

/** Draws a point light symbol transformed by the given matrix. */
kzsError kzuRenderShapesDrawPointLight(const struct KzuRenderer* renderer, const struct KzcMatrix4x4* worldTransformation);
/** Draws a directional light symbol transformed by the given matrix. */
kzsError kzuRenderShapesDrawDirectionalLight(const struct KzuRenderer* renderer, const struct KzcMatrix4x4* worldTransformation);
/** Draws a spot light symbol transformed by the given matrix. */
kzsError kzuRenderShapesDrawSpotLight(const struct KzuRenderer* renderer, kzFloat angle, const struct KzcMatrix4x4* worldTransformation);

/** Draws an empty object symbol transformed by the given matrix. */
kzsError kzuRenderShapesDrawEmptyObject(const struct KzuRenderer* renderer, const struct KzcMatrix4x4* worldTransformation);

/** Draws a camera symbol transformed by the given matrix. Uses projection and fov from the camera. */
kzsError kzuRenderShapesDrawCamera(const struct KzuRenderer* renderer, const struct KzuCameraNode* cameraNode,
                                   const struct KzcMatrix4x4* worldTransformation);

/** Add partial rendering bounding volume. */
void kzuRenderShapesAddPartialRenderingBoundingVolume(struct KzuRenderer* renderer, const struct KzuTransformedBoundingVolume* volume);


KZ_HEADER_END


#endif
