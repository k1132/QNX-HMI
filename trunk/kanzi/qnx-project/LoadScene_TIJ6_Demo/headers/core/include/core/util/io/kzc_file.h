/**
* \file
* Core file utilities.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZC_FILE_H
#define KZC_FILE_H


#include <system/kzs_types.h>
#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations */
struct KzcMemoryManager;


/** Get the size of a file with given path. */
kzsException kzcFileGetSize(kzString filePath, kzUint* out_size);

/** Get the file extension of a file with given path. */
kzsError kzcFileGetExtension(const struct KzcMemoryManager* memoryManger, kzString filePath, kzMutableString* out_extension);

/** Reads binary content of a file with given path. The caller must free the returned data using kzcMemoryFreePointer(). */
kzsException kzcFileReadBinaryFile(const struct KzcMemoryManager* memoryManager, kzString filePath, kzUint* out_size, kzByte** out_data);

/** Reads binary content of a resource with given path. The caller must free the returned data using kzcMemoryFreePointer(). */
kzsException kzcFileReadBinaryResource(const struct KzcMemoryManager* memoryManager, kzString resourcePath, kzUint* out_size, kzByte** out_data);

/** Reads the data from the file system to the string with given path. */
kzsException kzcFileReadTextFile(const struct KzcMemoryManager* memoryManager, kzString filePath, kzMutableString* out_string);
/** Reads text lines of a file with given path. */
kzsException kzcFileReadTextFileLines(const struct KzcMemoryManager* memoryManager, kzString filePath, kzMutableString** out_lines);

/**
 * Reads the data from a resource file to the string with given path. The behavior is platform dependent. 
 * E.g. in Android, a "file" is something on the file system and a "resource" is inside APK. In Windows the path for "resources" can be configured.
 */
kzsException kzcFileReadTextResource(const struct KzcMemoryManager* memoryManager, kzString filePath, kzMutableString* out_string);
/** Reads text lines of a resource file with given path. */
kzsException kzcFileReadTextResourceLines(const struct KzcMemoryManager* memoryManager, kzString resourcePath, kzMutableString** out_lines);

/** Writes binary data to a file with given path. */
kzsException kzcFileWriteBinaryFile(const struct KzcMemoryManager* memoryManager, kzString filePath, kzUint size, const kzByte* data);

/** Writes text lines to a file with given path. */
kzsException kzcFileWriteTextFile(const struct KzcMemoryManager* memoryManager, kzString filePath, kzUint lineCount, const kzString* lines);

/** Returns true if file exists. */
kzBool kzcFileExists(kzString filePath);


KZ_HEADER_END


#endif
