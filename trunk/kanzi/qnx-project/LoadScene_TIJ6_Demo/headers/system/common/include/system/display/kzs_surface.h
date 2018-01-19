/**
* \file
* Drawable surface.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZS_SURFACE_H
#define KZS_SURFACE_H


#include <system/debug/kzs_error.h>
#include <system/kzs_types.h>
#include <system/input/kzs_input.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations. */
struct KzsDesktop;
struct KzsDisplay;
struct KzsWindow;
struct KzsSurfaceNative;
struct KzsSurfaceProperties;
struct KzsSurfaceConfiguration;
struct KzsSurfaceConfigurationNative;
struct KzsWindowNative;


/** Indicates that the implementation can choose any value for a surface property. */
#define KZS_SURFACE_PROPERTY_DONT_CARE -1


/**
 * \struct KzsSurface
 * Surface for graphics output.
 */
struct KzsSurface;


/**
 * Creates a drawable surface for a window. Graphics context of the new surface is shared with the currently
 * active surface if the rendering APIs match. This function may change the active surface.
 */
kzsError kzsSurfaceCreate(const struct KzsDesktop* desktop, const struct KzsDisplay* display,
                          const struct KzsSurfaceConfiguration* configuration,
                          const struct KzsWindow* window, struct KzsSurface** out_surface);

/** Deletes a surface and frees all memory allocated for it. */
kzsError kzsSurfaceDelete(struct KzsSurface* surface);

/** Makes a surface active for drawing or deactivates it. Only one surface can be active at a time. */
kzsError kzsSurfaceSetActive(const struct KzsSurface* surface, kzBool active);

/** Updates the buffer to the screen. */
kzsError kzsSurfaceUpdate(const struct KzsSurface* surface);

/** Resizes the surface. */
kzsError kzsSurfaceResize(struct KzsSurface* surface, kzUint width, kzUint height);

/**
 * Specifies the minimum number of video frame periods per buffer swap.
 * Negative interval values are reserved for platform-specific special cases.
 */
kzsError kzsSurfaceSetSwapInterval(struct KzsSurface* surface, kzInt interval);

/** Reads pixels from the surface. */
kzsError kzsSurfaceReadPixels(const struct KzsSurface* surface, void* out_pixels);

/** Creates a native surface. */
kzsError kzsSurfaceNativeCreate(const struct KzsDesktop* desktop, const struct KzsDisplay* display,
                                const struct KzsSurfaceConfiguration* configuration,
                                const struct KzsWindow* window, struct KzsSurfaceNative** out_surfaceNative);

/** Deletes a native surface and frees all memory allocated for it. */
kzsError kzsSurfaceNativeDelete(struct KzsSurfaceNative* surfaceNative);

/** Sets surface active. */
kzsError kzsSurfaceNativeSetActive(struct KzsSurfaceNative* surfaceNative, kzBool active);

/** Updates the surface. */
kzsError kzsSurfaceNativeUpdate(struct KzsSurfaceNative* surfaceNative);

#ifdef OSX
/** Resizes the surface. */
kzsError kzsSurfaceNativeResize(struct KzsSurfaceNative* surfaceNative, kzUint width, kzUint height);
#endif

/**
 * Specifies the minimum number of video frame periods per buffer swap.
 * Negative interval values are reserved for platform-specific special cases.
 */
kzsError kzsSurfaceNativeSetSwapInterval(struct KzsSurfaceNative* surfaceNative, kzInt interval);

/** Copy color buffer data to the preallocated buffer out_pixels. */
kzsError kzsSurfaceNativeReadPixels(struct KzsSurfaceNative* surfaceNative, void* out_pixels);

/** Function for creating native image object, which can be shared between client APIs. */
kzsError kzsSurfaceNativeCreateImage(void* display, void* context, kzInt target, void* data, kzInt* attributes, void** out_image);
/** Function for deleting native image object. */
kzsError kzsSurfaceNativeDeleteImage(void* display, void* image);

/** Gets the display from native surface. */
void* kzsSurfaceNativeGetDisplay(struct KzsSurfaceNative* surfaceNative);

/** Gets the context from native surface. */
void* kzsSurfaceNativeGetContext(struct KzsSurfaceNative* surfaceNative);

/** Get native surface from surface. */
struct KzsSurfaceNative* kzsSurfaceGetNativeSurface(const struct KzsSurface* surface);
/** Get list of native surface extensions. */
kzString kzsSurfaceNativeGetExtensions(struct KzsSurfaceNative* surfaceNative);

/** Sets used surface settings to the given surface properties struct. */
kzsError kzsSurfaceGetUsedSurfaceProperties(const struct KzsSurface* surface, struct KzsSurfaceProperties* out_surfaceProperties);
/** Sets used surface settings to the given surface properties struct. */
kzsError kzsSurfaceGetUsedSurfaceNativeProperties(const struct KzsSurfaceNative* surfaceNative, struct KzsSurfaceProperties* out_surfaceProperties);


KZ_HEADER_END


#endif
