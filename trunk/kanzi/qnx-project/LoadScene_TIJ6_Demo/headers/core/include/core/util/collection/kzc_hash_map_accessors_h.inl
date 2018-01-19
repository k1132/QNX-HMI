/**
* \file
* Accessor declarations for hash map. To be included in kzc_hash_map.h
* Do not change this file, as the file is generated automatically.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/

#include <system/kzs_types.h>
#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/** Adds an entry to a hash map from pointers to pointers. In case of a key collision the existing entry is replaced. */
kzsError kzcHashMapPointerPutPointer(struct KzcHashMap* hashMap, const void* key, const void* value);
/** Adds an entry to a hash map from pointers to integers. In case of a key collision the existing entry is replaced. */
kzsError kzcHashMapPointerPutInt(struct KzcHashMap* hashMap, const void* key, kzInt value);
/** Adds an entry to a hash map from pointers to unsigned integers. In case of a key collision the existing entry is replaced. */
kzsError kzcHashMapPointerPutUint(struct KzcHashMap* hashMap, const void* key, kzUint value);
/** Adds an entry to a hash map from pointers to floats. In case of a key collision the existing entry is replaced. */
kzsError kzcHashMapPointerPutFloat(struct KzcHashMap* hashMap, const void* key, kzFloat value);
/** Adds an entry to a hash map from pointers to strings. In case of a key collision the existing entry is replaced. */
kzsError kzcHashMapPointerPutString(struct KzcHashMap* hashMap, const void* key, kzString value);
/** Adds an entry to a hash map from integers to pointers. In case of a key collision the existing entry is replaced. */
kzsError kzcHashMapIntPutPointer(struct KzcHashMap* hashMap, kzInt key, const void* value);
/** Adds an entry to a hash map from integers to integers. In case of a key collision the existing entry is replaced. */
kzsError kzcHashMapIntPutInt(struct KzcHashMap* hashMap, kzInt key, kzInt value);
/** Adds an entry to a hash map from integers to unsigned integers. In case of a key collision the existing entry is replaced. */
kzsError kzcHashMapIntPutUint(struct KzcHashMap* hashMap, kzInt key, kzUint value);
/** Adds an entry to a hash map from integers to floats. In case of a key collision the existing entry is replaced. */
kzsError kzcHashMapIntPutFloat(struct KzcHashMap* hashMap, kzInt key, kzFloat value);
/** Adds an entry to a hash map from integers to strings. In case of a key collision the existing entry is replaced. */
kzsError kzcHashMapIntPutString(struct KzcHashMap* hashMap, kzInt key, kzString value);
/** Adds an entry to a hash map from unsigned integers to pointers. In case of a key collision the existing entry is replaced. */
kzsError kzcHashMapUintPutPointer(struct KzcHashMap* hashMap, kzUint key, const void* value);
/** Adds an entry to a hash map from unsigned integers to integers. In case of a key collision the existing entry is replaced. */
kzsError kzcHashMapUintPutInt(struct KzcHashMap* hashMap, kzUint key, kzInt value);
/** Adds an entry to a hash map from unsigned integers to unsigned integers. In case of a key collision the existing entry is replaced. */
kzsError kzcHashMapUintPutUint(struct KzcHashMap* hashMap, kzUint key, kzUint value);
/** Adds an entry to a hash map from unsigned integers to floats. In case of a key collision the existing entry is replaced. */
kzsError kzcHashMapUintPutFloat(struct KzcHashMap* hashMap, kzUint key, kzFloat value);
/** Adds an entry to a hash map from unsigned integers to strings. In case of a key collision the existing entry is replaced. */
kzsError kzcHashMapUintPutString(struct KzcHashMap* hashMap, kzUint key, kzString value);
/** Adds an entry to a hash map from floats to pointers. In case of a key collision the existing entry is replaced. */
kzsError kzcHashMapFloatPutPointer(struct KzcHashMap* hashMap, kzFloat key, const void* value);
/** Adds an entry to a hash map from floats to integers. In case of a key collision the existing entry is replaced. */
kzsError kzcHashMapFloatPutInt(struct KzcHashMap* hashMap, kzFloat key, kzInt value);
/** Adds an entry to a hash map from floats to unsigned integers. In case of a key collision the existing entry is replaced. */
kzsError kzcHashMapFloatPutUint(struct KzcHashMap* hashMap, kzFloat key, kzUint value);
/** Adds an entry to a hash map from floats to floats. In case of a key collision the existing entry is replaced. */
kzsError kzcHashMapFloatPutFloat(struct KzcHashMap* hashMap, kzFloat key, kzFloat value);
/** Adds an entry to a hash map from floats to strings. In case of a key collision the existing entry is replaced. */
kzsError kzcHashMapFloatPutString(struct KzcHashMap* hashMap, kzFloat key, kzString value);
/** Adds an entry to a hash map from strings to pointers. In case of a key collision the existing entry is replaced. */
kzsError kzcHashMapStringPutPointer(struct KzcHashMap* hashMap, kzString key, const void* value);
/** Adds an entry to a hash map from strings to integers. In case of a key collision the existing entry is replaced. */
kzsError kzcHashMapStringPutInt(struct KzcHashMap* hashMap, kzString key, kzInt value);
/** Adds an entry to a hash map from strings to unsigned integers. In case of a key collision the existing entry is replaced. */
kzsError kzcHashMapStringPutUint(struct KzcHashMap* hashMap, kzString key, kzUint value);
/** Adds an entry to a hash map from strings to floats. In case of a key collision the existing entry is replaced. */
kzsError kzcHashMapStringPutFloat(struct KzcHashMap* hashMap, kzString key, kzFloat value);
/** Adds an entry to a hash map from strings to strings. In case of a key collision the existing entry is replaced. */
kzsError kzcHashMapStringPutString(struct KzcHashMap* hashMap, kzString key, kzString value);
/** Adds an entry to a hash map from pointers to pointers. In case of a key collision the existing entry is replaced. */
kzsError kzcHashMapCustomPutPointer(struct KzcHashMap* hashMap, const void* key, const void* value);
/** Adds an entry to a hash map from pointers to integers. In case of a key collision the existing entry is replaced. */
kzsError kzcHashMapCustomPutInt(struct KzcHashMap* hashMap, const void* key, kzInt value);
/** Adds an entry to a hash map from pointers to unsigned integers. In case of a key collision the existing entry is replaced. */
kzsError kzcHashMapCustomPutUint(struct KzcHashMap* hashMap, const void* key, kzUint value);
/** Adds an entry to a hash map from pointers to floats. In case of a key collision the existing entry is replaced. */
kzsError kzcHashMapCustomPutFloat(struct KzcHashMap* hashMap, const void* key, kzFloat value);
/** Adds an entry to a hash map from pointers to strings. In case of a key collision the existing entry is replaced. */
kzsError kzcHashMapCustomPutString(struct KzcHashMap* hashMap, const void* key, kzString value);

