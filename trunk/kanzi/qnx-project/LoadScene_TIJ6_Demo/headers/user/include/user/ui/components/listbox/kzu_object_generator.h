/**
* \file
* Defines interface for Object Generators that provide virtual items for ListBox.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_OBJECT_GENERATOR_H
#define KZU_OBJECT_GENERATOR_H


#include <user/ui/components/listbox/kzu_object_generator_common.h>

#include <system/kzs_types.h>
#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations. */
struct KzuObjectNode;
struct KzuObjectGenerator;
struct KzuUIDomain;
struct KzcMemoryManager;
struct KzcVector3;
struct KzuUiListBox;


/** Optional list interface for Object Generator. */
struct KzuObjectGeneratorListInterface
{
    /** Returns the number of objects controlled by the list interface. */
    kzsError (*getCount)(struct KzuObjectGenerator* generator, kzUint* out_count);

    /** Gets the object at the given index of the list. */
    kzsError (*getObject)(struct KzuObjectGenerator* generator, kzUint index, struct KzuObjectNode** out_object);    

    /** Finds index of the given object in the list. */
    kzsError (*findIndex)(struct KzuObjectGenerator* generator, struct KzuObjectNode* object, kzBool* out_found, kzUint* out_index);

    /** Inserts an object at the given index. */
    kzsError (*insertObject)(struct KzuObjectGenerator* generator, kzUint index, struct KzuObjectNode* object);

    /** Removes an object at the given index from the object generator's list. */
    kzsError (*removeObject)(struct KzuObjectGenerator* generator, kzUint index);

    /** Replaces the object at the given index in the object generator's list. */
    kzsError (*replaceObject)(struct KzuObjectGenerator* generator, kzUint index, struct KzuObjectNode* object);
};


/** Main virtual interface of Object Generator. */
struct KzuObjectGeneratorInterface
{
    /** Optional list interface for modifying content of the object generator. Can be KZU_OBJECT_GENERATOR_NO_LIST_INTERFACE. */
    const struct KzuObjectGeneratorListInterface* listInterface;

    /** Initializes the Object Generator. */
    kzsError (*initialize)(struct KzuObjectGenerator* generator);

    /** Uninitializes the Object Generator. */
    kzsError (*uninitialize)(struct KzuObjectGenerator* generator);

    /** Attaches the Object Generator. */
    kzsError (*attach)(struct KzuObjectGenerator* generator);

    /** Detaches the Object Generator. */
    kzsError (*detach)(struct KzuObjectGenerator* generator);

    /**
    * Gets an object that should be displayed at the given index.
    * If the object has already been created and not freed afterwards, returns the object from cache.
    */
    kzsError (*getObject)(struct KzuObjectGenerator* generator, kzUint index, struct KzuObjectNode** out_object);

    /** Frees an object that has been returned from getObject. */
    kzsError (*freeObject)(struct KzuObjectGenerator* generator, struct KzuObjectNode* object);

    /**
    * Gets index of an object that has been returned from getObject, or KZU_UI_LIST_BOX_NO_ITEM if
    * the object does not exist.
    */
    kzsError (*getObjectIndex)(struct KzuObjectGenerator* generator, struct KzuObjectNode* object, kzInt* out_index);

    /**
    * Gets exact size of the object that should be displayed at the given index.
    * This size will be used unless the list box is provided an object prototype.
    * Caching the sizes may be a good idea.
    */
    kzsError (*getObjectSize)(struct KzuObjectGenerator* generator, kzUint index, struct KzcVector3* out_size);

    /**
    * Gets the number of objects known by the object generator.
    * Last index can be calculated as 'count' - 1.
    */
    kzsError (*getCount)(struct KzuObjectGenerator* generator, kzUint* out_count);

    /**
    * Notify list box about a replaced item.
    */
    kzsError (*itemReplaced)(struct KzuObjectNode* listBox, kzUint index);

    /**
    * Notify list box about a removed item.
    */
    kzsError (*itemRemoved)(struct KzuObjectNode* listBox, kzUint index);

    /**
    * Notify list box about an added item.
    */
    kzsError (*itemAdded)(struct KzuObjectNode* listBox, kzUint index);
};


/** Base class for object generators that create and govern virtual items as needed. */
struct KzuObjectGenerator
{
    const struct KzuObjectGeneratorInterface* interface; /**< Generator interface implementation. */

    struct KzuObjectNode* listBox; /**< ListBox controlled by the generator. */
    struct KzuUIDomain* uiDomain; /**< UIDomain for creating new objects. */
};


/** Assigns a list box to the object generator. */
void kzuObjectGeneratorBindListBox(struct KzuObjectGenerator* generator, struct KzuObjectNode* listBox);

