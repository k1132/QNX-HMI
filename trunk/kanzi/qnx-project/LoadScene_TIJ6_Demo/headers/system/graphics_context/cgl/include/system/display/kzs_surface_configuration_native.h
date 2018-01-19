/**
* \file
* Kanzi surface configuration, CGL implementation.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZS_SURFACE_CONFIGURATION_NATIVE_H
#define KZS_SURFACE_CONFIGURATION_NATIVE_H

#ifdef __OBJC__
#import <Cocoa/Cocoa.h>
#endif

#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations. */
struct KzsSurfaceConfigurationNative;


#ifdef __OBJC__
/** Gets native CGL pixel format. */
NSOpenGLPixelFormat* kzsSurfaceConfigurationNativeGetCGLPixelFormat(const struct KzsSurfaceConfigurationNative* configurationNative);
#endif


KZ_HEADER_END


#endif
