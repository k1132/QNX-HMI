/**
 * \file
 * Resource manager.
 * 
 * Copyright 2008-2014 by Rightware. All rights reserved.
 */
#ifndef KZU_RESOURCE_MANAGER_H
#define KZU_RESOURCE_MANAGER_H


#include "kzu_resource_common.h"

#include <system/debug/kzs_error.h>
#include <system/kzs_types.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations */
struct KzcMemoryManager;
struct KzcRenderer;
struct KzuBinaryDirectory;
struct KzuResource;
struct KzcDynamicArray;


/** Resource manager memory strategy. */
enum KzuResourceManagerMemoryStrategy
{
    /** With this setting, when a resource is no longer referenced, resource manager keeps it in memory until \ref kzuResourceManagerPurge() is called. */
    KZU_RESOURCE_MANAGER_MEMORY_STRATEGY_KEEP_IN_MEMORY,

    /** With this setting, when a resource is no longer referenced, resource manager deletes it and frees the (CPU and GPU) memory used by the resource. */
    KZU_RESOURCE_MANAGER_MEMORY_STRATEGY_OPTIMIZE_MEMORY
};


/**
 * \struct KzuResourceManagerLoadCallbackData
 * Structure for passing required resource manager objects to core layer when needed.
 */
struct KzuResourceManagerLoadCallbackData
{
    struct KzuBinaryDirectory* directory; /**< Binary directory. */
    const struct KzuBinaryFileInfo* file; /**< File reference. */
};


/**
 * \struct KzuResourceManager
 * Resource manager is responsible for loading and unloading of all resources.
 */
struct KzuResourceManager;


/**
 * Protocol handler function type definition.
 *
 * \param resourceURL The full URL of the resource in the form of protocol://hostname[:port]/path.
 * \param protocol Extracted protocol part of the resource URL.
 * \param hostname Extracted hostname part of the resource URL.
 * \param port Extracted port part of the resource URL. This is 0 if the port is omitted from the URL.
 * \param path Extracted path part of the resource URL.
 * \param userData The userData object passed as parameter for kzuResourceManagerRegisterProtocolHandler().
 * \return Can return ::KZU_EXCEPTION_FILE_NOT_FOUND if the resource cannot be loaded.
 */
typedef kzsException (*KzuResourceManagerProtocolHandler)(struct KzuResourceManager* resourceManager, kzString resourceURL,
                                                          kzString protocol, kzString hostname, kzUint port, kzString path,
                                                          void* userData, struct KzuResource** out_resource);


/** Creates a resource manager. */
kzsError kzuResourceManagerCreate(const struct KzcMemoryManager* memoryManager, struct KzcRenderer* renderer,
                                  struct KzuResourceManager** out_resourceManager);

/** Deletes a resource manager. */
kzsError kzuResourceManagerDelete(struct KzuResourceManager* resourceManager);

/**
 * Initializes additional resource loader threads for resource manager, which process the resource loading in parallel.
 * The initialization should be executed only once, after the resource manager has been created.
 * \param threadCount Number of loader threads. If 0, parallel loading is disabled.
 * \param loaderMemoryManagerSize Memory manager size for resource loading, required to hold the allocated resource data. No effect if threadCount is 0.
 */
kzsError kzuResourceManagerInitializeLoaderThreads(struct KzuResourceManager* resourceManager, kzUint threadCount, kzUint loaderMemoryManagerSize);
/** Uninitalizes loader threads from resource manager. This function should be possible to be called at any time. */
kzsError kzuResourceManagerUninitializeLoaderThreads(struct KzuResourceManager* resourceManager);

/** Adds binary directory to resource manager. This transfers the ownership of the binary directory to the resource manager. */
kzsError kzuResourceManagerAddDirectory(const struct KzuResourceManager* resourceManager, const struct KzuBinaryDirectory* directory);
/** Removes binary directory to resource manager. */
kzsError kzuResourceManagerRemoveDirectory(const struct KzuResourceManager* resourceManager, const struct KzuBinaryDirectory* directory);
/** Gets the binary directory with the given name from resource manager.
 * \return ::KZ_NULL if a directory is not found.
 */
struct KzuBinaryDirectory* kzuResourceManagerGetDirectory(const struct KzuResourceManager* resourceManager, kzString name);
/** Gets all directories from binary loader.
 * \return A hash map where keys are binary directory names (::kzString) and values are the directories (struct ::KzuBinaryDirectory*).
 */
const struct KzcHashMap* kzuResourceManagerGetDirectories(const struct KzuResourceManager* resourceManager);

/** Tells the resource manager to load all resources from queue. Waits until load queue is empty, including the loader threads. */
kzsError kzuResourceManagerLoadAllResources(struct KzuResourceManager* resourceManager);

/** Tells the resource manager to deploy all GPU resources from queue. */
kzsError kzuResourceManagerDeployAllGPUResources(const struct KzuResourceManager* resourceManager);

/** Tells the resource manager to undeploy all GPU resources. */
kzsError kzuResourceManagerUndeployAllGPUResources(struct KzuResourceManager* resourceManager);

/**
 * Tells the resource manager to invalidate all GPU resource states back to undeployed state without actually undeploying.
 * This is needed e.g. when the GL context is recreated.
 */
kzsError kzuResourceManagerInvalidateAllGPUResources(struct KzuResourceManager* resourceManager);

