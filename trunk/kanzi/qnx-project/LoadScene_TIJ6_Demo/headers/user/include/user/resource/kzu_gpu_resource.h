/**
 * \file
 * GPU resource.
 * 
 * Copyright 2008-2014 by Rightware. All rights reserved.
 */
#ifndef KZU_GPU_RESOURCE_H
#define KZU_GPU_RESOURCE_H


#include "kzu_resource_common.h"

#include <system/debug/kzs_error.h>
#include <system/kzs_types.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations. */
struct KzcRenderer;


/** Resource type identifier for GPU resources. */
extern const KzuResourceType KZU_RESOURCE_TYPE_GPU_RESOURCE;


/**
 * \struct KzuGPUResource
 * GPU resource is a subtype of resource, which can be deployed to GPU.
 */
struct KzuGPUResource;


/** GPU resource deployment strategy. This specifies when the resource will be deployed and undeployed. */
enum KzuGPUResourceDeploymentStrategy {
    KZU_GPU_RESOURCE_DEPLOYMENT_STRATEGY_DEFAULT, /**< Default strategy. This guarantees that the GPU resource will be deployed before it is needed by the engine.
                                                       The actual strategy can depend on the platform or application. */
    KZU_GPU_RESOURCE_DEPLOYMENT_STRATEGY_MANUAL, /**< Manual deployment strategy. The GPU resource will never be deployed or undeployed automatically by the engine.
                                                      Application must call kzuGPUResourceDeploy manually. */
    KZU_GPU_RESOURCE_DEPLOYMENT_STRATEGY_KEEP, /**< This deployment strategy keeps the GPU resource in GPU memory all the time unless manually undeployed. */
    KZU_GPU_RESOURCE_DEPLOYMENT_STRATEGY_ON_DEMAND /**< This deployment strategy deploys the GPU resource when it is actually needed and undeploys when it is not.
                                                        This strategy is not yet supported. */
};


/** Convert GPU resource to resource. */
struct KzuResource* kzuGPUResourceToResource(const struct KzuGPUResource* gpuResource);
/** Convert resource to GPU resource. */
struct KzuGPUResource* kzuGPUResourceFromResource(const struct KzuResource* resource);

/** Checks if the given resource is a GPU resource. */
kzBool kzuResourceIsGPUResource(const struct KzuResource* resource);

/** Tells the GPU resource to deploy the data to GPU if it has not yet been deployed or has been undeployed. */
kzsError kzuGPUResourceDeploy(struct KzuGPUResource* gpuResource);

/** Tells the GPU resource to undeploy the data from GPU. */
kzsError kzuGPUResourceUndeploy(struct KzuGPUResource* gpuResource);

/** Checks if the given GPU resource has been deployed and is still in GPU memory. */
kzBool kzuGPUResourceIsDeployed(const struct KzuGPUResource* gpuResource);

/**
 * Tells the GPU resource to invalidate the GPU state back to undeployed state without actually undeploying.
 * This is needed e.g. when the GL context is recreated.
 */
kzsError kzuGPUResourceInvalidate(struct KzuGPUResource* gpuResource);

/** Returns the deployment strategy of the GPU resource. */
enum KzuGPUResourceDeploymentStrategy kzuGPUResourceGetDeploymentStrategy(const struct KzuGPUResource* gpuResource);

/** Sets the deployment strategy of the GPU resource. */
void kzuGPUResourceSetDeploymentStrategy(struct KzuGPUResource* gpuResource, enum KzuGPUResourceDeploymentStrategy deploymentStrategy);


/** Returns GPU memory usage of the resource. */
kzUint kzuGPUResourceGetGPUMemoryUsage(const struct KzuGPUResource* gpuResource);


KZ_HEADER_END


#endif
