/**
* \file
* Orbit camera utility. A utility for rotating camera around point of interest.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_ORBIT_CAMERA_H
#define KZU_ORBIT_CAMERA_H


#include <user/preview/kzu_preview_camera_system_base.h>

#include <system/debug/kzs_error.h>
#include <system/kzs_types.h>
#include <system/input/kzs_input.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations */
struct KzuCameraNode;
struct KzuObjectNode;
struct KzuCamera;
struct KzuScene;
struct KzuRenderer;
struct KzcMemoryManager;
struct KzuTransformedScene;
struct KzcDynamicArray;
struct KzcMatrix4x4;
struct KzcVector3;
struct KzuUIDomain;
struct KzuCameraTransformationAttributes;


/**
* \struct KzuOrbitCamera
* Structure for orbit camera object, that is, camera utility for rotating around arbitrary POIs.
*/
struct KzuOrbitCamera;


/** Creates a new orbit camera object with a default camera in origin. */
kzsError kzuOrbitCameraCreate(const struct KzcMemoryManager* memoryManager, struct KzuUIDomain* uiDomain,
                              struct KzuOrbitCamera** out_orbitCamera);

/** Deletes orbit camera object. */
kzsError kzuOrbitCameraDelete(struct KzuOrbitCamera* orbitCamera);

/** Returns world matrix from orbit camera position and orientation. */
void kzuOrbitCameraInitializeMatrix(const struct KzuOrbitCamera* orbitCamera, struct KzcMatrix4x4* out_worldMatrix);

/** Returns camera node from orbit camera. */
struct KzuCameraNode* kzuOrbitCameraGetCameraNode(const struct KzuOrbitCamera* orbitCamera);

/** Updates orbit camera, delta time in milliseconds. */
kzsError kzuOrbitCameraUpdate(struct KzuOrbitCamera* orbitCamera, kzUint deltaTime);
/** Renders orbit camera specific elements */
kzsError kzuOrbitCameraRender(const struct KzuOrbitCamera* orbitCamera, struct KzuRenderer* renderer);

/** Tell if orbit camera is active. */
kzBool kzuOrbitCameraIsActive(const struct KzuOrbitCamera* orbitCamera);
/** Replaces the view camera in a scene with this. */
kzsError kzuOrbitCameraReplace(struct KzuOrbitCamera* orbitCamera, const struct KzuScene* scene, const struct KzuObjectNode* viewCameraNode, const struct KzcMatrix4x4* parentWorldTransformation, const struct KzcMatrix4x4* viewCameraTransformation);
/** Replaces the view camera in a scene with this taking into account transformation attributes. */
kzsError kzuOrbitCameraReplaceWithTransformationAttributes(struct KzuOrbitCamera* orbitCamera, const struct KzuScene* scene, const struct KzcMatrix4x4* parentWorldTransformation, const struct KzuCameraTransformationAttributes* attributes);

/** Get attached scene object from orbit camera. */
struct KzuObjectNode* kzuOrbitCameraGetAttachedSceneObject(const struct KzuOrbitCamera* orbitCamera);
/** Restores the view camera previously replaced by this orbit camera. */
kzsError kzuOrbitCameraRestoreReplacedCamera(const struct KzuOrbitCamera* orbitCamera);

/** Handles orbit camera key events. */
kzsError kzuOrbitCameraHandleKeyEvents(struct KzuOrbitCamera* orbitCamera, enum KzsInputKey keyCode, enum KzsInputKeyDeviceState keyState);
/** Handles orbit camera pointing device events. */
kzsError kzuOrbitCameraHandlePointingDeviceEvents(struct KzuOrbitCamera* orbitCamera, kzU32 buttons, enum KzsInputPointingDeviceState state, kzInt mouseX, kzInt mouseY);
/** Handles orbit camera window events. */
kzsError kzuOrbitCameraHandleWindowEvent(struct KzuOrbitCamera* orbitCamera, enum KzsEventType eventType);

/** Sets orbit camera freezed / unfreezed. */
void kzuOrbitCameraSetFreezed(struct KzuOrbitCamera* orbitCamera, kzBool freezed);
/** Checks if orbit camera is freezed. */
kzBool kzuOrbitCameraIsFreezed(const struct KzuOrbitCamera* orbitCamera);

/** Focuses orbit camera to specified object node list. NodePaths is list of object node paths in project. */
kzsError kzuOrbitCameraFocusToSelection(struct KzuOrbitCamera* orbitCamera, const struct KzcDynamicArray* nodePaths, const struct KzuTransformedScene* transformedScene);
/** Reverts the orbit camera focus. */
kzsError kzuOrbitCameraRevertFocus(struct KzuOrbitCamera* orbitCamera);

/** Gets orbit camera transformation, including the parent inverse multiplied. */
void kzuOrbitCameraGetTransformation(const struct KzuOrbitCamera* orbitCamera, kzBool considerParent, struct KzcMatrix4x4* out_matrix);
/** Gets orbit camera's parent transformation. */
void kzuOrbitCameraGetParentWorldTransformation(const struct KzuOrbitCamera* orbitCamera, struct KzcMatrix4x4* out_matrix);
/**Gets orbit camera transformation attributes. */
void kzuOrbitCameraGetTransformationAttributes(const struct KzuOrbitCamera* orbitCamera, struct KzuCameraTransformationAttributes* out_attributes);
/** Gets radius from orbit camera. */
kzFloat kzuOrbitCameraGetRadius(const struct KzuOrbitCamera* orbitCamera);

/** Returns KZ_TRUE if picking should be enabled. */
kzBool kzuOrbitCameraIsPickingEnabled(const struct KzuOrbitCamera* orbitCamera);


KZ_HEADER_END


#endif
