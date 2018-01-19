/**
* \file
* Kanzi surface configuration, WGL implementation.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZS_SURFACE_CONFIGURATION_NATIVE_H
#define KZS_SURFACE_CONFIGURATION_NATIVE_H


#include <windows.h>

#include <system/kzs_types.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations. */
struct KzsSurfaceConfigurationNative;


/** Gets native WGL configuration attribute array. */
const int* kzsSurfaceConfigurationNativeGetWGLAttributeArray(const struct KzsSurfaceConfigurationNative* configurationNative);

/** Returns function pointer to wglChoosePixelFormatARB. */
BOOL (WINAPI *kzsSurfaceConfigurationNativeGetChoosePixelFormatARB(const struct KzsSurfaceConfigurationNative* configurationNative))(HDC, const int*, const FLOAT*, UINT, int*, UINT*);


KZ_HEADER_END


#endif