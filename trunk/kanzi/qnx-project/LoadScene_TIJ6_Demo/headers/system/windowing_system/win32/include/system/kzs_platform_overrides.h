/**
 * \file
 * Platform overrides for win32 platform
 * 
 * Copyright 2008-2014 by Rightware. All rights reserved.
 */
#ifndef KZS_PLATFORM_OVERRIDES_H
#define KZS_PLATFORM_OVERRIDES_H


#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/** Overrides kzsLogCreateDefaultLoggers from system/debug/kzs_log.c */
#define KZS_OVERRIDE_LOG_CREATE_DEFAULT_LOGGERS

/** Overrides kzsAssert_private from system/debug/kzs_error.c */
#define KZS_OVERRIDE_ASSERT_PRIVATE
/** Overrides kzsErrorBreak_private from system/debug/kzs_error.c */
#define KZS_OVERRIDE_ERROR_BREAK_PRIVATE
/** Overrides kzsDebugBreak_private from system/debug/kzs_error.c */
#define KZS_OVERRIDE_DEBUG_BREAK_PRIVATE


KZ_HEADER_END


#endif
