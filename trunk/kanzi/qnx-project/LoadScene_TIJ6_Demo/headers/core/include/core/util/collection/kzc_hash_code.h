/**
 * \file
 * General purpose hash code functions.
 * Hash code and comparator is related such that for two objects a and b if compare(a,b) == 0 then hashCode(a) == hashCode(b).
 * 
 * Copyright 2008-2014 by Rightware. All rights reserved.
 */
#ifndef KZC_HASH_CODE_H
#define KZC_HASH_CODE_H


#include "kzc_collection_value.h"

#include <core/util/string/kzc_string.h>

#include <system/kzs_types.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/** Knuth's hash multiplier for 32-bit constants. */
#define KZ_KNUTH_HASH_MUL 2654435761U


/** Custom hash function definition. */
typedef kzU32 (*KzcHashFunction)(const void* object);


/* Hash code functions for fundamental Kanzi collection data types. */

/** Hash code function for unsigned integers. */
KZ_INLINE kzU32 kzcHashCodeFromUint(kzUint value)
{
    return KZ_KNUTH_HASH_MUL * (kzU32)value;
}

/** Hash code function for floats. */
KZ_INLINE kzU32 kzcHashCodeFromFloat(kzFloat value)
{
    union KzcCollectionValue key;
    key.floatValue = value;
    return kzcHashCodeFromUint(key.uintValue);
}

/** Hash code function for signed integers. */
KZ_INLINE kzU32 kzcHashCodeFromInt(kzInt value)
{
    union KzcCollectionValue key;
    key.intValue = value;
    return kzcHashCodeFromUint(key.uintValue);
}

/** Hash code function for pointers that are already casted to uints. */
KZ_INLINE kzU32 kzcHashCodeFromPointerUint(kzUint value)
{
    return KZ_KNUTH_HASH_MUL * ((((kzU32)value) >> 3) + (((kzU32)value) << 29)); /* Rotate right with safe align (8) prior to multiply. */
}

/** Hash code function for pointers. */
KZ_INLINE kzU32 kzcHashCodeFromPointer(const void* value)
{
    union KzcCollectionValue key;
    key.pointerValue = value;
    return kzcHashCodeFromPointerUint(key.uintValue);
}

/** Hash code function for strings. */
KZ_INLINE kzU32 kzcHashCodeFromString(kzString value)
{
    kzU32 hash = 5381;
    kzUint i;

    /* djb2 hash algorithm */

    for (i = 0; value[i] != KZC_STRING_TERMINATION_SYMBOL; ++i)
    {
        hash = ((hash << 5) + hash) + (kzU32)(kzByte)value[i]; /* hash * 33 + c */
    }

    return hash;
}


KZ_HEADER_END


#endif

