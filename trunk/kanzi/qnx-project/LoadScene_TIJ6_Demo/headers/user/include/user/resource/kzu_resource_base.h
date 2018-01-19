/**
 * \file
 * Resource base definitions.
 * 
 * Copyright 2008-2014 by Rightware. All rights reserved.
 */
#ifndef KZU_RESOURCE_BASE_H
#define KZU_RESOURCE_BASE_H


#include "kzu_resource.h"

#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations */
struct KzcInputStream;
struct KzcMemoryManager;
struct KzuBinaryFileInfo;
struct KzuPropertyManager;
struct KzuResourceLoader;
struct KzuResourceLoaderThreadContext;
struct KzuUIDomain;


/** Resource loader thread specific data. */
struct KzuResourceLoaderThreadContext
{
    const struct KzcMemoryManager* memoryManager; /**< Thread safe memory manager. */
    struct KzuPropertyManager* propertyManager; /**< Thread specific Property manager. */
    struct KzsThreadLock* threadLock; /**< Thread specific lock. Needed for locking the property manager. */
};


/** Defines functions for different resource types. */
struct KzuResourceClass
{
    KzuResourceType parentType; /**< Pointer to the parent class. KZ_NULL for the first base class. */

    kzString typeName; /**< Name of the resource class. This is used for internal debugging. */

    /**
     * Destructor function for resource. This function should release the data allocated in the constructor.
     * Implementations should call super class destructor as the last statement.
     */
    kzsError (*destructor)(struct KzuResource* resource);

    /**
     * Function for loading the resource from .KZB. This function is called when loading the data from .KZB file.
     * Implementations should call super class loadFromKZB before reading anything else from inputStream.
     * This function is called from arbitrary loading threads. The parameter threadContext contains thread safe memory
     * manager and a thread specific Property manager which can be locked with the threadLock in the threadContext.
     * This function may not access resource manager or the UIDomain due to race conditions.
     */
    kzsError (*loadFromKZB)(struct KzuResource* resource, const struct KzuResourceLoaderThreadContext* threadContext,
                            struct KzcInputStream* inputStream, struct KzuBinaryFileInfo* file);

    /**
     * Function for finishing the loading of the resource. This function is called in the main thread after loading the data.
     * Implementations should call super class finishLoading first.
     * The parameter threadContext contains thread safe memory manager and the property manager that was used for loading
     * the resource, which can be locked with the threadLock in the threadContext.
     */
    kzsError (*finishLoading)(struct KzuResource* resource, const struct KzuResourceLoaderThreadContext* threadContext);

    /** Unload function for resource. Releases all memory taken by the resource except the resource loader. */
    kzsError (*unload)(struct KzuResource* resource);

    /** Function for getting the memory usage of a resource. */
    kzUint (*getCPUMemoryUsage)(const struct KzuResource* resource);
};


/** Function definition for resource loader load functions. */
typedef kzsError (*KzuResourceLoaderLoadFunction)(struct KzuResource* resource, const struct KzuResourceLoaderThreadContext* threadContext, void* loadData);
/** Function definition for resource loader free data functions. */
typedef kzsError (*KzuResourceLoaderFreeDataFunction)(void* loadData);


/** Resource loading state. */
enum KzuResourceLoadState
{
    KZU_RESOURCE_LOAD_STATE_INVALID, /**< A loader for the resource is not available and no data has been provided for the resource to mark it in LOADED state. */
    KZU_RESOURCE_LOAD_STATE_NOT_LOADED, /**< The resource has not yet been loaded. */
    KZU_RESOURCE_LOAD_STATE_LOADING, /**< The resource is currently loading. */
    KZU_RESOURCE_LOAD_STATE_LOADED /**< The resource has been loaded. */
};


/**
 * Resource dictionary.
 * This allows properties of ResourceID type to be used in resources to make them compatible with the same properties in object nodes.
 */
struct KzuResourceDictionary
{
    struct KzcHashMap* entries; /**< Resources URLs by their IDs. <kzString(resourceID), kzString(resourceURL)>. */
};

struct KzuResource
{
    const struct KzuResourceClass* resourceClass; /**< Class of the resource. */

    struct KzuResourceManager* resourceManager; /**< The resource manager where the resource is registered. */
    kzMutableString name; /**< Name of the resource. */

    struct KzuResourceLoader* loader; /**< Loader for the resource. */

    kzUint referenceCount; /**< Number of references for the resource. Increased in Acquire&AcquireExisting, decreased in Release. */

    enum KzuResourceLoadingStrategy loadingStrategy; /**< Resource loading strategy controls when the resource is loaded and unloaded. */
    enum KzuResourceLoadState loadState; /**< Has the resource been loaded yet. */
};

/**
 * Reference resource is used to store resource dependencies.
 *
 * For example Mesh can have dependencies to materials which have dependencies to shaders. A single resource can have multiple dependencies to the same resource.
 */
struct KzuResourceReferenceResource
{
    struct KzuResource* referencedResource; /**< The referenced resource. */
    kzUint referenceCount; /**< Number of references to the resource. */
};

/** Base class type for resource. */
extern const struct KzuResourceClass KZU_RESOURCE_CLASS;


/** Creates a resource loader. */
kzsError kzuResourceCreateResourceLoader_protected(const struct KzcMemoryManager* memoryManager,
                                                   KzuResourceLoaderLoadFunction load, KzuResourceLoaderFreeDataFunction freeData,
                                                   void* loadData, struct KzuResourceLoader** out_resourceLoader);

/** Base create function for resources. */
kzsError kzuResourceCreate_protected(struct KzuResource* resource, const struct KzuResourceClass* resourceClass,
                                     struct KzuResourceManager* resourceManager, kzString name, struct KzuResourceLoader* loader);

/** Base destructor for resources. */
kzsError kzuResourceDestructor_protected(struct KzuResource* resource);

/** Base set name function for resources. */
kzsError kzuResourceSetName_protected(struct KzuResource* resource, kzString name);

/** Notifies the resource that the data has been set. This must be called for resources without any resource loader after the data has been assigned. */
kzsError kzuResourceStaticDataSet_protected(struct KzuResource* resource);

/** Base function for loading resources from .KZB. */
kzsError kzuResourceLoadFromKZB_protected(struct KzuResource* resource, const struct KzuResourceLoaderThreadContext* threadContext,
                                          struct KzcInputStream* inputStream, struct KzuBinaryFileInfo* file);

/** Base function for finishing the loading of resources. */
kzsError kzuResourceFinishLoading_protected(struct KzuResource* resource, const struct KzuResourceLoaderThreadContext* threadContext);

/** Base function for unloading resources. */
kzsError kzuResourceUnload_protected(struct KzuResource* resource);

/** Base function for getting memory usage of resources. */
kzUint kzuResourceGetCPUMemoryUsage_protected(const struct KzuResource* resource);


KZ_HEADER_END


#endif
