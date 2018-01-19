/**
* \file
* Property manager.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_PROPERTY_MANAGER_BASE_H
#define KZU_PROPERTY_MANAGER_BASE_H


#include "kzu_property_manager.h"
#include "kzu_property_common.h"

#include <core/util/math/kzc_vector2.h>
#include <core/util/math/kzc_vector3.h>
#include <core/util/math/kzc_vector4.h>
#include <core/util/math/kzc_matrix2x2.h>
#include <core/util/math/kzc_matrix3x3.h>
#include <core/util/math/kzc_matrix4x4.h>
#include <core/util/color/kzc_color.h>
#include <core/util/string/kzc_string.h>

#include <system/kzs_types.h>
#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations */
struct KzuPropertyManager;
struct KzuPropertyType;
struct KzuArrayPropertyType;
struct KzuObjectNode;
struct KzcHashSet;


/** Common property data. */
struct KzuPropertyBaseStorage
{
    kzU32 flags; /**< Property flags. */
    struct KzcDynamicArray* valueStack; /**< Value stack. */
    struct KzcDynamicArray* modifierStack;  /**< Modifier stack. */
    kzUint notificationDepth; /**< Notification depth. */
    struct KzcDynamicArray* notificationHandlers; /**< Notification handlers. <KzuPropertyNotificationHandler_internal>. */
};

/** Float property data. */
struct KzuPropertyFloatStorage
{
    struct KzuPropertyBaseStorage baseStorage; /**< Base storage. */
};

/** Int property data. */
struct KzuPropertyIntStorage
{
    struct KzuPropertyBaseStorage baseStorage; /**< Base storage. */
};

/** Bool property data. */
struct KzuPropertyBoolStorage
{
    struct KzuPropertyBaseStorage baseStorage; /**< Base storage. */
};

/** Color property data. */
struct KzuPropertyColorStorage
{
    struct KzuPropertyBaseStorage baseStorage; /**< Base storage. */
};

/** Vector2 property data. */
struct KzuPropertyVector2Storage
{
    struct KzuPropertyBaseStorage baseStorage; /**< Base storage. */
};

/** Vector3 property data. */
struct KzuPropertyVector3Storage
{
    struct KzuPropertyBaseStorage baseStorage; /**< Base storage. */
};

/** Vector4 property data. */
struct KzuPropertyVector4Storage
{
    struct KzuPropertyBaseStorage baseStorage; /**< Base storage. */
};

/** Matrix2x2 property data. */
struct KzuPropertyMatrix2x2Storage
{
    struct KzuPropertyBaseStorage baseStorage; /**< Base storage. */
};

/** Matrix3x3 property data. */
struct KzuPropertyMatrix3x3Storage
{
    struct KzuPropertyBaseStorage baseStorage; /**< Base storage. */
};

/** Matrix4x4 property data. */
struct KzuPropertyMatrix4x4Storage
{
    struct KzuPropertyBaseStorage baseStorage; /**< Base storage. */
};

/** String property data. */
struct KzuPropertyStringStorage
{
    struct KzuPropertyBaseStorage baseStorage; /**< Base storage. */
};

/** Resource ID property data. */
struct KzuPropertyResourceIDStorage
{
    struct KzuPropertyBaseStorage baseStorage; /**< Base storage. */
    struct KzuResource* resource; /**< Resolved resource value. */
    kzBool overridden; /**< Se to true when resource is directly assigned with the API. In this case the attach/detach does nothing. */
    kzBool attached; /**< Is the resource ID property attached. */
    struct KzuResourceManager* resourceManager; /**< Resource manager where the resource matching the resourceURL is acquired. */
    kzMutableString resourceURL; /**< A resource URL that will be resolved to a resource by the property manager. */
};

/** ResourceID value source. */
struct KzuPropertyResourceIDValueSource
{
    kzMutableString value;   /**< Value. */
};

/** Void property data. */
struct KzuPropertyPointerStorage
{
    struct KzuPropertyBaseStorage baseStorage; /**< Base storage. */

