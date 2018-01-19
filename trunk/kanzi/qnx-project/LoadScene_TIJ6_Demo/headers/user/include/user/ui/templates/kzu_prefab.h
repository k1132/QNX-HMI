/**
* \file
* Prefab objects.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_PREFAB_H
#define KZU_PREFAB_H


#include <user/resource/kzu_resource_common.h>
#include <user/scene_graph/kzu_object_common.h>

#include <core/util/collection/kzc_dynamic_array.h>

#include <system/kzs_types.h>
#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations. */
struct KzcMemoryManager;
struct KzuUIDomain;
struct KzuPropertyManager;
struct KzuObjectNode;
struct KzuTimeLineSequence;
struct KzcInputStream;
struct KzuBinaryFileInfo;


/**
 * \struct KzuPrefabTemplate
 * Prefab template object.
 */
struct KzuPrefabTemplate;

/**
 * \struct KzuPrefabTemplateNode
 * Prefab template node.
 */
struct KzuPrefabTemplateNode;


/** Resource type identifier for prefab template */
extern const KzuResourceType KZU_RESOURCE_TYPE_PREFAB_TEMPLATE;
/** Resource type identifier for prefab template node. */
extern const KzuResourceType KZU_RESOURCE_TYPE_PREFAB_TEMPLATE_NODE;


/** Type of prefab template. */
enum KzuPrefabTemplateType
{
    KZU_PREFAB_TEMPLATE_TYPE_OBJECT,
    KZU_PREFAB_TEMPLATE_TYPE_LAYER
};


/** Creates a prefab template node for basic object types such as Mesh, Light, Instantiator etc. */
kzsError kzuPrefabTemplateNodeCreateBasic(const struct KzcMemoryManager* memoryManager, struct KzuUIDomain* uiDomain, kzString name,
                                          struct KzuObjectNode* referenceObjectNode, struct KzuPrefabTemplateNode** out_prefabTemplateNode);
/** Creates a prefab template with type identifier. This is used for UI components and Layers. */
kzsError kzuPrefabTemplateNodeCreateTyped(const struct KzcMemoryManager* memoryManager, struct KzuUIDomain* uiDomain, kzString name,
                                          struct KzuObjectNode* referenceObjectNode, KzuObjectType typeIdentifier,
                                          struct KzuPrefabTemplateNode** out_prefabTemplateNode);
/** Creates a prefab template node representing a prefab placeholder. */
kzsError kzuPrefabTemplateNodeCreatePlaceholder(const struct KzcMemoryManager* memoryManager, struct KzuUIDomain* uiDomain, kzString name,
                                                struct KzuObjectNode* referenceObjectNode, struct KzuPrefabTemplate* prefabTemplate,
                                                struct KzuPrefabTemplateNode** out_prefabTemplateNode);

/** Deletes a prefab template node. */
kzsError kzuPrefabTemplateNodeDelete(struct KzuPrefabTemplateNode* prefabTemplateNode);

/** Loads the children of a prefab template node. */
kzsException kzuPrefabTemplateNodeLoadChildrenFromKZB(const struct KzuPrefabTemplateNode* prefabTemplateNode,
                                                      struct KzcInputStream* inputStream, const struct KzuBinaryFileInfo* file);

/** Add a child to template node. */
kzsError kzuPrefabTemplateNodeAddChild(const struct KzuPrefabTemplateNode* prefabTemplateNode, const struct KzuPrefabTemplateNode* child);
/** Get the iterator for node template children. */
struct KzcDynamicArrayIterator kzuPrefabTemplateNodeGetChildren(const struct KzuPrefabTemplateNode* prefabTemplateNode);
/** Get the reference node from a node template. This node stores all properties, bindings and triggers that are copied to instances. */
struct KzuObjectNode* kzuPrefabTemplateNodeGetReferenceNode(const struct KzuPrefabTemplateNode* prefabTemplateNode);
/** Get the type of the node a node template creates. */
KzuObjectType kzuPrefabTemplateNodeGetObjectType(const struct KzuPrefabTemplateNode* prefabTemplateNode);

/** Instantiates a template node. This function is for internal use. */
kzsError kzuPrefabTemplateNodeInstantiate(const struct KzuPrefabTemplateNode* prefabTemplateNode, struct KzuObjectNode** out_objectNode);

