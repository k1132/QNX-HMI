/**
* \file
* Specifies boolean property.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_BOOL_PROPERTY_H
#define KZU_BOOL_PROPERTY_H


#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations */
struct KzcInputStream;
struct KzcMemoryManager;
struct KzuPropertyType;


/** 
* \struct KzuBoolPropertyType
* Structure for bool property type. 
*/
struct KzuBoolPropertyType;


/** Creates a property type bool. */
kzsError kzuBoolPropertyTypeCreate(const struct KzcMemoryManager* memoryManager, kzString name, kzBool defaultValue,
                                   struct KzuBoolPropertyType** out_boolPropertyType);
/** Deletes bool property type. */
kzsError kzuBoolPropertyTypeDelete(struct KzuBoolPropertyType* boolPropertyType);

/** Loads bool property type from KZB. */
kzsError kzuBoolPropertyTypeLoadFromKzb(struct KzuBoolPropertyType* boolPropertyType, struct KzcInputStream* inputStream);


/** Converts property type to bool property type. */
struct KzuBoolPropertyType* kzuBoolPropertyTypeFromPropertyType(const struct KzuPropertyType* propertyType);
/** Converts bool property type to property type. */
struct KzuPropertyType* kzuBoolPropertyTypeToPropertyType(const struct KzuBoolPropertyType* boolPropertyType);

/** Gets the default value of bool property type. */
kzBool kzuBoolPropertyTypeGetDefaultValue(const struct KzuBoolPropertyType* boolPropertyType);


KZ_HEADER_END


#endif
