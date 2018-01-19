/**
 * \file
 * Mesh.
 * 
 * Copyright 2008-2014 by Rightware. All rights reserved.
 */
#ifndef KZU_MESH_H
#define KZU_MESH_H


#include "kzu_resource_common.h"

#include <core/renderer/kzc_renderer.h>


KZ_HEADER_BEGIN


/* Forward declarations. */
struct KzcDynamicArray;
struct KzcMemoryManager;
struct KzuGPUResource;
struct KzuMaterial;
struct KzuBoundingVolume;
struct KzuPropertyManager;
struct KzuResourceLoader;
struct KzuResourceManager;
struct KzuShader;
struct KzuObjectNode;
struct KzuFactory;


/**
 * \struct KzuMesh
 * Mesh GPU resource.
 */
struct KzuMesh;


/** Resource type identifier for mesh. */
extern const KzuResourceType KZU_RESOURCE_TYPE_MESH;


/** Vertex attribute semantic. This specifies the meaning of a vertex attribute. */
enum KzuMeshVertexAttributeSemantic
{
    KZU_MESH_VERTEX_ATTRIBUTE_SEMANTIC_POSITION, /**< Position vertex attribute semantic. */
    KZU_MESH_VERTEX_ATTRIBUTE_SEMANTIC_NORMAL, /**< Normal vertex attribute semantic. */
    KZU_MESH_VERTEX_ATTRIBUTE_SEMANTIC_TANGENT, /**< Tangent vertex attribute semantic. */
    KZU_MESH_VERTEX_ATTRIBUTE_SEMANTIC_TEXTURE_COORDINATE, /**< Texture coordinate vertex attribute semantic. */
    KZU_MESH_VERTEX_ATTRIBUTE_SEMANTIC_COLOR, /**< Color vertex attribute semantic. */
    KZU_MESH_VERTEX_ATTRIBUTE_SEMANTIC_WEIGHT, /**< Weight vertex attribute semantic. */
    KZU_MESH_VERTEX_ATTRIBUTE_SEMANTIC_MATRIX_PALETTE, /**< Matrix palette vertex attribute semantic. */
    KZU_MESH_VERTEX_ATTRIBUTE_SEMANTIC_CUSTOM /**< Custom vertex attribute semantic. */
};

/** Vertex attribute data type. */
enum KzuMeshVertexAttributeDataType
{
    KZU_MESH_VERTEX_ATTRIBUTE_DATA_TYPE_S8, /**< Signed 8-bit integer data type. */
    KZU_MESH_VERTEX_ATTRIBUTE_DATA_TYPE_U8, /**< Unsigned 8-bit integer data type. */
    KZU_MESH_VERTEX_ATTRIBUTE_DATA_TYPE_S16, /**< Signed 16-bit integer data type. */
    KZU_MESH_VERTEX_ATTRIBUTE_DATA_TYPE_U16, /**< Unigned 16-bit integer data type. */
    KZU_MESH_VERTEX_ATTRIBUTE_DATA_TYPE_S32, /**< Signed 32-bit integer data type. */
    KZU_MESH_VERTEX_ATTRIBUTE_DATA_TYPE_U32, /**< Unsigned 32-bit integer data type. */
    KZU_MESH_VERTEX_ATTRIBUTE_DATA_TYPE_FLOAT16, /**< 16-bit floating point data type. Not supported by all hardware. */
    KZU_MESH_VERTEX_ATTRIBUTE_DATA_TYPE_FLOAT32 /**< Normal 32-bit floating point data type. */
};


/** Creates a mesh that loads the data when needed using the given resource loader. */
kzsError kzuMeshCreate(const struct KzuResourceManager* resourceManager, kzString name, struct KzuResourceLoader* loader,
                       struct KzuMesh** out_mesh);

/** Registers mesh node type to factory. */
kzsError kzuMeshRegisterToFactory(const struct KzuFactory* factory);

/**
 * Creates a mesh directly from the given data.
 * Mesh consists of vertex attributes, vertex data and Clusters.
 *
 * Each vertex attribute has:
 *  - Name (e.g. kzPosition), which should match the vertex attribute in the shader.
 *  - Semantic, which specifies the type of the attribute, e.g. position or normal. This can be used instead of the name to bind the vertex attribute to known Kanzi shader vertex attributes.
 *  - DataType, which specifies the data format of the attribute, e.g. 32-bit float.
 *  - Dimension, which specifies the number of elements in the attribute, e.g. 3 for vec3 attributes.
 *
 * Vertex data is an array of data in the following format:
 *  - vertexData = <vertex_0><vertex_1>...<vertex_N-1>, where N is vertexCount
 *  -     vertex = <attribute_0><attribute_1>...<attribute_N-1>, where N is vertexAttributeCount
 *  -  attribute = <element_0><element_1>...<element_N-1>, where N is dimension of the attribute
 *  -    element = Data in the format specified by data type of the attribute, e.g. kzFloat.
 *
 * Each cluster has:
 *  - IndexCount, which specifies how many vertex indices the cluster has.
 *  - Indices, which is an array of indices.
 *  - Type, which specifies how rendering should handle the index data, e.g. each group of 3 vertices to form a triangle.
 *  - Material, which specifies the material used for rendering the mesh cluster.
 */
