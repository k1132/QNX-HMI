/**
 * \file
 * Error (win32).
 * 
 * Copyright 2008-2014 by Rightware. All rights reserved.
 */
#ifndef KZS_ERROR_WIN32_H
#define KZS_ERROR_WIN32_H


#include <system/kzs_types.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/** This type controls whether debug break is called for errors and asserts. */
enum KzsErrorDebugBreakType
{
    KZS_ERROR_DEBUG_BREAK_TYPE_NEVER, /**< Never call debug break. */
    KZS_ERROR_DEBUG_BREAK_TYPE_ALWAYS, /**< Always call debug break for errors and asserts. */
    KZS_ERROR_DEBUG_BREAK_TYPE_IF_DEBUGGER_PRESENT /**< Call debug break only if debugger is present for errors and asserts. */
};

/** This type controls how asserts are handled */
enum KzsErrorAssertType
{
    KZS_ERROR_ASSERT_TYPE_EXIT, /**< Call exit(1) to terminate the program. */
    KZS_ERROR_ASSERT_TYPE_CRASH /**< Create an access violation to terminate the program. */
};


#ifdef _DEBUG

/** Asserts the given test parameter. If test evaluates to true, nothing happens. Only effective in debug build.
    Use only when the failing function reports errors using GetLastError(). Extends kzsAssert(). */
#define kzsWin32Assert(test) KZ_MULTILINE_MACRO                                 \
    kzBool assertResult = (test);                                               \
    if (!(assertResult))                                                        \
    {                                                                           \
        DWORD error = GetLastError();                                           \
        if (error != ERROR_SUCCESS)                                             \
        {                                                                       \
            kzsWin32ErrorNotify(error);                                         \
        }                                                                       \
        kzsErrorLog(KZS_ERROR_ASSERTION_FAILED, "Assertion failed: " # test);   \
        kzsAssert_private();                                                    \
    }                                                                           \
KZ_MULTILINE_MACRO_END

#else

/** Asserts the given test parameter. If test evaluates to true, nothing happens. Only effective in debug build.
    Use only when the failing function reports errors using GetLastError(). Extends kzsAssert(). */
#define kzsWin32Assert(test) (void)0

#endif

/** Return from the function with the given error code. Use only when the failing function reports errors using GetLastError().
    Extends kzsErrorThrow(). */
#define kzsWin32ErrorThrow(new_error, logMessage) KZ_MULTILINE_MACRO \
    DWORD error = GetLastError();                               \
    if (error != ERROR_SUCCESS)                                 \
    {                                                           \
        kzsWin32ErrorNotify(error);                             \
    }                                                           \
    kzsErrorLog(new_error, logMessage);                         \
    kzsErrorOccurred_private(new_error, logMessage);            \
    kzsErrorBreak();                                            \
    /*lint -e{904}*/                                            \
    return new_error;                                           \
KZ_MULTILINE_MACRO_END

/** Log system error message and return from the function with the given error code, if the test is false.
    Otherwise continue. Use only when the failing function reports errors using GetLastError(). Extends kzsErrorTest(). */
#define kzsWin32ErrorTest(test, new_error, logMessage) KZ_MULTILINE_MACRO \
    if (!(test))                                                          \
    {                                                                     \
        DWORD error = GetLastError();                                     \
        if (error != ERROR_SUCCESS)                                       \
        {                                                                 \
            kzsWin32ErrorNotify(error);                                   \
        }                                                                 \
        kzsErrorThrow(new_error, logMessage);                             \
    }                                                                     \
KZ_MULTILINE_MACRO_END

/** Sets error break type. */
void kzsErrorSetBreakType(enum KzsErrorDebugBreakType breakType);

/** Sets assert handling type. */
void kzsErrorSetAssertType(enum KzsErrorAssertType assertType);

/** Logs system error message corresponding to given error number. */
void kzsWin32ErrorNotify(kzU32 error);


KZ_HEADER_END


#endif
