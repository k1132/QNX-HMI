/**
 * \file
 * System header.
 * 
 * Copyright 2008-2014 by Rightware. All rights reserved.
 */
#ifndef KZS_SYSTEM_H
#define KZS_SYSTEM_H


/* System */
#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


/** Reporting mode for memory leaks. */
enum KzsSystemMemoryLeakReporting
{
    KZS_SYSTEM_MEMORY_LEAK_REPORTING_NONE, /**< Memory leaks are not reported. */
    KZS_SYSTEM_MEMORY_LEAK_REPORTING_WARNING, /**< Warning is logged for memory leaks. This is the default. */
    KZS_SYSTEM_MEMORY_LEAK_REPORTING_EXCEPTION /**< Exception is thrown for memory leaks. */
};


KZ_HEADER_BEGIN


/** Initializes the system. */
kzsError kzsSystemInitialize(void);

/** Uninitializes the system. */
kzsException kzsSystemUninitialize(void);

/** Enables the reporting of leaked memory when uninitializing the application. */
void kzsSystemSetMemoryLeakReporting(enum KzsSystemMemoryLeakReporting reportingMode);

/** Checks if the reporting of leaked memory when uninitializing the application is enabled. */
enum KzsSystemMemoryLeakReporting kzsSystemGetMemoryLeakReporting(void);

/** Converts a 32-bit floating point number to 4 bytes in little-endian format. */
void kzsFloatToBytesLittleEndian(kzFloat floatValue, kzByte* out_floatBytes);

/** Converts a 32-bit floating point number to 4 bytes in big-endian format. */
void kzsFloatToBytesBigEndian(kzFloat floatValue, kzByte* out_floatBytes);

/** Converts 4 bytes of floating point value from little-endian format to a 32-bit floating point number. */
kzFloat kzsBytesToFloatLittleEndian(const kzByte* floatBytes);

/** Converts 4 bytes of floating point value from big-endian format to a 32-bit floating point number. */
kzFloat kzsBytesToFloatBigEndian(const kzByte* floatBytes);

/** Returns the Kanzi version string constant. */
kzString kzsGetVersionString(void);


KZ_HEADER_END


#endif