/**
 * Queries information about memory usage. The information is returned for every type covered by given resourceType parameter.
 * Passing ::KZU_RESOURCE_TYPE_RESOURCE as the type will return information about all resources.
 * Passing ::KZU_RESOURCE_TYPE_GPU_RESOURCE as the type will return information about all GPU resources.
 * Passing the RESOURCE_TYPE of any specific resource such as mesh will return information only about such resources.
 */
kzsError kzuResourceManagerGetMemoryUsage(const struct KzuResourceManager* resourceManager, const KzuResourceType resourceType,
                                          kzUint* out_resourceCount, kzUint* out_cpuMemoryUsage, kzUint* out_gpuMemoryUsage);


/**
 * Controls resource CPU memory usage.
 * Normally when GPU resources are deployed, they are optionally unloaded from CPU memory depending on their loading strategy.
 * If this flag is set, the loading strategy is ignored and the resource is always kept in CPU memory after deployment.
 */
void kzuResourceManagerSetKeepGPUResourcesInCPUMemory(struct KzuResourceManager* resourceManager, kzBool keepGPUResourcesInCPUMemory);


/** Gets the renderer of the resource manager. */
struct KzcRenderer* kzuResourceManagerGetRenderer(const struct KzuResourceManager* resourceManager);
/** Gets UI domain from resource manager. */
struct KzuUIDomain* kzuResourceManagerGetUIDomain(const struct KzuResourceManager* resourceManager);

/** Registers the given protocol handler for loading resources specified with the given resource URL protocol (scheme name). */
kzsError kzuResourceManagerRegisterProtocolHandler(const struct KzuResourceManager* resourceManager, kzString protocol,
                                                   KzuResourceManagerProtocolHandler handler, void* userData);
/** Unregisters the protocol handler with the given resource URL protocol (scheme name). */
kzsError kzuResourceManagerUnregisterProtocolHandler(const struct KzuResourceManager* resourceManager, kzString protocol);
/** Checks if the given resource URL protocol (scheme name) is registered as a protocol handler for the resource manager. */
kzBool kzuResourceManagerSupportsProtocolHandler(const struct KzuResourceManager* resourceManager, kzString protocol);

/**
 * Acquires resource from resource manager based on given URL.
 * If resource is already loaded, increases the reference count and returns the loaded resource.
 * This function first queries from the Localization manager for a localized version of the resource URL.
 * \param out_resource Output resource or KZ_NULL. Can be ::KZ_NULL.
 * \return Can return ::KZU_EXCEPTION_FILE_NOT_FOUND if the resource cannot be loaded.
 */
kzsException kzuResourceManagerAcquireResource(struct KzuResourceManager* resourceManager, kzString url, struct KzuResource** out_resource);
/** Adds the resource with the given URL to resource manager. */
kzsError kzuResourceManagerAddResource(const struct KzuResourceManager* resourceManager, kzString url, struct KzuResource* resource);
/** Removes a resource with the given URL from resource manager. */
kzsError kzuResourceManagerRemoveResource(const struct KzuResourceManager* resourceManager, kzString url);
/** \return Resource with given url from resource manager storage. ::KZ_NULL if none exists. */
struct KzuResource* kzuResourceManagerGetResource(const struct KzuResourceManager* resourceManager, kzString url);
/** \return Resource URL from resource manager, ::KZ_NULL if not found. */
kzString kzuResourceManagerGetResourceURL(const struct KzuResourceManager* resourceManager, const struct KzuResource* resource);
/** Gets resource path from resource URL. Returns ::KZ_NULL if the URL is malformed. */
kzString kzuResourceManagerGetResourcePathFromURL(kzString resourceURL);

/** Gets relative path from absolute path (relative to screen). */
kzString kzuResourceManagerGetRelativePathFromAbsolutePath(kzString absolutePath);

/** Gets the resource type of a URL pointing to .KZB file. Returns ::KZ_NULL if the URL does not point to a .KZB resource file. */
kzsError kzuResourceManagerGetResourceTypeForKZBURL(const struct KzuResourceManager* resourceManager, kzString url,
                                                    KzuResourceType* out_resourceType);

/** Sets default memory strategy. */
void kzuResourceManagerSetDefaultMemoryStrategy(struct KzuResourceManager* resourceManager, enum KzuResourceManagerMemoryStrategy resourceReleaseStrategy);
/** Gets default memory strategy. */
enum KzuResourceManagerMemoryStrategy kzuResourceManagerGetDefaultMemoryStrategy(const struct KzuResourceManager* resourceManager);

/** Deletes unreferenced resources. */
kzsError kzuResourceManagerPurge(struct KzuResourceManager* resourceManager);

/**
 * Processes resource manager load and deployment queues. This function ensures that all immediately needed resources are loaded and deployed.
 * Resources marked for preloading will be deployed progressively.
 */
kzsError kzuResourceManagerUpdate(struct KzuResourceManager* resourceManager);

/**
 * Creates a background task that loads and deploys all resources from a set of URLs. After all resources are loaded and deployed, calls the provided callback.
 * The callback happens always in the main thread.
 */
kzsError kzuResourceManagerPreloadResources(struct KzuResourceManager* resourceManager, const struct KzcDynamicArray* preloadURLs,
                                            kzsError (*loadedCallback)(void* userData), void* userData);


KZ_HEADER_END


#endif
