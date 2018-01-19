/**
* \file
* Kanzi display, dummy implementation.
* 
* Copyright 2008-2013 by Rightware. All rights reserved.
*/
#ifndef KZS_DISPLAY_NATIVE_H
#define KZS_DISPLAY_NATIVE_H

#include <wayland-client.h>
#include <EGL/egl.h>
#include <system/kzs_header.h>

#include "kzs_window_native.h"
#include "kzs_desktop_native.h"

KZ_HEADER_BEGIN

struct KzsDesktopNative;
struct KzsDisplayNative;
struct KzsWindowNative;

struct wl_output* kzsDisplayNativeGetOutput(const struct KzsDisplayNative* displayNative);

KZ_HEADER_END

#endif
