/**
 * \file
 * Error handling functions.
 * 
 * Copyright 2008-2014 by Rightware. All rights reserved.
 */
#ifndef KZS_ERROR_H
#define KZS_ERROR_H


#include <system/kzs_types.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/** Error code type definition. */
typedef int kzsError;
/** Exception code type definition, extends error. */
typedef int kzsException;


#define KZS_EXCEPTION_MESSAGE_MAXIMUM_LENGTH 256 /**< Maximum length of exception. */


/*
      0 -  9999: Generic error codes
  10000 - 19999: System layer error codes
  20000 - 29999: Core layer error codes
  30000 - 39999: User layer error codes
  40000 - 49999: Framework error codes
 100000 -      : Application error codes
*/

/** Success code. */
#define KZS_SUCCESS (kzsError)0 /**< No error. */

/* Generic error codes. (1 - ) */
#define KZS_ERROR_ASSERTION_FAILED (kzsError)1 /**< Assertion failed. */
#define KZS_ERROR_NOT_IMPLEMENTED_YET (kzsError)2 /**< Functionality is not yet implemented. */
#define KZS_ERROR_ENUM_OUT_OF_RANGE (kzsError)3 /**< Invalid value for enum. */
#define KZS_ERROR_ILLEGAL_OPERATION (kzsError)4 /**< Trying to perform illegal operation. */
#define KZS_ERROR_ILLEGAL_ARGUMENT (kzsError)5 /**< An argument was invalid for the given context. */
#define KZS_ERROR_MALFORMED_DATA (kzsError)6 /**< Data is malformed. */
#define KZS_ERROR_ARRAY_OUT_OF_BOUNDS (kzsError)7 /**< Trying to access array with invalid index. */
#define KZS_ERROR_INVALID_STATE (kzsError)8 /**< Program is in invalid state. */

/** Return from the function without any error code. */
#define kzsSuccess() return KZS_SUCCESS


#ifdef _DEBUG

/** Asserts the given test parameter. If test evaluates to true, nothing happens. Only effective in debug build. */
#define kzsAssertText(test, text) KZ_MULTILINE_MACRO                        \
    kzBool assertResult = (test);                                           \
    if (!(assertResult))                                                    \
    {                                                                       \
        kzsErrorLog(KZS_ERROR_ASSERTION_FAILED, "Assertion failed: " text); \
        kzsAssert_private();                                                \
    }                                                                       \
KZ_MULTILINE_MACRO_END