    kzBool isResource; /**< Specifies if given pointer property is a resource, must be released properly if yes. */
    void* value; /**< Property value. */
    kzMutableString resourceURL; /**< Temporary resource URL during loading, from which the actual resource is acquired during finishing of loading. */
    kzMutableString pathValue; /**< Relative path. */
    kzBool overridden; /**< Se to true when pointer value is directly assigned with the API. In this case the attach/detach does nothing. */
    kzBool attached; /**< Is the pointer property attached. */
};

/** Struct property data. */
struct KzuPropertyStructStorage
{
    struct KzuPropertyBaseStorage baseStorage; /**< Base storage. */
};

/** Array property data. */
struct KzuPropertyArrayStorage
{
    struct KzuPropertyBaseStorage baseStorage; /**< Base storage. */

    struct KzcDynamicArray* values; /**< Property values. */
};

/** Property value source entry structure. */
struct KzuPropertyValueSourceEntry
{
    void* valueSource;                          /**< Value source. */
    void* owner;                                /**< Owner. */
    enum KzuPropertyValuePrecedence precedence; /**< Precedence. */
};

/** Property modifier entry structure. */
struct KzuPropertyModifierEntry
{
    void* valueSource;                      /**< Value source. */
    void* userData;                         /**< User data. */
    KzuPropertyModifierCallback callback;   /**< Callback. */
    kzBool valid;                           /**< Is modifier valid. */
};

/** Notification handler. */
struct KzuPropertyNotificationHandler_internal
{
    kzBool valid; /**< Is the handler still valid. */
    KzuPropertyNotificationHandler handler; /**< Handler function. */
    void* userData; /**< User data passed as an argument for the handler. */
};

/** Type data. */
struct KzuPropertyTypeStorage
{
    const struct KzuPropertyType* type; /**< Property type of the storage. */
    struct KzcHashMap* propertyContainer; /**< Property value storage. <void*, KzuPropertyBaseStorage*> */
    struct KzcDynamicArray* notificationHandlers; /**< Notification handlers for the property type. <KzuPropertyNotificationHandler_internal>. */
    kzUint notificationDepth; /**< Current notification depth. */
};

/** Property manager. */
struct KzuPropertyManager
{
    struct KzcDynamicArray* typeContainer; /**< Array of property type storages. <KzuPropertyTypeStorage>. */
    struct KzcHashMap* groupContainer; /**< Map for property groups. <void*, KzcDynamicArray<KzuPropertyGroup>>. */
    struct KzcHashMap* typesByNames; /**< Map for property types. <kzString, KzuPropertyType>. */
    struct KzcHashSet* objectNodes; /**< Hash set to store all object nodes. <KzuObjectNode>. */
    struct KzcHashMap* typesByObjects; /**< Map for  property types. <void*, KzcDynamicArray<KzuPropertyType>>. */
    kzUint suspendLayoutCounter;    /**< Counts how many times layout has been suspended. */
};


/** Initializes base property storage. */
void kzuPropertyManagerInitializeBaseProperty_protected(struct KzuPropertyBaseStorage* property);

/** Finds property type storage. Returns KZ_NULL if the type storage is not found. */
struct KzuPropertyTypeStorage* kzuPropertyManagerFindTypeStorage_protected(const struct KzuPropertyManager* propertyManager, const struct KzuPropertyType* propertyType);

/** Finds property storage. Finds only storages that have value sources. Returns KZ_NULL if the storage is not found. */
struct KzuPropertyBaseStorage* kzuPropertyManagerFindPropertyStorage_protected(const void* object, const struct KzuPropertyTypeStorage* typeStorage);

/** Finds property storage. Finds storages with and without value sources. Returns KZ_NULL if the storage is not found. */
struct KzuPropertyBaseStorage* kzuPropertyManagerFindOrphanedPropertyStorage_protected(const void* object, const struct KzuPropertyTypeStorage* typeStorage);

