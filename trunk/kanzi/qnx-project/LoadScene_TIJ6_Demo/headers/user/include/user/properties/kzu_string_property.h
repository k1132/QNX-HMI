/**
* \file
* Specifies string property.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_STRING_PROPERTY_H
#define KZU_STRING_PROPERTY_H


#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations */
struct KzcInputStream;
struct KzcMemoryManager;
struct KzuPropertyType;


/** 
* \struct KzuStringPropertyType
* Structure for string property type.
*/
struct KzuStringPropertyType;


/** Creates a new property type string. */
kzsError kzuStringPropertyTypeCreate(const struct KzcMemoryManager* memoryManager, kzString name, kzString defaultValue,
                                     struct KzuStringPropertyType** out_stringPropertyType);
/** Deletes string property type. */
kzsError kzuStringPropertyTypeDelete(struct KzuStringPropertyType* stringPropertyType);

/** Loads string property type from KZB. */
kzsError kzuStringPropertyTypeLoadFromKzb(struct KzuStringPropertyType* stringPropertyType, struct KzcInputStream* inputStream);


/** Returns string property type from property type. */
struct KzuStringPropertyType* kzuStringPropertyTypeFromPropertyType(const struct KzuPropertyType* propertyType);
/** Converts string property type to property type. */
struct KzuPropertyType* kzuStringPropertyTypeToPropertyType(const struct KzuStringPropertyType* stringPropertyType);

/** Gets the default value of string property type. */
kzString kzuStringPropertyTypeGetDefaultValue(const struct KzuStringPropertyType* stringPropertyType);


KZ_HEADER_END


#endif
