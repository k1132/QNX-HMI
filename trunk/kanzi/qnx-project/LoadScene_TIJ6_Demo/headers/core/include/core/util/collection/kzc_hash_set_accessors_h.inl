/**
* \file
* Accessor declarations for hash set. To be included in kzc_hash_set.h
* Do not change this file, as the file is generated automatically.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/

#include <system/kzs_types.h>
#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/** Adds the given pointer value to the given pointer hash set. In case of a collision the existing entry is replaced. */
kzsError kzcHashSetPointerAdd(struct KzcHashSet* hashSet, const void* value);
/** Adds the given integer value to the given integer hash set. In case of a collision the existing entry is replaced. */
kzsError kzcHashSetIntAdd(struct KzcHashSet* hashSet, kzInt value);
/** Adds the given unsigned integer value to the given unsigned integer hash set. In case of a collision the existing entry is replaced. */
kzsError kzcHashSetUintAdd(struct KzcHashSet* hashSet, kzUint value);
/** Adds the given float value to the given float hash set. In case of a collision the existing entry is replaced. */
kzsError kzcHashSetFloatAdd(struct KzcHashSet* hashSet, kzFloat value);
/** Adds the given string value to the given string hash set. In case of a collision the existing entry is replaced. */
kzsError kzcHashSetStringAdd(struct KzcHashSet* hashSet, kzString value);
/** Adds the given pointer value to the given pointer hash set. In case of a collision the existing entry is replaced. */
kzsError kzcHashSetCustomAdd(struct KzcHashSet* hashSet, const void* value);

/** Removes the given pointer value from the given pointer hash set. If the value does not exist, an error is returned. */
kzsError kzcHashSetPointerRemove(struct KzcHashSet* hashSet, const void* value);
/** Removes the given integer value from the given integer hash set. If the value does not exist, an error is returned. */
kzsError kzcHashSetIntRemove(struct KzcHashSet* hashSet, kzInt value);
/** Removes the given unsigned integer value from the given unsigned integer hash set. If the value does not exist, an error is returned. */
kzsError kzcHashSetUintRemove(struct KzcHashSet* hashSet, kzUint value);
/** Removes the given float value from the given float hash set. If the value does not exist, an error is returned. */
kzsError kzcHashSetFloatRemove(struct KzcHashSet* hashSet, kzFloat value);
/** Removes the given string value from the given string hash set. If the value does not exist, an error is returned. */
kzsError kzcHashSetStringRemove(struct KzcHashSet* hashSet, kzString value);
/** Removes the given pointer value from the given pointer hash set. If the value does not exist, an error is returned. */
kzsError kzcHashSetCustomRemove(struct KzcHashSet* hashSet, const void* value);

/**
* Gets the stored pointer value corresponding to the pointer value given as a parameter.
* Returns ::KZ_NULL if an entry with a matching value does not exist in the hash set.
*
* This function only makes sense for strings and custom types.
*/
void* kzcHashSetPointerGetStoredValue(const struct KzcHashSet* hashSet, const void* value);
/**
* Gets the stored pointer value corresponding to the pointer value given as a parameter.
* Returns ::KZ_NULL if an entry with a matching value does not exist in the hash set.
*
* This function only makes sense for strings and custom types.
*/
void* kzcHashSetCustomGetStoredValue(const struct KzcHashSet* hashSet, const void* value);

/** Checks if the specified pointer value exists in the pointer hash set. Returns ::KZ_TRUE if the value is found and ::KZ_FALSE otherwise. */
kzBool kzcHashSetPointerContains(const struct KzcHashSet* hashSet, const void* value);
/** Checks if the specified integer value exists in the integer hash set. Returns ::KZ_TRUE if the value is found and ::KZ_FALSE otherwise. */
kzBool kzcHashSetIntContains(const struct KzcHashSet* hashSet, kzInt value);
/** Checks if the specified unsigned integer value exists in the unsigned integer hash set. Returns ::KZ_TRUE if the value is found and ::KZ_FALSE otherwise. */
kzBool kzcHashSetUintContains(const struct KzcHashSet* hashSet, kzUint value);
/** Checks if the specified float value exists in the float hash set. Returns ::KZ_TRUE if the value is found and ::KZ_FALSE otherwise. */
kzBool kzcHashSetFloatContains(const struct KzcHashSet* hashSet, kzFloat value);
/** Checks if the specified string value exists in the string hash set. Returns ::KZ_TRUE if the value is found and ::KZ_FALSE otherwise. */
kzBool kzcHashSetStringContains(const struct KzcHashSet* hashSet, kzString value);
/** Checks if the specified pointer value exists in the pointer hash set. Returns ::KZ_TRUE if the value is found and ::KZ_FALSE otherwise. */
kzBool kzcHashSetCustomContains(const struct KzcHashSet* hashSet, const void* value);

/** Returns the pointer value of the pointer hash map entry pointed by the iterator. */
#define kzcHashSetIteratorPointerGetValue(iterator_param) kzcHashMapIteratorGetPointerValue(iterator_param.mapIterator_private)
/** Returns the integer value of the integer hash map entry pointed by the iterator. */
#define kzcHashSetIteratorIntGetValue(iterator_param) kzcHashMapIteratorGetIntValue(iterator_param.mapIterator_private)
/** Returns the unsigned integer value of the unsigned integer hash map entry pointed by the iterator. */
#define kzcHashSetIteratorUintGetValue(iterator_param) kzcHashMapIteratorGetUintValue(iterator_param.mapIterator_private)
/** Returns the float value of the float hash map entry pointed by the iterator. */
#define kzcHashSetIteratorFloatGetValue(iterator_param) kzcHashMapIteratorGetFloatValue(iterator_param.mapIterator_private)
/** Returns the string value of the string hash map entry pointed by the iterator. */
#define kzcHashSetIteratorStringGetValue(iterator_param) kzcHashMapIteratorGetStringValue(iterator_param.mapIterator_private)


KZ_HEADER_END


