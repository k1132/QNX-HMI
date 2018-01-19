/**
* \file
* Binding validator interface.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_BINDING_VALIDATOR_H
#define KZU_BINDING_VALIDATOR_H


#include <user/ui/binding/kzu_binding_validator_base.h>

#include <system/kzs_types.h>
#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations. */
struct KzuBindingRule;
struct KzuPropertyManager;
struct KzuVariant;
struct KzcMemoryManager;


/**
 * \struct KzuBindingValidator
 * Binding validator.
 */
struct KzuBindingValidator;


/** Copy a validator. */
kzsError kzuBindingValidatorCopy(const struct KzcMemoryManager* memoryManager, const struct KzuBindingValidator* sourceValidator, struct KzuBindingValidator** out_validator);
/** Delete a validator. */
kzsError kzuBindingValidatorDelete(struct KzuBindingValidator* validator);
/** Attach a validator to an object node. */
kzsError kzuBindingValidatorAttach(struct KzuBindingValidator* validator, struct KzuBindingRule* rule);
/** Detach a validator. */
kzsError kzuBindingValidatorDetach(struct KzuBindingValidator* validator);

/**
* Reattach a binding validator to the rule it already was in.
* This must be done if the binding validator properties were changed. The properties are cached upon attach.
*/
kzsError kzuBindingValidatorReattach(struct KzuBindingValidator* validator);

/** Get the property manager of a validator. */
struct KzuPropertyManager* kzuBindingValidatorGetPropertyManager(const struct KzuBindingValidator* validator);

/** Validates the source value. */
kzsError kzuBindingValidatorValidate(struct KzuBindingValidator* validator, struct KzuVariant* sourceValue, kzBool* out_valid);

/** Gets the type of binding validator. */
KzuBindingValidatorType kzuBindingValidatorGetType(const struct KzuBindingValidator* bindingValidator);


KZ_HEADER_END


#endif