/** Gets the value associated with the specified key from the hash map from pointers to pointers. If the key is not found, KZ_FALSE is returned and out_value is set to KZ_NULL. */
kzBool kzcHashMapPointerGetPointer(const struct KzcHashMap* hashMap, const void* key, void** out_value);
/** Gets the value associated with the specified key from the hash map from pointers to integers. If the key is not found, KZ_FALSE is returned and out_value is set to 0. */
kzBool kzcHashMapPointerGetInt(const struct KzcHashMap* hashMap, const void* key, kzInt* out_value);
/** Gets the value associated with the specified key from the hash map from pointers to unsigned integers. If the key is not found, KZ_FALSE is returned and out_value is set to 0U. */
kzBool kzcHashMapPointerGetUint(const struct KzcHashMap* hashMap, const void* key, kzUint* out_value);
/** Gets the value associated with the specified key from the hash map from pointers to floats. If the key is not found, KZ_FALSE is returned and out_value is set to 0.0f. */
kzBool kzcHashMapPointerGetFloat(const struct KzcHashMap* hashMap, const void* key, kzFloat* out_value);
/** Gets the value associated with the specified key from the hash map from pointers to strings. If the key is not found, KZ_FALSE is returned and out_value is set to KZ_NULL. */
kzBool kzcHashMapPointerGetString(const struct KzcHashMap* hashMap, const void* key, kzString* out_value);
/** Gets the value associated with the specified key from the hash map from integers to pointers. If the key is not found, KZ_FALSE is returned and out_value is set to KZ_NULL. */
kzBool kzcHashMapIntGetPointer(const struct KzcHashMap* hashMap, kzInt key, void** out_value);
/** Gets the value associated with the specified key from the hash map from integers to integers. If the key is not found, KZ_FALSE is returned and out_value is set to 0. */
kzBool kzcHashMapIntGetInt(const struct KzcHashMap* hashMap, kzInt key, kzInt* out_value);
/** Gets the value associated with the specified key from the hash map from integers to unsigned integers. If the key is not found, KZ_FALSE is returned and out_value is set to 0U. */
kzBool kzcHashMapIntGetUint(const struct KzcHashMap* hashMap, kzInt key, kzUint* out_value);
/** Gets the value associated with the specified key from the hash map from integers to floats. If the key is not found, KZ_FALSE is returned and out_value is set to 0.0f. */
kzBool kzcHashMapIntGetFloat(const struct KzcHashMap* hashMap, kzInt key, kzFloat* out_value);
/** Gets the value associated with the specified key from the hash map from integers to strings. If the key is not found, KZ_FALSE is returned and out_value is set to KZ_NULL. */
kzBool kzcHashMapIntGetString(const struct KzcHashMap* hashMap, kzInt key, kzString* out_value);
/** Gets the value associated with the specified key from the hash map from unsigned integers to pointers. If the key is not found, KZ_FALSE is returned and out_value is set to KZ_NULL. */
kzBool kzcHashMapUintGetPointer(const struct KzcHashMap* hashMap, kzUint key, void** out_value);
/** Gets the value associated with the specified key from the hash map from unsigned integers to integers. If the key is not found, KZ_FALSE is returned and out_value is set to 0. */
kzBool kzcHashMapUintGetInt(const struct KzcHashMap* hashMap, kzUint key, kzInt* out_value);
/** Gets the value associated with the specified key from the hash map from unsigned integers to unsigned integers. If the key is not found, KZ_FALSE is returned and out_value is set to 0U. */
kzBool kzcHashMapUintGetUint(const struct KzcHashMap* hashMap, kzUint key, kzUint* out_value);
/** Gets the value associated with the specified key from the hash map from unsigned integers to floats. If the key is not found, KZ_FALSE is returned and out_value is set to 0.0f. */
kzBool kzcHashMapUintGetFloat(const struct KzcHashMap* hashMap, kzUint key, kzFloat* out_value);
/** Gets the value associated with the specified key from the hash map from unsigned integers to strings. If the key is not found, KZ_FALSE is returned and out_value is set to KZ_NULL. */
kzBool kzcHashMapUintGetString(const struct KzcHashMap* hashMap, kzUint key, kzString* out_value);
/** Gets the value associated with the specified key from the hash map from floats to pointers. If the key is not found, KZ_FALSE is returned and out_value is set to KZ_NULL. */
kzBool kzcHashMapFloatGetPointer(const struct KzcHashMap* hashMap, kzFloat key, void** out_value);
/** Gets the value associated with the specified key from the hash map from floats to integers. If the key is not found, KZ_FALSE is returned and out_value is set to 0. */
kzBool kzcHashMapFloatGetInt(const struct KzcHashMap* hashMap, kzFloat key, kzInt* out_value);
/** Gets the value associated with the specified key from the hash map from floats to unsigned integers. If the key is not found, KZ_FALSE is returned and out_value is set to 0U. */
kzBool kzcHashMapFloatGetUint(const struct KzcHashMap* hashMap, kzFloat key, kzUint* out_value);
/** Gets the value associated with the specified key from the hash map from floats to floats. If the key is not found, KZ_FALSE is returned and out_value is set to 0.0f. */
kzBool kzcHashMapFloatGetFloat(const struct KzcHashMap* hashMap, kzFloat key, kzFloat* out_value);
/** Gets the value associated with the specified key from the hash map from floats to strings. If the key is not found, KZ_FALSE is returned and out_value is set to KZ_NULL. */
kzBool kzcHashMapFloatGetString(const struct KzcHashMap* hashMap, kzFloat key, kzString* out_value);
/** Gets the value associated with the specified key from the hash map from strings to pointers. If the key is not found, KZ_FALSE is returned and out_value is set to KZ_NULL. */
kzBool kzcHashMapStringGetPointer(const struct KzcHashMap* hashMap, kzString key, void** out_value);
/** Gets the value associated with the specified key from the hash map from strings to integers. If the key is not found, KZ_FALSE is returned and out_value is set to 0. */
kzBool kzcHashMapStringGetInt(const struct KzcHashMap* hashMap, kzString key, kzInt* out_value);
/** Gets the value associated with the specified key from the hash map from strings to unsigned integers. If the key is not found, KZ_FALSE is returned and out_value is set to 0U. */
kzBool kzcHashMapStringGetUint(const struct KzcHashMap* hashMap, kzString key, kzUint* out_value);
/** Gets the value associated with the specified key from the hash map from strings to floats. If the key is not found, KZ_FALSE is returned and out_value is set to 0.0f. */
kzBool kzcHashMapStringGetFloat(const struct KzcHashMap* hashMap, kzString key, kzFloat* out_value);
/** Gets the value associated with the specified key from the hash map from strings to strings. If the key is not found, KZ_FALSE is returned and out_value is set to KZ_NULL. */
kzBool kzcHashMapStringGetString(const struct KzcHashMap* hashMap, kzString key, kzString* out_value);
/** Gets the value associated with the specified key from the hash map from pointers to pointers. If the key is not found, KZ_FALSE is returned and out_value is set to KZ_NULL. */
kzBool kzcHashMapCustomGetPointer(const struct KzcHashMap* hashMap, const void* key, void** out_value);
/** Gets the value associated with the specified key from the hash map from pointers to integers. If the key is not found, KZ_FALSE is returned and out_value is set to 0. */
kzBool kzcHashMapCustomGetInt(const struct KzcHashMap* hashMap, const void* key, kzInt* out_value);
/** Gets the value associated with the specified key from the hash map from pointers to unsigned integers. If the key is not found, KZ_FALSE is returned and out_value is set to 0U. */
kzBool kzcHashMapCustomGetUint(const struct KzcHashMap* hashMap, const void* key, kzUint* out_value);
/** Gets the value associated with the specified key from the hash map from pointers to floats. If the key is not found, KZ_FALSE is returned and out_value is set to 0.0f. */
kzBool kzcHashMapCustomGetFloat(const struct KzcHashMap* hashMap, const void* key, kzFloat* out_value);
/** Gets the value associated with the specified key from the hash map from pointers to strings. If the key is not found, KZ_FALSE is returned and out_value is set to KZ_NULL. */
kzBool kzcHashMapCustomGetString(const struct KzcHashMap* hashMap, const void* key, kzString* out_value);

