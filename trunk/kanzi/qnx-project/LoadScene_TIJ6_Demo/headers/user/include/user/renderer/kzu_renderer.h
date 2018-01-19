/**
* \file
* Specifies a user renderer. Renderer is the core component for assigning
* lights, meshes, cameras, skin animations etc. to lower level rendering.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_RENDERER_H
#define KZU_RENDERER_H


#include "kzu_renderer_types.h"
#include <user/effect_system/stereoscopic_rendering/kzu_stereoscopic_rendering.h>
#include <user/common/kzu_user.h>

#include <core/util/collection/kzc_dynamic_array.h>
#include <core/util/color/kzc_color.h>

#include <system/debug/kzs_error.h>
#include <system/wrappers/kzs_opengl_base.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations. */
struct KzcDynamicArray;
struct KzcMatrix4x4;
struct KzcMemoryManager;
struct KzcRenderer;
struct KzcVector2;
struct KzcVector4;
struct KzuBoundingVolume;
struct KzuCameraNode;
struct KzuCanvas;
struct KzuLightNode;
struct KzuMaterial;
struct KzuObjectNode;
struct KzuPropertyManager;
struct KzuPropertyQuery;
struct KzuPropertyType;
struct KzuRenderPass;
struct KzuMesh;
struct KzuResourceManager;
struct KzuScene;
struct KzuObjectSource;
struct KzuTransformedObjectNode;
struct KzuRendererBatch;
struct KzuUIDomain;


/** Callback function for override materials. */
typedef kzsError (*KzuRendererOverrideMaterialCallback)(const struct KzuTransformedObjectNode* transformedObjectNode, struct KzuMaterial* material, kzUint cluster,
                                                        void* userData, struct KzuMaterial** out_material);


/**
 * \struct KzuRenderer
 * Renderer is the core component for assigning lights, meshes, cameras, skin animations etc. to lower level rendering.
 */
struct KzuRenderer;


#define KZU_RENDERER_FLOAT_BUFFER_LENGTH 5000 /**< Length of float buffer, that is used for dynamic data of vertex arrays. */


/** Function pointer for applying specific type of object for rendering. */
typedef kzsError (*KzuRendererApplyObjectFunction)(struct KzuTransformedObjectNode* transformedObjectNode, struct KzuRenderer* renderer);


/** Creates user renderer. */
kzsError kzuRendererCreate(const struct KzcMemoryManager* memoryManager, kzUint quickMemorySize, struct KzuUIDomain* uiDomain, kzBool createDefaultMaterials, struct KzuRenderer** out_renderer);
/** Deletes user renderer. */
kzsError kzuRendererDelete(struct KzuRenderer* renderer);

/**
 * Sets default materials for renderer. 
 * \param ownedByRenderer - indicates if materials will be owned and deleted by renderer.
 */
kzsError kzuRendererSetDefaultMaterials(struct KzuRenderer* renderer, struct KzuMaterial* defaultMaterial, struct KzuMaterial* solidColorMaterial, 
                                    struct KzuMaterial* opaqueSolidColorMaterial, struct KzuMaterial* errorMaterial,
                                    struct KzuMaterial* texturedMaterial, struct KzuMaterial* debugLightMaterial,
                                    struct KzuMaterial* layerTexturedMaterial, struct KzuMaterial* layerTexturedOpaqueMaterial,
                                    struct KzuMaterial* layerTexturedBackgroundMaterial, struct KzuMaterial* layerTexturedBackgroundOpaqueMaterial,
                                    struct KzuMaterial* layerCompositionMaterial, struct KzuMaterial* layerCompositionOpaqueMaterial,
                                    struct KzuMaterial* layerBackgroundMaterial, struct KzuMaterial* layerBackgroundOpaqueMaterial,
                                    struct KzuMaterial* layerBackgroundTexturedMaterial, struct KzuMaterial* layerBackgroundTexturedOpaqueMaterial,
                                    struct KzuMaterial* transitionLayerMaterial, kzBool owndedByRenderer);
/** Load default materials from project, then set them.
 * Will not replace materials that already exist.
 */
kzsError kzuRendererLoadDefaultMaterials(struct KzuRenderer* renderer, const struct KzuUIDomain* uiDomain);

