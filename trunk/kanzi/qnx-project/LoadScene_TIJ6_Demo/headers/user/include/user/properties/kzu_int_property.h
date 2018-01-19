/**
* \file
* Specifies integer property.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_INT_PROPERTY_H
#define KZU_INT_PROPERTY_H


#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations */
struct KzcInputStream;
struct KzcMemoryManager;
struct KzuPropertyType;


/** 
* \struct KzuIntPropertyType
* Structure for int property type.
*/
struct KzuIntPropertyType;


/** Creates a property type integer. */
kzsError kzuIntPropertyTypeCreate(const struct KzcMemoryManager* memoryManager, kzString name, kzInt defaultValue,
                                  struct KzuIntPropertyType** out_intPropertyType);
/** Deletes int property type. */
kzsError kzuIntPropertyTypeDelete(struct KzuIntPropertyType* intPropertyType);

/** Loads int property type from KZB. */
kzsError kzuIntPropertyTypeLoadFromKzb(struct KzuIntPropertyType* intPropertyType, struct KzcInputStream* inputStream);


/** Returns int property type from property type. */
struct KzuIntPropertyType* kzuIntPropertyTypeFromPropertyType(const struct KzuPropertyType* propertyType);
/** Return property type from int property type. */
struct KzuPropertyType* kzuIntPropertyTypeToPropertyType(const struct KzuIntPropertyType* intPropertyType);

/** Gets the default value of int property type. */
kzInt kzuIntPropertyTypeGetDefaultValue(const struct KzuIntPropertyType* intPropertyType);


KZ_HEADER_END


#endif
