/**
* \file
* Kanzi display, native portion for the win32 platform.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZS_DISPLAY_NATIVE_H
#define KZS_DISPLAY_NATIVE_H


#include <windows.h>

#include <system/kzs_types.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN

    
/* Forward declarations. */
struct KzsDisplayNative;


/** Returns the name of the display adapter device. */
LPCTSTR kzsDisplayNativeGetDeviceName(const struct KzsDisplayNative* displayNative);

/** Returns the x coordinate of the display with respect to the desktop. */
kzUint kzsDisplayNativeGetCurrentX(const struct KzsDisplayNative* displayNative);
/** Returns the y coordinate of the display with respect to the desktop. */
kzUint kzsDisplayNativeGetCurrentY(const struct KzsDisplayNative* displayNative);


KZ_HEADER_END


#endif
