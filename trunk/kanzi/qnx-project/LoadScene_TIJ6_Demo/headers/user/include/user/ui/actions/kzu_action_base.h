/**
* \file
* Action base class.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_ACTION_BASE_H
#define KZU_ACTION_BASE_H


#include <system/kzs_types.h>
#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations. */
struct KzuTrigger;
struct KzuAction;
struct KzuPropertyManager;
struct KzcMemoryManager;


/** Action class. */
struct KzuActionClass
{
    kzsError (*kzuActionAttach)(struct KzuAction* action); /**< Attach function for action. */
    kzsError (*kzuActionDetach)(struct KzuAction* action); /**< Detach function for action. */
    kzsError (*kzuActionInvoke)(struct KzuAction* action); /**< Invoke function for action. */
    kzsError (*kzuActionCopy)(const struct KzcMemoryManager* memoryManager, const struct KzuAction* sourceAction, struct KzuAction** out_action); /**< Copy function for action. */
    kzsError (*kzuActionDelete)(struct KzuAction* action); /**< Delete function for action. */
    kzsError (*kzuActionPrepareDelayedInvoke)(struct KzuAction* action); /**< Prepare action for delayed invoke. */
    kzsError (*kzuActionDelayedInvoke)(struct KzuAction* action); /**< Invoke delayed action. */
    kzsError (*kzuActionUnprepareDelayedInvoke)(struct KzuAction* action); /**< Clean up after delayed action. */
};

/** Action. */
struct KzuAction
{
    const struct KzuActionClass* actionClass; /**< Class of the action. */
    struct KzuUIDomain* uiDomain; /**< UIDomain of the action. */
    struct KzuTrigger* trigger; /**< Trigger an action is attached to. */
    kzBool isInvokingDelayed; /**< Is a delayed action being invoked. */
};


/** Create base action. */
kzsError kzuActionCreate_protected(struct KzuAction* action, const struct KzuActionClass* actionClass, struct KzuUIDomain* uiDomain);

/** Base attach implementation. */
kzsError kzuActionAttach_protected(struct KzuAction* action);
/** Base detach implementation. */
kzsError kzuActionDetach_protected(struct KzuAction* action);
/** Base invoke implementation. */
kzsError kzuActionInvoke_protected(struct KzuAction* action);
/** Base delete implementation. */
kzsError kzuActionDelete_protected(struct KzuAction* action);
/** Base prepare delayed invoke implementation. */
kzsError kzuActionPrepareDelayedInvoke_protected(struct KzuAction* action);
/** Base delete implementation. */
kzsError kzuActionDelayedInvoke_protected(struct KzuAction* action);
/** Base unprepare delayed invoke implementation. */
kzsError kzuActionUnprepareDelayedInvoke_protected(struct KzuAction* action);

/** Class copy function. */
kzsError kzuActionClassCopy_protected(struct KzuAction* targetAction, const struct KzuAction* sourceAction);


/** Gets the delay of the action in milliseconds. */
kzUint kzuActionGetDelayTime_protected(const struct KzuAction* action);


/** Sets ui domain to action. */
void kzuActionSetUIDomain_protected(struct KzuAction* action, struct KzuUIDomain* uiDomain);


KZ_HEADER_END


#endif
