/**
* \file
* Specifies property that holds multiple properties.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_STRUCT_PROPERTY_H
#define KZU_STRUCT_PROPERTY_H


#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations */
struct KzcInputStream;
struct KzcMemoryManager;
struct KzuBinaryFileInfo;
struct KzuUIDomain;
struct KzuPropertyType;
struct KzuPropertyTypeCollection;


/** 
* \struct KzuStructPropertyType
* Structure for struct property type.
*/
struct KzuStructPropertyType;


/** Creates a new struct property type. */
kzsError kzuStructPropertyTypeCreate(const struct KzcMemoryManager* memoryManager, kzString name, struct KzuStructPropertyType** out_structPropertyType);
/** Deletes struct property type. */
kzsError kzuStructPropertyTypeDelete(struct KzuStructPropertyType* structPropertyType);

/** Loads struct property type from KZB. */
kzsError kzuStructPropertyTypeLoadFromKzb(const struct KzuStructPropertyType* structPropertyType, struct KzcInputStream* inputStream,
                                          const struct KzuBinaryFileInfo* file);


/** Returns struct property type from property type. */
struct KzuStructPropertyType* kzuStructPropertyTypeFromPropertyType(const struct KzuPropertyType* propertyType);
/** Converts struct property type to property type. */
struct KzuPropertyType* kzuStructPropertyTypeToPropertyType(const struct KzuStructPropertyType* structPropertyType);


/** Gets the child property types from struct property type. */
struct KzuPropertyTypeCollection* kzuStructPropertyTypeGetChildren(const struct KzuStructPropertyType* structPropertyType);

/** Adds a child property type to struct property type. */
kzsError kzuStructPropertyTypeAddChild(const struct KzuStructPropertyType* structPropertyType, const struct KzuPropertyType* childPropertyType);


KZ_HEADER_END


#endif