/** Acquires property storage. Finds storages with and without value sources. Creates orphaned storage if a storage is not found. */
kzsError kzuPropertyManagerAcquirePropertyStorage_protected(const struct KzuPropertyManager* propertyManager, const void* object, const struct KzuPropertyTypeStorage* typeStorage, struct KzuPropertyBaseStorage** out_propertyStorage);

/** Finds base value source entry. Returns KZ_NULL if not found. */
struct KzuPropertyValueSourceEntry* kzuPropertyBaseStorageFindBaseValueSourceEntry_protected(const struct KzuPropertyBaseStorage* propertyStorage);

/** Finds local value source entry. Returns KZ_NULL if not found. */
struct KzuPropertyValueSourceEntry* kzuPropertyBaseStorageFindLocalValueSourceEntry_protected(const struct KzuPropertyBaseStorage* propertyStorage);

/** Removes local value. */
kzsError kzuPropertyBaseRemoveLocalValue_private(const struct KzuPropertyManager* propertyManager, struct KzuPropertyTypeStorage* typeStorage,
                                                 const void* object, struct KzuPropertyBaseStorage* propertyStorage, kzBool unlinking);

/** Removes property storage. */
kzsError kzuPropertyManagerUnlinkPropertyStorage_private(const struct KzuPropertyManager* propertyManager, const void* object,
                                                         struct KzuPropertyTypeStorage* typeStorage);


/** Adds a value source. */
kzsError kzuPropertyBaseStorageAddValueSource_protected(const struct KzuPropertyManager* propertyManager, struct KzuPropertyTypeStorage* typeStorage,
                                                        const void* object, struct KzuPropertyBaseStorage* propertyStorage,
                                                        void* valueSource, enum KzuPropertyValuePrecedence precedence, void* owner);

/** Finds property storage taking groups into account. Returns KZ_NULL if the storage is not found. */
struct KzuPropertyBaseStorage* kzuPropertyManagerFindPropertyStorageWithGroups_protected(const struct KzuPropertyManager* propertyManager, const void* object, const struct KzuPropertyTypeStorage* typeStorage);

/** Finds property storage taking groups into account. Returns KZ_NULL if the storage is not found. This vesion returns orphaned property storages as well. */
struct KzuPropertyBaseStorage* kzuPropertyManagerFindOrphanedPropertyStorageWithGroups_protected(const struct KzuPropertyManager* propertyManager, const void* object, const struct KzuPropertyTypeStorage* typeStorage);

/** Validate modifiers. */
kzsError kzuPropertyManagerValidateModifiers_protected(const struct KzuPropertyManager* propertyManager, const void* object, const struct KzuPropertyType* propertyType, const struct KzuPropertyBaseStorage* propertyStorage, kzBool fullInvalidation);


/** Gets a property type storage if it exists, or creates new storage if it is not found. */
kzsError kzuPropertyManagerAcquireTypeStorage_protected(const struct KzuPropertyManager* propertyManager, const struct
                                                        KzuPropertyType* propertyType,
                                                        struct KzuPropertyTypeStorage** out_storage);

/** Deletes a property type storage. */
kzsError kzuPropertyManagerDeleteTypeStorage_private(struct KzuPropertyTypeStorage* typeStorage);


/** Gets a float property storage if it exists, or creates new storage if it is not found. */
kzsError kzuPropertyManagerAcquireFloatStorage_private(const struct KzuPropertyManager* propertyManager, const void* object,
                                                       const struct KzuPropertyTypeStorage* typeStorage,
                                                       struct KzuPropertyFloatStorage** out_propertyStorage);

/** Gets a int property storage if it exists, or creates new storage if it is not found. */
kzsError kzuPropertyManagerAcquireIntStorage_private(const struct KzuPropertyManager* propertyManager, const void* object,
                                                     const struct KzuPropertyTypeStorage* typeStorage,
                                                     struct KzuPropertyIntStorage** out_propertyStorage);

/** Gets a bool property storage if it exists, or creates new storage if it is not found. */
kzsError kzuPropertyManagerAcquireBoolStorage_private(const struct KzuPropertyManager* propertyManager, const void* object,
                                                      const struct KzuPropertyTypeStorage* typeStorage,
                                                      struct KzuPropertyBoolStorage** out_propertyStorage);

