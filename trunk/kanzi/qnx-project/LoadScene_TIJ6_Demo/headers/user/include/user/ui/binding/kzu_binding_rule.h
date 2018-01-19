/**
* \file
* Rule describing a data binding in form of read rule and write rule.
*
* KzuBindingRule can be used to create a link between two properties, a variant and a property, or two message arguments of two messages.
* From these, the property to property binding rule is the only one that is updated without a manual ::kzuBindingRuleUpdate() call.
* 
* Example Code
* ----
* The following example code shows how a one-way binding rule can be created between the X-axis translation of two buttons.
* The ::kzuObjectNodeAddBinding() call transfers the ownership of the binding rule to the target object node, so the
* binding rule is destroyed at the same time with the target object node. When the source layer X translation is changed with
* ::kzuLayerSetLayerRenderTransformation(), the target layer's X translation changes to the same value.
* 
* \code{.c}
    kzsError result;
    struct KzuObjectNode* sourceObjectNode;
    struct KzuObjectNode* targetObjectNode;
    struct KzuBindingRule* rule;

    result = kzuButtonLayerCreate(memoryManager, "Source", uiDomain, &sourceLayer);
    kzsErrorForward(result);
    result = kzuButtonLayerCreate(memoryManager, "Target", uiDomain, &targetLayer);
    kzsErrorForward(result);

    sourceObjectNode = kzuLayerToObjectNode(kzuButtonLayerToLayer(sourceLayer));
    targetObjectNode = kzuLayerToObjectNode(kzuButtonLayerToLayer(targetLayer));

    result = kzuObjectNodeAddChild(rootObjectNode, sourceObjectNode);
    kzsErrorForward(result);
    result = kzuObjectNodeAddChild(rootObjectNode, targetObjectNode);
    kzsErrorForward(result);

    result = kzuBindingRuleCreate(memoryManager, uiDomain, &rule);
    kzsErrorForward(result);

    result = kzuBindingRuleSetTargetDynamicObjectProperty(rule, "./",
                 KZU_PROPERTY_TYPE_LAYER_RENDER_TRANSFORMATION, KZU_PROPERTY_FIELD_TRANSLATION_X);
    kzsErrorForward(result);
    result = kzuBindingRuleSetSourceDynamicObjectProperty(rule, "../Source",
                 KZU_PROPERTY_TYPE_LAYER_RENDER_TRANSFORMATION, KZU_PROPERTY_FIELD_TRANSLATION_X);
    kzsErrorForward(result);

    result = kzuObjectNodeAddBinding(targetObjectNode, rule);
    kzsErrorForward(result);

    // This code just demonstrates that the binding works.
    {
        struct KzcMatrix3x3 transformation = kzuLayerGetLayerRenderTransformation(
                                                    kzuButtonLayerToLayer(sourceLayer));
        struct KzcMatrix3x3 targetTransformation;

        transformation.data[KZC_MATRIX3X3_INDEX_TRANSLATION_X] += 10.0f;
        result = kzuLayerSetLayerRenderTransformation(kzuButtonLayerToLayer(sourceLayer), &transformation);
        kzsErrorForward(result);

        targetTransformation = kzuLayerGetLayerRenderTransformation(kzuButtonLayerToLayer(targetLayer));
        kzsAssert(targetTransformation.data[KZC_MATRIX3X3_INDEX_TRANSLATION_X] ==
                  transformation.data[KZC_MATRIX3X3_INDEX_TRANSLATION_X]);
    }
* \endcode
*
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_BINDING_RULE_H
#define KZU_BINDING_RULE_H


#include <user/animation/kzu_animation_util.h>
#include <user/ui/kzu_variant.h>

#include <core/util/collection/kzc_dynamic_array.h>

#include <system/kzs_types.h>
#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations. */
struct KzuMessage;
struct KzuObjectNode;
struct KzuPropertyManager;
struct KzuUIDomain;
struct KzuBindingValidator;


/**
 * \struct KzuBindingRule
 * Binding rule object.
 */
struct KzuBindingRule;


/** Binding mode enumeration. */
enum KzuBindingMode
{
    KZU_BINDING_MODE_ONE_WAY = 1,       /**< One way binding. */
    KZU_BINDING_MODE_TWO_WAY = 2        /**< Two way binding. */
};


