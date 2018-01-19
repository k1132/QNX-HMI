/**
* \file
* Thread barrier.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZS_BARRIER_H
#define KZS_BARRIER_H


#include <system/debug/kzs_error.h>
#include <system/kzs_types.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/**
 * \struct KzsThreadBarrier
 * Barrier object for synchronizing threads. This object can be used to implement multi-thread rendezvous.
 * Use kzsThreadBarrierWait to communicate between threads.
 */
struct KzsThreadBarrier;


/**
 * Creates a thread synchronization barrier object.
 * The threadCount parameter specifies the number of threads to rendezvous.
 */
kzsError kzsThreadBarrierCreate(kzUint threadCount, struct KzsThreadBarrier** out_threadBarrier);

/** Deletes a thread synchronization barrier object. */
kzsError kzsThreadBarrierDelete(struct KzsThreadBarrier* threadBarrier);

/**
 * Implements the barrier synchronization pattern. 
 * Blocks the calling thread until sufficient amount of threads have reached the barrier.
 */
kzsError kzsThreadBarrierWait(struct KzsThreadBarrier* threadBarrier);


KZ_HEADER_END


#endif
