/**
 * \file
 * Preview camera system structure contains free and orbit cameras that are used in the preview application.
 *
 * Copyright 2008-2014 by Rightware. All rights reserved.
 */
#ifndef KZU_PREVIEW_CAMERA_SYSTEM_H
#define KZU_PREVIEW_CAMERA_SYSTEM_H


#include <user/preview/kzu_preview_system.h>
#include <user/preview/kzu_preview_camera_system_base.h>
#include <user/util/kzu_free_camera.h>

#include <system/kzs_types.h>
#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>
#include <system/input/kzs_input.h>


KZ_HEADER_BEGIN


/* Forward declarations */
struct KzcMemoryManager;
struct KzcVolume;
struct KzcDynamicArray;
struct KzcMatrix4x4;
struct KzsInputEventPointer;
struct KzuRenderer;
struct KzuTransformedScene;
struct KzuPreviewSystem;
struct KzuPropertyType;
struct KzuUIDomain;


/**
 * \struct KzuPreviewCameraSystem
 * Preview camera system structure.
 */
struct KzuPreviewCameraSystem;


/** Type of preview camera. */
enum KzuPreviewCameraMode
{
    KZU_PREVIEW_CAMERA_MODE_DISABLED, /**< No preview camera. */
    KZU_PREVIEW_CAMERA_MODE_FLY_CAMERA, /**< Fly camera. */
    KZU_PREVIEW_CAMERA_MODE_ORBIT_CAMERA /**< Orbit camera. */
};

/** Preview camera focus margin between camera and selection. */
#define KZU_PREVIEW_CAMERA_FOCUS_MARGIN 1.0f

/** Creates a new preview camera system object. */
kzsError kzuPreviewCameraSystemCreate(const struct KzcMemoryManager* memoryManager, struct KzuPreviewSystem* previewSystem, struct KzuPreviewCameraSystem** out_previewCameraSystem);

/** Deletes a preview camera system object. */
kzsError kzuPreviewCameraSystemDelete(struct KzuPreviewCameraSystem* previewCameraSystem);


/** Updates the preview camera system. */
kzsError kzuPreviewCameraSystemUpdate(struct KzuPreviewCameraSystem* previewCameraSystem, kzUint deltaTime);

/** Notifies the preview camera system of a key device event. */
kzsError kzuPreviewCameraSystemHandleKeyEvent(struct KzuPreviewCameraSystem* previewCameraSystem, enum KzsInputKey keyCode, enum KzsInputKeyDeviceState keyState);

/** Notifies the preview camera system of a pointing device event. */
kzsError kzuPreviewCameraSystemHandlePointingEvent(const struct KzuPreviewCameraSystem* previewCameraSystem, const struct KzsInputEventPointer* inputData, kzBool* out_previewInputHandled);

/** Notifies the preview camera system of a window event. */
kzsError kzuPreviewCameraSystemHandleWindowEvent(struct KzuPreviewCameraSystem* previewCameraSystem, enum KzsEventType eventType);


/** Sets the current preview camera mode. */
kzsError kzuPreviewCameraSystemSetCameraMode(struct KzuPreviewCameraSystem* previewCameraSystem, enum KzuPreviewCameraMode cameraMode);

/** Sets focus to selected node on preview camera. If KZ_NULL has no effect. */
kzsError kzuPreviewCameraSystemFocusToSelection(const struct KzuPreviewCameraSystem* previewCameraSystem, const struct KzcDynamicArray* nodePaths);
/** Revers the focus on preview camera to the point where preview camera was previously located. */
kzsError kzuPreviewCameraSystemRevertFocus(const struct KzuPreviewCameraSystem* previewCameraSystem);
/** Utility to get total volume from selected paths. */
kzsError kzuPreviewCameraSystemGetSelectionVolume(const struct KzcDynamicArray* nodePaths, const struct KzuTransformedScene* transformedScene, struct KzcVolume* out_volume);

/** Gets the current preview camera mode. */
enum KzuPreviewCameraMode kzuPreviewCameraSystemGetCameraMode(const struct KzuPreviewCameraSystem* previewCameraSystem);
/** Sets bind camera mode for preview camera, when the values from virtual camera are saved to actual camera. */
kzsError kzuPreviewCameraSystemSetBindCameraMode(struct KzuPreviewCameraSystem* previewCameraSystem, kzBool bindCamera);
/** Returns if preview camera is in bind camera mode. */
kzBool kzuPreviewCameraSystemIsBindCameraMode(const struct KzuPreviewCameraSystem* previewCameraSystem);

/** Sets a callback for free camera. Pass KZ_NULL to disable. */
void kzuPreviewCameraSystemSetCameraCallback(struct KzuPreviewCameraSystem* previewCameraSystem, KzuPreviewCameraUpdateStateFunction updateStateFunction, void* userData);
/** Gets viewport layer from preview camera system. */
struct KzuViewportLayer* kzuPreviewCameraSystemGetViewportLayer(const struct KzuPreviewCameraSystem* previewCameraSystem);

/** Is the picking enabled in the preview camera. */
kzBool kzuPreviewCameraSystemIsPickingEnabled(const struct KzuPreviewCameraSystem* previewCameraSystem);

/** Refreshes the preview camera status on the current root layer. Modify parameter determines whether to reset the preview camera location or keep the old one. 
 * \param transformation Transformation to be set for preview camera, KZ_NULL to calculate from scene camera.
 */
kzsError kzuPreviewCameraSystemRefresh(const struct KzuPreviewCameraSystem* previewCameraSystem, const struct KzcMatrix4x4* transformation);

/** Helper function to clone camera specific data (properties) from node to target. */
kzsError kzuPreviewCameraCloneData(const struct KzuObjectNode* originalCameraNode, const struct KzuObjectNode* targetCameraNode);

/** Gets the free camera. */
struct KzuFreeCamera* kzuPreviewCameraSystemGetFreeCamera(const struct KzuPreviewCameraSystem* previewCameraSystem);

/** Gets the orbit camera. */
struct KzuOrbitCamera* kzuPreviewCameraSystemGetOrbitCamera(const struct KzuPreviewCameraSystem* previewCameraSystem);


KZ_HEADER_END


#endif
