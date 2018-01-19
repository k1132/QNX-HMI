/**
* \file
* Kanzi window, native part for Android platform.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZS_WINDOW_NATIVE_H
#define KZS_WINDOW_NATIVE_H


#include <system/debug/kzs_error.h>
#include <system/kzs_types.h>
#include <system/input/kzs_input.h>
#include <system/display/kzs_window.h>
#include <system/wrappers/kzs_opengl.h>
#include <system/display/kzs_egl.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Foward declarations. */
struct ANativeWindow;
struct KzsDesktopNative;
struct KzsDisplayNative;
struct KzsWindowNative;


/** Creates native window from Android window. */
kzsError kzsWindowNativeCreateWrapper(ANativeWindow* windowHandle, struct KzsWindowNative** out_windowNative);

/** Retrieve Android window (originates from Java side Surface) from native window. */
ANativeWindow* kzsWindowNativeGetAndroidWindow(const struct KzsWindowNative* windowNative);
/** Pass Android window (originates from Java side Surface) to native window. */
kzsError kzsWindowNativeSetAndroidNativeWindow(struct KzsWindowNative* windowNative, ANativeWindow* androidNativeWindow);

#if KZ_OPENGL_VERSION == KZ_OPENGL_ES_2_0
/** Gets EGL native window type. */
EGLNativeWindowType kzsEGLGetNativeWindow(const struct KzsWindowNative* windowNative);
/** Gets EGL native display type. */
EGLNativeDisplayType kzsEGLGetNativeDisplay(const struct KzsDesktopNative* desktopNative,
                                            const struct KzsDisplayNative* displayNative,
                                            const struct KzsWindowNative* windowNative);
#endif


KZ_HEADER_END


#endif
