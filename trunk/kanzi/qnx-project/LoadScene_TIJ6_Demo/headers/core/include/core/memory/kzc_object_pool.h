/**
* \file
* Object pool. Object pools can be used to reuse objects of a specified type.
* The object pool can grow as necessary and resets its objects when released back to the pool.
*
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZC_OBJECT_POOL_H
#define KZC_OBJECT_POOL_H


#include <system/debug/kzs_error.h>
#include <system/kzs_types.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations. */
struct KzcMemoryManager;


/**
* \struct KzcObjectPool
* Pools objects of a specific type.
*
* Creates new objects as needed and resets objects when they are released back to the pool.
*/
struct KzcObjectPool;


/** A function that creates a new object for the pool. */
typedef kzsError (*KzcObjectPoolCreateFunction)(const struct KzcMemoryManager* memoryManager, void* userData, void** out_object);

/** A function that resets an object to a clean state, ready to be reused. */
typedef kzsError (*KzcObjectPoolResetFunction)(void* object, void* userData);

/** A function that deletes an object. */
typedef kzsError (*KzcObjectPoolDeleteFunction)(void* object, void* userData);


/**
* \struct KzcObjectPoolConfiguration
* Tells the object pool how to create, reset and delete objects.
*/
struct KzcObjectPoolConfiguration
{
    KzcObjectPoolCreateFunction createFunction; /**< Creates a new object. Must not be KZ_NULL. */
    void* createUserData; /**< User data for createFunction. */

    KzcObjectPoolResetFunction resetFunction; /**< Resets an object so that it can be reused. May be KZ_NULL. */
    void* resetUserData; /**< User data for resetFunction. */

    KzcObjectPoolDeleteFunction deleteFunction; /**< Deletes an object. Must not be KZ_NULL.*/
    void* deleteUserData; /**< User data for deleteFunction. */
};


/**
* Creates an object pool for a given object type.
*
* At destruction the object pool destroys all its currently unused objects.
* The user is responsible for destroying objects that have not been returned to the pool at this time.
* \param memoryManager The memory manager used for allocating the pool and its objects.
* \param configuration Defines how objects are created, reseted and destroyed.
*/
kzsError kzcObjectPoolCreate(const struct KzcMemoryManager* memoryManager, struct KzcObjectPoolConfiguration configuration, struct KzcObjectPool** out_objectPool);

/** Destroys an object pool. */
kzsError kzcObjectPoolDelete(struct KzcObjectPool* objectPool);


/** Acquires an object from the pool. */
kzsError kzcObjectPoolAcquire(const struct KzcObjectPool* objectPool, void** out_object);

/** Releases an object back to the pool. */
kzsError kzcObjectPoolRelease(const struct KzcObjectPool* objectPool, void* object);


KZ_HEADER_END


#endif
