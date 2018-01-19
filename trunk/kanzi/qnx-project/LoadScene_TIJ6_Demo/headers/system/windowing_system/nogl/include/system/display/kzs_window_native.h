/**
* \file
* Kanzi window, dummy implementation.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZS_WINDOW_NATIVE_H
#define KZS_WINDOW_NATIVE_H


#include <system/wrappers/kzs_opengl.h>
#if KZ_OPENGL_VERSION == KZ_OPENGL_ES_2_0
#include <system/display/kzs_egl.h>
#endif
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations. */
struct KzsDesktopNative;
struct KzsDisplayNative;


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
