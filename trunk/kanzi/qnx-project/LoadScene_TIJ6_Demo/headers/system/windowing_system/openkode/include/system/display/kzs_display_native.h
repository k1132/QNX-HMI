/**
* \file
* Kanzi display, native portion for the Tegra (openKODE) platform.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZS_DISPLAY_NATIVE_H
#define KZS_DISPLAY_NATIVE_H


#include <system/kzs_types.h>
#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>
#include <system/display/kzs_egl.h>


KZ_HEADER_BEGIN


/* Forward declarations. */
struct KzsDesktopNative;
struct KzsDisplayNative;


/** Gets EGL native display type. */
EGLNativeDisplayType kzsEGLGetNativeDisplay(const struct KzsDesktopNative* desktopNative,
                                            const struct KzsDisplayNative* displayNative,
                                            const struct KzsWindowNative* windowNative);


KZ_HEADER_END


#endif
