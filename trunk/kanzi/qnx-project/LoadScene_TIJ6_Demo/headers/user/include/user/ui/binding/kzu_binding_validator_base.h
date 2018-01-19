/**
* \file
* Binding validator base class.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_BINDING_VALIDATOR_BASE_H
#define KZU_BINDING_VALIDATOR_BASE_H


#include <system/kzs_types.h>
#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations. */
struct KzuBindingRule;
struct KzuBindingValidator;
struct KzuPropertyManager;
struct KzuVariant;
struct KzcMemoryManager;


/** Binding validator class. */
struct KzuBindingValidatorClass
{
    /** Copy function for binding validators. */
    kzsError (*kzuBindingValidatorCopy)(const struct KzcMemoryManager* memoryManager, const struct KzuBindingValidator* sourceValidator, struct KzuBindingValidator** out_validator);

    /** Delete function for binding validators. */
    kzsError (*kzuBindingValidatorDelete)(struct KzuBindingValidator* validator);

    /** Attach function for binding validators. */
    kzsError (*kzuBindingValidatorAttach)(struct KzuBindingValidator* validator);

    /** Detach function for binding validators. */
    kzsError (*kzuBindingValidatorDetach)(struct KzuBindingValidator* validator);

    /** Validate function for binding validators. */
    kzsError (*kzuBindingValidatorValidate)(struct KzuBindingValidator* validator, struct KzuVariant* sourceValue, kzBool* out_valid);
};

/** Binding validator. */
struct KzuBindingValidator
{
    const struct KzuBindingValidatorClass* validatorClass; /**< Class of the binding validator. */
    struct KzuPropertyManager* propertyManager; /**< Property manager of the binding validator. */
    struct KzuBindingRule* rule; /**< Binding rule. */
};


/** The binding validator type identifier. */
typedef const void* KzuBindingValidatorType;


/** Create base validator. */
kzsError kzuBindingValidatorCreate_protected(struct KzuBindingValidator* validator, const struct KzuBindingValidatorClass* validatorClass, struct KzuPropertyManager* propertyManager);

/** Default validator delete implementation. */
kzsError kzuBindingValidatorDelete_protected(struct KzuBindingValidator* validator);
/** Default validator attach implementation. */
kzsError kzuBindingValidatorAttach_protected(struct KzuBindingValidator* validator);
/** Default validator detach implementation. */
kzsError kzuBindingValidatorDetach_protected(struct KzuBindingValidator* validator);

/** Class copy function. */
kzsError kzuBindingValidatorClassCopy_protected(const struct KzuBindingValidator* targetValidator, const struct KzuBindingValidator* sourceValidator);


KZ_HEADER_END


#endif