/** Gets an iterator to the location of the given pointer key in the hash map. If the key is not found, KZ_FALSE is returned and 'out_iterator' is unchanged. */
kzBool kzcHashMapPointerFind(const struct KzcHashMap* hashMap, const void* key, struct KzcHashMapIterator* out_iterator);
/** Gets an iterator to the location of the given integer key in the hash map. If the key is not found, KZ_FALSE is returned and 'out_iterator' is unchanged. */
kzBool kzcHashMapIntFind(const struct KzcHashMap* hashMap, kzInt key, struct KzcHashMapIterator* out_iterator);
/** Gets an iterator to the location of the given unsigned integer key in the hash map. If the key is not found, KZ_FALSE is returned and 'out_iterator' is unchanged. */
kzBool kzcHashMapUintFind(const struct KzcHashMap* hashMap, kzUint key, struct KzcHashMapIterator* out_iterator);
/** Gets an iterator to the location of the given float key in the hash map. If the key is not found, KZ_FALSE is returned and 'out_iterator' is unchanged. */
kzBool kzcHashMapFloatFind(const struct KzcHashMap* hashMap, kzFloat key, struct KzcHashMapIterator* out_iterator);
/** Gets an iterator to the location of the given string key in the hash map. If the key is not found, KZ_FALSE is returned and 'out_iterator' is unchanged. */
kzBool kzcHashMapStringFind(const struct KzcHashMap* hashMap, kzString key, struct KzcHashMapIterator* out_iterator);
/** Gets an iterator to the location of the given pointer key in the hash map. If the key is not found, KZ_FALSE is returned and 'out_iterator' is unchanged. */
kzBool kzcHashMapCustomFind(const struct KzcHashMap* hashMap, const void* key, struct KzcHashMapIterator* out_iterator);

