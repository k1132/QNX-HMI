/**
* \file
* Property manager.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_PROPERTY_MANAGER_H
#define KZU_PROPERTY_MANAGER_H


#include <user/resource/kzu_localization_manager_base.h>
#include <user/properties/kzu_property_common.h>

#include <system/kzs_types.h>
#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations */
struct KzcDynamicArray;
struct KzcHashMap;
struct KzcHashSet;
struct KzcMemoryManager;
struct KzuObjectNode;
struct KzuPropertyType;
struct KzuLocalizationManager;
struct KzuResourceManager;


/** Property notification reason. */
enum KzuPropertyNotificationReason
{
    KZU_PROPERTY_NOTIFICATION_REASON_CHANGED,
    KZU_PROPERTY_NOTIFICATION_REASON_REMOVED
};

/** Property value precedence. */
enum KzuPropertyValuePrecedence
{
    KZU_PROPERTY_VALUE_PRECEDENCE_CLASS,  /**< Lowest precedence. */
    KZU_PROPERTY_VALUE_PRECEDENCE_STYLE,
    KZU_PROPERTY_VALUE_PRECEDENCE_STATE_MANAGER,
    KZU_PROPERTY_VALUE_PRECEDENCE_LOCAL  /**< Highest precedence. */
};

/** Property manager object. */
struct KzuPropertyManager;


/**
 * \struct KzuPropertyGroup
 * Property groups can be associated to any object. They contain properties just like any other objects and when a property
 * value is queried for an object, all the associated property groups are considered as well.
 */
struct KzuPropertyGroup;


/** Flag to indicate that the property will not be copied when copying properties. */
#define KZU_PROPERTY_MANAGER_FLAG_NON_COPYABLE 2
/** Flag to indicate that the property has been removed from a prefab template node. */
#define KZU_PROPERTY_MANAGER_FLAG_REMOVED 4
/** Flag to indicate that the property has been changed in a prefab template node. */
#define KZU_PROPERTY_MANAGER_FLAG_CHANGED 8


/** Property notification handler function definition.
* \param object The object having the property.
* \param propertyType The property that changed.
* \param reason Type of the change.
* \param userData The user data pointer passed to ::kzuPropertyManagerAddNotificationHandler when the handler was added.
*/
typedef kzsError (*KzuPropertyNotificationHandler)(const void* object, const struct KzuPropertyType* propertyType, enum KzuPropertyNotificationReason reason, void* userData);
/** Property modifier callback function.
* \param object The object having the property.
* \param propertyType The property that changed.
* \param valueSource Value source out-parameter that can be modified to affect the final property value.
* \param reason Type of the change.
* \param userData The user data pointer passed to ::kzuPropertyManagerAddValueModifier when the modifier was added.
* \return The function should return KZS_SUCCESS during normal operation. If the return value is not KZS_SUCCESS, the rest of the modifier callbacks are not called
*         and the modifier is not validated (i.e. if ::kzuPropertyManagerInvalidateValueModifier was called earlier, the invalidation is still in effect).
*/
typedef kzsError (*KzuPropertyModifierCallback)(const void* object, const struct KzuPropertyType* propertyType, void* valueSource,
                                                enum KzuPropertyNotificationReason reason, void* userData);


/** Create a property manager. */
kzsError kzuPropertyManagerCreate(const struct KzcMemoryManager* memoryManager, struct KzuPropertyManager** out_propertyManager);
/** Delete a property manager. */
kzsError kzuPropertyManagerDelete(struct KzuPropertyManager* propertyManager);
/** Removes properties from property manager. */
kzsError kzuPropertyManagerRemoveProperties(const struct KzuPropertyManager* propertyManager);


/** Remove the local value (i.e. precendence ::KZU_PROPERTY_VALUE_PRECEDENCE_LOCAL) of propertyType associated with an object. */
kzsError kzuPropertyManagerRemoveLocalValue(const struct KzuPropertyManager* propertyManager, const void* object, const struct KzuPropertyType* propertyType);

