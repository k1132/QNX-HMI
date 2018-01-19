/**
 * \file
 * Expression condition.
 *
 * Copyright 2008-2014 by Rightware. All rights reserved.
 */
#ifndef KZU_EXPRESSION_CONDITION_H
#define KZU_EXPRESSION_CONDITION_H


#include <user/properties/kzu_property_common.h>

#include <system/kzs_types.h>
#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations. */
struct KzuVariant;
struct KzuPropertyType;
struct KzuCondition;
struct KzcMemoryManager;
struct KzuUIDomain;

/** Expression condition operand position. */
enum KzuExpressionConditionOperand
{
    KZU_EXPRESSION_CONDITION_OPERAND_LHS, /**< Left hand side operand. */
    KZU_EXPRESSION_CONDITION_OPERAND_RHS /**< Right hand side operand. */
};

/** Expression condition operation. */
enum KzuExpressionConditionOperation
{
    KZU_EXPRESSION_CONDITION_OPERATION_INVALID = 0, /**< Invalid comparison. */
    KZU_EXPRESSION_CONDITION_OPERATION_EQUAL = 1, /**< Equality comparison. */
    KZU_EXPRESSION_CONDITION_OPERATION_NOT_EQUAL = 2, /**< Inequality comparison. */
    KZU_EXPRESSION_CONDITION_OPERATION_LESS = 3, /**< Less than comparison. */
    KZU_EXPRESSION_CONDITION_OPERATION_GREATER = 4, /**< Greater than comparison. */
    KZU_EXPRESSION_CONDITION_OPERATION_LESS_OR_EQUAL = 5, /**< Less than or equal comparison. */
    KZU_EXPRESSION_CONDITION_OPERATION_GREATER_OR_EQUAL = 6 /**< Greater than or equal comparison. */
};


/**
 * Creates an expression condition that can be attached to triggers.
 *
 * Expression condition compares two operands with a specified comparison operator. Operand can be either a fixed value, a message argument from the message that the trigger forwards to
 * the condition, or a property value that is read from an object specified by a relative path to the trigger object. Both operands and the operation must be set before the condition
 * can be used.
 */
kzsError kzuExpressionConditionCreate(const struct KzcMemoryManager* memoryManager, struct KzuUIDomain* uiDomain, struct KzuCondition** out_condition);

/** Sets the comparisons operation for the condition. Not all property types support all operations. If the operation is not supported, the condition evaluates to KZ_FALSE. */
void kzuExpressionConditionSetOperation(struct KzuCondition* condition, enum KzuExpressionConditionOperation operation);

/** Sets an operand in the comparison to be read from a fixed value. */
kzsError kzuExpressionConditionSetOperandValue(const struct KzuCondition* condition, enum KzuExpressionConditionOperand operand, const struct KzuVariant* value);

/** Sets an operand in the comparison to be read from the forwarded message from the trigger. */
kzsError kzuExpressionConditionSetOperandMessageArgument(const struct KzuCondition* condition, enum KzuExpressionConditionOperand operand, const struct KzuPropertyType* messageArgument, enum KzuPropertyField argumentField);

/** Sets an operand in the comparison to be read from an objects property. */
kzsError kzuExpressionConditionSetOperandProperty(const struct KzuCondition* condition, enum KzuExpressionConditionOperand operand, kzString objectPath, const struct KzuPropertyType* propertyType, enum KzuPropertyField propertyField);


/** Determine if condition is of ExpressionCondition type. */
kzBool kzuConditionIsExpressionCondition(const struct KzuCondition* condition);

/** Sets UI domain to expression condition. */
void kzuExpressionConditionSetUIDomain(struct KzuCondition* condition, struct KzuUIDomain* uiDomain);


KZ_HEADER_END


#endif
