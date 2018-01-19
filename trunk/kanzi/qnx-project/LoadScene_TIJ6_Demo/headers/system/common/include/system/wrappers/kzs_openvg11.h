/**
* \file
* OpenVG 1.1 wrappers.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZS_OPENVG11_H
#define KZS_OPENVG11_H


#include "kzs_openvg_base.h"

#include <system/debug/kzs_error.h>
#include <system/kzs_types.h>

#include <VG/openvg.h>

#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/** If this is enabled, then all OpenVG calls will be checked for errors. */
#ifdef _DEBUG
#define DEBUG_OPENVG 1
#else
#define DEBUG_OPENVG 0
#endif

#if DEBUG_OPENVG
#include <system/debug/kzs_log.h>


static void kzsVgErrorNotify(VGErrorCode error)
{
    kzString errorString;

    switch (error)
    {
        case VG_BAD_HANDLE_ERROR:               errorString = "VG_BAD_HANDLE_ERROR";               break;
        case VG_ILLEGAL_ARGUMENT_ERROR:         errorString = "VG_ILLEGAL_ARGUMENT_ERROR";         break;
        case VG_OUT_OF_MEMORY_ERROR:            errorString = "VG_OUT_OF_MEMORY_ERROR";            break;
        case VG_PATH_CAPABILITY_ERROR:          errorString = "VG_PATH_CAPABILITY_ERROR";          break;
        case VG_UNSUPPORTED_IMAGE_FORMAT_ERROR: errorString = "VG_UNSUPPORTED_IMAGE_FORMAT_ERROR"; break;
        case VG_UNSUPPORTED_PATH_FORMAT_ERROR:  errorString = "VG_UNSUPPORTED_PATH_FORMAT_ERROR";  break;
        case VG_IMAGE_IN_USE_ERROR:             errorString = "VG_IMAGE_IN_USE_ERROR";             break;
        case VG_NO_CONTEXT_ERROR:               errorString = "VG_NO_CONTEXT_ERROR";               break;
        case VG_NO_ERROR:                       /* Fallthrough */
        case VG_ERROR_CODE_FORCE_SIZE:          /* Fallthrough */
        default:                                errorString = "Unknown OpenVG error";              break;
    }

    kzsLog(KZS_LOG_LEVEL_WARNING, errorString);
}

static void kzsVgErrorTest(void)
{
    const kzInt maxErrors = 8;
    kzInt i = 0;
    VGErrorCode error;
    
    for (;;)
    {
        error = vgGetError();
        if (error == VG_NO_ERROR)
        {
            break;
        }

        if (i >= maxErrors)
        {
            kzsLog(KZS_LOG_LEVEL_WARNING, "Additional OpenVG errors suppressed...");
            break;
        }

        kzsVgErrorNotify(error);
        ++i;        
    }
}
#else
#define kzsVgErrorTest()
#endif

KZ_INLINE VGboolean kzsGetVGBoolean_private(kzBool value)
{
    return value ? VG_TRUE : VG_FALSE;
}


/* Number Representations */
#define KZS_VG_MAXSHORT                                VG_MAXSHORT
#define KZS_VG_MAXINT                                  VG_MAXINT

/* Handle-based Data Types */
typedef VGHandle                                       KzsVgHandle;
typedef VGFont                                         KzsVgFont;
typedef VGImage                                        KzsVgImage;
typedef VGMaskLayer                                    KzsVgMaskLayer;
typedef VGPaint                                        KzsVgPaint;
typedef VGPath                                         KzsVgPath;

#define KZS_VG_INVALID_HANDLE                          VG_INVALID_HANDLE

/* Boolean */
#define KZS_VG_TRUE                                    VG_TRUE
#define KZS_VG_FALSE                                   VG_FALSE

/* Errors */
#define KZS_VG_NO_ERROR                                VG_NO_ERROR
#define KZS_VG_BAD_HANDLE_ERROR                        VG_BAD_HANDLE_ERROR
#define KZS_VG_ILLEGAL_ARGUMENT_ERROR                  VG_ILLEGAL_ARGUMENT_ERROR
#define KZS_VG_OUT_OF_MEMORY_ERROR                     VG_OUT_OF_MEMORY_ERROR
#define KZS_VG_PATH_CAPABILITY_ERROR                   VG_PATH_CAPABILITY_ERROR
#define KZS_VG_UNSUPPORTED_IMAGE_FORMAT_ERROR          VG_UNSUPPORTED_IMAGE_FORMAT_ERROR
#define KZS_VG_UNSUPPORTED_PATH_FORMAT_ERROR           VG_UNSUPPORTED_PATH_FORMAT_ERROR
#define KZS_VG_IMAGE_IN_USE_ERROR                      VG_IMAGE_IN_USE_ERROR
#define KZS_VG_NO_CONTEXT_ERROR                        VG_NO_CONTEXT_ERROR

/* Context Parameters*/
typedef VGParamType                                    KzsVgParamType;

#define KZS_VG_MATRIX_MODE                             VG_MATRIX_MODE

#define KZS_VG_MATRIX_PATH_USER_TO_SURFACE             VG_MATRIX_PATH_USER_TO_SURFACE
#define KZS_VG_MATRIX_IMAGE_USER_TO_SURFACE            VG_MATRIX_IMAGE_USER_TO_SURFACE
#define KZS_VG_MATRIX_FILL_PAINT_TO_USER               VG_MATRIX_FILL_PAINT_TO_USER
#define KZS_VG_MATRIX_STROKE_PAINT_TO_USER             VG_MATRIX_STROKE_PAINT_TO_USER
#define KZS_VG_MATRIX_GLYPH_USER_TO_SURFACE            VG_MATRIX_GLYPH_USER_TO_SURFACE

#define KZS_VG_FILL_RULE                               VG_FILL_RULE

#define KZS_VG_EVEN_ODD                                VG_EVEN_ODD
#define KZS_VG_NON_ZERO                                VG_NON_ZERO

#define KZS_VG_IMAGE_QUALITY                           VG_IMAGE_QUALITY

#define KZS_VG_IMAGE_QUALITY_NONANTIALIASED            VG_IMAGE_QUALITY_NONANTIALIASED
#define KZS_VG_IMAGE_QUALITY_FASTER                    VG_IMAGE_QUALITY_FASTER
#define KZS_VG_IMAGE_QUALITY_BETTER                    VG_IMAGE_QUALITY_BETTER

#define KZS_VG_RENDERING_QUALITY                       VG_RENDERING_QUALITY

#define KZS_VG_RENDERING_QUALITY_NONANTIALIASED        VG_RENDERING_QUALITY_NONANTIALIASED
#define KZS_VG_RENDERING_QUALITY_FASTER                VG_RENDERING_QUALITY_FASTER
#define KZS_VG_RENDERING_QUALITY_BETTER                VG_RENDERING_QUALITY_BETTER

#define KZS_VG_BLEND_MODE                              VG_BLEND_MODE

