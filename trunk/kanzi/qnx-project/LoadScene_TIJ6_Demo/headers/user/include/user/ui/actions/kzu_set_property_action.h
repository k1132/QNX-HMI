/**
* \file
* Set property action.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_SET_PROPERTY_ACTION_H
#define KZU_SET_PROPERTY_ACTION_H


#include "kzu_action_common.h"

#include <user/properties/kzu_property_base.h>

#include <system/kzs_types.h>
#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations. */
struct KzuVariant;
struct KzuPropertyType;
struct KzuAction;
struct KzuUIDomain;
struct KzuPropertyManager;
struct KzcMemoryManager;


/** Action type identifier for set property action. */
extern const KzuActionType KZU_ACTION_TYPE_SET_PROPERTY_ACTION;


/** Create a set property action. */
kzsError kzuSetPropertyActionCreate(const struct KzcMemoryManager* memoryManager, struct KzuUIDomain* uiDomain, struct KzuAction** out_action);
/** Set a value as source. */
kzsError kzuSetPropertyActionSetSourceValue(const struct KzuAction* action, const struct KzuVariant* sourceValue);
/** Set a message argument as patch message action. */
kzsError kzuSetPropertyActionSetSourceArgument(const struct KzuAction* action, const struct KzuPropertyType* sourceArgument, enum KzuPropertyField sourceField);
/** Set an object node property as source. */
kzsError kzuSetPropertyActionSetSourceProperty(const struct KzuAction* action, kzString sourceObjectPath,
                                               const struct KzuPropertyType* sourcePropertyType, enum KzuPropertyField sourceField);
/** Set target. */
kzsError kzuSetPropertyActionSetTarget(const struct KzuAction* action, kzString targetObjectPath,
                                       const struct KzuPropertyType* targetPropertyType, enum KzuPropertyField targetField);


/** Set ui domain to set property action. */
void kzuSetPropertyActionSetUIDomain(struct KzuAction* action, struct KzuUIDomain* uiDomain);


KZ_HEADER_END


#endif
