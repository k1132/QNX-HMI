/**
* \file
* Specifies color property.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_COLOR_PROPERTY_H
#define KZU_COLOR_PROPERTY_H


#include <core/util/color/kzc_color.h>

#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations */
struct KzcInputStream;
struct KzcMemoryManager;
struct KzuPropertyType;


/** 
* \struct KzuColorPropertyType
* Structure for color property type.
*/
struct KzuColorPropertyType;


/** Creates color property type. */
kzsError kzuColorPropertyTypeCreate(const struct KzcMemoryManager* memoryManager, kzString name, struct KzcColorRGBA defaultValue,
                                    struct KzuColorPropertyType** out_colorPropertyType);
/** Deletes color property type. */
kzsError kzuColorPropertyTypeDelete(struct KzuColorPropertyType* colorPropertyType);

/** Loads color property type from KZB. */
kzsError kzuColorPropertyTypeLoadFromKzb(struct KzuColorPropertyType* colorPropertyType, struct KzcInputStream* inputStream);


/** Converts property type to color property type */
struct KzuColorPropertyType* kzuColorPropertyTypeFromPropertyType(const struct KzuPropertyType* propertyType);
/** Converts color property type to property type. */
struct KzuPropertyType* kzuColorPropertyTypeToPropertyType(const struct KzuColorPropertyType* colorPropertyType);

/** Gets the default value of color property type. */
struct KzcColorRGBA kzuColorPropertyTypeGetDefaultValue(const struct KzuColorPropertyType* colorPropertyType);


KZ_HEADER_END


#endif