/** Removes an entry with the given pointer key from the hash map. If the key does not exist, an error is returned. */
kzsError kzcHashMapPointerRemove(struct KzcHashMap* hashMap, const void* key);
/** Removes an entry with the given integer key from the hash map. If the key does not exist, an error is returned. */
kzsError kzcHashMapIntRemove(struct KzcHashMap* hashMap, kzInt key);
/** Removes an entry with the given unsigned integer key from the hash map. If the key does not exist, an error is returned. */
kzsError kzcHashMapUintRemove(struct KzcHashMap* hashMap, kzUint key);
/** Removes an entry with the given float key from the hash map. If the key does not exist, an error is returned. */
kzsError kzcHashMapFloatRemove(struct KzcHashMap* hashMap, kzFloat key);
/** Removes an entry with the given string key from the hash map. If the key does not exist, an error is returned. */
kzsError kzcHashMapStringRemove(struct KzcHashMap* hashMap, kzString key);
/** Removes an entry with the given pointer key from the hash map. If the key does not exist, an error is returned. */
kzsError kzcHashMapCustomRemove(struct KzcHashMap* hashMap, const void* key);

/** Removes an entry with the given pointer key from the hash map, if such an entry exists. If the key does not exist, silently does nothing. */
kzsError kzcHashMapPointerRemoveIfExists(struct KzcHashMap* hashMap, const void* key);
/** Removes an entry with the given integer key from the hash map, if such an entry exists. If the key does not exist, silently does nothing. */
kzsError kzcHashMapIntRemoveIfExists(struct KzcHashMap* hashMap, kzInt key);
/** Removes an entry with the given unsigned integer key from the hash map, if such an entry exists. If the key does not exist, silently does nothing. */
kzsError kzcHashMapUintRemoveIfExists(struct KzcHashMap* hashMap, kzUint key);
/** Removes an entry with the given float key from the hash map, if such an entry exists. If the key does not exist, silently does nothing. */
kzsError kzcHashMapFloatRemoveIfExists(struct KzcHashMap* hashMap, kzFloat key);
/** Removes an entry with the given string key from the hash map, if such an entry exists. If the key does not exist, silently does nothing. */
kzsError kzcHashMapStringRemoveIfExists(struct KzcHashMap* hashMap, kzString key);
/** Removes an entry with the given pointer key from the hash map, if such an entry exists. If the key does not exist, silently does nothing. */
kzsError kzcHashMapCustomRemoveIfExists(struct KzcHashMap* hashMap, const void* key);

