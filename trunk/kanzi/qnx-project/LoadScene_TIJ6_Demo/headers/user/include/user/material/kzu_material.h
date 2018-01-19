/**
* \file
* Specifies material structure and its properties.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_MATERIAL_H
#define KZU_MATERIAL_H


#include <user/resource/kzu_shader.h>

#include <core/util/collection/kzc_dynamic_array.h>
#include <core/util/color/kzc_color.h>

#include <system/kzs_types.h>
#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations */
struct KzcInputStream;
struct KzcMemoryManager;
struct KzuBinaryFileInfo;
struct KzuUIDomain;
struct KzuPropertyManager;
struct KzuPropertyType;
struct KzuShader;


/**
* \struct KzuMaterial
* Structure for material. Contains specific visual properties and material type (shader).
*/
struct KzuMaterial;


/** Resource type identifier for material. */
extern const KzuResourceType KZU_RESOURCE_TYPE_MATERIAL;


/** Allocates memory and returns a new material. */
kzsError kzuMaterialCreate(const struct KzcMemoryManager* memoryManager, struct KzuUIDomain* uiDomain, kzString name, struct KzuMaterial** out_material);
/** Frees the memory allocated for the material. */
kzsError kzuMaterialDelete(struct KzuMaterial* material);

/** Loads material from KZB. */
kzsError kzuMaterialLoadFromKZB(struct KzuMaterial* material, struct KzcInputStream* inputStream, const struct KzuBinaryFileInfo* file);

/** Creates a copy of given material. */
kzsError kzuMaterialCopy(const struct KzcMemoryManager* memoryManager, const struct KzuMaterial* materialToCopy, struct KzuMaterial** out_material);

/** Returns the material property manager. */
struct KzuPropertyManager* kzuMaterialGetPropertyManager(const struct KzuMaterial* material);

/** Returns material name from material. */
kzString kzuMaterialGetName(const struct KzuMaterial* material);

/** Returns shader from material. */
struct KzuShader* kzuMaterialGetShader(const struct KzuMaterial* material);
/** Private function for setting material shader. */
kzsError kzuMaterialSetShader(struct KzuMaterial* material, struct KzuShader* shader);

/** Returns true if material is renderable (located on GPU). */
kzBool kzuMaterialIsRenderable(const struct KzuMaterial* material);

/** Converts material to resource. */
struct KzuResource* kzuMaterialToResource(const struct KzuMaterial* material);
/** Converts material from resource. */
struct KzuMaterial* kzuMaterialFromResource(const struct KzuResource* resource);
/** Casts material from resource, KZ_NULL if invalid type. */
struct KzuMaterial* kzuMaterialCastFromResource(const struct KzuResource* resource);

/** Sets property manager to material. */
void kzuMaterialSetPropertyManager(struct KzuMaterial* material, struct KzuPropertyManager* propertyManager);
/** Sets ui domain to material. */
void kzuMaterialSetUIDomain(struct KzuMaterial* material, struct KzuUIDomain* uiDomain);


KZ_HEADER_END


#endif
