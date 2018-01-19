/**
 * \file
 * Condition base class.
 *
 * Copyright 2008-2014 by Rightware. All rights reserved.
 */
#ifndef KZU_CONDITION_BASE_H
#define KZU_CONDITION_BASE_H


#include <system/kzs_types.h>
#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations. */
struct KzuTrigger;
struct KzuCondition;
struct KzuPropertyManager;
struct KzuUIDomain;
struct KzcMemoryManager;


/** Condition class. */
struct KzuConditionClass
{
    kzsError (*kzuConditionAttach)(struct KzuCondition* condition); /**< Attach function for condition. */
    kzsError (*kzuConditionDetach)(struct KzuCondition* condition); /**< Detach function for condition. */
    kzsError (*kzuConditionCheck)(struct KzuCondition* condition, kzBool* out_conditionValue); /**< Check function for condition. */
    kzsError (*kzuConditionCopy)(const struct KzcMemoryManager* memoryManager, const struct KzuCondition* sourceCondition, struct KzuCondition** out_condition); /**< Copy function for condition. */
    kzsError (*kzuConditionDelete)(struct KzuCondition* condition); /**< Delete function for condition. */
};

/** Condition. */
struct KzuCondition
{
    const struct KzuConditionClass* conditionClass; /**< Class of the condition. */
    struct KzuUIDomain* uiDomain; /**< UI Domain of the condition. */
    struct KzuTrigger* trigger; /**< Trigger the condition is attached to. */
};


/** Create base action. */
kzsError kzuConditionCreate_protected(struct KzuCondition* condition, const struct KzuConditionClass* conditionClass, struct KzuUIDomain* uiDomain);

/** Base attach implementation. */
kzsError kzuConditionAttach_protected(struct KzuCondition* condition);
/** Base detach implementation. */
kzsError kzuConditionDetach_protected(struct KzuCondition* condition);
/** Base invoke implementation. */
kzsError kzuConditionInvoke_protected(struct KzuCondition* condition);
/** Base delete implementation. */
kzsError kzuConditionDelete_protected(struct KzuCondition* condition);

/** Class copy function. */
kzsError kzuConditionClassCopy_protected(struct KzuCondition* targetCondition, const struct KzuCondition* sourceCondition);

/** Set ui domain to condition. */
void kzuConditionSetUIDomain_protected(struct KzuCondition* condition, struct KzuUIDomain* uiDomain);


KZ_HEADER_END


#endif
