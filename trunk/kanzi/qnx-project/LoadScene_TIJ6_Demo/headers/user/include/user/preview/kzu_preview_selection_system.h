/**
 * \file
 * Preview selection system structure contains the picking functionality that is used in the preview application.
 *
 * Copyright 2008-2014 by Rightware. All rights reserved.
 */
#ifndef KZU_PREVIEW_SELECTION_SYSTEM_H
#define KZU_PREVIEW_SELECTION_SYSTEM_H


#include <user/preview/kzu_preview_system.h>

#include <system/kzs_types.h>
#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>
#include <system/input/kzs_input.h>


KZ_HEADER_BEGIN


/* Forward declarations */
struct KzcMemoryManager;
struct KzsInputEventPointer;
struct KzuRenderer;
struct KzuTransformedScene;
struct KzuPreviewSystem;
struct KzcVector2;
struct KzuViewportLayer;
struct KzuObjectNode;

/**
 * \struct KzuPreviewSelectionSystem
 * Preview selection system structure.
 */
struct KzuPreviewSelectionSystem;

/** Selection mode for the preview selection system. */
enum KzuPreviewSelectionMode
{
    KZU_PREVIEW_SELECTION_MODE_NODE,
    KZU_PREVIEW_SELECTION_MODE_MATERIAL
};

/** Selection callback prototype. */
typedef kzsError (*KzuPreviewSelectionCallback)(kzString objectPath, void* userData);



/** Creates a new preview selection system object. */
kzsError kzuPreviewSelectionSystemCreate(const struct KzcMemoryManager* memoryManager, struct KzuPreviewSystem* previewSystem, struct KzuPreviewSelectionSystem** out_previewSelectionSystem);

/** Deletes a preview selection system object. */
kzsError kzuPreviewSelectionSystemDelete(struct KzuPreviewSelectionSystem* previewSelectionSystem);


/** Notifies the preview selection system of a pointing device event that has been mapped to a viewport layer. */
kzsError kzuPreviewSelectionSystemHandleLayerPointingEvent(const struct KzuPreviewSelectionSystem* previewSelectionSystem, enum KzsInputPointingDeviceState state,
                                                           const struct KzuViewportLayer* viewportLayer, const struct KzcVector2* layerPoint);

/** Sets the selection mode. */
void kzuPreviewSelectionSystemSetSelectionMode(struct KzuPreviewSelectionSystem* previewSelectionSystem, enum KzuPreviewSelectionMode mode);

/** Sets the callback that is called when objects are selected by the preview selection system. */
void kzuPreviewSelectionSystemSetSelectionCallback(struct KzuPreviewSelectionSystem* previewSelectionSystem, KzuPreviewSelectionCallback selectionCallback, void* userData);

/** Performs a single selection operation in the current root layer. The selection callback is called for an object under the pointer. The object is not automatically added to the current selection. */
kzsError kzuPreviewSelectionSystemPerformSelection(const struct KzuPreviewSelectionSystem* previewSelectionSystem, kzUint x, kzUint y, struct KzuObjectNode** out_node, kzUint* out_cluster);

/** Tell if selection modulation is on. */
kzBool kzuPreviewSelectionSystemHasModulateSelection(const struct KzuPreviewSelectionSystem* previewSelectionSystem);
/** Turn selection modulation on or off. */
void kzuPreviewSelectionSystemSetModulateSelection(struct KzuPreviewSelectionSystem* previewSelectionSystem, kzBool enabled);
/** Clears all selected objects. */
kzsError kzuPreviewSelectionSystemClearSelection(const struct KzuPreviewSelectionSystem* previewSelectionSystem);
/** Adds one target object for the selection. */
kzsError kzuPreviewSelectionSystemAddToSelection(const struct KzuPreviewSelectionSystem* previewSelectionSystem, kzString objectPath);
/**
 * Apply one path for the selection.
 * This either selects or unselects the given object.
 */
kzsError kzuPreviewSelectionSystemApplySelection(const struct KzuPreviewSelectionSystem* previewSelectionSystem, kzString objectPath);
/** Gets all selected objects. Each object is represented as a kzString path.*/
struct KzcDynamicArray* kzuPreviewSelectionSystemGetSelection(const struct KzuPreviewSelectionSystem* previewSelectionSystem);
/** Gets the first selected object. */
kzString kzuPreviewSelectionSystemGetFirstSelectedObject(const struct KzuPreviewSelectionSystem* previewSelectionSystem);


KZ_HEADER_END


#endif
