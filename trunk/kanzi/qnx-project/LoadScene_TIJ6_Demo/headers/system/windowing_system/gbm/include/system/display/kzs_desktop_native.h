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

int kzsDesktopNativeGetHandle(const struct KzsDesktopNative* desktopNative);

kzsError kzsDesktopNativeRemoveFB(const struct KzsDesktopNative* desktopNative, uint32_t fb_id);
kzsError kzsDesktopNativeAddFB(const struct KzsDesktopNative* desktopNative, uint32_t width, uint32_t height, uint32_t stride, uint32_t handle, uint32_t* fb_id);
kzsError kzsDesktopNativePageFlip(const struct KzsDesktopNative* desktopNative, int fb_id);
kzsError kzsDesktopNativeModeSet(const struct KzsDesktopNative* desktopNative, int fb_id);


KZ_HEADER_END


#endif
