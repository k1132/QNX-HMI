/**
* \file
* Animation validator.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_ANIMATION_VALIDATOR_H
#define KZU_ANIMATION_VALIDATOR_H


#include <user/ui/binding/kzu_binding_validator_base.h>

#include <system/kzs_types.h>
#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations. */
struct KzuBindingValidator;
struct KzuPropertyManager;
struct KzcMemoryManager;
struct KzuAnimationItem;


/** Animation validator type. */
extern const KzuBindingValidatorType KZU_BINDING_VALIDATOR_TYPE_ANIMATION;


/** Creates an animation validator. */
kzsError kzuAnimationValidatorCreate(const struct KzcMemoryManager* memoryManager, struct KzuPropertyManager* propertyManager, struct KzuBindingValidator** out_validator);

/** This class copy function. */
kzsError kzuAnimationValidatorCopyClassData_private(const struct KzuBindingValidator* targetValidator, const struct KzuBindingValidator* sourceValidator);


KZ_HEADER_END


#endif
