/**
* \file
* Kanzi window, native portion for Tegra (openKODE) platform.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZS_WINDOW_NATIVE_H
#define KZS_WINDOW_NATIVE_H


#include <system/debug/kzs_error.h>
#include <system/kzs_types.h>
#include <system/input/kzs_input.h>
#include <system/display/kzs_window.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


#include <KD/kd.h>
#include <KD/NV_display.h>


/* Forward declarations. */
struct KzsWindowNative;


KDWindow* kzsWindowNativeGetKDWindow(const struct KzsWindowNative* windowNative);

EGLNativeWindowType kzsEGLGetNativeWindow(const struct KzsWindowNative* windowNative);
kzsError kzsWindowNativeRealize(struct KzsWindowNative* windowNative, EGLDisplay eglDisplay, EGLConfig eglConfiguration);


KZ_HEADER_END


#endif
