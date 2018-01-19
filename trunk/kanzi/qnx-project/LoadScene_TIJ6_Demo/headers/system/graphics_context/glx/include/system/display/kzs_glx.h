/**
* \file
* GLX functions.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZS_GLX_H
#define KZS_GLX_H


#include <system/debug/kzs_error.h>
#include <system/kzs_types.h>
#include <system/input/kzs_input.h>
#include <system/display/kzs_window.h>
#include <system/wrappers/kzs_opengl_base.h>
#include <system/kzs_header.h>

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xatom.h>
#include <GL/gl.h>
#include <GL/glx.h>


KZ_HEADER_BEGIN


/** Initializes the GLX context. */
kzsError kzsGLXContextInitialize(Display* display, XVisualInfo *visualInfo, GLXContext shareList, GLXContext* out_glxContext);

/** Deinitializes the GLX context. */
kzsError kzsGLXContextDeinitialize(Display* display, GLXContext context);

/** Makes the GLX surface active. */
kzsError kzsGLXMakeCurrent(Display* display, Window window, GLXContext context);

/** Updates the GLX surface on the screen. */
kzsError kzsGLXUpdateSurface(Display* display, Window window);

/** Sets the swap interval. */
kzsError kzsGLXSwapInterval(kzInt interval);

/** Returns an GLX configuration attribute. */
kzsError kzsGLXGetConfig(Display* display, XVisualInfo* visualInfo, kzInt attribute, kzInt* out_value);


KZ_HEADER_END


#endif
