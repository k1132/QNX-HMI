/**
 * \file
 * Message registry.
 * 
 * Copyright 2008-2014 by Rightware. All rights reserved.
 */
#ifndef KZU_MESSAGE_REGISTRY_H
#define KZU_MESSAGE_REGISTRY_H


#include <user/ui/message/kzu_message_type.h>


#include <system/kzs_types.h>
#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations */
struct KzcMemoryManager;


/** Creates message registry. */
kzsError kzuMessageRegistryCreate(const struct KzcMemoryManager* memoryManager);

/** Deletes standard message types. */
kzsError kzuMessageRegistryDelete(void);

/** Finds a message type by name. */
const struct KzuMessageType* kzuMessageRegistryFindMessageType(kzString name);

/** Adds a message type */
kzsError kzuMessageRegistryAddMessageType(const struct KzcMemoryManager* memoryManager, kzString name, enum KzuMessageRouting routing, struct KzuMessageType** out_messageType);


KZ_HEADER_END


#endif
