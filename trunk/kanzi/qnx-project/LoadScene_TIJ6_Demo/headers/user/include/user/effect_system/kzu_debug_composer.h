/**
* \file
* Grid debug object composer.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_DEBUG_COMPOSER_H
#define KZU_DEBUG_COMPOSER_H


#include <system/debug/kzs_error.h>
#include <system/kzs_types.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations */
struct KzcInputStream;
struct KzcMemoryManager;
struct KzuComposer;
struct KzuBinaryFileInfo;
struct KzuMaterial;
struct KzuUIDomain;
struct KzuPropertyManager;
struct KzuTransformGizmo;
struct KzuPreviewSystem;

/**
 * \struct KzuDebugComposer
 * Debug composer.
 */
struct KzuDebugComposer;


/** Creates new debug composer. */
kzsError kzuDebugComposerCreate(const struct KzcMemoryManager* memoryManager, struct KzuPropertyManager* propertyManager,
                                const struct KzuUIDomain* uiDomain, struct KzuDebugComposer** out_debugComposer);

/** Casts a debug composer to composer. */
struct KzuComposer* kzuDebugComposerToComposer(const struct KzuDebugComposer* debugComposer);
/** Casts composer to a debug composer. */
struct KzuDebugComposer* kzuDebugComposerFromComposer(const struct KzuComposer* composer);

/** Set bounding box display status. */
void kzuDebugComposerSetBoundingBoxesEnabled(struct KzuDebugComposer* debugComposer, kzBool enabled);
/** Tell if bounding boxes are displayed. */
kzBool kzuDebugComposerIsBoundingBoxesEnabled(const struct KzuDebugComposer* debugComposer);
/** Set grid display status. */
void kzuDebugComposerSetGridEnabled(struct KzuDebugComposer* debugComposer, kzBool enabled);
/** Tell if grid is displayed. */
kzBool kzuDebugComposerIsGridEnabled(const struct KzuDebugComposer* debugComposer);
/** Set debug objects display status. */
void kzuDebugComposerSetDebugObjectsEnabled(struct KzuDebugComposer* debugComposer, kzBool enabled);
/** Tell if debug objects are displayed. */
kzBool kzuDebugComposerIsDebugObjectsEnabled(const struct KzuDebugComposer* debugComposer);
/** Set allocated size display status. */
void kzuDebugComposerSetAllocatedSizeEnabled(struct KzuDebugComposer* debugComposer, kzBool enabled);
/** Get allocated size display status. */
kzBool kzuDebugComposerIsAllocatedSizeEnabled(const struct KzuDebugComposer* debugComposer);
/** Set actual size display status. */
void kzuDebugComposerSetActualSizeEnabled(struct KzuDebugComposer* debugComposer, kzBool enabled);
/** Get actual size display status. */
kzBool kzuDebugComposerIsActualSizeEnabled(const struct KzuDebugComposer* debugComposer);
/** Set selection display status. */
void kzuDebugComposerSetSelectionEnabled(struct KzuDebugComposer* debugComposer, kzBool enabled);
/** Get selection display status. */
kzBool kzuDebugComposerIsSelectionEnabled(const struct KzuDebugComposer* debugComposer);
/** Tell if transform gizmo exists and is enabled. */
kzBool kzuDebugComposerIsTransformGizmoEnabled(const struct KzuDebugComposer* debugComposer);
/** Set the preview system. */
void kzuDebugComposerSetPreviewSystem(struct KzuDebugComposer* debugComposer, struct KzuPreviewSystem* previewSystem);


KZ_HEADER_END


#endif
