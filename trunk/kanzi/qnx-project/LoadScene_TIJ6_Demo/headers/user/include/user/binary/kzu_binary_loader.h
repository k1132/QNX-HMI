/**
* \file
* Binary loader for .kzb format.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_BINARY_LOADER_H
#define KZU_BINARY_LOADER_H


#include <system/kzs_types.h>
#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations. */
struct KzcMemoryManager;
struct KzcProject;
struct KzcInputStream;
struct KzuResourceManager;


/**
 * \struct KzuBinaryLoader
 * Binary loader structure.
 */
struct KzuBinaryLoader;


/** Callback that is asked for if a binary name is valid for loading. */
typedef kzsError (*KzuBinaryLoaderValidator)(kzString binaryPath, void* userData, kzBool* out_valid);


/** Creates a new binary loader. */
kzsError kzuBinaryLoaderCreate(const struct KzcMemoryManager* memoryManager, struct KzuResourceManager* resourceManager,
                               struct KzuBinaryLoader** out_binaryLoader);

/** Deletes a binary loader. */
kzsError kzuBinaryLoaderDelete(struct KzuBinaryLoader* binaryLoader);


/** Sets a callback that is asked for if a binary name is valid for loading. */
kzsError kzuBinaryLoaderSetValidator(struct KzuBinaryLoader* binaryLoader, KzuBinaryLoaderValidator validator, void* userData);


/** Reads the directory structure of given file resource to memory and merges it with the current state. */
kzsError kzuBinaryLoaderAddBinary(const struct KzuBinaryLoader* binaryLoader, kzString binaryPath);

/** Reads the directory structure of given memory block to memory and merges it with the current state. */
kzsError kzuBinaryLoaderAddBinaryMemory(const struct KzuBinaryLoader* binaryLoader, kzUint byteCount, const kzByte* bytes);

/** Maps the binary file to memory and reads the directory structure from it and merges it with the current state. */
kzsError kzuBinaryLoaderAddMemoryMappedBinary(const struct KzuBinaryLoader* binaryLoader, kzString binaryPath);

/** Reads the given binary config file and adds all of the listed binary files to the binary loader. */
kzsException kzuBinaryLoaderAddBinaryConfig(const struct KzuBinaryLoader* binaryLoader, kzString configPath, kzBool useMemoryMapping);


KZ_HEADER_END


#endif
