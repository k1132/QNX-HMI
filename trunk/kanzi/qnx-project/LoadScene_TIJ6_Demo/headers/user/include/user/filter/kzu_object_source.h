/**
* \file
* Object source. Object source that can be coupled with filters.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_OBJECT_SOURCE_H
#define KZU_OBJECT_SOURCE_H


#include "kzu_object_source_common.h"

#include <user/common/kzu_user.h>
#include <user/resource/kzu_resource_common.h>

#include <core/util/collection/kzc_comparator.h>

#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations */
struct KzcDynamicArray;
struct KzcInputStream;
struct KzcMemoryManager;
struct KzuBinaryFileInfo;
struct KzuUIDomain;
struct KzuResource;
struct KzuObjectSource;
struct KzuSortObjectSource;
struct KzuTransformedObjectNode;
struct KzuTransformedScene;


/** Resource type identifier for object source. */
extern const KzuResourceType KZU_RESOURCE_TYPE_OBJECT_SOURCE;


#define KZU_OBJECT_SOURCE_RUNTIME_CHANGE_FLAG_LOD_APPLY_REQUIRED 1 /**< Change flag specifying the LOD Apply is required. */


/**
 * \struct KzuObjectSourceCache
 * Storage for object source cache data.
 */
struct KzuObjectSourceCache;

/**
 * \struct KzuObjectSourceRuntimeData
 * Structure passed as parameter to object source reset.
 */
struct KzuObjectSourceRuntimeData;


/** Creates an object source, which combines several object sources together. */
kzsError kzuCombinerObjectSourceCreate(const struct KzcMemoryManager* memoryManager, struct KzuUIDomain* uiDomain,
                                       kzString name, struct KzuObjectSource** out_objectSource);

/** Deletes an object source. */
kzsError kzuObjectSourceDelete(struct KzuObjectSource* objectSource);


/** Loads combiner object source from KZB. */
kzsError kzuCombinerObjectSourceLoadFromKZB(struct KzuObjectSource* objectSource, struct KzcInputStream* inputStream, const struct KzuBinaryFileInfo* file);

/** Initializes combiner object source. */
kzsError kzuCombinerObjectSourceInitialize(struct KzuObjectSource* objectSource, kzUint inputCount, struct KzuObjectSource* const* inputs);


/** Gets transformed object node from object source. out_objects is filled with transformed object nodes. */
kzsError kzuObjectSourceFetchGraph(const struct KzuObjectSource* objectSource, const struct KzuObjectSourceRuntimeData* runtimeData,
                                   const struct KzuTransformedObjectNode* camera, struct KzcDynamicArray** out_objects);

/** Checks if the object source is an object set filter. */
kzBool kzuObjectSourceIsFilter(const struct KzuObjectSource* objectSource);

/** Sets input data for object source. */
kzsError kzuFilterObjectSourceSetInput(const struct KzuObjectSource* objectSource, struct KzuObjectSource* input);
/** Sets input for object source. In case of root object source does nothing. Combiner object source not supported. */
kzsError kzuObjectSourceSetInput(const struct KzuObjectSource* objectSource, struct KzuObjectSource* inputObjectSource);
/** Gets an input from object source, KZ_NULL if not specified. */
struct KzuObjectSource* kzuObjectSourceGetInput(const struct KzuObjectSource* objectSource);

/** Creates an object for object source reset data. */
kzsError kzuObjectSourceRuntimeDataCreate(const struct KzcMemoryManager* memoryManager, struct KzuTransformedScene* transformedScene,
                                            struct KzuObjectSourceRuntimeData** out_runtimeData);
/** Sets change flag for the object source runtime data. */
void kzuObjectSourceRuntimeDataSetChangeFlag(struct KzuObjectSourceRuntimeData* runtimeData, kzU32 flag);
/** Clears object source runtime data change flag. */
void kzuObjectSourceRuntimeDataClearChangeFlag(struct KzuObjectSourceRuntimeData* runtimeData, kzU32 flag);
/** Returns if specific change flag is set for object source runtime data. */
kzBool kzuObjectSourceRuntimeDataIsChangeFlagSet(const struct KzuObjectSourceRuntimeData* runtimeData, kzU32 flag);

/** Resets object source's runtime data, i.e. cache is cleaned. */
kzsError kzuObjectSourceResetRuntimeOutputData(const struct KzuObjectSource* objectSource, const struct KzuObjectSourceRuntimeData* objectSourceRuntimeData);

/** Returns type of object source. */
enum KzuObjectSourceType kzuObjectSourceGetType(const struct KzuObjectSource* objectSource);

/** Converts object source to resource. */
struct KzuResource* kzuObjectSourceToResource(const struct KzuObjectSource* objectSource);
/** Converts object source from resource. */
struct KzuObjectSource* kzuObjectSourceFromResource(const struct KzuResource* resource);
/** Casts object source from resource, KZ_NULL if invalid type. */
struct KzuObjectSource* kzuObjectSourceCastFromResource(const struct KzuResource* resource);


KZ_HEADER_END


#endif
