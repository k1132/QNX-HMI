/**
 * \file
 * Fixed property types.
 * 
 * Copyright 2008-2014 by Rightware. All rights reserved.
 */
#ifndef KZU_FIXED_PROPERTIES_H
#define KZU_FIXED_PROPERTIES_H


#include <system/kzs_types.h>
#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations */
struct KzuPropertyType;
struct KzcMemoryManager;


/*lint -esym(956, KZU_PROPERTY_TYPE_*) Suppress warning of global non-const variables. */
/*lint -esym(956, KZU_MESSAGE_*) Suppress warning of global non-const variables. */

/** Fixed property type CameraAspectRatio. The aspect ratio of the camera. The default value is 1.666667f. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_CAMERA_ASPECT_RATIO;

/** Fixed property type CameraDisableAspectRatio. Whether or not to use the aspect ratio setting from the viewport in render pass. If not, the aspect ratio can be specified in the camera. The default value is KZ_TRUE. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_CAMERA_DISABLE_ASPECT_RATIO;

/** Fixed property type CameraZNear. The proximity of the near clipping plane. Objects closer to camera are not displayed. The default value is 0.1f. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_CAMERA_ZNEAR;

/** Fixed property type CameraZFar. The distance of the far clipping plane. Nothing that is farther than the far clipping plane is displayed through the camera. The default value is 100.0f. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_CAMERA_ZFAR;

/** Fixed property type CameraProjectionType. Whether to use perspective or orthographic camera. The default value is 0. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_CAMERA_PROJECTION_TYPE;

/** Fixed property type CameraOrthogonalCoordinateSystemType. ABSOLUTE / RELATIVE. In absolute mode the camera uses pixel coordinates. In relative mode the camera displays an area whose width is -1..1 scaled with orthogonal plane height. The default value is 1. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_CAMERA_ORTHOGONAL_COORDINATE_SYSTEM_TYPE;

/** Fixed property type CameraOrthogonalPlaneHeight. A value used for scaling the view area of a relative orthographic camera. The default value is 1.0f. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_CAMERA_ORTHOGONAL_PLANE_HEIGHT;

/** Fixed property type CameraFovType. Whether to specify the field-of-view in Y or X direction. The default value is 0. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_CAMERA_FOV_TYPE;

/** Fixed property type CameraFov. The field-of-view of the camera in degrees. The default value is 45.0f. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_CAMERA_FOV;

/** Fixed property type CameraOrientationAngle. The default value is 0.0f. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_CAMERA_ORIENTATION_ANGLE;

/** Fixed property type CameraScreenSpaceShift. The default value is kzcVector2(0.0f, 0.0f). */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_CAMERA_SCREEN_SPACE_SHIFT;

/** Fixed property type PreviewCameraRadius. The default value is 10.0f. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_PREVIEW_CAMERA_RADIUS;

/** Fixed property type PreviewCameraPointOfInterest. The default value is kzcVector3(0.0f, 0.0f, 0.0f). */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_PREVIEW_CAMERA_POINT_OF_INTEREST;

/** Fixed property type PreviewCameraPosition. The default value is kzcVector3(0.0f, 0.0f, 0.0f). */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_PREVIEW_CAMERA_POSITION;

/** Fixed property type Object.Path. Object full path. The default value is KZ_NULL. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_OBJECT__PATH;

/** Fixed property type Transformation. The location, orientation and scale of the node relative to its parent node. The default value is kzcMatrix4x4(1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f). */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_TRANSFORMATION;

/** Fixed property type RenderTransformation. The location, orientation and scale of the node relative to its parent node. This transform does not affect the layout of the node. The default value is kzcMatrix4x4(1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f). */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_RENDER_TRANSFORMATION;

/** Fixed property type Mesh. The mesh data asset used by the mesh node. The default value is KZ_NULL. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_MESH;

/** Fixed property type MeshMorphTarget. A morph target mesh for a mesh. Both the meshes should have similar structure and vertex count. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_MESH_MORPH_TARGET;

/** Fixed property type MeshMorphTargetWeight. A weight value for a morph target. The default value is 1.0f. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_MESH_MORPH_TARGET_WEIGHT;

/** Fixed property type MeshWeightedMorphTarget. A structure containing a mesh morph target reference and a weight for it. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_MESH_WEIGHTED_MORPH_TARGET;

/** Fixed property type MeshMorphTargets. List of weighted morph targets that each specifies a mesh data item and a weight for it. 
The targeted meshes should have the same amount clusters and vertices for morphing to make sense. 
Each vertex in the resulting morphed mesh is calculated by summing up the morph targets multiplied by their normalized weights. 
The animation of morphing weights must be performed with application code. The default value is KZU_PROPERTY_TYPE_MESH_WEIGHTED_MORPH_TARGET, KZU_ARRAY_PROPERTY_TYPE_UNLIMITED_SIZE. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_MESH_MORPH_TARGETS;

/** Fixed property type MeshMorphTargetInterpolationFormula. Specifies the formula the morph targets are interpolated. The default value is 0. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_MESH_MORPH_TARGET_INTERPOLATION_FORMULA;

/** Fixed property type MeshMorphTargetInterpolateOnGPU. Specifies if morph targets are interpolated on GPU, i.e. the CPU interpolation is skipped and shader is passed with multiple vertex attributes. The default value is KZ_FALSE. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_MESH_MORPH_TARGET_INTERPOLATE_ON_GPU;

/** Fixed property type MeshVertexIndexAccess. Enables access to the mesh vertex indices. Used with vertex attribute kzVertexIndex, where primitive type is triangle and indices are (1, 0, 0), (0, 1, 0), (0, 0, 1). Mesh needs to be stored in RAM and in Float32 format. The default value is KZ_FALSE. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_MESH_VERTEX_INDEX_ACCESS;

/** Fixed property type ComposerEnabled. This determines if composer is rendered (enabled by default). The default value is KZ_TRUE. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_COMPOSER_ENABLED;

/** Fixed property type ComposerExecutionPoint. If iterating through composers, stop at this composer and continue at the next frame. The default value is KZ_FALSE. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_COMPOSER_EXECUTION_POINT;

/** Fixed property type FlushAfterRender. This determines if GPU pipeline is flushed after rendering of this composer has occurred, to prevent GPU pipeline stall. The default value is KZ_FALSE. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_FLUSH_AFTER_RENDER;

/** Fixed property type RenderPassCamera. The default value is KZ_NULL. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_RENDER_PASS_CAMERA;

/** Fixed property type RenderPassObjectSource. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_RENDER_PASS_OBJECT_SOURCE;

/** Fixed property type RenderPassMaterial. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_RENDER_PASS_MATERIAL;

/** Fixed property type RenderPassRenderTarget. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_RENDER_PASS_RENDER_TARGET;

/** Fixed property type FrustumCullingOn. Whether or not to use frustum culling. When frustum culling is enabled the objects not overlapping with the viewing frustum of the camera are not rendered. The default value is KZ_FALSE. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_FRUSTUM_CULLING_ON;

/** Fixed property type CullMode. Whether or not to use culling of the triangle faces in the rendered meshes (NONE / BACK (Default) / FRONT). 
In backface culling the triangles whose normal points away from the camera are not rendered. 
Frontface culling drops the triangles whose normal points to the direction of the camera. The default value is 1. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_CULL_MODE;

/** Fixed property type RenderOnce. This determines if render pass is only rendered once (by default rendered every frame). The default value is KZ_FALSE. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_RENDER_ONCE;

/** Fixed property type SortBatchesByShader. This determines if render pass batches are sorted by their batches to reduce shader switches. The default value is KZ_FALSE. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_SORT_BATCHES_BY_SHADER;

/** Fixed property type ColorBufferClearColor. The color used to clear the color buffer. The default value is kzcColorRGBA(0.4f, 0.4f, 0.4f, 1.0f). */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_COLOR_BUFFER_CLEAR_COLOR;

/** Fixed property type ColorBufferClearEnabled. Whether or not to clear the color buffer before writing new color values. The default value is KZ_TRUE. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_COLOR_BUFFER_CLEAR_ENABLED;

/** Fixed property type ColorWriteMode. Options: None/RBG/RGBA. None: writing to color buffer is disabled. The default value is 2. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_COLOR_WRITE_MODE;

/** Fixed property type DepthBufferClearEnabled. Whether or not to clear depth buffer. The default value is KZ_TRUE. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_DEPTH_BUFFER_CLEAR_ENABLED;

/** Fixed property type DepthBufferClearValue. The value used for clearing the depth buffer. The default value is 1.0f. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_DEPTH_BUFFER_CLEAR_VALUE;

/** Fixed property type DepthBufferTestEnabled. Whether or not the depth test is enabled. The default value is KZ_TRUE. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_DEPTH_BUFFER_TEST_ENABLED;

/** Fixed property type DepthBufferWriteEnabled. Whether or not the writing of the depth buffer is enabled. The default value is KZ_TRUE. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_DEPTH_BUFFER_WRITE_ENABLED;

/** Fixed property type StencilBufferClearEnabled. Whether or not to clear the stencil buffer. The default value is KZ_FALSE. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_STENCIL_BUFFER_CLEAR_ENABLED;

/** Fixed property type StencilBufferClearValue. The value used for clearing the stencil buffer. The default value is 0. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_STENCIL_BUFFER_CLEAR_VALUE;

/** Fixed property type StencilFailOperation. Operation which is performed when stencil test fails. The default value is 0. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_STENCIL_FAIL_OPERATION;

/** Fixed property type StencilPassDepthFailOperation. Operation which is performed when stencil test fails and depth test passes. The default value is 0. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_STENCIL_PASS_DEPTH_FAIL_OPERATION;

/** Fixed property type StencilPassDepthPassOperation. Operation which is performed when stencil test fails and depth test fails. The default value is 0. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_STENCIL_PASS_DEPTH_PASS_OPERATION;

/** Fixed property type StencilFunction. The function used to control whether a fragment is discarded or not by the stencil test. The default value is 0. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_STENCIL_FUNCTION;

/** Fixed property type StencilFunctionReferenceValue. Specifies the reference value for the stencil test. The default value is 0. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_STENCIL_FUNCTION_REFERENCE_VALUE;

/** Fixed property type StencilFunctionReferenceMask. Specifies a mask that is ANDed with both the reference value and the stored stencil value when the test is done. The default value is 255. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_STENCIL_FUNCTION_REFERENCE_MASK;

/** Fixed property type StencilBufferTestEnabled. Whether or not the stencil test is enabled. The default value is KZ_FALSE. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_STENCIL_BUFFER_TEST_ENABLED;

/** Fixed property type RenderPassScissorEnabled. Whether scissor area is enabled in render pass or not. When scissor area is enabled rendering is done only inside the specified scissor area. The default value is KZ_FALSE. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_RENDER_PASS_SCISSOR_ENABLED;

/** Fixed property type RenderPassScissorX. X coordinate of the left border of the scissor area. The default value is 0.0f. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_RENDER_PASS_SCISSOR_X;

/** Fixed property type RenderPassScissorY. Y coordinate of the top border of the scissor area. The default value is 0.0f. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_RENDER_PASS_SCISSOR_Y;

/** Fixed property type RenderPassScissorWidth. Width of the scissor area. The default value is 1.0f. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_RENDER_PASS_SCISSOR_WIDTH;

/** Fixed property type RenderPassScissorHeight. Height of the scissor area. The default value is 1.0f. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_RENDER_PASS_SCISSOR_HEIGHT;

/** Fixed property type RenderPassAbsoluteScissorX. Absolute X coordinate of the left border of the scissor area. The default value is 0.0f. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_RENDER_PASS_ABSOLUTE_SCISSOR_X;

/** Fixed property type RenderPassAbsoluteScissorY. Absolute Y coordinate of the top border of the scissor area. The default value is 0.0f. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_RENDER_PASS_ABSOLUTE_SCISSOR_Y;

/** Fixed property type RenderPassAbsoluteScissorWidth. Absolute width of the scissor area. The default value is 480.0f. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_RENDER_PASS_ABSOLUTE_SCISSOR_WIDTH;

/** Fixed property type RenderPassAbsoluteScissorHeight. Absolute height of the scissor area. The default value is 800.0f. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_RENDER_PASS_ABSOLUTE_SCISSOR_HEIGHT;

/** Fixed property type RenderPassRelativeScissorX. Relative X coordinate of the left border of the scissor area. The default value is 0.0f. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_RENDER_PASS_RELATIVE_SCISSOR_X;

/** Fixed property type RenderPassRelativeScissorY. Relative Y coordinate of the top border of the scissor area. The default value is 0.0f. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_RENDER_PASS_RELATIVE_SCISSOR_Y;

/** Fixed property type RenderPassRelativeScissorWidth. Relative width of the scissor area. The default value is 1.0f. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_RENDER_PASS_RELATIVE_SCISSOR_WIDTH;

/** Fixed property type RenderPassRelativeScissorHeight. Relative height of the scissor area. The default value is 1.0f. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_RENDER_PASS_RELATIVE_SCISSOR_HEIGHT;

/** Fixed property type RenderPassScissorType. Whether the border settings of the scissor area are relative (range 0-1) or absolute (pixel coordinates). The default value is 1. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_RENDER_PASS_SCISSOR_TYPE;

/** Fixed property type CubemapRenderTarget. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_CUBEMAP_RENDER_TARGET;

/** Fixed property type CubemapViewNode. Node that is viewer for the cubemap. The default value is KZ_NULL. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_CUBEMAP_VIEW_NODE;

/** Fixed property type PostProcessingBloomIntensity. The intensity of the bloom effect as color. The default value is kzcColorRGBA(0.5f, 0.5f, 0.5f, 1.0f). */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_POST_PROCESSING_BLOOM_INTENSITY;