/** Create a binding rule object. */
kzsError kzuBindingRuleCreate(const struct KzcMemoryManager* memoryManager, struct KzuUIDomain* uiDomain, struct KzuBindingRule** out_rule);
/** Helper to create a property-to-property binding rule object.
 * \param memoryManager The memory manager to use for allocations.
 * \param uiDomain The UI domain.
 * \param sourcePath An object path pointing to the source object that has the source property. This can be relative to the target property owner.
 * \param sourcePropertyType ::KzuPropertyType of the source property.
 * \param sourceField Field of the source property to bind or ::KZU_PROPERTY_FIELD_WHOLE for the whole property.
 * \param targetPropertyType ::KzuPropertyType of the target property.
 * \param targetField Field of the target property to bind or ::KZU_PROPERTY_FIELD_WHOLE for the whole property.
 * \param out_rule A pointer that is set to point to the new KzuBindingRule.
 * \return ::KZS_SUCCESS on success.
 */
kzsError kzuBindingRuleCreateForProperty(const struct KzcMemoryManager* memoryManager, struct KzuUIDomain* uiDomain,
                                         kzString sourcePath, const struct KzuPropertyType* sourcePropertyType, enum KzuPropertyField sourceField,
                                         const struct KzuPropertyType* targetPropertyType, enum KzuPropertyField targetField,
                                         struct KzuBindingRule** out_rule);
/** Copy a binding rule. */
kzsError kzuBindingRuleCopy(const struct KzcMemoryManager* memoryManager, const struct KzuBindingRule* sourceRule, struct KzuBindingRule** out_rule);
/** Delete a binding rule object. */
kzsError kzuBindingRuleDelete(struct KzuBindingRule* rule);

/** Set binding mode. */
void kzuBindingRuleSetMode(struct KzuBindingRule* rule, enum KzuBindingMode mode);
/** Get binding mode. */
enum KzuBindingMode kzuBindingRuleGetMode(const struct KzuBindingRule* rule);

/** Set up source rule to specify a value. */
kzsError kzuBindingRuleSetSourceValue(struct KzuBindingRule* rule, const struct KzuVariant* value);
/** Set up source rule to specify an object property.
 * \param rule The binding rule which source property is specified.
 * \param objectPath Object path leading to the source object node, relative to the target object node.
 * \param propertyType The property type in the source object node.
 * \param field Field to bind in the property or ::KZU_PROPERTY_FIELD_WHOLE for the whole property.
 * \return ::KZS_SUCCESS on success.
 */
kzsError kzuBindingRuleSetSourceDynamicObjectProperty(struct KzuBindingRule* rule, kzString objectPath, const struct KzuPropertyType* propertyType, enum KzuPropertyField field);
/** Adds or a source property as the source rule. It is possible to add multiple sources with this function. */
kzsError kzuBindingRuleAddSourceDynamicObjectProperty(struct KzuBindingRule* rule, kzString objectPath, const struct KzuPropertyType* propertyType, enum KzuPropertyField field);
/** Set up source rule to specify a message argument. */
kzsError kzuBindingRuleSetSourceMessageArgument(struct KzuBindingRule* rule, const struct KzuPropertyType* argumentType, enum KzuPropertyField field);
/** Set a zero source binding. */
kzsError kzuBindingRuleSetZeroSource(struct KzuBindingRule* rule);


/** Set up target rule to specify an object property.
 * \param rule The binding rule which target property is specified.
 * \param objectPath Object path leading to the target object node, relative to the target object node.
 * \param propertyType The property type in the target object node.
 * \param field Field to bind in the property or ::KZU_PROPERTY_FIELD_WHOLE for the whole property.
 * \return ::KZS_SUCCESS on success.
 */
kzsError kzuBindingRuleSetTargetDynamicObjectProperty(struct KzuBindingRule* rule, kzString objectPath, const struct KzuPropertyType* propertyType, enum KzuPropertyField field);
/** Set up target rule to specify a message argument. */
kzsError kzuBindingRuleSetTargetMessageArgument(struct KzuBindingRule* rule, const struct KzuPropertyType* argumentType, enum KzuPropertyField field);

/** Read values from sourceMessage and store them in rule's internal cache. */
kzsError kzuBindingRuleRead(const struct KzuBindingRule* rule, struct KzuObjectNode* currentObjectNode, const struct KzuMessage* sourceMessage, kzBool* out_read);
/** Save the cached value from the rule to targetMessage if it has one cached. */
kzsError kzuBindingRuleWrite(const struct KzuBindingRule* rule, struct KzuObjectNode* currentObjectNode, const struct KzuMessage* targetMessage, kzBool* out_written);
/** Read values from sourceMessage and write them to targetMessage if the binding rule type is a message argument
 * to message argument. Otherwise updates the binding depending on its type (e.g. property to property, variant to property).
 * \param rule The binding rule to update.
 * \param currentObjectNode The object node for which the binding rule object paths are relative to.
 * \param sourceMessage The source message or ::KZ_NULL.
 * \param targetMessage The target message or ::KZ_NULL.
 * \param out_updated A pointer to a Boolean that is set to ::KZ_TRUE if the rule was updated, otherwise it is set to ::KZ_FALSE.
 * \return ::KZS_SUCCESS on success. ::KZS_ERROR_ENUM_OUT_OF_RANGE if the binding source type is invalid.
 */
