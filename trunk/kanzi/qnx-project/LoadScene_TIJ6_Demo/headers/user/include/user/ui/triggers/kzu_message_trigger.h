/**
* \file
* Message trigger.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_MESSAGE_HANDLER_TRIGGER_H
#define KZU_MESSAGE_HANDLER_TRIGGER_H


#include <system/kzs_types.h>
#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations. */
struct KzuTrigger;
struct KzuUIDomain;
struct KzcMemoryManager;


/** Creates a message handler trigger. */
kzsError kzuMessageHandlerTriggerCreate(const struct KzcMemoryManager* memoryManager, struct KzuUIDomain* uiDomain, struct KzuTrigger** out_trigger);


KZ_HEADER_END


#endif