/** Gets a color property storage if it exists, or creates new storage if it is not found. */
kzsError kzuPropertyManagerAcquireColorStorage_private(const struct KzuPropertyManager* propertyManager, const void* object,
                                                       const struct KzuPropertyTypeStorage* typeStorage,
                                                       struct KzuPropertyColorStorage** out_propertyStorage);

/** Gets a vector2 property storage if it exists, or creates new storage if it is not found. */
kzsError kzuPropertyManagerAcquireVector2Storage_private(const struct KzuPropertyManager* propertyManager, const void* object,
                                                         const struct KzuPropertyTypeStorage* typeStorage,
                                                         struct KzuPropertyVector2Storage** out_propertyStorage);

/** Gets a vector3 property storage if it exists, or creates new storage if it is not found. */
kzsError kzuPropertyManagerAcquireVector3Storage_private(const struct KzuPropertyManager* propertyManager, const void* object,
                                                         const struct KzuPropertyTypeStorage* typeStorage,
                                                         struct KzuPropertyVector3Storage** out_propertyStorage);

/** Gets a vector4 property storage if it exists, or creates new storage if it is not found. */
kzsError kzuPropertyManagerAcquireVector4Storage_private(const struct KzuPropertyManager* propertyManager, const void* object,
                                                         const struct KzuPropertyTypeStorage* typeStorage,
                                                         struct KzuPropertyVector4Storage** out_propertyStorage);

/** Gets a matrix2x2 property storage if it exists, or creates new storage if it is not found. */
kzsError kzuPropertyManagerAcquireMatrix2x2Storage_private(const struct KzuPropertyManager* propertyManager, const void* object,
                                                           const struct KzuPropertyTypeStorage* typeStorage,
                                                           struct KzuPropertyMatrix2x2Storage** out_propertyStorage);

/** Gets a matrix3x3 property storage if it exists, or creates new storage if it is not found. */
kzsError kzuPropertyManagerAcquireMatrix3x3Storage_private(const struct KzuPropertyManager* propertyManager, const void* object,
                                                           const struct KzuPropertyTypeStorage* typeStorage,
                                                           struct KzuPropertyMatrix3x3Storage** out_propertyStorage);

/** Gets a matrix4x4 property storage if it exists, or creates new storage if it is not found. */
kzsError kzuPropertyManagerAcquireMatrix4x4Storage_private(const struct KzuPropertyManager* propertyManager, const void* object,
                                                           const struct KzuPropertyTypeStorage* typeStorage,
                                                           struct KzuPropertyMatrix4x4Storage** out_propertyStorage);

/** Gets a void property storage if it exists, or creates new storage if it is not found. */
kzsError kzuPropertyManagerAcquirePointerStorage_private(const struct KzuPropertyManager* propertyManager, const void* object,
                                                         const struct KzuPropertyTypeStorage* typeStorage,
                                                         struct KzuPropertyPointerStorage** out_propertyStorage);

/** Gets a string property storage if it exists, or creates new storage if it is not found. */
kzsError kzuPropertyManagerAcquireStringStorage_private(const struct KzuPropertyManager* propertyManager, const void* object,
                                                        const struct KzuPropertyTypeStorage* typeStorage,
                                                        struct KzuPropertyStringStorage** out_propertyStorage);

/** Gets a struct property storage if it exists, or creates new storage if it is not found. */
kzsError kzuPropertyManagerAcquireStructStorage_private(const struct KzuPropertyManager* propertyManager, const void* object,
                                                        const struct KzuPropertyTypeStorage* typeStorage,
                                                        struct KzuPropertyStructStorage** out_propertyStorage);

/** Gets an array property storage if it exists, or creates new storage if it is not found. */
kzsError kzuPropertyManagerAcquireArrayStorage_private(const struct KzuPropertyManager* propertyManager, const void* object,
                                                       const struct KzuPropertyTypeStorage* typeStorage,
                                                       struct KzuPropertyArrayStorage** out_propertyStorage);

