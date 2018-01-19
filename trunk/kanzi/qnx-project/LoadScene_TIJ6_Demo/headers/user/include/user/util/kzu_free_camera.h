/**
* \file
* Free camera utility. A utility for freely moving camera with pointing and key devices.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_FREE_CAMERA_H
#define KZU_FREE_CAMERA_H


#include <user/preview/kzu_preview_camera_system_base.h>

#include <system/debug/kzs_error.h>
#include <system/kzs_types.h>
#include <system/input/kzs_input.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/** Free camera action types. */
enum KzuFreeCameraActionType
{
    KZU_FREE_CAMERA_ACTION_MOVE_FORWARD,         /**< Action forward. */
    KZU_FREE_CAMERA_ACTION_MOVE_BACKWARD,        /**< Action backward. */
    KZU_FREE_CAMERA_ACTION_MOVE_LEFT,            /**< Action left. */
    KZU_FREE_CAMERA_ACTION_MOVE_RIGHT,           /**< Action right. */
    KZU_FREE_CAMERA_ACTION_SPEED_UP,        /**< Action speed up. */
    KZU_FREE_CAMERA_ACTION_SPEED_DOWN,      /**< Action speed down. */
    KZU_FREE_CAMERA_ACTION_DOUBLE_SPEED,    /**< Action double speed. */
    KZU_FREE_CAMERA_ACTION_ROTATING,        /**< Action rotating on. */
    KZU_FREE_CAMERA_ACTION_LIFTING,         /**< Action lifting on. */
    KZU_FREE_CAMERA_ACTION_ROLLING,         /**< Action rolling on. */
    KZU_FREE_CAMERA_ACTION_FIELD_OF_VIEW_UP, /**< Action field of view up. */
    KZU_FREE_CAMERA_ACTION_FIELD_OF_VIEW_DOWN, /**< Action field of view down */
    KZU_FREE_CAMERA_ACTION_ROLLING_LEFT,    /**< Action rolling left. */
    KZU_FREE_CAMERA_ACTION_ROLLING_RIGHT,   /**< Action rolling right. */
    KZU_FREE_CAMERA_ACTION_LIFTING_SIDE,   /**< Action lifting to side direction. */
    KZU_FREE_CAMERA_ACTION_LIFTING_DEPTH,   /**< Action lifting to depth direction. */
    KZU_FREE_CAMERA_ACTION_STRAIGHTEN,       /**< Straightens the free camera to look horizontally. */
    KZU_FREE_CAMERA_ACTION_ROTATE_X_CLOCKWISE, /**< Rotate X clockwise. */
    KZU_FREE_CAMERA_ACTION_ROTATE_X_COUNTERCLOCKWISE, /**< Rotate X counterclockwise. */
    KZU_FREE_CAMERA_ACTION_ROTATE_Y_CLOCKWISE, /**< Rotate Y clockwise. */
    KZU_FREE_CAMERA_ACTION_ROTATE_Y_COUNTERCLOCKWISE, /**< Rotate Y counterclockwise. */

    KZU_FREE_CAMERA_ACTION_TOGGLE_FREEZE, /**< Toggles free camera freeze on/off. */

    KZU_FREE_CAMERA_ACTION_COUNT            /**< Number of actions for free camera. */
};


/* Forward declarations */
struct KzuCameraNode;
struct KzuCamera;
struct KzuObjectNode;
struct KzuScene;
struct KzuTransformedScene;
struct KzcMemoryManager;
struct KzuUIDomain;
struct KzcDynamicArray;
struct KzcMatrix4x4;
struct KzcVector3;
struct KzuCameraTransformationAttributes;


/**
* \struct KzuFreeCamera
* Structure for free camera object, that is, freely controllable camera utility.
*/
struct KzuFreeCamera;


/** Creates a new free camera object with a default camera in origin. */
kzsError kzuFreeCameraCreate(const struct KzcMemoryManager* memoryManager, struct KzuUIDomain* uiDomain,
                             struct KzuFreeCamera** out_freeCamera);

/** Deletes free camera object. */
kzsError kzuFreeCameraDelete(struct KzuFreeCamera* freeCamera);

/** Sets position for free camera. */
kzsError kzuFreeCameraSetPosition(const struct KzuFreeCamera* freeCamera, const struct KzcVector3* position);
/** Returns world matrix from free camera position and orientation. */
void kzuFreeCameraInitializeMatrix(const struct KzuFreeCamera* freeCamera, struct KzcMatrix4x4* out_worldMatrix);