/** Object generator's base constructor. */
kzsError kzuObjectGeneratorCreate_protected(const struct KzcMemoryManager* memoryManager, struct KzuUIDomain* uiDomain,
                                            const struct KzuObjectGeneratorInterface* interface,
                                            struct KzuObjectGenerator* generator);

/** Gets the list box assigned to the object generator. */
struct KzuObjectNode* kzuObjectGeneratorGetListBox_protected(const struct KzuObjectGenerator* generator);

/** Gets the project assigned to the object generator. */
struct KzuUIDomain* kzuObjectGeneratorGetUIDomain_protected(const struct KzuObjectGenerator* generator);

/** Gets the memory manager used by the object generator. */
const struct KzcMemoryManager* kzuObjectGeneratorGetMemoryManager_protected(const struct KzuObjectGenerator* generator);


/** Destroys object generator. */
kzsError kzuObjectGeneratorDelete(struct KzuObjectGenerator* generator);

/** Initializes the Object Generator. */
kzsError kzuObjectGeneratorInitialize(struct KzuObjectGenerator* generator);

/** Uninitializes the Object Generator. */
kzsError kzuObjectGeneratorUninitialize(struct KzuObjectGenerator* generator);

/** Attaches the Object Generator. */
kzsError kzuObjectGeneratorAttach(struct KzuObjectGenerator* generator);

/** Detaches the Object Generator. */
kzsError kzuObjectGeneratorDetach(struct KzuObjectGenerator* generator);


/**
* Returns an object that should be displayed at the given index.
* If the object has already been created and not freed afterwards, returns the object from cache.
*/
kzsError kzuObjectGeneratorGetObject(struct KzuObjectGenerator* generator, kzUint index, struct KzuObjectNode** out_object);

/** Frees an object that has been returned from getObject. */
kzsError kzuObjectGeneratorFreeObject(struct KzuObjectGenerator* generator, struct KzuObjectNode* object);

/**
* Gets index of an object that has been returned from getObject, or KZU_UI_LIST_BOX_NO_ITEM if
* the object does not exist.
*/
kzsError kzuObjectGeneratorGetObjectIndex(struct KzuObjectGenerator* generator, struct KzuObjectNode* object, kzInt* out_index);

/** Gets size of the object that should be displayed at the given index. */
kzsError kzuObjectGeneratorGetObjectSize(struct KzuObjectGenerator* generator, kzUint index, struct KzcVector3* out_size);

/** Returns number of virtual items. */
kzsError kzuObjectGeneratorGetCount(struct KzuObjectGenerator* generator, kzUint* out_count);


/**
* Returns KZ_TRUE if the object generator implements the list interface.
* Functions starting with kzuObjectGeneratorList can only be called if this function returns KZ_TRUE.
*/
kzBool kzuObjectGeneratorImplementsListInterface(const struct KzuObjectGenerator* generator);


/** Gets the number of objects in the object generator's object list. Not all object generators support this. */
kzsError kzuObjectGeneratorListGetCount(struct KzuObjectGenerator* generator, kzUint* out_count);

/** Gets the object at the given index in object generator's object list. Not all object generators support this. */
kzsError kzuObjectGeneratorListGetObject(struct KzuObjectGenerator* generator, kzUint index, struct KzuObjectNode** out_object);

/** Finds index of the given object in object generator's object list. Not all object generators support this. */
kzsError kzuObjectGeneratorListFindIndex(struct KzuObjectGenerator* generator, struct KzuObjectNode* object, kzBool* out_found, kzUint* out_index);

/** Inserts an object at the given index in object generator's object list. Not all object generators support this. */
kzsError kzuObjectGeneratorListInsertObject(struct KzuObjectGenerator* generator, kzUint index, struct KzuObjectNode* object);

/** Removes an object at the given index from the object generator's object list. Not all object generators support this. */
kzsError kzuObjectGeneratorListRemoveObject(struct KzuObjectGenerator* generator, kzUint index);

/** Replaces the object at the given index from the object generator's object list with the given object. Not all object generators support this. */
kzsError kzuObjectGeneratorListReplaceObject(struct KzuObjectGenerator* generator, kzUint index, struct KzuObjectNode* object);

/** Adds an object at end of the object generator's object list. Not all object generators support this. */
kzsError kzuObjectGeneratorListAddObject(struct KzuObjectGenerator* generator, struct KzuObjectNode* object);

/** Removes the last object in the object generator's object list. Not all object generators support this. */
kzsError kzuObjectGeneratorListRemoveLastObject(struct KzuObjectGenerator* generator);

/** Gets whether the object generator's object list is empty. Not all object generators support this. */
kzsError kzuObjectGeneratorListIsEmpty(struct KzuObjectGenerator* generator, kzBool* out_empty);


/** Defines empty list interface. */
extern const struct KzuObjectGeneratorListInterface KZU_OBJECT_GENERATOR_NO_LIST_INTERFACE;


KZ_HEADER_END


#endif