#define KZS_VG_BLEND_SRC                               VG_BLEND_SRC
#define KZS_VG_BLEND_SRC_OVER                          VG_BLEND_SRC_OVER
#define KZS_VG_BLEND_DST_OVER                          VG_BLEND_DST_OVER
#define KZS_VG_BLEND_SRC_IN                            VG_BLEND_SRC_IN
#define KZS_VG_BLEND_DST_IN                            VG_BLEND_DST_IN
#define KZS_VG_BLEND_MULTIPLY                          VG_BLEND_MULTIPLY
#define KZS_VG_BLEND_SCREEN                            VG_BLEND_SCREEN
#define KZS_VG_BLEND_DARKEN                            VG_BLEND_DARKEN
#define KZS_VG_BLEND_LIGHTEN                           VG_BLEND_LIGHTEN
#define KZS_VG_BLEND_ADDITIVE                          VG_BLEND_ADDITIVE

#define KZS_VG_IMAGE_MODE                              VG_IMAGE_MODE

#define KZS_VG_DRAW_IMAGE_NORMAL                       VG_DRAW_IMAGE_NORMAL
#define KZS_VG_DRAW_IMAGE_MULTIPLY                     VG_DRAW_IMAGE_MULTIPLY
#define KZS_VG_DRAW_IMAGE_STENCIL                      VG_DRAW_IMAGE_STENCIL

#define KZS_VG_SCISSOR_RECTS                           VG_SCISSOR_RECTS

#define KZS_VG_COLOR_TRANSFORM                         VG_COLOR_TRANSFORM

#define KZS_VG_COLOR_TRANSFORM_VALUES                  VG_COLOR_TRANSFORM_VALUES

#define KZS_VG_STROKE_LINE_WIDTH                       VG_STROKE_LINE_WIDTH

#define KZS_VG_STROKE_CAP_STYLE                        VG_STROKE_CAP_STYLE

#define KZS_VG_CAP_BUTT                                VG_CAP_BUTT
#define KZS_VG_CAP_ROUND                               VG_CAP_ROUND
#define KZS_VG_CAP_SQUARE                              VG_CAP_SQUARE

#define KZS_VG_STROKE_JOIN_STYLE                       VG_STROKE_JOIN_STYLE

#define KZS_VG_JOIN_MITER                              VG_JOIN_MITER
#define KZS_VG_JOIN_ROUND                              VG_JOIN_ROUND
#define KZS_VG_JOIN_BEVEL                              VG_JOIN_BEVEL

#define KZS_VG_STROKE_MITER_LIMIT                      VG_STROKE_MITER_LIMIT

#define KZS_VG_STROKE_DASH_PATTERN                     VG_STROKE_DASH_PATTERN

#define KZS_VG_STROKE_DASH_PHASE                       VG_STROKE_DASH_PHASE

#define KZS_VG_STROKE_DASH_PHASE_RESET                 VG_STROKE_DASH_PHASE_RESET

#define KZS_VG_TILE_FILL_COLOR                         VG_TILE_FILL_COLOR

#define KZS_VG_CLEAR_COLOR                             VG_CLEAR_COLOR

#define KZS_VG_GLYPH_ORIGIN                            VG_GLYPH_ORIGIN

#define KZS_VG_MASKING                                 VG_MASKING

#define KZS_VG_SCISSORING                              VG_SCISSORING

#define KZS_VG_SCREEN_LAYOUT                           VG_SCREEN_LAYOUT

#define KZS_VG_PIXEL_LAYOUT                            VG_PIXEL_LAYOUT

#define KZS_VG_PIXEL_LAYOUT_UNKNOWN                    VG_PIXEL_LAYOUT_UNKNOWN
#define KZS_VG_PIXEL_LAYOUT_RGB_VERTICAL               VG_PIXEL_LAYOUT_RGB_VERTICAL
#define KZS_VG_PIXEL_LAYOUT_BGR_VERTICAL               VG_PIXEL_LAYOUT_BGR_VERTICAL
#define KZS_VG_PIXEL_LAYOUT_RGB_HORIZONTAL             VG_PIXEL_LAYOUT_RGB_HORIZONTAL
#define KZS_VG_PIXEL_LAYOUT_BGR_HORIZONTAL             VG_PIXEL_LAYOUT_BGR_HORIZONTAL

#define KZS_VG_FILTER_FORMAT_LINEAR                    VG_FILTER_FORMAT_LINEAR

#define KZS_VG_FILTER_FORMAT_PREMULTIPLIED             VG_FILTER_FORMAT_PREMULTIPLIED

#define KZS_VG_FILTER_CHANNEL_MASK                     VG_FILTER_CHANNEL_MASK

#define KZS_VG_RED                                     VG_RED
#define KZS_VG_GREEN                                   VG_GREEN
#define KZS_VG_BLUE                                    VG_BLUE
#define KZS_VG_ALPHA                                   VG_ALPHA

/* Read-only Context Parameters*/
#define KZS_VG_MAX_SCISSOR_RECTS                       VG_MAX_SCISSOR_RECTS
#define KZS_VG_MAX_DASH_COUNT                          VG_MAX_DASH_COUNT
#define KZS_VG_MAX_KERNEL_SIZE                         VG_MAX_KERNEL_SIZE
#define KZS_VG_MAX_SEPARABLE_KERNEL_SIZE               VG_MAX_SEPARABLE_KERNEL_SIZE
#define KZS_VG_MAX_COLOR_RAMP_STOPS                    VG_MAX_COLOR_RAMP_STOPS
#define KZS_VG_MAX_IMAGE_WIDTH                         VG_MAX_IMAGE_WIDTH
#define KZS_VG_MAX_IMAGE_HEIGHT                        VG_MAX_IMAGE_HEIGHT
#define KZS_VG_MAX_IMAGE_PIXELS                        VG_MAX_IMAGE_PIXELS
#define KZS_VG_MAX_IMAGE_BYTES                         VG_MAX_IMAGE_BYTES
#define KZS_VG_MAX_FLOAT                               VG_MAX_FLOAT
#define KZS_VG_MAX_GAUSSIAN_STD_DEVIATION              VG_MAX_GAUSSIAN_STD_DEVIATION

/* Mask Operation */
typedef VGMaskOperation                                KzsVgMaskOperation;

#define KZS_VG_CLEAR_MASK                              VG_CLEAR_MASK
#define KZS_VG_FILL_MASK                               VG_FILL_MASK
#define KZS_VG_SET_MASK                                VG_SET_MASK
#define KZS_VG_UNION_MASK                              VG_UNION_MASK
#define KZS_VG_INTERSECT_MASK                          VG_INTERSECT_MASK
#define KZS_VG_SUBTRACT_MASK                           VG_SUBTRACT_MASK

