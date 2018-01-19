/**
 * \file
 * Endianness check for Kanzi.
 *
 * Must be extended with new platforms as need be.
 * 
 * Copyright 2008-2014 by Rightware. All rights reserved.
 */
#ifndef KZS_ENDIAN_H
#define KZS_ENDIAN_H


#include <system/kzs_types.h>
#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/*
Determining the endianness is rather nontrivial.

This file will determine both endianness macros and then an endianness check
that must be run compile-time in debug mode to see that we were successful.
*/

#if defined(_MSC_VER) || defined(WIN32)

/** With MSVC, always little-endian. */
#define KZS_ENDIANNESS_LITTLE_ENDIAN

#elif defined(__linux__) || defined(ANDROID)

#include <endian.h>

#if __BYTE_ORDER == __LITTLE_ENDIAN
/** Little endian detected on Linux platform. */
#define KZS_ENDIANNESS_LITTLE_ENDIAN
#elif __BYTE_ORDER == __BIG_ENDIAN
/** Big endian detected on Linux platform. */
#define KZS_ENDIANNESS_BIG_ENDIAN
#else
#error "could not determine endianness on Linux platform"
#endif

#elif defined(__INTEGRITY) || defined(INTEGRITY)

#if defined(__LittleEndian) || defined(LittleEndian)
/** Little endian detected on Integrity platform. */
#define KZS_ENDIANNESS_LITTLE_ENDIAN
#elif defined(__BigEndian) || defined(BigEndian)
/** Big endian detected on Integrity platform. */
#define KZS_ENDIANNESS_BIG_ENDIAN
#else
#error "could not determine endianness on Integrity platform"
#endif

#elif defined(__clang__) || defined(__GNUC__)

#if defined(__LITTLEENDIAN__)
/** Little endian detected from Clang/GCC definition. */
#define KZS_ENDIANNESS_LITTLE_ENDIAN
#elif defined(__BIGENDIAN__)
/** Big endian detected from Clang/GCC definition. */
#define KZS_ENDIANNESS_BIG_ENDIAN
#else
#error "could not determine endianness from Clang/GCC compiler definitions"
#endif

#else /* Guess? */

#if defined(__LITTLEENDIAN__)
/** Little endian detected on generic POSIX platform. */
#define KZS_ENDIANNESS_LITTLE_ENDIAN
#elif defined(__BIGENDIAN__)
/** Big endian detected on generic POSIX platform. */
#define KZS_ENDIANNESS_BIG_ENDIAN
#else
#error "could not determine endianness on generic POSIX platform"
#endif

#endif


/**
* Check that endianness is detected correctly.
*
* Should only be used in assertions in debug build.
*
* \return True if compile-time endianness check resulted in correct endianness.
*/
kzBool kzsEndiannessDetectedCorrectly(void);


/**
* Tell if we're on a big-endian system.
* \return True if in big-endian, false if in little-endian.
*/
KZ_INLINE kzBool kzsIsBigEndian(void)
{
    kzsAssert(kzsEndiannessDetectedCorrectly());

#if defined(KZS_ENDIANNESS_BIG_ENDIAN)
    return KZ_TRUE;
#else
    return KZ_FALSE;
#endif
}


KZ_HEADER_END


#endif
