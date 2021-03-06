/**
 * \file
 * System layer error codes.
 * 
 * Copyright 2008-2014 by Rightware. All rights reserved.
 */
#ifndef KZS_ERROR_CODES_H
#define KZS_ERROR_CODES_H


#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* System layer error codes have reserved range of 10000 - 19999 */

/* System error codes. (10000 - 10099) */
#define KZS_ERROR_INITIALIZATION_FAILED (kzsError)10001 /**< System initialization failed. */
#define KZS_ERROR_UNINITIALIZATION_FAILED (kzsError)10002 /**< System uninitialization failed. */

/* Memory error codes. (10100 - 10199) */
#define KZS_ERROR_OUT_OF_MEMORY (kzsError)10101 /**< Out of memory. */
#define KZS_EXCEPTION_MEMORY_LEAK (kzsException)(-10102) /**< Memory leak detected when exiting the application. */

/* Debug / log error codes. (10200 - 10299) */
#define KZS_ERROR_TOO_MANY_LOGGERS (kzsError)10201 /**< Number of loggers exceeds the supported maximum. */

/* Window / surface error codes. (10300 - 10399) */
#define KZS_ERROR_DISPLAY_INITIALIZATION_FAILED (kzsError)10301 /**< Failed to initialize display. */
#define KZS_ERROR_WINDOW_CREATION_FAILED (kzsError)10302 /**< Failed to create window. */
#define KZS_EXCEPTION_WINDOW_CREATION_FAILED (kzsError)(-10302) /**< Failed to create window. */
#define KZS_ERROR_WINDOW_MODIFICATION_FAILED (kzsError)10303 /**< Failed to create window. */
#define KZS_ERROR_SURFACE_INITIALIZATION_FAILED (kzsError)10304 /**< Failed to initialize surface. */
#define KZS_ERROR_SURFACE_UPDATE_FAILED (kzsError)10305 /**< Failed to update surface. */
#define KZS_ERROR_SURFACE_ACTIVATION_FAILED (kzsError)10306 /**< Failed to activate surface. */
#define KZS_ERROR_SURFACE_PARAMETER_QUERY_FAILED (kzsError)10307 /**< Failed to get surface parameters. */
#define KZS_EXCEPTION_SURFACE_PARAMETER_QUERY_FAILED (kzsException)(-10307) /**< Failed to get surface parameters. */
#define KZS_ERROR_DISPLAY_OPENGL2_NOT_SUPPORTED (kzsError)10308 /**< OpenGL 2.0 or better not supported. */
#define KZS_ERROR_DISPLAY_OPENGL_VERSION_NOT_DETECTED (kzsError)10309 /**< Failed to read OpenGL version information. */
#define KZS_ERROR_SURFACE_COPY_FAILED (kzsError)10310 /**< Failed to copy surface to pixmap. */
#define KZS_ERROR_IMAGE_DELETE_FAILED (kzsError)10311 /**< Deleting an image failed. */
#define KZS_ERROR_CONTEXT_UPDATE_FAILED (kzsError)10312 /**< Failed to update context. */
#define KZS_ERROR_CONTEXT_PARAMETER_QUERY_FAILED (kzsError)10313 /**< Failed to get context parameters. */

/* File error codes (10400 - 10499) */
#define KZS_EXCEPTION_FILE_OPEN_FAILED (kzsException)(-10401) /**< Failed to open file or directory. */
#define KZS_ERROR_FILE_OPERATION_FAILED (kzsError)10402 /**< File operation failed. */
#define KZS_ERROR_INVALID_NAME (kzsError)10403 /**< Invalid file or directory name. */
#define KZS_ERROR_NOT_FOUND (kzsError)10404 /**< File or directory not found (while opening). */

/* Threading error codes (10500 - 10599) */
#define KZS_ERROR_THREAD_NOT_FINISHED (kzsError)10501 /**< Thread is still running. */
#define KZS_ERROR_THREAD_OPERATION_FAILED (kzsError)10502 /**< Thread operation failed for some reason. */
#define KZS_EXCEPTION_UNDEFINED_THREAD_OPERATION (kzsException)(-10503) /**< Undefined thread operation was executed. */

/* Socket error codes (10600 - 10699) */
#define KZS_ERROR_SOCKET_OPERATION_FAILED (kzsError)10601 /**< Socket operation failed for some reason. */

/* Miscellaneous. */
#define KZS_EXCEPTION_ILLEGAL_ARGUMENT ((kzsException)-10701) /**< Function was passed an illegal argument. */
#define KZS_ERROR_STRING_INVALID_FORMAT (kzsError)10702  /**< Invalid format string. */



KZ_HEADER_END


#endif
