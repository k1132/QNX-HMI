/**
* \file
* Trigger.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_TRIGGER_H
#define KZU_TRIGGER_H


#include <system/kzs_types.h>
#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations. */
struct KzuObjectNode;
struct KzuAction;
struct KzuCondition;
struct KzuPropertyManager;
struct KzcMemoryManager;


/**
 * \struct KzuTrigger
 * Trigger.
 */
struct KzuTrigger;


/** Attach a trigger to an object node. */
kzsError kzuTriggerAttach(struct KzuTrigger* trigger, struct KzuObjectNode* objectNode);
/** Detach a trigger. */
kzsError kzuTriggerDetach(struct KzuTrigger* trigger);
/** Copy a trigger. */
kzsError kzuTriggerCopy(const struct KzcMemoryManager* memoryManager, const struct KzuTrigger* sourceTrigger, struct KzuTrigger** out_trigger);
/** Delete a trigger. */
kzsError kzuTriggerDelete(struct KzuTrigger* trigger);
/** Get the property manager of a trigger. */
struct KzuUIDomain* kzuTriggerGetUIDomain(const struct KzuTrigger* trigger);
/** Get the object node a trigger is attached to. */
struct KzuObjectNode* kzuTriggerGetObjectNode(const struct KzuTrigger* trigger);
/** Add an action to a trigger. */
kzsError kzuTriggerAddAction(const struct KzuTrigger* trigger, const struct KzuAction* action);
/** Invoke actions in a trigger. */
kzsError kzuTriggerInvokeActions(const struct KzuTrigger* trigger);
/** Add a condition to a trigger. */
kzsError kzuTriggerAddCondition(const struct KzuTrigger* trigger, const struct KzuCondition* condition);
/** Check all conditions in a trigger. */
kzsError kzuTriggerCheckConditions(const struct KzuTrigger* trigger, kzBool* out_conditionsTrue);

/** Get actions of a trigger. */
struct KzcDynamicArrayIterator kzuTriggerGetActions(const struct KzuTrigger* trigger);
/** Get conditions of a trigger. */
struct KzcDynamicArrayIterator kzuTriggerGetConditions(const struct KzuTrigger* trigger);
/** Set UI domain to a trigger. */
void kzuTriggerSetUIDomain(struct KzuTrigger* trigger, struct KzuUIDomain* uiDomain);


KZ_HEADER_END


#endif
