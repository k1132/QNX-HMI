/**
 * \file
 * Kanzi types - integers, floats, doubles, strings, inlines
 * 
 * Copyright 2008-2014 by Rightware. All rights reserved.
 */
#ifndef KZS_TYPES_H
#define KZS_TYPES_H


#include <system/kzs_header.h>
#include <system/kzs_stdint.h>


KZ_HEADER_BEGIN


/** Boolean type. */
typedef int kzBool;

#define KZ_FALSE (kzBool)0 /**< False boolean value. */
#define KZ_TRUE (kzBool)1 /**< True boolean value. */

/** Char type. */
typedef char kzChar;
/** Unsigned char type. */
typedef unsigned int kzUnicodeChar;
/** Constant string type. */
typedef kzChar const* kzString;
/** Non-const string type. */
typedef kzChar* kzMutableString;

/** Signed integer type. */
typedef int kzInt;
/** Unsigned integer type. */
typedef unsigned int kzUint;

/** Float type. */
typedef float kzFloat;
/** Double precision float type. */
typedef double kzDouble;

/** Byte type. */
typedef unsigned char kzByte;

/** Pointer to anything type. */
typedef void* kzPointer;


/** Null pointer value. */
#define KZ_NULL 0 /*lint --e(910,634)*/


/** Inline function definition. */
#ifndef KZ_INLINE
#ifdef _MSC_VER
#define KZ_INLINE __inline static /**< Inline function definition. For MSVC. */
#elif __STDC_VERSION__ >= 199901L
#define KZ_INLINE inline static /**< Inline function definition. For C99 and up. */
#elif defined __GNUC__
#define KZ_INLINE __inline__ static /**< Inline function definition. For GCC. */
#else
#define KZ_INLINE static /**< Inline function definition. For C89. */
#endif
#endif


/** Macro for flagging unused function parameters. */
#define KZ_UNUSED_PARAMETER(param) (void)param

/** Macro for flagging unused return value. */
#define KZ_UNUSED_RETURN_VALUE(param) (void)param

/** Macro for flagging a function as a call-back function. */
#define KZ_CALLBACK /*lint -e{715, 818} Suppress warnings of unused parameters and parameter could be const pointer. */

/** \see KZ_MULTILINE_MACRO */
KZ_INLINE kzBool kzMultiLineMacroTest_private(void) { return KZ_FALSE; }
/** Beginning of a multiline macro. */
#define KZ_MULTILINE_MACRO do {
/** End of a multiline macro. */
#define KZ_MULTILINE_MACRO_END } while (kzMultiLineMacroTest_private())

/** Macro to use in empty source file to allow compilation. */
#define KZ_EMPTY_SOURCE_FILE static void* const unusedVariable = KZ_NULL /*lint --e{528}*/


KZ_HEADER_END


#endif
