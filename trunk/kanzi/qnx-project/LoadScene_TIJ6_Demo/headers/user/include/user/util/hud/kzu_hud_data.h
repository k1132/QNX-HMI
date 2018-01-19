/**
* \file
* Heads up display data.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_HUD_DATA_H
#define KZU_HUD_DATA_H


#include <system/debug/kzs_error.h>
#include <system/kzs_types.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


extern const kzUint KZU_HUD_DATA_FONT_IMAGE_DATA_SIZE; /**< Font image data size. */
extern const kzUint KZU_HUD_DATA_FONT_IMAGE_WIDTH; /**< Font image width. */
extern const kzUint KZU_HUD_DATA_FONT_IMAGE_HEIGHT; /**< Font image height. */

extern const kzU8 kzuHudDataFontImage[]; /**< Font image data. */
extern const kzString kzuHudDataFontDescriptor; /**< Font descriptor. */


KZ_HEADER_END


#endif
