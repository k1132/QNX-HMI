/**
* \file
* Screen capturing utility.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZC_SCREEN_CAPTURE_H
#define KZC_SCREEN_CAPTURE_H


#include <core/util/image/kzc_image.h>


KZ_HEADER_BEGIN


/* Forward declarations */
struct KzcMemoryManager;
struct KzcImage;


/** Creates image from color buffer attached to window */
kzsError kzcScreenCaptureToImage(const struct KzcMemoryManager* memoryManager, kzUint width, kzUint height,
                                 enum KzcImageDataFormat format, struct KzcImage** out_image);


KZ_HEADER_END


#endif