kzsError kzuMeshCreateFromMemory(const struct KzuResourceManager* resourceManager, kzString name, 
                                 kzUint vertexAttributeCount, const kzString* vertexAttributeNames,
                                 const enum KzuMeshVertexAttributeSemantic* vertexAttributeSemantics,
                                 const enum KzuMeshVertexAttributeDataType* vertexAttributeDataTypes,
                                 const kzUint* vertexAttributeDimensions, kzUint vertexCount, const kzByte* vertexData,
                                 kzUint clusterCount, const kzUint* clusterIndexCounts, const kzU16* const* clusterIndices,
                                 const enum KzcPrimitiveType* clusterTypes, struct KzuMaterial* const* clusterMaterials,
                                 struct KzuMesh** out_mesh);

/** Creates a sphere mesh. */
kzsError kzuMeshCreateSphere(const struct KzuResourceManager* resourceManager, kzString name, kzFloat radius, 
                             kzUint segmentCount, kzUint rowCount, struct KzuMaterial* material,
                             struct KzuMesh** out_mesh);

/** Creates a box mesh. */
kzsError kzuMeshCreateBox(const struct KzuResourceManager* resourceManager, kzString name, kzFloat width, 
                          kzFloat height, kzFloat depth, struct KzuMaterial* material,
                          struct KzuMesh** out_mesh);

/** Creates a copy of an existing mesh. The source mesh will be loaded if the data is not yet available. */
kzsError kzuMeshCreateCopy(const struct KzuResourceManager* resourceManager, kzString name, const struct KzuMesh* sourceMesh, struct KzuMesh** out_mesh);

/**
 * Initializes a mesh with the given data.
 * Calling this function is safe only from a resource loader passed as an argument to kzuMeshCreate().
 *
 * \see kzuMeshCreate for creating the mesh.
 * \see kzuMeshCreateFromMemory for documentation of parameters.
 */
kzsError kzuMeshInitializeFromMemory(struct KzuMesh* mesh, kzUint vertexAttributeCount, const kzString* vertexAttributeNames,
                                     const enum KzuMeshVertexAttributeSemantic* vertexAttributeSemantics,
                                     const enum KzuMeshVertexAttributeDataType* vertexAttributeDataTypes,
                                     const kzUint* vertexAttributeDimensions, kzUint vertexCount, const kzByte* vertexData,
                                     kzUint clusterCount, const kzUint* clusterIndexCounts, const kzU16* const* clusterIndices,
                                     const enum KzcPrimitiveType* clusterTypes, struct KzuMaterial* const* clusterMaterials);


/** Converts mesh to GPU resource. */
struct KzuGPUResource* kzuMeshToGPUResource(const struct KzuMesh* mesh);
/** Converts GPU resource to mesh. */
struct KzuMesh* kzuMeshFromGPUResource(const struct KzuGPUResource* gpuResource);
/** Converts mesh to resource. */
struct KzuResource* kzuMeshToResource(const struct KzuMesh* mesh);
/** Converts resource to mesh. */
struct KzuMesh* kzuMeshFromResource(const struct KzuResource* resource);
/** Casts mesh from resource, KZ_NULL if invalid type. */
struct KzuMesh* kzuMeshCastFromResource(const struct KzuResource* resource);


/** Returns true if the mesh is deployed and valid. */
kzBool kzuMeshIsRenderable(const struct KzuMesh* mesh);

/** Binds a cluster of the mesh for rendering. */
kzsError kzuMeshBind(const struct KzuMesh* mesh, kzUint clusterIndex, const struct KzuShader* shader);

/** Unbinds the mesh from rendering. */
kzsError kzuMeshUnbind(struct KzuMesh* mesh, const struct KzuShader* shader);

/** Gets bounding volume from mesh. */
kzsError kzuMeshGetBoundingVolume(const struct KzuMesh* mesh, struct KzuBoundingVolume** out_boundingVolume);

/** Gets the number of vertices in a mesh. */
kzUint kzuMeshGetVertexCount(const struct KzuMesh* mesh);

/** Returns the number of vertex attribute in a mesh. */
kzUint kzuMeshGetVertexAttributeCount(const struct KzuMesh* mesh);

/**
 * Returns information about a vertex attribute with the given index. Any of the output parameters can be KZ_NULL.
 * \see kzuMeshCreateFromMemory
 */
kzsError kzuMeshGetVertexAttributeInfo(const struct KzuMesh* mesh, kzUint index, kzString* out_name,
                                       enum KzuMeshVertexAttributeSemantic* out_semantic,
                                       enum KzuMeshVertexAttributeDataType* out_dataType,
                                       kzUint* out_dimension, kzUint* out_offset, kzUint* out_size);

