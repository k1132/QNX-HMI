/**
 * \file
 * Hash map. A hash map stores arbitrary key-value mappings in a way that allows retrieving the value for a key in constant time.
 * If the Kanzi library was built in the debug mode (i.e. _DEBUG was defined), the hash map will assert if elements are
 * added or removed during iteration of the hash map's elements. Also, ::kzcHashMapIterationBreak() should be used when breaking
 * out of an iteration loop before iterating over all of the elements.
 * 
 * Copyright 2008-2014 by Rightware. All rights reserved.
 */
#ifndef KZC_HASH_MAP_H
#define KZC_HASH_MAP_H


#include "kzc_hash_code.h"
#include "kzc_comparator.h"

#include <system/kzs_types.h>
#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations */
struct KzcMemoryManager;
struct KzcHashMapOrderedEntry;


/** Hash map iterator for unordered KzcHashMap. */
struct KzcHashMapIteratorIndexing
{
    kzInt currentIndex; /**< Current index in the iterator. */
    kzInt nextChain; /**< Next chain in the iterator. */
    kzInt maxIndex; /**< Maximum index for the iteration. */
};


/**
 * Iterator to the contents of a KzcHashMap.
 * If the hash map is ordered, the iterator will iterate the elements in the order specified by the ::KzcComparatorFunction.
 *
 * Usage
 * ----
 * The following example code shows how to iterate over a hash map. Notice that ::kzcHashMapIterationBreak() is necessary
 * for breaking out of the iteration loop when Kanzi has been built for debugging.
 \code{.c}
    struct KzcHashMapIterator it = kzcHashMapGetIterator(map);
    while (kzcHashMapIterate(it))
    {
        struct SomeKey* key = (struct SomeKey*)kzcHashMapIteratorPointerGetKey(it); // (Optional)
        struct SomeStruct* value = (struct SomeStruct*)kzcHashMapIteratorGetPointerValue(it);
        somestruct_some_operation(value);
        // ... etc ...
        if (condition_for_breaking_out_of_the_loop)
            kzcHashMapIterationBreak(map);
    }
\endcode  
 * Alternative accessor functions are listed in \ref kzc_hash_map_accessors_h.inl.
 */
struct KzcHashMapIterator
{
    struct KzcHashMap* map_private; /**< Reference to the hash map accessed by this iterator. */
    union
    {
        struct KzcHashMapIteratorIndexing index_private;
        struct KzcHashMapOrderedEntry* entry_private;
    } data; /**< Used for tracking position of the iterator. */
};


/**
* Key type identifier for hash map.
* To use custom hash and comparator functions set key type to ::KZC_HASH_MAP_KEY_TYPE_CUSTOM.
*/
enum KzcHashMapKeyType
{
    KZC_HASH_MAP_KEY_TYPE_INT = 1,      /**< Integer key. */
    KZC_HASH_MAP_KEY_TYPE_UINT = 2,     /**< Unsigned integer key. */
    KZC_HASH_MAP_KEY_TYPE_FLOAT = 4,    /**< Float key. */
    KZC_HASH_MAP_KEY_TYPE_POINTER = 8,  /**< Pointer key. */
    KZC_HASH_MAP_KEY_TYPE_STRING = 16,  /**< String key (::kzString). */
    KZC_HASH_MAP_KEY_TYPE_CUSTOM = 32   /**< Pointer key with custom hash function and comparator. */
};


/**
 * Configuration parameters for a KzcHashMap. The configuration specifies the type of keys and the hash and
 * comparator function of the hash map.
 * Kanzi provides ready-made configurations for the most common use-cases: ::KZC_HASH_MAP_CONFIGURATION_POINTER for
 * arbitrary pointer keys, ::KZC_HASH_MAP_CONFIGURATION_STRING for string keys and ::KZC_HASH_MAP_CONFIGURATION_INT
 * for integer keys.
 * Custom configurations can also be created for other key types such as structs by setting key type to be
 * ::KZC_HASH_MAP_KEY_TYPE_CUSTOM and providing the required callbacks.
 *
 * \see ::KZC_HASH_MAP_CONFIGURATION_INT, ::KZC_HASH_MAP_CONFIGURATION_UINT, ::KZC_HASH_MAP_CONFIGURATION_FLOAT,
 * ::KZC_HASH_MAP_CONFIGURATION_POINTER, ::KZC_HASH_MAP_CONFIGURATION_STRING.
 */
struct KzcHashMapConfiguration
{
    enum KzcHashMapKeyType keyType; /**< Type of the hash map key. */
    KzcHashFunction hashFunction; /**< Function for calculating the hash code for a specified key.
                                       An optimal hash function returns different values for each different key.
                                       A bad hash function returns the same values for different keys, leading to slower element look-ups
                                       and frequent memory allocations. */
    KzcComparatorFunction keyComparator; /**< Comparator function for the key. */
};


/**
 * \struct KzcHashMap
 * Hash map.
 */
struct KzcHashMap;


