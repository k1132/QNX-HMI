/**
 * \file
 * Core logging. Higher level helper utilities for logging.
 * 
 * Copyright 2008-2014 by Rightware. All rights reserved.
 */
#ifndef KZC_LOG_H
#define KZC_LOG_H


#include <system/debug/kzs_log.h>
#include <system/debug/kzs_error.h>
#include <system/wrappers/kzs_arg.h>
#include <system/kzs_types.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations. */
struct KzcMemoryManager;
struct KzcOutputStream;


/**
 * Logs a formatted message with arbitrary number of parameters.
 * Arguments parameter provides the formatting arguments as variable arguments list.
 * The formatting is the same as in kzcStringFormat.
 */
kzsError kzcLogList(const struct KzcMemoryManager* memoryManager, KzsLogLevel level, kzString format, KZ_CONST_ARGLIST kzArgList* arguments);

/**
 * Logs a formatted message with arbitrary number of parameters.
 * Formatting arguments are given as variable arguments.
 * The formatting is the same as in kzcStringFormat.
 */
#ifdef __GNUC__
kzsError kzcLog(const struct KzcMemoryManager* memoryManager, KzsLogLevel level, kzString format, ...) __attribute__((format(printf, 3, 4)));
#else
kzsError kzcLog(const struct KzcMemoryManager* memoryManager, KzsLogLevel level, kzString format, ...);
#endif

/**
 * Logs a formatted message with arbitrary number of parameters with KZS_LOG_LEVEL_DEBUG.
 * Formatting arguments are given as variable arguments.
 * The formatting is the same as in kzcStringFormat.
 * Warning: This function always uses a thread unsafe global system memory manager and discards all errors silently.
 */
void kzcLogDebug(kzString format, ...);


KZ_HEADER_END


#endif
