/**
* \file
* OpenGL wrapper.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZS_OPENGL_H
#define KZS_OPENGL_H


#include <system/kzs_header.h>


KZ_HEADER_BEGIN


#include "kzs_opengl_base.h"


#if KZ_OPENGL_VERSION == KZ_OPENGL_ES_2_0
#include "kzs_opengles20.h"
#elif KZ_OPENGL_VERSION == KZ_OPENGL_ES_3_0
#include "kzs_opengles30.h"
#elif KZ_OPENGL_VERSION == KZ_OPENGL_2_1
#include "kzs_opengl21.h"
#elif KZ_OPENGL_VERSION == KZ_OPENGL_4_3
#include "kzs_opengl43.h"
#elif KZ_OPENGL_VERSION == KZ_OPENGL_LATEST
#include "kzs_opengl_latest.h"
#elif KZ_OPENGL_VERSION == KZ_OPENGL_NONE
#include "kzs_opengl_none.h"
#else
#error KZ_OPENGL_VERSION undefined or unknown
#endif


KZ_HEADER_END


#endif