/* Segment Commands */
#define KZS_VG_CLOSE_PATH                              VG_CLOSE_PATH
#define KZS_VG_MOVE_TO_ABS                             VG_MOVE_TO_ABS
#define KZS_VG_LINE_TO_ABS                             VG_LINE_TO_ABS
#define KZS_VG_HLINE_TO_ABS                            VG_HLINE_TO_ABS
#define KZS_VG_VLINE_TO_ABS                            VG_VLINE_TO_ABS
#define KZS_VG_QUAD_TO_ABS                             VG_QUAD_TO_ABS
#define KZS_VG_CUBIC_TO_ABS                            VG_CUBIC_TO_ABS
#define KZS_VG_SQUAD_TO_ABS                            VG_SQUAD_TO_ABS
#define KZS_VG_SCUBIC_TO_ABS                           VG_SCUBIC_TO_ABS
#define KZS_VG_SCCWARC_TO_ABS                          VG_SCCWARC_TO_ABS
#define KZS_VG_SCWARC_TO_ABS                           VG_SCWARC_TO_ABS
#define KZS_VG_LCCWARC_TO_ABS                          VG_LCCWARC_TO_ABS
#define KZS_VG_LCWARC_TO_ABS                           VG_LCWARC_TO_ABS
#define KZS_VG_MOVE_TO_REL                             VG_MOVE_TO_REL
#define KZS_VG_LINE_TO_REL                             VG_LINE_TO_REL
#define KZS_VG_HLINE_TO_REL                            VG_HLINE_TO_REL
#define KZS_VG_VLINE_TO_REL                            VG_VLINE_TO_REL
#define KZS_VG_QUAD_TO_REL                             VG_QUAD_TO_REL
#define KZS_VG_CUBIC_TO_REL                            VG_CUBIC_TO_REL
#define KZS_VG_SQUAD_TO_REL                            VG_SQUAD_TO_REL
#define KZS_VG_SCUBIC_TO_REL                           VG_SCUBIC_TO_REL
#define KZS_VG_SCCWARC_TO_REL                          VG_SCCWARC_TO_REL
#define KZS_VG_SCWARC_TO_REL                           VG_SCWARC_TO_REL
#define KZS_VG_LCCWARC_TO_REL                          VG_LCCWARC_TO_REL
#define KZS_VG_LCWARC_TO_REL                           VG_LCWARC_TO_REL

/* Path Operations */
#define KZS_VG_PATH_CAPABILITY_APPEND_FROM             VG_PATH_CAPABILITY_APPEND_FROM
#define KZS_VG_PATH_CAPABILITY_APPEND_TO               VG_PATH_CAPABILITY_APPEND_TO
#define KZS_VG_PATH_CAPABILITY_MODIFY                  VG_PATH_CAPABILITY_MODIFY
#define KZS_VG_PATH_CAPABILITY_TRANSFORM_FROM          VG_PATH_CAPABILITY_TRANSFORM_FROM
#define KZS_VG_PATH_CAPABILITY_TRANSFORM_TO            VG_PATH_CAPABILITY_TRANSFORM_TO
#define KZS_VG_PATH_CAPABILITY_INTERPOLATE_FROM        VG_PATH_CAPABILITY_INTERPOLATE_FROM
#define KZS_VG_PATH_CAPABILITY_INTERPOLATE_TO          VG_PATH_CAPABILITY_INTERPOLATE_TO
#define KZS_VG_PATH_CAPABILITY_PATH_LENGTH             VG_PATH_CAPABILITY_PATH_LENGTH
#define KZS_VG_PATH_CAPABILITY_POINT_ALONG_PATH        VG_PATH_CAPABILITY_POINT_ALONG_PATH
#define KZS_VG_PATH_CAPABILITY_TANGENT_ALONG_PATH      VG_PATH_CAPABILITY_TANGENT_ALONG_PATH
#define KZS_VG_PATH_CAPABILITY_PATH_BOUNDS             VG_PATH_CAPABILITY_PATH_BOUNDS
#define KZS_VG_PATH_CAPABILITY_PATH_TRANSFORMED_BOUNDS VG_PATH_CAPABILITY_PATH_TRANSFORMED_BOUNDS
#define KZS_VG_PATH_CAPABILITY_ALL                     VG_PATH_CAPABILITY_ALL

/* Path Object Parameter */
#define KZS_VG_PATH_FORMAT                             VG_PATH_FORMAT

#define KZS_VG_PATH_FORMAT_STANDARD                    VG_PATH_FORMAT_STANDARD

typedef VGPathDatatype                                 KzsVgPathDatatype;

#define KZS_VG_PATH_DATATYPE                           VG_PATH_DATATYPE

#define KZS_VG_PATH_DATATYPE_S_8                       VG_PATH_DATATYPE_S_8
#define KZS_VG_PATH_DATATYPE_S_16                      VG_PATH_DATATYPE_S_16
#define KZS_VG_PATH_DATATYPE_S_32                      VG_PATH_DATATYPE_S_32
#define KZS_VG_PATH_DATATYPE_F                         VG_PATH_DATATYPE_F

#define KZS_VG_PATH_SCALE                              VG_PATH_SCALE

#define KZS_VG_PATH_BIAS                               VG_PATH_BIAS

#define KZS_VG_PATH_NUM_SEGMENTS                       VG_PATH_NUM_SEGMENTS

#define KZS_VG_PATH_NUM_COORDS                         VG_PATH_NUM_COORDS

/* Paint Modes */
typedef VGPaintMode                                    KzsVgPaintMode;

#define KZS_VG_STROKE_PATH                             VG_STROKE_PATH
#define KZS_VG_FILL_PATH                               VG_FILL_PATH

#define KZS_VG_PAINT_TYPE                              VG_PAINT_TYPE

#define KZS_VG_PAINT_TYPE_COLOR                        VG_PAINT_TYPE_COLOR
#define KZS_VG_PAINT_TYPE_LINEAR_GRADIENT              VG_PAINT_TYPE_LINEAR_GRADIENT
#define KZS_VG_PAINT_TYPE_RADIAL_GRADIENT              VG_PAINT_TYPE_RADIAL_GRADIENT
#define KZS_VG_PAINT_TYPE_PATTERN                      VG_PAINT_TYPE_PATTERN

#define KZS_VG_PAINT_COLOR                             VG_PAINT_COLOR

#define KZS_VG_PAINT_COLOR_RAMP_SPREAD_MODE            VG_PAINT_COLOR_RAMP_SPREAD_MODE

#define KZS_VG_COLOR_RAMP_SPREAD_PAD                   VG_COLOR_RAMP_SPREAD_PAD
#define KZS_VG_COLOR_RAMP_SPREAD_REPEAT                VG_COLOR_RAMP_SPREAD_REPEAT
#define KZS_VG_COLOR_RAMP_SPREAD_REFLECT               VG_COLOR_RAMP_SPREAD_REFLECT

#define KZS_VG_PAINT_COLOR_RAMP_PREMULTIPLIED          VG_PAINT_COLOR_RAMP_PREMULTIPLIED

#define KZS_VG_PAINT_COLOR_RAMP_STOPS                  VG_PAINT_COLOR_RAMP_STOPS

#define KZS_VG_PAINT_LINEAR_GRADIENT                   VG_PAINT_LINEAR_GRADIENT