/** Gets the stored key corresponding to the pointer key given as a parameter. Returns ::KZ_NULL if an entry with a matching key does not exist in the hash map. */
const void* kzcHashMapPointerGetStoredKey(const struct KzcHashMap* hashMap, const void* key);
/** Gets the stored key corresponding to the pointer key given as a parameter. Returns ::KZ_NULL if an entry with a matching key does not exist in the hash map. */
const void* kzcHashMapCustomGetStoredKey(const struct KzcHashMap* hashMap, const void* key);

/** Checks if the specified key exists in the hash map from pointers. Returns ::KZ_TRUE if the key is found and KZ_FALSE otherwise. */
kzBool kzcHashMapPointerContains(const struct KzcHashMap* hashMap, const void* key);
/** Checks if the specified key exists in the hash map from integers. Returns ::KZ_TRUE if the key is found and KZ_FALSE otherwise. */
kzBool kzcHashMapIntContains(const struct KzcHashMap* hashMap, kzInt key);
/** Checks if the specified key exists in the hash map from unsigned integers. Returns ::KZ_TRUE if the key is found and KZ_FALSE otherwise. */
kzBool kzcHashMapUintContains(const struct KzcHashMap* hashMap, kzUint key);
/** Checks if the specified key exists in the hash map from floats. Returns ::KZ_TRUE if the key is found and KZ_FALSE otherwise. */
kzBool kzcHashMapFloatContains(const struct KzcHashMap* hashMap, kzFloat key);
/** Checks if the specified key exists in the hash map from strings. Returns ::KZ_TRUE if the key is found and KZ_FALSE otherwise. */
kzBool kzcHashMapStringContains(const struct KzcHashMap* hashMap, kzString key);
/** Checks if the specified key exists in the hash map from pointers. Returns ::KZ_TRUE if the key is found and KZ_FALSE otherwise. */
kzBool kzcHashMapCustomContains(const struct KzcHashMap* hashMap, const void* key);

