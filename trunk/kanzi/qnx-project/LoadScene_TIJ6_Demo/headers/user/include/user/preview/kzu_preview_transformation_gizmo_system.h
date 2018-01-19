/**
 * \file
 * Preview transformation gizmo system structure contains the transformation gizmo that is used in the preview application.
 *
 * Copyright 2008-2014 by Rightware. All rights reserved.
 */
#ifndef KZU_PREVIEW_TRANSFORMATION_GIZMO_SYSTEM_H
#define KZU_PREVIEW_TRANSFORMATION_GIZMO_SYSTEM_H


#include <user/preview/kzu_preview_system.h>
#include <user/util/kzu_transform_gizmo.h>

#include <system/kzs_types.h>
#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>
#include <system/input/kzs_input.h>


KZ_HEADER_BEGIN


/* Forward declarations */
struct KzcMemoryManager;
struct KzsInputEventPointer;
struct KzuRenderer;
struct KzuUIDomain;
struct KzuTransformedScene;
struct KzuPreviewSystem;
struct KzuPick;

/**
 * \struct KzuPreviewTransformationGizmoSystem
 * Preview transformation gizmo system structure.
 */
struct KzuPreviewTransformationGizmoSystem;


/** Creates a new preview transformation gizmo system object. */
kzsError kzuPreviewTransformationGizmoSystemCreate(const struct KzcMemoryManager* memoryManager, struct KzuPreviewSystem* previewSystem, struct KzuUIDomain* uiDomain, struct KzuPreviewTransformationGizmoSystem** out_previewTransformationGizmoSystem);

/** Deletes a preview transformation gizmo system object. */
kzsError KzuPreviewTransformationGizmoSystemDelete(struct KzuPreviewTransformationGizmoSystem* previewTransformationGizmoSystem);


/** Handles key events of the preview gizmo system. */
kzsError kzuPreviewTransformationGizmoSystemHandleKeyEvent(const struct KzuPreviewTransformationGizmoSystem* previewGizmoSystem, enum KzsInputKey keyCode, enum KzsInputKeyDeviceState keyState);
/** Notifies the preview transformation gizmo system of a pointing device event. */
kzsError kzuPreviewTransformationGizmoSystemHandleLayerPointingEvent(const struct KzuPreviewTransformationGizmoSystem* previewTransformationGizmoSystem, const struct KzuEngine* engine, const struct KzuUIDomain* uiDomain,
                                                                const struct KzuViewportLayer* viewportLayer, struct KzuPick* pick, kzInt pointerX, kzInt pointerY, enum KzsInputPointingDeviceState state,
                                                                kzBool* out_previewInputHandled);

/** Renders the preview transformation gizmo system. */
kzsError kzuPreviewTransformationGizmoSystemRender(const struct KzuPreviewTransformationGizmoSystem* previewTransformationGizmoSystem,
                                                   struct KzuRenderer* renderer, struct KzuRenderContextStack* renderContextStack,
                                                   const struct KzuTransformedScene* transformedScene);

/** Gets the transformation gizmo. */
struct KzuTransformGizmo* kzuPreviewTransformationGizmoSystemGetTransformGizmo(const struct KzuPreviewTransformationGizmoSystem* previewTransformationGizmoSystem);


KZ_HEADER_END


#endif