#define KZS_VG_PAINT_RADIAL_GRADIENT                   VG_PAINT_RADIAL_GRADIENT

#define KZS_VG_PAINT_PATTERN_TILING_MODE               VG_PAINT_PATTERN_TILING_MODE

#define KZS_VG_TILE_FILL                               VG_TILE_FILL
#define KZS_VG_TILE_PAD                                VG_TILE_PAD
#define KZS_VG_TILE_REPEAT                             VG_TILE_REPEAT
#define KZS_VG_TILE_REFLECT                            VG_TILE_REFLECT

/* Image Object Parameter */
typedef VGImageFormat                                  KzsVgImageFormat;

#define KZS_VG_IMAGE_FORMAT                            VG_IMAGE_FORMAT

#define KZS_VG_sRGBX_8888                              VG_sRGBX_8888
#define KZS_VG_sRGBA_8888                              VG_sRGBA_8888
#define KZS_VG_sRGBA_8888_PRE                          VG_sRGBA_8888_PRE
#define KZS_VG_sRGB_565                                VG_sRGB_565
#define KZS_VG_sRGBA_5551                              VG_sRGBA_5551
#define KZS_VG_sRGBA_4444                              VG_sRGBA_4444
#define KZS_VG_sL_8                                    VG_sL_8
#define KZS_VG_lRGBX_8888                              VG_lRGBX_8888
#define KZS_VG_lRGBA_8888                              VG_lRGBA_8888
#define KZS_VG_lRGBA_8888_PRE                          VG_lRGBA_8888_PRE
#define KZS_VG_lL_8                                    VG_lL_8
#define KZS_VG_A_8                                     VG_A_8
#define KZS_VG_BW_1                                    VG_BW_1
#define KZS_VG_A_1                                     VG_A_1
#define KZS_VG_A_4                                     VG_A_4

#define KZS_VG_sXRGB_8888                              VG_sXRGB_8888
#define KZS_VG_sARGB_8888                              VG_sARGB_8888
#define KZS_VG_sARGB_8888_PRE                          VG_sARGB_8888_PRE
#define KZS_VG_sARGB_1555                              VG_sARGB_1555
#define KZS_VG_sARGB_4444                              VG_sARGB_4444
#define KZS_VG_lXRGB_8888                              VG_lXRGB_8888
#define KZS_VG_lARGB_8888                              VG_lARGB_8888
#define KZS_VG_lARGB_8888_PRE                          VG_lARGB_8888_PRE

#define KZS_VG_sBGRX_8888                              VG_sBGRX_8888
#define KZS_VG_sBGRA_8888                              VG_sBGRA_8888
#define KZS_VG_sBGRA_8888_PRE                          VG_sBGRA_8888_PRE
#define KZS_VG_sBGR_565                                VG_sBGR_565
#define KZS_VG_sBGRA_5551                              VG_sBGRA_5551
#define KZS_VG_sBGRA_4444                              VG_sBGRA_4444
#define KZS_VG_lBGRX_8888                              VG_lBGRX_8888
#define KZS_VG_lBGRA_8888                              VG_lBGRA_8888
#define KZS_VG_lBGRA_8888_PRE                          VG_lBGRA_8888_PRE

#define KZS_VG_sXBGR_8888                              VG_sXBGR_8888
#define KZS_VG_sABGR_8888                              VG_sABGR_8888
#define KZS_VG_sABGR_8888_PRE                          VG_sABGR_8888_PRE
#define KZS_VG_sABGR_1555                              VG_sABGR_1555
#define KZS_VG_sABGR_4444                              VG_sABGR_4444
#define KZS_VG_lXBGR_8888                              VG_lXBGR_8888
#define KZS_VG_lABGR_8888                              VG_lABGR_8888
#define KZS_VG_lABGR_8888_PRE                          VG_lABGR_8888_PRE

#define KZS_VG_IMAGE_WIDTH                             VG_IMAGE_WIDTH
#define KZS_VG_IMAGE_HEIGHT                            VG_IMAGE_HEIGHT

/* Font Object Parameter */
#define KZS_VG_FONT_NUM_GLYPHS                         VG_FONT_NUM_GLYPHS

/* Convolution */
typedef VGTilingMode                                   KzsVgTilingMode;
typedef VGImageChannel                                 KzsVgImageChannel;

/* Querying Hardware Capabilities */
typedef VGHardwareQueryResult                          KzsVgHardwareQueryResult;

#define KZS_VG_HARDWARE_ACCELERATED                    VG_HARDWARE_ACCELERATED
#define KZS_VG_HARDWARE_UNACCELERATED                  VG_HARDWARE_UNACCELERATED

typedef VGHardwareQueryType                            KzsVgHardwareQueryType;

#define KZS_VG_IMAGE_FORMAT_QUERY                      VG_IMAGE_FORMAT_QUERY
#define KZS_VG_PATH_DATATYPE_QUERY                     VG_PATH_DATATYPE_QUERY

/* String IDs */
typedef VGStringID                                     KzsVgStringID;

#define KZS_VG_VENDOR                                  VG_VENDOR
#define KZS_VG_RENDERER                                VG_RENDERER
#define KZS_VG_VERSION                                 VG_VERSION
#define KZS_VG_EXTENSIONS                              VG_EXTENSIONS


/* Object Parameter Set/Get API */

KZ_INLINE void kzsVgSetParameterf(KzsVgHandle obj, kzInt paramType, kzFloat val)
{
KZS_OPENVG_CALL_BEGIN
    vgSetParameterf(obj, paramType, val);
    kzsVgErrorTest();
KZS_OPENVG_CALL_END
}

KZ_INLINE void kzsVgSetParameteri(KzsVgHandle obj, kzInt paramType, kzInt val)
{
KZS_OPENVG_CALL_BEGIN
    vgSetParameteri(obj, paramType, val);
    kzsVgErrorTest();
KZS_OPENVG_CALL_END
}

KZ_INLINE void kzsVgSetParameterfv(KzsVgHandle obj, kzInt paramType, kzInt cnt, const kzFloat* val)
{
KZS_OPENVG_CALL_BEGIN
    vgSetParameterfv(obj, paramType, cnt, val);
    kzsVgErrorTest();
KZS_OPENVG_CALL_END
}

KZ_INLINE void kzsVgSetParameteriv(KzsVgHandle obj, kzInt paramType, kzInt cnt, const kzInt* val)
{
KZS_OPENVG_CALL_BEGIN
    vgSetParameteriv(obj, paramType, cnt, val);
    kzsVgErrorTest();
KZS_OPENVG_CALL_END
}

KZ_INLINE kzFloat kzsVgGetParameterf(KzsVgHandle obj, kzInt paramType)
{
KZS_OPENVG_CALL_BEGIN
    return vgGetParameterf(obj, paramType);
KZS_OPENVG_CALL_END_RETURN_VALUE(0.0f)
}

KZ_INLINE kzInt kzsVgGetParameteri(KzsVgHandle obj, kzInt paramType)
{
KZS_OPENVG_CALL_BEGIN
    return vgGetParameteri(obj, paramType);
KZS_OPENVG_CALL_END_RETURN_VALUE(0)
}

