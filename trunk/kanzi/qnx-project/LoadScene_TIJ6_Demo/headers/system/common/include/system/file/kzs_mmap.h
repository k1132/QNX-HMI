/**
* \mmap
* 
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZS_MMAP_H
#define KZS_MMAP_H


#include <system/debug/kzs_error.h>
#include <system/kzs_types.h>
#include <system/kzs_header.h>
#include <system/wrappers/kzs_memory.h>


KZ_HEADER_BEGIN


struct KzsMemoryMappedFile;

/** Returns true if memory mapped files are supported on this platform. */
kzBool kzsMemoryMappedFileIsSupported(void);

/** Opens a memory mapped file. */
kzsError kzsMemoryMappedFileCreate(kzString filePath, struct KzsMemoryMappedFile** out_memoryMappedFile);

/** Closes a memory mapped file. */
kzsError kzsMemoryMappedFileDelete(struct KzsMemoryMappedFile* memoryMappedFile);

/** Returns true if the file exists and is over 0 bytes in size. */
kzBool kzsMemoryMappedFileIsValid(kzString filePath);

/** Returns the size of the memory mapped file. */
kzSizeT kzsMemoryMappedFileGetSize(const struct KzsMemoryMappedFile* memoryMappedFile);

/** Returns the address of the beginning of the memory mapped file. */
void* kzsMemoryMappedFileGetPointer(const struct KzsMemoryMappedFile* memoryMappedFile);


KZ_HEADER_END


#endif
