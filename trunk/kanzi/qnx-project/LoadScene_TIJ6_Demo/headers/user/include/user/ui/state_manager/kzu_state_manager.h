/**
* \file
* State manager.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_STATE_MANAGER_H
#define KZU_STATE_MANAGER_H


#include <user/resource/kzu_resource_common.h>

#include <system/kzs_types.h>
#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations. */
struct KzuPropertyManager;
struct KzuObjectNode;
struct KzuUIDomain;
struct KzuResource;
struct KzuBinaryFileInfo;
struct KzcInputStream;
struct KzcDynamicArray;
struct KzcMemoryManager;


/**
 * \struct KzuStateManager
 * State manager for managing states of nodes or application.
 */
struct KzuStateManager;

/**
 * \struct KzuStateManagerRuntime
 * State manager runtime state.
 */
struct KzuStateManagerRuntime;


/** Resource type identifier for state manager. */
extern const KzuResourceType KZU_RESOURCE_TYPE_STATE_MANAGER;


/** Create an empty state manager. */
kzsError kzuStateManagerCreateEmpty(const struct KzcMemoryManager* memoryManager, struct KzuUIDomain* uiDomain,
                                    kzString name, struct KzuStateManager** out_stateManager);

/** Create a state manager. */
kzsError kzuStateManagerCreate(const struct KzcMemoryManager* memoryManager, struct KzuUIDomain* uiDomain,
                               kzString name, struct KzuStateManager** out_stateManager);

/** Delete a state manager. */
kzsError kzuStateManagerDelete(struct KzuStateManager* stateManager);


/** Attempt to go to a state. */
kzsError kzuStateManagerGoToStateAsync(struct KzuObjectNode* objectNode, kzString stateName);

/** Load a state manager from kzb. */
kzsError kzuStateManagerLoadFromKZB(struct KzuStateManager* stateManager, struct KzcInputStream* inputStream, const struct KzuBinaryFileInfo* file);


/** Get the property manager of a state manager. */
struct KzuPropertyManager* kzuStateManagerGetPropertyManager(const struct KzuStateManager* stateManager);

/** Attach a state manager. */
kzsError kzuStateManagerAttach(struct KzuStateManager* stateManager, struct KzuObjectNode* objectNode, struct KzuStateManagerRuntime** out_stateManagerRuntime);
/** Detach a state manager. */
kzsError kzuStateManagerDetach(struct KzuStateManagerRuntime* stateManagerRuntime);

/** Gets state manager from state manager runtime. */
struct KzuStateManager* kzuStateManagerRuntimeGetStateManager(const struct KzuStateManagerRuntime* stateManagerRuntime);

/** Converts state manager to resource. */
struct KzuResource* kzuStateManagerToResource(const struct KzuStateManager* stateManager);
/** Converts state manager from resource. */
struct KzuStateManager* kzuStateManagerFromResource(const struct KzuResource* resource);
/** Casts state manager from resource, KZ_NULL if invalid type. */
struct KzuStateManager* kzuStateManagerCastFromResource(const struct KzuResource* resource);

/** Sets UI domain to state manager. */
void kzuStateManagerSetUIDomain(struct KzuStateManager* stateManager, struct KzuUIDomain* uiDomain);


KZ_HEADER_END


#endif
