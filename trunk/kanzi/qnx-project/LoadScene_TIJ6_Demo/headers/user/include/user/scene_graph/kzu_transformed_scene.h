/**
* \file
* Transformed scene object. Transformed scene is extracted from a scene object.
* After extracting it holds all the data needed to perform updates and to render the scene.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_TRANSFORMED_SCENE_H
#define KZU_TRANSFORMED_SCENE_H


#include <system/debug/kzs_error.h>
#include <system/kzs_types.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations */
struct KzcMemoryManager;
struct KzuCameraNode;
struct KzuLayer;
struct KzuObjectSourceRuntimeData;
struct KzuScene;
struct KzuViewportLayer;
struct KzuTransformedObjectNode;


/**
* \struct KzuTransformedScene
* Structure to hold transformed scene state.
*/
struct KzuTransformedScene;


/** Create a new transformed scene object. */
kzsError kzuTransformedSceneCreate(const struct KzcMemoryManager* memoryManager, struct KzuTransformedScene** out_scene);
/** Delete a transformed scene object. */
kzsError kzuTransformedSceneDelete(struct KzuTransformedScene* transformedScene);

/** Generates a transformed scene from a scene. */
kzsError kzuTransformedSceneExtract(struct KzuTransformedScene* transformedScene, struct KzuScene* scene);
/** Generates a transformed scene from a scene under a viewport layer. */
kzsError kzuTransformedSceneExtractFromViewportLayer(struct KzuTransformedScene* transformedScene, const struct KzuViewportLayer* viewportLayer);
/** Generates a transformed scene from a layer. */
kzsError kzuTransformedSceneExtractFromLayer(struct KzuTransformedScene* transformedScene, const struct KzuLayer* layer);

/** Get the camera that was determined to be used when rendering this transformed scene. */
struct KzuCameraNode* kzuTransformedSceneGetCamera(const struct KzuTransformedScene* transformedScene);
/** Get the composer that was determined to be used when rendering this transformed scene. */
struct KzuComposer* kzuTransformedSceneGetComposer(const struct KzuTransformedScene* transformedScene);
/** Get the scene that was used to generate the transformed scene. */
struct KzuScene* kzuTransformedSceneGetScene(const struct KzuTransformedScene* transformedScene);
/** Get the transformed object array KzcDynamicArray<struct KzuTransformedObjectNode*>. */
struct KzcDynamicArray* kzuTransformedSceneGetObjects(const struct KzuTransformedScene* transformedScene);
/** Get the transformed root object node. */
struct KzuTransformedObjectNode* kzuTransformedSceneGetRootNode(const struct KzuTransformedScene* transformedScene);

/** Get the object source runtime data. */
struct KzuObjectSourceRuntimeData* kzuTransformedSceneGetObjectSourceRuntimeData(const struct KzuTransformedScene* transformedScene);

/** Get current transformed camera node. */
struct KzuTransformedObjectNode* kzuTransformedSceneResolveHitTestCameraNode(const struct KzuTransformedScene* transformedScene);

/** Sets view camera of transformed scene. */
void kzuTransformedSceneSetExtractedViewCamera(struct KzuTransformedScene* transformedScene, struct KzuTransformedObjectNode* transformedObjectNode);
/** Gets view camera of transformed scene. */
struct KzuTransformedObjectNode* kzuTransformedSceneGetExtractedViewCamera(const struct KzuTransformedScene* transformedScene);


KZ_HEADER_END


#endif