/** Configuration for hash maps where key type is an integer. */
extern const struct KzcHashMapConfiguration KZC_HASH_MAP_CONFIGURATION_INT;
/** Configuration for hash maps where key type is an unsigned integer. */
extern const struct KzcHashMapConfiguration KZC_HASH_MAP_CONFIGURATION_UINT;
/** Configuration for hash maps where key type is a float. */
extern const struct KzcHashMapConfiguration KZC_HASH_MAP_CONFIGURATION_FLOAT;
/** Configuration for hash maps where key type is an arbitrary pointer. */
extern const struct KzcHashMapConfiguration KZC_HASH_MAP_CONFIGURATION_POINTER;
/** Configuration for hash maps where key type is a string. */
extern const struct KzcHashMapConfiguration KZC_HASH_MAP_CONFIGURATION_STRING;


/** Creates a new initially empty hash map. Stores key-value pairs.
* \param memoryManager The memory manager to use for memory allocations.
* \param configuration Specifies what type of keys are stored in the map.
* \param capacity Initial capacity of the hash map. This is the number of chains (of starting length 2) in the map.
* \param out_hashMap Pointer that is set to point to the new hash map on successful return.
* \return ::KZS_SUCCESS on success.
*/
kzsError kzcHashMapCreateWithCapacity(const struct KzcMemoryManager* memoryManager, struct KzcHashMapConfiguration configuration,
                                      kzUint capacity, struct KzcHashMap** out_hashMap);

/** Creates a new initially empty hash map with zero capacity. Stores key-value pairs.
* \param memoryManager The memory manager to use for memory allocations.
* \param configuration Specifies what type of keys are stored in the map.
* \param out_hashMap Pointer that is set to point to the new hash map on successful return.
* \return ::KZS_SUCCESS on success.
*/
kzsError kzcHashMapCreate(const struct KzcMemoryManager* memoryManager, struct KzcHashMapConfiguration configuration,
                          struct KzcHashMap** out_hashMap);

/** Creates a new initially empty hash map, which ensures that the iteration order is same as the order of elements. Stores key-value pairs.
* \param memoryManager The memory manager to use for memory allocations.
* \param configuration Specifies what type of keys are stored in the map.
* \param capacity Initial capacity of the hash map. This is the number of chains (of starting length 2) in the map.
* \param out_hashMap Pointer that is set to point to the new hash map on successful return.
* \return ::KZS_SUCCESS on success.
*/
kzsError kzcHashMapCreateOrderedWithCapacity(const struct KzcMemoryManager* memoryManager, struct KzcHashMapConfiguration configuration,
                                             kzUint capacity, struct KzcHashMap** out_hashMap);

/** Creates a new initially empty hash map, which ensures that the iteration order is same as the order of elements.
* \param memoryManager The memory manager to use for memory allocations.
* \param configuration Specifies what type of keys are stored in the map.
* \param out_hashMap Pointer that is set to point to the new hash map on successful return.
* \return ::KZS_SUCCESS on success.
*/
kzsError kzcHashMapCreateOrdered(const struct KzcMemoryManager* memoryManager, struct KzcHashMapConfiguration configuration,
                                 struct KzcHashMap** out_hashMap);

/** Frees the memory allocated for the hash map. */
kzsError kzcHashMapDelete(struct KzcHashMap* hashMap);


/** Clears the content of the hash map. The capacity of the hash map does not change. */
kzsError kzcHashMapClear(struct KzcHashMap* hashMap);

/** Get hash map configuration. */
struct KzcHashMapConfiguration kzcHashMapGetConfiguration(const struct KzcHashMap* hashMap);


/** Returns the number of entries stored in the hash map. */
kzUint kzcHashMapGetSize(const struct KzcHashMap* HashMap);

/** Checks if the hash map is empty or not. */
kzBool kzcHashMapIsEmpty(const struct KzcHashMap* hashMap);


/** Returns an iterator to the hash map.
* Call ::kzcHashMapIterate() before accessing the first and any subsequent entries.
*/
struct KzcHashMapIterator kzcHashMapGetIterator(const struct KzcHashMap* hashMap);

#if defined(_DEBUG)
/** Disable active iterator status. */
void kzcHashMapDisableActiveIterator_private(const struct KzcHashMap* hashMap);
/** Break from hash map iteration. */
#define kzcHashMapIterationBreak(hashMap) \
{ \
    kzcHashMapDisableActiveIterator_private(hashMap); \
    break; \
}
#else
/** Break from hash map iteration - do nothing on release build. */
#define kzcHashMapIterationBreak(hashMap) \
{ \
    break; \
}
#endif


/** Finds the next entry in the attached hash map.
* \return ::KZ_TRUE if the next entry is found, otherwise ::KZ_FALSE.
*/
#define kzcHashMapIterate(iterator_param) kzcHashMapIterate_private(&iterator_param)
/**
 * Removes current entry of hash map pointed by the iterator.
 * Next iteration gives the entry that would have been next. Iterator should not be dereferenced at current state.
 */
#define kzcHashMapIteratorRemove(iterator_param) kzcHashMapIteratorRemove_private(&iterator_param)


/** \see kzcHashMapIterate */
kzBool kzcHashMapIterate_private(struct KzcHashMapIterator* iterator);
/** \see kzcHashMapIteratorRemove */
kzsError kzcHashMapIteratorRemove_private(struct KzcHashMapIterator* it);


KZ_HEADER_END


#include "kzc_hash_map_accessors_h.inl"


#endif
