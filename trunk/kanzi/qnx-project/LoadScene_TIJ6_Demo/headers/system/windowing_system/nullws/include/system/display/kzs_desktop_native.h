/**
* \file
* Kanzi desktop, native portion for NullWS.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZS_DESKTOP_NATIVE_H
#define KZS_DESKTOP_NATIVE_H


#include <system/display/kzs_egl.h>

#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations. */
struct KzsDesktopNative;
struct KzsDisplayNative;
struct KzsWindowNative;


/** Gets EGL native display type. */
NativeDisplayType kzsWindowNativeGetEGLNativeDisplay(const struct KzsDesktopNative* desktopNative,
                                                     const struct KzsDisplayNative* displayNative,
                                                     const struct KzsWindowNative* windowNative);


KZ_HEADER_END


#endif
