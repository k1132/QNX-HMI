/**
* \file
* Specifies property is equal filter.
* Filter that compares object property default value to 
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_PROPERTY_IS_EQUAL_FILTER_H
#define KZU_PROPERTY_IS_EQUAL_FILTER_H


#include <system/kzs_types.h>
#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations */
struct KzcInputStream;
struct KzcMemoryManager;
struct KzuBinaryFileInfo;
struct KzuObjectSource;
struct KzuUIDomain;
struct KzuPropertyType;
struct KzuPropertyManager;


/** Creates property is equal filter. */
kzsError kzuPropertyIsEqualFilterCreate(const struct KzcMemoryManager* memoryManager, struct KzuUIDomain* uiDomain,
                                        kzString name, struct KzuObjectSource** out_objectSource);

/** Loads a property is equal filter from KZB. */
kzsError kzuPropertyIsEqualFilterLoadFromKZB(struct KzuObjectSource* objectSource, struct KzcInputStream* inputStream, const struct KzuBinaryFileInfo* file);

/** Initializes a property is equal filter. 
 * \param propertyType Property type that is used in comparison. Compared property is the one that the filter contains in property manager.
 */
kzsError kzPropertyIsEqualFilterInitialize(struct KzuObjectSource* objectSource, struct KzuObjectSource* input,
                                           struct KzuPropertyManager* propertyManager, const struct KzuPropertyType* propertyType, kzBool isExclusive);


KZ_HEADER_END


#endif
