/**
* \file
* Property manager.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_PROPERTY_MANAGER_COLOR_H
#define KZU_PROPERTY_MANAGER_COLOR_H


#include <core/util/color/kzc_color.h>

#include <system/kzs_types.h>
#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations */
struct KzuObjectNode;
struct KzuPropertyManager;
struct KzuPropertyType;


/** Color value source. */
struct KzuPropertyColorValueSource;


/** Create a Color value source. */
kzsError kzuPropertyColorValueSourceCreate(const struct KzuPropertyManager* propertyManager, struct KzcColorRGBA value, struct KzuPropertyColorValueSource** out_valueSource);
/** Delete a Color value source. */
kzsError kzuPropertyColorValueSourceDelete(struct KzuPropertyColorValueSource* valueSource);
/** Copy a color value source. */
kzsError kzuPropertyColorValueSourceClone(const struct KzuPropertyManager* propertyManager, const struct KzuPropertyColorValueSource* valueSource, struct KzuPropertyColorValueSource** out_newValueSource);
/** Copy a color value source. */
kzsError kzuPropertyColorValueSourceCopy(struct KzuPropertyColorValueSource* target, const struct KzuPropertyColorValueSource* source);

/** Set a color value source. */
kzsError kzuPropertyColorValueSourceSetValue(struct KzuPropertyColorValueSource* valueSource, struct KzcColorRGBA value);
/** Gets a color value source value. */
struct KzcColorRGBA kzuPropertyColorValueSourceGetValue(const struct KzuPropertyColorValueSource* valueSource);

/** Set a property of propertyType associated with an object. */
kzsError kzuPropertyManagerSetColor(const struct KzuPropertyManager* propertyManager, const void* object, const struct KzuPropertyType* propertyType, struct KzcColorRGBA value);

/**
 * Get the value of a property of propertyType associated with an object. Returns KZ_TRUE if the property is found and KZ_FALSE otherwise.
 * The return value is calculated based on the following steps:
 * 1. If an animation is applied to the property, the animated value is returned. It is calculated from the base and relative values of the property.
 * 2. The value associated with the object is returned.
 * 3. If the property is not associated with the object, the property groups associated with the object are queried:
 *  3.1 Property groups associated with the object are queried in the reverse order than they were added.
 * 4. If the property can not be deduced, the output value is not modified and KZ_FALSE is returned.
 */
kzBool kzuPropertyManagerGetColor(const struct KzuPropertyManager* propertyManager, const void* object, const struct KzuPropertyType* propertyType, struct KzcColorRGBA* out_value);
/**
 * Get the base value of a property of propertyType associated with an object. Returns KZ_TRUE if the property is found and KZ_FALSE otherwise.
 */
kzBool kzuPropertyManagerGetBaseColor(const struct KzuPropertyManager* propertyManager, const void* object, const struct KzuPropertyType* propertyType, struct KzcColorRGBA* out_value);
/**
  * Get a property of propertyType associated with an object and return the default value from the property type if not found.
  * If the property value can be deduced with kzuPropertyManagerGetColor then that value is returned.
  * If the property can not be deduced, the default value from the property type is returned.
  */
struct KzcColorRGBA kzuPropertyManagerGetColorDefault(const struct KzuPropertyManager* propertyManager, const void* object, const struct KzuPropertyType* propertyType);


/** Set a property on an object node.  */
kzsError kzuObjectNodeSetColorProperty(const struct KzuObjectNode* objectNode, const struct KzuPropertyType* propertyType, struct KzcColorRGBA value);

/**
 * Get the value of a property of propertyType associated with an object node. Returns KZ_TRUE if the property is found and KZ_FALSE otherwise.
 * The return value is calculated based on the following steps:
 * 1. kzuPropertyManagerGetColor is used for getting the property value.
 * 2. If the property value can not be deduced from the object node, the same query is performed for the parent of the current object node.
 * 3. If the property is not found until the root is reached, the output value is not modified and KZ_FALSE is returned.
 */
kzBool kzuObjectNodeGetColorProperty(const struct KzuObjectNode* objectNode, const struct KzuPropertyType* propertyType, struct KzcColorRGBA* out_value);

/**
 * Get the base value of a property of propertyType associated with an object node.
 * Behaves like kzuObjectNodeGetColorProperty but does not take animation into account.
 */
kzBool kzuObjectNodeGetBaseColorProperty(const struct KzuObjectNode* objectNode, const struct KzuPropertyType* propertyType, struct KzcColorRGBA* out_value);

/**
 * Get the value of a property associated with an object node.
 * Behaves like kzuObjectNodeGetColorProperty, but if the property value can not be deduced, the default value from the property type is returned.
 */
struct KzcColorRGBA kzuObjectNodeGetColorPropertyDefault(const struct KzuObjectNode* objectNode, const struct KzuPropertyType* propertyType);


KZ_HEADER_END


#endif
