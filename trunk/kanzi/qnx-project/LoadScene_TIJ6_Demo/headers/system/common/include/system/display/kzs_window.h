/**
* \file
* Window handling.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZS_WINDOW_H
#define KZS_WINDOW_H


#include <system/debug/kzs_error.h>
#include <system/kzs_types.h>
#include <system/display/kzs_surface_configuration.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations. */
struct KzsDisplay;
struct KzsSurface;
struct KzsInputEventPointer;
struct KzsInputEventKey;
struct KzsWindowNative;
struct KzsSurfaceConfigurationNative;


/**
 * \struct KzsWindow
 * Kanzi window structure.
 */
struct KzsWindow;


/** List of window orientation angles. */
enum KzsWindowOrientationAngle
{
    KZS_WINDOW_ORIENTATION_ANGLE_0, /**< 0 degrees. */
    KZS_WINDOW_ORIENTATION_ANGLE_180 /**< 180 degrees. */
};

/** Enumeration for different window styles. */
enum KzsWindowStyle
{
    KZS_WINDOW_STYLE_FIXED,                     /**< A window that cannot be resized. */
    KZS_WINDOW_STYLE_RESIZABLE,                 /**< A window that can be resized. */
    KZS_WINDOW_STYLE_FULL_SCREEN,               /**< Window occupies the whole screen. */
    KZS_WINDOW_STYLE_BORDERLESS,                /**< No borders or other decorations. */
    KZS_WINDOW_STYLE_STUDIO_PREVIEW,            /**< Docked window with external message handling. Should only be used by Kanzi Studio. */
    KZS_WINDOW_STYLE_DEFAULT                    /**< Let the system choose the appropriate window style for the platform. */
};

/**
 * Properties for a window.
 * Position is defined as the distance from the top-left corner of the desktop to the top-left corner of the window, measured towards the center of the desktop.
 * If style is set to KZS_WINDOW_STYLE_FULL_SCREEN, the window position is ignored and the primary screen resolution is changed to match the requested window size.
 * If both width and height is set to zero, no change of resolution is attempted.
 */
struct KzsWindowProperties
{
    kzInt x;                        /**< X position of the window (in pixels). Use 0 to let the system choose the position. */
    kzInt y;                        /**< Y position of the window (in pixels). Use 0 to let the system choose the position. */
    kzUint width;                   /**< Width of the window (in pixels). Use 0 to use the maximum width available on the primary screen. */
    kzUint height;                  /**< Height of the window (in pixels). Use 0 to use the maximum height available on the primary screen. */
    enum KzsWindowStyle style;      /**< Style properties of the window. */
};


/** Creates a window with a previously created native window. Takes ownership of the native window. */
kzsError kzsWindowCreateFromNative(struct KzsWindowNative* windowNative, const struct KzsWindowProperties* windowProperties, 
                                   struct KzsWindow** out_window);
/** Creates a window and returns it. */
kzsError kzsWindowCreate(const struct KzsDesktop* desktop, const struct KzsDisplay* display,
                         const struct KzsWindowProperties* windowPropertiesRequested,
                         const struct KzsSurfaceConfiguration* configuration, struct KzsWindow** out_window);

/** Deletes a window. */
kzsError kzsWindowDelete(struct KzsWindow* window);

/** Resizes the window. */
kzsError kzsWindowResize(const struct KzsWindow* window, kzUint width, kzUint height);

/** Sets the absolute position the window, if supported by the platform. */
kzsError kzsWindowSetPositionAbsolute(const struct KzsWindow* window, kzUint x, kzUint y);

/** Makes newly created window visible. */
kzsError kzsWindowShow(struct KzsWindow* window);

/** Sets the title bar string for the window, if supported by the platform. */
kzsError kzsWindowSetTitle(const struct KzsWindow* window, kzString titleText);

/** Gets the width of the window. */
kzUint kzsWindowGetCurrentWidth(const struct KzsWindow* window);
/** Gets the height of the window. */
kzUint kzsWindowGetCurrentHeight(const struct KzsWindow* window);

/** Gets the native window. */
struct KzsWindowNative* kzsWindowGetNative(const struct KzsWindow* window);


/** Creates a native window. */
kzsError kzsWindowNativeCreate(const struct KzsDesktop* desktop, const struct KzsDisplay* display,
    const struct KzsWindowProperties* windowPropertiesRequested,
    const struct KzsSurfaceConfigurationNative* configurationNative,
    struct KzsWindowProperties* out_windowProperties, struct KzsWindowNative** out_windowNative);

/** Initializes window. Called after creating window and native window. */
kzsError kzsWindowNativeInitialize(struct KzsWindowNative* windowNative, struct KzsWindow* window);

/** Deletes a native window. */
kzsError kzsWindowNativeDelete(struct KzsWindowNative* windowNative);

/** Resizes the window. Native implementation. */
kzsError kzsWindowNativeResize(const struct KzsWindowNative* windowNative, kzUint width, kzUint height);

/** Sets the absolute position the window, if supported by the platform. Native implementation. */
kzsError kzsWindowNativeSetPositionAbsolute(const struct KzsWindowNative* windowNative, kzUint x, kzUint y);

/** Makes newly created window visible. */
kzsError kzsWindowNativeShow(struct KzsWindowNative* windowNative);

/** Sets the title bar string for the window, if supported by the platform. Native implementation. */
kzsError kzsWindowNativeSetTitle(const struct KzsWindowNative* windowNative, kzString titleText);

/** Gets the width of the window. */
kzUint kzsWindowNativeGetCurrentWidth(const struct KzsWindowNative* windowNative);
/** Gets the height of the window. */
kzUint kzsWindowNativeGetCurrentHeight(const struct KzsWindowNative* windowNative);


KZ_HEADER_END


#endif
