/**
* \file
* Property collection.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_PROPERTY_COLLECTION_H
#define KZU_PROPERTY_COLLECTION_H


#include <core/util/collection/kzc_dynamic_array.h>

#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declaration structures. */
struct KzuPropertyType;
struct KzcMemoryManager;
struct KzcDynamicArray;


/**
 * \struct KzuPropertyTypeCollection
 * Contains list of property types.
 */
struct KzuPropertyTypeCollection;


/** Creates new property type collection. */
kzsError kzuPropertyTypeCollectionCreate(const struct KzcMemoryManager* memoryManager, struct KzuPropertyTypeCollection** out_collection);
/** Deletes property type collection and properties associated to it. */
kzsError kzuPropertyTypeCollectionDelete(struct KzuPropertyTypeCollection* collection);
/** Adds property type to property type collection. */
kzsError kzuPropertyTypeCollectionAddPropertyType(const struct KzuPropertyTypeCollection* collection, const struct KzuPropertyType* propertyType);
/** Removes property type from property type collection. */
kzsError kzuPropertyTypeCollectionRemovePropertyType(const struct KzuPropertyTypeCollection* collection, const struct KzuPropertyType* propertyType);
/** Adds another property type collection property types to destination property collection. */
kzsError kzuPropertyTypeCollectionRemoveAllPropertyTypes(const struct KzuPropertyTypeCollection* collection);
/** Returns iterator of property type collection elements. */
struct KzcDynamicArrayIterator kzuPropertyTypeCollectionGetIterator(const struct KzuPropertyTypeCollection* collection);
/** Gets property type from property type collection by name. KZ_NULL if not found. */
struct KzuPropertyType* kzuPropertyTypeCollectionGetPropertyTypeByName(const struct KzuPropertyTypeCollection* collection, kzString propertyTypeName);

/** Clears all property types from property type collection. After the clear the property type collection is empty. */
void kzuPropertyTypeCollectionClear(const struct KzuPropertyTypeCollection* collection);
/** Gets the number of stored property types from the property type collection. */
kzUint kzuPropertyTypeCollectionGetSize(const struct KzuPropertyTypeCollection* collection);
/** Gets property type by index from collection. KZ_NULL if not found. */
const struct KzuPropertyType* kzuPropertyTypeCollectionGet(const struct KzuPropertyTypeCollection* collection, kzUint index);

/** Checks if property collection contains specific property type. */
kzBool kzuPropertyTypeCollectionContainsPropertyType(const struct KzuPropertyTypeCollection* collection, const struct KzuPropertyType* propertyType);


KZ_HEADER_END


#endif
