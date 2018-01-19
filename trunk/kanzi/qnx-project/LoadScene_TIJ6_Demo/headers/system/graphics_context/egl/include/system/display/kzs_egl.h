/**
* \file
* EGL functions.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZS_EGL_H
#define KZS_EGL_H


#include <system/wrappers/kzs_opengl_base.h>
#include <system/debug/kzs_error.h>
#include <system/kzs_types.h>
#include <system/input/kzs_input.h>
#include <system/display/kzs_window.h>
#include <system/wrappers/kzs_opengl_base.h>
#include <system/kzs_header.h>

#include <EGL/egl.h>


KZ_HEADER_BEGIN


#define KZS_EGL_VENDOR      EGL_VENDOR
#define KZS_EGL_VERSION     EGL_VERSION
#define KZS_EGL_EXTENSIONS  EGL_EXTENSIONS
#define KZS_EGL_CLIENT_APIS EGL_CLIENT_APIS

typedef void* kzsEGLImage;

/* Config Attributes */
#define KZS_EGL_CONFIG_ID              EGL_CONFIG_ID

/* Surface Attributes */
#define KZS_EGL_HEIGHT                 EGL_HEIGHT
#define KZS_EGL_WIDTH                  EGL_WIDTH
#define KZS_EGL_LARGEST_PBUFFER        EGL_LARGEST_PBUFFER
#define KZS_EGL_TEXTURE_FORMAT         EGL_TEXTURE_FORMAT
#define KZS_EGL_TEXTURE_TARGET         EGL_TEXTURE_TARGET
#define KZS_EGL_MIPMAP_TEXTURE         EGL_MIPMAP_TEXTURE
#define KZS_EGL_MIPMAP_LEVEL           EGL_MIPMAP_LEVEL
#ifdef EGL_VERSION_1_2
#define KZS_EGL_RENDER_BUFFER          EGL_RENDER_BUFFER
#define KZS_EGL_HORIZONTAL_RESOLUTION  EGL_HORIZONTAL_RESOLUTION
#define KZS_EGL_VERTICAL_RESOLUTION    EGL_VERTICAL_RESOLUTION
#define KZS_EGL_PIXEL_ASPECT_RATIO     EGL_PIXEL_ASPECT_RATIO
#define KZS_EGL_SWAP_BEHAVIOR          EGL_SWAP_BEHAVIOR
#endif
#ifdef EGL_VERSION_1_4	
#define KZS_EGL_MULTISAMPLE_RESOLVE    EGL_MULTISAMPLE_RESOLVE
#endif

/* Context Attributes */
#ifdef EGL_VERSION_1_2
#define KZS_EGL_CONTEXT_CLIENT_TYPE    EGL_CONTEXT_CLIENT_TYPE
#endif
#ifdef EGL_VERSION_1_3
#define KZS_EGL_CONTEXT_CLIENT_VERSION EGL_CONTEXT_CLIENT_VERSION
#endif


/* EGL wrapper functions. */
kzsError kzsEGLGetDisplay(EGLNativeDisplayType displayID, EGLDisplay* out_eglDisplay);
kzsError kzsEGLInitialize(EGLDisplay eglDisplay, kzInt* major, kzInt* minor);
kzsError kzsEGLTerminate(EGLDisplay eglDisplay);
kzsError kzsEGLGetConfigs(EGLDisplay eglDisplay, EGLConfig* configs, kzInt configSize, kzInt* out_configCount);
kzsError kzsEGLChooseConfig(EGLDisplay eglDisplay, const kzInt* attributeList, EGLConfig* configs, kzInt configSize, kzInt* out_configCount);
kzsException kzsEGLGetConfigAttrib(EGLDisplay eglDisplay, EGLConfig config, kzInt attribute, kzInt* out_value);
kzsError kzsEGLCreateWindowSurface(EGLDisplay eglDisplay, EGLConfig config, EGLNativeWindowType window, const EGLint* attributeList, EGLSurface* out_surface);
kzsError kzsEGLMakeCurrent(EGLDisplay eglDisplay, EGLSurface eglSurfaceRead, EGLSurface eglSurfaceWrite, EGLContext eglContext);
EGLContext kzsEGLGetCurrentContext(void);
EGLDisplay kzsEGLGetCurrentDisplay(void);
kzsError kzsEGLCopyBuffers(EGLDisplay eglDisplay, EGLSurface eglSurface, void* target);
kzsError kzsEGLSwapInterval(EGLDisplay eglDisplay, EGLint interval);
kzsError kzsEGLSwapBuffers(EGLDisplay eglDisplay, EGLSurface eglSurface);
kzString kzsEGLQueryString(EGLDisplay eglDisplay, kzInt name);
EGLenum kzsEGLQueryAPI(void);
kzsError kzsEGLBindAPI(EGLenum api);
kzsError kzsEGLCreateContext(EGLDisplay eglDisplay, EGLConfig config, EGLContext shareContext, const EGLint* attributeList, EGLContext* out_context);
kzsError kzsEGLSurfaceAttrib(EGLDisplay eglDisplay, EGLSurface surface, EGLint attribute, EGLint value);
kzsError kzsEGLQuerySurface(EGLDisplay eglDisplay, EGLSurface surface, EGLint attribute, EGLint* out_value);
kzsError kzsEGLQueryContext(EGLDisplay eglDisplay, EGLContext context, EGLint attribute, EGLint* out_value);
kzsError kzsEGLDestroySurface(EGLDisplay eglDisplay, EGLSurface surface);
kzsError kzsEGLDestroyContext(EGLDisplay eglDisplay, EGLContext context);
kzsError kzsEGLCreateImage(EGLDisplay display, EGLContext context, EGLenum target, void* data, EGLint* attr, kzsEGLImage* out_eglImage);
kzsError kzsEGLDeleteImage(EGLDisplay display, kzsEGLImage eglImage);


KZ_HEADER_END


#endif
