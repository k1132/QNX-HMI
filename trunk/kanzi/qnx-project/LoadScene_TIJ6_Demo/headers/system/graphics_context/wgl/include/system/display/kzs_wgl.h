/**
* \file
* WGL functions.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZS_WGL_H
#define KZS_WGL_H


#include <system/debug/kzs_error.h>
#include <system/kzs_types.h>
#include <system/input/kzs_input.h>
#include <system/display/kzs_window.h>
#include <system/wrappers/kzs_opengl_base.h>
#include <system/kzs_header.h>

#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/wglext.h>


KZ_HEADER_BEGIN


/* Forward declarations. */
struct KzsSurfaceProperties;
struct KzsWglDummyContext;


/** Creates a temporary rendering context. */
kzsError KzsWglDummyContextCreate(struct KzsWglDummyContext** out_dummyContext);

/** Destroys a temporary rendering context. */
kzsError KzsWglDummyContextDestroy(struct KzsWglDummyContext* dummyContext);

/* Test for OpenGL version.
*
* Opens the OpenGL library and saves some essential functions as a side effect. */
kzsError kzsWindowsTestOpenGLVersion(kzInt requestedMajor, kzInt requestedMinor, HMODULE* out_module);

/** Initializes an WGL display. */
kzsError kzsWGLSurfaceInitialize(HDC hdc, const struct KzsSurfaceConfigurationNative* configurationNative, HGLRC* out_hrc);

/** Uninitializes an WGL display. */
kzsError kzsWGLSurfaceUninitialize(HDC hdc, HGLRC hrc);

/** Gets active WGL rendering context. */
HGLRC kzsWGLGetCurrentContext(void);

/** Shares display-lists between WGL rendering contexts. */
kzsError kzsWGLShareLists(HGLRC hglrc1, HGLRC hglrc2);

/** Makes a WGL surface active. */
kzsError kzsWGLMakeCurrent(HDC hdc, HGLRC hrc);
/** Deletes a WGL context. */
kzsError kzsWGLDeleteContext(HGLRC glContext);

/** Updates theWGL surface on the screen. */
kzsError kzsWGLUpdateSurface(HDC hdc);

/** Sets the swap interval. */
kzsError kzsWGLSwapInterval(kzInt interval);

/** Returns actual surface properties. */
kzsError kzsWGLGetUsedSurfaceProperties(HDC hdc, struct KzsSurfaceProperties* out_surfaceProperties);

/** Checks whether given WGL extension is supported. */
kzBool kzsWGLExtensionSupported(kzString extensionString);
/** Returns list of supported WGL extensions. */
kzString kzsWGLGetExtensions();


KZ_HEADER_END


#endif
