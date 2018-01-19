/**
* \file
* Specifies property that holds multiple properties.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_ARRAY_PROPERTY_H
#define KZU_ARRAY_PROPERTY_H


#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations */
struct KzcInputStream;
struct KzcMemoryManager;
struct KzuBinaryFileInfo;
struct KzuPropertyType;
struct KzuPropertyTypeCollection;
struct KzuUIDomain;


/** 
* \struct KzuArrayPropertyType
* Arrayure for array property type.
*/
struct KzuArrayPropertyType;


/** Unlimited size for array property. This can be used as the elementCount for kzuArrayPropertyTypeCreate(). */
#define KZU_ARRAY_PROPERTY_TYPE_UNLIMITED_SIZE -1


/**
 * Creates a new array property type.
 * \param elementCount Number of elements in the array or KZU_ARRAY_PROPERTY_TYPE_UNLIMITED_SIZE for unlimited.
 */
kzsError kzuArrayPropertyTypeCreate(const struct KzcMemoryManager* memoryManager, kzString name,
                                    const struct KzuPropertyType* childPropertyType, kzInt elementCount,
                                    struct KzuArrayPropertyType** out_arrayPropertyType);
/** Deletes array property type. */
kzsError kzuArrayPropertyTypeDelete(struct KzuArrayPropertyType* arrayPropertyType);

/** Loads string property type from KZB. */
kzsError kzuArrayPropertyTypeLoadFromKzb(struct KzuArrayPropertyType* arrayPropertyType, struct KzcInputStream* inputStream,
                                         const struct KzuBinaryFileInfo* file);


/** Returns array property type from property type. */
struct KzuArrayPropertyType* kzuArrayPropertyTypeFromPropertyType(const struct KzuPropertyType* propertyType);
/** Converts array property type to property type. */
struct KzuPropertyType* kzuArrayPropertyTypeToPropertyType(const struct KzuArrayPropertyType* arrayPropertyType);


/** Gets the child property type from array property type. */
const struct KzuPropertyType* kzuArrayPropertyTypeGetChildPropertyType(const struct KzuArrayPropertyType* arrayPropertyType);

/** Sets child property type for array property type. */
void kzuArrayPropertyTypeSetChildPropertyType(struct KzuArrayPropertyType* arrayPropertyType, const struct KzuPropertyType* childPropertyType);

/** Gets the number of elements from array property type, or -1 for unlimited. */
kzInt kzuArrayPropertyTypeGetElementCount(const struct KzuArrayPropertyType* arrayPropertyType);


KZ_HEADER_END


#endif
