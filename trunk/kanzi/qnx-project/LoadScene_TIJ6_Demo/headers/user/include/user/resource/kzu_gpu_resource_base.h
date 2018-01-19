/**
 * \file
 * GPU resource base definitions.
 * 
 * Copyright 2008-2014 by Rightware. All rights reserved.
 */
#ifndef KZU_GPU_RESOURCE_BASE_H
#define KZU_GPU_RESOURCE_BASE_H


#include "kzu_gpu_resource.h"
#include "kzu_resource_base.h"

#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations. */
struct KzcMemoryManager;
struct KzuUIDomain;


/** Defines functions for different resource types. */
struct KzuGPUResourceClass
{
    struct KzuResourceClass base; /**< Inherited from KzuResourceClass. */

    /** Deploy function for GPU resource. */
    kzsError (*deploy)(struct KzuGPUResource* gpuResource);

    /** Undeploy function for GPU resource. */
    kzsError (*undeploy)(struct KzuGPUResource* gpuResource);

    /** Free RAM function for GPU resource. */
    kzsError (*freeCommonData)(struct KzuGPUResource* gpuResource);

    /** Invalidate function for GPU resource. */
    kzsError (*invalidate)(struct KzuGPUResource* gpuResource);

    /** Function for getting the GPU memory usage of a GPU resource. */
    kzUint (*getGPUMemoryUsage)(const struct KzuGPUResource* gpuResource);
};


/** GPU resource class. */
extern const struct KzuGPUResourceClass KZU_GPU_RESOURCE_CLASS;

/** GPU resource deployment state. */
enum KzuGPUResourceDeployState
{
    KZU_GPU_RESOURCE_DEPLOYMENT_STATE_NOT_DEPLOYED, /**< The GPU resource has not yet been deployed. */
    KZU_GPU_RESOURCE_DEPLOYMENT_STATE_DEPLOYING, /**< The GPU resource deployment is in progress. */
    KZU_GPU_RESOURCE_DEPLOYMENT_STATE_DEPLOYED /**< The GPU resource has been deployed. */

};


struct KzuGPUResource
{
    struct KzuResource resource; /**< Inherited from KzuResource. */

    enum KzuGPUResourceDeploymentStrategy deploymentStrategy; /**< Deployment straget controls when the resource is deployed to the GPU and undeployed. */
    enum KzuGPUResourceDeployState deployState; /**< State of deployment for GPU resource. */
};


/** Base function for creating GPU resources. All GPU resource constructors should call this first. */
kzsError kzuGPUResourceCreate_protected(struct KzuGPUResource* gpuResource, const struct KzuGPUResourceClass* resourceClass,
                                        struct KzuResourceManager* resourceManager, kzString name, struct KzuResourceLoader* loader);

/** Base destructor for GPU resources. */
kzsError kzuGPUResourceDestructor_protected(struct KzuResource* resource);

/** Base function for loading GPU resources from .KZB. */
kzsError kzuGPUResourceLoadFromKZB_protected(struct KzuResource* resource, const struct KzuResourceLoaderThreadContext* threadContext,
                                             struct KzcInputStream* inputStream, struct KzuBinaryFileInfo* file);

/** Base function for finishing the loading of GPU resources. */
kzsError kzuGPUResourceFinishLoading_protected(struct KzuResource* resource, const struct KzuResourceLoaderThreadContext* threadContext);

/** Base function for unloading GPU resources. */
kzsError kzuGPUResourceUnload_protected(struct KzuResource* resource);

/** Base function for getting CPU memory usage of GPU resources. */
kzUint kzuGPUResourceGetCPUMemoryUsage_protected(const struct KzuResource* resource);

/** Base function for deploying GPU resources. */
kzsError kzuGPUResourceDeploy_protected(struct KzuGPUResource* gpuResource);

/** Base function for undeploying GPU resources. */
kzsError kzuGPUResourceUndeploy_protected(struct KzuGPUResource* gpuResource);

/** Base function for freeing RAM of GPU resources. */
kzsError kzuGPUResourceFreeCommonData_protected(struct KzuGPUResource* gpuResource);

/** Base function for invalidating GPU resources. */
kzsError kzuGPUResourceInvalidate_protected(struct KzuGPUResource* gpuResource);

/** Base function for getting GPU memory usage of GPU resources. */
kzUint kzuGPUResourceGetGPUMemoryUsage_protected(const struct KzuGPUResource* gpuResource);

/** Gets the renderer needed for the GPU resource. */
struct KzcRenderer* kzuGPUResourceGetRenderer_protected(const struct KzuGPUResource* gpuResource);


KZ_HEADER_END


#endif
