/**
* \file
* Screen container canvas.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_CANVAS_H
#define KZU_CANVAS_H


#include <system/debug/kzs_error.h>
#include <system/display/kzs_window.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations */
struct KzuScreen;
struct KzcMemoryManager;


/**
 * \struct KzuCanvas
 * A Canvas designed for holding screens.
 */
struct KzuCanvas;


/** Create canvas object. */
kzsError kzuCanvasCreate(const struct KzcMemoryManager* memoryManager, struct KzuScreen* screen, struct KzuCanvas** out_canvas);
/** Delete canvas. */
kzsError kzuCanvasDelete(struct KzuCanvas* canvas);

/** Sets canvas size. */
void kzuCanvasSetSize(struct KzuCanvas* canvas, kzUint width, kzUint height);
/** Gets canvas width. */
kzUint kzuCanvasGetWidth(const struct KzuCanvas* canvas);
/** Gets canvas height. */
kzUint kzuCanvasGetHeight(const struct KzuCanvas* canvas);

/** Sets canvas orientation angle. */
void kzuCanvasSetOrientationAngle(struct KzuCanvas* canvas, enum KzsWindowOrientationAngle angle);
/** Gets canvas orientation angle. */
enum KzsWindowOrientationAngle kzuCanvasGetOrientationAngle(const struct KzuCanvas* canvas);

/** Sets the orientation of the screen. */
kzsError kzuCanvasSetScreenOrientation(struct KzuCanvas* canvas, enum KzsWindowOrientation orientation);

/** Sets screen of canvas. */
kzsError kzuCanvasSetScreen(struct KzuCanvas* canvas, struct KzuScreen* screen);
/** Gets screen of canvas. */
struct KzuScreen* kzuCanvasGetScreen(const struct KzuCanvas* canvas);

/** Invalidates the layout of the attached screen. */
void kzuCanvasInvalidateScreenLayout(struct KzuCanvas* canvas);

KZ_HEADER_END


#endif