KZ_INLINE kzInt kzsVgGetParameterVectorSize(KzsVgHandle obj, kzInt paramType)
{
KZS_OPENVG_CALL_BEGIN
    return vgGetParameterVectorSize(obj, paramType);
KZS_OPENVG_CALL_END_RETURN_VALUE(0)
}

KZ_INLINE void kzsVgGetParameterfv(KzsVgHandle obj, kzInt paramType, kzInt cnt, kzFloat* val)
{
KZS_OPENVG_CALL_BEGIN
    vgGetParameterfv(obj, paramType, cnt, val);
    kzsVgErrorTest();
KZS_OPENVG_CALL_END
}

KZ_INLINE void kzsVgGetParameteriv(KzsVgHandle obj, kzInt paramType, kzInt cnt, kzInt* val)
{
KZS_OPENVG_CALL_BEGIN
    vgGetParameteriv(obj, paramType, cnt, val);
    kzsVgErrorTest();
KZS_OPENVG_CALL_END
}

/* Forcing Drawing to Complete API */

KZ_INLINE void kzsVgFlush(void)
{
KZS_OPENVG_CALL_BEGIN
    vgFlush();
    kzsVgErrorTest();
KZS_OPENVG_CALL_END
}

KZ_INLINE void kzsVgFinish(void)
{
KZS_OPENVG_CALL_BEGIN
    vgFinish();
    kzsVgErrorTest();
KZS_OPENVG_CALL_END
}

/* Context Parameter Set/Get API */

KZ_INLINE void kzsVgSetf(KzsVgParamType paramType, kzFloat val)
{
KZS_OPENVG_CALL_BEGIN
    vgSetf(paramType, val);
    kzsVgErrorTest();
KZS_OPENVG_CALL_END
}

KZ_INLINE void kzsVgSeti(KzsVgParamType paramType, kzInt val)
{
KZS_OPENVG_CALL_BEGIN
    vgSeti(paramType, val);
    kzsVgErrorTest();
KZS_OPENVG_CALL_END
}

KZ_INLINE void kzsVgSetfv(KzsVgParamType paramType, kzInt cnt, const kzFloat* val)
{
KZS_OPENVG_CALL_BEGIN
    vgSetfv(paramType, cnt, val);
    kzsVgErrorTest();
KZS_OPENVG_CALL_END
}

KZ_INLINE void kzsVgSetiv(KzsVgParamType paramType, kzInt cnt, const kzInt* val)
{
KZS_OPENVG_CALL_BEGIN
    vgSetiv(paramType, cnt, val);
    kzsVgErrorTest();
KZS_OPENVG_CALL_END
}

KZ_INLINE kzFloat kzsVgGetf(KzsVgParamType paramType)
{
KZS_OPENVG_CALL_BEGIN
    return vgGetf(paramType);
KZS_OPENVG_CALL_END_RETURN_VALUE(0.0f)
}

KZ_INLINE kzInt kzsVgGeti(KzsVgParamType paramType)
{
KZS_OPENVG_CALL_BEGIN
    return vgGeti(paramType);
KZS_OPENVG_CALL_END_RETURN_VALUE(0)
}

KZ_INLINE kzInt kzsVgGetVectorSize(KzsVgParamType paramType)
{
KZS_OPENVG_CALL_BEGIN
    return vgGetVectorSize(paramType);
KZS_OPENVG_CALL_END_RETURN_VALUE(0)
}

KZ_INLINE void kzsVgGetfv(KzsVgParamType paramType, kzInt cnt, kzFloat* val)
{
KZS_OPENVG_CALL_BEGIN
    vgGetfv(paramType, cnt, val);
    kzsVgErrorTest();
KZS_OPENVG_CALL_END
}

KZ_INLINE void kzsVgGetiv(KzsVgParamType paramType, kzInt cnt, kzInt* val)
{
KZS_OPENVG_CALL_BEGIN
    vgGetiv(paramType, cnt, val);
    kzsVgErrorTest();
KZS_OPENVG_CALL_END
}

/* Matrix Transformation */

KZ_INLINE void kzsVgLoadIdentity(void)
{
KZS_OPENVG_CALL_BEGIN
    vgLoadIdentity();
    kzsVgErrorTest();
KZS_OPENVG_CALL_END
}

KZ_INLINE void kzsVgLoadMatrix(const kzFloat* m)
{
KZS_OPENVG_CALL_BEGIN
    vgLoadMatrix(m);
    kzsVgErrorTest();
KZS_OPENVG_CALL_END
}

KZ_INLINE void kzsVgMultMatrix(const kzFloat* m)
{
KZS_OPENVG_CALL_BEGIN
    vgMultMatrix(m);
    kzsVgErrorTest();
KZS_OPENVG_CALL_END
}

KZ_INLINE void kzsVgGetMatrix(kzFloat* m)
{
KZS_OPENVG_CALL_BEGIN
    vgGetMatrix(m);
    kzsVgErrorTest();
KZS_OPENVG_CALL_END
}

KZ_INLINE void kzsVgTranslate(kzFloat tx, kzFloat ty)
{
KZS_OPENVG_CALL_BEGIN
    vgTranslate(tx, ty);
    kzsVgErrorTest();
KZS_OPENVG_CALL_END
}

KZ_INLINE void kzsVgScale(kzFloat sx, kzFloat sy)
{
KZS_OPENVG_CALL_BEGIN
    vgTranslate(sx, sy);
    kzsVgErrorTest();
KZS_OPENVG_CALL_END
}

KZ_INLINE void kzsVgShear(kzFloat shx, kzFloat shy)
{
KZS_OPENVG_CALL_BEGIN
    vgShear(shx, shy);
    kzsVgErrorTest();
KZS_OPENVG_CALL_END
}

KZ_INLINE void kzsVgRotate(kzFloat angle)
{
KZS_OPENVG_CALL_BEGIN
    vgRotate(angle);
    kzsVgErrorTest();
KZS_OPENVG_CALL_END
}

/* Masking */

KZ_INLINE void kzsVgMask(KzsVgHandle mask, KzsVgMaskOperation op, kzInt x, kzInt y, kzInt width, kzInt height)
{
KZS_OPENVG_CALL_BEGIN
    vgMask(mask, op, x, y, width, height);
    kzsVgErrorTest();
KZS_OPENVG_CALL_END
}

KZ_INLINE void kzsVgRenderToMask(KzsVgPath path, kzUint paintMode, KzsVgMaskOperation op)
{
KZS_OPENVG_CALL_BEGIN
    vgRenderToMask(path, paintMode, op);
    kzsVgErrorTest();
KZS_OPENVG_CALL_END
}

KZ_INLINE KzsVgMaskLayer kzsVgCreateMaskLayer(kzInt width, kzInt height)
{
KZS_OPENVG_CALL_BEGIN
    return vgCreateMaskLayer(width, height);
KZS_OPENVG_CALL_END_RETURN_VALUE(KZS_VG_INVALID_HANDLE)
}