/** Fixed property type PostProcessingBloomAdditiveTexture. Texture that is added on top of screen contents texture. The default value is KZ_NULL. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_POST_PROCESSING_BLOOM_ADDITIVE_TEXTURE;

/** Fixed property type PostProcessingColorAdjustBrightness. Brightness adjustment. The default value is 1.0f. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_POST_PROCESSING_COLOR_ADJUST_BRIGHTNESS;

/** Fixed property type PostProcessingColorAdjustContrast. Contrast adjustment. The default value is 1.0f. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_POST_PROCESSING_COLOR_ADJUST_CONTRAST;

/** Fixed property type PostProcessingColorAdjustGammaCorrect. Gamma correction adjustment. The default value is 1.0f. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_POST_PROCESSING_COLOR_ADJUST_GAMMA_CORRECT;

/** Fixed property type PostProcessingColorAdjustHue. Hue adjustment. The default value is 0.0f. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_POST_PROCESSING_COLOR_ADJUST_HUE;

/** Fixed property type PostProcessingColorAdjustSaturation. Saturation adjustment. The default value is 1.0f. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_POST_PROCESSING_COLOR_ADJUST_SATURATION;

/** Fixed property type PostProcessingColorAdjustLightness. Lightness adjustment. The default value is 0.0f. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_POST_PROCESSING_COLOR_ADJUST_LIGHTNESS;

/** Fixed property type PostProcessingDOFFocusDistance. The focus distance calculated from active camera. The default value is 50.0f. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_POST_PROCESSING_DOFFOCUS_DISTANCE;

/** Fixed property type PostProcessingDOFFocusAreaLength. The depth of the focused area. The default value is 10.0f. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_POST_PROCESSING_DOFFOCUS_AREA_LENGTH;

/** Fixed property type PostProcessingDOFFocusFadeOff. The depth of areas in front of and behind of the focused area where sharpness linearly degrades to full blurriness. The default value is 10.0f. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_POST_PROCESSING_DOFFOCUS_FADE_OFF;

/** Fixed property type PostProcessingDOFTextureBlur. Blur texture. The default value is KZ_NULL. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_POST_PROCESSING_DOFTEXTURE_BLUR;

/** Fixed property type PostProcessingDOFTextureDepth. Texture that contains the depth info. The default value is KZ_NULL. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_POST_PROCESSING_DOFTEXTURE_DEPTH;

/** Fixed property type PostProcessingMotionBlurStrength. The amount of motion blur. The default value is 1.0f. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_POST_PROCESSING_MOTION_BLUR_STRENGTH;

/** Fixed property type PostProcessingRadialBlurAmount. The amount of radial blur. The default value is 0.5f. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_POST_PROCESSING_RADIAL_BLUR_AMOUNT;

/** Fixed property type PostProcessingStereoscopicRenderingMode. Stereoscopic composer produces two images; one image for both the eyes. Stereoscopic mode defines how the images are combined into the result image. The default value is 0. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_POST_PROCESSING_STEREOSCOPIC_RENDERING_MODE;

/** Fixed property type PostProcessingStereoscopicEyeDistance. The distance between cameras that take the stereoscopic image. The default value is 0.15f. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_POST_PROCESSING_STEREOSCOPIC_EYE_DISTANCE;

/** Fixed property type PostProcessingStereoscopicFocusDistance. The distance of the camera focus point from the camera. The default value is 10.0f. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_POST_PROCESSING_STEREOSCOPIC_FOCUS_DISTANCE;

/** Fixed property type PostProcessingStereoscopicEyesFlipped. Whether or not to flip the locations of the eye cameras. Can be used if the display device requires the images in opposite order. The default value is KZ_FALSE. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_POST_PROCESSING_STEREOSCOPIC_EYES_FLIPPED;

/** Fixed property type PostProcessingVignetteFadeSpeed. The length of vignette fade. The default value is 0.0f. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_POST_PROCESSING_VIGNETTE_FADE_SPEED;

/** Fixed property type PostProcessingVignettePower. The . The default value is 2.0f. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_POST_PROCESSING_VIGNETTE_POWER;

/** Fixed property type PostProcessingVignetteXScale. The default value is 1.0f. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_POST_PROCESSING_VIGNETTE_XSCALE;

/** Fixed property type PostProcessingVignetteYScale. The default value is 1.0f. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_POST_PROCESSING_VIGNETTE_YSCALE;

/** Fixed property type ShadowCasterCamera. The camera node that is used to render the shadow map. The default value is KZ_FALSE. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_SHADOW_CASTER_CAMERA;

/** Fixed property type ShadowCastingObject. The object node that will cast shadows to objects. The default value is KZ_FALSE. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_SHADOW_CASTING_OBJECT;

/** Fixed property type ShadowReceiverObject. The object node that receives the shadow. The default value is KZ_FALSE. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_SHADOW_RECEIVER_OBJECT;

/** Fixed property type ShadowDepthDefaultMaterial. The default material that the shadow map depth is rendered with. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_SHADOW_DEPTH_DEFAULT_MATERIAL;

/** Fixed property type ShadowMapDefaultMaterial. The default material that will be used for shadow mapped surfaces. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_SHADOW_MAP_DEFAULT_MATERIAL;

/** Fixed property type ShadowMapWidth. The pixel width of the shadow maps. The default value is 256. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_SHADOW_MAP_WIDTH;

/** Fixed property type ShadowMapHeight. The pixel height of the shadow maps. The default value is 256. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_SHADOW_MAP_HEIGHT;

/** Fixed property type ShadowMapVisualizeShadowMaps. When enabled, the shadow map textures are visualized. The default value is KZ_FALSE. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_SHADOW_MAP_VISUALIZE_SHADOW_MAPS;

/** Fixed property type kzLightShadowProjectionMatrix0. The matrix used for projecting the shadow map #1. The default value is kzcMatrix4x4(1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f). */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_SHADOW_PASS_PROJECTION_MATRIX_0;

/** Fixed property type kzLightShadowProjectionMatrix1. The matrix used for projecting the shadow map #2. The default value is kzcMatrix4x4(1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f). */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_SHADOW_PASS_PROJECTION_MATRIX_1;

/** Fixed property type kzLightShadowProjectionMatrix2. The matrix used for projecting the shadow map #3. The default value is kzcMatrix4x4(1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f). */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_SHADOW_PASS_PROJECTION_MATRIX_2;

/** Fixed property type kzLightShadowProjectionMatrix3. The matrix used for projecting the shadow map #4. The default value is kzcMatrix4x4(1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f). */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_SHADOW_PASS_PROJECTION_MATRIX_3;

/** Fixed property type kzLightShadowViewPosition0. The view position of the shadow viewer. The default value is kzcVector3(0.0f, 0.0f, 0.0f). */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_SHADOW_PASS_VIEW_POSITION_0;

/** Fixed property type PostProcessingBlurSpread. Defines how much the blur effect is spread. The default value is 0.5f. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_POST_PROCESSING_BLUR_SPREAD;

/** Fixed property type PostProcessingBlurRenderTargetWidth. Defines how big is the blur render target width. The default value is 256. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_POST_PROCESSING_BLUR_RENDER_TARGET_WIDTH;

/** Fixed property type PostProcessingBlurRenderTargetHeight. Defines how big is the blur render target height. The default value is 256. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_POST_PROCESSING_BLUR_RENDER_TARGET_HEIGHT;

/** Fixed property type ComposerRenderToTexture. If true, render to texture is enabled for composer. The default value is KZ_FALSE. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_COMPOSER_RENDER_TO_TEXTURE;

/** Fixed property type PostProcessingEffectBlurMaterial. Material to blur the Contents on vertical + horizontal pass. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_POST_PROCESSING_EFFECT_BLUR_MATERIAL;

/** Fixed property type PostProcessingEffectDepthMaterial. Material to assign the depth for the DOF. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_POST_PROCESSING_EFFECT_DEPTH_MATERIAL;

/** Fixed property type PostProcessingEffectBlitMaterial. Material to blit the DOF on-screen. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_POST_PROCESSING_EFFECT_BLIT_MATERIAL;

/** Fixed property type PostProcessingEffectAnaglyphicMaterial. Material to be used in anaglyphic stereoscopic rendering. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_POST_PROCESSING_EFFECT_ANAGLYPHIC_MATERIAL;

/** Fixed property type PostProcessingEffectVerticalInterlaceMaterial. Material to be used in vertical interlace stereoscopic rendering. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_POST_PROCESSING_EFFECT_VERTICAL_INTERLACE_MATERIAL;

/** Fixed property type PostProcessingEffectHorizontalInterlaceMaterial. Material to be used in horizontal interlace stereoscopic rendering. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_POST_PROCESSING_EFFECT_HORIZONTAL_INTERLACE_MATERIAL;

/** Fixed property type LightEnabled. Whether the light is on or off. The lights that are off do not affect to the rendering. The default value is KZ_TRUE. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_LIGHT_ENABLED;

/** Fixed property type DirectionalLightColor. The color of the direction light . The default value is kzcColorRGBA(0.4980392f, 0.4980392f, 0.4980392f, 1.0f). */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_DIRECTIONAL_LIGHT_COLOR;

/** Fixed property type DirectionalLightDirection. A hidden property whose value is read from the light node’s transformation. The default value is kzcVector3(0.0f, 0.0f, 0.0f). */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_DIRECTIONAL_LIGHT_DIRECTION;

/** Fixed property type PointLightColor. The color of the point light. The default value is kzcColorRGBA(0.4980392f, 0.4980392f, 0.4980392f, 1.0f). */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_POINT_LIGHT_COLOR;

/** Fixed property type PointLightAttenuation. A factor that is used to lessen the effect of the light for objects that are farther away. Consists of three coefficients. The default value is kzcVector3(1.0f, 0.0f, 0.0f). */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_POINT_LIGHT_ATTENUATION;

/** Fixed property type PointLightPosition. A hidden property whose value is read from the light node’s transformation. The default value is kzcVector3(0.0f, 0.0f, 0.0f). */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_POINT_LIGHT_POSITION;

/** Fixed property type SpotLightColor. The color of the spot light . The default value is kzcColorRGBA(0.4980392f, 0.4980392f, 0.4980392f, 1.0f). */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_SPOT_LIGHT_COLOR;

/** Fixed property type SpotLightAttenuation. A factor that is used to lessen the effect of the light for objects that are farther away. Consists of three coefficients. The default value is kzcVector3(1.0f, 0.0f, 0.0f). */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_SPOT_LIGHT_ATTENUATION;

/** Fixed property type SpotLightCutoffAngle. The angle of the light cone in degrees. The default value is 90.0f. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_SPOT_LIGHT_CUTOFF_ANGLE;

/** Fixed property type SpotLightDirection. A hidden property whose value is read from the light node’s transformation. The default value is kzcVector3(0.0f, 0.0f, 0.0f). */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_SPOT_LIGHT_DIRECTION;

/** Fixed property type SpotLightExponent. Governs how fast the fully lit area turn into non lit area. The default value is 1.0f. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_SPOT_LIGHT_EXPONENT;

/** Fixed property type SpotLightPosition. A hidden property whose value is read from the light node’s transformation. The default value is kzcVector3(0.0f, 0.0f, 0.0f). */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_SPOT_LIGHT_POSITION;

/** Fixed property type DirectionalLight. Directional light settings. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_DIRECTIONAL_LIGHT;

/** Fixed property type PointLight. Point light settings. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_POINT_LIGHT;

/** Fixed property type SpotLight. Spot light settings. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_SPOT_LIGHT;

/** Fixed property type GlobalAmbient. A color that is multiplied automatically with the "Ambient" property of the materials in the scene. The default value is kzcColorRGBA(1.0f, 1.0f, 1.0f, 1.0f). */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_GLOBAL_AMBIENT;

/** Fixed property type FogColor. The color of fog. Attached property enables overriding at render pass / scene level. The default value is kzcColorRGBA(0.4980392f, 0.4980392f, 0.4980392f, 1.0f). */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_FOG_COLOR;

/** Fixed property type FogDensity. The density of fog. Attached property enables overriding at render pass / scene level. The default value is 0.05f. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_FOG_DENSITY;

/** Fixed property type FogEnd. Fog ending distance for linear fog. Attached property enables overriding at render pass / scene level. The default value is 10.0f. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_FOG_END;

/** Fixed property type FogMode. Attached property enables overriding at render pass / scene level. The default value is 0. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_FOG_MODE;

/** Fixed property type FogStart. Fog starting distance for linear fog. Attached property enables overriding at render pass / scene level. The default value is 0.0f. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_FOG_START;

/** Fixed property type Ambient. The color of the material when no light are present. The default value is kzcColorRGBA(0.2f, 0.2f, 0.2f, 1.0f). */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_AMBIENT;

/** Fixed property type BlendIntensity. Controls the intensity how materials are blended on top of the existing color. 
Attached property enables overriding of the blend intensity of the used  materials at render pass or object node level. The default value is 1.0f. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_BLEND_INTENSITY;

/** Fixed property type BlendMode. Controls how blending is performed. Attached property enables overriding of the blend mode of the used materials at render pass or object node level. 
Use "Alpha: Automatic" setting to use premultiplied or non-premultiplied alpha depending on the value of "Use Premultiplied Alpha by Default" project setting. The default value is 0. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_BLEND_MODE;

/** Fixed property type Diffuse. The color of the material when it is lit by a light. The default value is kzcColorRGBA(0.8f, 0.8f, 0.8f, 1.0f). */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_DIFFUSE;

/** Fixed property type Emissive. The color of the light that is emitted from the material surface. The default value is kzcColorRGBA(0.0f, 0.0f, 0.0f, 1.0f). */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_EMISSIVE;

/** Fixed property type Texture. The texture of the material. The default value is KZ_NULL. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_TEXTURE;

/** Fixed property type ColorIntensity. The color intensity. The default value is kzcVector3(0.0f, 0.0f, 0.0f). */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_COLOR_INTENSITY;

/** Fixed property type ShadowMapTexture0. The shadow map slot 0 for the shadow mapped material. The default value is KZ_NULL. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_SHADOW_MAP_TEXTURE_0;

/** Fixed property type ShadowMapTexture1. The shadow map slot 1 for the shadow mapped material. The default value is KZ_NULL. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_SHADOW_MAP_TEXTURE_1;

/** Fixed property type ShadowMapTexture2. The shadow map slot 1 for the shadow mapped material. The default value is KZ_NULL. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_SHADOW_MAP_TEXTURE_2;

/** Fixed property type ShadowMapTexture3. The shadow map slot 1 for the shadow mapped material. The default value is KZ_NULL. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_SHADOW_MAP_TEXTURE_3;

/** Fixed property type SpecularColor. The color of the specular reflection. The default value is kzcColorRGBA(0.4980392f, 0.4980392f, 0.4980392f, 1.0f). */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_SPECULAR_COLOR;

