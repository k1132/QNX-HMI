/**
* \file
* AGL functions.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZS_AGL_H
#define KZS_AGL_H


#include <system/debug/kzs_error.h>
#include <system/kzs_types.h>
#include <system/kzs_header.h>

#include <AGL/agl.h>


KZ_HEADER_BEGIN


/** Returns an AGL configuration attribute. */
kzsError kzsAGLDescribePixelFormat(const AGLPixelFormat pixelFormat, kzInt attribute, kzInt *out_value);

/** Sets the AGL swap interval parameter. */
kzsError kzsAGLSwapInterval(AGLContext ctx, kzInt interval);


KZ_HEADER_END


#endif
