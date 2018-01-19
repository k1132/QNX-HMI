/**
* \file
* Specifies property.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_PROPERTY_H
#define KZU_PROPERTY_H


#include <user/properties/kzu_property_common.h>

#include <system/kzs_types.h>
#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations */
struct KzcDynamicArray;
struct KzcInputStream;
struct KzcMemoryManager;
struct KzuBinaryFileInfo;
struct KzuUIDomain;
struct KzuPropertyManager;


/**
 * \struct KzuPropertyType
 * Structure for property type. Contains ID, datatype and reference value.
 */
struct KzuPropertyType;


/* Change flags. */
#define KZU_PROPERTY_TYPE_CHANGE_FLAG_TRANSFORMATION (1 << 0) /**< Property type with this flag affects transformation of an object. */
#define KZU_PROPERTY_TYPE_CHANGE_FLAG_FINAL_TRANSFORMATION (1 << 1) /**< Property type with this flag affects final transformation of an object and all its children. */
#define KZU_PROPERTY_TYPE_CHANGE_FLAG_LAYOUT (1 << 2) /**< Property type with this flag affects layout. */
#define KZU_PROPERTY_TYPE_CHANGE_FLAG_ARRANGE (1 << 3) /**< Property type with this flag affects layout arrange. */
#define KZU_PROPERTY_TYPE_CHANGE_FLAG_RENDER (1 << 4) /**< Property type with this flag affects rendering. */
#define KZU_PROPERTY_TYPE_CHANGE_FLAG_RENDER_LAYER_MASK_AREA (1 << 5) /**< Property type with this flag only affects to mask area, used in layer render order on-demand. */
#define KZU_PROPERTY_TYPE_CHANGE_FLAG_RENDER_TREE (1 << 6) /**< Property type with this flag only affects to mask area, used in layer render order on-demand. */
#define KZU_PROPERTY_TYPE_CHANGE_FLAG_PARTIAL_RENDERING_OBJECT (1 << 16) /**< Property type with this flag affects partial rendering of itself. */
#define KZU_PROPERTY_TYPE_CHANGE_FLAG_PARTIAL_RENDERING_TREE (1 << 17) /**< Property type with this flag affects partial rendering of itself and all its children. */
#define KZU_PROPERTY_TYPE_CHANGE_FLAG_CONSTRAINT (1 << 18) /**< Property type with this flag informs that constraints are in use. */
#define KZU_PROPERTY_TYPE_CHANGE_FLAG_LAYER_RENDER_QUAD (1 << 19) /**< Property type with this flag informs that rendered quad area of layer changed, i.e. there are different fragments covered by layer than on previous arrange. */


/** Initializes property types. */
kzsError kzuPropertyTypesInitialize(const struct KzcMemoryManager* memoryManager);

/** Uninitializes property types. */
kzsError kzuPropertyTypesUninitialize(void);


/** Creates a property type. */
kzsError kzuPropertyTypeCreate(const struct KzcMemoryManager* memoryManager, enum KzuPropertyDataType dataType,
                               kzString name, struct KzuPropertyType** out_propertyType);

/** Deletes a property type. */
kzsError kzuPropertyTypeDelete(const struct KzuPropertyType* propertyType);

/** Marks the property type as read-only. This means that .KZB files cannot overwrite any of its data later on. */
kzsError kzuPropertyTypeSetReadOnly(struct KzuPropertyType* propertyType);

/** Loads a property type from KZB. */
kzsError kzuPropertyTypeLoadFromKZB(struct KzuPropertyType* propertyType, struct KzcInputStream* inputStream, const struct KzuBinaryFileInfo* file);

/** Returns property type's name. */
kzString kzuPropertyTypeGetName(const struct KzuPropertyType* propertyType);

/** Gets data type of property. */
enum KzuPropertyDataType kzuPropertyTypeGetDataType(const struct KzuPropertyType* propertyType);

/** Sets the inheritance behavior of the property type. */
void kzuPropertyTypeSetInherited(struct KzuPropertyType* propertyType, kzBool inherited);
/** Gets the inheritance behavior of the property type. */
kzBool kzuPropertyTypeIsInherited(const struct KzuPropertyType* propertyType);
/** Sets the change flags this type updates when a property is set on object nodes. */
void kzuPropertyTypeSetChangeFlags(struct KzuPropertyType* propertyType, kzU32 flags);
/** Clear the change flags this type updates when a property is set on object nodes. */
void kzuPropertyTypeClearChangeFlags(struct KzuPropertyType* propertyType, kzU32 flags);
/** Get the change flags this type updates when a property is set on object nodes. */
kzU32 kzuPropertyTypeGetChangeFlags(const struct KzuPropertyType* propertyType);

/** Gets the float-type property field of the given property type for the referenced target object. */
kzFloat kzuPropertyFieldGetFloat(const struct KzuPropertyManager* propertyManager, const struct KzuPropertyType* propertyType, 
                                 enum KzuPropertyField targetAttribute, const void* targetObject, kzBool localValue);
/** Gets the index of the property type that is used inside property manager for look-up. */
kzUint kzuPropertyTypeGetIndex(const struct KzuPropertyType* propertyType);


KZ_HEADER_END


#endif
