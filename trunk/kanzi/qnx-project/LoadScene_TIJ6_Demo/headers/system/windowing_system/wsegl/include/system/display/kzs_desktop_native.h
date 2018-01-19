/**
* \file
* Kanzi desktop, WSEGL implementation.
* 
* Copyright 2008-2013 by Rightware. All rights reserved.
*/
#ifndef KZS_DESKTOP_NATIVE_H
#define KZS_DESKTOP_NATIVE_H


#include <system/display/kzs_egl.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


struct KzsDesktopNative;
struct KzsWindowNative;


/** Gets EGL native display type. */
NativeDisplayType kzsWindowNativeGetEGLNativeDisplayType(const struct KzsDesktopNative* desktopNative, const struct KzsWindowNative* windowNative);


KZ_HEADER_END


#endif
