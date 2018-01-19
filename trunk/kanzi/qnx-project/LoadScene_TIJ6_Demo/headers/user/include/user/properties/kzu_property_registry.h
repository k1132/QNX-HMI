/**
 * \file
 * Property registry.
 * 
 * Copyright 2008-2014 by Rightware. All rights reserved.
 */
#ifndef KZU_PROPERTY_REGISTRY
#define KZU_PROPERTY_REGISTRY


#include <system/kzs_types.h>
#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations */
struct KzuPropertyType;
struct KzcMemoryManager;


/** Creates property registry. */
kzsError kzuPropertyRegistryCreate(const struct KzcMemoryManager* memoryManager);

/** Deletes all fixed properties. */
kzsError kzuPropertyRegistryDelete(void);

/** Marks all currently registered property types as read-only. This means that .KZB files cannot overwrite any of their data later on. */
kzsError kzuPropertyRegistryLockPropertyTypes(void);

/** Finds a fixed property type by name. */
struct KzuPropertyType* kzuPropertyRegistryFindPropertyType(kzString name);

/**
 * Register a property type in fixed properties. After a property type is registered to fixed properties,
 * it is possible to find it by its name.
 */
kzsError kzuPropertyRegistyAddPropertyType(const struct KzuPropertyType* propertyType);


KZ_HEADER_END


#endif