/** Gets the specified value from the hash map from pointers to pointers. Returns error if the key is not found. */
kzsError kzcHashMapPointerGetPointerOrThrowError(const struct KzcHashMap* hashMap, const void* key, void** out_value);
/** Gets the specified value from the hash map from pointers to integers. Returns error if the key is not found. */
kzsError kzcHashMapPointerGetIntOrThrowError(const struct KzcHashMap* hashMap, const void* key, kzInt* out_value);
/** Gets the specified value from the hash map from pointers to unsigned integers. Returns error if the key is not found. */
kzsError kzcHashMapPointerGetUintOrThrowError(const struct KzcHashMap* hashMap, const void* key, kzUint* out_value);
/** Gets the specified value from the hash map from pointers to floats. Returns error if the key is not found. */
kzsError kzcHashMapPointerGetFloatOrThrowError(const struct KzcHashMap* hashMap, const void* key, kzFloat* out_value);
/** Gets the specified value from the hash map from pointers to strings. Returns error if the key is not found. */
kzsError kzcHashMapPointerGetStringOrThrowError(const struct KzcHashMap* hashMap, const void* key, kzString* out_value);
/** Gets the specified value from the hash map from integers to pointers. Returns error if the key is not found. */
kzsError kzcHashMapIntGetPointerOrThrowError(const struct KzcHashMap* hashMap, kzInt key, void** out_value);
/** Gets the specified value from the hash map from integers to integers. Returns error if the key is not found. */
kzsError kzcHashMapIntGetIntOrThrowError(const struct KzcHashMap* hashMap, kzInt key, kzInt* out_value);
/** Gets the specified value from the hash map from integers to unsigned integers. Returns error if the key is not found. */
kzsError kzcHashMapIntGetUintOrThrowError(const struct KzcHashMap* hashMap, kzInt key, kzUint* out_value);
/** Gets the specified value from the hash map from integers to floats. Returns error if the key is not found. */
kzsError kzcHashMapIntGetFloatOrThrowError(const struct KzcHashMap* hashMap, kzInt key, kzFloat* out_value);
/** Gets the specified value from the hash map from integers to strings. Returns error if the key is not found. */
kzsError kzcHashMapIntGetStringOrThrowError(const struct KzcHashMap* hashMap, kzInt key, kzString* out_value);
/** Gets the specified value from the hash map from unsigned integers to pointers. Returns error if the key is not found. */
kzsError kzcHashMapUintGetPointerOrThrowError(const struct KzcHashMap* hashMap, kzUint key, void** out_value);
/** Gets the specified value from the hash map from unsigned integers to integers. Returns error if the key is not found. */
kzsError kzcHashMapUintGetIntOrThrowError(const struct KzcHashMap* hashMap, kzUint key, kzInt* out_value);
/** Gets the specified value from the hash map from unsigned integers to unsigned integers. Returns error if the key is not found. */
kzsError kzcHashMapUintGetUintOrThrowError(const struct KzcHashMap* hashMap, kzUint key, kzUint* out_value);
/** Gets the specified value from the hash map from unsigned integers to floats. Returns error if the key is not found. */
kzsError kzcHashMapUintGetFloatOrThrowError(const struct KzcHashMap* hashMap, kzUint key, kzFloat* out_value);
/** Gets the specified value from the hash map from unsigned integers to strings. Returns error if the key is not found. */
kzsError kzcHashMapUintGetStringOrThrowError(const struct KzcHashMap* hashMap, kzUint key, kzString* out_value);
/** Gets the specified value from the hash map from floats to pointers. Returns error if the key is not found. */
kzsError kzcHashMapFloatGetPointerOrThrowError(const struct KzcHashMap* hashMap, kzFloat key, void** out_value);
/** Gets the specified value from the hash map from floats to integers. Returns error if the key is not found. */
kzsError kzcHashMapFloatGetIntOrThrowError(const struct KzcHashMap* hashMap, kzFloat key, kzInt* out_value);
/** Gets the specified value from the hash map from floats to unsigned integers. Returns error if the key is not found. */
kzsError kzcHashMapFloatGetUintOrThrowError(const struct KzcHashMap* hashMap, kzFloat key, kzUint* out_value);
/** Gets the specified value from the hash map from floats to floats. Returns error if the key is not found. */
kzsError kzcHashMapFloatGetFloatOrThrowError(const struct KzcHashMap* hashMap, kzFloat key, kzFloat* out_value);
/** Gets the specified value from the hash map from floats to strings. Returns error if the key is not found. */
kzsError kzcHashMapFloatGetStringOrThrowError(const struct KzcHashMap* hashMap, kzFloat key, kzString* out_value);
/** Gets the specified value from the hash map from strings to pointers. Returns error if the key is not found. */
kzsError kzcHashMapStringGetPointerOrThrowError(const struct KzcHashMap* hashMap, kzString key, void** out_value);
/** Gets the specified value from the hash map from strings to integers. Returns error if the key is not found. */
kzsError kzcHashMapStringGetIntOrThrowError(const struct KzcHashMap* hashMap, kzString key, kzInt* out_value);
/** Gets the specified value from the hash map from strings to unsigned integers. Returns error if the key is not found. */
kzsError kzcHashMapStringGetUintOrThrowError(const struct KzcHashMap* hashMap, kzString key, kzUint* out_value);
/** Gets the specified value from the hash map from strings to floats. Returns error if the key is not found. */
kzsError kzcHashMapStringGetFloatOrThrowError(const struct KzcHashMap* hashMap, kzString key, kzFloat* out_value);
/** Gets the specified value from the hash map from strings to strings. Returns error if the key is not found. */
kzsError kzcHashMapStringGetStringOrThrowError(const struct KzcHashMap* hashMap, kzString key, kzString* out_value);
/** Gets the specified value from the hash map from pointers to pointers. Returns error if the key is not found. */
kzsError kzcHashMapCustomGetPointerOrThrowError(const struct KzcHashMap* hashMap, const void* key, void** out_value);
/** Gets the specified value from the hash map from pointers to integers. Returns error if the key is not found. */
kzsError kzcHashMapCustomGetIntOrThrowError(const struct KzcHashMap* hashMap, const void* key, kzInt* out_value);
/** Gets the specified value from the hash map from pointers to unsigned integers. Returns error if the key is not found. */
kzsError kzcHashMapCustomGetUintOrThrowError(const struct KzcHashMap* hashMap, const void* key, kzUint* out_value);
/** Gets the specified value from the hash map from pointers to floats. Returns error if the key is not found. */
kzsError kzcHashMapCustomGetFloatOrThrowError(const struct KzcHashMap* hashMap, const void* key, kzFloat* out_value);
/** Gets the specified value from the hash map from pointers to strings. Returns error if the key is not found. */
kzsError kzcHashMapCustomGetStringOrThrowError(const struct KzcHashMap* hashMap, const void* key, kzString* out_value);

