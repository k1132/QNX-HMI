/**
* \file
* Object source private members.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_OBJECT_SOURCE_BASE_H
#define KZU_OBJECT_SOURCE_BASE_H


#include "kzu_object_source_common.h"

#include <user/common/kzu_user.h>
#include <user/resource/kzu_resource_base.h>

#include <system/kzs_types.h>
#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations */
struct KzcDynamicArray;
struct KzcInputStream;
struct KzcMatrix4x4;
struct KzcMemoryManager;
struct KzuBinaryFileInfo;
struct KzuCameraNode;
struct KzuFilterObjectSource;
struct KzuObjectSourceRuntimeData;
struct KzuUIDomain;
struct KzuSortObjectSource;
struct KzuTransformedObjectNode;


/* Filters */

/** Function type for per frame filter initialization. */
typedef kzsError (*KzuFilterResetFunction)(struct KzuFilterObjectSource* filterObjectSource,
                                           const struct KzuObjectSourceRuntimeData* runtimeData);
/** Function type for filter start function. This is called just before apply, but only once per frame */
typedef kzsError (*KzuFilterStartFunction)(struct KzuFilterObjectSource* filterObjectSource,
                                           const struct KzuObjectSourceRuntimeData* runtimeData,
                                           const struct KzuTransformedObjectNode* camera,
                                           const struct KzcDynamicArray* inputObjects);
/** Function type for cleaning up filter. */
typedef kzsError (*KzuFilterDeleteFunction)(struct KzuFilterObjectSource* filterObjectSource);
/** Function type for determining whether to accept given object or not. */
typedef kzsError (*KzuFilterApplyFunction)(struct KzuFilterObjectSource* filterObjectSource,
                                           const struct KzuObjectSourceRuntimeData* runtimeData,
                                           const struct KzuTransformedObjectNode* camera,
                                           const struct KzuTransformedObjectNode* object,
                                           kzBool* out_accepted);


/** Configuration for filter types. */
struct KzuFilterConfiguration
{
    KzuFilterStartFunction startFunction; /**< Function to call every frame in the beginning of apply. Can be KZ_NULL. */
    KzuFilterDeleteFunction deleteFunction; /**< Function which is called when the filter is deleted. Can be KZ_NULL. */
    KzuFilterApplyFunction applyFunction; /**< Function to use for evaluation whether a specific object will be included or not. */
};


/* Sort */

/** Function type for per frame sort object source initialization. */
typedef kzsError (*KzuSortObjectSourceResetFunction)(struct KzuSortObjectSource* sortObjectSource,
                                                     const struct KzuObjectSourceRuntimeData* runtimeData);
/** Function type for sort start function. This is called just before sorting. */
typedef kzsError (*KzuSortObjectSourceStartFunction)(struct KzuSortObjectSource* sortObjectSource,
                                                     const struct KzuObjectSourceRuntimeData* runtimeData,
                                                     const struct KzuTransformedObjectNode* camera,
                                                     const struct KzcDynamicArray* inputObjects);
/** Function type for cleaning up sort object source. */
typedef kzsError (*KzuSortObjectSourceDeleteFunction)(struct KzuSortObjectSource* sortObjectSource);
/** Function type for sorting transformed object nodes with sort object sources. */
typedef kzInt (*KzuSortObjectSourceComparatorFunction)(const struct KzuTransformedObjectNode* first,
                                                       const struct KzuTransformedObjectNode* second,
                                                       const struct KzcMatrix4x4* cameraMatrix,
                                                       const struct KzuObjectSourceRuntimeData* runtimeData);

/** Configuration for sort object sources. */
struct KzuSortObjectSourceConfiguration
{
    KzuSortObjectSourceStartFunction startFunction; /**< Function to call just before sorting. Can be KZ_NULL. */
    KzuSortObjectSourceDeleteFunction deleteFunction; /**< Function which is called when the sort object source is deleted. Can be KZ_NULL. */
    KzuSortObjectSourceComparatorFunction comparator; /**< Comparator function to use for sorting objects. */
};

/** Structure for object source. */
struct KzuObjectSource
{
    struct KzuResource resource; /**< Resource where object source is inherited. */
    enum KzuObjectSourceType type;  /**< Type of object source. */
};

/** Structure for filter object source. */
struct KzuFilterObjectSource
{
    struct KzuObjectSource objectSource; /**< Object source. Used for inheritance. */
    struct KzuObjectSource* input; /**< Object source that goes in filter. */

    kzBool isExclusive; /**< Is this filter exclusive. */
    kzBool applyRequired; /**< Is apply for filter required. */
    
    const struct KzuFilterConfiguration* configuration; /**< Filter type configuration. */
};

/** Sort object source. This sorts the object list according to specified comparator. */
struct KzuSortObjectSource
{
    struct KzuObjectSource objectSource; /**< Object source. Used for inheritance. */
    struct KzuObjectSource* input; /**< Input object source. */
    const struct KzuSortObjectSourceConfiguration* configuration; /**< Sort configuration. */
};

struct KzuObjectSourceRuntimeData
{
    struct KzuTransformedScene* transformedScene; /**< Transformed scene the runtime data was extracted from. */
    struct KzcDynamicArray* allTransformedObjects; /**< All transformed objects of the scene. */

    kzU32 changeFlags; /**< Change flags of the runtime data. */

    struct KzcHashMap* objectSourceOutputs; /**< Cached outputs for object sources. <KzuObjectSource,KzcDynamicArray<KzuObjectNode>>. */
    struct KzcHashMap* objectSourceCameras; /**< Cached cameras for object sources. <KzuObjectSource, KzuTransformedObjectNode>. */
    struct KzcHashMap* objectSourceCacheDatas; /**< Arbitrary object source specific data. <KzuObjectSourceData,void>. */
};


/** Creates an object source. */
kzsError kzuObjectSourceCreate_protected(enum KzuObjectSourceType type, struct KzuUIDomain* uiDomain, kzString name,
                                         struct KzuObjectSource* objectSource);

/** Creates a filter object source. */
kzsError kzuFilterObjectSourceCreate_protected(const struct KzuFilterConfiguration* configuration, struct KzuUIDomain* uiDomain,
                                               kzString name, struct KzuFilterObjectSource* filterObjectSource);

/** Loads a filter object source from KZB. */
kzsError kzuFilterObjectSourceLoadFromKZB_protected(struct KzuFilterObjectSource* filterObjectSource, struct KzcInputStream* inputStream,
                                                    const struct KzuBinaryFileInfo* file);

/** Initializes a filter object source. */
kzsError kzuFilterObjectSourceInitialize_protected(struct KzuFilterObjectSource* filterObjectSource, struct KzuObjectSource* input,
                                                   kzBool isExclusive);

/** Converts an object source into a filter object source */
struct KzuFilterObjectSource* kzuFilterObjectSourceFromObjectSource_protected(const struct KzuObjectSource* objectSource);


/** Store the cache data for an object source. */
kzsError kzuObjectSourceSetRuntimeCacheData_protected(const struct KzuObjectSource* objectSource,
                                                      const struct KzuObjectSourceRuntimeData* runtimeData,
                                                      const void* data);

/** Get the cache data of an object source. */
void* kzuObjectSourceGetRuntimeCacheData_protected(const struct KzuObjectSource* objectSource,
                                                   const struct KzuObjectSourceRuntimeData* runtimeData);


KZ_HEADER_END


#endif
