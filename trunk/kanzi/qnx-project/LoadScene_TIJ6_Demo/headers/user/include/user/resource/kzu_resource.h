/**
 * \file
 * \ref KzuResource is the base class for all resource objects in the Engine.
 * The main functionality is to provide:
 * - Functionality for loading and unloading data
 * - Runtime type information (RTTI) of resources
 *
 * Loading and unloading of resource data is controlled by a \ref KzuResourceManager,
 * which uses \ref KzuResourceLoadingStrategy of the resource to determine when the data
 * should be loaded or unloaded.
 *
 * User can derive this class using the API provided by \ref kzu_resource_base.h.
 *
 * \example The following example uses RTTI to check if a resource is a texture resource
 * and queries texture specific information if it is.
 * ~~~
 * if (kzuResourceIsTypeOf(resource, KZU_RESOURCE_TYPE_TEXTURE))
 * {
 *     struct KzuTexture* texture = kzuTextureFromResource(resource);
 *     kzString name = kzuResourceGetName(resource);
 *     kzUint width = kzuTextureGetWidth(texture);
 *     kzUint height = kzuTextureGetHeight(texture);
 *     kzcLogDebug("Resource %s is a texture of size %i * %i", name, width, height);
 * }
 * ~~~
 *
 * \example The following example logs how much memory a resource currently consumes.
 * ~~~
 * kzString name = kzuResourceGetName(resource);
 * KzuResourceType type = kzuResourceGetType(resource);
 * kzString typeName = kzuResourceTypeGetName(type);
 * kzUint memoryUsage = kzuResourceGetCPUMemoryUsage(resource);
 * kzcLogDebug("Resource %s of type %s uses %i bytes of RAM", name, typeName, memoryUsage);
 * ~~~
 * 
 * \see kzu_resource_manager.h
 * \see kzu_gpu_resource.h
 * 
 * Copyright 2008-2014 by Rightware. All rights reserved.
 */
#ifndef KZU_RESOURCE_H
#define KZU_RESOURCE_H


#include "kzu_resource_common.h"

#include <system/debug/kzs_error.h>
#include <system/debug/kzs_profiling.h>
#include <system/kzs_types.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations */
struct KzcMemoryManager;
struct KzuPropertyManager;
struct KzuBinaryDirectory;
struct KzuResourceLoaderThreadContext;


/**
 * \struct KzuResourceLoader
 * Represents the structure for loading a resource.
 * This contains data and function pointers for loading resource data from arbitrary sources.
 * The only ready-made implementation of a resource loader is \ref kzuResourceCreateKZBLoader, which creates
 * a resource loader that can load data from .KZB files.
 * Custom resource loaders can be created with \ref kzuResourceCreateResourceLoader_protected from \ref kzu_resource_base.h API.
 */
struct KzuResourceLoader;


/**
 * \struct KzuResource
 * Represents the base class for all resources.
 * This base class contains information related to the type of the resource and the
 * loading status of the resource data. The actual resource data is specific to the sub-classes.
 * 
 * \see KzuGPUResource for implementations of this class.
 */
struct KzuResource;


/**
 * Base resource type identifier for all resources.
 * All resource types inherit from this resource type.
 * This implies that `kzuResourceIsTypeOf(resource, KZU_RESOURCE_TYPE_RESOURCE)` always returns `KZ_TRUE`.
 */
extern const KzuResourceType KZU_RESOURCE_TYPE_RESOURCE;


/** Resource loading strategy specifies when the resource is loaded and unloaded. */
enum KzuResourceLoadingStrategy
{
    /**
     * When using the default strategy the engine loads the resource before it is needed.
     * The loading strategy depends on the platform and Kanzi application,
     * but the engine optimizes the loading strategy.
     */
    KZU_RESOURCE_LOADING_STRATEGY_DEFAULT,

