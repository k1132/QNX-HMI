/**
* \file
* Kanzi surface configuration, NoGL implementation.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZS_SURFACE_CONFIGURATION_NATIVE_H
#define KZS_SURFACE_CONFIGURATION_NATIVE_H


#include <system/kzs_header.h>


KZ_HEADER_BEGIN

/* Forward declarations. */
struct KzsSurfaceConfigurationNative;

/** Gets pointer to GLX visual info describing the surface configuration. */
void* kzsSurfaceConfigurationNativeGetGLXVisualInfo(const struct KzsSurfaceConfigurationNative* configurationNative);

/** Gets requested screen depth, even when GLX visual info is null. */
int kzsSurfaceConfigurationNativeGetGLXDepth(const struct KzsSurfaceConfigurationNative* configurationNative);


KZ_HEADER_END


#endif
