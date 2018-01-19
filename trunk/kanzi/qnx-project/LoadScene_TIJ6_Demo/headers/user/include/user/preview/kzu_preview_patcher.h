/**
* \file
* Preview patcher. 
* This component provides mechanism for loading and patching .KZB binary data while running under Tool preview.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_PREVIEW_PATCHER_H
#define KZU_PREVIEW_PATCHER_H


#include <system/kzs_types.h>
#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations */
struct KzuBinaryDirectory;
struct KzuBinarySource;
struct KzuUIDomain;


/** Patches with the given .KZB data. Returns the binary source that was created for the data. out_binarySource can be KZ_NULL. */
kzsError kzuPreviewPatcherPatchFromMemory(const struct KzuUIDomain* uiDomain, kzUint byteCount, const kzByte* bytes, struct KzuBinarySource** out_binarySource);

/** Patches with the .KZB data of given file. Returns the binary source that was created for the data. out_binarySource can be KZ_NULL. */
kzsError kzuPreviewPatcherPatchFromFile(const struct KzuUIDomain* uiDomain, kzString filePath, struct KzuBinarySource** out_binarySource);

/** Patches with the .KZB data of given resource. Returns the binary source that was created for the data. out_binarySource can be KZ_NULL. */
kzsError kzuPreviewPatcherPatchFromFileResource(const struct KzuUIDomain* uiDomain, kzString resourcePath, struct KzuBinarySource** out_binarySource);


KZ_HEADER_END


#endif
