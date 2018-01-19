/**
* \file
* Kanzi surface configuration, EGL implementation.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZS_SURFACE_CONFIGURATION_NATIVE_H
#define KZS_SURFACE_CONFIGURATION_NATIVE_H


#include <system/kzs_header.h>
#include <system/display/kzs_egl.h>


KZ_HEADER_BEGIN


/* Forward declarations. */
struct KzsSurfaceConfigurationNative;

/** Gets pointer to GLX visual info describing the surface configuration. */
void* kzsSurfaceConfigurationNativeGetGLXVisualInfo(const struct KzsSurfaceConfigurationNative* configurationNative);

/** Gets EGL configuration attribute array. */
const EGLint* kzsSurfaceConfigurationNativeGetEGLAttributeArray(const struct KzsSurfaceConfigurationNative* configurationNative);

/** Gets EGL API. */
EGLenum kzsSurfaceConfigurationNativeGetAPI(const struct KzsSurfaceConfigurationNative* configurationNative);


KZ_HEADER_END


#endif