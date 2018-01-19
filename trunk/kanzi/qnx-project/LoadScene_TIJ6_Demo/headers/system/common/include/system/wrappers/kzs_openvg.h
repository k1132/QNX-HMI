/**
* \file
* OpenVG wrapper.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZS_OPENVG_H
#define KZS_OPENVG_H


#include <system/kzs_header.h>


KZ_HEADER_BEGIN


#include "kzs_openvg_base.h"


#if KZ_OPENVG_VERSION == KZ_OPENVG_NONE
#include "kzs_openvg_none.h"
#elif KZ_OPENVG_VERSION == KZ_OPENVG_1_1
#include "kzs_openvg11.h"
#else
#error KZ_OPENVG_VERSION undefined or unknown
#endif


KZ_HEADER_END


#endif
