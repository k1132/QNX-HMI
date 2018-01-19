/**
* \file
* Kanzi window, native part for X11-GLX platform.
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
#if KZ_OPENGL_VERSION == KZ_OPENGL_ES_2_0
#include <system/display/kzs_egl.h>
#endif
#include <system/kzs_header.h>

#include <X11/Xlib.h>


KZ_HEADER_BEGIN


struct KzsWindowNative;


Window kzsWindowNativeGetWindow(const struct KzsWindowNative* windowNative);

#if KZ_OPENGL_VERSION == KZ_OPENGL_ES_2_0
/** Gets EGL native window type. */
EGLNativeWindowType kzsEGLGetNativeWindowType(const struct KzsWindowNative* windowNative);

#endif


KZ_HEADER_END


#endif
