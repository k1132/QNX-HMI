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

#include <wayland-client.h>

KZ_HEADER_BEGIN


struct KzsDesktopNative;
struct KzsWindowNative;
struct KzsDisplayNative;

void kzsDesktopNativeDispatch(const struct KzsDesktopNative* desktopNative);

void kzsDesktopNativeDispatchQueue(const struct KzsDesktopNative* desktopNative, struct wl_event_queue* queue);

struct wl_compositor* kzsDesktopNativeGetCompositor(const struct KzsDesktopNative* desktopNative);

struct wl_shell* kzsDesktopNativeGetShell(const struct KzsDesktopNative* desktopNative);

struct wl_display* kzsDesktopNativeGetDisplay(const struct KzsDesktopNative* desktopNative);

struct wl_seat* kzsDesktopNativeGetSeat(const struct KzsDesktopNative* desktopNative);

struct wl_output* kzsDesktopNativeGetOutput(const struct KzsDesktopNative* desktopNative, kzUint displayID);

struct wl_event_queue* kzsDesktopNativeGetDisplayQueue(const struct KzsDesktopNative* desktopNative, kzUint displayID);

/** Gets EGL native display. */
EGLNativeDisplayType kzsEGLGetNativeDisplay(const struct KzsDesktopNative* desktopNative, const struct KzsDisplayNative* displayNative, const struct KzsWindowNative* windowNative);

KZ_HEADER_END


#endif
