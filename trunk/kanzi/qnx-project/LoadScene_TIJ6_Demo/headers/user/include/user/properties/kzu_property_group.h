/**
* \file
* Property group. Group object that contains set of objects, materials, render passes and scenes, and properties for them.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_PROPERTY_GROUP_H
#define KZU_PROPERTY_GROUP_H


#include <user/resource/kzu_resource_common.h>

#include <system/debug/kzs_error.h>
#include <system/kzs_types.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations */
struct KzcInputStream;
struct KzcMemoryManager;
struct KzuBinaryFileInfo;
struct KzuPropertyManager;
struct KzuResourceManager;


/** 
* \struct KzuPropertyGroup
* Structure for property group, that specifies set of objects and properties.
*/
struct KzuPropertyGroup;


/** Resource type identifier for property group. */
extern const KzuResourceType KZU_RESOURCE_TYPE_PROPERTY_GROUP;


/** Creates new property group. */
kzsError kzuPropertyGroupCreate(const struct KzcMemoryManager* memoryManager, struct KzuPropertyManager* propertyManager,
                                struct KzuResourceManager* resourceManager, kzString name, struct KzuPropertyGroup** out_propertyGroup);
/** Deletes property group. */
kzsError kzuPropertyGroupDelete(struct KzuPropertyGroup* propertyGroup);

/** Loads property group from KZB. */
kzsError kzuPropertyGroupLoadFromKZB(struct KzuPropertyGroup* propertyGroup, struct KzcInputStream* inputStream, const struct KzuBinaryFileInfo* file);


/** Sets property override enabled or disabled. */
void kzuPropertyGroupSetOverrideEnabled(struct KzuPropertyGroup* propertyGroup, kzBool enabled);
/** Returns is property override enabled or not. */
kzBool kzuPropertyGroupIsOverrideEnabled(const struct KzuPropertyGroup* propertyGroup);


/** Sets property manager to property group. For internal use only. */
void kzuPropertyGroupSetPropertyManager(struct KzuPropertyGroup* propertyGroup, struct KzuPropertyManager* propertyManager);


/** Converts state manager to resource. */
struct KzuResource* kzuPropertyGroupToResource(const struct KzuPropertyGroup* propertyGroup);
/** Converts state manager from resource. */
struct KzuPropertyGroup* kzuPropertyGroupFromResource(const struct KzuResource* resource);
/** Casts state manager from resource, KZ_NULL if invalid type. */
struct KzuPropertyGroup* kzuPropertyGroupCastFromResource(const struct KzuResource* resource);


KZ_HEADER_END


#endif
