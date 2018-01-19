/**
* \file
* Implements a factory object that can be used to create instances of runtime-registered
* classes by their type.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_FACTORY_H
#define KZU_FACTORY_H


#include <user/resource/kzu_resource_common.h>
#include <user/scene_graph/kzu_object_common.h>
#include <user/ui/components/listbox/kzu_object_generator_common.h>
#include <user/ui/components/listbox/kzu_item_container_generator_common.h>

#include <system/debug/kzs_error.h>
#include <system/kzs_types.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations. */
struct KzcMemoryManager;
struct KzuComposer;
struct KzuFactory;
struct KzuResource;
struct KzuResourceLoader;
struct KzuLayer;
struct KzuObjectNode;
struct KzuUIDomain;
struct KzuUiComponentNode;
struct KzuObjectGenerator;
struct KzuItemGenerator;
struct KzcInputStream;


/** Pointer to a function that creates an object node with its default parameters. */
typedef kzsError (*kzuFactoryObjectNodeCreateFunction)(const struct KzcMemoryManager* memoryManager, kzString name,
                                                       struct KzuUIDomain* uiDomain, struct KzuObjectNode** out_objectNode);

/** Pointer to a function that creates a resource with its default parameters. */
typedef kzsError (*kzuFactoryResourceCreateFunction)(const struct KzcMemoryManager* memoryManager, kzString name, struct KzuResourceLoader* loader,
                                                     struct KzuUIDomain* uiDomain, struct KzuResource** out_resource);

/** Pointer to a function that creates an object generator with its default parameters. */
typedef kzsError (*kzuFactoryObjectGeneratorCreateFunction)(const struct KzcMemoryManager* memoryManager, struct KzuUIDomain* uiDomain,
                                                            struct KzuObjectGenerator** out_generator);

/** Pointer to a function that creates an item container generator with its default parameters. */
typedef kzsError (*kzuFactoryItemContainerGeneratorCreateFunction)(const struct KzcMemoryManager* memoryManager, struct KzuUIDomain* uiDomain,
                                                                   struct KzuItemGenerator** out_generator);


/**
* \struct KzuFactory
* Creates instances of classes by their type.
*/
struct KzuFactory;


/** Creates a factory. */
kzsError kzuFactoryCreate(const struct KzcMemoryManager* memoryManager, struct KzuFactory** out_factory);
/** Deletes a factory. */
kzsError kzuFactoryDelete(struct KzuFactory* factory);

/** Registers an object node type to the factory. */
kzsError kzuFactoryRegisterObjectNodeType(const struct KzuFactory* factory, KzuObjectType objectType, kzString typeString,
                                          kzuFactoryObjectNodeCreateFunction createFunction);

/** Registers a resource type to the factory. */
kzsError kzuFactoryRegisterResourceType(const struct KzuFactory* factory, KzuResourceType resourceType, kzString typeString,
                                        kzuFactoryResourceCreateFunction createFunction);

/** Registers an object generator type to the factory. */
kzsError kzuFactoryRegisterObjectGeneratorType(const struct KzuFactory* factory, KzuObjectGeneratorType generatorType, kzString typeString,
                                               kzuFactoryObjectGeneratorCreateFunction createFunction);
/** Registers an item container generator type to the factory. */
kzsError kzuFactoryRegisterItemContainerGeneratorType(const struct KzuFactory* factory, KzuItemContainerGeneratorType generatorType, kzString typeString,
                                                      kzuFactoryItemContainerGeneratorCreateFunction createFunction);

/** Gets object type's name by its type identifier. The returned string must not be freed manually. */
kzsException kzuFactoryGetObjectTypeName(const struct KzuFactory* factory, const void* objectType, kzString* out_string);
/** Gets object type's type identifier by its name. */
kzsException kzuFactoryGetObjectType(const struct KzuFactory* factory, kzString objectTypeName, const void** out_objectType);


/** Creates and initializes an object node of the given type. */
kzsException kzuFactoryCreateObjectNode(const struct KzuFactory* factory, const struct KzcMemoryManager* memoryManager,
                                        kzString name, struct KzuUIDomain* uiDomain, KzuObjectType objectType,
                                        struct KzuObjectNode** out_objectNode);

/** Creates an object of the given type without initializing. Should not be used in applications. */
kzsException kzuFactoryCreateUninitializedObjectNode(const struct KzuFactory* factory, const struct KzcMemoryManager* memoryManager,
                                                     kzString name, struct KzuUIDomain* uiDomain, KzuObjectType objectType,
                                                     struct KzuObjectNode** out_objectNode);

/** Creates and initializes a resource with its default settings. */
kzsException kzuFactoryCreateResource(const struct KzuFactory* factory, const struct KzcMemoryManager* memoryManager,
                                      kzString name, struct KzuResourceLoader* loader, struct KzuUIDomain* uiDomain, 
                                      KzuResourceType resourceType, struct KzuResource** out_resource);

/** Creates and initializes an object generator with its default settings. */
kzsException kzuFactoryCreateObjectGenerator(const struct KzuFactory* factory, const struct KzcMemoryManager* memoryManager,
                                             struct KzuUIDomain* uiDomain, KzuObjectGeneratorType objectGeneratorType,
                                             struct KzuObjectGenerator** out_generator);

/** Creates and initializes an item container generator with its default settings. */
kzsException kzuFactoryCreateItemContainerGenerator(const struct KzuFactory* factory, const struct KzcMemoryManager* memoryManager,
                                                    struct KzuUIDomain* uiDomain, KzuItemContainerGeneratorType itemContainerGeneratorType,
                                                    struct KzuItemGenerator** out_generator);

/** Load factory object type. */
kzsException kzuFactoryLoadObjectTypeFromKZB(const struct KzuFactory* factory, struct KzcInputStream* inputStream, const void** out_objectType); 


KZ_HEADER_END


#endif