/** Unlink all property entries associated with an object. Should be called from the destructor of an object that uses property manager to store properties.*/
kzsError kzuPropertyManagerUnlinkProperties(const struct KzuPropertyManager* propertyManager, const void* object);

/** Remove all properties associated with an object that are originated from .KZB data. */
kzsError kzuPropertyManagerRemoveKZBProperties(const struct KzuPropertyManager* propertyManager, const void* object);

/**
 * Get all property types associated with an object. 
 * \param out_propertyTypes Dynamic array containing property types associated with object. The caller is responsible for deleting this array after use.
 */
kzsError kzuPropertyManagerGetPropertyTypes(const struct KzuPropertyManager* propertyManager, const struct KzcMemoryManager* memoryManager, const void* object,
                                            struct KzcDynamicArray** out_propertyTypes);

/**
 * Get all property types associated with an object. Unlike kzuPropertyManagerGetPropertyTypes,
 * this function also returns property types for which the given object has a container but not necessarily any values.
 * \param out_propertyTypes Dynamic array containing property types associated with object. The caller is responsible for deleting this array after use.
 */
kzsError kzuPropertyManagerGetAllPropertyTypes(const struct KzuPropertyManager* propertyManager, const struct KzcMemoryManager* memoryManager, const void* object,
                                               struct KzcDynamicArray** out_propertyTypes);

/** Check if any value of propertyType is associated with an object. */
kzBool kzuPropertyManagerHasValue(const struct KzuPropertyManager* propertyManager, const void* object, const struct KzuPropertyType* propertyType);
/** Check if a local value (i.e. precendence ::KZU_PROPERTY_VALUE_PRECEDENCE_LOCAL) of propertyType is associated with an object. */
kzBool kzuPropertyManagerHasLocalValue(const struct KzuPropertyManager* propertyManager, const void* object, const struct KzuPropertyType* propertyType);


/**
 * Compare the property value of two objects.
 * If properties are equal or not associated with either of the objects, KZ_TRUE is returned.
 * Otherwise KZ_FALSE is returned.
 */
kzBool kzuPropertyManagerIsPropertyEqual(const struct KzuPropertyManager* propertyManager, const void* object1, const void* object2, const struct KzuPropertyType* propertyType);

/** Copy a property of given type from source object to target object. */
kzsError kzuPropertyManagerCopyProperty(const struct KzuPropertyManager* propertyManager, const void* sourceObject, const void* targetObject, const struct KzuPropertyType* propertyType);
/** Copy all properties from source object to target object. */
kzsError kzuPropertyManagerCopyProperties(const struct KzuPropertyManager* propertyManager, const void* sourceObject, const void* targetObject);

/** Copies all properties of object from source property manager to target property manager. */
kzsError kzuPropertyManagerCopyObjectToTargetManager(const struct KzcMemoryManager* memoryManager, const struct KzuPropertyManager* sourcePropertyManager,
                                                     const void* object, const struct KzuPropertyManager* targetPropertyManager);
/** Resolves properties with a resource URL value by acquiring the resources. This must be called in the main thread for objects which have unresolved pointer properties due to .KZB loading. */
kzsError kzuPropertyManagerResolveResourceURLs(const struct KzuPropertyManager* propertyManager, const void* object,
                                               struct KzuResourceManager* resourceManager);

/**
 * Copies all properties to target property manager. 
 * If there is property with the same name and with different type in target property manager, the function will return an error.
 */
kzsError kzuPropertyManagerCopyToTargetManager(const struct KzuPropertyManager* propertyManager, const struct KzuPropertyManager* targetPropertyManager);