/** Gets a resource ID property storage if it exists, or creates new storage if it is not found. */
kzsError kzuPropertyManagerAcquireResourceIDStorage_private(const struct KzuPropertyManager* propertyManager, const void* object,
                                                            const struct KzuPropertyTypeStorage* typeStorage,
                                                            struct KzuPropertyResourceIDStorage** out_propertyStorage);


/** Process a property change but do not invoke modifiers. */
kzsError kzuPropertyManagerProcessPropertyChangeNoModifiers_protected(const struct KzuPropertyManager* propertyManager, struct KzuPropertyTypeStorage* typeStorage,
                                                                      const void* object, struct KzuPropertyBaseStorage* propertyStorage, enum KzuPropertyNotificationReason reason);
/** Process a property change. */
kzsError kzuPropertyManagerProcessPropertyChange_protected(const struct KzuPropertyManager* propertyManager, struct KzuPropertyTypeStorage* typeStorage,
                                                           const void* object, struct KzuPropertyBaseStorage* propertyStorage, enum KzuPropertyNotificationReason reason);
/** Updates property change flags for an object node. */
kzsError kzuPropertyManagerUpdateObjectNodeChangeFlags_protected(const struct KzuPropertyManager* propertyManager,
                                                                 const struct KzuPropertyTypeStorage* typeStorage, struct KzuObjectNode* objectNode);
/** Updates property change flags for a property group. */
kzsError kzuPropertyManagerUpdateGroupChangeFlags_protected(const struct KzuPropertyManager* propertyManager,
                                                            const struct KzuPropertyTypeStorage* typeStorage, const void* group);

/** Cleanup invalid notifications. */
kzsError kzuPropertyManagerCleanupTypeNotifications_private(const struct KzuPropertyTypeStorage* typeStorage);
/** Cleanup invalid notifications. */
kzsError kzuPropertyManagerCleanupPropertyNotifications_private(const struct KzuPropertyBaseStorage* propertyStorage);

/** Finds property storage for an object node. Takes groups into account. Returns KZ_NULL if the storage is not found. */
struct KzuPropertyBaseStorage* kzuObjectNodeFindPropertyStorage_protected(const struct KzuObjectNode* objectNode, const struct KzuPropertyType* propertyType);
/** Finds property storage for an object node. Takes groups into account. Returns KZ_NULL if the storage is not found. This function returns orphaned property storages as well. */
struct KzuPropertyBaseStorage* kzuObjectNodeFindOrphanedPropertyStorage_protected(const struct KzuObjectNode* objectNode, const struct KzuPropertyType* propertyType);
/**
 * Finds property storage for an object node and provides the object node site where the property value was stored.
 * Takes groups into account. Returns the property storage and writes the site to out_objectNode.
 * Returns KZ_NULL and doesn't modify out_objectNode if not found.
 */
struct KzuPropertyBaseStorage* kzuObjectNodeFindPropertyStorageWithSite_private(const struct KzuObjectNode* objectNode, const struct KzuPropertyTypeStorage* typeStorage,
                                                                                const struct KzuObjectNode** out_objectNode);
/**
 * Finds property storage for an object node and provides the object node site where the property value was stored.
 * Takes groups into account. Returns the property storage and writes the site to out_objectNode.
 * This vesion returns orphaned property storages as well.
 * Returns KZ_NULL and doesn't modify out_objectNode if not found.
 */
struct KzuPropertyBaseStorage* kzuObjectNodeFindOrphanedPropertyStorageWithSite_private(const struct KzuObjectNode* objectNode, const struct KzuPropertyTypeStorage* typeStorage,
                                                                                        const struct KzuObjectNode** out_objectNode);

/** Registers a property type for an object. */
kzsError kzuPropertyManagerRegisterPropertyTypeForObject_private(const struct KzuPropertyManager* propertyManager, const void* object,
                                                                 const struct KzuPropertyType* propertyType);
