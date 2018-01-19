/**
 * \file
 * Preview system structure contains those features that are used in the preview but not in the normal application.
 *
 * Copyright 2008-2014 by Rightware. All rights reserved.
 */
#ifndef KZU_PREVIEW_SYSTEM_H
#define KZU_PREVIEW_SYSTEM_H


#include <system/kzs_types.h>
#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>
#include <system/input/kzs_input.h>


KZ_HEADER_BEGIN


/* Forward declarations */
struct KzsInputEventPointer;
struct KzcMemoryManager;
struct KzuRenderer;
struct KzuComposer;
struct KzuTransformedScene;
struct KzuPreviewCameraSystem;
struct KzuPreviewTransformationGizmoSystem;
struct KzuLayer;
struct KzuEngine;
struct KzuRenderContextStack;
struct KzuScreen;
struct KzuPick;
struct KzuUIDomain;

struct KzuViewportLayer;
struct KzcVector2;

/**
 * \struct KzuPreviewSystem
 * Preview system structure.
 */
struct KzuPreviewSystem;


/** Type of a patching event. */
enum KzuPreviewSystemPatchType
{
    KZU_PREVIEW_SYSTEM_PATCH_TYPE_UPDATE,
    KZU_PREVIEW_SYSTEM_PATCH_TYPE_REMOVE
};

/** Type of a preview system feature. */
enum KzuPreviewSystemFeatureType
{
    KZU_PREVIEW_SYSTEM_FEATURE_PREVIEW_CAMERA_SYSTEM,
    KZU_PREVIEW_SYSTEM_FEATURE_PREVIEW_SELECTION_SYSTEM,
    KZU_PREVIEW_SYSTEM_FEATURE_PREVIEW_GIZMO_SYSTEM,
    KZU_PREVIEW_SYSTEM_FEATURE_HUD
};

/** Current preview system mode. */
enum KzuPreviewSystemMode
{
    KZU_PREVIEW_SYSTEM_MODE_INTERACT = 0, /**< Interactive mode. */
    KZU_PREVIEW_SYSTEM_MODE_EDIT = 1 /**< Edit mode. */
};

/** Specifies option for overdraw visualization. */
#define KZU_PREVIEW_SYSTEM_OPTION_OVERDRAW_VISUALIZATION "Overdraw visualization"
/** Specifies option for visualization if layer is rendered into a texture. */
#define KZU_PREVIEW_SYSTEM_OPTION_LAYER_RENDER_TO_TEXTURE_VISUALIZATION "Layer render to texture visualization"
/** Specifies option for visualization if layer is rendered into a texture. */
#define KZU_PREVIEW_SYSTEM_OPTION_LAYER_IS_TRANSPARENT_VISUALIZATION "Layer is transparent visualization"
/** Specifies option for overdraw visualization. */
#define KZU_PREVIEW_SYSTEM_OPTION_LAYER_VISUALIZATION "Layer visualization"
/** Specifies option for Performance HUD display. */
#define KZU_PREVIEW_SYSTEM_OPTION_PERFORMANCE_HUD "Performance HUD"
/** Specifies option for Animation HUD display. */
#define KZU_PREVIEW_SYSTEM_OPTION_ANIMATION_HUD "Animation HUD"
/** Specifies option for bounding volume visualization. */
#define KZU_PREVIEW_SYSTEM_OPTION_BOUNDING_VOLUMES "Bounding Volumes"


/** Creates a new preview system object. */
kzsError kzuPreviewSystemCreate(const struct KzcMemoryManager* memoryManager, struct KzuEngine* engine, struct KzuUIDomain* uiDomain,
                                kzUint width, kzUint height, struct KzuPreviewSystem** out_previewSystem);

/** Initialized the preview system with resource set up. */
kzsError kzuPreviewSystemInitialize(struct KzuPreviewSystem* previewSystem);

/** Deletes a preview system object. */
kzsError KzuPreviewSystemDelete(struct KzuPreviewSystem* previewSystem);


/** Updates the preview system. */
kzsError kzuPreviewSystemUpdate(struct KzuPreviewSystem* previewSystem, kzUint deltaTime);

/** Notifies the preview system of an input event. Output parameter is set to KZ_TRUE if the preview system has consumed the event. */
kzsError kzuPreviewSystemHandleInputEvent(const struct KzuPreviewSystem* previewSystem, const struct KzsEvent* event, kzBool* out_inputHandled);


/** Renders the preview system. */
kzsError kzuPreviewSystemRender(struct KzuPreviewSystem* previewSystem, struct KzuRenderer* renderer, const struct KzcVector2* offset, const struct KzcVector2* limits);
/** Visualizes the preview system layers. */
kzsError kzuPreviewSystemVisualizeLayers(const struct KzuPreviewSystem* previewSystem, struct KzuRenderer* renderer, struct KzuLayer* rootLayer);