    /**
     * When using the manual loading strategy you must load and unload the resource
     * manually by calling the \ref kzuResourceLoad and \ref kzuResourceUnload functions.
     * This is the only loading strategy that you can control completely.
     */
    KZU_RESOURCE_LOADING_STRATEGY_MANUAL,
    
    /**
     * When using the optimize speed strategy the engine keeps the resource in RAM.
     * When the application needs the resource, the engine can deploy the resource
     * from RAM to GPU as fast as possible. The engine releases the resource from RAM
     * only when the resource is not accessible anymore.
     * This strategy guarantees that the engine does not unload the resource during runtime. */
    KZU_RESOURCE_LOADING_STRATEGY_OPTIMIZE_SPEED,

    /**
     * When using the optimize memory loading strategy the engine unloads the resource as soon as possible.
     * The engine releases the GPU resources from RAM after deploying the resources.
     */
    KZU_RESOURCE_LOADING_STRATEGY_OPTIMIZE_MEMORY,

    /**
     * When using the on demand strategy the engine loads the resource when
     * it is needed and releases it when it is not needed anymore.
     * On demand loading strategy differs from the optimize loading strategy
     * in that it does not load the resource before it is needed.
     * This strategy is not yet supported.
     */
    KZU_RESOURCE_LOADING_STRATEGY_ON_DEMAND
};


/**
 * Creates the resource loader that loads the resource from the project file (.KZB) using the given path.
 *
 * \param memoryManager Memory manager to allocate memory for resource loader.
 * \param binaryDirectory Binary directory containing resource to load.
 * \param path Path of the resource inside a .KZB virtual file system.
 * \param out_resourceLoader The created resource loader.
 */
kzsError kzuResourceCreateKZBLoader(const struct KzcMemoryManager* memoryManager, const struct KzuBinaryDirectory* binaryDirectory, 
                                    kzString path, struct KzuResourceLoader** out_resourceLoader);

/** 
 * Deletes the resource. The reference count of the resource must be zero or an assert may fail.
 * # If the resource is a GPU resource and it has been deployed, it will be undeployed.
 * # If the resource has been loaded, it will be unloaded.
 * # Frees any remaining data owned by the resource by calling a virtual destructor.
 * After calling this function, the pointer to the resource becomes invalid and must not be used anymore.
 *
 * \param resource The resource that will be deleted.
 * \return KZS_SUCCESS on success.
 */
kzsError kzuResourceDelete(struct KzuResource* resource);

/**
 * Checks whether the resourceType, or one of its base types, is of the given base resource type.
 *
 * \param resourceType The resource type to check.
 * \param baseResourceType Resource type to check against.
 * \return Returns `KZ_TRUE` if the resource type or one of its parent types is of the given
 *         base resource type, otherwise returns `KZ_FALSE`.
 */
kzBool kzuResourceTypeIsTypeOf(const KzuResourceType resourceType, const KzuResourceType baseResourceType);

/**
 * Checks whether the resource, or one of its base types, is of the given resource type.
 *
 * \param resource The resource whose type to check.
 * \param resourceType Resource type to check against.
 * \return Returns `KZ_TRUE` if the resource or one of its parent types is of the given
 *         resource type, otherwise returns `KZ_FALSE`.
 */
kzBool kzuResourceIsTypeOf(const struct KzuResource* resource, const KzuResourceType resourceType);

/**
 * Returns the type of the resource.
 *
 * \param resource The resource.
 * \return Type of the resource specified on creation time.
 */
KzuResourceType kzuResourceGetType(const struct KzuResource* resource);

/**
 * Returns the resource type name as a string. This function is meant for debugging.
 * \param resourceType The resource type.
 * \return Name of the resource type as a string.
 */
kzString kzuResourceTypeGetName(KzuResourceType resourceType);


/**
 * Returns the name of the resource as a string.
 * \param resource The resource.
 * \return Name of the resource.
 */
kzString kzuResourceGetName(const struct KzuResource* resource);

