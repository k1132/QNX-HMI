/**
* \file
* Message object private functions.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_MESSAGE_PRIVATE_H
#define KZU_MESSAGE_PRIVATE_H


#include <system/kzs_types.h>
#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations. */
struct KzuMessageType;
struct KzcMemoryManager;


struct KzuMessage
{
    kzBool valid;                             /**< Is message valid. */
    kzBool handled;                           /**< Is message handled yet. */
    kzUint timestamp;                         /**< Timestamp of message. */
    struct KzuMessageDispatcher* dispatcher;  /**< Dispatcher assigned to the message. */
    const struct KzuMessageType* messageType; /**< Type of the message. */
    struct KzuObjectNode* source;             /**< Sender of the message. */
    struct KzcDynamicArray* arguments;        /**< Arguments of the message. */
};


/** Create a message object. */
kzsError kzuMessageCreate_private(const struct KzcMemoryManager* memoryManager, struct KzuMessageDispatcher* messageDispatcher,
                                  const struct KzuMessageType* messageType, struct KzuMessage** out_message);

/** Set the message source. */
void kzuMessageSetSource_private(struct KzuMessage* message, struct KzuObjectNode* source);
/** Set the message timestamp. */
void kzuMessageSetTimestamp_private(struct KzuMessage* message, kzUint timestamp);


KZ_HEADER_END


#endif