/** Notifies the preview system that a project has been reloaded. */
kzsError kzuPreviewSystemProjectReloaded(struct KzuPreviewSystem* previewSystem, struct KzuUIDomain* uiDomain);

/** Enables a preview system feature. */
kzsError kzuPreviewSystemEnableFeature(struct KzuPreviewSystem* previewSystem, enum KzuPreviewSystemFeatureType feature);

/** Disables a preview system feature. */
kzsError kzuPreviewSystemDisableFeature(struct KzuPreviewSystem* previewSystem, enum KzuPreviewSystemFeatureType feature);

/** Toggles a preview system feature. */
kzsError kzuPreviewSystemToggleFeature(struct KzuPreviewSystem* previewSystem, enum KzuPreviewSystemFeatureType feature);

/** Returns the preview camera system, if it's enabled. Returns KZ_NULL if the feature is not enabled. */
struct KzuPreviewCameraSystem* kzuPreviewSystemGetPreviewCameraSystem(const struct KzuPreviewSystem* previewSystem);

/** Returns the preview selection system, if it's enabled. Returns KZ_NULL if the feature is not enabled. */
struct KzuPreviewSelectionSystem* kzuPreviewSystemGetPreviewSelectionSystem(const struct KzuPreviewSystem* previewSystem);

/** Returns the preview transformation gizmo system, if it's enabled. Returns KZ_NULL if the feature is not enabled. */
struct KzuPreviewTransformationGizmoSystem* kzuPreviewSystemGetPreviewTransformationGizmoSystem(const struct KzuPreviewSystem* previewSystem);

/** Returns the hud from preview system. */
struct KzuHud* kzuPreviewSystemGetHud(const struct KzuPreviewSystem* previewSystem);

/** Sets edit legend for preview system. */
kzsError kzuPreviewSystemSetEditLegend(struct KzuPreviewSystem* previewSystem, kzString legend);
/** Sets camera legend for preview system. */
kzsError kzuPreviewSystemSetCameraLegend(struct KzuPreviewSystem* previewSystem, kzString legend);


/** Sets the current screen to the preview system. */
void kzuPreviewSystemSetScreen(struct KzuPreviewSystem* previewSystem, struct KzuScreen* screen);
/** Gets screen from preview system. */
struct KzuScreen* kzuPreviewSystemGetScreen(const struct KzuPreviewSystem* previewSystem);
/** Gets the current root layer. */
struct KzuLayer* kzuPreviewSystemGetRootLayer(const struct KzuPreviewSystem* previewSystem);

/** Sets the edit/interact mode for preview. */
kzsError kzuPreviewSystemSetMode(struct KzuPreviewSystem* previewSystem, enum KzuPreviewSystemMode mode);
/** Gets the edit/interact mode from preview. */
enum KzuPreviewSystemMode kzuPreviewSystemGetMode(const struct KzuPreviewSystem* previewSystem);

/** Gets the engine. */
struct KzuEngine* kzuPreviewSystemGetEngine(const struct KzuPreviewSystem* previewSystem);

/** Gets the memory manager. */
const struct KzcMemoryManager* kzuPreviewSystemGetMemoryManager(const struct KzuPreviewSystem* previewSystem);

/** Gets the project. */
struct KzuUIDomain* kzuPreviewSystemGetUIDomain(const struct KzuPreviewSystem* previewSystem);

/** Gets the pick. */
struct KzuPick* kzuPreviewSystemGetPick(const struct KzuPreviewSystem* previewSystem);

/** Begins overdraw visualization. */
kzsError kzuPreviewSystemBeginOverdrawVisualization(struct KzuPreviewSystem* previewSystem, struct KzuRenderer* renderer);
/** Ends overdraw visualization. */
kzsError kzuPreviewSystemEndOverdrawVisualization(const struct KzuPreviewSystem* previewSystem, struct KzuRenderer* renderer);

/** Sets preview option for application. For example "IsMyCustomVisualizationEnabled", 1. */
kzsError kzuPreviewSystemSetPreviewOptionInteger(struct KzuPreviewSystem* previewSystem, kzString optionName, kzInt value);
/** Returns preview option value from application. Return if it was found
 * \param optionName Name of the preview option.
 * \param out_value Output value, KZ_NULL if not required.
 */
kzBool kzuPreviewSystemGetPreviewOptionInteger(const struct KzuPreviewSystem* previewSystem, kzString optionName, kzInt* out_value);
/** Finds the first viewport layer from given preview system. */
struct KzuViewportLayer* kzuPreviewSystemFindFirstViewportLayer(const struct KzuPreviewSystem* previewSystem);

/** Sets debug composer for preview system. */
void kzuPreviewSystemSetDebugComposer(struct KzuPreviewSystem* previewSystem, struct KzuComposer* debugComposer);
/** Enables or disables the preview system key handling. By default, the key handling is enabled. */
void kzuPreviewSystemSetKeyHandlingEnabled(struct KzuPreviewSystem* previewSystem, kzBool enabled);


KZ_HEADER_END


#endif
