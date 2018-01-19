/**
* \file
* Expression validator.
*
* An expression validator can be used to modify a binding rule value before it is written to the binding rule target.
* See \ref kzu_scroll_layer.h example code for an example.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_EXPRESSION_VALIDATOR_H
#define KZU_EXPRESSION_VALIDATOR_H


#include <user/ui/binding/kzu_binding_validator_base.h>

#include <system/kzs_types.h>
#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations. */
struct KzuBindingValidator;
struct KzuPropertyManager;
struct KzcMemoryManager;


/** Expression argument type. */
enum KzuExpressionValidatorArgumentType
{
    KZU_EXPRESSION_VALIDATOR_ARGUMENT_TYPE_SOURCE = 0,
    KZU_EXPRESSION_VALIDATOR_ARGUMENT_TYPE_TARGET = 1,
    KZU_EXPRESSION_VALIDATOR_ARGUMENT_TYPE_SOURCE_REGISTER_0    = 100,
    KZU_EXPRESSION_VALIDATOR_ARGUMENT_TYPE_CONSTANT_REGISTER_0  = 200,
    KZU_EXPRESSION_VALIDATOR_ARGUMENT_TYPE_TEMPORARY_REGISTER_0 = 300
};

/** Expression operation. */
enum KzuExpressionValidatorOperation
{
    KZU_EXPRESSION_VALIDATOR_OPERATION_WRITE = 0,
    KZU_EXPRESSION_VALIDATOR_OPERATION_ADD = 1,
    KZU_EXPRESSION_VALIDATOR_OPERATION_SUBTRACT = 2,
    KZU_EXPRESSION_VALIDATOR_OPERATION_MULTIPLY = 3,
    KZU_EXPRESSION_VALIDATOR_OPERATION_DIVIDE = 4,
    KZU_EXPRESSION_VALIDATOR_OPERATION_MODULO = 5,
    KZU_EXPRESSION_VALIDATOR_OPERATION_ABS = 6,
    KZU_EXPRESSION_VALIDATOR_OPERATION_MAX = 7,
    KZU_EXPRESSION_VALIDATOR_OPERATION_MIN = 8,
    KZU_EXPRESSION_VALIDATOR_OPERATION_CEIL = 9,
    KZU_EXPRESSION_VALIDATOR_OPERATION_FLOOR = 10,
    KZU_EXPRESSION_VALIDATOR_OPERATION_ROUND = 11,
    KZU_EXPRESSION_VALIDATOR_OPERATION_POW = 12,
    KZU_EXPRESSION_VALIDATOR_OPERATION_SQRT = 13,
    KZU_EXPRESSION_VALIDATOR_OPERATION_STEP = 14,
    KZU_EXPRESSION_VALIDATOR_OPERATION_TO_BOOL = 15,
    KZU_EXPRESSION_VALIDATOR_OPERATION_TO_INT = 16,
    KZU_EXPRESSION_VALIDATOR_OPERATION_TO_FLOAT = 17,
    KZU_EXPRESSION_VALIDATOR_OPERATION_TO_STRING = 18
};


/** Expression validator type. */
extern const KzuBindingValidatorType KZU_BINDING_VALIDATOR_TYPE_EXPRESSION;


/** Create an expression validator. */
kzsError kzuExpressionValidatorCreate(const struct KzcMemoryManager* memoryManager, struct KzuPropertyManager* propertyManager, struct KzuBindingValidator** out_validator);

/** This class copy function. */
kzsError kzuExpressionValidatorCopyClassData_protected(const struct KzuBindingValidator* targetValidator, const struct KzuBindingValidator* sourceValidator);

/** Get expression validator argument. */
const struct KzuVariant* kzuExpressionValidatorGetArgument(const struct KzuBindingRule* rule, enum KzuExpressionValidatorArgumentType argumentType);


KZ_HEADER_END


#endif