/**
 * Returns the resource manager that was used for creating the resource.
 * \param resource The resource.
 * \return The resource manager specified on creation time.
 */
struct KzuResourceManager* kzuResourceGetResourceManager(const struct KzuResource* resource);

/**
 * Loads the resource if the resource is not loaded.
 * Depending on the deployment strategy this may also deploy the resource if it is a GPU resource.
 * \param resource The resource to load.
 * \return KZS_SUCCESS on successful loading or if the resource is already loaded.
 */
kzsError kzuResourceLoad(struct KzuResource* resource);

/**
 * Unloads the resource if the resource is loaded. Ignores the loading strategy.
 * \param resource The resource to unload.
 * \return KZS_SUCCESS on successful unloading or if the resource is not loaded.
 */
kzsError kzuResourceUnload(struct KzuResource* resource);

/**
 * Checks whether the resource is loaded.
 * \param resource The resource.
 * \return Returns `KZ_TRUE` if the resource is loaded, otherwise returns `KZ_FALSE`.
 */
kzBool kzuResourceIsLoaded(const struct KzuResource* resource);

/**
 * Returns the loading strategy of the resource.
 * \param resource The resource which loading strategy is returned.
 * \return Returns previously set loading strategy or KZU_RESOURCE_LOADING_STRATEGY_DEFAULT if it's not set.
 */
enum KzuResourceLoadingStrategy kzuResourceGetLoadingStrategy(const struct KzuResource* resource);

/**
 * Sets the loading strategy of the resource.
 * \param resource The resource which loading strategy is set.
 * \param loadingStrategy The loading strategy to use. See ::KzuResourceLoadingStrategy.
 */
void kzuResourceSetLoadingStrategy(struct KzuResource* resource, enum KzuResourceLoadingStrategy loadingStrategy);

/**
 * Returns the amount of memory used by the resource.
 * \param resource The resource.
 * \return The amount of memory used by the resource in bytes or zero.
 */
kzUint kzuResourceGetCPUMemoryUsage(const struct KzuResource* resource);


/** Acquires an existing resource, increasing the reference count by one. */
kzsError kzuResourceAcquire(struct KzuResource* resource);

/**
 * Decreases the reference count of a resource by one, effectively releases the resource when the reference count reaches zero.
 * Note that the memory allocated for the resource may or may not be freed when the count reaches zero, depending on the resource manager's settings.
 * \param resource The resource which reference count to decrease.
 */
kzsError kzuResourceRelease(struct KzuResource* resource);

/** Private function for kzuResourceLoad() with specified thread context. */
kzsError kzuResourceLoad_private(struct KzuResource* resource, const struct KzuResourceLoaderThreadContext* threadContext);

/** Private function for finishing the loading of the resource. */
kzsError kzuResourceFinishLoading_private(struct KzuResource* resource, const struct KzuResourceLoaderThreadContext* threadContext);


