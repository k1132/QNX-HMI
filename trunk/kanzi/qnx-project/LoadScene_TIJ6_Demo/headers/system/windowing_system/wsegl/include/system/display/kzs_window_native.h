/**
* \file
* Kanzi window, dummy implementation.
* 
* Copyright 2008-2013 by Rightware. All rights reserved.
*/
#ifndef KZS_WINDOW_NATIVE_H
#define KZS_WINDOW_NATIVE_H

#include <EGL/egl.h>
#include <system/display/kzs_egl.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN

#define __WSEGL__

/* Forward declarations. */
struct KzsDesktopNative;
struct KzsDisplayNative;
struct KzsWindowNative;


/** Gets EGL native window. */
EGLNativeWindowType kzsEGLGetNativeWindow(const struct KzsWindowNative* windowNative);
/** Gets EGL native display. */
EGLNativeDisplayType kzsEGLGetNativeDisplay(const struct KzsDesktopNative* desktopNative, const struct KzsDisplayNative* displayNative, const struct KzsWindowNative* windowNative);

/** . */
kzsError kzsWindowNativeSetEGLSurface(struct KzsWindowNative* windowNative, EGLSurface* surface, EGLDisplay* display);


KZ_HEADER_END


#endif