/** Fixed property type SpecularExponent. Determines the size of the specular highlight. The default value is 50.0f. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_SPECULAR_EXPONENT;

/** Fixed property type PickColor. The pick color is internally set by the system and shouldn't be used manually. The default value is kzcColorRGBA(0.0f, 0.0f, 0.0f, 1.0f). */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_PICK_COLOR;

/** Fixed property type MessageArgument.ChangeRenderPassCamera.Camera. Camera property of ChangeRenderPass event handler argument. The default value is KZ_NULL. */
extern const struct KzuPropertyType* KZU_MESSAGE_ARGUMENT__CHANGE_RENDER_PASS_CAMERA__CAMERA;

/** Fixed property type MessageArgument.ChangeRenderPassCamera.RenderPass. The render pass whose camera to change. The default value is KZ_NULL. */
extern const struct KzuPropertyType* KZU_MESSAGE_ARGUMENT__CHANGE_RENDER_PASS_CAMERA__RENDER_PASS;

/** Fixed property type Message.ChangeComposer.Composer. The new composer. The default value is KZ_NULL. */
extern const struct KzuPropertyType* KZU_MESSAGE__CHANGE_COMPOSER__COMPOSER;

/** Fixed property type Message.Navigate.Target. The layer to which to navigate, will become effectively root layer of the screen. */
extern const struct KzuPropertyType* KZU_MESSAGE__NAVIGATE__TARGET;

/** Fixed property type MessageArgument.InstantiatePrefab.SourcePrefab. Source prefab template that will be instantiated. The default value is KZ_NULL. */
extern const struct KzuPropertyType* KZU_MESSAGE_ARGUMENT__INSTANTIATE_PREFAB__SOURCE_PREFAB;

/** Fixed property type MessageArgument.InstantiatePrefab.TargetNode. Target node that will be instantiated with a prefab created from the source template. The default value is KZ_NULL. */
extern const struct KzuPropertyType* KZU_MESSAGE_ARGUMENT__INSTANTIATE_PREFAB__TARGET_NODE;

/** Fixed property type MessageArgument.InstantiatePrefab.Name. Name of the new prefab instance. When using empty string, engine will generate name for the instance, if such name already exists, concatenates with _xN until unique name has been found. The default value is KZ_NULL. */
extern const struct KzuPropertyType* KZU_MESSAGE_ARGUMENT__INSTANTIATE_PREFAB__NAME;

/** Fixed property type MessageArgument.InstantiatePrefab.InstantiatingNode. Pointer of the instantiating node, by default NULL, but can be specified via API. */
extern const struct KzuPropertyType* KZU_MESSAGE_ARGUMENT__INSTANTIATE_PREFAB__INSTANTIATING_NODE;

/** Fixed property type MessageArgument.RemoveNode.TargetNode. Target node that will be removed from the scene graph, if such node is found. The default value is KZ_NULL. */
extern const struct KzuPropertyType* KZU_MESSAGE_ARGUMENT__REMOVE_NODE__TARGET_NODE;

/** Fixed property type MessageArgument.ReplaceNode.NodeToBeReplaced. Target node that will be replaced with a prefab instance. The default value is KZ_NULL. */
extern const struct KzuPropertyType* KZU_MESSAGE_ARGUMENT__REPLACE_NODE__NODE_TO_BE_REPLACED;

/** Fixed property type MessageArgument.ReplaceNode.ReplacingPrefab. Replacing prefab that will be instantiated over replaced node. The default value is KZ_NULL. */
extern const struct KzuPropertyType* KZU_MESSAGE_ARGUMENT__REPLACE_NODE__REPLACING_PREFAB;

/** Fixed property type MessageArgument.ReplaceNode.Name. Name of the replaced node. When using empty string, engine will use the name of the node that is replaced. The default value is KZ_NULL. */
extern const struct KzuPropertyType* KZU_MESSAGE_ARGUMENT__REPLACE_NODE__NAME;

/** Fixed property type MessageArgument.ReplaceNode.ReplacingNode. Pointer of the replaced node, by default NULL, but can be specified via API. */
extern const struct KzuPropertyType* KZU_MESSAGE_ARGUMENT__REPLACE_NODE__REPLACING_NODE;

/** Fixed property type MessageArgument.PreloadResources.ResourceDictionaries. Use the drop-down menu to select the resource dictionaries you want to preload. The default value is KZ_NULL. */
extern const struct KzuPropertyType* KZU_MESSAGE_ARGUMENT__PRELOAD_RESOURCES__RESOURCE_DICTIONARIES;

/** Fixed property type MessageArgument.PreloadResources.TaskName. Name of the preload task. The default value is KZ_NULL. */
extern const struct KzuPropertyType* KZU_MESSAGE_ARGUMENT__PRELOAD_RESOURCES__TASK_NAME;

/** Fixed property type MessageArgument.PreloadResources.Locale. Select the locale the resources of which you want to preload. The default value is KZ_NULL. */
extern const struct KzuPropertyType* KZU_MESSAGE_ARGUMENT__PRELOAD_RESOURCES__LOCALE;

/** Fixed property type MessageArgument.SetLocale.Locale. TODO: Add tooltip 2. The default value is KZ_NULL. */
extern const struct KzuPropertyType* KZU_MESSAGE_ARGUMENT__SET_LOCALE__LOCALE;

/** Fixed property type MessageArgument.LocaleChanged.Locale. TODO: Add tooltip 3. The default value is KZ_NULL. */
extern const struct KzuPropertyType* KZU_MESSAGE_ARGUMENT__LOCALE_CHANGED__LOCALE;

/** Fixed property type MessageArgument.RenderPass. The target render pass. The default value is KZ_NULL. */
extern const struct KzuPropertyType* KZU_MESSAGE_ARGUMENT__RENDER_PASS;

/** Fixed property type MessageArgument.RenderPassSetEnabled.IsEnabled. The new value for enabled state. The default value is KZ_FALSE. */
extern const struct KzuPropertyType* KZU_MESSAGE_ARGUMENT__RENDER_PASS_SET_ENABLED__IS_ENABLED;

/** Fixed property type MessageArgument.ChangePickingCamera.Scene. Target scene of ChangePickingCamera event handler argument. The default value is KZ_NULL. */
extern const struct KzuPropertyType* KZU_MESSAGE_ARGUMENT__CHANGE_PICKING_CAMERA__SCENE;

/** Fixed property type MessageArgument.ChangePickingCamera.Camera. Camera property of ChangePickingCamera event handler argument. The default value is KZ_NULL. */
extern const struct KzuPropertyType* KZU_MESSAGE_ARGUMENT__CHANGE_PICKING_CAMERA__CAMERA;

/** Fixed property type MessageArgument.ChangeSceneCamera.Scene. Target scene of ChangeSceneCamera event handler argument. The default value is KZ_NULL. */
extern const struct KzuPropertyType* KZU_MESSAGE_ARGUMENT__CHANGE_SCENE_CAMERA__SCENE;

/** Fixed property type MessageArgument.ChangeSceneCamera.Camera. Camera property of ChangeSceneCamera event handler argument. The default value is KZ_NULL. */
extern const struct KzuPropertyType* KZU_MESSAGE_ARGUMENT__CHANGE_SCENE_CAMERA__CAMERA;

/** Fixed property type MessageArgument.Slider.Value. The current value of a slider passed in slider events. The default value is 0.0f. */
extern const struct KzuPropertyType* KZU_MESSAGE_ARGUMENT__SLIDER__VALUE;

/** Fixed property type MessageArgument.StateManager.State. State Manager State. The default value is KZ_NULL. */
extern const struct KzuPropertyType* KZU_MESSAGE_ARGUMENT__STATE_MANAGER__STATE;

/** Fixed property type MessageArgument.StateManager.StateGroup. State Manager State Group. The default value is KZ_NULL. */
extern const struct KzuPropertyType* KZU_MESSAGE_ARGUMENT__STATE_MANAGER__STATE_GROUP;

/** Fixed property type MessageArgument.StateManager.LoopStates. Loop states. The default value is KZ_TRUE. */
extern const struct KzuPropertyType* KZU_MESSAGE_ARGUMENT__STATE_MANAGER__LOOP_STATES;

/** Fixed property type MessageArgument.ScrollView.ScrollPositionX. The X coordinate of the new scroll position of a scroll view. The default value is 0.0f. */
extern const struct KzuPropertyType* KZU_MESSAGE_ARGUMENT__SCROLL_VIEW__SCROLL_POSITION_X;

/** Fixed property type MessageArgument.ScrollView.ScrollPositionY. The Y coordinate of the new scroll position of a scroll view. The default value is 0.0f. */
extern const struct KzuPropertyType* KZU_MESSAGE_ARGUMENT__SCROLL_VIEW__SCROLL_POSITION_Y;

/** Fixed property type MessageArgument.ScrollView.ScrollPosition. The new scroll position of a scroll view. The default value is kzcVector2(0.0f,  0.0f). */
extern const struct KzuPropertyType* KZU_MESSAGE_ARGUMENT__SCROLL_VIEW__SCROLL_POSITION;

/** Fixed property type MessageArgument.ScrollView.ScrollSpeed. The new scrolling speed of a scroll view. The default value is kzcVector2(0.0f,  0.0f). */
extern const struct KzuPropertyType* KZU_MESSAGE_ARGUMENT__SCROLL_VIEW__SCROLL_SPEED;

/** Fixed property type MessageArgument.ScrollView.ScrollTarget. The target position for scrolling. The default value is kzcVector2(0.0f,  0.0f). */
extern const struct KzuPropertyType* KZU_MESSAGE_ARGUMENT__SCROLL_VIEW__SCROLL_TARGET;

/** Fixed property type MessageArgument.ScrollView.SnapPosition. The target of a snap request. The default value is kzcVector2(0.0f,  0.0f). */
extern const struct KzuPropertyType* KZU_MESSAGE_ARGUMENT__SCROLL_VIEW__SNAP_POSITION;

/** Fixed property type MessageArgument.ScrollView.SnapDirection. The direction of a snap request. The default value is kzcVector2(0.0f,  0.0f). */
extern const struct KzuPropertyType* KZU_MESSAGE_ARGUMENT__SCROLL_VIEW__SNAP_DIRECTION;

/** Fixed property type MessageArgument.ListBox.Selection. Index of selected item. Value -1 indicates no selection. The default value is -1. */
extern const struct KzuPropertyType* KZU_MESSAGE_ARGUMENT__LIST_BOX__SELECTION;

/** Fixed property type MessageArgument.ListBox.Selection1Based. Index of selected item converted to 1-based indexing. Value -1 indicates no selection. The default value is -1. */
extern const struct KzuPropertyType* KZU_MESSAGE_ARGUMENT__LIST_BOX__SELECTION_1BASED;

/** Fixed property type MessageArgument.ListBox.PreviousSelection. Index of previously selected item. Value -1 indicates no selection. The default value is -1. */
extern const struct KzuPropertyType* KZU_MESSAGE_ARGUMENT__LIST_BOX__PREVIOUS_SELECTION;

/** Fixed property type MessageArgument.ListBox.PreviousSelection1Based. Index of previously selected item converted to 1-based indexing. Value -1 indicates no selection. The default value is -1. */
extern const struct KzuPropertyType* KZU_MESSAGE_ARGUMENT__LIST_BOX__PREVIOUS_SELECTION_1BASED;

/** Fixed property type MessageArgument.ListBox.ItemIndex. Index of item that is closest to the new scroll target. The default value is -1. */
extern const struct KzuPropertyType* KZU_MESSAGE_ARGUMENT__LIST_BOX__ITEM_INDEX;

/** Fixed property type MessageArgument.ListBox.Item. Address of the message's target item. Used as a name for the target. The default value is KZ_NULL. */
extern const struct KzuPropertyType* KZU_MESSAGE_ARGUMENT__LIST_BOX__ITEM;

/** Fixed property type MessageArgument.ListBox.PreviousItem. Address of the message's previous target item. Used as a name for the target. The default value is KZ_NULL. */
extern const struct KzuPropertyType* KZU_MESSAGE_ARGUMENT__LIST_BOX__PREVIOUS_ITEM;

/** Fixed property type MessageArgument.PlayAnimation.PlaybackMode. Normal plays the animation as it is defined in the animation clip.
Ping pong first plays the animation as it is defined in the animation clip and then plays the animation in reverse.
Reverse plays the animation defined in the animation clip in reverse. The default value is 0. */
extern const struct KzuPropertyType* KZU_MESSAGE_ARGUMENT__PLAY_ANIMATION__PLAYBACK_MODE;

/** Fixed property type MessageArgument.PlayAnimation.DurationScale. Defines the duration of the animation defined in the animation clip.
For example:
- When set to 1, the animation is of the same length as it is defined in the animation clip.
- When set to 0,5, the animation is half as long as it is defined in the animation clip.
- When set to 2, the animation is twice as long as it is defined in the animation clip. The default value is 1.0f. */
extern const struct KzuPropertyType* KZU_MESSAGE_ARGUMENT__PLAY_ANIMATION__DURATION_SCALE;

/** Fixed property type MessageArgument.PlayAnimation.RepeatCount. The amount of times the target animation will be played (1 for one time playback). Endless loop can be defined using 'Infinite' checkbox. The default value is 1. */
extern const struct KzuPropertyType* KZU_MESSAGE_ARGUMENT__PLAY_ANIMATION__REPEAT_COUNT;

/** Fixed property type MessageArgument.PlayAnimation.RestoreOriginalValuesAfterPlayback. Defines whether the values of the animated properties return to their initial values when the animation in the animation clip ends. The default value is KZ_FALSE. */
extern const struct KzuPropertyType* KZU_MESSAGE_ARGUMENT__PLAY_ANIMATION__RESTORE_ORIGINAL_VALUES_AFTER_PLAYBACK;

/** Fixed property type MessageArgument.PlayAnimation.InputPropertyHostItem. The project item that contains the property from which the input is read from. The default value is KZ_NULL. */
extern const struct KzuPropertyType* KZU_MESSAGE_ARGUMENT__PLAY_ANIMATION__INPUT_PROPERTY_HOST_ITEM;

/** Fixed property type MessageArgument.PlayAnimation.InputPropertyType. The property on the input property host project item from which the input is read from. The default value is KZ_NULL. */
extern const struct KzuPropertyType* KZU_MESSAGE_ARGUMENT__PLAY_ANIMATION__INPUT_PROPERTY_TYPE;

