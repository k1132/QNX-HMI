/**
* \file
* Core assets.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_CORE_ASSETS_H
#define KZU_CORE_ASSETS_H


#include <system/kzs_types.h>
#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/** URL prefix for loading core assets data. */
#define KZU_CORE_ASSETS_URL_PREFIX "kzb://CoreAssets/"


/* Forward declarations */
struct KzcMemoryManager;
struct KzuBinaryDirectory;


/** Creates core assets binary directory. */
kzsError kzuCoreAssetsCreateDirectory(const struct KzcMemoryManager* memoryManager, struct KzuBinaryDirectory** out_coreAssetsDirectory);


KZ_HEADER_END


#endif