/** Set a flag for a property. Throws error if the property is not found. */
kzsError kzuPropertyManagerSetPropertyFlag(const struct KzuPropertyManager* propertyManager, const void* object, const struct KzuPropertyType* propertyType, kzU32 flag);
/** Clears a flag for a property. Throws error if the property is not found. */
kzsError kzuPropertyManagerClearPropertyFlag(const struct KzuPropertyManager* propertyManager, const void* object, const struct KzuPropertyType* propertyType, kzU32 flag);
/** Checks if a flag is set for a property. Returns KZ_TRUE if the property is found and KZ_FALSE otherwise. */
kzBool kzuPropertyManagerIsPropertyFlagSet(const struct KzuPropertyManager* propertyManager, const void* object, const struct KzuPropertyType* propertyType, kzU32 flag, kzBool* out_isSet);
/** Checks if a flag is set for a property. Returns KZ_TRUE if the property is found and the flag is set for the property, KZ_FALSE otherwise. */
kzBool kzuPropertyManagerIsPropertyFlagSetDefault(const struct KzuPropertyManager* propertyManager, const void* object, const struct KzuPropertyType* propertyType, kzU32 flag);


/**
 * Register a property type in the property manager. After a property type is registered to the manager,
 * it is possible to find it by its name.
 */
kzsError kzuPropertyManagerRegisterPropertyType(const struct KzuPropertyManager* propertyManager, const struct KzuPropertyType* propertyType);
/**
 * Unregister a property type from the property manager. It is the responsibility of the caller to ensure,
 * that all properties with specified type have been removed prior to the call.
 */
kzsError kzuPropertyManagerUnregisterPropertyType(const struct KzuPropertyManager* propertyManager, const struct KzuPropertyType* propertyType);

/** Finds a property type by name from the property manager. Returns KZ_NULL if the type is not found. */
const struct KzuPropertyType* kzuPropertyManagerFindPropertyType(const struct KzuPropertyManager* propertyManager, kzString propertyTypeName);


/** Associate a property group with a given object. */
kzsError kzuPropertyManagerAddPropertyGroup(const struct KzuPropertyManager* propertyManager, const void* object, const struct KzuPropertyGroup* propertyGroup);

/** Unassociate a property group from a given object. */
kzsError kzuPropertyManagerRemovePropertyGroup(const struct KzuPropertyManager* propertyManager, const void* object, const struct KzuPropertyGroup* propertyGroup);

/** Unassociate all property groups from a given object. */
kzsError kzuPropertyManagerRemovePropertyGroups(const struct KzuPropertyManager* propertyManager, const void* object);

/** Check if a property group is associated with an object. */
kzBool kzuPropertyManagerHasPropertyGroup(const struct KzuPropertyManager* propertyManager, const void* object, const struct KzuPropertyGroup* propertyGroup);

/** Get all property groups associated with an object. */
kzsError kzuPropertyManagerGetPropertyGroups(const struct KzuPropertyManager* propertyManager, const struct KzcMemoryManager* memoryManager, const void* object,
                                             struct KzcDynamicArray** out_propertyGroups);

/** Get all objects associated with the property group. */
kzsError kzuPropertyManagerGetObjectsByPropertyGroup(const struct KzuPropertyManager* propertyManager, const struct KzcMemoryManager* memoryManager,
                                                     const struct KzuPropertyGroup* propertyGroup, struct KzcDynamicArray** out_objects);

/** Copy all property group associations from source object to target object. */
kzsError kzuPropertyManagerCopyPropertyGroups(const struct KzuPropertyManager* propertyManager, const void* sourceObject, const void* targetOject);

/** Copy all property associations from source group to target group. */
kzsError kzuPropertyManagerCopyPropertyGroupContent(const struct KzuPropertyManager* propertyManager, const struct KzuPropertyGroup* sourceGroup,
                                                    const struct KzuPropertyGroup* targetGroup);

/** Remove all property associations from a property group. */
kzsError kzuPropertyManagerRemovePropertyGroupContent(const struct KzuPropertyManager* propertyManager, const struct KzuPropertyGroup* propertyGroup);


/** Check if an object node has or inherits a property.
* \param objectNode The object node containing the property, or where the search starts in case the property is inherited.
* \param propertyType The property to search for.
* \return KZ_TRUE if the object node has or inherits the property, KZ_FALSE otherwise.
*/
kzBool kzuObjectNodeHasProperty(const struct KzuObjectNode* objectNode, const struct KzuPropertyType* propertyType);


