/**
* \file
* Mesh node representing a 3D mesh. Inherited from KzuObjectNode.
*
* Mesh Node Messages
* ----
* KzuMeshNode does not send or receive any messages.
*
* Mesh Node Properties
* ----
* ::KZU_PROPERTY_TYPE_MESH resource ID property specifies the ::KzuMesh belonging to this node. This mesh is only used if ::KZ_NULL was passed to ::kzuMeshNodeCreate
* as the mesh and the mesh was not set with ::kzuMeshNodeSetMesh.
* 
* ::KZU_PROPERTY_TYPE_DRAWN_AS_BOUNDING_BOX Boolean property specifies whether or not the mesh should be drawn as a bounding box. The default value is ::KZ_FALSE.
*
* Mesh Node Example Code
* ----
* The following code creates a simple 3D box KzuMeshNode.
*
* \code {.c}
*     kzsError result;
*     struct KzuRenderer* renderer = kzuEngineGetRenderer(engine);
*     struct KzuMaterial* material = kzuRendererGetSolidColorMaterial(renderer);
*     struct KzuMesh* boxMesh;
*     struct KzuMeshNode* boxNode;

*     result = kzuMeshCreateBox(resourceManager, "box mesh", 1.0f, 1.0f, 1.0f, material, &boxMesh);
*     kzsErrorForward(result);
*
*     result = kzuMeshNodeCreate(memoryManager, "box node", uiDomain, boxMesh, &boxNode);
*     kzsErrorForward(result);
*
*     // Mesh node has taken a reference to the mesh, release ours.
*     result = kzuResourceRelease(kzuMeshToResource(boxMesh));
*     kzsErrorForward(result);
*
*     // Add the mesh node into the 3D scene.
*     result = kzuObjectNodeAddChild(kzuSceneToObjectNode(scene), kzuMeshNodeToObjectNode(boxNode));
*     kzsErrorForward(result);
*
*     // Do something else.
*
*     // Free memory.
*     result = kzuObjectNodeDelete(kzuMeshNodeToObjectNode(boxNode));
*     kzsErrorForward(result);
* \endcode
*
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_MESH_NODE_H
#define KZU_MESH_NODE_H


#include <user/scene_graph/kzu_object_common.h>

#include <core/util/math/kzc_matrix4x4.h>
#include <core/util/math/kzc_vector3.h>

#include <system/kzs_types.h>
#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declaration structures. */
struct KzcInputStream;
struct KzcMemoryManager;
struct KzuBinaryFileInfo;
struct KzuMesh;
struct KzuObjectNode;
struct KzuUIDomain;
struct KzuFactory;


/**
* \struct KzuMeshNode
* Structure for the mesh node, inherited from KzuObjectNode.
*/
struct KzuMeshNode;


/** Object type identifier for mesh objects. */
extern const KzuObjectType KZU_OBJECT_TYPE_MESH;


/** Creates a new mesh node. */
kzsError kzuMeshNodeCreate(const struct KzcMemoryManager* memoryManager, kzString name,  struct KzuUIDomain* uiDomain, 
                                        struct KzuMesh* mesh, struct KzuMeshNode** out_meshNode);

/** Registers mesh node type to factory. */
kzsError kzuMeshNodeRegisterToFactory(const struct KzuFactory* factory);


/** Sets mesh for mesh node. */
kzsError kzuMeshNodeSetMesh(struct KzuMeshNode* meshNode, struct KzuMesh* mesh);
/** Gets a mesh from mesh node. */
struct KzuMesh* kzuMeshNodeGetMesh(const struct KzuMeshNode* meshNode);
/** Returns mesh node from object node. */
struct KzuMeshNode* kzuMeshNodeFromObjectNode(const struct KzuObjectNode* objectNode);
/** Returns an object node from mesh node. */
struct KzuObjectNode* kzuMeshNodeToObjectNode(const struct KzuMeshNode* meshNode);


KZ_HEADER_END


#endif
