/**
* \file
* Action.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_ACTION_H
#define KZU_ACTION_H


#include "kzu_action_common.h"

#include <system/kzs_types.h>
#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations. */
struct KzuTrigger;
struct KzuUIDomain;
struct KzcMemoryManager;


/**
 * \struct KzuAction
 * Trigger action.
 */
struct KzuAction;


/** Get the property manager of an action. */
struct KzuUIDomain* kzuActionGetUIDomain(const struct KzuAction* action);
/** Get the trigger an action is attached to. */
struct KzuTrigger* kzuActionGetTrigger(const struct KzuAction* action);
/** Attach an action. */
kzsError kzuActionAttach(struct KzuAction* action, struct KzuTrigger* trigger);
/** Detach an action. */
kzsError kzuActionDetach(struct KzuAction* action);
/** Invoke an action. */
kzsError kzuActionInvoke(struct KzuAction* action);
/** Copy an action. */
kzsError kzuActionCopy(const struct KzcMemoryManager* memoryManager, const struct KzuAction* sourceAction, struct KzuAction** out_action);
/** Delete an action. */
kzsError kzuActionDelete(struct KzuAction* action);


/** Get the type of an action. */
KzuActionType kzuActionGetType(const struct KzuAction* action);


KZ_HEADER_END


#endif
