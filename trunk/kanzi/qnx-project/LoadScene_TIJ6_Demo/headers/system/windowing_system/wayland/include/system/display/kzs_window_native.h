/**
* \file
* Kanzi window, dummy implementation.
* 
* Copyright 2008-2013 by Rightware. All rights reserved.
*/
#ifndef KZS_WINDOW_NATIVE_H
#define KZS_WINDOW_NATIVE_H

#define __WAYLAND__

#include <EGL/egl.h>
#include <system/display/kzs_egl.h>
#include <system/kzs_header.h>

#include <wayland-client.h>
#include <wayland-egl.h>

KZ_HEADER_BEGIN

/* Forward declarations. */
struct KzsDesktopNative;
struct KzsDisplayNative;
struct KzsWindowNative;


/** Gets EGL native window. */
EGLNativeWindowType kzsEGLGetNativeWindow(const struct KzsWindowNative* windowNative);

void kzsWindowNativeSwapBuffers(struct KzsWindowNative* windowNative);

KZ_HEADER_END


#endif