/** Fixed property type MessageArgument.PlayAnimation.InputPropertyAttribute. The property attribute from which the input (input is always float) is read from. E.g. WHOLE_PROPERTY for float properties and TRANSLATE_X for matrix properties. The default value is 9. */
extern const struct KzuPropertyType* KZU_MESSAGE_ARGUMENT__PLAY_ANIMATION__INPUT_PROPERTY_ATTRIBUTE;

/** Fixed property type MessageArgument.PlayAnimation.Animation. The target animation. The default value is KZ_NULL. */
extern const struct KzuPropertyType* KZU_MESSAGE_ARGUMENT__PLAY_ANIMATION__ANIMATION;

/** Fixed property type MessageArgument.PlayAnimation.InputType. The type of the input for the target animation: time (default) / property. The default value is 0. */
extern const struct KzuPropertyType* KZU_MESSAGE_ARGUMENT__PLAY_ANIMATION__INPUT_TYPE;

/** Fixed property type MessageArgument.TransitionLayer.StartTransition.Mode. Where to transition to (next, previous or specify child). The default value is 0. */
extern const struct KzuPropertyType* KZU_MESSAGE_ARGUMENT__TRANSITION_LAYER__START_TRANSITION__MODE;

/** Fixed property type MessageArgument.TransitionLayer.StartTransition.TargetLayer. The target layer to transition to (if transition mode is DEFINED). The selected value must be one of the child layers of the routing target. The default value is KZ_NULL. */
extern const struct KzuPropertyType* KZU_MESSAGE_ARGUMENT__TRANSITION_LAYER__START_TRANSITION__TARGET_LAYER;

/** Fixed property type MessageArgument.TransitionLayer.TransitionStarted.SourceLayer. Source layer of the TransitionStarted message. The default value is KZ_NULL. */
extern const struct KzuPropertyType* KZU_MESSAGE_ARGUMENT__TRANSITION_LAYER__TRANSITION_STARTED__SOURCE_LAYER;

/** Fixed property type MessageArgument.TransitionLayer.TransitionStarted.TargetLayer. Transition target of the TransitionStarted message. The default value is KZ_NULL. */
extern const struct KzuPropertyType* KZU_MESSAGE_ARGUMENT__TRANSITION_LAYER__TRANSITION_STARTED__TARGET_LAYER;

/** Fixed property type MessageArgument.TransitionLayer.TransitionFinished.SourceLayer. Source layer of the TransitionFinished message. The default value is KZ_NULL. */
extern const struct KzuPropertyType* KZU_MESSAGE_ARGUMENT__TRANSITION_LAYER__TRANSITION_FINISHED__SOURCE_LAYER;

/** Fixed property type MessageArgument.TransitionLayer.TransitionFinished.TargetLayer. Transition target of the TransitionStarted message. The default value is KZ_NULL. */
extern const struct KzuPropertyType* KZU_MESSAGE_ARGUMENT__TRANSITION_LAYER__TRANSITION_FINISHED__TARGET_LAYER;

/** Fixed property type MessageArgument.SetProperty.TargetObject. The target item containing the target property. */
extern const struct KzuPropertyType* KZU_MESSAGE_ARGUMENT__SET_PROPERTY__TARGET_OBJECT;

/** Fixed property type MessageArgument.SetProperty.PropertyType. The target property. The default value is KZ_NULL. */
extern const struct KzuPropertyType* KZU_MESSAGE_ARGUMENT__SET_PROPERTY__PROPERTY_TYPE;

/** Fixed property type MessageArgument.SetProperty.PropertyAttribute. The target property part (such as vector x, y or z) . The default value is 2. */
extern const struct KzuPropertyType* KZU_MESSAGE_ARGUMENT__SET_PROPERTY__PROPERTY_ATTRIBUTE;

/** Fixed property type MessageArgument.SetProperty.BooleanValue. The new Boolean value. The default value is KZ_TRUE. */
extern const struct KzuPropertyType* KZU_MESSAGE_ARGUMENT__SET_PROPERTY__BOOLEAN_VALUE;

/** Fixed property type MessageArgument.SetProperty.TextureValue. The new texture value. The default value is KZ_NULL. */
extern const struct KzuPropertyType* KZU_MESSAGE_ARGUMENT__SET_PROPERTY__TEXTURE_VALUE;

/** Fixed property type MessageArgument.SetProperty.FloatValue. The new float value. The default value is 0.0f. */
extern const struct KzuPropertyType* KZU_MESSAGE_ARGUMENT__SET_PROPERTY__FLOAT_VALUE;

/** Fixed property type MessageArgument.SetProperty.PropertyValue. The new property value. The default value is 0.0f. */
extern const struct KzuPropertyType* KZU_MESSAGE_ARGUMENT__SET_PROPERTY__PROPERTY_VALUE;

/** Fixed property type MessageArgument.SetProperty.SourceItem. The source item. The default value is KZ_NULL. */
extern const struct KzuPropertyType* KZU_MESSAGE_ARGUMENT__SET_PROPERTY__SOURCE_ITEM;

/** Fixed property type MessageArgument.SetProperty.SourcePropertyAttribute. The source property part (such as vector x, y or z) . The default value is 2. */
extern const struct KzuPropertyType* KZU_MESSAGE_ARGUMENT__SET_PROPERTY__SOURCE_PROPERTY_ATTRIBUTE;

/** Fixed property type MessageArgument.SetProperty.TargetPath. The default value is KZ_NULL. */
extern const struct KzuPropertyType* KZU_MESSAGE_ARGUMENT__SET_PROPERTY__TARGET_PATH;

/** Fixed property type MessageArgument.Timer.BatchCount. How many times the subscription interval has passed. The default value is 1. */
extern const struct KzuPropertyType* KZU_MESSAGE_ARGUMENT__TIMER__BATCH_COUNT;

/** Fixed property type MessageArgument.WriteLog.LogMessage. The message to be written into log. The default value is KZ_NULL. */
extern const struct KzuPropertyType* KZU_MESSAGE_ARGUMENT__WRITE_LOG__LOG_MESSAGE;

/** Fixed property type MessageArgument.ChangeScene.Scene. Target scene of ChangeScene event handler argument. The default value is KZ_NULL. */
extern const struct KzuPropertyType* KZU_MESSAGE_ARGUMENT__CHANGE_SCENE__SCENE;

/** Fixed property type ColorR. The red component of the color. The default value is 0.0f. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_COLOR_R;

/** Fixed property type ColorG. The green component of the color. The default value is 0.0f. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_COLOR_G;

/** Fixed property type ColorB. The blue component of the color. The default value is 0.0f. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_COLOR_B;

/** Fixed property type ColorA. The alpha component of the color. The default value is 0.0f. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_COLOR_A;

/** Fixed property type VectorX. The x component of the vector. The default value is 0.0f. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_VECTOR_X;

/** Fixed property type VectorY. The y component of the vector. The default value is 0.0f. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_VECTOR_Y;

/** Fixed property type VectorZ. The z component of the vector. The default value is 0.0f. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_VECTOR_Z;

/** Fixed property type LayoutWidth. The width of the node when used in a layout. Overrides the default bounds of the item. The default value is 0.0f. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_LAYOUT_WIDTH;

/** Fixed property type LayoutHeight. The height of the node when used in a layout. Overrides the default bounds of the item. The default value is 0.0f. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_LAYOUT_HEIGHT;

/** Fixed property type LayoutDepth. The size of the node in depth direction when used in a layout. Overrides the default bounds of the item. The default value is 0.0f. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_LAYOUT_DEPTH;

/** Fixed property type ActualWidth. The width of the node calculated during layout. The default value is 0.0f. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_ACTUAL_WIDTH;

/** Fixed property type ActualHeight. The height of the node calculated during layout. The default value is 0.0f. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_ACTUAL_HEIGHT;

/** Fixed property type ActualDepth. The size of the node in depth calculated during layout. The default value is 0.0f. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_ACTUAL_DEPTH;

/** Fixed property type LayoutHorizontalAlignment. The alignment in horizontal direction the node should use when it resides under a layout. The default value is 2. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_LAYOUT_HORIZONTAL_ALIGNMENT;

/** Fixed property type LayoutVerticalAlignment. The alignment in vertical direction the node should use when it resides under a layout. The default value is 2. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_LAYOUT_VERTICAL_ALIGNMENT;

/** Fixed property type LayoutDepthAlignment. The alignment in depth direction the node should use when it resides under a layout. The default value is 2. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_LAYOUT_DEPTH_ALIGNMENT;

/** Fixed property type LayoutHorizontalMargin. The margin in horizontal direction the node should use when it resides under a layout. The default value is kzcVector2(0.0f, 0.0f). */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_LAYOUT_HORIZONTAL_MARGIN;

/** Fixed property type LayoutVerticalMargin. The margin in vertical direction the node should use when it resides under a layout. The default value is kzcVector2(0.0f, 0.0f). */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_LAYOUT_VERTICAL_MARGIN;

/** Fixed property type LayoutDepthMargin. The margin in depth direction the node should use when it resides under a layout. The default value is kzcVector2(0.0f, 0.0f). */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_LAYOUT_DEPTH_MARGIN;

/** Fixed property type HitTestable. When enabled, the object node can be picked from the active scene's default 3D camera. Hit testing is needed for example for the button components to work. The default value is KZ_FALSE. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_HIT_TESTABLE;

/** Fixed property type HitTestableContainer. When enabled, the layout bounds are used as the hit testing geometry. The default value is KZ_FALSE. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_HIT_TESTABLE_CONTAINER;

/** Fixed property type Visible. When disabled the scene graph node is not rendered. The default value is KZ_TRUE. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_VISIBLE;

/** Fixed property type FrustumCullMargin. Used to increase (or decrease) the margin of the frustum cull radius of given object. Useful when for example vertex shaders modify the geometry, and too early frustum culling is wanted to be prevented. The default value is 0.0f. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_FRUSTUM_CULL_MARGIN;

/** Fixed property type Enabled. When disabled, the scene graph node doesn't receive input. The default value is KZ_TRUE. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_ENABLED;

/** Fixed property type Focusable. When enabled the object node can receive focus. The default value is KZ_TRUE. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_FOCUSABLE;

/** Fixed property type Focused. When enabled the object node has focus. The default value is KZ_TRUE. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_FOCUSED;

/** Fixed property type PartialRenderingForceRender. Force partial rendering update even if object was not otherwise changed. The default value is KZ_FALSE. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_PARTIAL_RENDERING_FORCE_RENDER;

/** Fixed property type PartialRenderingStencilObject. Subtree of nodes used as stencil mesh for object in partial rendering. The default value is KZ_NULL. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_PARTIAL_RENDERING_STENCIL_OBJECT;

/** Fixed property type ObjectDepthTest. Enables or disables depth testing on per-object basis. Overrides depth test property of a render pass. The default value is KZ_TRUE. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_OBJECT_DEPTH_TEST;

/** Fixed property type ObjectDepthWrite. Enables or disables depth write on per-object basis. Overrides depth write property of a render pass. The default value is KZ_TRUE. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_OBJECT_DEPTH_WRITE;

/** Fixed property type ObjectScissorEnabled. Whether scissor area is enabled in object or not. When scissor area is enabled rendering is done only inside the specified relative scissor area. The default value is KZ_FALSE. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_OBJECT_SCISSOR_ENABLED;

/** Fixed property type ObjectScissorAreaXY. Scissor Area X and Y. The default value is kzcVector2(0.0f, 0.0f). */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_OBJECT_SCISSOR_AREA_XY;

/** Fixed property type ObjectScissorAreaWidthHeight. Scissor Area Width and Height. The default value is kzcVector2(1.0f, 1.0f). */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_OBJECT_SCISSOR_AREA_WIDTH_HEIGHT;

/** Fixed property type DrawnAsBoundingBox. When enabled the object is drawn its solid bounding box. The default value is KZ_FALSE. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_DRAWN_AS_BOUNDING_BOX;

/** Fixed property type ConstraintPosition. Makes an object node where the property is attached to obtain position from target object. The default value is KZ_NULL. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_CONSTRAINT_POSITION;

/** Fixed property type ConstraintOrientation. Makes an object node where the property is attached to obtain orientation from target object. The default value is KZ_NULL. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_CONSTRAINT_ORIENTATION;

/** Fixed property type ConstraintInWorldCoordinates. Specifies if the object constraining is done in world coordinates (when false, done in local coordinates). The default value is KZ_FALSE. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_CONSTRAINT_IN_WORLD_COORDINATES;

/** Fixed property type VisibleAmountInParent. The default value is 1.0f. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_VISIBLE_AMOUNT_IN_PARENT;

/** Fixed property type GridListBoxOffset. The default value is 0.0f. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_GRID_LIST_BOX_OFFSET;

/** Fixed property type TrajectoryOffset. The default value is 0.0f. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_TRAJECTORY_OFFSET;

/** Fixed property type StaticTrajectoryOffset. The default value is 0.0f. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_STATIC_TRAJECTORY_OFFSET;

/** Fixed property type ClipChildren. Specified whether or not the children should be clipped. Children whose bounding box is completely outside the bounding box of the parent are clipped. 
The property is to be used with layout nodes. The children should only use transformation that contain only translation. The default value is KZ_TRUE. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_CLIP_CHILDREN;

/** Fixed property type ComponentPressed. The default value is KZ_FALSE. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_COMPONENT_PRESSED;

/** Fixed property type ContentContainer. The default value is KZ_TRUE. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_CONTENT_CONTAINER;

/** Fixed property type CustomNodeTypeID. The default value is KZ_NULL. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_CUSTOM_NODE_TYPE_ID;

/** Fixed property type FaceToCamera. When enabled the object node always turns itself to face the camera. FaceToCameraIsBillboarding affects how the objects look to camera. The default value is KZ_FALSE. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_FACE_TO_CAMERA;

/** Fixed property type FaceToCameraIsBillboarding. Specifies if the object faces to camera with billboarding (matching the camera orientation with object) or by making object to look camera. The default value is KZ_TRUE. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_FACE_TO_CAMERA_IS_BILLBOARDING;

/** Fixed property type FaceToCameraCylindral. When enabled the object node always turns itself to face the camera according to cylinder in Y axis. The default value is KZ_FALSE. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_FACE_TO_CAMERA_CYLINDRAL;

/** Fixed property type FaceToCameraTargetCamera. Target camera specified for face to camera, when NULL, uses the scene default camra. The default value is KZ_NULL. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_FACE_TO_CAMERA_TARGET_CAMERA;

/** Fixed property type ToggleButtonState. When true, the toggle button is checked. The default value is KZ_TRUE. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_TOGGLE_BUTTON_STATE;

/** Fixed property type LookAt. Makes an object node where the property is attached to face another object. The default value is KZ_NULL. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_LOOK_AT;

/** Fixed property type GridLayoutDirection. The direction which the items are laid out first in the grid layout. The default value is 0. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_GRID_LAYOUT_DIRECTION;

/** Fixed property type GridLayoutColumnDefinitions. The column definitions. The default value is KZ_NULL. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_GRID_LAYOUT_COLUMN_DEFINITIONS;

/** Fixed property type GridLayoutRowDefinitions. The row definitions. The default value is KZ_NULL. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_GRID_LAYOUT_ROW_DEFINITIONS;

/** Fixed property type GridLayoutColumn. The column under which the scene graph node shall be put into when residing under grid layout. The default value is 0. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_GRID_LAYOUT_COLUMN;

/** Fixed property type GridLayoutColumnSpan. The amount of columns a node that is under a grid layout occupies. The default value is 1. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_GRID_LAYOUT_COLUMN_SPAN;

/** Fixed property type GridLayoutRow. The row under which the scene graph node shall be put into when residing under grid layout. The default value is 0. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_GRID_LAYOUT_ROW;

/** Fixed property type GridLayoutRowSpan. The amount of rows the node that is under a grid layout occupies. The default value is 1. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_GRID_LAYOUT_ROW_SPAN;

/** Fixed property type ScrollViewScrollAxis. Direction of Scroll View's primary axis. The default value is kzcVector2(1.0f,  0.0f). */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_SCROLL_VIEW_SCROLL_AXIS;

