/**
* \file
* Base functions for file related operations.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZS_FILE_BASE_H
#define KZS_FILE_BASE_H


#include <system/kzs_types.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/**
 * Sets the active working directory to the given one.
 * All relative file and resource paths will be relative to the given path after this call, unless path is null.
 * Note that caller is responsible for keeping the path string alive as long as the application is running and accessing resource files.
 */
void kzsFileBaseSetResourceDirectory(kzString path);

/** Returns the active working directory. */
kzString kzsFileBaseGetResourceDirectory(void);


KZ_HEADER_END


#endif
