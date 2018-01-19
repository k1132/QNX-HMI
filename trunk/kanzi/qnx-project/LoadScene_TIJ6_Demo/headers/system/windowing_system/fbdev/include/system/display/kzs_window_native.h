/**
* \file
* Kanzi window, native part for fbdev.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZS_WINDOW_NATIVE_H
#define KZS_WINDOW_NATIVE_H


#include <system/display/kzs_egl.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


struct KzsWindowNative;


/** Gets EGL native window type. */
EGLNativeWindowType kzsEGLGetNativeWindow(const struct KzsWindowNative* windowNative);


KZ_HEADER_END


#endif