/** Unregisters a property type for an object. */
kzsError kzuPropertyManagerUnregisterPropertyTypeForObject_private(const struct KzuPropertyManager* propertyManager, const void* object,
                                                                   const struct KzuPropertyType* propertyType);

/* TODO: Rename all these functions to _private. */
/** Get base float value. */
kzFloat kzuPropertyManagerGetBaseFloatValue(const struct KzuPropertyFloatStorage* storage);
/** Get final float value. */
kzFloat kzuPropertyManagerGetFinalFloatValue(const struct KzuPropertyFloatStorage* storage);
/** Get base bool value. */
kzBool kzuPropertyManagerGetBaseBoolValue(const struct KzuPropertyBoolStorage* storage);
/** Get final bool value. */
kzBool kzuPropertyManagerGetFinalBoolValue(const struct KzuPropertyBoolStorage* storage);
/** Get base int value. */
kzInt kzuPropertyManagerGetBaseIntValue(const struct KzuPropertyIntStorage* storage);
/** Get final int value. */
kzInt kzuPropertyManagerGetFinalIntValue(const struct KzuPropertyIntStorage* storage);
/** Get base vector2 value. */
struct KzcVector2 kzuPropertyManagerGetBaseVector2Value(const struct KzuPropertyVector2Storage* storage);
/** Get final vector2 value. */
struct KzcVector2 kzuPropertyManagerGetFinalVector2Value(const struct KzuPropertyVector2Storage* storage);
/** Get base vector3 value. */
struct KzcVector3 kzuPropertyManagerGetBaseVector3Value(const struct KzuPropertyVector3Storage* storage);
/** Get final vector3 value. */
struct KzcVector3 kzuPropertyManagerGetFinalVector3Value(const struct KzuPropertyVector3Storage* storage);
/** Get base vector4 value. */
struct KzcVector4 kzuPropertyManagerGetBaseVector4Value(const struct KzuPropertyVector4Storage* storage);
/** Get final vector4 value. */
struct KzcVector4 kzuPropertyManagerGetFinalVector4Value(const struct KzuPropertyVector4Storage* storage);
/** Get base color value. */
struct KzcColorRGBA kzuPropertyManagerGetBaseColorValue(const struct KzuPropertyColorStorage* storage);
/** Get final color value. */
struct KzcColorRGBA kzuPropertyManagerGetFinalColorValue(const struct KzuPropertyColorStorage* storage);
/** Get base matrix2x2 value. */
struct KzcMatrix2x2 kzuPropertyManagerGetBaseMatrix2x2Value(const struct KzuPropertyMatrix2x2Storage* storage);
/** Get final matrix2x2 value. */
struct KzcMatrix2x2 kzuPropertyManagerGetFinalMatrix2x2Value(const struct KzuPropertyMatrix2x2Storage* storage);
/** Get base matrix3x3 value. */
struct KzcMatrix3x3 kzuPropertyManagerGetBaseMatrix3x3Value(const struct KzuPropertyMatrix3x3Storage* storage);
/** Get final matrix3x3 value. */
struct KzcMatrix3x3 kzuPropertyManagerGetFinalMatrix3x3Value(const struct KzuPropertyMatrix3x3Storage* storage);
/** Get base matrix3x3 value. */
void kzuPropertyManagerGetBaseMatrix3x3ValueSRT(const struct KzuPropertyMatrix3x3Storage* storage, struct KzcVector2* out_scale, kzFloat* out_rotateInDegrees, struct KzcVector2* out_translate);
/** Get final matrix3x3 value. */
void kzuPropertyManagerGetFinalMatrix3x3ValueSRT(const struct KzuPropertyMatrix3x3Storage* storage, struct KzcVector2* out_scale, kzFloat* out_rotateInDegrees, struct KzcVector2* out_translate);
/** Gets combined base matrix3x3 and SRT values. Also retrieves flag value if matrix value was last set (if so, SRT values are not reliable since they are extracted from matrix). */
void kzuPropertyManagerGetBaseMatrix3x3ValueCombined(const struct KzuPropertyMatrix3x3Storage* storage, struct KzcMatrix3x3* out_matrixValue,
                                                     struct KzcVector2* out_scale, kzFloat* out_rotateInDegrees, struct KzcVector2* out_translate, kzBool* out_isMatrixValue);