/** Enables or disables debug log writing. */
void kzuRendererSetLogging(struct KzuRenderer* renderer, kzBool logging);
/** Enables or disables gathering rendering statistics. */
void kzuRendererSetCollectingStatisticsEnabled(struct KzuRenderer* renderer, kzBool enabled);
/** Returns KZ_TRUE if gathering rendering statistics is enabled, KZ_FALSE otherwise. */
kzBool kzuRendererIsCollectingStatisticsEnabled(const struct KzuRenderer* renderer);

/** Resets renderer, that is, puts it to initial state. */
kzsError kzuRendererReset(const struct KzuRenderer* renderer);
/** Resets user renderer for frame, that is, clear property stack and core renderer per-frame variables. */
kzsError kzuRendererResetFrame(struct KzuRenderer* renderer);
/** Ends a frame. */
void kzuRendererEndFrame(struct KzuRenderer* renderer);
/** Gets number of frames rendered by renderer. */
kzUint kzuRendererGetFrameCount(const struct KzuRenderer* renderer);
/** Resets pass for renderer, that is, per-render pass specific properties, such as lighting. */
kzsError kzuRendererResetPass(struct KzuRenderer* renderer);
/** Ends frame for renderer. */
kzsError kzuRendererPrintInfo(const struct KzuRenderer* renderer);


/** Adds light property to rendering pipeline. Lights should be reset each pass by calling kzuRendererResetPass. */
kzsError kzuRendererApplyLight(const struct KzuRenderer* renderer, const struct KzuLightNode* lightNode,
                               const struct KzcMatrix4x4* worldTransformation);
/** Applies renderable object for rendering. Called from render pass. */
kzsError kzuRendererApplyRenderable(struct KzuTransformedObjectNode* transformedObjectNode, struct KzuRenderer* renderer);
/** Applies mesh object (2D & 3D) down in rendering pipeline, to core renderer. */
kzsError kzuRendererApplyMeshObject(struct KzuRenderer* renderer, const struct KzuTransformedObjectNode* transformedObjectNode, 
                                    struct KzcMatrix4x4* worldTransformation);
/** Sets transformed object list for renderer, used for fetching bones for mesh. */
void kzuRendererSetTransformedObjectList(struct KzuRenderer* renderer, struct KzcDynamicArray* transformedObjectList);
/** Gets transformed object list from renderer. */
struct KzcDynamicArray* kzuRendererGetTransformedObjectList(const struct KzuRenderer* renderer);
/** Applies transformation and draws vertex and index buffers with current settings. */
kzsError kzuRendererDrawBuffers(struct KzuRenderer* renderer, struct KzuMesh* mesh, const struct KzuObjectNode* baseNode,
                                kzUint cluster, const struct KzuMaterial* material);


/** Resolves renderer batch queue, if there's such (queue generated by batch sorting). */
kzsError kzuRendererResolveBatchQueue(struct KzuRenderer* renderer);
/** Sets renderer sort by shader enabled. */
void kzuRendererSetSortByShader(struct KzuRenderer* renderer, kzBool sortByShader);
/** Returns if sort by shader is enabled. */
kzBool kzuRendererIsSortByShader(const struct KzuRenderer* renderer);


/** Gets renderer resource manager. */
struct KzuResourceManager* kzuRendererGetResourceManager(const struct KzuRenderer* renderer);
/** Gets renderer property query. */
struct KzuPropertyQuery* kzuRendererGetPropertyQuery(const struct KzuRenderer* renderer);


/** Applies material to renderer, attaches the shader and uniforms. */
kzsError kzuRendererApplyMaterial(struct KzuRenderer* renderer, const struct KzuMaterial* material);
/** Applies camera node to renderer, containing projection and camera matrices. */
kzsError kzuRendererApplyCameraNode(const struct KzuRenderer* renderer, const struct KzuTransformedObjectNode* transformedCameraNode,
                                    kzFloat viewportX, kzFloat viewportY, kzFloat viewportWidth, kzFloat viewportHeight);