KZ_INLINE void kzsVgDestroyMaskLayer(KzsVgMaskLayer masklayer)
{
KZS_OPENVG_CALL_BEGIN
    vgDestroyMaskLayer(masklayer);
    kzsVgErrorTest();
KZS_OPENVG_CALL_END
}

KZ_INLINE void kzsVgFillMaskLayer(KzsVgMaskLayer masklayer, kzInt x, kzInt y,
                                  kzInt width, kzInt height, kzFloat val)
{
KZS_OPENVG_CALL_BEGIN
    vgFillMaskLayer(masklayer, x, y, width, height, val);
    kzsVgErrorTest();
KZS_OPENVG_CALL_END
}

KZ_INLINE void kzsVgCopyMask(KzsVgMaskLayer masklayer, kzInt x, kzInt y, kzInt sx, kzInt sy,
                             kzInt width, kzInt height)
{
KZS_OPENVG_CALL_BEGIN
    vgCopyMask(masklayer, x, y, sx, sy, width, height);
    kzsVgErrorTest();
KZS_OPENVG_CALL_END
}

/* Fast Clear */

KZ_INLINE void kzsVgClear(kzInt x, kzInt y, kzInt width, kzInt height)
{
KZS_OPENVG_CALL_BEGIN
    vgClear(x, y, width, height);
    kzsVgErrorTest();
KZS_OPENVG_CALL_END
}

/* Path */

KZ_INLINE KzsVgPath kzsVgCreatePath(kzInt pathFormat, KzsVgPathDatatype datatype, kzFloat scale, kzFloat bias,
                                    kzInt segCapacityHint, kzInt coordCapacityHint, kzUint capabilities)
{
KZS_OPENVG_CALL_BEGIN
    return vgCreatePath(pathFormat, datatype, scale, bias, segCapacityHint, coordCapacityHint, capabilities);
KZS_OPENVG_CALL_END_RETURN_VALUE(KZS_VG_INVALID_HANDLE)
}

KZ_INLINE void kzsVgClearPath(KzsVgPath path, kzUint capabilities)
{
KZS_OPENVG_CALL_BEGIN
    vgClearPath(path, capabilities);
    kzsVgErrorTest();
KZS_OPENVG_CALL_END
}

KZ_INLINE void kzsVgDestroyPath(KzsVgPath path)
{
KZS_OPENVG_CALL_BEGIN
    vgDestroyPath(path);
    kzsVgErrorTest();
KZS_OPENVG_CALL_END
}

KZ_INLINE kzUint kzsVgGetPathCapabilities(KzsVgPath path)
{
KZS_OPENVG_CALL_BEGIN
    return vgGetPathCapabilities(path);
KZS_OPENVG_CALL_END_RETURN_VALUE(0)
}

KZ_INLINE void kzsVgRemovePathCapabilities(KzsVgPath path, kzUint capabilities)
{
KZS_OPENVG_CALL_BEGIN
    vgRemovePathCapabilities(path, capabilities);
    kzsVgErrorTest();
KZS_OPENVG_CALL_END
}

KZ_INLINE void kzsVgAppendPath(KzsVgPath dstPath, KzsVgPath srcPath)
{
KZS_OPENVG_CALL_BEGIN
    vgAppendPath(dstPath, srcPath);
    kzsVgErrorTest();
KZS_OPENVG_CALL_END
}

KZ_INLINE void kzsVgAppendPathData(KzsVgPath dstPath, kzInt numSeg, const kzByte* pathSeg, const void* pathData)
{
KZS_OPENVG_CALL_BEGIN
    vgAppendPathData(dstPath, numSeg, pathSeg, pathData);
    kzsVgErrorTest();
KZS_OPENVG_CALL_END
}

KZ_INLINE void kzsVgModifyPathCoords(KzsVgPath dstPath, kzInt startIdx, kzInt numSeg, const void* pathData)
{
KZS_OPENVG_CALL_BEGIN
    vgModifyPathCoords(dstPath, startIdx, numSeg, pathData);
    kzsVgErrorTest();
KZS_OPENVG_CALL_END
}

KZ_INLINE void kzsVgTransformPath(KzsVgPath dstPath, KzsVgPath srcPath)
{
KZS_OPENVG_CALL_BEGIN
    vgTransformPath(dstPath, srcPath);
    kzsVgErrorTest();
KZS_OPENVG_CALL_END
}

KZ_INLINE kzBool kzsVgInterpolatePath(KzsVgPath dstPath, KzsVgPath startPath, KzsVgPath endPath, kzFloat amount)
{
KZS_OPENVG_CALL_BEGIN
    return vgInterpolatePath(dstPath, startPath, endPath, amount) == VG_TRUE ? KZ_TRUE : KZ_FALSE;
KZS_OPENVG_CALL_END_RETURN_VALUE(KZ_FALSE)
}

KZ_INLINE kzFloat kzsVgPathLength(KzsVgPath path, kzInt startSeg, kzInt numSeg)
{
KZS_OPENVG_CALL_BEGIN
    return vgPathLength(path, startSeg, numSeg);
KZS_OPENVG_CALL_END_RETURN_VALUE(-1.0f)
}

KZ_INLINE void kzsVgPointAlongPath(KzsVgPath dstPath, kzInt startSeg, kzInt numSeg, kzFloat distance, kzFloat* out_x, kzFloat* out_y, kzFloat* out_tanX, kzFloat* out_tanY)
{
KZS_OPENVG_CALL_BEGIN
    vgPointAlongPath(dstPath, startSeg, numSeg, distance, out_x, out_y, out_tanX, out_tanY);
    kzsVgErrorTest();
KZS_OPENVG_CALL_END
}

KZ_INLINE void kzsVgPathBounds(KzsVgPath dstPath, kzFloat* out_minx, kzFloat* out_miny, kzFloat* out_width, kzFloat* out_height)
{
KZS_OPENVG_CALL_BEGIN
    vgPathBounds(dstPath, out_minx, out_miny, out_width, out_height);
    kzsVgErrorTest();
KZS_OPENVG_CALL_END
}

KZ_INLINE void kzsVgPathTransformedBounds(KzsVgPath dstPath, kzFloat* out_minx, kzFloat* out_miny, kzFloat* out_width, kzFloat* out_height)
{
KZS_OPENVG_CALL_BEGIN
    vgPathTransformedBounds(dstPath, out_minx, out_miny, out_width, out_height);
    kzsVgErrorTest();
KZS_OPENVG_CALL_END
}

KZ_INLINE void kzsVgDrawPath(KzsVgPath path, kzUint paintModes)
{
KZS_OPENVG_CALL_BEGIN
    vgDrawPath(path, paintModes);
    kzsVgErrorTest();
KZS_OPENVG_CALL_END
}

/* Paint */

KZ_INLINE KzsVgPaint kzsVgCreatePaint(void)
{
KZS_OPENVG_CALL_BEGIN
    return vgCreatePaint();
KZS_OPENVG_CALL_END_RETURN_VALUE(KZS_VG_INVALID_HANDLE)
}