/** Fixed property type ScrollViewRecognitionThreshold. How much the pointing device has to move for scrolling to start. The default value is 5.0f. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_SCROLL_VIEW_RECOGNITION_THRESHOLD;

/** Fixed property type ScrollViewSensitivity. How much the scroll value changes relative to pointing device movement on the scroll view plane. The default value is 1.0f. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_SCROLL_VIEW_SENSITIVITY;

/** Fixed property type ScrollViewSlidingAccelerationCoefficient. How fast scrolling accelerates when sliding. The default value is 40.0f. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_SCROLL_VIEW_SLIDING_ACCELERATION_COEFFICIENT;

/** Fixed property type ScrollViewSlidingDragCoefficient. How much drag affects scrolling when sliding. The default value is 80.0f. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_SCROLL_VIEW_SLIDING_DRAG_COEFFICIENT;

/** Fixed property type ScrollViewDraggingAccelerationCoefficient. How fast scrolling accelerates when dragging. The default value is 80.0f. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_SCROLL_VIEW_DRAGGING_ACCELERATION_COEFFICIENT;

/** Fixed property type ScrollViewDraggingDragCoefficient. How much drag affects scrolling when dragging. The default value is 150.0f. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_SCROLL_VIEW_DRAGGING_DRAG_COEFFICIENT;

/** Fixed property type ScrollViewDraggingImpulseFactor. How much impulse is generated from pointing device movement when dragging. The default value is 2.0f. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_SCROLL_VIEW_DRAGGING_IMPULSE_FACTOR;

/** Fixed property type ScrollViewSwipeDistance. How far a swipe sends the scroll value, relative to pointing device speed. The default value is 0.005f. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_SCROLL_VIEW_SWIPE_DISTANCE;

/** Fixed property type ScrollViewScrollPosition. The current scroll value (read-only). The default value is kzcVector2(0.0f,  0.0f). */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_SCROLL_VIEW_SCROLL_POSITION;

/** Fixed property type ScrollViewScrollTargetPosition. The current target scroll value (read-only). The default value is kzcVector2(0.0f,  0.0f). */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_SCROLL_VIEW_SCROLL_TARGET_POSITION;

/** Fixed property type ScrollViewScrollSpeed. The current scroll speed (read-only). The default value is kzcVector2(0.0f,  0.0f). */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_SCROLL_VIEW_SCROLL_SPEED;

/** Fixed property type ScrollViewScrolling. Is the scroll view currently scrolling (read-only). The default value is KZ_FALSE. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_SCROLL_VIEW_SCROLLING;

/** Fixed property type ListBoxKeepAliveItemCount. Size of the buffer for invisible list box items. Invisible items that don't fit the buffer are returned to the Object Generator. The default value is 20000000. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_LIST_BOX_KEEP_ALIVE_ITEM_COUNT;

/** Fixed property type ListBoxLoopAlongX. Is list box looping (X axis). The default value is KZ_FALSE. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_LIST_BOX_LOOP_ALONG_X;

/** Fixed property type ListBoxLoopAlongY. Is list box looping (Y axis). The default value is KZ_FALSE. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_LIST_BOX_LOOP_ALONG_Y;

/** Fixed property type ListBoxSelectionBehavior. Specifies the behavior for the list box scroll when an item is clicked. The default value is 0. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_LIST_BOX_SELECTION_BEHAVIOR;

/** Fixed property type ListBoxObjectGeneratorTypeName. Name of the object generator type to use for providing items dynamically to the list box. The default value is "DefaultObjectGenerator". */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_LIST_BOX_OBJECT_GENERATOR_TYPE_NAME;

/** Fixed property type ListBoxItemContainerGeneratorTypeName. Name of the item container generator type to use for providing item containers dynamically for the list box. The default value is "DefaultItemContainerGenerator". */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_LIST_BOX_ITEM_CONTAINER_GENERATOR_TYPE_NAME;

/** Fixed property type ListBoxItemPrototype. If set, the prototype prefab overrides list box item sizes in layouting. The default value is KZ_NULL. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_LIST_BOX_ITEM_PROTOTYPE;

/** Fixed property type ListBoxItemContainerTemplate. If set, the the default item container generator uses this to instantiate item containers. The default value is KZ_NULL. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_LIST_BOX_ITEM_CONTAINER_TEMPLATE;

/** Fixed property type GridListBoxDirection. The direction which the items are laid out first in the grid list box. The default value is 0. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_GRID_LIST_BOX_DIRECTION;

/** Fixed property type GridListBoxCellWidth. Width of one list box cell. The default value is 1.0f. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_GRID_LIST_BOX_CELL_WIDTH;

/** Fixed property type GridListBoxCellHeight. Height of one list box cell. The default value is 1.0f. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_GRID_LIST_BOX_CELL_HEIGHT;

/** Fixed property type GridListBoxItemAreaBegin. Proportional offset where the area meant for items starts. The default value is 0.0f. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_GRID_LIST_BOX_ITEM_AREA_BEGIN;

/** Fixed property type GridListBoxItemAreaEnd. Proportional offset where the area meant for items ends. The default value is 1.0f. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_GRID_LIST_BOX_ITEM_AREA_END;

/** Fixed property type GridListBoxScrollAxis. Direction of Scroll View's primary axis. The default value is kzcVector2(1.0f,  0.0f). */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_GRID_LIST_BOX_SCROLL_AXIS;

/** Fixed property type GridListBoxRecognitionThreshold. How much the pointing device has to move for scrolling to start. The default value is 5.0f. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_GRID_LIST_BOX_RECOGNITION_THRESHOLD;

/** Fixed property type GridListBoxSensitivity. How much the scroll value changes relative to pointing device movement on the scroll view plane. The default value is 1.0f. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_GRID_LIST_BOX_SENSITIVITY;

/** Fixed property type GridListBoxSlidingAccelerationCoefficient. How fast scrolling accelerates when sliding. The default value is 40.0f. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_GRID_LIST_BOX_SLIDING_ACCELERATION_COEFFICIENT;

/** Fixed property type GridListBoxSlidingDragCoefficient. How much drag affects scrolling when sliding. The default value is 80.0f. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_GRID_LIST_BOX_SLIDING_DRAG_COEFFICIENT;

/** Fixed property type GridListBoxDraggingAccelerationCoefficient. How fast scrolling accelerates when dragging. The default value is 80.0f. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_GRID_LIST_BOX_DRAGGING_ACCELERATION_COEFFICIENT;

/** Fixed property type GridListBoxDraggingDragCoefficient. How much drag affects scrolling when dragging. The default value is 150.0f. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_GRID_LIST_BOX_DRAGGING_DRAG_COEFFICIENT;

/** Fixed property type GridListBoxDraggingImpulseFactor. How much impulse is generated from pointing device movement when dragging. The default value is 2.0f. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_GRID_LIST_BOX_DRAGGING_IMPULSE_FACTOR;

/** Fixed property type GridListBoxSwipeDistance. How far a swipe sends the scroll value, relative to pointing device speed. The default value is 0.005f. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_GRID_LIST_BOX_SWIPE_DISTANCE;

/** Fixed property type TrajectoryListBoxTrajectory. The trajectory to use. The default value is KZ_NULL. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_TRAJECTORY_LIST_BOX_TRAJECTORY;

/** Fixed property type TrajectoryListBoxClipStartOffsetProportional. Offset of starting point of the area in which the child object is fully visible. Used for property VisibleAmountInParent. The default value is 0.0f. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_TRAJECTORY_LIST_BOX_CLIP_START_OFFSET_PROPORTIONAL;

/** Fixed property type TrajectoryListBoxClipEndOffsetProportional. Offset of ending point of the area in which the child object is fully visible. Used for property VisibleAmountInParent. The default value is 1.0f. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_TRAJECTORY_LIST_BOX_CLIP_END_OFFSET_PROPORTIONAL;

/** Fixed property type TrajectoryListBoxAlignToTangent. If set, aligns laid out items to match the trajectory's tangent. Vertical trajectories are not supported. The default value is KZ_FALSE. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_TRAJECTORY_LIST_BOX_ALIGN_TO_TANGENT;

/** Fixed property type TrajectoryListBoxSpacing. Distance between items in trajectory list box. The default value is 0.0f. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_TRAJECTORY_LIST_BOX_SPACING;

/** Fixed property type TrajectoryListBoxSelectorOffsetProportional. Offset of the position that is used for selecting the active object, in proportional range [0,1]. The default value is 0.5f. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_TRAJECTORY_LIST_BOX_SELECTOR_OFFSET_PROPORTIONAL;

/** Fixed property type TrajectoryListBoxScrollAxis. Direction of Scroll View's primary axis. The default value is kzcVector2(1.0f,  0.0f). */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_TRAJECTORY_LIST_BOX_SCROLL_AXIS;

/** Fixed property type TrajectoryListBoxRecognitionThreshold. How much the pointing device has to move for scrolling to start. The default value is 5.0f. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_TRAJECTORY_LIST_BOX_RECOGNITION_THRESHOLD;

/** Fixed property type TrajectoryListBoxSensitivity. How much the scroll value changes relative to pointing device movement on the scroll view plane. The default value is 1.0f. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_TRAJECTORY_LIST_BOX_SENSITIVITY;

/** Fixed property type TrajectoryListBoxSlidingAccelerationCoefficient. How fast scrolling accelerates when sliding. The default value is 40.0f. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_TRAJECTORY_LIST_BOX_SLIDING_ACCELERATION_COEFFICIENT;

/** Fixed property type TrajectoryListBoxSlidingDragCoefficient. How much drag affects scrolling when sliding. The default value is 80.0f. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_TRAJECTORY_LIST_BOX_SLIDING_DRAG_COEFFICIENT;

/** Fixed property type TrajectoryListBoxDraggingAccelerationCoefficient. How fast scrolling accelerates when dragging. The default value is 80.0f. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_TRAJECTORY_LIST_BOX_DRAGGING_ACCELERATION_COEFFICIENT;

/** Fixed property type TrajectoryListBoxDraggingDragCoefficient. How much drag affects scrolling when dragging. The default value is 150.0f. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_TRAJECTORY_LIST_BOX_DRAGGING_DRAG_COEFFICIENT;

/** Fixed property type TrajectoryListBoxDraggingImpulseFactor. How much impulse is generated from pointing device movement when dragging. The default value is 2.0f. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_TRAJECTORY_LIST_BOX_DRAGGING_IMPULSE_FACTOR;

/** Fixed property type TrajectoryListBoxSwipeDistance. How far a swipe sends the scroll value, relative to pointing device speed. The default value is 0.005f. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_TRAJECTORY_LIST_BOX_SWIPE_DISTANCE;

/** Fixed property type Trajectory. The trajectory to use. The default value is KZ_NULL. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_TRAJECTORY;

/** Fixed property type TrajectoryLayoutClipStartOffsetProportional. Offset of starting point of the area in which the child object is fully visible. Used for property VisibleAmountInParent. The default value is 0.0f. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_TRAJECTORY_LAYOUT_CLIP_START_OFFSET_PROPORTIONAL;

/** Fixed property type TrajectoryLayoutClipEndOffsetProportional. Offset of ending point of the area in which the child object is fully visible. Used for property VisibleAmountInParent. The default value is 1.0f. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_TRAJECTORY_LAYOUT_CLIP_END_OFFSET_PROPORTIONAL;

/** Fixed property type TrajectoryLayoutFixedDistance. If set, the given fixed distance between objects in the trajectory layout, in length units. The default value is 1.0f. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_TRAJECTORY_LAYOUT_FIXED_DISTANCE;

/** Fixed property type TrajectoryLayoutScrollOffsetProportional. Scrolling offset of a trajectory layout, in proportional range [0,1]. The default value is 0.0f. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_TRAJECTORY_LAYOUT_SCROLL_OFFSET_PROPORTIONAL;

/** Fixed property type TrajectoryLayoutAlignToTangent. If set, aligns laid out items to match the trajectory's tangent. Vertical trajectories are not supported. The default value is KZ_FALSE. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_TRAJECTORY_LAYOUT_ALIGN_TO_TANGENT;

/** Fixed property type SceneBackgroundTimelineSequence. The animation sequence to play in the scene. Dynamic animations are added at runtime to this sequence. The default value is KZ_NULL. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_SCENE_BACKGROUND_TIMELINE_SEQUENCE;

/** Fixed property type SceneStartupScriptFunctionName. The default value is KZ_NULL. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_SCENE_STARTUP_SCRIPT_FUNCTION_NAME;

/** Fixed property type SceneDefaultPickingCamera. The camera used in picking the objects in the scene. When not set, the default camera is used. The default value is KZ_NULL. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_SCENE_DEFAULT_PICKING_CAMERA;

/** Fixed property type SceneDefaultCamera. The default camera for displaying the scene in the viewport. The camera can be overridden with the render pass camera or in Studio with the preview camera. The default value is KZ_NULL. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_SCENE_DEFAULT_CAMERA;

/** Fixed property type ComposerReference. The default value is KZ_NULL. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_COMPOSER_REFERENCE;

/** Fixed property type GestureRecognizer.Click. Whether or not to enable detection of clicks. The default value is KZ_FALSE. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_GESTURE_RECOGNIZER__CLICK;

/** Fixed property type GestureRecognizer.MultiClick. Whether or not to enable detection of multi-clicks. Detection of multi-clicks introduces a small lag for detecting single-clicks. The default value is KZ_FALSE. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_GESTURE_RECOGNIZER__MULTI_CLICK;

/** Fixed property type Button.Pressed. When true, the button is in pressed-down state. The default value is KZ_FALSE. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_BUTTON__PRESSED;

/** Fixed property type ButtonLongPressInterval. Button long press happens after this delay (milliseconds, 0 means off). The default value is 0.0f. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_BUTTON_LONG_PRESS_INTERVAL;

/** Fixed property type ButtonDownOnHover. When true, hovering a pointer over button makes it go into pressed-down state. The default value is KZ_FALSE. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_BUTTON_DOWN_ON_HOVER;

/** Fixed property type ButtonRepeatInterval. An interval in milliseconds. Every time the specified time has passed and button has been held down, a 'Click' message is published. The default value is 0.0f. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_BUTTON_REPEAT_INTERVAL;

/** Fixed property type ButtonToggleState. The current toggle state of the button. The default value is 0. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_BUTTON_TOGGLE_STATE;

/** Fixed property type ButtonToggleStateCount. The number of toggle states of the button. The default value is 0. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_BUTTON_TOGGLE_STATE_COUNT;

/** Fixed property type Font. The font to be used for rendering the text. The default value is KZ_NULL. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_FONT;

/** Fixed property type FontSize. The size of the font in device independent pixels (DIP). The default value is 36.0f. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_FONT_SIZE;

/** Fixed property type FontMaterial. The material whose shader is used to render the text. The shader needs to include GlyphTexture uniform to be able to be used. 
An example of this kind of shader can be found by loading General/FontTexture.kzmat material type. The default value is KZ_NULL. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_FONT_MATERIAL;

/** Fixed property type FontColor. The color of the text. The default value is kzcColorRGBA(1.0f, 1.0f, 1.0f, 1.0f). */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_FONT_COLOR;