/** Returns default material from renderer. */
struct KzuMaterial* kzuRendererGetDefaultMaterial(const struct KzuRenderer* renderer);
/** Returns error material from renderer. */
struct KzuMaterial* kzuRendererGetErrorMaterial(const struct KzuRenderer* renderer);
/** Gets textured material from renderer. */
struct KzuMaterial* kzuRendererGetTexturedMaterial(const struct KzuRenderer* renderer);
/** Returns solid color material. Uses color property "Emissive" to specify solid color. */
struct KzuMaterial* kzuRendererGetSolidColorMaterial(const struct KzuRenderer* renderer);
/** Returns opaque solid color material. Uses color property "Emissive" to specify solid color. */
struct KzuMaterial* kzuRendererGetOpaqueSolidColorMaterial(const struct KzuRenderer* renderer);
/** Returns debug light material. Uses color property "Emissive" to specify rendering color. */
struct KzuMaterial* kzuRendererGetDebugLightMaterial(const struct KzuRenderer* renderer);
/** Returns layer material from renderer. */
struct KzuMaterial* kzuRendererGetLayerTexturedMaterial(const struct KzuRenderer* renderer);
/** Returns layer opaque material from renderer. */
struct KzuMaterial* kzuRendererGetLayerTexturedOpaqueMaterial(const struct KzuRenderer* renderer);
/** Returns layer material from renderer. */
struct KzuMaterial* kzuRendererGetLayerTexturedBackgroundMaterial(const struct KzuRenderer* renderer);
/** Returns layer opaque material from renderer. */
struct KzuMaterial* kzuRendererGetLayerTexturedBackgroundOpaqueMaterial(const struct KzuRenderer* renderer);
/** Returns layer composition material from renderer. */
struct KzuMaterial* kzuRendererGetLayerCompositionMaterial(const struct KzuRenderer* renderer);
/** Returns layer opaque composition material from renderer. */
struct KzuMaterial* kzuRendererGetLayerCompositionOpaqueMaterial(const struct KzuRenderer* renderer);
/** Returns layer background material from renderer. */
struct KzuMaterial* kzuRendererGetLayerBackgroundMaterial(const struct KzuRenderer* renderer);
/** Returns layer opaque background material from renderer. */
struct KzuMaterial* kzuRendererGetLayerBackgroundOpaqueMaterial(const struct KzuRenderer* renderer);
/** Returns layer textured background material from renderer. */
struct KzuMaterial* kzuRendererGetLayerBackgroundTexturedMaterial(const struct KzuRenderer* renderer);
/** Returns layer opaque textured background material from renderer. */
struct KzuMaterial* kzuRendererGetLayerBackgroundTexturedOpaqueMaterial(const struct KzuRenderer* renderer);
/** Returns layer material used to render transition layers in their multitexturing transition phase. */
struct KzuMaterial* kzuRendererGetTransitionLayerMaterial(const struct KzuRenderer* renderer);
/** Sets clear color override for rendering. KZ_NULL to colorRGBA to disable. */
void kzuRendererSetClearColorOverride(struct KzuRenderer* renderer, const struct KzcColorRGBA* colorRGBA);
/** Gets clear color override from renderer. Returns KZ_TRUE if override enabled. */
kzBool kzuRendererGetClearColorOverride(const struct KzuRenderer* renderer, struct KzcColorRGBA* out_colorRGBA);
/** Sets cull mode override. */
void kzuRendererSetCullFaceOverride(struct KzuRenderer* renderer, kzBool enabled, enum KzuCullMode overriddenCullMode);
/** Returns cull face override. */
kzBool kzuRendererGetCullFaceOverride(const struct KzuRenderer* renderer, enum KzuCullMode* out_overriddenCullMode);

/** Sets clear color buffer override for renderer. */
void kzuRendererSetClearColorBufferOverride(struct KzuRenderer* renderer, kzBool enabled);
/** Returns if clear color buffer override is set. */
kzBool kzuRendererGetClearColorBufferOverride(const struct KzuRenderer* renderer);

/** Sets color write disabled, overrides render pass settings. */
void kzuRendererSetDisableColorWrite(struct KzuRenderer* renderer, kzBool setDisabled);
/** Returns if color write is disabled. */
kzBool kzuRendererIsColorWriteDisabled(const struct KzuRenderer* renderer);

/**
 * Create vertex combining array from quick memory manager.
 * After this vertices added with kzuRendererAddMeshVertexCombiningArrayVertices will be combined into one big single mesh.
 */
kzsError kzuRendererCreateMeshVertexCombiningArray(struct KzuRenderer* renderer);
/** Sets vertex array combine enabled. */
void kzuRendererSetMeshVertexCombiningEnabled(struct KzuRenderer* renderer, kzBool enabled);
/** Returns if vertex array combine is enabled. */
kzBool kzuRendererIsMeshVertexCombiningEnabled(const struct KzuRenderer* renderer);

