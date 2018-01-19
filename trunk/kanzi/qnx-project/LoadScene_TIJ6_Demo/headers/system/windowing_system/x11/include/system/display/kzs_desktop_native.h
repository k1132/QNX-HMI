/**
* \file
* Kanzi desktop, native portion for the X11 platform.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZS_DESKTOP_NATIVE_H
#define KZS_DESKTOP_NATIVE_H


#include <system/wrappers/kzs_opengl.h>
#if KZ_OPENGL_VERSION == KZ_OPENGL_ES_2_0
#include <system/display/kzs_egl.h>
#endif
#if KZ_OPENGL_VERSION == KZ_OPENGL_2_1
#include <system/display/kzs_glx.h>
#endif

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xatom.h>

#include <system/kzs_header.h>


KZ_HEADER_BEGIN


struct KzsDesktopNative;
struct KzsDisplayNative;
struct KzsWindowNative;


/** Return the X11 display. */
Display* kzsDesktopNativeGetX11Display(const struct KzsDesktopNative* desktopNative);
XContext kzsDesktopNativeGetX11Context(const struct KzsDesktopNative* desktopNative);

#if KZ_OPENGL_VERSION == KZ_OPENGL_ES_2_0
/** Gets EGL native display type. */
EGLNativeDisplayType kzsEGLGetNativeDisplay(const struct KzsDesktopNative* desktopNative,
                                            const struct KzsDisplayNative* displayNative,
                                            const struct KzsWindowNative* windowNative);
#else
XVisualInfo* kzsDisplayNativeGetGLXVisualInfo(struct KzsDesktopNative* desktopNative);
#endif


KZ_HEADER_END


#endif