/** Fixed property type GlyphTexture. The automatic texture of the glyph cache. The default value is KZ_NULL. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_GLYPH_TEXTURE;

/** Fixed property type Text.HorizontalAlignment. Determines how the text is aligned horizontally inside the component. The default value is 0. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_TEXT__HORIZONTAL_ALIGNMENT;

/** Fixed property type Text.VerticalAlignment. Determines how the text is aligned vertically inside the component. The default value is 0. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_TEXT__VERTICAL_ALIGNMENT;

/** Fixed property type Text.LineSpacing. The spacing of lines in measures of line height. The default value is 1.0f. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_TEXT__LINE_SPACING;

/** Fixed property type Text.CharacterSpacing. The spacing of characters in device independent pixels (DIP). The default value is 0.0f. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_TEXT__CHARACTER_SPACING;

/** Fixed property type Text.Overflow. The text that represents the clipped text when the text doesn't fit to the layout. The default value is KZ_NULL. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_TEXT__OVERFLOW;

/** Fixed property type Text.FixedCharacterWidth. The width of characters in device independent pixels (DIP).
Use this property to turn any font into a monospaced font. The default value is 18.0f. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_TEXT__FIXED_CHARACTER_WIDTH;

/** Fixed property type TextBlock.TextResource. The text resource to be rendered. Overrides text property. The default value is KZ_NULL. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_TEXT_BLOCK__TEXT_RESOURCE;

/** Fixed property type TextBlock.Text. The text to be rendered. Use Shift+enter for a line break. The default value is "<Text>". */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_TEXT_BLOCK__TEXT;

/** Fixed property type TextBlock.LineHeight. The height of a text line in 3D space units. The default value is 1.25f. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_TEXT_BLOCK__LINE_HEIGHT;

/** Fixed property type TextBlock.TwoPassRendering. Specified whether or not text block is rendered in two passes. Disabling the two pass rendering improves performance, but may cause invalid rendering result when glyph bounds overlap. The default value is KZ_TRUE. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_TEXT_BLOCK__TWO_PASS_RENDERING;

/** Fixed property type TextLayer.TextResource. The text resource to be rendered. Overrides text property. The default value is KZ_NULL. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_TEXT_LAYER__TEXT_RESOURCE;

/** Fixed property type TextLayer.Text. The text to be rendered. The default value is "<Text>". */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_TEXT_LAYER__TEXT;

/** Fixed property type SliderValue. The value of the slider. The default value is 0.5f. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_SLIDER_VALUE;

/** Fixed property type SliderMinimumValue.  The value of the slider when the knob is in its lowest value. The default value is 0.0f. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_SLIDER_MINIMUM_VALUE;

/** Fixed property type SliderMaximumValue. The value of the slider when the knob is in its largest value. The default value is 1.0f. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_SLIDER_MAXIMUM_VALUE;

/** Fixed property type SliderDirection. The direction into which the knob can be moved on the rail. Options X, Y, Z. The default value is 0. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_SLIDER_DIRECTION;

/** Fixed property type SliderExpandDirection. Expands the volume where slider dragging is registered. When dragging the slider the drag is registered, by default, only when the drag is over the rail. 
When a certain axis is selected for expanding the bounding box of the rail that is used for dragging is expanded to be infinite to that direction. The default value is 0. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_SLIDER_EXPAND_DIRECTION;

/** Fixed property type SliderInvertDirection. Whether or not to invert the slider direction. Normally value increases to the direction of axis. The default value is KZ_FALSE. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_SLIDER_INVERT_DIRECTION;

/** Fixed property type WindowMetricsType. Absolute / Relative (default). The default value is 1. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_WINDOW_METRICS_TYPE;

/** Fixed property type WindowWidth. A relative value between [0,1] / an absolute number of pixels for window width. The default value is 1.0f. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_WINDOW_WIDTH;

/** Fixed property type WindowHeight. A relative value between [0,1] / an absolute number of pixels for window height. The default value is 1.0f. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_WINDOW_HEIGHT;

/** Fixed property type ScreenOrientation. Landscape / Portrait. The default value is 0. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_SCREEN_ORIENTATION;

/** Fixed property type LayerRenderOnDemand. Specifies if layer and its children are only rendered when needed, saving the performance. The default value is KZ_FALSE. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_LAYER_RENDER_ON_DEMAND;

/** Fixed property type ImageLayerTexture. Texture to use on this image layer, preferred over the image if present. The default value is KZ_NULL. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_IMAGE_LAYER_TEXTURE;

/** Fixed property type NinePatchLayerTypeTop. Control the display of the top texture:
- Stretch. Scale the texture to fill the space between the top-left and top-right textures.
- Wrap. When the width of the space between the top-left and top-right textures exceeds
the width of the texture, either extend the last column of pixels in the texture or tile the texture.
Depends on the value of the texture's Wrap Mode property. The default value is 1. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_NINE_PATCH_LAYER_TYPE_TOP;

/** Fixed property type NinePatchLayerTypeBottom. Control the display of the bottom texture:
- Stretch. Scale the texture to fill the space between the bottom-left and bottom-right textures.
- Wrap. When the width of the space between the bottom-left and bottom-right textures exceeds
the width of the texture, either extend the last column of pixels in the texture or tile the texture.
Depends on the value of the texture's Wrap Mode property. The default value is 1. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_NINE_PATCH_LAYER_TYPE_BOTTOM;

/** Fixed property type NinePatchLayerTypeLeft. Control the display of the left texture:
- Stretch. Scale the texture to fill the space between the top-left and bottom-left textures.
- Wrap. When the height of the space between the top-left and bottom-left textures exceeds
the height of the texture, either extend the last row of pixels in the texture or tile the texture.
Depends on the value of the texture's Wrap Mode property. The default value is 1. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_NINE_PATCH_LAYER_TYPE_LEFT;

/** Fixed property type NinePatchLayerTypeRight. Control the display of the right texture:
- Stretch. Scale the texture to fill the space between the top-right and bottom-right textures.
- Wrap. When the height of the space between the top-right and bottom-right textures exceeds
the height of the texture, either extend the last row of pixels in the texture or tile the texture.
Depends on the value of the texture's Wrap Mode property. The default value is 1. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_NINE_PATCH_LAYER_TYPE_RIGHT;

/** Fixed property type NinePatchLayerTypeCenter. Control the display of the center texture:
- Stretch. Scale the texture to fill the width and height of the center of the nine-patch layer.
- Wrap. When the height and width of the center exceed the size of the texture, either
extend the last row or column of pixels in the texture or tile the texture.
Depends on the value of the texture's Wrap Mode property. The default value is 1. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_NINE_PATCH_LAYER_TYPE_CENTER;

/** Fixed property type NinePatchLayerTextureTopLeft. Texture to use on the top-left corner. The default value is KZ_NULL. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_NINE_PATCH_LAYER_TEXTURE_TOP_LEFT;

/** Fixed property type NinePatchLayerTextureTop. Texture to use on middle of the top row. The default value is KZ_NULL. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_NINE_PATCH_LAYER_TEXTURE_TOP;

/** Fixed property type NinePatchLayerTextureTopRight. Texture to use on the top-right corner. The default value is KZ_NULL. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_NINE_PATCH_LAYER_TEXTURE_TOP_RIGHT;

/** Fixed property type NinePatchLayerTextureLeft. Texture to use on the center-left. The default value is KZ_NULL. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_NINE_PATCH_LAYER_TEXTURE_LEFT;

/** Fixed property type NinePatchLayerTextureCenter. Texture to use on the center. The default value is KZ_NULL. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_NINE_PATCH_LAYER_TEXTURE_CENTER;

/** Fixed property type NinePatchLayerTextureRight. Texture to use on the center-right. The default value is KZ_NULL. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_NINE_PATCH_LAYER_TEXTURE_RIGHT;

/** Fixed property type NinePatchLayerTextureBottomLeft. Texture to use on the bottom-left corner. The default value is KZ_NULL. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_NINE_PATCH_LAYER_TEXTURE_BOTTOM_LEFT;

/** Fixed property type NinePatchLayerTextureBottom. Texture to use on middle of the bottom row. The default value is KZ_NULL. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_NINE_PATCH_LAYER_TEXTURE_BOTTOM;

/** Fixed property type NinePatchLayerTextureBottomRight. Texture to use on the bottom-right corner. The default value is KZ_NULL. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_NINE_PATCH_LAYER_TEXTURE_BOTTOM_RIGHT;

/** Fixed property type StackLayoutDirection. The direction along which the child nodes are arranged. The default value is 0. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_STACK_LAYOUT_DIRECTION;

/** Fixed property type StackLayoutReversed. When true, the direction of the layout is reversed. The default value is KZ_FALSE. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_STACK_LAYOUT_REVERSED;

/** Fixed property type FlowLayoutPrimaryDirection. The direction along which the child nodes are arranged until the layout width is reached. The default value is 0. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_FLOW_LAYOUT_PRIMARY_DIRECTION;

/** Fixed property type FlowLayoutSecondaryDirection. The direction along which the flow layout grows after the primary direction does not have space. The default value is 2. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_FLOW_LAYOUT_SECONDARY_DIRECTION;

/** Fixed property type FlowLayerPrimaryDirection. The direction along which the child layers are arranged until the layout width is reached. The default value is 0. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_FLOW_LAYER_PRIMARY_DIRECTION;

/** Fixed property type FlowLayerSecondaryDirection. The direction along which the layout grows after the primary direction does not have space. The default value is 2. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_FLOW_LAYER_SECONDARY_DIRECTION;

/** Fixed property type DockLayoutLastChildFill. When true, the last child of the dock layout is given all the remaining free space. The default value is KZ_FALSE. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_DOCK_LAYOUT_LAST_CHILD_FILL;

/** Fixed property type DockLayoutDockingSide. The docking side of a child of the dock layout. The default value is 0. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_DOCK_LAYOUT_DOCKING_SIDE;

/** Fixed property type ScrollLayerScrollAxis. Direction of Scroll layer's primary axis. The default value is kzcVector2(1.0f,  0.0f). */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_SCROLL_LAYER_SCROLL_AXIS;

/** Fixed property type ScrollLayerRecognitionThreshold. How much the pointing device has to move for scrolling to start. The default value is 5.0f. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_SCROLL_LAYER_RECOGNITION_THRESHOLD;

/** Fixed property type ScrollLayerSensitivity. How much the scroll value changes relative to pointing device movement on the scroll view plane. The default value is 10.0f. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_SCROLL_LAYER_SENSITIVITY;

/** Fixed property type ScrollLayerSlidingAccelerationCoefficient. How fast scrolling accelerates when sliding. The default value is 40.0f. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_SCROLL_LAYER_SLIDING_ACCELERATION_COEFFICIENT;

/** Fixed property type ScrollLayerSlidingDragCoefficient. How much drag affects scrolling when sliding. The default value is 80.0f. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_SCROLL_LAYER_SLIDING_DRAG_COEFFICIENT;

/** Fixed property type ScrollLayerDraggingAccelerationCoefficient. How fast scrolling accelerates when dragging. The default value is 80.0f. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_SCROLL_LAYER_DRAGGING_ACCELERATION_COEFFICIENT;

/** Fixed property type ScrollLayerDraggingDragCoefficient. How much drag affects scrolling when dragging. The default value is 150.0f. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_SCROLL_LAYER_DRAGGING_DRAG_COEFFICIENT;

/** Fixed property type ScrollLayerDraggingImpulseFactor. How much impulse is generated from pointing device movement when dragging. The default value is 2.0f. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_SCROLL_LAYER_DRAGGING_IMPULSE_FACTOR;

/** Fixed property type ScrollLayerSwipeDistance. How far a swipe sends the scroll value, relative to pointing device speed. The default value is 0.005f. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_SCROLL_LAYER_SWIPE_DISTANCE;

/** Fixed property type ScrollLayerScrollPosition. The current scroll value (read-only). The default value is kzcVector2(0.0f,  0.0f). */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_SCROLL_LAYER_SCROLL_POSITION;

