/**
* \file
* Transform gizmo utility.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_TRANSFORM_GIZMO_H
#define KZU_TRANSFORM_GIZMO_H


#include <system/input/kzs_input.h>
#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations. */
struct KzcMatrix3x3;
struct KzcMatrix4x4;
struct KzcMemoryManager;
struct KzuEngine;
struct KzuMessageDispatcher;
struct KzuPick;
struct KzuUIDomain;
struct KzuPropertyManager;
struct KzuRenderer;
struct KzuTransformedScene;
struct KzuRenderContextStack;
struct KzuViewportLayer;
struct KzuUIDomain;


#define KZU_TRANSFORM_GIZMO_DEFAULT_GRID_SNAP_SIZE 1.0f    /**< Default snap size for transform gizmo. */
#define KZU_TRANSFORM_GIZMO_DEFAULT_ROTATE_SNAP_SIZE 15.0f /**< Default snap size for transform gizmo. */
#define KZU_TRANSFORM_GIZMO_DEFAULT_SCALE_SNAP_SIZE 0.5f   /**< Default snap size for transform gizmo. */


/** Enumeration for transform gizmo modes. */
enum KzuTransformGizmoMode
{
    KZU_TRANSFORM_GIZMO_MODE_NONE,          /** No mode. */
    KZU_TRANSFORM_GIZMO_MODE_TRANSLATE,     /** Translate mode. */
    KZU_TRANSFORM_GIZMO_MODE_ROTATE,        /** Rotate mode. */
    KZU_TRANSFORM_GIZMO_MODE_SCALE          /** Scale mode. */
};

/** Enumeration for transform gizmo coordinate system reference modes. */
enum KzuTransformGizmoReferenceMode
{
    KZU_TRANSFORM_GIZMO_REFERENCE_LOCAL,    /** Local reference. */
    KZU_TRANSFORM_GIZMO_REFERENCE_GLOBAL    /** Global reference. */
};

/** Enumeration for transform gizmo grid snap mode. */
enum KzuTransformGizmoGridSnapMode
{
    KZU_TRANSFORM_GIZMO_GRID_SNAP_NONE,     /**< Used when mode is not known. */
    KZU_TRANSFORM_GIZMO_GRID_SNAP_RELATIVE, /**< Snap to relative motion. */
    KZU_TRANSFORM_GIZMO_GRID_SNAP_ABSOLUTE, /**< Snap to absolute coordinates. */
    KZU_TRANSFORM_GIZMO_GRID_SNAP_OBJECT    /**< Snap to other objects. */
};


/**
* \struct KzuTransformGizmo
* Structure to hold transform gizmo context.
*/
struct KzuTransformGizmo;


/** Create a transform gizmo context. */
kzsError kzuTransformGizmoCreate(const struct KzcMemoryManager* memoryManager, struct KzuTransformGizmo** out_gizmo);
/** Delete a transform gizmo context. */
kzsError kzuTransformGizmoDelete(struct KzuTransformGizmo* gizmo);

/** Initialize a transform gizmo context for a new project. */
kzsError kzuTransformGizmoInitialize(struct KzuTransformGizmo* gizmo, struct KzuUIDomain* uiDomain);
/** Uninitializes the transform gizmo. */
kzsError kzuTransformGizmoUninitialize(struct KzuTransformGizmo* gizmo);


/** Sets the transform gizmo mode. */
kzsError kzuTransformGizmoSetMode(struct KzuTransformGizmo* gizmo, enum KzuTransformGizmoMode mode);
/** Gets the transform gizmo mode. */
enum KzuTransformGizmoMode kzuTransformGizmoGetMode(const struct KzuTransformGizmo* gizmo);


/** Tell whether or not grid snap is enabled. */
kzBool kzuTransformGizmoIsGridSnapEnabled(const struct KzuTransformGizmo* gizmo);
/** Sets the grid snap on or off in the transform gizmo. */
void kzuTransformGizmoSetGridSnapEnabled(struct KzuTransformGizmo* gizmo, kzBool enabled);
/** Get the size of the grid in the transform gizmo. */
kzFloat kzuTransformGizmoGetGridSize(const struct KzuTransformGizmo* gizmo);
/**
* Set the grid size for the transform gizmo.
* If the user is trying to set the grid size to a value <= 0.0f, it is left unchanged. */
void kzuTransformGizmoSetGridSize(struct KzuTransformGizmo* gizmo, kzFloat size);
/** Get the grid snap mode. */
enum KzuTransformGizmoGridSnapMode kzuTransformGizmoGetGridSnapMode(const struct KzuTransformGizmo* gizmo);
/** Set the grid snap mode. */
void kzuTransformGizmoSetGridSnapMode(struct KzuTransformGizmo* gizmo, enum KzuTransformGizmoGridSnapMode mode);
/** Get the rotation snap size. */
kzFloat kzuTransformGizmoGetRotateSnapSize(const struct KzuTransformGizmo* gizmo);
/** Set the rotation snap size. The size must be a positive number, greater than zero. */
void kzuTransformGizmoSetRotateSnapSize(struct KzuTransformGizmo* gizmo, kzFloat size);
/** Get the scale snap size. */
kzFloat kzuTransformGizmoGetScaleSnapSize(const struct KzuTransformGizmo* gizmo);
/** Set the scale snap size. The size must be a positive number, greater than zero. */
void kzuTransformGizmoSetScaleSnapSize(struct KzuTransformGizmo* gizmo, kzFloat size);

/** Render the transform gizmo. */
kzsError kzuTransformGizmoRender(const struct KzuTransformGizmo* gizmo, struct KzuRenderer* renderer, struct KzuRenderContextStack* renderContextStack,
                                 const struct KzuTransformedScene* transformedScene, kzString targetObjectPath);

/** Process key events for the transform gizmo. */
kzsError kzuTransformGizmoProcessInput(struct KzuTransformGizmo* gizmo, const struct KzuEngine* engine,
                                       const struct KzuViewportLayer* viewportLayer, struct KzuPick* pick, kzInt x, kzInt y,
                                       enum KzsInputPointingDeviceState state, kzString targetObjectPath, kzBool* out_handled);

/** Transform gizmo callback prototype. */
typedef kzsError (*KzuTransformGizmoCallback)(kzString objectPath, const struct KzcMatrix4x4* transformation, enum KzuTransformGizmoMode mode, void* userData);
/** Sets a callback for transform gizmo. Pass KZ_NULL to disable. */
void kzuTransformGizmoSetCallback(struct KzuTransformGizmo* gizmo, KzuTransformGizmoCallback callback, void* userData);


KZ_HEADER_END


#endif
