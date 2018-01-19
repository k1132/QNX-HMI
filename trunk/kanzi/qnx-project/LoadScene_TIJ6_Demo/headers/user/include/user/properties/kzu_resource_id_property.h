/**
* \file
* Specifies Resource ID property.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_RESOURCE_ID_PROPERTY_H
#define KZU_RESOURCE_ID_PROPERTY_H


#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations */
struct KzcInputStream;
struct KzcMemoryManager;
struct KzuPropertyType;


/** 
* \struct KzuResourceIDProperty
* Structure for Resource ID property type.
*/
struct KzuResourceIDPropertyType;


/** Creates a new property type resource ID. */
kzsError kzuResourceIDPropertyTypeCreate(const struct KzcMemoryManager* memoryManager, kzString name, kzString defaultValue,
                                         struct KzuResourceIDPropertyType** out_resourceIDPropertyType);
/** Deletes resourceID property type. */
kzsError kzuResourceIDPropertyTypeDelete(struct KzuResourceIDPropertyType* resourceIDPropertyType);

/** Loads resourceID property type from KZB. */
kzsError kzuResourceIDPropertyTypeLoadFromKzb(struct KzuResourceIDPropertyType* resourceIDPropertyType, struct KzcInputStream* inputStream);


/** Returns resourceID property type from property type. */
struct KzuResourceIDPropertyType* kzuResourceIDPropertyTypeFromPropertyType(const struct KzuPropertyType* propertyType);
/** Converts resourceID property type to property type. */
struct KzuPropertyType* kzuResourceIDPropertyTypeToPropertyType(const struct KzuResourceIDPropertyType* resourceIDPropertyType);

/** Gets the default value of resourceID property type. */
kzString kzuResourceIDPropertyTypeGetDefaultValue(const struct KzuResourceIDPropertyType* resourceIDPropertyType);


KZ_HEADER_END


#endif
