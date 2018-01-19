/**
* \file
* Message type.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_MESSAGE_TYPE_H
#define KZU_MESSAGE_TYPE_H


#include <system/kzs_types.h>
#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations */
struct KzcInputStream;
struct KzcMemoryManager;
struct KzuBinaryFileInfo;


/**
 * \struct KzuMessageType
 * Message type.
 */
struct KzuMessageType;


/** Message routing enumeration. */
enum KzuMessageRouting
{
    KZU_MESSAGE_ROUTING_TUNNELLING_BUBBLING     = 0,
    KZU_MESSAGE_ROUTING_TUNNELLING              = 1,
    KZU_MESSAGE_ROUTING_BUBBLING                = 2,
    KZU_MESSAGE_ROUTING_DIRECT                  = 3
};


/** Create a message type. */
kzsError kzuMessageTypeCreate(const struct KzcMemoryManager* memoryManager, kzString name, enum KzuMessageRouting routing, struct KzuMessageType** out_messageType);

/** Delete a message type. */
kzsError kzuMessageTypeDelete(struct KzuMessageType* messageType);

/** Loads message type from KZB. */
kzsError kzuMessageTypeLoadFromKZB(struct KzuMessageType* messageType, struct KzcInputStream* inputStream);


/** Gets the name of a message type. */
kzString kzuMessageTypeGetName(const struct KzuMessageType* messageType);

/** Gets the routing method of a message type. */
enum KzuMessageRouting kzuMessageTypeGetRouting(const struct KzuMessageType* messageType);


KZ_HEADER_END


#endif
