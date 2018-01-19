/**
* \file
* Kanzi window, native portion for the win32 platform.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZS_WINDOW_NATIVE_H
#define KZS_WINDOW_NATIVE_H


#include <system/debug/kzs_error.h>
#include <system/kzs_types.h>
#include <system/wrappers/kzs_opengl_base.h>
#if (KZ_OPENGL_VERSION == KZ_OPENGL_ES_2_0) || (KZ_OPENVG_VERSION != KZ_OPENVG_NONE)
#include <system/display/kzs_egl.h>
#endif
#include <system/kzs_header.h>

#include <windows.h>


KZ_HEADER_BEGIN


/* Forward declarations. */
struct KzsDesktopNative;
struct KzsDisplayNative;
struct KzsEventQueue;


/** 
 * \struct KzsWindowNative Native window for Win32.
 */
struct KzsWindowNative;
struct KzsWindowProperties;


/** Creates empty wrapper window for a given window handle. */
kzsError kzsWindowNativeCreateWrapper(HWND windowHandle, struct KzsWindowProperties* out_windowProperties, struct KzsWindowNative** out_windowNative);

/** Returns the win32 window handle. */
HWND kzsWindowNativeGetHandle(const struct KzsWindowNative* windowNative);

/** Sets touch state for native window. */
void kzsWindowNativeSetTouchState(struct KzsWindowNative* windowNative, kzBool inTouch);

/** Gets touch state for native window. */
kzBool kzsWindowNativeGetTouchState(struct KzsWindowNative* windowNative);

/** Returns the win32 device context handle. */
HDC kzsWindowNativeGetHDC(const struct KzsWindowNative* windowNative);

#if (KZ_OPENGL_VERSION == KZ_OPENGL_ES_2_0) || (KZ_OPENVG_VERSION != KZ_OPENVG_NONE)
/** Gets EGL native window type. */
EGLNativeWindowType kzsEGLGetNativeWindow(const struct KzsWindowNative* windowNative);

/** Gets EGL native display type. */
EGLNativeDisplayType kzsEGLGetNativeDisplay(const struct KzsDesktopNative* desktopNative,
                                            const struct KzsDisplayNative* displayNative,
                                            const struct KzsWindowNative* windowNative);
#endif


KZ_HEADER_END


#endif
