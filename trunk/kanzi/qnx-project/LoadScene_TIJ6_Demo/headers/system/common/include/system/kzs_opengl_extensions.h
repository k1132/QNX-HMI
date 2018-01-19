/**
* \file
* OpenGL extension wrapper
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/

#ifndef KZS_OPENGL_EXTENSIONS_H_
#define KZS_OPENGL_EXTENSIONS_H_


#include <system/debug/kzs_error.h>
#include <system/kzs_types.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Disable GCC warning. */
#ifdef __GNUC__
#define GCC_VERSION (__GNUC__ * 10000 + \
                     __GNUC_MINOR__ * 100 + \
                     __GNUC_PATCHLEVEL__)
#define GCC_SUPPORTS_DIAGNOSTIC_STACK (GCC_VERSION >= 40600)
#if GCC_SUPPORTS_DIAGNOSTIC_STACK
#pragma GCC diagnostic push
#endif
#pragma GCC diagnostic ignored "-Wstrict-prototypes"
#endif


/** Pointer to any GL function. */
typedef void (*kzsGLProcPointer)();


/* Re-enable GCC warning. */
#ifdef __GNUC__
#if GCC_SUPPORTS_DIAGNOSTIC_STACK
#pragma GCC diagnostic pop
#else
#pragma GCC diagnostic warning "-Wstrict-prototypes"
#endif
#endif


/** Gets the function pointer address for given string. */
kzsGLProcPointer kzsGLGetProcAddress(kzString functionName);
/** Initializes native window system. */
kzsError kzsNativeWindowSystemInitialize(void);


KZ_HEADER_END


#endif
