/**
* \file
* Trigger base class.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_TRIGGER_BASE_H
#define KZU_TRIGGER_BASE_H


#include <system/kzs_types.h>
#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations. */
struct KzuObjectNode;
struct KzuTrigger;
struct KzuAction;
struct KzuCondition;
struct KzuPropertyManager;
struct KzcMemoryManager;


/** Trigger class. */
struct KzuTriggerClass
{
    /** Attach function for triggers. */
    kzsError (*kzuTriggerAttach)(struct KzuTrigger* trigger);

    /** Detach function for triggers. */
    kzsError (*kzuTriggerDetach)(struct KzuTrigger* trigger);

    /** Copy function for triggers. */
    kzsError (*kzuTriggerCopy)(const struct KzcMemoryManager* memoryManager, const struct KzuTrigger* sourceTrigger, struct KzuTrigger** out_trigger);

    /** Delete function for triggers. */
    kzsError (*kzuTriggerDelete)(struct KzuTrigger* trigger);
};

/** Trigger. */
struct KzuTrigger
{
    const struct KzuTriggerClass* triggerClass; /**< Class of the trigger. */
    struct KzuUIDomain* uiDomain;               /**< Project reference. */
    struct KzuObjectNode* objectNode;           /**< Object node reference. */
    struct KzcDynamicArray* actions;            /**< List of actions. <KzuAction>. */
    struct KzcDynamicArray* conditions;         /**< List of conditions. <KzuCondition>. */
};


/** Create base trigger. */
kzsError kzuTriggerCreate_protected(struct KzuTrigger* trigger, const struct KzuTriggerClass* triggerClass, struct KzuUIDomain* uiDomain);

/** Default trigger attach implementation. */
kzsError kzuTriggerAttach_protected(struct KzuTrigger* trigger);
/** Default trigger detach implementation. */
kzsError kzuTriggerDetach_protected(struct KzuTrigger* trigger);
/** Default trigger delete implementation. */
kzsError kzuTriggerDelete_protected(struct KzuTrigger* trigger);

/** Class copy function. */
kzsError kzuTriggerClassCopy_protected(struct KzuTrigger* targetTrigger, const struct KzuTrigger* sourceTrigger);

/* Sets UI domain to the trigger and to its actions and con*/


KZ_HEADER_END


#endif