/** Profiling tag for mesh. */
#define KZU_RESOURCE_PROFILING_MESH_KZB "kzuResourceLoadMeshFromKZB"
/** Profiling tag for mesh deploy. */
#define KZU_RESOURCE_PROFILING_MESH_DEPLOY "kzuResourceDeployMesh"
/** Profiling tag for 2d texture. */
#define KZU_RESOURCE_PROFILING_TEXTURE_2D_KZB "kzuResourceLoadTexture2DFromKZB"
/** Profiling tag for 2d texture deploy. */
#define KZU_RESOURCE_PROFILING_TEXTURE_2D_DEPLOY "kzuResourceDeployTexture2D"
/** Profiling tag for cubemap texture. */
#define KZU_RESOURCE_PROFILING_TEXTURE_CUBE_KZB "kzuResourceLoadTextureCubeFromKZB"
/** Profiling tag for cubemap texture deploy. */
#define KZU_RESOURCE_PROFILING_TEXTURE_CUBE_DEPLOY "kzuResourceDeployTextureCube"
/** Profiling tag for 2d render target texture. */
#define KZU_RESOURCE_PROFILING_TEXTURE_RENDER_TARGET_2D_KZB "kzuResourceLoadTextureRenderTarget2DFromKZB"
/** Profiling tag for 2d render target texture deploy. */
#define KZU_RESOURCE_PROFILING_TEXTURE_RENDER_TARGET_2D_DEPLOY "kzuResourceDeployTextureRenderTarget2D"
/** Profiling tag for cubemap render target texture. */
#define KZU_RESOURCE_PROFILING_TEXTURE_RENDER_TARGET_CUBE_KZB "kzuResourceLoadTextureRenderTargetCubeFromKZB"
/** Profiling tag for cubemap render target texture deploy. */
#define KZU_RESOURCE_PROFILING_TEXTURE_RENDER_TARGET_CUBE_DEPLOY "kzuResourceDeployTextureRenderTargetCube"
/** Profiling tag for shader. */
#define KZU_RESOURCE_PROFILING_SHADER_KZB "kzuResourceLoadShaderFromKZB"
/** Profiling tag for shader deploy. */
#define KZU_RESOURCE_PROFILING_SHADER_DEPLOY "kzuResourceDeployShader"
/** Profiling tag for material. */
#define KZU_RESOURCE_PROFILING_MATERIAL_KZB "kzuResourceLoadMaterialFromKZB"
/** Profiling tag for style. */
#define KZU_RESOURCE_PROFILING_STYLE_KZB "kzuResourceLoadStyleFromKZB"
/** Profiling tag for state manager. */
#define KZU_RESOURCE_PROFILING_STATE_MANAGER_KZB "kzuResourceLoadStateManagerFromKZB"
/** Profiling tag for timeline sequence. */
#define KZU_RESOURCE_PROFILING_TIMELINE_SEQUENCE_KZB "kzuResourceLoadTimeLineSequenceFromKZB"
/** Profiling tag for animation clip. */
#define KZU_RESOURCE_PROFILING_ANIMATION_CLIP_KZB "kzuResourceLoadAnimationClipFromKZB"
/** Profiling tag for animation. */
#define KZU_RESOURCE_PROFILING_ANIMATION_KZB "kzuResourceLoadAnimationFromKZB"
/** Profiling tag for composer. */
#define KZU_RESOURCE_PROFILING_COMPOSER_KZB "kzuResourceLoadComposerFromKZB"
/** Profiling tag for object node. */
#define KZU_RESOURCE_PROFILING_OBJECT_NODE_KZB "kzuResourceLoadObjectNodeFromKZB"
/** Profiling tag for prefab template. */
#define KZU_RESOURCE_PROFILING_PREFAB_TEMPLATE_KZB "kzuResourceLoadPrefabTemplateFromKZB"
/** Profiling tag for prefab template. */
#define KZU_RESOURCE_PROFILING_PREFAB_TEMPLATE_NODE_KZB "kzuResourceLoadPrefabTemplateNodeFromKZB"
/** Profiling tag for prefab template. */
#define KZU_RESOURCE_PROFILING_GENERIC_FILE_KZB "kzuResourceLoadGenericFileFromKZB"
/** Profiling tag for trajectory. */
#define KZU_RESOURCE_PROFILING_TRAJECTORY_KZB "kzuResourceLoadTrajectoryFromKZB"
/** Profiling tag for object source. */
#define KZU_RESOURCE_PROFILING_OBJECT_SOURCE_KZB "kzuResourceLoadObjectSourceFromKZB"
/** Profiling tag for font. */
#define KZU_RESOURCE_PROFILING_FONT_KZB "kzuResourceLoadFontFromKZB"
/** Profiling tag for text. */
#define KZU_RESOURCE_PROFILING_TEXT_KZB "kzuResourceLoadTextFromKZB"


KZ_HEADER_END


#endif