kzsError kzuBindingRuleUpdate(struct KzuBindingRule* rule, struct KzuObjectNode* currentObjectNode, const struct KzuMessage* sourceMessage, const struct KzuMessage* targetMessage, kzBool* out_updated);
/** Update the source value in binding. */
kzsError kzuBindingRuleUpdateSource(struct KzuBindingRule* rule, struct KzuObjectNode* currentObjectNode, const struct KzuMessage* sourceMessage, const struct KzuMessage* targetMessage, kzBool* out_updated);
/** Read the target value. */
kzsError kzuBindingRuleReadTargetValue(const struct KzuBindingRule* rule, struct KzuVariant* value, kzBool* out_read);
/** Returns the source value from rule's internal cache. This is an internal Kanzi function. */
const struct KzuVariant* kzuBindingRuleGetCachedSourceValue(const struct KzuBindingRule* rule);

/** Add a validator object. */
kzsError kzuBindingRuleAddValidator(const struct KzuBindingRule* rule, const struct KzuBindingValidator* validator);
/** Remove a validator object. */
kzsError kzuBindingRuleRemoveValidator(const struct KzuBindingRule* rule, const struct KzuBindingValidator* validator);
/** Get the validator iterator. */
struct KzcDynamicArrayIterator kzuBindingRuleGetValidators(const struct KzuBindingRule* rule);

/** Gets the number of source registers in binding rule. */
kzUint kzuBindingRuleGetSourceRegisterCount(const struct KzuBindingRule* rule);
/** Gets the number of constant registers in binding rule. */
kzUint kzuBindingRuleGetConstantRegisterCount(const struct KzuBindingRule* rule);
/** Gets the number of temporary registers in binding rule. */
kzUint kzuBindingRuleGetTemporaryRegisterCount(const struct KzuBindingRule* rule);

/** Attach binding. This is Kanzi-internal function, use ::kzuObjectNodeAddBinding() instead. */
kzsError kzuBindingRuleAttach(struct KzuBindingRule* rule, struct KzuObjectNode* objectNode);
/** Detach binding. This is Kanzi-internal function, use ::kzuObjectNodeRemoveBinding() instead. */
kzsError kzuBindingRuleDetach(struct KzuBindingRule* rule);
/** Get the object node the rule is attached to, if any. */
struct KzuObjectNode* kzuBindingRuleGetAttachedNode(const struct KzuBindingRule* rule);

/** Converts a property attribute to a field. */
enum KzuPropertyField kzuBindingFieldFromBinaryAttribute(enum KzuPropertyBinaryTargetAttribute attribute);

/** Resolve an object node from a binding rule object node. */
kzsError kzuBindingRuleResolveObjectNode_private(kzString path, struct KzuObjectNode* currentObjectNode, struct KzuObjectNode** out_objectNode);

/** Add a constant value to the binding. */
kzsError kzuBindingRuleAddConstantRegister(const struct KzuBindingRule* rule, const struct KzuVariant* constant);
/** Set the number of temporaries for the binding. */
kzsError kzuBindingRuleSetTemporaryRegisterCount(const struct KzuBindingRule* rule, kzUint count);

/** Get access to source register. */
const struct KzuVariant* kzuBindingRuleGetSourceRegister(const struct KzuBindingRule* rule, kzUint index);
/** Get access to constant register. */
const struct KzuVariant* kzuBindingRuleGetConstantRegister(const struct KzuBindingRule* rule, kzUint index);
/** Get access to temporary register. */
struct KzuVariant* kzuBindingRuleGetTemporaryRegister(const struct KzuBindingRule* rule, kzUint index);


/** Sets UI domain to binding rule. */
void kzuBindingRuleSetUIDomain(struct KzuBindingRule* bindingRule, struct KzuUIDomain* uiDomain);

/** Returns target property type and property field of the binding rule if it is writing to property. */
kzBool kzuBindingRuleGetTargetPropertyType(const struct KzuBindingRule* bindingRule, const struct KzuPropertyType** out_targetPropertyType,
                                           enum KzuPropertyField* out_field);


KZ_HEADER_END


#endif
