/**
* \file
* Callback validator. Validation happens in a user-provided callback.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_CALLBACK_VALIDATOR_H
#define KZU_CALLBACK_VALIDATOR_H


#include <user/ui/kzu_variant.h>

#include <system/kzs_types.h>
#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/** Type of the user-provided callback. */
typedef kzsError (*KzuCallbackValidatorCallback)(void* userData, struct KzuVariant* value, kzBool* out_valid);


/* Forward declarations. */
struct KzuPropertyManager;
struct KzcMemoryManager;


/** Create a callback validator. */
kzsError kzuCallbackValidatorCreate(const struct KzcMemoryManager* memoryManager, struct KzuPropertyManager* propertyManager,
                                    KzuCallbackValidatorCallback callback, void* callbackUserData,
                                    struct KzuBindingValidator** out_validator);


KZ_HEADER_END


#endif
