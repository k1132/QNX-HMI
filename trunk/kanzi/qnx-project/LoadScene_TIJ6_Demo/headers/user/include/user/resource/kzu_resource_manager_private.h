/**
 * \file
 * Resource manager private definitions.
 * 
 * Copyright 2008-2014 by Rightware. All rights reserved.
 */
#ifndef KZU_RESOURCE_MANAGER_PRIVATE_H
#define KZU_RESOURCE_MANAGER_PRIVATE_H


#include <system/debug/kzs_error.h>
#include <system/kzs_types.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations */
struct KzsThreadLock;
struct KzcDynamicArray;
struct KzcMemoryManager;
struct KzuBinaryDirectory;
struct KzuPropertyManager;
struct KzuGPUResource;
struct KzuUIDomain;
struct KzuResource;
struct KzuResourceLoaderThreadContext;
struct KzuResourceManager;


/** Adds a resource to resource manager. Resources themselves are responsible for adding them, so this function is not public. */
kzsError kzuResourceManagerAddResource_private(const struct KzuResourceManager* resourceManager, const struct KzuResource* resource);

/** Removes a resource from resource manager. Resources themselves are responsible for removing them, so this function is not public. */
kzsError kzuResourceManagerRemoveResource_private(const struct KzuResourceManager* resourceManager, const struct KzuResource* resource);

/** Notifies the resource manager that a resource loading has been processed and it can be placed to the queue for finishing the loading in the main thread. */
kzsError kzuResourceManagerEnqueueResourceFinishLoading_private(const struct KzuResourceManager* resourceManager, struct KzuResource* resource,
                                                                const struct KzuResourceLoaderThreadContext* threadContext);

/** Notifies the resource manager that a resource has been fully loaded. */
kzsError kzuResourceManagerResourceLoaded_private(struct KzuResourceManager* resourceManager, const struct KzuResource* resource,
                                                  kzBool forcePrioritizeResource);

/** Notifies the resource manager that a resource has been unloaded. */
kzsError kzuResourceManagerResourceUnloaded_private(const struct KzuResourceManager* resourceManager, const struct KzuResource* resource);

/** Notifies the resource manager that a GPU resource has been deployed. */
kzsError kzuResourceManagerGPUResourceDeployed_private(struct KzuResourceManager* resourceManager, const struct KzuGPUResource* gpuResource);

/** Notifies the resource manager that a GPU resource has been undeployed. */
kzsError kzuResourceManagerGPUResourceUndeployed_private(const struct KzuResourceManager* resourceManager, const struct KzuGPUResource* gpuResource);

/** Notifies the resource manager that the common data of a GPU resource has been freed. */
kzsError kzuResourceManagerGPUResourceCommonDataFreed_private(const struct KzuResourceManager* resourceManager, const struct KzuGPUResource* gpuResource);

/** Notifies the resource manager that a GPU resource has been invalidated. */
kzsError kzuResourceManagerGPUResourceInvalidated_private(struct KzuResourceManager* resourceManager, const struct KzuGPUResource* gpuResource);

/** Notifies the resource manager that a reference count of a resource has been updated due to acquire or release. */
kzsError kzuResourceManagerResourceReferenceCountUpdated_private(const struct KzuResourceManager* resourceManager, struct KzuResource* resource);

/** Helper function for setting project to resource manager. */
kzsError kzuResourceManagerSetUIDomain_private(struct KzuResourceManager* resourceManager, struct KzuUIDomain* uiDomain);

/* TODO: project merge specific function. Remove it after project merge became obsolete. */
/** Returns the array of all resources registered in resource manager. caller of this function should delete returned array. */
kzsError kzuResourceManagerGetResources_private(const struct KzuResourceManager* resourceManager, struct KzcDynamicArray** out_resources);

/** Adds property manager object to resource manager, which shall be merged to main property manager. Used for loading resources in secondary thread, which contain properties and separate 
    property manager, and need to be transfered to main property manager. */
kzsError kzuResourceManagerAddPropertyManagerObject_private(const struct KzcMemoryManager* memoryManager, const struct KzuResourceManager* resourceManager, const struct KzuResource* resource, 
                                                            struct KzuPropertyManager* propertyManager, struct KzcDynamicArray* propertyTypes, struct KzcDynamicArray* propertyGroups);

/** Gets the resource loader thread context for the main thread. */
const struct KzuResourceLoaderThreadContext* kzuResourceManagerGetMainThreadContext_private(const struct KzuResourceManager* resourceManager);

/**
 * Processes resource manager load and deployment queues. This function ensures that all immediately needed resources are loaded and deployed.
 * Resources marked for preloading will be deployed progressively if preloading is KZ_TRUE.
 */
kzsError kzuResourceManagerUpdate_private(struct KzuResourceManager* resourceManager, kzBool preloading);

/** Tries to stop resource loading as soon as possible. If the loading has already started in a loader thread, waits until the resource is loaded. */
kzsError kzuResourceManagerInterceptResourceLoading_private(struct KzuResourceManager* resourceManager, struct KzuResource* resource);

/** Marks the resource as prioritized. Prioritized resources will be loaded and deployed on the next call to kzuResourceManagerUpdate(). */
kzsError kzuResourceManagerPrioritizeResource_private(struct KzuResourceManager* resourceManager, const struct KzuResource* resource);

/** Deployes the resource if it is a GPU resource and it has been enqueued for deployment (not for progressive deployment). */
kzsError kzuResourceManagerDeployIfQueued_private(struct KzuResourceManager* resourceManager, const struct KzuResource* resource);

/**
 * Increments or decrements the number of pending resources in the resource manager. This function acquires the required lock.
 * \param resourceManager The resource manager object holding the counter for pending resources.
 * \param amount If amount == 1, the pending resource count is incremented. If amount == -1, the pending resource count is decremented. Other values are invalid.
 */
kzsError kzuResourceManagerUpdatePendingResourceCount_private(struct KzuResourceManager* resourceManager, kzInt amount);

/* TODO: project merge specific function. Remove it after project merge became obsolete. */
/** Transfers the given resource from its current resource manager to the target resource manager. */
kzsError kzuResourceManagerTransferResources_private(const struct KzuResourceManager* sourceResourceManager, struct KzuResourceManager* targetResourceManager);

/* TODO: project merge specific function. Remove it after project merge became obsolete. */
/** Copies binary directories from one resource manager to another. */
kzsError kzuResourceManagerTransferDirectories_private(const struct KzuResourceManager* sourceResourceManager, const struct KzuResourceManager* targetResourceManager);


KZ_HEADER_END


#endif
