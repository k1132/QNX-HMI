/**
* \file
* Kanzi desktop, native portion for the OpenKODE platform.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZS_DESKTOP_NATIVE_H
#define KZS_DESKTOP_NATIVE_H


#include <system/kzs_header.h>

#include <KD/NV_display.h>


KZ_HEADER_BEGIN


/* Forward declarations. */
struct KzsDesktopNative;


/** Gets OpenKODE native system. */
KDDisplaySystemNV* kzsDesktopNativeGetKDSystem(const struct KzsDesktopNative* desktopNative);


KZ_HEADER_END


#endif