KZ_INLINE void kzsVgDestroyPaint(KzsVgPaint paint)
{
KZS_OPENVG_CALL_BEGIN
    vgDestroyPaint(paint);
    kzsVgErrorTest();
KZS_OPENVG_CALL_END
}

KZ_INLINE void kzsVgSetPaint(KzsVgPaint paint, kzUint paintMode)
{
KZS_OPENVG_CALL_BEGIN
    vgSetPaint(paint, paintMode);
    kzsVgErrorTest();
KZS_OPENVG_CALL_END
}

KZ_INLINE KzsVgPaint kzsVgGetPaint(KzsVgPaintMode paintModes)
{
KZS_OPENVG_CALL_BEGIN
    return vgGetPaint(paintModes);
KZS_OPENVG_CALL_END_RETURN_VALUE(KZS_VG_INVALID_HANDLE)
}

KZ_INLINE void kzsVgSetColor(KzsVgPaint paint, kzUint rgba)
{
KZS_OPENVG_CALL_BEGIN
    vgSetColor(paint, rgba);
    kzsVgErrorTest();
KZS_OPENVG_CALL_END
}

KZ_INLINE kzUint kzsVgGetColor(KzsVgPaint paint)
{
KZS_OPENVG_CALL_BEGIN
    return vgGetColor(paint);
KZS_OPENVG_CALL_END_RETURN_VALUE(0)
}

KZ_INLINE void kzsVgPaintPattern(KzsVgPaint paint, KzsVgImage pattern)
{
KZS_OPENVG_CALL_BEGIN
    vgPaintPattern(paint, pattern);
    kzsVgErrorTest();
KZS_OPENVG_CALL_END
}

/* Images */

KZ_INLINE KzsVgImage kzsVgCreateImage(KzsVgImageFormat fmt, kzInt width, kzInt height, kzUint quality)
{
KZS_OPENVG_CALL_BEGIN
    return vgCreateImage(fmt, width, height, quality);
KZS_OPENVG_CALL_END_RETURN_VALUE(KZS_VG_INVALID_HANDLE)
}

KZ_INLINE void kzsVgDestroyImage(KzsVgImage image)
{
KZS_OPENVG_CALL_BEGIN
    vgDestroyImage(image);
    kzsVgErrorTest();
KZS_OPENVG_CALL_END
}

KZ_INLINE void kzsVgClearImage(KzsVgImage image, kzInt x, kzInt y, kzInt width, kzInt height)
{
KZS_OPENVG_CALL_BEGIN
    vgClearImage(image, x, y, width, height);
    kzsVgErrorTest();
KZS_OPENVG_CALL_END
}

KZ_INLINE void kzsVgImageSubData(KzsVgImage image, const void* data, kzInt dataStride, KzsVgImageFormat fmt,
                                 kzInt x, kzInt y, kzInt width, kzInt height)
{
KZS_OPENVG_CALL_BEGIN
    vgImageSubData(image, data, dataStride, fmt, x, y, width, height);
    kzsVgErrorTest();
KZS_OPENVG_CALL_END
}

KZ_INLINE void kzsVgGetImageSubData(KzsVgImage image, void* data, kzInt dataStride, KzsVgImageFormat fmt,
                                    kzInt x, kzInt y, kzInt width, kzInt height)
{
KZS_OPENVG_CALL_BEGIN
    vgGetImageSubData(image, data, dataStride, fmt, x, y, width, height);
    kzsVgErrorTest();
KZS_OPENVG_CALL_END
}

KZ_INLINE KzsVgImage kzsVgChildImage(KzsVgImage parent, kzInt x, kzInt y, kzInt width, kzInt height)
{
KZS_OPENVG_CALL_BEGIN
    return vgChildImage(parent, x, y, width, height);
KZS_OPENVG_CALL_END_RETURN_VALUE(KZS_VG_INVALID_HANDLE)
}

KZ_INLINE KzsVgImage kzsVgGetParent(KzsVgImage image)
{
KZS_OPENVG_CALL_BEGIN
    return vgGetParent(image);
KZS_OPENVG_CALL_END_RETURN_VALUE(image)
}

KZ_INLINE void kzsVgCopyImage(KzsVgImage dst, kzInt dx, kzInt dy, KzsVgImage src, kzInt sx, kzInt sy,
                              kzInt width, kzInt height, kzBool dither)
{
KZS_OPENVG_CALL_BEGIN
    vgCopyImage(dst, dx, dy, src, sx, sy, width, height, kzsGetVGBoolean_private(dither));
    kzsVgErrorTest();
KZS_OPENVG_CALL_END
}

KZ_INLINE void kzsVgDrawImage(KzsVgImage image)
{
KZS_OPENVG_CALL_BEGIN
    vgDrawImage(image);
    kzsVgErrorTest();
KZS_OPENVG_CALL_END
}

KZ_INLINE void kzsVgSetPixels(kzInt dx, kzInt dy, KzsVgImage src, kzInt sx, kzInt sy, kzInt width, kzInt height)
{
KZS_OPENVG_CALL_BEGIN
    vgSetPixels(dx, dy, src, sx, sy, width, height);
    kzsVgErrorTest();
KZS_OPENVG_CALL_END
}

KZ_INLINE void kzsVgWritePixels(const void* data, kzInt dataStride, KzsVgImageFormat fmt,
                                kzInt dx, kzInt dy, kzInt width, kzInt height)
{
KZS_OPENVG_CALL_BEGIN
    vgWritePixels(data, dataStride, fmt, dx, dy, width, height);
    kzsVgErrorTest();
KZS_OPENVG_CALL_END
}

KZ_INLINE void kzsVgGetPixels(KzsVgImage dst, kzInt dx, kzInt dy, kzInt sx, kzInt sy, kzInt width, kzInt height)
{
KZS_OPENVG_CALL_BEGIN
    vgGetPixels(dst, dx, dy, sx, sy, width, height);
    kzsVgErrorTest();
KZS_OPENVG_CALL_END
}

KZ_INLINE void kzsVgReadPixels(void* data, kzInt dataStride, KzsVgImageFormat fmt,
                               kzInt dx, kzInt dy, kzInt width, kzInt height)
{
KZS_OPENVG_CALL_BEGIN
    vgReadPixels(data, dataStride, fmt, dx, dy, width, height);
    kzsVgErrorTest();
KZS_OPENVG_CALL_END
}

KZ_INLINE void kzsVgCopyPixels(kzInt dx, kzInt dy, kzInt sx, kzInt sy, kzInt width, kzInt height)
{
KZS_OPENVG_CALL_BEGIN
    vgCopyPixels(dx, dy, sx, sy, width, height);
    kzsVgErrorTest();
KZS_OPENVG_CALL_END
}

/* Text and Font Operations */

