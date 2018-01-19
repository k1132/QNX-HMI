/**
* \file
* Threading support.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZS_THREAD_H
#define KZS_THREAD_H


#include <system/debug/kzs_error.h>
#include <system/kzs_types.h>
#include <system/kzs_header.h>

#if defined MAC || defined IOS || defined INTEGRITY
#include <pthread.h>
#endif


KZ_HEADER_BEGIN


/**
 * \struct KzsThread
 * An operating system thread that allows concurrent execution of code.
 * The code is supplied as a callback of type KzsThreadRunner.
 */
struct KzsThread;


/** Key type to use when storing thread specific global data. */
#if defined MAC || defined IOS || defined INTEGRITY
typedef pthread_key_t KzsThreadLocalStorageKey;
#elif defined WIN32 || defined ANDROID || defined QNX
typedef kzInt KzsThreadLocalStorageKey;
#else
typedef kzUint KzsThreadLocalStorageKey;
#endif


/** Thread identifier. */
#ifdef WIN32
typedef unsigned long KzsThreadId;
#else
typedef void* KzsThreadId;
#endif

/**
 * \struct KzsThreadLock
 * Lock object for synchronizing threads. This object can be used to prevent multiple threads from accessing data
 * concurrently and to signal between threads. Use kzsThreadLockAcquire and kzsThreadLockRelease to protect data from
 * concurrent access. Use kzsThreadLockWait and kzsThreadLockSet to communicate between threads.
 */
struct KzsThreadLock;


/** Thread execution function type. */
typedef kzsError (*KzsThreadRunner)(void* userData);


/**
 * Creates a thread using the given runner function and arbitrary user data. This function also starts the thread.
 * If deleteAutomatically is KZ_TRUE, the thread object is deleted when the thread finishes execution.
 * \param out_thread Resulting thread, KZ_NULL if not required.
 */
kzsError kzsThreadCreate(KzsThreadRunner threadRunner, void* userData, kzBool deleteAutomatically, struct KzsThread** out_thread);

/** Deletes a thread. It is an error to delete a running thread. */
kzsError kzsThreadDelete(struct KzsThread* thread);

/** Waits until the given thread is terminated. */
kzsError kzsThreadJoin(struct KzsThread* thread);

/**
 * Returns the error result of the thread. Also returns error if the thread has not yet finished execution.
 * Use kzsThreadJoin to make sure the thread is finished.
 */
kzsError kzsThreadGetExitResult(const struct KzsThread* thread);

/** Gets the current thread id. */
KzsThreadId kzsThreadGetCurrent(void);

/** Checks if the given thread is the thread that is executing this function. */
kzBool kzsThreadIsCurrent(const struct KzsThread* thread);

/** Sleeps the thread that is executing this function by given amount of milliseconds. */
kzsError kzsThreadSleep(kzUint milliseconds);


/** Creates a thread synchronization lock object. */
kzsError kzsThreadLockCreate(struct KzsThreadLock** out_threadLock);

/** Deletes a thread synchronization lock object. */
kzsError kzsThreadLockDelete(struct KzsThreadLock* threadLock);

/** Starts a synchronized code section by acquiring a thread lock. This call must be paired with kzsThreadLockRelease in all code paths. */
kzsError kzsThreadLockAcquire(struct KzsThreadLock* threadLock);

/** Ends a synchronized code section by releasing a thread lock. This call must be paired with kzsThreadLockAcquire in all code paths. */
kzsError kzsThreadLockRelease(struct KzsThreadLock* threadLock);

/**
 * Waits for a given thread lock to become true. If the lock is already true, this function will not wait.
 * If autoLock is KZ_TRUE, the lock must not be already acquired by the current thread calling the function.
 * If autoLock is KZ_FALSE, the lock must have been acquired by the calling thread exactly once.
 */
kzsError kzsThreadLockWait(struct KzsThreadLock* threadLock, kzBool autoLock);

/**
 * Waits for a given thread lock to become true. If the lock is already true, this function will not wait.
 * If the wait lasts longer than the time limit given as parameter, the function exits.
 * Use kzsThreadLockIsSet to check if the wait was ended by a signal or exceeding the time limit.
 * If autoLock is KZ_TRUE, the lock must not be already acquired by the current thread calling the function.
 * If autoLock is KZ_FALSE, the lock must have been acquired by the calling thread exactly once.
 */
kzsError kzsThreadLockWaitTimeout(struct KzsThreadLock* threadLock, kzUint milliseconds, kzBool autoLock);

/**
 * Waits for a given thread lock to become true. If the lock is already true, this function will not wait.
 * After the wait is finished, the lock will be set to KZ_FALSE before any other thread wokes up.
 * If autoLock is KZ_TRUE, the lock must not be already acquired by the current thread calling the function.
 * If autoLock is KZ_FALSE, the lock must have been acquired by the calling thread exactly once.
 */
kzsError kzsThreadLockWaitAndReset(struct KzsThreadLock* threadLock, kzBool autoLock);

/** 
 * Sets the value of the given thread lock to true or false. If the value is true, any thread waiting for it can wake up.
 * If autoLock is KZ_TRUE, the lock must not be already acquired by the current thread calling the function.
 * If autoLock is KZ_FALSE, the lock must have been acquired by the calling thread exactly once.
 */
kzsError kzsThreadLockSet(struct KzsThreadLock* threadLock, kzBool value, kzBool autoLock);

/** 
 * Returns the value of the given thread lock (true or false).
 * If autoLock is KZ_TRUE, the lock must not be already acquired by the current thread calling the function.
 * If autoLock is KZ_FALSE, the lock must have been acquired by the calling thread exactly once.
 */
kzsError kzsThreadLockIsSet(struct KzsThreadLock* threadLock, kzBool autoLock, kzBool* out_isSet);

/** Gets number of processor cores in system. Throws KZS_EXCEPTION_UNDEFINED_THREAD_OPERATION if processor count cannot be queried from system. */
kzsException kzsThreadGetProcessorCount(kzUint* out_processorCount);

/** Initializes thread local storage key. */
kzsError kzsThreadLocalStorageKeyInitialize(KzsThreadLocalStorageKey* key);
/** Uninitializes thread local storage key. */
kzsError kzsThreadLocalStorageKeyUninitialize(KzsThreadLocalStorageKey* key);
/** Sets thread specific global data using the given key. This data is unique between different threads and can be retrieved with GetData. */
kzsError kzsThreadLocalStoragePutData(const KzsThreadLocalStorageKey* key, void* data);
/** Gets thread specific global data using the given key. */
kzsError kzsThreadLocalStorageGetData(const KzsThreadLocalStorageKey* key, void** out_data);


KZ_HEADER_END


#endif
