/**
* \file
* Specifies matrix2x2 property.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_MATRIX2X2_PROPERTY_H
#define KZU_MATRIX2X2_PROPERTY_H


#include <core/util/math/kzc_matrix2x2.h>

#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations */
struct KzcInputStream;
struct KzcMemoryManager;
struct KzuPropertyType;


/** 
* \struct KzuMatrix2x2PropertyType
* Structure for matrix2x2 property type.
*/
struct KzuMatrix2x2PropertyType;


/** Creates a new matrix property type. */
kzsError kzuMatrix2x2PropertyTypeCreate(const struct KzcMemoryManager* memoryManager, kzString name, struct KzcMatrix2x2 defaultValue,
                                        struct KzuMatrix2x2PropertyType** out_matrix2x2PropertyType);
/** Deletes matrix property type. */
kzsError kzuMatrix2x2PropertyTypeDelete(struct KzuMatrix2x2PropertyType* matrix2x2PropertyType);

/** Loads matrix property type from KZB. */
kzsError kzuMatrix2x2PropertyTypeLoadFromKzb(struct KzuMatrix2x2PropertyType* matrix2x2PropertyType, struct KzcInputStream* inputStream);


/** Returns matrix property type from property type. */
struct KzuMatrix2x2PropertyType* kzuMatrix2x2PropertyTypeFromPropertyType(const struct KzuPropertyType* propertyType);
/** Returns property type from matrix property type. */
struct KzuPropertyType* kzuMatrix2x2PropertyTypeToPropertyType(const struct KzuMatrix2x2PropertyType* matrix2x2PropertyType);

/** Gets the default value of matrix property type. */
struct KzcMatrix2x2 kzuMatrix2x2PropertyTypeGetDefaultValue(const struct KzuMatrix2x2PropertyType* matrix2x2PropertyType);


KZ_HEADER_END


#endif
