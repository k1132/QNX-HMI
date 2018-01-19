/**
* \file
* CGL functions.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZS_CGL_H
#define KZS_CGL_H


#include <system/debug/kzs_error.h>
#include <system/kzs_types.h>
#include <system/kzs_header.h>

#include <OpenGL/OpenGL.h>


KZ_HEADER_BEGIN


/** Returns a CGL configuration attribute. */
kzsError kzsCGLDescribePixelFormat(CGLPixelFormatObj pix, GLint pix_num, CGLPixelFormatAttribute attrib, GLint* out_value);

/** Sets the CGL swap interval parameter. */
kzsError kzsCGLSwapInterval(CGLContextObj ctx, kzInt interval);


KZ_HEADER_END


#endif