/** Asserts the given test parameter. If test evaluates to true, nothing happens. Only effective in debug build. */
#define kzsAssert(test) KZ_MULTILINE_MACRO                                      \
    kzBool assertResult = (test);                                               \
    if (!(assertResult))                                                        \
    {                                                                           \
        kzsErrorLog(KZS_ERROR_ASSERTION_FAILED, "Assertion failed: " # test);   \
        kzsAssert_private();                                                    \
    }                                                                           \
KZ_MULTILINE_MACRO_END

/** Terminates the application and traps the debugger if possible. Only effective in debug build. */
#define kzsErrorBreak() kzsErrorBreak_private()

/** Traps the debugger if possible. Only effective in debug build. */
#define kzsDebugBreak() kzsDebugBreak_private()

#else

/* The following construct in asserts tells compiler to treat test parameter as used (to not warn about unused symbols) without actually evaluating it. */
/** Asserts the given test parameter. If test evaluates to true, nothing happens. Only effective in debug build. */
#define kzsAssertText(test, text) while ((void)0, 0) (void)(test)

/** Asserts the given test parameter. If test evaluates to true, nothing happens. Only effective in debug build. */
#define kzsAssert(test) while ((void)0, 0) (void)(test)

/** Terminates the application and traps the debugger if possible. Only effective in debug build. */
#define kzsErrorBreak() (void)0

/** Traps the debugger if possible. Only effective in debug build. */
#define kzsDebugBreak() (void)0

#endif

/** kzsErrorThrow macro wrapper to share code. */
void kzsErrorThrowFunctionWithMessage_private(kzsError error, kzString message);

/** Return from the function with the given error code. */
#define kzsErrorThrow(new_error, logMessage) KZ_MULTILINE_MACRO \
    kzsErrorThrowFunctionWithMessage_private(new_error, logMessage); \
    /*lint -e{904}*/                                            \
    return new_error;                                           \
KZ_MULTILINE_MACRO_END

/**
 * \see kzsErrorThrow
 * formatArgs is the collection of format string and format arguments in parentheses, 
 * i.e. kzsErrorThrowFormat(KZS_ERROR_ARRAY_OUT_OF_BOUNDS, ("Shadow map array out of bounds for texture %s", textureName));
 */
#define kzsErrorThrowFormat(new_error, formatArgs) KZ_MULTILINE_MACRO                    \
    kzsErrorFormatMessage_private formatArgs;                                            \
    kzsErrorThrowFunctionWithMessage_private(new_error, kzsErrorGetLastFormattedErrorMessage_private()); \
    /*lint -e{904}*/                                                                     \
    return new_error;                                                                    \
KZ_MULTILINE_MACRO_END

/** Return from the function with the given exception code. */
#define kzsExceptionThrow(new_exception, logMessage) KZ_MULTILINE_MACRO              \
    kzsAssertText((new_exception) < 0, "Tried to throw error code as an exception"); \
    kzsExceptionLog_private(logMessage);                                             \
    kzsExceptionOccurred_private(new_exception, logMessage);                         \
    /*lint -e{904}*/                                                                 \
    return new_exception;                                                            \
KZ_MULTILINE_MACRO_END

/** 
 * \see kzsExceptionThrow
 * formatArgs is the collection of format string and format arguments in parentheses,
 * i.e. kzsExceptionThrowFormat(KZU_EXCEPTION_INCOMPLETE_BINARY_FILE, ("Binary file %s is truncated and does not contain requested data", binaryFileName));
 */
#define kzsExceptionThrowFormat(new_exception, formatArgs) KZ_MULTILINE_MACRO        \
    kzsAssertText((new_exception) < 0, "Tried to throw error code as an exception"); \
    kzsExceptionLogFormat_private formatArgs;                                        \
    kzsExceptionOccurred_private(new_exception, kzsErrorGetLastExceptionMessage());  \
    /*lint -e{904}*/                                                                 \
    return new_exception;                                                            \
KZ_MULTILINE_MACRO_END

/** Return from the function with the given exception code. */
#define kzsExceptionRethrow(param_exception) KZ_MULTILINE_MACRO                            \
    kzsAssertText((param_exception) < 0, "Tried to rethrow error code as an exception");   \
    /*lint -e{904}*/                                                                 \
    return exception;                                                            \
KZ_MULTILINE_MACRO_END

/** Return from the function with the given error code, if the test is false. Otherwise continue. */
#define kzsErrorTest(test, new_error, logMessage) KZ_MULTILINE_MACRO    \
    if (!(test))                                                        \
    {                                                                   \
        kzsErrorThrowFunctionWithMessage_private(new_error, logMessage);\
        /*lint -e{904}*/                                                \
        return new_error;                                               \
    }                                                                   \
KZ_MULTILINE_MACRO_END

/** 
 * \see kzsErrorTest
 * formatArgs is the collection of format string and format arguments in parentheses,
 * i.e. kzsErrorTestFormat(indexFound, KZC_ERROR_ELEMENT_NOT_FOUND, ("Child to be removed %s not found in parent clip %s", childClipName, parentClipName));
 */
#define kzsErrorTestFormat(test, new_error, formatArgs) KZ_MULTILINE_MACRO \
    if (!(test))                                                           \
    {                                                                      \
        kzsErrorThrowFormat(new_error, formatArgs);                        \
    }                                                                      \
KZ_MULTILINE_MACRO_END

/** Return from the function with the given exception code, if the test is false. Otherwise continue. */
#define kzsExceptionTest(test, new_exception, logMessage) KZ_MULTILINE_MACRO    \
    if (!(test))                                                                \
    {                                                                           \
        /*lint -e{904}*/                                                        \
        kzsExceptionThrow((new_exception), logMessage);                         \
    }                                                                           \
KZ_MULTILINE_MACRO_END

/** 
 * \see kzsExceptionTest
 * formatArgs is the collection of format string and format arguments in parentheses,
 * i.e. kzsExceptionTestFormat(file != KZ_NULL, KZS_EXCEPTION_FILE_OPEN_FAILED, ("Failed to open resource file %s", resourceFileName));
 */
#define kzsExceptionTestFormat(test, new_exception, formatArgs) KZ_MULTILINE_MACRO \
    if (!(test))                                                                   \
    {                                                                              \
        /*lint -e{904}*/                                                           \
        kzsExceptionThrowFormat((new_exception), formatArgs);                      \
    }                                                                              \
KZ_MULTILINE_MACRO_END

/** Wrapper for kzsErrorThrow() to share more code. */
void kzsErrorThrowFunction_private(kzsError error);

/**
* Return from the function with the given error code, if it is one.
* If the error code is an exception, the code may or may not return (use ::kzsExceptionForward instead).
*/
#define kzsErrorForward(error) KZ_MULTILINE_MACRO                              \
    if ((error) != KZS_SUCCESS)                                                \
    {                                                                          \
        if ((error) < KZS_SUCCESS)                                             \
        {                                                                      \
            kzsErrorThrowFunction_private(error);                              \
        }                                                                      \
        return error;                                                          \
    }                                                                          \
KZ_MULTILINE_MACRO_END

/** Return from the function with the given exception or error code, if it is one. Otherwise continue. */
#define kzsExceptionForward(exception) KZ_MULTILINE_MACRO   \
    if ((exception) != KZS_SUCCESS)                         \
    {                                                       \
        /*lint -e{904}*/                                    \
        return exception;                                   \
    }                                                       \
KZ_MULTILINE_MACRO_END

/**
 * If the given exception code is an error, pass it forward. If it is an exception, substitute it with the given error.
 * Otherwise continue.
 */
#define kzsExceptionForwardAsError(exception, new_error, logMessage) KZ_MULTILINE_MACRO \
    if ((exception) < KZS_SUCCESS)                                                      \
    {                                                                                   \
        kzsErrorThrow(new_error, logMessage);                                           \
    }                                                                                   \
    else if ((exception) > KZS_SUCCESS)                                                 \
    {                                                                                   \
        /*lint -e{904}*/                                                                \
        return (kzsError)(exception);                                                   \
    }                                                                                   \
KZ_MULTILINE_MACRO_END

/** 
 * \see kzsExceptionForwardAsError
 * formatArgs is the collection of format string and format arguments in parentheses, 
 * i.e. kzsExceptionForwardAsErrorFormat(result, KZC_ERROR_SHADER_RESTORE_TO_GPU_FAILED, ("Failed to restore shader %s on GPU", shaderName));
 */
#define kzsExceptionForwardAsErrorFormat(test, new_error, formatArgs) KZ_MULTILINE_MACRO \
    if ((exception) < KZS_SUCCESS)                                                       \
    {                                                                                    \
        kzsErrorThrowFormat(new_error, formatArgs);                                      \
    }                                                                                    \
    else if ((exception) > KZS_SUCCESS)                                                  \
    {                                                                                    \
        /*lint -e{904}*/                                                                 \
        return (kzsError)(exception);                                                    \
    }                                                                                    \
KZ_MULTILINE_MACRO_END

/**
 * Return from the function with the given new error code,
 * if the given old code is also an error. Otherwise continue.
 */
#define kzsErrorSubstitute(error, new_error, logMessage) KZ_MULTILINE_MACRO \
    if ((error) != KZS_SUCCESS)                                             \
    {                                                                       \
        kzsErrorLog(new_error, logMessage);                                 \
        /*lint -e{904}*/                                                    \
        return new_error;                                                   \
    }                                                                       \
KZ_MULTILINE_MACRO_END

/**
 * Return from the function with the given new exception code,
 * if the given old code is also an exception. Otherwise continue.
 */
#define kzsExceptionSubstitute(error, new_exception, logMessage) KZ_MULTILINE_MACRO \
    if ((error) != KZS_SUCCESS)                                                     \
    {                                                                               \
        /*lint -e{904}*/                                                            \
        return new_exception;                                                       \
    }                                                                               \
KZ_MULTILINE_MACRO_END

/** Test if the given error is an error. */
#define kzsErrorIf(error) if ((error) != KZS_SUCCESS)

/** Test if the given exception matches the specified exception code. */
#define kzsExceptionCatch(exception, exception_code) if ((exception) == (exception_code))

/** Test if the given exception is an actual exception and not success or error. */
#define kzsExceptionCatchAll(exception) if ((exception) < 0)

/** Macro to use to indicate that some code is not yet implemented. */
#define KZS_NOT_IMPLEMENTED_YET kzsErrorLog(KZS_ERROR_NOT_IMPLEMENTED_YET, "Not implemented yet.") /*lint --e{715,818}*/
/** Macro to use to indicate and throw error that some code is not yet implemented. */
#define KZS_NOT_IMPLEMENTED_YET_ERROR kzsErrorThrow(KZS_ERROR_NOT_IMPLEMENTED_YET, "Not implemented yet.") /*lint --e{715,818}*/
/** Macro to use to indicate and throw error with an explanation, that some code is not yet implemented. */
#define KZS_NOT_IMPLEMENTED_YET_ERROR_TEXT(message) kzsErrorThrow(KZS_ERROR_NOT_IMPLEMENTED_YET, message) /*lint --e{715,818}*/


/** Logs the given error code with given message. */
#define kzsErrorLog(errorCode, message) kzsErrorLog_private(errorCode, message, __FILE__, __LINE__)

/** \see kzsErrorLog */
void kzsErrorLog_private(kzsError errorCode, kzString message, kzString file, kzUint line);
/** \see kzsAssert */
void kzsAssert_private(void);
/** \see kzsErrorBreak */
void kzsErrorBreak_private(void);
/** \see kzsDebugBreak */
void kzsDebugBreak_private(void);
/** Exception log. */
void kzsExceptionLog_private(kzString message);
/** Exception log format. */
void kzsExceptionLogFormat_private(kzString format, ...);
/** Error callback */
void kzsErrorOccurred_private(kzsError errorCode, kzString message);
/** Exception callback */
void kzsExceptionOccurred_private(kzsError errorCode, kzString message);

/** Initializes error handling for thread. */
kzsError kzsErrorInitializeThread(kzMutableString* storage);
/** De-initializes error handling for thread. */
kzsError kzsErrorDeinitializeThread(void);

/** Initialize a global variable for error message storage. */
kzsError kzsErrorInitialize(void);
/** De-initialize a global variable for error message storage. */
kzsError kzsErrorUninitialize(void);

/** Callback that is triggered in error situations. */
typedef void (*KzsErrorCallback)(kzsError errorCode, kzString message);
/** Sets error callback. */
void kzsErrorSetErrorCallback(KzsErrorCallback callback);

/** Callback that is triggered in exception situations. */
typedef void (*KzsExceptionCallback)(kzsError errorCode, kzString message);
/** Sets exception callback. */
void kzsErrorSetExceptionCallback(KzsExceptionCallback callback);

/** Gets last error message or empty string if there is no error. */
kzString kzsErrorGetLastErrorMessage(void);
/** Gets the last exception message for the thread. */
kzString kzsErrorGetLastExceptionMessage(void);

/** Formats error message. */
#ifdef __GNUC__
void kzsErrorFormatMessage_private(kzString format, ...) __attribute__((format(printf, 1, 2)));
#else
void kzsErrorFormatMessage_private(kzString format, ...);
#endif
/** Gets last formatted error message. */
kzString kzsErrorGetLastFormattedErrorMessage_private(void);


KZ_HEADER_END


#endif