/** Register an object node with a property manager.
* Only registered object nodes are known to be object nodes as opposed to e.g. void pointers.
*/
kzsError kzuPropertyManagerRegisterObjectNode(const struct KzuPropertyManager* propertyManager, const struct KzuObjectNode* objectNode);
/** Unregister an object node with a property manager. */
kzsError kzuPropertyManagerUnregisterObjectNode(const struct KzuPropertyManager* propertyManager, const struct KzuObjectNode* objectNode);

/** Suspend layout invalidation. This function can be called several times, but each call must be matched with ResumeLayoutInvalidation. */
kzsError kzuPropertyManagerSuspendLayoutInvalidation(struct KzuPropertyManager* propertyManager);
/** Resume layout invalidation. */
kzsError kzuPropertyManagerResumeLayoutInvalidation(struct KzuPropertyManager* propertyManager);
/** Check if layout invalidation is suspended.
* While the layout invalidation is suspended, the ::KZU_PROPERTY_TYPE_CHANGE_FLAG_LAYOUT property type flag is not in effect.
*/
kzBool kzuPropertyManagerIsLayoutInvalidationSuspended(const struct KzuPropertyManager* propertyManager);


/** Checks if a property type is supported in the property stack.
* Properties that are not supported by the property stack cannot have value sources or modifiers.
* The property stack cannot support properties of type KZU_PROPERTY_DATA_TYPE_ARRAY, KZU_PROPERTY_DATA_TYPE_STRUCT and KZU_PROPERTY_DATA_TYPE_POINTER.
*/
kzBool kzuPropertyManagerSupportsPropertyStack(const struct KzuPropertyType* propertyType);


/** Add a value source. The highest priority value source provides the property value which is then passed to all of the modifiers (if any).
* \param propertyManager The property manager to use.
* \param object The object containing the property.
* \param propertyType The property whose value the value source provides.
* \param valueSource The value source to add.
* \param precedence Priority of the value in case there are more than one value sources for the property.
* \param owner Pointer value distinguishing this value source addition from other additions of this same value source.
* \return KZS_SUCCESS on success.
*/
kzsError kzuPropertyManagerAddValueSource(const struct KzuPropertyManager* propertyManager, const void* object, const struct KzuPropertyType* propertyType,
                                          void* valueSource, enum KzuPropertyValuePrecedence precedence, void* owner);
/** Remove a value source.
* \param propertyManager The property manager to use.
* \param object The object containing the property.
* \param propertyType The property whose value the value source provides.
* \param valueSource The value source to remove.
* \param owner Pointer value provided when adding the value source.
* \return KZS_SUCCESS on success.
*/
kzsError kzuPropertyManagerRemoveValueSource(const struct KzuPropertyManager* propertyManager, const void* object, const struct KzuPropertyType* propertyType,
                                             const void* valueSource, const void* owner);

/** Finds base value source, i.e. the highest priority value source, of an object.
* \param propertyManager The property manager to use.
* \param object The object containing the property.
* \param propertyType The property whose value is read.
* \return The highest priority value source of the object or KZ_NULL if not found.
*/
void* kzuPropertyManagerFindBaseValueSource(const struct KzuPropertyManager* propertyManager, const void* object, const struct KzuPropertyType* propertyType);

/** Finds local value source (i.e. precedence ::KZU_PROPERTY_VALUE_PRECEDENCE_LOCAL).
* \param propertyManager The property manager to use.
* \param object The object containing the property.
* \param propertyType The property whose value is read.
* \return The ::KZU_PROPERTY_VALUE_PRECEDENCE_LOCAL value or KZ_NULL if not found.
*/
void* kzuPropertyManagerFindLocalValueSource(const struct KzuPropertyManager* propertyManager, const void* object, const struct KzuPropertyType* propertyType);

/** Copy a value source. */
kzsError kzuPropertyManagerCopyValueSource(const struct KzuPropertyManager* propertyManager, enum KzuPropertyDataType type, const void* valueSource, void** out_valueSource);

/** Delete a value source. */
kzsError kzuPropertyManagerDeleteValueSource(enum KzuPropertyDataType type, void* valueSource);


