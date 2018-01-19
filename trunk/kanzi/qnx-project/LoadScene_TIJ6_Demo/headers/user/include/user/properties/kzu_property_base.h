/**
* \file
* Property private members.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_PROPERTY_BASE_H
#define KZU_PROPERTY_BASE_H


#include "kzu_property_common.h"

#include <system/debug/kzs_error.h>
#include <system/kzs_types.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations. */
struct KzcMemoryManager;
struct KzuColorPropertyType;


/** Base structure for property type. */
struct KzuPropertyType
{
    kzMutableString name;                /**< Name of the property type. */
    enum KzuPropertyDataType dataType;   /**< Datatype for property type. */
    kzBool inherited;                    /**< Is the property inherited by default. */
    kzU32 changeFlags;                   /**< Change flags set on an object where a property of this type is set. */
    kzUint index;                        /**< Index of the property type in property manager lookup-table. */
    kzBool readOnly;                     /**< Read-only properties cannot be changed afterwards. */
};


/** Creates a property type. */
kzsError kzuPropertyTypeCreate_protected(const struct KzcMemoryManager* memoryManager, enum KzuPropertyDataType dataType,
                                         kzString name, struct KzuPropertyType* propertyType);

/** Deletes the base structure of property type. */
kzsError kzuPropertyTypeDeleteBase_protected(struct KzuPropertyType* propertyType);


KZ_HEADER_END


#endif
