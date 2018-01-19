/**
* \file
* UI domain merge.
* This component provides mechanism for transfer resources from one UI domain to another.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_UI_DOMAIN_MERGER_H
#define KZU_UI_DOMAIN_MERGER_H


#include <user/common/kzu_user.h>
#include <user/resource/kzu_resource_common.h>
#include <user/scene_graph/kzu_object_common.h>

#include <system/debug/kzs_error.h>
#include <system/kzs_types.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/** UI domain merger error code: conflicting resource URL's during merging. */
#define KZU_UI_DOMAIN_MERGER_ERROR_CONFLICTING_RESOURCE_URLS (1 << 0)
/** UI domain merger error code: resource of non-supported by domain merger type was encountered during merging. */
#define KZU_UI_DOMAIN_MERGER_ERROR_RESOURCES_NOT_SUPPORTED (1 << 1)
/** UI domain merger error code: object node of non-supported by domain merger type was encountered during merging. */
#define KZU_UI_DOMAIN_MERGER_ERROR_OBJECT_NODES_NOT_SUPPORTED (1 << 2)


/* Forward declarations */
struct KzcHashSetIterator;
struct KzcMemoryManager;
struct KzuObjectNode;
struct KzcRenderer;
struct KzuResource;
struct KzuTrigger;
struct KzuUIDomain;

/**
 * \struct KzuUiDomaintMerger
 * UI domain merger structure.
 */
struct KzuUIDomainMerger;


/** Dependency resolver of resource by type. */
typedef kzsError (*KzuUIDomainMergerResourceDependencyResolverFunction)(const struct KzuUIDomainMerger* uiDomainMerger, const struct KzuResource* resource);

/** Dependency resolver of object node by type. */
typedef kzsError (*KzuUIDomainMergerObjectNodeDependencyResolverFunction)(const struct KzuUIDomainMerger* uiDomainMerger, struct KzuObjectNode* objectNode);


/** Creates UI domain merger for merging 2 ui domains. */
kzsError kzuUIDomainMergerCreate(const struct KzcMemoryManager* memoryManager, struct KzuUIDomain* sourceUIDomain, 
                               struct KzuUIDomain* destinationUIDomain, struct KzuUIDomainMerger** out_uiDomainMerger);

/** Creates project merge object with temporal domain where resources can be loaded and after that merged to destination UI domain. */
kzsError kzuUIDomainMergerCreateWithSourceUIDomain(const struct KzcMemoryManager* memoryManager, struct KzuUIDomain* destinationUIDomain, 
                                                   struct KzuUIDomainMerger** out_uiDomainMerger);

/** Deletes project merge object. */
kzsError kzuUIDomainMergerDelete(struct KzuUIDomainMerger* uiDomainMerger);

/** Returns source UI domain. */
struct KzuUIDomain* kzuUIDomainMergerGetSourceUIDomain(const struct KzuUIDomainMerger* uiDomainMerger);

/** Returns destination UI domain. */
struct KzuUIDomain* kzuUIDomainMergerGetDestinationUIDomain(const struct KzuUIDomainMerger* uiDomainMerger);

/**
 * Transfers resources and their properties from one UI domain to another.
 * If there are resources with conflicting URL's not supported resources or object node, 
 * a combination of KZU_UI_DOMAIN_MERGER_ERROR constants will be written to out_mergingResult, 0 otherwise.
 * If merging fails, states of source and target UI domains will remain unchanged, so it is safe to call this function again.
 */
kzsError kzuUIDomainMergerDoMerge(struct KzuUIDomainMerger* uiDomainMerger, kzUint* out_mergeErrors);

/** Get conflicting resource URLs after UI domain merge fails. */
kzBool kzuUIDomainMergerGetConflictingResourceUrls(const struct KzuUIDomainMerger* uiDomainMerger, struct KzcHashSetIterator* out_iterator);
/** Get URLs of non-supported resources after UI domain merge fails. */
kzBool kzuUIDomainMergerGetNotSupportedResourceUrls(const struct KzuUIDomainMerger* uiDomainMerger, struct KzcHashSetIterator* out_iterator);
/** Get paths of non-supported object nodes after UI domain merge fails. */
kzBool kzuUIDomainMergerGetNotSupportedObjectNodePaths(const struct KzuUIDomainMerger* uiDomainMerger, struct KzcHashSetIterator* out_iterator);

/** Registers resource dependency resolver for resource type. */
kzsError kzuUiDomainMergerRegisterResourceDependencyResolver(const struct KzuUIDomainMerger* uiDomainMerger, KzuResourceType resourceType, 
                                                             KzuUIDomainMergerResourceDependencyResolverFunction resourceDependencyResolver);
/** Retrieves resource dependency resolver for resource type if registered. */
kzBool kzuUIDomainMergerGetResourceDependencyResolver(const struct KzuUIDomainMerger* uiDomainMerger, KzuResourceType resourceType, 
                                                      KzuUIDomainMergerResourceDependencyResolverFunction* out_resolverFunction);

/** Registers object node dependency resolver for resource type. */
kzsError kzuUiDomainMergerRegisterObjectNodeDependencyResolver(const struct KzuUIDomainMerger* uiDomainMerger, KzuObjectType objectType, 
                                                               KzuUIDomainMergerObjectNodeDependencyResolverFunction resourceDependencyResolver);
/** Retrieves object node dependency resolver for resource type if registered. */
kzBool kzuUIDomainMergerGetObjectNodeDependencyResolver(const struct KzuUIDomainMerger* uiDomainMerger, KzuObjectType objectType, 
                                                        KzuUIDomainMergerObjectNodeDependencyResolverFunction* out_resolverFunction);

/** Resolves dependencies of trigger. */
kzsError kzuUIDomainMergerTriggerResolveDependencies_internal(const struct KzuUIDomainMerger* uiDomainMerger, struct KzuTrigger* trigger);

/** Logs details about ui domain merger errors. */
void kzuUIDomainMergerLogErrors(const struct KzuUIDomainMerger* uiDomainMerger);


KZ_HEADER_END


#endif
