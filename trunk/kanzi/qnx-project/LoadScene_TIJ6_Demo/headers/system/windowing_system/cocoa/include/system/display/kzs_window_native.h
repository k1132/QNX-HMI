/**
* \file
* Kanzi window, native part for Cocoa platform.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZS_WINDOW_NATIVE_H
#define KZS_WINDOW_NATIVE_H


#ifdef __OBJC__
#import <system/display/kzs_cocoa_window.h>
#endif
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations. */
struct KzsWindowNative;


#ifdef __OBJC__
/** Returns native Cocoa window. */
KzsCocoaWindow* kzsWindowNativeGetCocoaWindow(const struct KzsWindowNative* windowNative);
#endif


KZ_HEADER_END


#endif