/** Notifies the prefab template node that an instance of it is deleted. */
kzsError kzuPrefabTemplateNodeInstanceDeleted(const struct KzuPrefabTemplateNode* prefabTemplateNode, const struct KzuObjectNode* objectNode);

/** Deletes all instances created from the given prefab template node. */
kzsError kzuPrefabTemplateNodeDeleteInstances(const struct KzuPrefabTemplateNode* prefabTemplateNode);


/** Converts prefab template node to resource. */
struct KzuResource* kzuPrefabTemplateNodeToResource(const struct KzuPrefabTemplateNode* prefabTemplateNode);
/** Converts prefab template node from resource. */
struct KzuPrefabTemplateNode* kzuPrefabTemplateNodeFromResource(const struct KzuResource* resource);
/** Casts prefab template node from resource, KZ_NULL if invalid type. */
struct KzuPrefabTemplateNode* kzuPrefabTemplateNodeCastFromResource(const struct KzuResource* resource);


/** Creates a prefab template. */
kzsError kzuPrefabTemplateCreate(const struct KzcMemoryManager* memoryManager, struct KzuUIDomain* uiDomain,
                                 kzString name, struct KzuPrefabTemplate** out_prefabTemplate);
/** Deletes a prefab template. */
kzsError kzuPrefabTemplateDelete(struct KzuPrefabTemplate* prefabTemplate);

/** Gets the root template node of a prefab. */
struct KzuPrefabTemplateNode* kzuPrefabTemplateGetRoot(const struct KzuPrefabTemplate* prefabTemplate);
/** Get the timeline sequence that is started when a prefab is instantiated. */
struct KzuTimeLineSequence* kzuPrefabTemplateGetStartupSequence(const struct KzuPrefabTemplate* prefabTemplate);
/** Set the timeline sequence that is started when a prefab is instantiated. */
kzsError kzuPrefabTemplateSetStartupSequence(struct KzuPrefabTemplate* prefabTemplate, struct KzuTimeLineSequence* startupSequence);

/** Update all existing instances of the prefab template node with updated data. */
kzsError kzuPrefabTemplateNodeUpdateInstances(const struct KzuPrefabTemplateNode* prefabTemplateNode);

/** Gets the list of all object node instances created from the prefab template node. */
struct KzcDynamicArrayIterator kzuPrefabTemplateNodeGetInstances(const struct KzuPrefabTemplateNode* prefabTemplateNode);
/** Gets the list of all placeholders created to point to the prefab template that owns this prefab template node. */
struct KzcDynamicArrayIterator kzuPrefabTemplateNodeGetPlaceholders(const struct KzuPrefabTemplateNode* prefabTemplateNode);

/** Instantiates a prefab template. */
kzsError kzuPrefabTemplateInstantiate(const struct KzuPrefabTemplate* prefabTemplate, kzString rootName, struct KzuObjectNode** out_objectNode);

/** Loads prefab from KZB. */
kzsError kzuPrefabTemplateLoadFromKZB(struct KzuPrefabTemplate* prefabTemplate, struct KzcInputStream* inputStream, const struct KzuBinaryFileInfo* file);
/** Initialized a prefab instance. This function is for internal use. */
kzsError kzuPrefabTemplateInitializeInstance(const struct KzuPrefabTemplate* prefabTemplate, struct KzuObjectNode* objectNode);


/** Converts prefab template to resource. */
struct KzuResource* kzuPrefabTemplateToResource(const struct KzuPrefabTemplate* prefabTemplate);
/** Converts prefab template from resource. */
struct KzuPrefabTemplate* kzuPrefabTemplateFromResource(const struct KzuResource* resource);
/** Casts prefab from resource, KZ_NULL if invalid type. */
struct KzuPrefabTemplate* kzuPrefabTemplateCastFromResource(const struct KzuResource* resource);


/** Sets ui domain to prefab template. */
void kzuPrefabTemplateSetUIDomain(struct KzuPrefabTemplate* prefabTemplate, struct KzuUIDomain* uiDomain);
/** Sets ui domain to prefab template node. */
void kzuPrefabTemplateNodeSetUIDomain(struct KzuPrefabTemplateNode* prefabTemplate, struct KzuUIDomain* uiDomain);


KZ_HEADER_END


#endif