/** Adds vertices for vertex combining. */
void kzuRendererAddMeshVertexCombiningArrayVertices(struct KzuRenderer* renderer, const kzFloat* vertices, kzUint vertexCount);

/** Gets vertices from vertex combining. */
kzFloat* kzuRendererGetMeshVertexCombiningArray(const struct KzuRenderer* renderer, kzUint* out_vertexCount);



/** Sets render pass input object source override. KZ_NULL to not override. */
void kzuRendererSetRenderPassInputObjectSourceOverride(struct KzuRenderer* renderer, struct KzuObjectSource* overrideObjectSource);
/** Gets render pass input object source override. */
struct KzuObjectSource* kzuRendererGetRenderPassInputObjectSourceOverride(const struct KzuRenderer* renderer);


/** Sets forced material for rendering, none of the properties are inherited from the object node. */
void kzuRendererSetForcedMaterial(struct KzuRenderer* renderer, struct KzuMaterial* material);
/** Sets current override material, which is used instead of all default materials. Setting material to KZ_NULL disables overrides. */
void kzuRendererSetOverrideMaterial(struct KzuRenderer* renderer, struct KzuMaterial* material);
/**
* If object node's material is overridden, sets out_overridden to KZ_TRUE and the overriding material to out_material.
* Otherwise sets out_overridden to KZ_FALSE.
*/
kzsError kzuRendererGetOverrideClusterMaterial(const struct KzuRenderer* renderer, const struct KzuTransformedObjectNode* transformedObjectNode,
                                        struct KzuMaterial* clusterMaterial, kzUint clusterIndex, kzBool* out_overridden, struct KzuMaterial** out_material);
/** Returns the given material if it is valid, otherwise either renderer's default material or error material. */
struct KzuMaterial* kzuRendererGetValidMaterial(const struct KzuRenderer* renderer, struct KzuMaterial* material);
/** Tells if given material is a default layer material. */
kzBool kzuRendererIsDefaultLayerMaterial(const struct KzuRenderer* renderer, const struct KzuMaterial* material);

/** Sets active canvas for renderer. */
void kzuRendererSetActiveCanvas(struct KzuRenderer* renderer, const struct KzuCanvas* canvas);
/** Gets active canvas from renderer. */
const struct KzuCanvas* kzuRendererGetActiveCanvas(const struct KzuRenderer* renderer);

/** Sets viewport for renderer. */
void kzuRendererSetViewport(struct KzuRenderer* renderer, kzFloat x, kzFloat y, kzFloat width, kzFloat height, kzBool relative);
/** Gets viewport from renderer. 
* \param out_x Viewport X coordinate in relative / absolute coordinates. KZ_NULL if not needed.
* \param out_y Viewport Y coordinate in relative / absolute coordinates. KZ_NULL if not needed.
* \param out_width Viewport Width in relative / absolute coordinates. KZ_NULL if not needed.
* \param out_height Viewport Height in relative / absolute coordinates. KZ_NULL if not needed.
* \param out_relative Is this window relative (absolute if not). KZ_NULL if not needed.
*/
void kzuRendererGetViewport(const struct KzuRenderer* renderer, kzFloat* out_x, kzFloat* out_y, kzFloat* out_width, kzFloat* out_height,
                            kzBool* out_relative);

/** Gets adjusted viewport from renderer. Adjusted viewport calculates real viewport size according to window size,
* \param limits Size of the available rendering area, for example X and Y sizes taken from a window.
* \param out_x Viewport X coordinate in absolute (pixel) coordinates.
* \param out_y Viewport Y coordinate in absolute (pixel) coordinates.
* \param out_width Viewport Width in absolute (pixel) coordinates.
* \param out_height Viewport Height in absolute (pixel) coordinates.
*/
void kzuRendererGetAdjustedViewport(const struct KzuRenderer* renderer, const struct KzcVector2* limits, kzFloat* out_x,
                                    kzFloat* out_y, kzFloat* out_width, kzFloat* out_height);
/** As kzuRendererGetAdjustedViewport, but get viewport limits from canvas. */
void kzuRendererGetAdjustedViewportFromCanvas(const struct KzuRenderer* renderer, const struct KzuCanvas* canvas, kzFloat* out_x,
                                              kzFloat* out_y, kzFloat* out_width, kzFloat* out_height);

