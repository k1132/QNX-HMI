/**
 * \file
 * Exact Kanzi types - 8 bit, 16 bit, 32 bit, 64 bit
 * 
 * Copyright 2008-2014 by Rightware. All rights reserved.
 */
#ifndef KZS_STDINT_H
#define KZS_STDINT_H


#include <system/kzs_header.h>
#if __STDC_VERSION__ >= 199901L /*lint --e{553}*/ || defined ANDROID
#include <stdint.h>
#endif


KZ_HEADER_BEGIN


/*
Getting the exact sizes of integer types right is a nontrivial task.
Here we try to solve the sizes by testing macros in the following order:
1. Language-specific macros
2. Compiler-specific macros
3. CPU architecture-specific macros
4. Platform-specific macros
If these tests fail we fall back to guessing the sizes.
*/

#if __STDC_VERSION__ >= 199901L /*lint --e{553}*/ /* C99 Language */

/** Unsigned 8-bit type. */
typedef uint8_t kzU8;
/** Signed 8-bit type. */
typedef int8_t kzS8;

/** Unsigned 16-bit type. */
typedef uint16_t kzU16;
/** Signed 16-bit type. */
typedef int16_t kzS16;

/** Unsigned 32-bit type. */
typedef uint32_t kzU32;
/** Signed 32-bit type. */
typedef int32_t kzS32;

/** Unsigned 64-bit type. */
typedef uint64_t kzU64;
/** Signed 64-bit type. */
typedef int64_t kzS64;

#elif defined _MSC_VER /* Microsoft Visual C++ Compiler */

/** Unsigned 8-bit type. */
typedef unsigned __int8 kzU8;
/** Signed 8-bit type. */
typedef __int8 kzS8;

/** Unsigned 16-bit type. */
typedef unsigned __int16 kzU16;
/** Signed 16-bit type. */
typedef __int16 kzS16;

/** Unsigned 32-bit type. */
typedef unsigned __int32 kzU32;
/** Signed 32-bit type. */
typedef __int32 kzS32;

/** Unsigned 64-bit type. */
typedef unsigned __int64 kzU64;
/** Signed 64-bit type. */
typedef __int64 kzS64;

#elif defined _LP64 || defined __LP64__ /* LP64 Architecture */

/** Unsigned 8-bit type. */
typedef unsigned char kzU8;
/** Signed 8-bit type. */
typedef signed char kzS8;

/** Unsigned 16-bit type. */
typedef unsigned short kzU16;
/** Signed 16-bit type. */
typedef signed short kzS16;

/** Unsigned 32-bit type. */
typedef unsigned int kzU32;
/** Signed 32-bit type. */
typedef signed int kzS32;

/** Unsigned 64-bit type. */
typedef unsigned long kzU64;
/** Signed 64-bit type. */
typedef signed long kzS64;

#elif defined ANDROID /* Android Platform */

/** Unsigned 8-bit type. */
typedef uint8_t kzU8;
/** Signed 8-bit type. */
typedef int8_t kzS8;

/** Unsigned 16-bit type. */
typedef uint16_t kzU16;
/** Signed 16-bit type. */
typedef int16_t kzS16;

/** Unsigned 32-bit type. */
typedef uint32_t kzU32;
/** Signed 32-bit type. */
typedef int32_t kzS32;

/** Unsigned 64-bit type. */
typedef uint64_t kzU64;
/** Signed 64-bit type. */
typedef int64_t kzS64;

#else /* Guess */

/** Unsigned 8-bit type. */
typedef unsigned char kzU8;
/** Signed 8-bit type. */
typedef signed char kzS8;

/** Unsigned 16-bit type. */
typedef unsigned short kzU16;
/** Signed 16-bit type. */
typedef signed short kzS16;

/** Unsigned 32-bit type. */
typedef unsigned long kzU32;
/** Signed 32-bit type. */
typedef signed long kzS32;

/** Unsigned 64-bit type. */
typedef unsigned long long kzU64;
/** Signed 64-bit type. */
typedef signed long long kzS64;

#endif


KZ_HEADER_END


#endif
