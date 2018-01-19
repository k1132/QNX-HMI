/**
* \file
* Defines interface for Item Generators that create List Box Items for ListBox.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_ITEM_GENERATOR_H
#define KZU_ITEM_GENERATOR_H


#include <user/ui/components/listbox/kzu_item_container_generator_common.h>

#include <system/kzs_types.h>
#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations. */
struct KzuObjectNode;
struct KzcMemoryManager;
struct KzuItemGenerator;
struct KzcVector3;


/** Main interface of Item Generator. */
struct KzuItemGeneratorInterface
{
    /** Initializes the item generator. */
    kzsError (*initialize)(struct KzuItemGenerator* generator);

    /** Uninitializes the item generator. */
    kzsError (*uninitialize)(struct KzuItemGenerator* generator);
    
    /** Attaches the Item Generator. */
    kzsError (*attach)(struct KzuItemGenerator* generator, const struct KzuObjectNode* objectNode);

    /** Detaches the Item Generator. */
    kzsError (*detach)(struct KzuItemGenerator* generator, const struct KzuObjectNode* objectNode);

    /** Outputs an empty item container for an object. */
    kzsError (*createItem)(struct KzuItemGenerator* generator, kzString name, struct KzuObjectNode** out_item);

    /** Deletes an item container returned by createItem. */
    kzsError (*deleteItem)(struct KzuItemGenerator* generator, struct KzuObjectNode* item);

    /** Gets size of an item container that would be created for an object of the given size. */
    kzsError (*getContainerSize)(struct KzuItemGenerator* generator, const struct KzcVector3* objectSize, struct KzcVector3* out_size);

    /** Gets the object attached to the list box item. */
    kzsError (*getObject)(struct KzuItemGenerator* generator, struct KzuObjectNode* item, struct KzuObjectNode** out_object);

    /** Attaches an object to the list box item. */
    kzsError (*attachObject)(struct KzuItemGenerator* generator, struct KzuObjectNode* item, struct KzuObjectNode* object);

    /** Detaches the object contained by the list box item. */
    kzsError (*detachObject)(struct KzuItemGenerator* generator, struct KzuObjectNode* item);

};

/** Base class for item generators that create and govern list box items as needed. */
struct KzuItemGenerator
{
    const struct KzuItemGeneratorInterface* interface; /**< Main interface of item generator. */
    struct KzuUIDomain* uiDomain; /**< UIDomain for item generator. */
};


/** Creates an item generator. */
kzsError kzuItemGeneratorCreate_protected(const struct KzcMemoryManager* memoryManager, struct KzuUIDomain* uiDomain, const struct KzuItemGeneratorInterface* interface, struct KzuItemGenerator* generator);

/** Destroys item generator. */
kzsError kzuItemGeneratorDelete(struct KzuItemGenerator* generator);


/** Gets the project assigned to the object generator. */
struct KzuUIDomain* kzuItemGeneratorGetUIDomain_protected(const struct KzuItemGenerator* generator);

/** Gets the memory manager used by the object generator. */
const struct KzcMemoryManager* kzuItemGeneratorGetMemoryManager_protected(const struct KzuItemGenerator* generator);


/** Initializes the item generator. */
kzsError kzuItemGeneratorInitialize(struct KzuItemGenerator* generator);

/** Uninitializes the item generator. */
kzsError kzuItemGeneratorUninitialize(struct KzuItemGenerator* generator);

/** Attaches the Object Generator. */
kzsError kzuItemGeneratorAttach(struct KzuItemGenerator* generator, const struct KzuObjectNode* objectNode);

/** Detaches the Object Generator. */
kzsError kzuItemGeneratorDetach(struct KzuItemGenerator* generator, const struct KzuObjectNode* objectNode);

/** Outputs an empty item container for an object. */
kzsError kzuItemGeneratorCreateItem(struct KzuItemGenerator* generator, kzString name, struct KzuObjectNode** out_item);

/** Deletes an item container returned by kzuItemGeneratorCreateItem. */
kzsError kzuItemGeneratorDeleteItem(struct KzuItemGenerator* generator, struct KzuObjectNode* item);


/** Gets size of an item container that would be created for an object of the given size. */
kzsError kzuItemGeneratorGetContainerSize(struct KzuItemGenerator* generator, const struct KzcVector3* objectSize, struct KzcVector3* out_size);


/** Gets the object attached to the list box item. */
kzsError kzuItemGeneratorGetObject(struct KzuItemGenerator* generator, struct KzuObjectNode* item, struct KzuObjectNode** out_object);

/** Attaches the object to the list box item. */
kzsError kzuItemGeneratorAttachObject(struct KzuItemGenerator* generator, struct KzuObjectNode* item, struct KzuObjectNode* object);

/** Detaches the object attached to the list box item. */
kzsError kzuItemGeneratorDetachObject(struct KzuItemGenerator* generator, struct KzuObjectNode* item);


KZ_HEADER_END


#endif