KZ_INLINE KzsVgFont kzsVgCreateFont(kzInt gluphCapacityHint)
{
KZS_OPENVG_CALL_BEGIN
    return vgCreateFont(gluphCapacityHint);
KZS_OPENVG_CALL_END_RETURN_VALUE(KZS_VG_INVALID_HANDLE)
}

KZ_INLINE void kzsVgDestroyFont(KzsVgFont font)
{
KZS_OPENVG_CALL_BEGIN
    vgDestroyFont(font);
    kzsVgErrorTest();
KZS_OPENVG_CALL_END
}

KZ_INLINE void kzsVgSetGlyphToPath(KzsVgFont font, kzUint glyphIndex, KzsVgPath path, kzBool inHinted,
                                   const kzFloat origin[2], const kzFloat escape[2])
{
KZS_OPENVG_CALL_BEGIN
    vgSetGlyphToPath(font, glyphIndex, path, kzsGetVGBoolean_private(inHinted), (VGfloat*)origin, (VGfloat*)escape); /* Reference implementation is not const-correct. */
    kzsVgErrorTest();
KZS_OPENVG_CALL_END
}

KZ_INLINE void kzsVgSetGlyphToImage(KzsVgFont font, kzUint glyphIndex, KzsVgImage image,
                                    const kzFloat origin[2], const kzFloat escape[2])
{
KZS_OPENVG_CALL_BEGIN
    vgSetGlyphToImage(font, glyphIndex, image, (VGfloat*)origin, (VGfloat*)escape); /* Reference implementation is not const-correct. */
    kzsVgErrorTest();
KZS_OPENVG_CALL_END
}

KZ_INLINE void kzsVgClearGlyph(KzsVgFont font, kzUint glyphIndex)
{
KZS_OPENVG_CALL_BEGIN
    vgClearGlyph(font, glyphIndex);
    kzsVgErrorTest();
KZS_OPENVG_CALL_END
}

KZ_INLINE void kzsVgDrawGlyph(KzsVgFont font, kzUint glyphIndex, kzUint paintModes, kzBool allowAutoHinting)
{
KZS_OPENVG_CALL_BEGIN
    vgDrawGlyph(font, glyphIndex, paintModes, kzsGetVGBoolean_private(allowAutoHinting));
    kzsVgErrorTest();
KZS_OPENVG_CALL_END
}

KZ_INLINE void kzsVgDrawGlyphs(KzsVgFont font, kzUint glyphCount, const kzUint* glyphIndices,
                               const kzFloat* adjustments_x, const kzFloat* adjustments_y,
                               kzUint paintModes, kzBool allowAutoHinting)
{
KZS_OPENVG_CALL_BEGIN
    vgDrawGlyphs(font, (VGint)glyphCount, (VGuint*)glyphIndices,               /* Reference implementation is not const-correct. */
                (VGfloat*)adjustments_x, (VGfloat*)adjustments_y,
                paintModes, kzsGetVGBoolean_private(allowAutoHinting));
    kzsVgErrorTest();
KZS_OPENVG_CALL_END
}

/* Image Filter */

KZ_INLINE void kzsVgColorMatrix(KzsVgImage dst, KzsVgImage src, const kzFloat* matrix)
{
KZS_OPENVG_CALL_BEGIN
    vgColorMatrix(dst, src, matrix);
    kzsVgErrorTest();
KZS_OPENVG_CALL_END
}

KZ_INLINE void kzsVgConvolve(KzsVgImage dst, KzsVgImage src, kzInt kernelW, kzInt kernelH,
                             kzInt shiftX, kzInt shiftY, const kzS16* kernel,
                             kzFloat scale, kzFloat bias, KzsVgTilingMode tilingMode)
{
KZS_OPENVG_CALL_BEGIN
    kzsAssert(sizeof(kzS16) == sizeof(VGshort));
    vgConvolve(dst, src, kernelW, kernelH, shiftX, shiftY, (VGshort*)kernel, scale, bias, tilingMode);
    kzsVgErrorTest();
KZS_OPENVG_CALL_END
}

KZ_INLINE void kzsVgSeparableConvolve(KzsVgImage dst, KzsVgImage src, kzInt kernelW, kzInt kernelH,
                                      kzInt shiftX, kzInt shiftY, const kzS16* kernelX, const kzS16* kernelY,
                                      kzFloat scale, kzFloat bias, KzsVgTilingMode tilingMode)
{
KZS_OPENVG_CALL_BEGIN
    kzsAssert(sizeof(kzS16) == sizeof(VGshort));
    vgSeparableConvolve(dst, src, kernelW, kernelH, shiftX, shiftY, (VGshort*)kernelX, (VGshort*)kernelY, scale, bias, tilingMode);
    kzsVgErrorTest();
KZS_OPENVG_CALL_END
}

KZ_INLINE void kzsVgGaussianBlur(KzsVgImage dst, KzsVgImage src, kzFloat stdDevX, kzFloat stdDevY, KzsVgTilingMode tilingMode)
{
KZS_OPENVG_CALL_BEGIN
    vgGaussianBlur(dst, src, stdDevX, stdDevY, tilingMode);
    kzsVgErrorTest();
KZS_OPENVG_CALL_END
}

KZ_INLINE void kzsVgLookup(KzsVgImage dst, KzsVgImage src,
                           const kzByte* redLUT, const kzByte* greenLUT, const kzByte* blueLUT, const kzByte* alphaLUT,
                           kzBool outputLinear, kzBool outputPremultiplied)
{
KZS_OPENVG_CALL_BEGIN
    vgLookup(dst, src, redLUT, greenLUT, blueLUT, alphaLUT,
             kzsGetVGBoolean_private(outputLinear),
             kzsGetVGBoolean_private(outputPremultiplied));
    kzsVgErrorTest();
KZS_OPENVG_CALL_END
}

KZ_INLINE void kzsVgLookupSingle(KzsVgImage dst, KzsVgImage src,
                                 const kzUint* LUT, KzsVgImageChannel sourceChannel,
                                 kzBool outputLinear, kzBool outputPremultiplied)
{
KZS_OPENVG_CALL_BEGIN
    vgLookupSingle(dst, src, LUT, sourceChannel,
                   kzsGetVGBoolean_private(outputLinear),
                   kzsGetVGBoolean_private(outputPremultiplied));
    kzsVgErrorTest();
KZS_OPENVG_CALL_END
}

/* Querying Hardware Capabilities */

KZ_INLINE KzsVgHardwareQueryResult kzsVgHardwareQuery(KzsVgHardwareQueryType key, kzInt setting)
{
KZS_OPENVG_CALL_BEGIN
    return vgHardwareQuery(key, setting);
KZS_OPENVG_CALL_END_RETURN_VALUE(KZS_VG_HARDWARE_UNACCELERATED)
}

/* Querying Strings */

KZ_INLINE kzString kzsVgGetString(KzsVgStringID name)
{
KZS_OPENVG_CALL_BEGIN
    return (kzString)vgGetString(name);
KZS_OPENVG_CALL_END_RETURN_VALUE(KZ_NULL)
}


KZ_HEADER_END


#endif
