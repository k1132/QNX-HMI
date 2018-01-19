/**
 * \file
 * Condition.
 *
 * Copyright 2008-2014 by Rightware. All rights reserved.
 */
#ifndef KZU_CONDITION_H
#define KZU_CONDITION_H


#include <system/kzs_types.h>
#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations. */
struct KzuTrigger;
struct KzuUIDomain;
struct KzcMemoryManager;


/**
 * \struct KzuCondition
 * Trigger condition.
 */
struct KzuCondition;


/** Get the ui domain of a condition. */
struct KzuUIDomain* kzuConditionGetUIDomain(const struct KzuCondition* condition);
/** Get the trigger an condition is attached to. */
struct KzuTrigger* kzuConditionGetTrigger(const struct KzuCondition* condition);

/** Attach a condition. */
kzsError kzuConditionAttach(struct KzuCondition* condition, struct KzuTrigger* trigger);
/** Detach a condition. */
kzsError kzuConditionDetach(struct KzuCondition* condition);
/** Evaluate a condition value. */
kzsError kzuConditionCheck(struct KzuCondition* condition, kzBool* out_conditionValue);
/** Copy a condition. */
kzsError kzuConditionCopy(const struct KzcMemoryManager* memoryManager, const struct KzuCondition* sourceAction, struct KzuCondition** out_condition);
/** Delete a condition. */
kzsError kzuConditionDelete(struct KzuCondition* condition);


KZ_HEADER_END


#endif
