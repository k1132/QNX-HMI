/**
* \file
* Screen container window.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_WINDOW_H
#define KZU_WINDOW_H


#include <system/debug/kzs_error.h>
#include <system/display/kzs_window.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations */
struct KzuCanvas;
struct KzcMemoryManager;
struct KzsDesktop;
struct KzsDisplay;
struct KzsSurfaceConfiguration;
struct KzsWindow;
struct KzsSurface;
struct KzsWindowProperties;


/**
 * \struct KzuWindow
 * A Window designed for holding a canvas.
 */
struct KzuWindow;


/** Create window object. */
kzsError kzuWindowCreate(const struct KzcMemoryManager* memoryManager, struct KzsWindow* childWindow,
                         struct KzsSurface* surface, struct KzuCanvas* canvas, struct KzuWindow** out_window);
/** Delete window. */
kzsError kzuWindowDelete(struct KzuWindow* window);

/** Synchronizes screen properties to system-dependent window properties. */
kzsError kzuWindowUpdate(struct KzuWindow* window);

/** Makes window surface active. */
kzsError kzuWindowPreRender(const struct KzuWindow* window);

/** Makes surface changes visible. */
kzsError kzuWindowPostRender(const struct KzuWindow* window);

/** Sets the title bar string for the window, if any. */
kzsError kzuWindowSetTitle(const struct KzuWindow* window, kzString titleText);

/** Makes newly created window visible. */
kzsError kzuWindowShow(struct KzuWindow* window);

/** Resizes the window. */
kzsError kzuWindowResize(struct KzuWindow* window, kzUint width, kzUint height);

/** Sets window orientation. */
kzsError kzuWindowSetOrientation(struct KzuWindow* window, enum KzsWindowOrientation orientation);
/** Sets window orientation angle. */
void kzuWindowSetOrientationAngle(struct KzuWindow* window, enum KzsWindowOrientationAngle angle);

/** Sets system-dependent window object. */
kzsError kzuWindowSetWindow(struct KzuWindow* window, struct KzsWindow* nativeWindow);
/** Returns system-dependent window object. */
struct KzsWindow* kzuWindowGetWindow(const struct KzuWindow* window);

/** Sets canvas of window. */
kzsError kzuWindowSetCanvas(struct KzuWindow* window, struct KzuCanvas* canvas);
/** Gets canvas of window. */
struct KzuCanvas* kzuWindowGetCanvas(const struct KzuWindow* window);

/** Sets surface from window. Useful if created empty window that doesn't contain surface in the beginning. */
void kzuWindowSetSurface(struct KzuWindow* window, struct KzsSurface* surface);
/** Gets surface from window. */
struct KzsSurface* kzuWindowGetSurface(const struct KzuWindow* window);

/** Reads pixel data from window surface to out_pixels. out_pixels must be preallocated to correct size.*/
kzsError kzuWindowReadPixels(const struct KzuWindow* window, void* out_pixels);


KZ_HEADER_END


#endif