/** Returns the pointer key of the hash map entry pointed by the iterator. */
#define kzcHashMapIteratorPointerGetKey(iterator_param) (kzcHashMapIteratorPointerGetKey_private(&iterator_param))
/** Returns the integer key of the hash map entry pointed by the iterator. */
#define kzcHashMapIteratorIntGetKey(iterator_param) (kzcHashMapIteratorIntGetKey_private(&iterator_param))
/** Returns the unsigned integer key of the hash map entry pointed by the iterator. */
#define kzcHashMapIteratorUintGetKey(iterator_param) (kzcHashMapIteratorUintGetKey_private(&iterator_param))
/** Returns the float key of the hash map entry pointed by the iterator. */
#define kzcHashMapIteratorFloatGetKey(iterator_param) (kzcHashMapIteratorFloatGetKey_private(&iterator_param))
/** Returns the string key of the hash map entry pointed by the iterator. */
#define kzcHashMapIteratorStringGetKey(iterator_param) (kzcHashMapIteratorStringGetKey_private(&iterator_param))
/** Returns the pointer key of the hash map entry pointed by the iterator. */
#define kzcHashMapIteratorCustomGetKey(iterator_param) (kzcHashMapIteratorCustomGetKey_private(&iterator_param))

/** Returns the pointer value of the hash map entry pointed by the iterator. */
#define kzcHashMapIteratorGetPointerValue(iterator_param) (kzcHashMapIteratorGetPointerValue_private(&iterator_param))
/** Returns the integer value of the hash map entry pointed by the iterator. */
#define kzcHashMapIteratorGetIntValue(iterator_param) (kzcHashMapIteratorGetIntValue_private(&iterator_param))
/** Returns the unsigned integer value of the hash map entry pointed by the iterator. */
#define kzcHashMapIteratorGetUintValue(iterator_param) (kzcHashMapIteratorGetUintValue_private(&iterator_param))
/** Returns the float value of the hash map entry pointed by the iterator. */
#define kzcHashMapIteratorGetFloatValue(iterator_param) (kzcHashMapIteratorGetFloatValue_private(&iterator_param))
/** Returns the string value of the hash map entry pointed by the iterator. */
#define kzcHashMapIteratorGetStringValue(iterator_param) (kzcHashMapIteratorGetStringValue_private(&iterator_param))

