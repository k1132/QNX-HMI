/**
* \file
* OpenGL base header.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZS_OPENGL_BASE_H
#define KZS_OPENGL_BASE_H


#include <system/debug/kzs_error.h>
#include <system/kzs_types.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


#define KZ_OPENGL_NONE      0 /**< No OpenGL version specified. */
#define KZ_OPENGL_ES_2_0    2 /**< OpenGL ES 2.0 version. */
#define KZ_OPENGL_2_1       3 /**< Desktop OpenGL 2.1 version. */
#define KZ_OPENGL_LATEST    6 /**< Desktop OpenGL latest. */
#define KZ_OPENGL_ES_3_0    7 /**< OpenGL ES 3.0 version. */
#define KZ_OPENGL_4_3       8 /**< Desktop OpenGL 4.3 version. */

#define KZ_PLATFORM_UNSPECIFIED 0 /**< No platform specified. */
#define KZ_PLATFORM_IMG         1 /**< IMG platform. */
#define KZ_PLATFORM_AMD         2 /**< AMD platform. */
#define KZ_PLATFORM_TEGRA       3 /**< Tegra platform. */
#define KZ_PLATFORM_DESKTOP     4 /**< Desktop platform. */

#define KZ_OPENGL_VERSION KZ_OPENGL_ES_2_0

#ifndef KZ_OPENGL_VERSION
#error KZ_OPENGL_VERSION undefined
#endif

#ifndef KZ_OPENGL_PLATFORM
#define KZ_OPENGL_PLATFORM KZ_PLATFORM_UNSPECIFIED
#endif


/** OpenGL binary shader format identifier. */
extern const kzUint KZS_OPENGL_BINARY_FORMAT;
/** OpenGL binary shader format name. */
extern const kzString KZS_OPENGL_BINARY_NAME;
/** Use OES_get_program_binary extension when loading combined binary shaders. */
extern const kzBool KZS_OPENGL_USE_PROGRAM_BINARY_EXTENSION;

/** Global variable for controlling if OpenGL calls are enabled. */
extern kzBool g_kzsEnableOpenGLCalls;


/** Macro to use for starting OpenGL calls to allow disabling them with a control flag. */
#define KZS_OPENGL_CALL_BEGIN \
    if(g_kzsEnableOpenGLCalls) { /*lint --e{904}*/

/** Macro to use for enging OpenGL calls to allow disabling them with a control flag. */
#define KZS_OPENGL_CALL_END \
    }

/** Macro to use for enging OpenGL calls with a return value to allow disabling them with a control flag. */
#define KZS_OPENGL_CALL_END_RETURN_VALUE(x) \
    } return x;


/** Sets OpenGL calls enabled / disabled. */
void kzsOpenGLCallsSetEnabled(kzBool enabled);
/** Checks if opengl calls are enabled. */
kzBool kzsOpenGLCallsIsEnabled(void);
/**
 * Initializes OpenGL, associates extensions needed for OpenGL profile.
 * This function should be called once, after the first GL context has been created.
 */
kzsError kzsOpenGLInitialize(void);


KZ_HEADER_END


#endif
