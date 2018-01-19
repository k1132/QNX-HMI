/**
 * \file
 * Hash set. Hash set stores unique values, whose existence in the set can be queried in constant time.
 * 
 * Copyright 2008-2014 by Rightware. All rights reserved.
 */
#ifndef KZC_HASH_SET_H
#define KZC_HASH_SET_H


#include "kzc_hash_code.h"
#include "kzc_comparator.h"
#include "kzc_hash_map.h"

#include <system/kzs_types.h>
#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations */
struct KzcMemoryManager;


/**
 * \struct KzcHashSet
 * Internal structure of a HashSet.
 */
struct KzcHashSet;

/**
 * Accessor to the contents of a KzcHashSet.
 *
 * Usage
 * ----
 * The following example code shows how to iterate over the elements in a hash set.
 \code{.c}
    struct KzcHashSetIterator it = kzcHashSetGetIterator(set);
    while (kzcHashSetIterate(it))
    {
        struct SomeStruct* value = (struct SomeStruct*)kzcHashSetIteratorPointerGetValue(it);
        somestruct_some_operation(value);
        // ... etc ...
        if (condition_for_breaking_out_of_the_loop)
            kzcHashSetIterationBreak(set);
    }
\endcode
 *
 * Alternative accessor functions are listed in \ref kzc_hash_set_accessors_h.inl.
 */
struct KzcHashSetIterator
{
    struct KzcHashMapIterator mapIterator_private; /**< Hash map iterator corresponding the hash set iterator. */
};


/** Creates a new initially empty hash set. Initial capacity is given as a parameter. */
kzsError kzcHashSetCreateWithCapacity(const struct KzcMemoryManager* memoryManager, struct KzcHashMapConfiguration configuration,
                                      kzUint capacity, struct KzcHashSet** out_hashSet);

/** Creates a new initially empty hash set. */
kzsError kzcHashSetCreate(const struct KzcMemoryManager* memoryManager, struct KzcHashMapConfiguration configuration,
                          struct KzcHashSet** out_hashSet);

/** Creates a new initially empty hash set, which ensures that the iteration order is same as the order of adding elements. Initial capacity is given as a parameter. */
kzsError kzcHashSetCreateOrderedWithCapacity(const struct KzcMemoryManager* memoryManager, struct KzcHashMapConfiguration configuration,
                                             kzUint capacity, struct KzcHashSet** out_hashSet);

/** Creates a new initially empty hash set, which ensures that the iteration order is same as the order of adding elements. */
kzsError kzcHashSetCreateOrdered(const struct KzcMemoryManager* memoryManager, struct KzcHashMapConfiguration configuration,
                                 struct KzcHashSet** out_hashSet);

/** Frees the memory allocated for the hash set. */
kzsError kzcHashSetDelete(struct KzcHashSet* hashSet);

/** Clears the content of the hash set. */
kzsError kzcHashSetClear(const struct KzcHashSet* hashSet);

/** Gets configuration. */
struct KzcHashMapConfiguration kzcHashSetGetConfiguration(const struct KzcHashSet* hashSet);

/** Returns the number of entries stored in the hash set. */
kzUint kzcHashSetGetSize(const struct KzcHashSet* hashSet);

/** Checks if the hash set is empty or not. */
kzBool kzcHashSetIsEmpty(const struct KzcHashSet* hashSet);


/** Returns an iterator to the hash set. Call ::kzcHashSetIterate() before accessing the first and any subsequent entries. */
struct KzcHashSetIterator kzcHashSetGetIterator(const struct KzcHashSet* hashSet);

#if defined(_DEBUG)
/** Disable active iterator status. */
void kzcHashSetDisableActiveIterator_private(const struct KzcHashSet* hashMap);
/** Break from a hash set iteration. */
#define kzcHashSetIterationBreak(hashSet) \
{ \
    kzcHashSetDisableActiveIterator_private(hashSet); \
    break; \
}
#else
/** Break from a hash set iteration. */
#define kzcHashSetIterationBreak(hashSet) \
{ \
    break; \
}
#endif

/** Finds the next entry in the iterated hash set.
* \param iterator_param ::KzcHashSetIterator structure.
* \return ::KZ_TRUE if the next entry is found, otherwise ::KZ_FALSE.
*/
#define kzcHashSetIterate(iterator_param) kzcHashMapIterate(iterator_param.mapIterator_private)

/** Ensures the specified hash set is valid. */
kzBool kzcHashSetIsValid(const struct KzcHashSet* hashSet);


KZ_HEADER_END


#include "kzc_hash_set_accessors_h.inl"


#endif
