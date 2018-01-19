/**
 * \file
 * Binary resource.
 * 
 * Copyright 2008-2014 by Rightware. All rights reserved.
 */
#ifndef KZU_BINARY_RESOURCE_H
#define KZU_BINARY_RESOURCE_H


#include "kzu_resource_common.h"

#include <system/debug/kzs_error.h>
#include <system/kzs_types.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations */
struct KzuResourceManager;
struct KzuResource;
struct KzuBinaryFileInfo;
struct KzcInputStream;


/**
 * \struct KzuBinaryResource
 * Binary resource.
 */
struct KzuBinaryResource;


/** Resource type identifier for binary resource. */
extern const KzuResourceType KZU_RESOURCE_TYPE_BINARY_RESOURCE;


/** Creates a binary resource. */
kzsError kzuBinaryResourceCreate(struct KzuResourceManager* resourceManager, kzString name,
                                 struct KzuBinaryResource** out_binaryResource);


/** Convert binary resource to resource. */
struct KzuResource* kzuBinaryResourceToResource(const struct KzuBinaryResource* binaryResource);
/** Convert resource to binary resource. */
struct KzuBinaryResource* kzuBinaryResourceFromResource(const struct KzuResource* resource);
/** Casts binary resource from resource, KZ_NULL if invalid type. */
struct KzuBinaryResource* kzuBinaryResourceCastFromResource(const struct KzuResource* resource);

/** Returns resource data. */
const kzByte* kzuBinaryResourceGetData(const struct KzuBinaryResource* binaryResource);
/** Returns resource data size. */
kzUint kzuBinaryResourceGetDataSize(const struct KzuBinaryResource* binaryResource);

/** Loads resource wrapper from KZB. */
kzsError kzuBinaryResourceLoadFromKZB(struct KzuBinaryResource* binaryResource, struct KzcInputStream* inputStream, const struct KzuBinaryFileInfo* file);


KZ_HEADER_END


#endif
