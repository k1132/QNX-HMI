/**
* \file
* Kanzi surface configuration, AGL implementation.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZS_SURFACE_CONFIGURATION_NATIVE_H
#define KZS_SURFACE_CONFIGURATION_NATIVE_H


#include <AGL/agl.h>

#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations. */
struct KzsSurfaceConfigurationNative;

/** Gets native AGL pixel format. */
AGLPixelFormat kzsSurfaceConfigurationNativeGetAGLPixelFormat(const struct KzsSurfaceConfigurationNative* configurationNative);


KZ_HEADER_END


#endif