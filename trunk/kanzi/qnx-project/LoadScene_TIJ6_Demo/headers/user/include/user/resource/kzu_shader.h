/**
 * \file
 * Shader.
 * 
 * Copyright 2008-2014 by Rightware. All rights reserved.
 */
#ifndef KZU_SHADER_H
#define KZU_SHADER_H


#include "kzu_resource_common.h"

#include <core/util/collection/kzc_dynamic_array.h>
#include <core/util/collection/kzc_hash_map.h>


KZ_HEADER_BEGIN


/* Forward declarations */
struct KzcMemoryManager;
struct KzuGPUResource;
struct KzuPropertyType;
struct KzuResourceLoader;
struct KzuResourceManager;
struct KzuStructPropertyType;
struct KzuFactory;


/**
 * \struct KzuShader
 * Shader GPU resource.
 */
struct KzuShader;


/** Resource type identifier for shader. */
extern const KzuResourceType KZU_RESOURCE_TYPE_SHADER;


/** Light container in shader. */
struct KzuShaderLightContainer
{
    struct KzuStructPropertyType* lightType; /**< Light property type. */
    kzUint lightCount; /**< Number of lights. */
    struct KzcDynamicArray* uniformLocations; /**< Uniform locations. */
};


/** Creates a shader that loads the data when needed using the given resource loader. */
kzsError kzuShaderCreate(const struct KzuResourceManager* resourceManager, kzString name, struct KzuResourceLoader* loader,
                         struct KzuShader** out_shader);

/** Registers shader type to factory. */
kzsError kzuShaderRegisterToFactory(const struct KzuFactory* factory);

/** Creates a shader with the given vertex and fragment shader strings and given vertex attributes. */
kzsError kzuShaderCreateFromMemory(const struct KzuResourceManager* resourceManager, kzString name,
                                   kzString vertexShader, kzString fragmentShader,
                                   kzUint vertexAttributeCount, const kzString* vertexAttribute,
                                   struct KzuShader** out_shader);

/**
 * Initializes a shader with the given vertex and fragment shader strings and given vertex attributes.
 * Calling this function is safe only from a resource loader passed as an argument to kzuShaderCreate().
 *
 * \see kzuShaderCreate for creating the shader.
 */
kzsError kzuShaderInitializeFromMemory(struct KzuShader* shader, kzString vertexShader, kzString fragmentShader,
                                       kzUint vertexAttributeCount, const kzString* vertexAttributes);


/** Converts shader to GPU resource. */
struct KzuGPUResource* kzuShaderToGPUResource(const struct KzuShader* shader);
/** Converts GPU resource to shader. */
struct KzuShader* kzuShaderFromGPUResource(const struct KzuGPUResource* gpuResource);
/** Converts shader to resource. */
struct KzuResource* kzuShaderToResource(const struct KzuShader* shader);
/** Converts resource to shader. */
struct KzuShader* kzuShaderFromResource(const struct KzuResource* resource);
/** Casts shader from resource, KZ_NULL if invalid type. */
struct KzuShader* kzuShaderCastFromResource(const struct KzuResource* resource);


/** Adds property type to shader. */
kzsError kzuShaderAddPropertyType(struct KzuShader* shader, const struct KzuPropertyType* propertyType);
/** Removes property type from shader. */
kzsError kzuShaderRemovePropertyType(const struct KzuShader* shader, const struct KzuPropertyType* propertyType);
/** Assigns lights for shader. */
kzsError kzuShaderAddLightType(struct KzuShader* shader, const struct KzuStructPropertyType* propertyType);
/** Removes lights from shader. */
kzsError kzuShaderRemoveLightType(const struct KzuShader* shader, const struct KzuStructPropertyType* propertyType);

/** Gets property type from shader by name. Returns KZ_NULL if not found. */
const struct KzuPropertyType* kzuShaderGetPropertyTypeByName(const struct KzuShader* shader, kzString propertyTypeName);

/** Returns all property types from shader. <PropertyType>. */
struct KzcDynamicArrayIterator kzuShaderGetPropertyTypes(const struct KzuShader* shader);
/** Returns all light types from shader. <KzuShaderLightContainer>. */
struct KzcDynamicArrayIterator kzuShaderGetLightTypes(const struct KzuShader* shader);


/** Returns true if the shader is deployed and valid. */
kzBool kzuShaderIsRenderable(const struct KzuShader* shader);

/** Gets vertex attributes from shader. <kzString(attributeName), kzUint(attributeIndex)>. */
struct KzcHashMapIterator kzuShaderGetVertexAttributes(const struct KzuShader* shader);

/** Binds the shader for rendering. */
kzsError kzuShaderBind(const struct KzuShader* shader);
/** Gets uniform location from shader object based on index in the property collection. Uses caching if possible. */
kzsError kzuShaderGetUniformLocation(const struct KzuShader* shader, kzUint index, kzInt* out_location);
/** Gets uniform location for light property type from shader object based on index in the property collection. Uses caching if possible. */
kzsError kzuShaderGetLightUniformLocation(const struct KzuShader* shader, kzUint lightIndex, kzUint lightPropertyTypeIndex, kzInt* out_location);
/** Gets uniform location in buffer. */
kzBool kzuShaderGetUniformBufferLocation(const struct KzuShader* shader, kzUint index, kzInt* out_offset, kzByte** out_data, kzUint* out_uniformBufferHandle);
/** Returns texture specific uniform locations form shader. */
kzsError kzuShaderGetTextureUniformLocation(struct KzuShader* shader, kzString textureName, kzUint textureUnit,
                                            kzInt* out_textureLocation, kzInt* out_textureWidthUniformLocation,
                                            kzInt* out_textureHeightUniformLocation);


KZ_HEADER_END


#endif
