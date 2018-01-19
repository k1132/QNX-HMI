/**
 * \file
 * Application framework.
 * 
 * Copyright 2008-2014 by Rightware. All rights reserved.
 */
#ifndef KZA_APPLICATION_PREVIEW_OPTIONS_H
#define KZA_APPLICATION_PREVIEW_OPTIONS_H


#include <system/kzs_types.h>
#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations */
struct KzaApplication;
struct KzcHashMap;


/** Enables or disables debug objects. */
void kzaApplicationSetDebugObjectsEnabled(const struct KzaApplication* application, kzBool enabled);
/** Checks if debug objects are enabled. */
kzBool kzaApplicationIsDebugObjectsEnabled(const struct KzaApplication* application);

/** Sets grid enabled or not. */
void kzaApplicationSetGridEnabled(const struct KzaApplication* application, kzBool enabled);
/** Checks if grid is enabled or not. */
kzBool kzaApplicationIsGridEnabled(const struct KzaApplication* application);

/** Sets selection indicators enabled or not. */
void kzaApplicationSetSelectionVisualizationEnabled(const struct KzaApplication* application, kzBool enabled);
/** Checks if selection indicators are enabled or not. */
kzBool kzaApplicationIsSelectionVisualizationEnabled(const struct KzaApplication* application);


/** Sets allocated layout bounding box visualization enabled or disabled. */
void kzaApplicationSetAllocatedLayoutBoundingBoxVisualizationEnabled(const struct KzaApplication* application, kzBool enabled);
/** Checks if allocated layout bounding box visualization is enabled or not. */
kzBool kzaApplicationIsAllocatedLayouBoundingBoxVisualizationEnabled(const struct KzaApplication* application);
/** Sets actual layout bounding box visualization enabled or disabled. */
void kzaApplicationSetActualLayoutBoundingBoxVisualizationEnabled(const struct KzaApplication* application, kzBool enabled);
/** Checks if actual layout bounding box visualization is enabled or not. */
kzBool kzaApplicationIsActualLayoutBoundingBoxVisualizationEnabled(const struct KzaApplication* application);
/** Sets background checker visualization enabled. */
void kzaApplicationSetBackgroundCheckerVisualizationEnabled(struct KzaApplication* application, kzBool enabled);
/** Returns if background checker visualization is enabled. */
kzBool kzaApplicationIsBackgroundCheckerVisualizationEnabled(const struct KzaApplication* application);


/** Enables the preview system. */
kzsError kzaApplicationEnablePreviewSystem(struct KzaApplication* application);
/** Gets the preview system. Returns KZ_NULL if the preview system is not enabled. */
struct KzuPreviewSystem* kzaApplicationGetPreviewSystem(const struct KzaApplication* application);


KZ_HEADER_END


#endif