/** Returns the data size of a single vertex. This is the sum of all vertex attribute sizes. */
kzUint kzuMeshGetVertexSize(const struct KzuMesh* mesh);

/**
 * Returns the vertex data of the mesh. The size of the data is kzuMeshGetVertexCount(mesh) * kzuMeshGetVertexSize(mesh).
 * \see kzuMeshCreateFromMemory
 */
const kzByte* kzuMeshGetVertexData(const struct KzuMesh* mesh);

/** Gets the number of clusters in the mesh. */
kzUint kzuMeshGetClusterCount(const struct KzuMesh* mesh);

/** Gets the number of indices of a given cluster in a mesh. */
kzUint kzuMeshGetIndexCount(const struct KzuMesh* mesh, kzUint clusterIndex);

/** Returns the index data of a given cluster in a mesh. */
const kzU16* kzuMeshGetIndices(const struct KzuMesh* mesh, kzUint clusterIndex);

/** Returns the cluster type of a given cluster in a mesh. */
enum KzcPrimitiveType kzuMeshGetClusterType(const struct KzuMesh* mesh, kzUint clusterIndex);

/** Gets the material of a given cluster in a mesh. */
struct KzuMaterial* kzuMeshGetMaterial(const struct KzuMesh* mesh, kzUint clusterIndex);

/** Sets the material of a given cluster in a mesh. */
kzsError kzuMeshSetMaterial(const struct KzuMesh* mesh, kzUint clusterIndex, struct KzuMaterial* material);

/** Applies morphing by calculating dynamic vertex attributes based on morph properties. */
kzsError kzuMeshApplyMorph(struct KzuMesh* mesh, const struct KzcMemoryManager* quickMemoryManager);

/** Applies mesh skeleton (bones). */
kzsError kzuMeshApplySkeleton(const struct KzuMesh* mesh, const struct KzuObjectNode* baseNode, const struct KzcMemoryManager* quickMemoryManager,
                              const struct KzcDynamicArray* transformedObjectList);
/** Updates the bounding box of a mesh based on the mesh skeleton and current pose. */
kzsError kzuMeshUpdateBoundingBox(const struct KzuMesh* mesh, struct KzuObjectNode* baseNode, const struct KzcDynamicArray* transformedObjectList,
                                  kzBool* out_isSkinned);

/** Returns the number of bones in a mesh skeleton. */
kzUint kzuMeshGetBoneCount(const struct KzuMesh* mesh);

/** Returns the bone node of a given bone in a mesh skeleton. */
struct KzuObjectNode* kzuMeshGetBoneNode(const struct KzuMesh* mesh, kzUint boneIndex);

/** Returns the child joint node of a given bone in a mesh skeleton. */
struct KzuObjectNode* kzuMeshGetBoneChildJoint(const struct KzuMesh* mesh, kzUint boneIndex);

/** Attach bone node for the mesh. */
kzsError kzuMeshAttach(struct KzuMesh* mesh, struct KzuObjectNode* baseNode);
/** Detach bone node for the mesh. */
kzsError kzuMeshDetach(const struct KzuMesh* mesh);

/**
 * Sets the property manager of the mesh.
 * Warning: This function is deprecated and will be removed in future release.
 */
void kzuMeshSetPropertyManager(struct KzuMesh* mesh, struct KzuPropertyManager* propertyManager);

/** 
 * Returns array of shaders having attribute mappings in this mesh.
 * Caller of this function should delete returned array after use.
 */
kzsError kzuMeshGetMappedShaders(const struct KzuMesh* mesh, struct KzcDynamicArray** out_mappedShaders);

/** Removes attribute mapping for the shader. Nothing will happen if there is no mapping for this shader */
kzsError kzuMeshRemoveAttributeMappingForShader(const struct KzuMesh* mesh, const struct KzuShader* shader);
/** Replaces attribute mapping for the shader. Nothing will happen if there is no mapping for this shader */
kzsError kzuMeshReplaceAttributeMappingForShader(const struct KzuMesh* mesh, const struct KzuShader* shader, const struct KzuShader* newShader);

/** Sets attribute mapping for the shader attribute. */
kzsError kzuMeshSetAttributeMapping(const struct KzuMesh* mesh, const struct KzuShader* shader, kzString shaderAttribute, 
                                    const struct KzuMesh* targetMesh, kzUint attributeIndex);

/** Gets attribute mapping for shader attribute. Returns KZ_TRUE if mapping has been found. */
kzBool kzuMeshGetAttributeMapping(const struct KzuMesh* mesh, const struct KzuShader* shader, kzString shaderAttribute, 
                                  const struct KzuMesh** out_targetMesh, kzUint* out_attributeIndex);

/** Removes attribute mapping for shader attribute. */
kzsError kzuMeshRemoveAttributeMapping(const struct KzuMesh* mesh, const struct KzuShader* shader, kzString shaderAttribute);


KZ_HEADER_END


#endif
