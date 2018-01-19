/**
* \file
* Kanzi display, native portion for fbdev.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZS_DISPLAY_NATIVE_H
#define KZS_DISPLAY_NATIVE_H

#include <system/display/kzs_egl.h>

#include <system/kzs_header.h>


KZ_HEADER_BEGIN


struct KzsDesktopNative;
struct KzsDisplayNative;
struct KzsWindowNative;

/** Gets EGL native display type. */
EGLNativeDisplayType kzsEGLGetNativeDisplay(const struct KzsDesktopNative* desktopNative,
                                            const struct KzsDisplayNative* displayNative,
                                            const struct KzsWindowNative* windowNative);

KZ_HEADER_END


#endif
