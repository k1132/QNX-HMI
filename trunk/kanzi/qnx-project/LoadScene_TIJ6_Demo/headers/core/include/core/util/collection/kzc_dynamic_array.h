/**
 * \file
 * Automatically growing array of arbitrary data.
 * The data type of the elements is determined when the first element is added with ::kzcDynamicArrayPointerAdd(),
 * ::kzcDynamicArrayIntAdd(), ::kzcDynamicArrayUintAdd(), ::kzcDynamicArrayFloatAdd() or ::kzcDynamicArrayStringAdd().
 * It is the caller's responsibility to use accessor functions of the right type.
 * 
 * Copyright 2008-2014 by Rightware. All rights reserved.
 */
#ifndef KZC_DYNAMIC_ARRAY_H
#define KZC_DYNAMIC_ARRAY_H


#include "kzc_comparator.h"
#include "kzc_collection_value.h"

#include <system/kzs_types.h>
#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations */
struct KzcMemoryManager;


/**
 * \struct KzcDynamicArray
 * Structure of a DynamicArray.
 */
struct KzcDynamicArray;


/** Read-only iterator for dynamic array. */
struct KzcDynamicArrayIterator
{
    const struct KzcDynamicArray* dynamicArray_private; /**< Reference to the dynamic array accessed by this iterator. */
    const union KzcCollectionValue* elements_private; /**< Const copy of the elements array. */
    kzUint elementCount_private; /**< Number of elements. */
    kzInt currentIndex_private; /**< Current index in the iterator. */
};

/** Mutable iterator for dynamic array. */
struct KzcDynamicArrayMutableIterator
{
    struct KzcDynamicArray* dynamicArray_private; /**< Reference to the dynamic array accessed by this iterator. */
    kzInt currentIndex_private; /**< Current index in the iterator. */
};


/** Dynamic array iterator that can be used for an empty iteration result e.g. when an actual empty dynamic array doesn't exist. */
extern const struct KzcDynamicArrayIterator KZC_DYNAMIC_ARRAY_EMPTY_ITERATOR;


/** Creates a new initially empty dynamic array with initial capacity of 10.
* \param memoryManager The memory manager to use.
* \param out_dynamicArray A pointer that is set to point to the new dynamic array on success.
* \return ::KZS_SUCCESS on success.
*/
kzsError kzcDynamicArrayCreate(const struct KzcMemoryManager* memoryManager, struct KzcDynamicArray** out_dynamicArray);

/** Creates a new initially empty dynamic array. Initial capacity is given as a parameter.
* \param memoryManager The memory manager to use.
* \param capacity The initial capacity of the array.
*                 I.e. the number of elements that can be added to the array before more memory needs to be allocated.
* \param out_dynamicArray A pointer that is set to point to the new dynamic array on success.
* \return ::KZS_SUCCESS on success.
*/
kzsError kzcDynamicArrayCreateWithCapacity(const struct KzcMemoryManager* memoryManager, kzUint capacity,
                                           struct KzcDynamicArray** out_dynamicArray);

/** Frees the memory allocated for the dynamic array.
* \return ::KZS_SUCCESS on success.
*/
kzsError kzcDynamicArrayDelete(struct KzcDynamicArray* dynamicArray);

/** Creates a copy of a dynamic array.
* \param memoryManager The memory manager to use for allocating the copy.
* \param original A valid dynamic array.
* \param out_copy A pointer that is set to point to the copy on success.
* \return ::KZS_SUCCESS on success.
*/
kzsError kzcDynamicArrayCopy(const struct KzcMemoryManager* memoryManager, const struct KzcDynamicArray* original, struct KzcDynamicArray** out_copy);

/** Removes all the elements from the dynamic array. */
void kzcDynamicArrayClear(struct KzcDynamicArray* dynamicArray);

/** Removes the index'th element from the dynamic array.
* \param dynamicArray A valid dynamic array.
* \param index The index of the element.
* \return ::KZS_ERROR_ARRAY_OUT_OF_BOUNDS if the index is out of bounds, ::KZS_SUCCESS on success.
*/
kzsError kzcDynamicArrayRemoveByIndex(struct KzcDynamicArray* dynamicArray, const kzUint index);

/** Sorts the given dynamic array according to the given comparator function.
* \param dynamicArray A valid dynamic array.
* \param comparator The comparator function to use for sorting.
*/
void kzcDynamicArraySort(const struct KzcDynamicArray* dynamicArray, KzcComparatorFunction comparator);