/** Turn on sub-rectangle of what would be the normal projection with given relative parameters. */
void kzuRendererSetSubRectangleProjection(struct KzuRenderer* renderer, kzFloat x, kzFloat y, kzFloat width,
                                          kzFloat height);
/** Disable sub-rectangle of projection. */
void kzuRendererDisableSubRectangleProjection(struct KzuRenderer* renderer);
/** Get the multiplier to inherited aspect ratio. */
kzFloat kzuRendererGetInheritedAspectRatioMultiplier(const struct KzuRenderer* renderer);

/** Gets adjusted scissor from renderer. */
void kzuRendererGetAdjustedScissor(const struct KzuRenderer* renderer, kzBool scissorEnabled, const struct KzcVector4* scissorArea, kzBool* out_scissorEnabled, struct KzcVector4* out_adjustedScissorArea);

/** Returns core renderer from user renderer. */
struct KzcRenderer* kzuRendererGetCoreRenderer(const struct KzuRenderer* renderer);


/** Sets bounding box visualization enabled / disabled. */
void kzuRendererSetBoundingBoxVisualizationEnabled(struct KzuRenderer* renderer, kzBool enabled);
/** Returns if bounding box visualization is enabled. */
kzBool kzuRendererIsBoundingBoxVisualizationEnabled(const struct KzuRenderer* renderer);
/** Sets skeleton visualization enabled / disabled. */
void kzuRendererSetSkeletonVisualizationEnabled(struct KzuRenderer* renderer, kzBool enabled);
/** Returns if skeleton visualization is enabled. */
kzBool kzuRendererIsSkeletonVisualizationEnabled(const struct KzuRenderer* renderer);


/** Returns float buffer from renderer. Float buffer contains maximum of KZU_RENDERER_FLOAT_BUFFER_LENGTH elements,
    and it's used for dynamic vertex arrays. */
kzFloat* kzuRendererGetFloatBuffer(const struct KzuRenderer* renderer);


/** Set override material callback. Pass KZ_NULL to disable. */
kzsError kzuRendererSetOverrideMaterialCallback(struct KzuRenderer* renderer, KzuRendererOverrideMaterialCallback callbackFunction, void* userData);
/** Gets override material callback from renderer, KZ_NULL if not enabled. */
KzuRendererOverrideMaterialCallback kzuRendererGetOverrideMaterialCallback(const struct KzuRenderer* renderer);
/** Gets override material callback user data from renderer. */
void* kzuRendererGetOverrideMaterialCallbackUserData(const struct KzuRenderer* renderer);


/** Returns a quick memory manager of the renderer. */
struct KzcMemoryManager* kzuRendererGetQuickMemoryManager(const struct KzuRenderer* renderer);

/** Callback prototype for setActiveFrameBuffer. */
typedef void (*KzuRendererFrameBufferCallback)(kzUint frameBufferHandle);
/** Sets callback function for setActiveFrameBuffer. Called each time engine changes framebuffer. */
void kzuRendererSetFrameBufferCallback(struct KzuRenderer* renderer, KzuRendererFrameBufferCallback callbackFunction);

/** Enables stereoscopic rendering. */
void kzuRendererEnableStereoscopic(struct KzuRenderer* renderer, enum KzuStereoscopicRenderingMode mode, kzUint pass, kzBool flipped, kzFloat eyeDistance, kzFloat focalDistance);
/** Disables stereoscopic rendering */
void kzuRendererDisableStereoscopic(struct KzuRenderer* renderer);
/** Gets stereoscopic properties from renderer. If out_enabled, out_mode, out_pass or out_flipped is KZ_NULL, they're not used. */
void kzuRendererGetStereoscopic(const struct KzuRenderer* renderer, kzBool* out_enabled, enum KzuStereoscopicRenderingMode* out_mode, kzUint* out_pass,
                                kzBool* out_flipped);
/** Gets stereoscopic eye properties from renderer. If KZ_NULL, not used. */
void kzuRendererGetStereoscopicEyeProperties(const struct KzuRenderer* renderer, kzFloat* out_eyeDistance, kzFloat* out_focalDistance);

/** Adds batch to batch queue. */
kzsError kzuRendererAddBatchToQueue(const struct KzuRenderer* renderer, struct KzuTransformedObjectNode* objectNode, struct KzuMesh* mesh, kzUint clusterIndex,
                                    const struct KzuMaterial* material, const struct KzcMatrix4x4* transformation);


KZ_HEADER_END


#endif
