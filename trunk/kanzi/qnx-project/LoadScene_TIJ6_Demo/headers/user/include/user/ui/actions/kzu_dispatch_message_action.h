/**
* \file
* Dispatch message action.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_DISPATCH_MESSAGE_ACTION_H
#define KZU_DISPATCH_MESSAGE_ACTION_H


#include "kzu_action_common.h"

#include <system/kzs_types.h>
#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations. */
struct KzuVariant;
struct KzuPropertyType;
struct KzuAction;
struct KzcMemoryManager;
struct KzuUIDomain;


/** Action type identifier for dispatch message action. */
extern const KzuActionType KZU_ACTION_TYPE_DISPATCH_MESSAGE_ACTION;


/** Create a dispatch message action. */
kzsError kzuDispatchMessageActionCreate(const struct KzcMemoryManager* memoryManager, struct KzuUIDomain* uiDomain, struct KzuAction** out_action);
/** Add a value binding to a dispatch message action. */
kzsError kzuDispatchMessageActionAddValueBinding(const struct KzuAction* action, const struct KzuVariant* sourceValue, const struct KzuPropertyType* targetArgument);
/** Add an argument binding to a dispatch message action. */
kzsError kzuDispatchMessageActionAddArgumentBinding(const struct KzuAction* action, const struct KzuPropertyType* sourceArgument, const struct KzuPropertyType* targetArgument);
/** Add an object node property binding to a dispatch message action. */
kzsError kzuDispatchMessageActionAddObjectNodePropertyBinding(const struct KzuAction* action, kzString sourceObjectPath,
                                                              const struct KzuPropertyType* sourcePropertyType, const struct KzuPropertyType* targetArgument);

/** Set ui domain to dispatch message action. */
void kzuDispatchMessageActionSetUIDomain(struct KzuAction* action, struct KzuUIDomain* uiDomain);

KZ_HEADER_END


#endif
