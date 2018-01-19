/**
* \file
* Scene is an object node type that is the root for the 3D part of the scene graph. Scenes can be added only under
* viewport layers. Scene may not have layers or scenes as children.
*
* Scene Messages
* ----
* KzuScene does not send or receive any messages.
*
* Scene Properties
* ----
* ::KZU_PROPERTY_TYPE_COMPOSER_REFERENCE resource ID property specifies the ::KzuComposer for rendering the scene.
*
* ::KZU_PROPERTY_TYPE_SCENE_BACKGROUND_TIMELINE_SEQUENCE resource ID property specifies a ::KzuAnimationItem that is run in the background.
* 
* ::KZU_PROPERTY_TYPE_SCENE_OVERRIDE_CAMERA pointer property specifies a camera that will be used instead of the one specified with the
* ::KZU_PROPERTY_TYPE_SCENE_DEFAULT_CAMERA property.
*
* ::KZU_PROPERTY_TYPE_SCENE_DEFAULT_CAMERA pointer property specifies the camera for viewing the scene.
*
* ::KZU_PROPERTY_TYPE_SCENE_DEFAULT_PICKING_CAMERA pointer property specifies the camera used in picking the objects in the scene.
* When the property is not set, the default camera is used.
*
* ::KZU_PROPERTY_TYPE_SCENE_STARTUP_SCRIPT_FUNCTION_NAME is not used.
*
* \see \ref kzu_viewport_layer.h.
*
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_SCENE_H
#define KZU_SCENE_H


#include <user/scene_graph/kzu_object_common.h>

#include <system/input/kzs_input.h>
#include <system/debug/kzs_error.h>
#include <system/kzs_types.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/** Scene performance measurement constants. */
enum KzuScenePerformanceMeasurement
{
    KZU_SCENE_PERFORMANCE_MEASUREMENT_LAYOUT, /**< Scene measurement for layouting. */
    KZU_SCENE_PERFORMANCE_MEASUREMENT_EXTRACT, /**< Scene measurement for extracting nodes. */
    KZU_SCENE_PERFORMANCE_MEASUREMENT_CONSTRAINTS /**< Scene measurement for applying constraints. */
};


/* Forward declaration structures */
struct KzcDynamicArray;
struct KzcInputStream;
struct KzcMatrix4x4;
struct KzcMemoryManager;
struct KzuBinaryFileInfo;
struct KzuCameraNode;
struct KzuComposer;
struct KzuObjectNode;
struct KzuUIDomain;
struct KzuRenderer;
struct KzuTransformedObjectNode;
struct KzuTransformedScene;
struct KzuUiScreen;
struct KzuFactory;


/**
 * \struct KzuScene
 * Scene is an object node type that is the root for the 3D part of the scene graph. Scenes can be added only under
 * viewport layers. Scene may not have layers or scenes as children.
 */
struct KzuScene;


/** Object type identifier for scene objects. */
extern const KzuObjectType KZU_OBJECT_TYPE_SCENE;


/** Convert scene to object node. */
struct KzuObjectNode* kzuSceneToObjectNode(const struct KzuScene* scene);
/** Convert object node to scene. */
struct KzuScene* kzuSceneFromObjectNode(const struct KzuObjectNode* objectNode);

/** Creates a new scene object. */
kzsError kzuSceneCreate(const struct KzcMemoryManager* memoryManager, kzString name, 
                        struct KzuUIDomain* uiDomain, struct KzuScene** out_scene);

/** Registers scene node type to factory. */
kzsError kzuSceneRegisterToFactory(const struct KzuFactory* factory);


/**
 * Extracts a scene graph, that is, creates a KzuTransformedObjectNode for each KzuObjectNode in the scene.
 * Traverses the object nodes one by one and duplicates their hierarchy into the hierarchy of the transformed object nodes.
 * Also transforms the resulting transformed object nodes to world coordinates.
 * \param memoryManager The memory manager to use for memory allocations.
 * \param scene The KzuScene to traverse.
 * \param transformedScene The KzuTransformedScene to where the resulting transformed object nodes are added.
 *        If the transformed scene has any existing transformed object nodes, those are not removed.
 * \param out_extractedRootNode A pointer that is set to point to the new KzuTransformedObjectNode corresponding to the scene argument.
 */
kzsError kzuSceneExtract(struct KzcMemoryManager* memoryManager, struct KzuScene* scene, struct KzuTransformedScene* transformedScene, struct KzuTransformedObjectNode** out_extractedRootNode);


/** Adds an object node to the scene's children. */
kzsError kzuSceneAddObject(const struct KzuScene* scene, struct KzuObjectNode* objectNode);
/** Removes an object node from the scene's children. */
kzsError kzuSceneRemoveObject(const struct KzuScene* scene, struct KzuObjectNode* objectNode);

/** Get currently active camera (default or override). */
struct KzuCameraNode* kzuSceneGetCurrentCamera(const struct KzuScene* scene);

/** Recursively calculate the layouts in the scene. I.e. calls the measure and arrange functions of every KzuUiComponentNode in the scene. */
kzsError kzuSceneLayout(struct KzuScene* scene);
/** Initial scene arrange. */
kzsError kzuSceneArrangeInitial(struct KzuObjectNode* objectNode);
/** Initial scene measure. */
kzsError kzuSceneMeasureInitial(struct KzuObjectNode* objectNode);
/** Perform layout measurement on a node. */
kzsError kzuSceneMeasureNode(struct KzuObjectNode* node, kzBool* out_changed);
/** Perform layout arrangement on a node. */
kzsError kzuSceneArrangeNode(struct KzuObjectNode* objectNode);

/** Sets constraint apply enabled, enabled by default. Affects on LOOK_AT, FACE_TO_CAMERA, CONSTRAINT_POSITION and CONSTRAINT_ORIENTATION properties. */
void kzuSceneSetConstraintsEnabled(struct KzuScene* scene, kzBool enabled);
/** Returns if scene constraints are enabled. */
kzBool kzuSceneIsConstraintsEnabled(const struct KzuScene* scene);


/** Returns true if scene contains specified object node. */
kzBool kzuSceneContainsObject(const struct KzuScene* scene, const struct KzuObjectNode* objectNode);

/** Gets the value of property ComposerReference in scene. */
struct KzuComposer* kzuSceneGetComposerReference(const struct KzuScene* scene);
/** Sets the value of property ComposerReference in scene. */
kzsError kzuSceneSetComposerReference(struct KzuScene* scene, struct KzuComposer* composer);


/** Tell if an object node is a scene. */
kzBool kzuObjectNodeIsScene(const struct KzuObjectNode* objectNode);


KZ_HEADER_END


#include "kzu_scene_properties.h"


#endif