/** Fixed property type ScrollLayerScrollTargetPosition. The current target scroll value (read-only). The default value is kzcVector2(0.0f,  0.0f). */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_SCROLL_LAYER_SCROLL_TARGET_POSITION;

/** Fixed property type ScrollLayerScrollSpeed. The current scroll speed (read-only). The default value is kzcVector2(0.0f,  0.0f). */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_SCROLL_LAYER_SCROLL_SPEED;

/** Fixed property type ScrollLayerScrolling. Is the scroll layer currently scrolling (read-only). The default value is KZ_FALSE. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_SCROLL_LAYER_SCROLLING;

/** Fixed property type TransitionLayerAnimation. Animation to use for the transition. The default value is KZ_NULL. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_TRANSITION_LAYER_ANIMATION;

/** Fixed property type TransitionLayerDuration. Duration of the transition in seconds. Only meaningful if using default linear animation that is created if animation clip is not specified. The default value is 1.0f. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_TRANSITION_LAYER_DURATION;

/** Fixed property type TransitionLayerTexture0. First texture of transition layer material. The default value is KZ_NULL. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_TRANSITION_LAYER_TEXTURE_0;

/** Fixed property type TransitionLayerTexture1. Second texture of transition layer material. The default value is KZ_NULL. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_TRANSITION_LAYER_TEXTURE_1;

/** Fixed property type TransitionLayerContentTexcoord0. First content texture coordinates of transition layer material. The default value is kzcVector4(0.0f, 0.0f, 1.0f, 1.0f). */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_TRANSITION_LAYER_CONTENT_TEXCOORD_0;

/** Fixed property type TransitionLayerContentTexcoord1. Second content texture coordinates of transition layer material. The default value is kzcVector4(0.0f, 0.0f, 1.0f, 1.0f). */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_TRANSITION_LAYER_CONTENT_TEXCOORD_1;

/** Fixed property type TransitionLayerPhase. Phase of the transition in range [0,1] from source layer to target layer. Can be controlled either via program code or using animation. The default value is 0.0f. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_TRANSITION_LAYER_PHASE;

/** Fixed property type TransitionLayerSource. The source layer from which the transition is performed to the target layer. The default value is KZ_NULL. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_TRANSITION_LAYER_SOURCE;

/** Fixed property type TransitionLayerTarget. The target layer to perform transition into from the source layer. The default value is KZ_NULL. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_TRANSITION_LAYER_TARGET;

/** Fixed property type TransitionLayerMaterial. The material whose shader is used in transition. The shader must contain texture uniforms by names 
 specified in "Uniform Name for First Texture" and "Uniform Name for Second Texture" properties 
and a float uniform with name specified by "Uniform Name for Phase" property. The default value is KZ_NULL. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_TRANSITION_LAYER_MATERIAL;

/** Fixed property type TransitionLayerMaterialFirstTexture. The name of the first texture uniform in a transition layer shader. The default value is "TransitionLayerTexture0". */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_TRANSITION_LAYER_MATERIAL_FIRST_TEXTURE;

/** Fixed property type TransitionLayerMaterialSecondTexture. The name of the second texture uniform in a transition layer shader. The default value is "TransitionLayerTexture1". */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_TRANSITION_LAYER_MATERIAL_SECOND_TEXTURE;

/** Fixed property type TransitionLayerMaterialFirstContentTexcoord. The name of the first content texcoord uniform in a transition layer shader. The default value is "TransitionLayerContentTexcoord0". */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_TRANSITION_LAYER_MATERIAL_FIRST_CONTENT_TEXCOORD;

/** Fixed property type TransitionLayerMaterialSecondContentTexcoord. The name of the second content texcoord uniform in a transition layer shader. The default value is "TransitionLayerContentTexcoord1". */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_TRANSITION_LAYER_MATERIAL_SECOND_CONTENT_TEXCOORD;

/** Fixed property type StepRenderingLayerScene. Scene that step rendering renders. The default value is KZ_NULL. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_STEP_RENDERING_LAYER_SCENE;

/** Fixed property type StepRenderingLayerTriangleLimit. Triangle limit after which the next frame is executed. The default value is 5000. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_STEP_RENDERING_LAYER_TRIANGLE_LIMIT;

/** Fixed property type StepRenderingLayerBatchLimit. Batch limit after which the next frame is executed. The default value is 1. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_STEP_RENDERING_LAYER_BATCH_LIMIT;

/** Fixed property type StepRenderingLayerVisualizeSteps. When enabled, the steps construction is visualized. The default value is KZ_FALSE. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_STEP_RENDERING_LAYER_VISUALIZE_STEPS;

/** Fixed property type LayerAspectRatio. User defined layer aspect ratio. This setting determines the proportion of width and height. If both those settings are fixed, the aspect ratio is ignored. The default value is 1.0f. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_LAYER_ASPECT_RATIO;

/** Fixed property type LayerCacheChildren. Cache layer's children into a render target, also see Layer Cache Self. The default value is KZ_FALSE. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_LAYER_CACHE_CHILDREN;

/** Fixed property type LayerCacheResult. Cache layer's final result (combination of itself and its children) into a render target. The default value is KZ_FALSE. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_LAYER_CACHE_RESULT;

/** Fixed property type LayerCacheSelf. Cache layer's contents into a render target, also see Layer Cache Children. The default value is KZ_FALSE. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_LAYER_CACHE_SELF;

/** Fixed property type LayerContentStretch. Toggle how the content belonging to this layer is stretched (as opposed to manipulating the actual layer size). The default value is 2. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_LAYER_CONTENT_STRETCH;

/** Fixed property type LayerLayoutTransformation. 2D transformation to be applied before layouting. The default value is kzcMatrix3x3(1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f). */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_LAYER_LAYOUT_TRANSFORMATION;

/** Fixed property type LayerRenderTransformationOrigin. Layer r transform origin in relative coordinates. The default value is kzcVector2(0.0f,  0.0f). */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_LAYER_RENDER_TRANSFORMATION_ORIGIN;

/** Fixed property type LayerRenderTransformation. 2D transformation to be applied after layouting. The default value is kzcMatrix3x3(1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f). */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_LAYER_RENDER_TRANSFORMATION;

/** Fixed property type LayerSnapToPixel. Snap layer's translation and actual size into pixel boundary. The default value is KZ_FALSE. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_LAYER_SNAP_TO_PIXEL;

/** Fixed property type LayerBackgroundBrushColor. Color for background brush color used for filling layer backgrounds. Set alpha to 0 to disable background brush. The default value is kzcColorRGBA(0.0f, 0.0f, 0.0f, 1.0f). */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_LAYER_BACKGROUND_BRUSH_COLOR;

/** Fixed property type LayerBackgroundBrushTexture. Texture for background brush used for filling layer backgrounds. The default value is KZ_NULL. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_LAYER_BACKGROUND_BRUSH_TEXTURE;

/** Fixed property type LayerBackgroundMaterial. Material used for rendering layer backgrounds. The default value is KZ_NULL. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_LAYER_BACKGROUND_MATERIAL;

/** Fixed property type LayerCompositionMaterial. Material used for rendering a layer that has been rendered into an FBO. The default value is KZ_NULL. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_LAYER_COMPOSITION_MATERIAL;

/** Fixed property type LayerCompositionTexture. Texture used to render composited layers. The default value is KZ_NULL. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_LAYER_COMPOSITION_TEXTURE;

/** Fixed property type LayerForegroundHint. Give a hint of the type of the foreground provided by (viewport) layers. The default value is 0. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_LAYER_FOREGROUND_HINT;

/** Fixed property type LayerMaterial. Material used for rendering a layer as a texture. The default value is KZ_NULL. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_LAYER_MATERIAL;

/** Fixed property type LayerOpacity. User defined layer opacity. The default value is 1.0f. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_LAYER_OPACITY;

/** Fixed property type LayerRenderOpacity. Opacity used to render the layer itself. The default value is 1.0f. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_LAYER_RENDER_OPACITY;

/** Fixed property type LayerRenderAlways. Specifies if layer rendering is always triggered, used only if LayerRenderOnDemand is true. Triggers rerender always for the specified layer. The default value is KZ_FALSE. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_LAYER_RENDER_ALWAYS;

/** Fixed property type LayerOffscreenRendering. If set and the layer has an explicitly set render target, do not render the resulting framebuffer onto screen. The default value is KZ_FALSE. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_LAYER_OFFSCREEN_RENDERING;

/** Fixed property type LayerDisableRenderTargetClear. Do not clear render target buffers before rendering into it even if it would be deemed necessary. The default value is KZ_FALSE. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_LAYER_DISABLE_RENDER_TARGET_CLEAR;

/** Fixed property type LayerPixelFormat. Layer pixel format if rendering into a texture. The default value is 0. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_LAYER_PIXEL_FORMAT;

/** Fixed property type LayerRenderSelf. Does the layer render itself. Children are still rendered, affect only calling layer's personal render method. The default value is KZ_TRUE. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_LAYER_RENDER_SELF;

/** Fixed property type LayerRenderTarget. Forces layer to be rendered into a given render target texture. When specified as "No Target", regular conditions whether layer is rendered to a texture such as opacity and rotation are applied. The default value is KZ_NULL. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_LAYER_RENDER_TARGET;

/** Fixed property type LayerRenderTargetMinimumHeight. Minimum width an implicitly generated layer render target. The default value is 0.0f. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_LAYER_RENDER_TARGET_MINIMUM_HEIGHT;

/** Fixed property type LayerRenderTargetMinimumWidth. Minimum width of an implicitly generated layer render target. The default value is 0.0f. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_LAYER_RENDER_TARGET_MINIMUM_WIDTH;

/** Fixed property type LayerRenderTargetReallocationLimit. Relative size limit where a layer render target is shrunk. The default value is 0.25f. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_LAYER_RENDER_TARGET_REALLOCATION_LIMIT;

/** Fixed property type LayerRenderTargetOverride. Forces or denies use of . The default value is 0. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_LAYER_RENDER_TARGET_OVERRIDE;

/** Fixed property type LayerRenderTexture. Texture used to render layers - used internally. The default value is KZ_NULL. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_LAYER_RENDER_TEXTURE;

/** Fixed property type LayerRenderBackgroundColor. Color used to render layer backgrounds. The default value is kzcColorRGBA(1.0f, 1.0f, 1.0f, 1.0f). */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_LAYER_RENDER_BACKGROUND_COLOR;

/** Fixed property type LayerRenderBackgroundTexture. Texture used to render layer backgrounds. The default value is KZ_NULL. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_LAYER_RENDER_BACKGROUND_TEXTURE;

/** Fixed property type PartialRenderingLayerDebugVisualization. Determines if partial rendering is visualized normally, or showing only color changes or stencil buffer for debugging. The default value is 0. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_PARTIAL_RENDERING_LAYER_DEBUG_VISUALIZATION;

/** Fixed property type ViewportLayerCamera. The default value is KZ_NULL. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_VIEWPORT_LAYER_CAMERA;

/** Fixed property type ViewportLayerHitTestCamera. The default value is KZ_NULL. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_VIEWPORT_LAYER_HIT_TEST_CAMERA;

/** Fixed property type ViewportLayerComposer. The default value is KZ_NULL. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_VIEWPORT_LAYER_COMPOSER;

/** Fixed property type ViewportX. The X coordinate in v to render the render pass on the render target. The default value is 0.0f. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_VIEWPORT_X;

/** Fixed property type ViewportY. The Y coordinate in which to render the render pass on the render target. The default value is 0.0f. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_VIEWPORT_Y;

/** Fixed property type ViewportWidth. The width of the render area on the render target. The default value is 1.0f. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_VIEWPORT_WIDTH;

/** Fixed property type ViewportHeight. The height of the render area on the render target. The default value is 1.0f. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_VIEWPORT_HEIGHT;

/** Fixed property type ViewportRelativeX. The relative X coordinate in which to render the render pass on the render target. The default value is 0.0f. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_VIEWPORT_RELATIVE_X;

/** Fixed property type ViewportRelativeY. The relative Y coordinate in which to render the render pass on the render target. The default value is 0.0f. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_VIEWPORT_RELATIVE_Y;

/** Fixed property type ViewportRelativeWidth. The relative width of the render area on the render target. The default value is 1.0f. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_VIEWPORT_RELATIVE_WIDTH;

/** Fixed property type ViewportRelativeHeight. The relative height of the render area on the render target. The default value is 1.0f. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_VIEWPORT_RELATIVE_HEIGHT;

/** Fixed property type ViewportAbsoluteX. The X coordinate in which to render the render pass on the render target in pixels. The default value is 0.0f. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_VIEWPORT_ABSOLUTE_X;

/** Fixed property type ViewportAbsoluteY. The Y coordinate in which to render the render pass on the render target in pixels. The default value is 0.0f. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_VIEWPORT_ABSOLUTE_Y;

/** Fixed property type ViewportAbsoluteWidth. The absolute width of the render area on the render target in pixels. The default value is 480.0f. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_VIEWPORT_ABSOLUTE_WIDTH;

/** Fixed property type ViewportAbsoluteHeight. The absolute height of the render area on the render target in pixels. The default value is 800.0f. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_VIEWPORT_ABSOLUTE_HEIGHT;

/** Fixed property type ViewportType. When absolute, the viewport settings are read in pixel coordinates, when relative the settings are read as proportional values from top-left (0,0) corner to bottom-right (1,1) corner. The default value is 1. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_VIEWPORT_TYPE;

/** Fixed property type MessageHandlerTriggerSetHandled. Whether or not to set message as handled which ceases its traversal. The default value is KZ_TRUE. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_MESSAGE_HANDLER_TRIGGER_SET_HANDLED;

/** Fixed property type MessageHandlerTriggerRoutingMode. The routing phase where the message is going to be intercepted. The default value is 2. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_MESSAGE_HANDLER_TRIGGER_ROUTING_MODE;

/** Fixed property type MessageHandlerTriggerMessageSource. A filter that makes possible to intercept events only for a certain source node. Defaults to no filtering. The default value is KZ_NULL. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_MESSAGE_HANDLER_TRIGGER_MESSAGE_SOURCE;

/** Fixed property type ActionDelay. The time in milliseconds after which the message is dispatched. The default value is 0. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_ACTION_DELAY;

/** Fixed property type DispatchMessageActionDispatchMode. The message dispatch mode.
POST queues the message after message handling is done.
SEND dispatches the message right away in the middle of the message handling. The default value is 2. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_DISPATCH_MESSAGE_ACTION_DISPATCH_MODE;

/** Fixed property type DispatchMessageActionRoutingTarget. Specifies the target item where to the message will be dispatched. If the target resides within scene graph, and the message type has tunneling and bubbling enabled, the message is tunneled and bubbled through the parents of the target. The default value is ".". */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_DISPATCH_MESSAGE_ACTION_ROUTING_TARGET;