/** Gets combined final matrix3x3 and SRT values. Also retrieves flag value if matrix value was last set (if so, SRT values are not reliable since they are extracted from matrix). */
void kzuPropertyManagerGetFinalMatrix3x3ValueCombined(const struct KzuPropertyMatrix3x3Storage* storage, struct KzcMatrix3x3* out_matrixValue,
                                                     struct KzcVector2* out_scale, kzFloat* out_rotateInDegrees, struct KzcVector2* out_translate, kzBool* out_isMatrixValue);
/** Get base matrix4x4 value. */
struct KzcMatrix4x4 kzuPropertyManagerGetBaseMatrix4x4Value(const struct KzuPropertyMatrix4x4Storage* storage);
/** Get final matrix4x4 value. */
struct KzcMatrix4x4 kzuPropertyManagerGetFinalMatrix4x4Value(const struct KzuPropertyMatrix4x4Storage* storage);
/** Get base matrix4x4 value. */
void kzuPropertyManagerGetBaseMatrix4x4ValueSRT(const struct KzuPropertyMatrix4x4Storage* storage, struct KzcVector3* out_scale, struct KzcVector3* out_rotateInDegrees, struct KzcVector3* out_translate);
/** Get final matrix4x4 value. */
void kzuPropertyManagerGetFinalMatrix4x4ValueSRT(const struct KzuPropertyMatrix4x4Storage* storage, struct KzcVector3* out_scale, struct KzcVector3* out_rotateInDegrees, struct KzcVector3* out_translate);
/** Gets combined base matrix4x4 and SRT values. Also retrieves flag value if matrix value was last set (if so, SRT values are not reliable since they are extracted from matrix). */
void kzuPropertyManagerGetBaseMatrix4x4ValueCombined(const struct KzuPropertyMatrix4x4Storage* storage, struct KzcMatrix4x4* out_matrixValue,
                                                     struct KzcVector3* out_scale, struct KzcVector3* out_rotateInDegrees, struct KzcVector3* out_translate, kzBool* out_isMatrixValue);
/** Gets combined final matrix4x4 and SRT values. Also retrieves flag value if matrix value was last set (if so, SRT values are not reliable since they are extracted from matrix). */
void kzuPropertyManagerGetFinalMatrix4x4ValueCombined(const struct KzuPropertyMatrix4x4Storage* storage, struct KzcMatrix4x4* out_matrixValue,
                                                     struct KzcVector3* out_scale, struct KzcVector3* out_rotateInDegrees, struct KzcVector3* out_translate, kzBool* out_isMatrixValue);
/** Get base string value. */
kzString kzuPropertyManagerGetBaseStringValue(const struct KzuPropertyStringStorage* storage);
/** Get final string value. */
kzString kzuPropertyManagerGetFinalStringValue(const struct KzuPropertyStringStorage* storage);
/** Get base resource ID value. */
kzString kzuPropertyManagerGetBaseResourceIDValue(const struct KzuPropertyResourceIDStorage* storage);
/** Get final resource ID value. */
kzString kzuPropertyManagerGetFinalResourceIDValue(const struct KzuPropertyResourceIDStorage* storage);
/** Checks if the given storage has a resource value. This means that either it has been overridden with a resource value or it has been attached from a modifier or value stack. */
kzBool kzuPropertyManagerResourceIDHasResource_private(const struct KzuPropertyResourceIDStorage* storage);

/** Refreshes a resource ID property. This causes the resource to be resolved again. */
kzsError kzuPropertyManagerResourceIDRefresh_private(const struct KzuPropertyManager* propertyManager, struct KzuPropertyTypeStorage* typeStorage,
                                                     struct KzuPropertyResourceIDStorage* storage, const void* object);


KZ_HEADER_END


#endif