/** Returns camera node from free camera. */
struct KzuCameraNode* kzuFreeCameraGetCameraNode(const struct KzuFreeCamera* freeCamera);

/** Updates free camera, delta time in milliseconds. */
kzsError kzuFreeCameraUpdate(struct KzuFreeCamera* freeCamera, kzUint deltaTime);

/** Tell if free camera is active. */
kzBool kzuFreeCameraIsActive(const struct KzuFreeCamera* freeCamera);
/** Replaces the view camera in a scene with this. */
kzsError kzuFreeCameraReplace(struct KzuFreeCamera* freeCamera, const struct KzuScene* scene, const struct KzuObjectNode* viewCameraNode, const struct KzcMatrix4x4* parentWorldTransformation, const struct KzcMatrix4x4* viewCameraTransformation);
/** Replaces the view camera in a scene with this taking into account transformation attributes. */
kzsError kzuFreeCameraReplaceWithTransformationAttributes(struct KzuFreeCamera* freeCamera, const struct KzuScene* scene, const struct KzcMatrix4x4* parentWorldTransformation, const struct KzuCameraTransformationAttributes* attributes);
/** Get attached scene from free camera. */
struct KzuScene* kzuFreeCameraGetAttachedScene(const struct KzuFreeCamera* freeCamera);
/** Get attached scene object from free camera. */
struct KzuObjectNode* kzuFreeCameraGetAttachedSceneObject(const struct KzuFreeCamera* freeCamera);
/** Restores the view camera previously replaced by this free camera. */
kzsError kzuFreeCameraRestoreReplacedCamera(const struct KzuFreeCamera* freeCamera);

/** Sets free camera freezed / unfreezed. */
void kzuFreeCameraSetFreezed(struct KzuFreeCamera* freeCamera, kzBool freezed);
/** Checks if free camera is freezed. */
kzBool kzuFreeCameraIsFreezed(const struct KzuFreeCamera* freeCamera);

/** Gets free camera speed. */
kzFloat kzuFreeCameraGetSpeed(const struct KzuFreeCamera* freeCamera);

/** Maps new action to key device key. Same key can have several actions. */
kzsError kzuFreeCameraMapActionToKey(struct KzuFreeCamera* freeCamera, enum KzsInputKey key, enum KzuFreeCameraActionType actionType);
/** Maps new action to pointer device button. Same pointer device button can be mapped with several actions. */
kzsError kzuFreeCameraMapActionToPointerButton(struct KzuFreeCamera* freeCamera, kzU32 pointerButton, enum KzuFreeCameraActionType actionType);

/** Handles free camera key events. */
void kzuFreeCameraHandleKeyEvents(struct KzuFreeCamera* freeCamera, enum KzsInputKey keyCode, enum KzsInputKeyDeviceState keyState);
/** Handles free camera pointing device events. */
void kzuFreeCameraHandlePointingDeviceEvents(struct KzuFreeCamera* freeCamera, kzU32 buttons, enum KzsInputPointingDeviceState state, kzInt mouseX, kzInt mouseY);
/** Handles a free camera window event. */
void kzuFreeCameraHandleWindowEvent(struct KzuFreeCamera* freeCamera, enum KzsEventType eventType);

/** Sets free camera action event. */
void kzuFreeCameraSetActionEvent(struct KzuFreeCamera* freeCamera, enum KzuFreeCameraActionType actionType);

/** Focuses free camera to specified object node. */
kzsError kzuFreeCameraFocusToSelection(struct KzuFreeCamera* freeCamera, const struct KzcDynamicArray* nodePaths, const struct KzuTransformedScene* transformedScene);
/** Reverts the free camera focus. */
kzsError kzuFreeCameraRevertFocus(struct KzuFreeCamera* freeCamera);

/** Gets free camera transformation, including the parent inverse multiplied. */
void kzuFreeCameraGetTransformation(const struct KzuFreeCamera* freeCamera, kzBool considerParent, struct KzcMatrix4x4* out_matrix);
/** Gets free camera's parent world transformation. */
void kzuFreeCameraGetParentWorldTransformation(const struct KzuFreeCamera* freeCamera, struct KzcMatrix4x4* out_matrix);
/** Gets free camera transformation attributes. */
void kzuFreeCameraGetTransformationAttributes(const struct KzuFreeCamera* freeCamera, struct KzuCameraTransformationAttributes* out_attributes);

/** Returns KZ_TRUE if picking should be enabled. */
kzBool kzuFreeCameraIsPickingEnabled(const struct KzuFreeCamera* freeCamera);


KZ_HEADER_END


#endif