/** Sets the pointer value of the hash map entry pointed by the iterator. */
#define kzcHashMapIteratorSetPointerValue(iterator_param, value_param) (kzcHashMapIteratorSetPointerValue_private(&iterator_param, value_param))
/** Sets the integer value of the hash map entry pointed by the iterator. */
#define kzcHashMapIteratorSetIntValue(iterator_param, value_param) (kzcHashMapIteratorSetIntValue_private(&iterator_param, value_param))
/** Sets the unsigned integer value of the hash map entry pointed by the iterator. */
#define kzcHashMapIteratorSetUintValue(iterator_param, value_param) (kzcHashMapIteratorSetUintValue_private(&iterator_param, value_param))
/** Sets the float value of the hash map entry pointed by the iterator. */
#define kzcHashMapIteratorSetFloatValue(iterator_param, value_param) (kzcHashMapIteratorSetFloatValue_private(&iterator_param, value_param))
/** Sets the string value of the hash map entry pointed by the iterator. */
#define kzcHashMapIteratorSetStringValue(iterator_param, value_param) (kzcHashMapIteratorSetStringValue_private(&iterator_param, value_param))


/* Private definitions. */

/** \see kzcHashMapIteratorPointerGetKey */
const void* kzcHashMapIteratorPointerGetKey_private(const struct KzcHashMapIterator* iterator);
/** \see kzcHashMapIteratorIntGetKey */
kzInt kzcHashMapIteratorIntGetKey_private(const struct KzcHashMapIterator* iterator);
/** \see kzcHashMapIteratorUintGetKey */
kzUint kzcHashMapIteratorUintGetKey_private(const struct KzcHashMapIterator* iterator);
/** \see kzcHashMapIteratorFloatGetKey */
kzFloat kzcHashMapIteratorFloatGetKey_private(const struct KzcHashMapIterator* iterator);
/** \see kzcHashMapIteratorStringGetKey */
kzString kzcHashMapIteratorStringGetKey_private(const struct KzcHashMapIterator* iterator);
/** \see kzcHashMapIteratorCustomGetKey */
const void* kzcHashMapIteratorCustomGetKey_private(const struct KzcHashMapIterator* iterator);

/** \see kzcHashMapIteratorGetPointerValue */
void* kzcHashMapIteratorGetPointerValue_private(const struct KzcHashMapIterator* iterator);
/** \see kzcHashMapIteratorGetIntValue */
kzInt kzcHashMapIteratorGetIntValue_private(const struct KzcHashMapIterator* iterator);
/** \see kzcHashMapIteratorGetUintValue */
kzUint kzcHashMapIteratorGetUintValue_private(const struct KzcHashMapIterator* iterator);
/** \see kzcHashMapIteratorGetFloatValue */
kzFloat kzcHashMapIteratorGetFloatValue_private(const struct KzcHashMapIterator* iterator);
/** \see kzcHashMapIteratorGetStringValue */
kzString kzcHashMapIteratorGetStringValue_private(const struct KzcHashMapIterator* iterator);

/** \see kzcHashMapIteratorSetPointerValue */
void kzcHashMapIteratorSetPointerValue_private(const struct KzcHashMapIterator* iterator, const void* value);
/** \see kzcHashMapIteratorSetIntValue */
void kzcHashMapIteratorSetIntValue_private(const struct KzcHashMapIterator* iterator, kzInt value);
/** \see kzcHashMapIteratorSetUintValue */
void kzcHashMapIteratorSetUintValue_private(const struct KzcHashMapIterator* iterator, kzUint value);
/** \see kzcHashMapIteratorSetFloatValue */
void kzcHashMapIteratorSetFloatValue_private(const struct KzcHashMapIterator* iterator, kzFloat value);
/** \see kzcHashMapIteratorSetStringValue */
void kzcHashMapIteratorSetStringValue_private(const struct KzcHashMapIterator* iterator, kzString value);


KZ_HEADER_END