/** Add a modifier to the end of the modifiers list of the property.
* A property value originates from the highest priority value source and then goes through all the modifiers.
* If there are more than one modifier, the modifier functions are called in the order they were added.
* \param propertyManager The property manager to use.
* \param object The object containing the property.
* \param propertyType The property whose value the modifier modifies.
* \param callback The modifier function.
* \param userData User data pointer passed to the modifier function.
* \return KZS_SUCCESS on success.
*/
kzsError kzuPropertyManagerAddValueModifier(const struct KzuPropertyManager* propertyManager, const void* object, const struct KzuPropertyType* propertyType,
                                            KzuPropertyModifierCallback callback, void* userData);
/** Remove a modifier. Modifiers can be removed in a different order than they were added.
* \param propertyManager The property manager to use.
* \param object The object containing the property.
* \param propertyType The property whose value the modifier modifies.
* \param callback The modifier function.
* \param userData User data pointer passed to the modifier function.
* \return KZS_SUCCESS on success.
*/
kzsError kzuPropertyManagerRemoveValueModifier(const struct KzuPropertyManager* propertyManager, const void* object, const struct KzuPropertyType* propertyType,
                                               KzuPropertyModifierCallback callback, const void* userData);
/** Invalidate a modifier. This means invalidating the modifier's value source so that the callback is called again.
* \param propertyManager The property manager to use.
* \param object The object containing the property.
* \param propertyType The property whose value the modifier modifies.
* \param callback The modifier function.
* \param userData User data pointer passed to the modifier function.
*/
kzsError kzuPropertyManagerInvalidateValueModifier(const struct KzuPropertyManager* propertyManager, const void* object, const struct KzuPropertyType* propertyType,
                                                   KzuPropertyModifierCallback callback, const void* userData);

/**
 * Add a property change notification handler. The handler will receive notifications when property value changes.
 * If object is KZ_NULL, the handler will get notified for any changed object.
 * \param propertyManager The property manager to use.
 * \param object The object containing the property to monitor, or KZ_NULL to monitor this property in all objects.
 * \param propertyType Non-null property type which changes are monitored.
 * \param handler Pointer to the handler function.
 * \param userData User data pointer to pass to the notification handler.
 * \return KZS_SUCCESS on success.
 */
kzsError kzuPropertyManagerAddNotificationHandler(const struct KzuPropertyManager* propertyManager, const void* object,
                                                  const struct KzuPropertyType* propertyType,
                                                  KzuPropertyNotificationHandler handler, void* userData);
/** Remove a property change notification handler.
* \param propertyManager The property manager to use.
* \param object The object containing the notification handler to remove, or KZ_NULL to remove this notification handler from all objects.
* \param propertyType Non-null property type the handler was accepting.
* \param handler Pointer to the handler function.
* \param userData User data provided to the notification handler when it was added.
* \return KZS_SUCCESS on success.
*/
kzsError kzuPropertyManagerRemoveNotificationHandler(const struct KzuPropertyManager* propertyManager, const void* object,
                                                     const struct KzuPropertyType* propertyType, KzuPropertyNotificationHandler handler, void* userData);


/** Callback function for notifying property manager when localization manager has been updated. */
kzsError kzuPropertyManagerLocalizationUpdated(struct KzuLocalizationManager* localizationManager,
                                               enum KzuLocalizationUpdateReason reason, void* userData);


KZ_HEADER_END


#include "kzu_property_manager_array.h"
#include "kzu_property_manager_bool.h"
#include "kzu_property_manager_color.h"
#include "kzu_property_manager_float.h"
#include "kzu_property_manager_int.h"
#include "kzu_property_manager_matrix2x2.h"
#include "kzu_property_manager_matrix3x3.h"
#include "kzu_property_manager_matrix4x4.h"
#include "kzu_property_manager_pointer.h"
#include "kzu_property_manager_string.h"
#include "kzu_property_manager_struct.h"
#include "kzu_property_manager_vector2.h"
#include "kzu_property_manager_vector3.h"
#include "kzu_property_manager_vector4.h"
#include "kzu_property_manager_resource_id.h"


#endif
