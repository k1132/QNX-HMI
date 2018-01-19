/**
* \file
* Frame time queue.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_FRAME_TIME_QUEUE_H
#define KZU_FRAME_TIME_QUEUE_H


#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declaration structures. */
struct KzcMemoryManager;

/**
* \struct KzuFrameTimeQueue
* Queue specialization for calculating frame rate.
*/
struct KzuFrameTimeQueue;


/** Create a frame time queue. */
kzsError KzuFrameTimeQueueCreate(const struct KzcMemoryManager* memoryManager, struct KzuFrameTimeQueue** out_queue);
/** Delete a frame time queue. */
kzsError KzuFrameTimeQueueDelete(struct KzuFrameTimeQueue* queue);

/** Updates the frame time queue with a new frame time. */
void KzuFrameTimeQueueUpdate(struct KzuFrameTimeQueue* queue, kzUint frameTime);
/** Returns the current FPS. */
kzFloat KzuFrameTimeQueueGetFPS(const struct KzuFrameTimeQueue* queue);


KZ_HEADER_END


#endif