/** Sorts the given dynamic array according to the given comparator function. The given arbitrary context is passed to the comparator.
* \param dynamicArray A valid dynamic array.
* \param comparator The comparator function to use for sorting.
* \param context An arbitrary pointer passed to the comparator function.
*/
void kzcDynamicArraySortWithContext(const struct KzcDynamicArray* dynamicArray, KzcComparatorWithContextFunction comparator,
                                    const void* context);

/** Swaps places of two elements of a dynamic array with each other.
* \param dynamicArray A valid dynamic array.
* \param indexA Index of the first element.
* \param indexB Index of the second element.
*/
void kzcDynamicArraySwap(const struct KzcDynamicArray* dynamicArray, kzUint indexA, kzUint indexB);

/** Reverses the order of a dynamic array.
* \param dynamicArray A valid dynamic array.
*/
void kzcDynamicArrayReverse(const struct KzcDynamicArray* dynamicArray);

/** Returns the number of elements in the dynamic array.
* \param dynamicArray A valid dynamic array.
* \return The number of elements in the dynamic array.
*/
kzUint kzcDynamicArrayGetSize(const struct KzcDynamicArray* dynamicArray);

/** Checks if the dynamic array is empty or not.
* \param dynamicArray A valid dynamic array.
* \return ::KZ_TRUE if the dynamic array is empty, otherwise ::KZ_FALSE.
*/
kzBool kzcDynamicArrayIsEmpty(const struct KzcDynamicArray* dynamicArray);


/** Returns an iterator for the dynamic array.
* \param dynamicArray A valid dynamic array.
*/
struct KzcDynamicArrayIterator kzcDynamicArrayGetIterator(const struct KzcDynamicArray* dynamicArray);

/** Finds the next entry in the attached dynamic array.
* \return ::KZ_TRUE if the next entry is found, otherwise ::KZ_FALSE.
*/
#define kzcDynamicArrayIterate(iterator_param) kzcDynamicArrayIterate_private(&iterator_param)


/** Returns a mutable iterator for the dynamic array.
* \param dynamicArray A valid dynamic array.
*/
struct KzcDynamicArrayMutableIterator kzcDynamicArrayGetMutableIterator(struct KzcDynamicArray* dynamicArray);

/** Finds the next entry in the iterated dynamic array.
* \return ::KZ_TRUE if the next entry is found, otherwise ::KZ_FALSE.
*/
#define kzcDynamicArrayMutableIterate(iterator_param) kzcDynamicArrayMutableIterate_private(&iterator_param)
/** Removes the entry pointed by the iterator from the dynamic array. */
#define kzcDynamicArrayMutableIteratorRemove(iterator_param) kzcDynamicArrayMutableIteratorRemove_private(&iterator_param)


/** \see kzcDynamicArrayIterate */
KZ_INLINE kzBool kzcDynamicArrayIterate_private(struct KzcDynamicArrayIterator* iterator)
{
    return (kzUint)(++iterator->currentIndex_private) < iterator->elementCount_private;
}
/** \see kzcDynamicArrayMutableIterate */
KZ_INLINE kzBool kzcDynamicArrayMutableIterate_private(struct KzcDynamicArrayMutableIterator* iterator)
{
    return (kzUint)(++iterator->currentIndex_private) < kzcDynamicArrayGetSize(iterator->dynamicArray_private);
}
/** \see kzcDynamicArrayMutableIteratorRemove */
kzsError kzcDynamicArrayMutableIteratorRemove_private(struct KzcDynamicArrayMutableIterator* iterator);


#if defined(_DEBUG)

/** Fails if dynamic array's value type is not one of those with 1-flag in the given value mask. */
void kzcDynamicArrayRequireValueType_private(const struct KzcDynamicArray* dynamicArray, enum KzcCollectionValueType valueType);
/** Sets dynamic array's value type if it was not set before. Fails if dynamic array's value type is not one of those with 1-flag in the given value mask. */
void kzcHashMapRequireOrSetValueType_private(struct KzcDynamicArray* dynamicArray, enum KzcCollectionValueType valueType);

#endif


KZ_HEADER_END


/* Include type specific interface. */
#include "kzc_dynamic_array_accessors_h.inl"


#endif
