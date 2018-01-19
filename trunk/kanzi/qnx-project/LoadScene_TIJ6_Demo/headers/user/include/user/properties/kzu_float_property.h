/**
* \file
* Specifies float property.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_FLOAT_PROPERTY_H
#define KZU_FLOAT_PROPERTY_H


#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations */
struct KzcInputStream;
struct KzcMemoryManager;
struct KzuPropertyType;


/** 
* \struct KzuFloatPropertyType
* Structure for float property type. 
*/
struct KzuFloatPropertyType;


/** Creates a new float property type. */
kzsError kzuFloatPropertyTypeCreate(const struct KzcMemoryManager* memoryManager, kzString name, 
                                    kzFloat defaultValue, struct KzuFloatPropertyType** out_floatPropertyType);
/** Deletes float property type. */
kzsError kzuFloatPropertyTypeDelete(struct KzuFloatPropertyType* floatPropertyType);

/** Loads float property type from KZB. */
kzsError kzuFloatPropertyTypeLoadFromKzb(struct KzuFloatPropertyType* floatPropertyType, struct KzcInputStream* inputStream);


/** Returns float property type from property type. */
struct KzuFloatPropertyType* kzuFloatPropertyTypeFromPropertyType(const struct KzuPropertyType* propertyType);
/** Returns property type from float property type. */
struct KzuPropertyType* kzuFloatPropertyTypeToPropertyType(const struct KzuFloatPropertyType* floatPropertyType);

/** Gets the default value of float property type. */
kzFloat kzuFloatPropertyTypeGetDefaultValue(const struct KzuFloatPropertyType* floatPropertyType);


KZ_HEADER_END


#endif