/** Fixed property type ExpressionValidator.Argument1. The first argument in the expression. The default value is 0. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_EXPRESSION_VALIDATOR__ARGUMENT_1;

/** Fixed property type ExpressionValidator.ArgumentAttribute1. The property attribute for argument 1. The default value is 9. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_EXPRESSION_VALIDATOR__ARGUMENT_ATTRIBUTE_1;

/** Fixed property type ExpressionValidator.Argument2. The second argument in the expression. The default value is 0. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_EXPRESSION_VALIDATOR__ARGUMENT_2;

/** Fixed property type ExpressionValidator.ArgumentAttribute2. The property attribute for argument 2. The default value is 9. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_EXPRESSION_VALIDATOR__ARGUMENT_ATTRIBUTE_2;

/** Fixed property type ExpressionValidator.Operation. The operation in the expression. The default value is 1. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_EXPRESSION_VALIDATOR__OPERATION;

/** Fixed property type ExpressionValidator.OutputAttribute. The property attribute of output register. The default value is 9. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_EXPRESSION_VALIDATOR__OUTPUT_ATTRIBUTE;

/** Fixed property type ExpressionValidator.ExtraArgumentObjectPath. Path to an object with extra argument. The default value is KZ_NULL. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_EXPRESSION_VALIDATOR__EXTRA_ARGUMENT_OBJECT_PATH;

/** Fixed property type ExpressionValidator.ExtraArgumentPropertyType. Property type of extra argument. The default value is KZ_NULL. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_EXPRESSION_VALIDATOR__EXTRA_ARGUMENT_PROPERTY_TYPE;

/** Fixed property type ExpressionValidator.ExtraArgumentField. Attribute of the extra item property. The default value is 0. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_EXPRESSION_VALIDATOR__EXTRA_ARGUMENT_FIELD;

/** Fixed property type ExpressionValidator.ConstantArgumentPropertyType. Property type of constant argument. The default value is KZ_NULL. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_EXPRESSION_VALIDATOR__CONSTANT_ARGUMENT_PROPERTY_TYPE;

/** Fixed property type ExpressionValidator.ConstantFloatValue. Constant float value to be used in the expression. The default value is 0.0f. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_EXPRESSION_VALIDATOR__CONSTANT_FLOAT_VALUE;

/** Fixed property type ExpressionValidator.ArgumentLeft. The temporary register to write left argument to. The default value is 0. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_EXPRESSION_VALIDATOR__ARGUMENT_LEFT;

/** Fixed property type ExpressionValidator.ArgumentRight. The temporary register to write right argument to. The default value is 0. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_EXPRESSION_VALIDATOR__ARGUMENT_RIGHT;

/** Fixed property type ExpressionValidator.Result. The temporary register to write result to. The default value is 0. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_EXPRESSION_VALIDATOR__RESULT;

/** Fixed property type AnimationValidator.AnimationItemPath. Path to animation item. The animation item will be applied by validator when input property changes. The default value is KZ_NULL. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_ANIMATION_VALIDATOR__ANIMATION_ITEM_PATH;

/** Fixed property type LevelOfDetailMinimumArea. The area setting used in the children of level-of-detail nodes. See level-of-detail nodes. The default value is 0.0f. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_LEVEL_OF_DETAIL_MINIMUM_AREA;

/** Fixed property type LevelOfDetailMinimumDistance. The distance setting used in the children of level-of-detail nodes. See level-of-detail nodes. The default value is 0.0f. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_LEVEL_OF_DETAIL_MINIMUM_DISTANCE;

/** Fixed property type InstantiatedNode. The node to instantiate. The default value is KZ_NULL. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_INSTANTIATED_NODE;

/** Fixed property type BindingProperty.ConstantFloat. Float property for binding to support constant values. The default value is 0.0f. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_BINDING_PROPERTY__CONSTANT_FLOAT;

/** Fixed property type StencilWriteMode. Controls how the stencil buffer is updated by the results of the stencil and depth tests. The default value is 0. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_STENCIL_WRITE_MODE;

/** Fixed property type TimelineEntryWeight. The weight ratio of this entry among all entries. The default value is 1.0f. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_TIMELINE_ENTRY_WEIGHT;

/** Fixed property type MessageType. The name of the a message type. The default value is KZ_NULL. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_MESSAGE_TYPE;

/** Fixed property type StyleName. The default value is KZ_NULL. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_STYLE_NAME;

/** Fixed property type StateManager. The default value is KZ_NULL. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_STATE_MANAGER;

/** Fixed property type EditingSequence. Temporary sequence for animation editing purposes, for tool use only. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_EDITING_SEQUENCE;

/** Fixed property type StartupScreen. The startup screen when the binary is viewed with the KZB player application. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_STARTUP_SCREEN;

/** Fixed property type StartupLocale. The start-up locale exported to kzb. The default value is KZ_NULL. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_STARTUP_LOCALE;

/** Fixed property type PreviewWindowBackgroundColor. The color of the area in the preview window that is not covered by screen. The default value is kzcColorRGBA(0.0f, 0.0f, 0.0f, 0.0f). */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_PREVIEW_WINDOW_BACKGROUND_COLOR;

/** Fixed property type MessageLimitPerFrame. The maximum number of messages sent in a frame. This can be used to detect an infinite loop in a state manager. Set to zero to disable the limit. The default value is 1000. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_MESSAGE_LIMIT_PER_FRAME;

/** Fixed property type CustomComposerTypeName. The factory name of the custom composer to be used. The default value is KZ_NULL. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_CUSTOM_COMPOSER_TYPE_NAME;

/** Fixed property type Message.WriteLogProperty. Log message to be written on the log. The default value is KZ_NULL. */
extern const struct KzuPropertyType* KZU_MESSAGE__WRITE_LOG_PROPERTY;

/** Fixed property type MessageArgument.TargetObject. */
extern const struct KzuPropertyType* KZU_MESSAGE_ARGUMENT__TARGET_OBJECT;

/** Fixed property type MessageArgument.AnimationItem. */
extern const struct KzuPropertyType* KZU_MESSAGE_ARGUMENT__ANIMATION_ITEM;

/** Fixed property type MessageArgument.AnimationItemTime. The default value is 0.0f. */
extern const struct KzuPropertyType* KZU_MESSAGE_ARGUMENT__ANIMATION_ITEM_TIME;

/** Fixed property type MessageArgument.TimelineEntry. */
extern const struct KzuPropertyType* KZU_MESSAGE_ARGUMENT__TIMELINE_ENTRY;

/** Fixed property type MessageArgument.TimelineEntryPlayback. */
extern const struct KzuPropertyType* KZU_MESSAGE_ARGUMENT__TIMELINE_ENTRY_PLAYBACK;

/** Fixed property type MessageArgument.TargetObjectName. The default value is KZ_NULL. */
extern const struct KzuPropertyType* KZU_MESSAGE_ARGUMENT__TARGET_OBJECT_NAME;

/** Fixed property type MessageArgument.InputManager. */
extern const struct KzuPropertyType* KZU_MESSAGE_ARGUMENT__INPUT_MANAGER;

/** Fixed property type MessageArgument.Key. The default value is 0. */
extern const struct KzuPropertyType* KZU_MESSAGE_ARGUMENT__KEY;

/** Fixed property type MessageArgument.TouchPoints. */
extern const struct KzuPropertyType* KZU_MESSAGE_ARGUMENT__TOUCH_POINTS;

/** Fixed property type MessageArgument.AllTouchPoints. */
extern const struct KzuPropertyType* KZU_MESSAGE_ARGUMENT__ALL_TOUCH_POINTS;

/** Fixed property type MessageArgument.Manipulator.Point. The default value is kzcVector2(0.0f, 0.0f). */
extern const struct KzuPropertyType* KZU_MESSAGE_ARGUMENT__MANIPULATOR__POINT;

/** Fixed property type MessageArgument.Manipulator.RayOrigin. The default value is kzcVector3(0.0f, 0.0f, 0.0f). */
extern const struct KzuPropertyType* KZU_MESSAGE_ARGUMENT__MANIPULATOR__RAY_ORIGIN;

/** Fixed property type MessageArgument.Manipulator.RayDirection. The default value is kzcVector3(0.0f, 0.0f, -1.0f). */
extern const struct KzuPropertyType* KZU_MESSAGE_ARGUMENT__MANIPULATOR__RAY_DIRECTION;

/** Fixed property type MessageArgument.HitTest.Point. The default value is kzcVector2(0.0f, 0.0f). */
extern const struct KzuPropertyType* KZU_MESSAGE_ARGUMENT__HIT_TEST__POINT;

/** Fixed property type MessageArgument.HitTest.RayOrigin. The default value is kzcVector3(0.0f, 0.0f, 0.0f). */
extern const struct KzuPropertyType* KZU_MESSAGE_ARGUMENT__HIT_TEST__RAY_ORIGIN;

/** Fixed property type MessageArgument.HitTest.RayDirection. The default value is kzcVector3(0.0f, 0.0f, -1.0f). */
extern const struct KzuPropertyType* KZU_MESSAGE_ARGUMENT__HIT_TEST__RAY_DIRECTION;

/** Fixed property type MessageArgument.HitTest.Object. */
extern const struct KzuPropertyType* KZU_MESSAGE_ARGUMENT__HIT_TEST__OBJECT;

/** Fixed property type MessageArgument.Pan.Delta. The default value is kzcVector2(0.0f, 0.0f). */
extern const struct KzuPropertyType* KZU_MESSAGE_ARGUMENT__PAN__DELTA;

/** Fixed property type MessageArgument.Pinch.Scale. The default value is 1.0f. */
extern const struct KzuPropertyType* KZU_MESSAGE_ARGUMENT__PINCH__SCALE;

/** Fixed property type MessageArgument.Pinch.Rotation. The default value is 0.0f. */
extern const struct KzuPropertyType* KZU_MESSAGE_ARGUMENT__PINCH__ROTATION;

/** Fixed property type MessageArgument.Swipe.Direction. The default value is 0. */
extern const struct KzuPropertyType* KZU_MESSAGE_ARGUMENT__SWIPE__DIRECTION;

/** Fixed property type MessageArgument.Swipe.Velocity. The default value is 0.0f. */
extern const struct KzuPropertyType* KZU_MESSAGE_ARGUMENT__SWIPE__VELOCITY;

/** Fixed property type MessageArgument.TestValue. The default value is 0.0f. */
extern const struct KzuPropertyType* KZU_MESSAGE_ARGUMENT__TEST_VALUE;

/** Fixed property type MessageArgument.FloatValue. The default value is 0.0f. */
extern const struct KzuPropertyType* KZU_MESSAGE_ARGUMENT__FLOAT_VALUE;

/** Fixed property type MessageArgument.BoolValue. The default value is KZ_FALSE. */
extern const struct KzuPropertyType* KZU_MESSAGE_ARGUMENT__BOOL_VALUE;

/** Fixed property type MessageArgument.IntValue. The default value is 0. */
extern const struct KzuPropertyType* KZU_MESSAGE_ARGUMENT__INT_VALUE;

/** Fixed property type MessageArgument.PropertyAttribute. The default value is 9. */
extern const struct KzuPropertyType* KZU_MESSAGE_ARGUMENT__PROPERTY_ATTRIBUTE;

/** Fixed property type SceneOverrideCamera. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_SCENE_OVERRIDE_CAMERA;

/** Fixed property type SceneGraphAddNodeChangeChildFlags. The default value is 196614. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_SCENE_GRAPH_ADD_NODE_CHANGE_CHILD_FLAGS;

/** Fixed property type SceneGraphAddNodeChangeParentFlags. The default value is 65540. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_SCENE_GRAPH_ADD_NODE_CHANGE_PARENT_FLAGS;

/** Fixed property type SceneGraphRemoveNodeChangeChildFlags. The default value is 0. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_SCENE_GRAPH_REMOVE_NODE_CHANGE_CHILD_FLAGS;

/** Fixed property type SceneGraphRemoveNodeChangeParentFlags. The default value is 65540. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_SCENE_GRAPH_REMOVE_NODE_CHANGE_PARENT_FLAGS;

/** Fixed property type ObjectNodePrefabTemplateSource. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_OBJECT_NODE_PREFAB_TEMPLATE_SOURCE;

/** Fixed property type SwipeManipulatorDirection. The default value is 15. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_SWIPE_MANIPULATOR_DIRECTION;

/** Fixed property type TriggerForwardMessage. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_TRIGGER_FORWARD_MESSAGE;

/** Fixed property type TargetComponentLocation. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_TARGET_COMPONENT_LOCATION;

/** Fixed property type ButtonPressDuration. The default value is 0.0f. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_BUTTON_PRESS_DURATION;

/** Fixed property type ObjectFromKZB. The default value is KZ_FALSE. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_OBJECT_FROM_KZB;

/** Fixed property type ObjectExternalOwnership. The default value is KZ_FALSE. */
extern const struct KzuPropertyType* KZU_PROPERTY_TYPE_OBJECT_EXTERNAL_OWNERSHIP;


/** Initializes all fixed properties. */
kzsError kzuFixedPropertiesCreate(const struct KzcMemoryManager* memoryManager);


KZ_HEADER_END


#endif
