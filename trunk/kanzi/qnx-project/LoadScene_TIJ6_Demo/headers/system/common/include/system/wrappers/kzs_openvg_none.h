/**
* \file
* OpenVG none wrapper.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZS_OPENVG_NONE_H
#define KZS_OPENVG_NONE_H


#include "kzs_openvg_base.h"

#include <system/debug/kzs_error.h>
#include <system/kzs_types.h>

#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Number Representations */
#define KZS_VG_MAXSHORT                                0x7FFF
#define KZS_VG_MAXINT                                  0x7FFFFFFF

/* Handle-based Data Types */
typedef kzUint                                         KzsVgHandle;
typedef kzUint                                         KzsVgFont;
typedef kzUint                                         KzsVgImage;
typedef kzUint                                         KzsVgMaskLayer;
typedef kzUint                                         KzsVgPaint;
typedef kzUint                                         KzsVgPath;

#define KZS_VG_INVALID_HANDLE                          ((kzUint)0)

/* Boolean */
#define KZS_VG_TRUE                                    1
#define KZS_VG_FALSE                                   0

/* Errors */
#define KZS_VG_NO_ERROR                                0
#define KZS_VG_BAD_HANDLE_ERROR                        0x1000
#define KZS_VG_ILLEGAL_ARGUMENT_ERROR                  0x1001
#define KZS_VG_OUT_OF_MEMORY_ERROR                     0x1002
#define KZS_VG_PATH_CAPABILITY_ERROR                   0x1003
#define KZS_VG_UNSUPPORTED_IMAGE_FORMAT_ERROR          0x1004
#define KZS_VG_UNSUPPORTED_PATH_FORMAT_ERROR           0x1005
#define KZS_VG_IMAGE_IN_USE_ERROR                      0x1006
#define KZS_VG_NO_CONTEXT_ERROR                        0x1007

/* Context Parameters*/
typedef kzInt                                          KzsVgParamType;

#define KZS_VG_MATRIX_MODE                             0x1100

#define KZS_VG_MATRIX_PATH_USER_TO_SURFACE             0x1400
#define KZS_VG_MATRIX_IMAGE_USER_TO_SURFACE            0x1401
#define KZS_VG_MATRIX_FILL_PAINT_TO_USER               0x1402
#define KZS_VG_MATRIX_STROKE_PAINT_TO_USER             0x1403
#define KZS_VG_MATRIX_GLYPH_USER_TO_SURFACE            0x1404

#define KZS_VG_FILL_RULE                               0x1101

#define KZS_VG_EVEN_ODD                                0x1900
#define KZS_VG_NON_ZERO                                0x1901

#define KZS_VG_IMAGE_QUALITY                           0x1102

#define KZS_VG_IMAGE_QUALITY_NONANTIALIASED            (1 << 0)
#define KZS_VG_IMAGE_QUALITY_FASTER                    (1 << 1)
#define KZS_VG_IMAGE_QUALITY_BETTER                    (1 << 2)

#define KZS_VG_RENDERING_QUALITY                       0x1103

#define KZS_VG_RENDERING_QUALITY_NONANTIALIASED        0x1200
#define KZS_VG_RENDERING_QUALITY_FASTER                0x1201
#define KZS_VG_RENDERING_QUALITY_BETTER                0x1202

#define KZS_VG_BLEND_MODE                              0x1104

#define KZS_VG_BLEND_SRC                               0x2000
#define KZS_VG_BLEND_SRC_OVER                          0x2001
#define KZS_VG_BLEND_DST_OVER                          0x2002
#define KZS_VG_BLEND_SRC_IN                            0x2003
#define KZS_VG_BLEND_DST_IN                            0x2004
#define KZS_VG_BLEND_MULTIPLY                          0x2005
#define KZS_VG_BLEND_SCREEN                            0x2006
#define KZS_VG_BLEND_DARKEN                            0x2007
#define KZS_VG_BLEND_LIGHTEN                           0x2008
#define KZS_VG_BLEND_ADDITIVE                          0x2009

#define KZS_VG_IMAGE_MODE                              0x1105

#define KZS_VG_DRAW_IMAGE_NORMAL                       0x1F00
#define KZS_VG_DRAW_IMAGE_MULTIPLY                     0x1F01
#define KZS_VG_DRAW_IMAGE_STENCIL                      0x1F02

#define KZS_VG_SCISSOR_RECTS                           0x1106

#define KZS_VG_COLOR_TRANSFORM                         0x1170

#define KZS_VG_COLOR_TRANSFORM_VALUES                  0x1171

#define KZS_VG_STROKE_LINE_WIDTH                       0x1110

#define KZS_VG_STROKE_CAP_STYLE                        0x1111

#define KZS_VG_CAP_BUTT                                0x1700
#define KZS_VG_CAP_ROUND                               0x1701
#define KZS_VG_CAP_SQUARE                              0x1702

#define KZS_VG_STROKE_JOIN_STYLE                       0x1112

#define KZS_VG_JOIN_MITER                              0x1800
#define KZS_VG_JOIN_ROUND                              0x1801
#define KZS_VG_JOIN_BEVEL                              0x1802

#define KZS_VG_STROKE_MITER_LIMIT                      0x1113

#define KZS_VG_STROKE_DASH_PATTERN                     0x1114

#define KZS_VG_STROKE_DASH_PHASE                       0x1115

#define KZS_VG_STROKE_DASH_PHASE_RESET                 0x1116

#define KZS_VG_TILE_FILL_COLOR                         0x1120

#define KZS_VG_CLEAR_COLOR                             0x1121

#define KZS_VG_GLYPH_ORIGIN                            0x1122

#define KZS_VG_MASKING                                 0x1130

#define KZS_VG_SCISSORING                              0x1131

#define KZS_VG_SCREEN_LAYOUT                           0x1141

#define KZS_VG_PIXEL_LAYOUT                            0x1140

#define KZS_VG_PIXEL_LAYOUT_UNKNOWN                    0x1300
#define KZS_VG_PIXEL_LAYOUT_RGB_VERTICAL               0x1301
#define KZS_VG_PIXEL_LAYOUT_BGR_VERTICAL               0x1302
#define KZS_VG_PIXEL_LAYOUT_RGB_HORIZONTAL             0x1303
#define KZS_VG_PIXEL_LAYOUT_BGR_HORIZONTAL             0x1304

#define KZS_VG_FILTER_FORMAT_LINEAR                    0x1150

#define KZS_VG_FILTER_FORMAT_PREMULTIPLIED             0x1151

#define KZS_VG_FILTER_CHANNEL_MASK                     0x1152

#define KZS_VG_RED                                     (1 << 3)
#define KZS_VG_GREEN                                   (1 << 2)
#define KZS_VG_BLUE                                    (1 << 1)
#define KZS_VG_ALPHA                                   (1 << 0)

/* Read-only Context Parameters*/
#define KZS_VG_MAX_SCISSOR_RECTS                       0x1160
#define KZS_VG_MAX_DASH_COUNT                          0x1161
#define KZS_VG_MAX_KERNEL_SIZE                         0x1162
#define KZS_VG_MAX_SEPARABLE_KERNEL_SIZE               0x1163
#define KZS_VG_MAX_COLOR_RAMP_STOPS                    0x1164
#define KZS_VG_MAX_IMAGE_WIDTH                         0x1165
#define KZS_VG_MAX_IMAGE_HEIGHT                        0x1166
#define KZS_VG_MAX_IMAGE_PIXELS                        0x1167
#define KZS_VG_MAX_IMAGE_BYTES                         0x1168
#define KZS_VG_MAX_FLOAT                               0x1169
#define KZS_VG_MAX_GAUSSIAN_STD_DEVIATION              0x116A

/* Mask Operation */
typedef kzInt                                          KzsVgMaskOperation;

#define KZS_VG_CLEAR_MASK                              0x1500
#define KZS_VG_FILL_MASK                               0x1501
#define KZS_VG_SET_MASK                                0x1502
#define KZS_VG_UNION_MASK                              0x1503
#define KZS_VG_INTERSECT_MASK                          0x1504
#define KZS_VG_SUBTRACT_MASK                           0x1505

/* Segment Commands */
#define KZS_VG_CLOSE_PATH                              ( 0 << 1)
#define KZS_VG_MOVE_TO_ABS                             (( 1 << 1) | 0)
#define KZS_VG_LINE_TO_ABS                             (( 2 << 1) | 0)
#define KZS_VG_HLINE_TO_ABS                            (( 3 << 1) | 0)
#define KZS_VG_VLINE_TO_ABS                            (( 4 << 1) | 0)
#define KZS_VG_QUAD_TO_ABS                             (( 5 << 1) | 0)
#define KZS_VG_CUBIC_TO_ABS                            (( 6 << 1) | 0)
#define KZS_VG_SQUAD_TO_ABS                            (( 7 << 1) | 0)
#define KZS_VG_SCUBIC_TO_ABS                           (( 8 << 1) | 0)
#define KZS_VG_SCCWARC_TO_ABS                          (( 9 << 1) | 0)
#define KZS_VG_SCWARC_TO_ABS                           ((10 << 1) | 0)
#define KZS_VG_LCCWARC_TO_ABS                          ((11 << 1) | 0)
#define KZS_VG_LCWARC_TO_ABS                           ((12 << 1) | 0)
#define KZS_VG_MOVE_TO_REL                             (( 1 << 1) | 1)
#define KZS_VG_LINE_TO_REL                             (( 2 << 1) | 1)
#define KZS_VG_HLINE_TO_REL                            (( 3 << 1) | 1)
#define KZS_VG_VLINE_TO_REL                            (( 4 << 1) | 1)
#define KZS_VG_QUAD_TO_REL                             (( 5 << 1) | 1)
#define KZS_VG_CUBIC_TO_REL                            (( 6 << 1) | 1)
#define KZS_VG_SQUAD_TO_REL                            (( 7 << 1) | 1)
#define KZS_VG_SCUBIC_TO_REL                           (( 8 << 1) | 1)
#define KZS_VG_SCCWARC_TO_REL                          (( 9 << 1) | 1)
#define KZS_VG_SCWARC_TO_REL                           ((10 << 1) | 1)
#define KZS_VG_LCCWARC_TO_REL                          ((11 << 1) | 1)
#define KZS_VG_LCWARC_TO_REL                           ((12 << 1) | 1)

/* Path Operations */
#define KZS_VG_PATH_CAPABILITY_APPEND_FROM             (1 <<  0)
#define KZS_VG_PATH_CAPABILITY_APPEND_TO               (1 <<  1)
#define KZS_VG_PATH_CAPABILITY_MODIFY                  (1 <<  2)
#define KZS_VG_PATH_CAPABILITY_TRANSFORM_FROM          (1 <<  3)
#define KZS_VG_PATH_CAPABILITY_TRANSFORM_TO            (1 <<  4)
#define KZS_VG_PATH_CAPABILITY_INTERPOLATE_FROM        (1 <<  5)
#define KZS_VG_PATH_CAPABILITY_INTERPOLATE_TO          (1 <<  6)
#define KZS_VG_PATH_CAPABILITY_PATH_LENGTH             (1 <<  7)
#define KZS_VG_PATH_CAPABILITY_POINT_ALONG_PATH        (1 <<  8)
#define KZS_VG_PATH_CAPABILITY_TANGENT_ALONG_PATH      (1 <<  9)
#define KZS_VG_PATH_CAPABILITY_PATH_BOUNDS             (1 << 10)
#define KZS_VG_PATH_CAPABILITY_PATH_TRANSFORMED_BOUNDS (1 << 11)
#define KZS_VG_PATH_CAPABILITY_ALL                     ((1 << 12) - 1)

/* Path Object Parameter */
#define KZS_VG_PATH_FORMAT                             0x1600

#define KZS_VG_PATH_FORMAT_STANDARD                    0

typedef kzInt                                          KzsVgPathDatatype;

#define KZS_VG_PATH_DATATYPE                           0x1601

#define KZS_VG_PATH_DATATYPE_S_8                       0
#define KZS_VG_PATH_DATATYPE_S_16                      1
#define KZS_VG_PATH_DATATYPE_S_32                      2
#define KZS_VG_PATH_DATATYPE_F                         3

#define KZS_VG_PATH_SCALE                              0x1602

#define KZS_VG_PATH_BIAS                               0x1603

#define KZS_VG_PATH_NUM_SEGMENTS                       0x1604

#define KZS_VG_PATH_NUM_COORDS                         0x1605

/* Paint Modes */
typedef kzInt                                          KzsVgPaintMode;

#define KZS_VG_STROKE_PATH                             (1 << 0)
#define KZS_VG_FILL_PATH                               (1 << 1)

#define KZS_VG_PAINT_TYPE                              0x1A00

#define KZS_VG_PAINT_TYPE_COLOR                        0x1B00
#define KZS_VG_PAINT_TYPE_LINEAR_GRADIENT              0x1B01
#define KZS_VG_PAINT_TYPE_RADIAL_GRADIENT              0x1B02
#define KZS_VG_PAINT_TYPE_PATTERN                      0x1B03

#define KZS_VG_PAINT_COLOR                             0x1A01

#define KZS_VG_PAINT_COLOR_RAMP_SPREAD_MODE            0x1A02

#define KZS_VG_COLOR_RAMP_SPREAD_PAD                   0x1C00
#define KZS_VG_COLOR_RAMP_SPREAD_REPEAT                0x1C01
#define KZS_VG_COLOR_RAMP_SPREAD_REFLECT               0x1C02

#define KZS_VG_PAINT_COLOR_RAMP_PREMULTIPLIED          0x1A07

#define KZS_VG_PAINT_COLOR_RAMP_STOPS                  0x1A03

#define KZS_VG_PAINT_LINEAR_GRADIENT                   0x1A04

#define KZS_VG_PAINT_RADIAL_GRADIENT                   0x1A05

#define KZS_VG_PAINT_PATTERN_TILING_MODE               0x1A06

#define KZS_VG_TILE_FILL                               0x1D00
#define KZS_VG_TILE_PAD                                0x1D01
#define KZS_VG_TILE_REPEAT                             0x1D02
#define KZS_VG_TILE_REFLECT                            0x1D03

/* Image Object Parameter */
typedef kzInt                                          KzsVgImageFormat;

#define KZS_VG_IMAGE_FORMAT                            0x1E00

#define KZS_VG_sRGBX_8888                              0
#define KZS_VG_sRGBA_8888                              1
#define KZS_VG_sRGBA_8888_PRE                          2
#define KZS_VG_sRGB_565                                3
#define KZS_VG_sRGBA_5551                              4
#define KZS_VG_sRGBA_4444                              5
#define KZS_VG_sL_8                                    6
#define KZS_VG_lRGBX_8888                              7
#define KZS_VG_lRGBA_8888                              8
#define KZS_VG_lRGBA_8888_PRE                          9
#define KZS_VG_lL_8                                    10
#define KZS_VG_A_8                                     11
#define KZS_VG_BW_1                                    12
#define KZS_VG_A_1                                     13
#define KZS_VG_A_4                                     14

#define KZS_VG_sXRGB_8888                              (0 | (1 << 6))
#define KZS_VG_sARGB_8888                              (1 | (1 << 6))
#define KZS_VG_sARGB_8888_PRE                          (2 | (1 << 6))
#define KZS_VG_sARGB_1555                              (4 | (1 << 6))
#define KZS_VG_sARGB_4444                              (5 | (1 << 6))
#define KZS_VG_lXRGB_8888                              (7 | (1 << 6))
#define KZS_VG_lARGB_8888                              (8 | (1 << 6))
#define KZS_VG_lARGB_8888_PRE                          (9 | (1 << 6))

#define KZS_VG_sBGRX_8888                              (0 | (1 << 7))
#define KZS_VG_sBGRA_8888                              (1 | (1 << 7))
#define KZS_VG_sBGRA_8888_PRE                          (2 | (1 << 7))
#define KZS_VG_sBGR_565                                (3 | (1 << 7))
#define KZS_VG_sBGRA_5551                              (4 | (1 << 7))
#define KZS_VG_sBGRA_4444                              (5 | (1 << 7))
#define KZS_VG_lBGRX_8888                              (7 | (1 << 7))
#define KZS_VG_lBGRA_8888                              (8 | (1 << 7))
#define KZS_VG_lBGRA_8888_PRE                          (9 | (1 << 7))

#define KZS_VG_sXBGR_8888                              (0 | (1 << 6) | (1 << 7))
#define KZS_VG_sABGR_8888                              (1 | (1 << 6) | (1 << 7))
#define KZS_VG_sABGR_8888_PRE                          (2 | (1 << 6) | (1 << 7))
#define KZS_VG_sABGR_1555                              (4 | (1 << 6) | (1 << 7))
#define KZS_VG_sABGR_4444                              (5 | (1 << 6) | (1 << 7))
#define KZS_VG_lXBGR_8888                              (7 | (1 << 6) | (1 << 7))
#define KZS_VG_lABGR_8888                              (8 | (1 << 6) | (1 << 7))
#define KZS_VG_lABGR_8888_PRE                          (9 | (1 << 6) | (1 << 7))

#define KZS_VG_IMAGE_WIDTH                             0x1E01
#define KZS_VG_IMAGE_HEIGHT                            0x1E02

/* Font Object Parameter */
#define KZS_VG_FONT_NUM_GLYPHS                         0x2F00

/* Convolution */
typedef kzInt                                          KzsVgTilingMode;
typedef kzInt                                          KzsVgImageChannel;

/* Querying Hardware Capabilities */
typedef kzInt                                          KzsVgHardwareQueryResult;

#define KZS_VG_HARDWARE_ACCELERATED                    0x2200
#define KZS_VG_HARDWARE_UNACCELERATED                  0x2201

typedef kzInt                                          KzsVgHardwareQueryType;

#define KZS_VG_IMAGE_FORMAT_QUERY                      0x2100
#define KZS_VG_PATH_DATATYPE_QUERY                     0x2101

/* String IDs */
typedef kzInt                                          KzsVgStringID;

#define KZS_VG_VENDOR                                  0x2300
#define KZS_VG_RENDERER                                0x2301
#define KZS_VG_VERSION                                 0x2302
#define KZS_VG_EXTENSIONS                              0x2303


/* Object Parameter Set/Get API */

KZ_INLINE void kzsVgSetParameterf(KzsVgHandle obj, kzInt paramType, kzFloat val)
{
    KZS_NOT_IMPLEMENTED_YET;
}

KZ_INLINE void kzsVgSetParameteri(KzsVgHandle obj, kzInt paramType, kzInt val)
{
    KZS_NOT_IMPLEMENTED_YET;
}

KZ_INLINE void kzsVgSetParameterfv(KzsVgHandle obj, kzInt paramType, kzInt cnt, const kzFloat* val)
{
    KZS_NOT_IMPLEMENTED_YET;
}

KZ_INLINE void kzsVgSetParameteriv(KzsVgHandle obj, kzInt paramType, kzInt cnt, const kzInt* val)
{
    KZS_NOT_IMPLEMENTED_YET;
}

KZ_INLINE kzFloat kzsVgGetParameterf(KzsVgHandle obj, kzInt paramType)
{
    KZS_NOT_IMPLEMENTED_YET;
    return 0.0f;
}

KZ_INLINE kzInt kzsVgGetParameteri(KzsVgHandle obj, kzInt paramType)
{
    KZS_NOT_IMPLEMENTED_YET;
    return 0;
}

KZ_INLINE kzInt kzsVgGetParameterVectorSize(KzsVgHandle obj, kzInt paramType)
{
    KZS_NOT_IMPLEMENTED_YET;
    return 0;
}

KZ_INLINE void kzsVgGetParameterfv(KzsVgHandle obj, kzInt paramType, kzInt cnt, kzFloat* val)
{
    KZS_NOT_IMPLEMENTED_YET;
}

KZ_INLINE void kzsVgGetParameteriv(KzsVgHandle obj, kzInt paramType, kzInt cnt, kzInt* val)
{
    KZS_NOT_IMPLEMENTED_YET;
}

/* Forcing Drawing to Complete API */

KZ_INLINE void kzsVgFlush(void)
{
    KZS_NOT_IMPLEMENTED_YET;
}

KZ_INLINE void kzsVgFinish(void)
{
    KZS_NOT_IMPLEMENTED_YET;
}

/* Context Parameter Set/Get API */

KZ_INLINE void kzsVgSetf(KzsVgParamType paramType, kzFloat val)
{
    KZS_NOT_IMPLEMENTED_YET;
}

KZ_INLINE void kzsVgSeti(KzsVgParamType paramType, kzInt val)
{
    KZS_NOT_IMPLEMENTED_YET;
}

KZ_INLINE void kzsVgSetfv(KzsVgParamType paramType, kzInt cnt, const kzFloat* val)
{
    KZS_NOT_IMPLEMENTED_YET;
}

KZ_INLINE void kzsVgSetiv(KzsVgParamType paramType, kzInt cnt, const kzInt* val)
{
    KZS_NOT_IMPLEMENTED_YET;
}

KZ_INLINE kzFloat kzsVgGetf(KzsVgParamType paramType)
{
    KZS_NOT_IMPLEMENTED_YET;
    return 0.0f;
}

KZ_INLINE kzInt kzsVgGeti(KzsVgParamType paramType)
{
    KZS_NOT_IMPLEMENTED_YET;
    return 0;
}

KZ_INLINE kzInt kzsVgGetVectorSize(KzsVgParamType paramType)
{
    KZS_NOT_IMPLEMENTED_YET;
    return 0;
}

KZ_INLINE void kzsVgGetfv(KzsVgParamType paramType, kzInt cnt, kzFloat* val)
{
    KZS_NOT_IMPLEMENTED_YET;
}

KZ_INLINE void kzsVgGetiv(KzsVgParamType paramType, kzInt cnt, kzInt* val)
{
    KZS_NOT_IMPLEMENTED_YET;
}

/* Matrix Transformation */

KZ_INLINE void kzsVgLoadIdentity(void)
{
    KZS_NOT_IMPLEMENTED_YET;
}

KZ_INLINE void kzsVgLoadMatrix(const kzFloat* m)
{
    KZS_NOT_IMPLEMENTED_YET;
}

KZ_INLINE void kzsVgMultMatrix(const kzFloat* m)
{
    KZS_NOT_IMPLEMENTED_YET;
}

KZ_INLINE void kzsVgGetMatrix(kzFloat* m)
{
    KZS_NOT_IMPLEMENTED_YET;
}

KZ_INLINE void kzsVgTranslate(kzFloat tx, kzFloat ty)
{
    KZS_NOT_IMPLEMENTED_YET;
}

KZ_INLINE void kzsVgScale(kzFloat sx, kzFloat sy)
{
    KZS_NOT_IMPLEMENTED_YET;
}

KZ_INLINE void kzsVgShear(kzFloat shx, kzFloat shy)
{
    KZS_NOT_IMPLEMENTED_YET;
}

KZ_INLINE void kzsVgRotate(kzFloat angle)
{
    KZS_NOT_IMPLEMENTED_YET;
}

/* Masking */

KZ_INLINE void kzsVgMask(KzsVgHandle mask, KzsVgMaskOperation op, kzInt x, kzInt y, kzInt width, kzInt height)
{
    KZS_NOT_IMPLEMENTED_YET;
}

KZ_INLINE void kzsVgRenderToMask(KzsVgPath path, kzUint paintMode, KzsVgMaskOperation op)
{
    KZS_NOT_IMPLEMENTED_YET;
}

KZ_INLINE KzsVgMaskLayer kzsVgCreateMaskLayer(kzInt width, kzInt height)
{
    KZS_NOT_IMPLEMENTED_YET;
    return KZS_VG_INVALID_HANDLE;
}

KZ_INLINE void kzsVgDestroyMaskLayer(KzsVgMaskLayer masklayer)
{
    KZS_NOT_IMPLEMENTED_YET;
}

KZ_INLINE void kzsVgFillMaskLayer(KzsVgMaskLayer masklayer, kzInt x, kzInt y,
    kzInt width, kzInt height, kzFloat val)
{
    KZS_NOT_IMPLEMENTED_YET;
}

KZ_INLINE void kzsVgCopyMask(KzsVgMaskLayer masklayer, kzInt x, kzInt y, kzInt sx, kzInt sy,
    kzInt width, kzInt height)
{
    KZS_NOT_IMPLEMENTED_YET;
}

/* Fast Clear */

KZ_INLINE void kzsVgClear(kzInt x, kzInt y, kzInt width, kzInt height)
{
    KZS_NOT_IMPLEMENTED_YET;
}

/* Path */

KZ_INLINE KzsVgPath kzsVgCreatePath(kzInt pathFormat, KzsVgPathDatatype datatype, kzFloat scale, kzFloat bias,
    kzInt segCapacityHint, kzInt coordCapacityHint, kzUint capabilities)
{
    KZS_NOT_IMPLEMENTED_YET;
    return KZS_VG_INVALID_HANDLE;
}

KZ_INLINE void kzsVgClearPath(KzsVgPath path, kzUint capabilities)
{
    KZS_NOT_IMPLEMENTED_YET;
}

KZ_INLINE void kzsVgDestroyPath(KzsVgPath path)
{
    KZS_NOT_IMPLEMENTED_YET;
}

KZ_INLINE kzUint kzsVgGetPathCapabilities(KzsVgPath path)
{
    KZS_NOT_IMPLEMENTED_YET;
    return 0;
}

KZ_INLINE void kzsVgRemovePathCapabilities(KzsVgPath path, kzUint capabilities)
{
    KZS_NOT_IMPLEMENTED_YET;
}

KZ_INLINE void kzsVgAppendPath(KzsVgPath dstPath, KzsVgPath srcPath)
{
    KZS_NOT_IMPLEMENTED_YET;
}

KZ_INLINE void kzsVgAppendPathData(KzsVgPath dstPath, kzInt numSeg, const kzByte* pathSeg, const void* pathData)
{
    KZS_NOT_IMPLEMENTED_YET;
}

KZ_INLINE void kzsVgModifyPathCoords(KzsVgPath dstPath, kzInt startIdx, kzInt numSeg, const void* pathData)
{
    KZS_NOT_IMPLEMENTED_YET;
}

KZ_INLINE void kzsVgTransformPath(KzsVgPath dstPath, KzsVgPath srcPath)
{
    KZS_NOT_IMPLEMENTED_YET;
}

KZ_INLINE kzBool kzsVgInterpolatePath(KzsVgPath dstPath, KzsVgPath startPath, KzsVgPath endPath, kzFloat amount)
{
    KZS_NOT_IMPLEMENTED_YET;
    return KZ_FALSE;
}

KZ_INLINE kzFloat kzsVgPathLength(KzsVgPath path, kzInt startSeg, kzInt numSeg)
{
    KZS_NOT_IMPLEMENTED_YET;
    return -1.0f;
}

KZ_INLINE void kzsVgPointAlongPath(KzsVgPath dstPath, kzInt startSeg, kzInt numSeg, kzFloat distance, kzFloat* out_x, kzFloat* out_y, kzFloat* out_tanX, kzFloat* out_tanY)
{
    KZS_NOT_IMPLEMENTED_YET;
}

KZ_INLINE void kzsVgPathBounds(KzsVgPath dstPath, kzFloat* out_minx, kzFloat* out_miny, kzFloat* out_width, kzFloat* out_height)
{
    KZS_NOT_IMPLEMENTED_YET;
}

KZ_INLINE void kzsVgPathTransformedBounds(KzsVgPath dstPath, kzFloat* out_minx, kzFloat* out_miny, kzFloat* out_width, kzFloat* out_height)
{
    KZS_NOT_IMPLEMENTED_YET;
}

KZ_INLINE void kzsVgDrawPath(KzsVgPath path, kzUint paintModes)
{
    KZS_NOT_IMPLEMENTED_YET;
}

/* Paint */

KZ_INLINE KzsVgPaint kzsVgCreatePaint(void)
{
    KZS_NOT_IMPLEMENTED_YET;
    return KZS_VG_INVALID_HANDLE;
}

KZ_INLINE void kzsVgDestroyPaint(KzsVgPaint paint)
{
    KZS_NOT_IMPLEMENTED_YET;
}

KZ_INLINE void kzsVgSetPaint(KzsVgPaint paint, kzUint paintMode)
{
    KZS_NOT_IMPLEMENTED_YET;
}

KZ_INLINE KzsVgPaint kzsVgGetPaint(KzsVgPaintMode paintModes)
{
    KZS_NOT_IMPLEMENTED_YET;
    return KZS_VG_INVALID_HANDLE;
}

KZ_INLINE void kzsVgSetColor(KzsVgPaint paint, kzUint rgba)
{
    KZS_NOT_IMPLEMENTED_YET;
}

KZ_INLINE kzUint kzsVgGetColor(KzsVgPaint paint)
{
    KZS_NOT_IMPLEMENTED_YET;
    return 0;
}

KZ_INLINE void kzsVgPaintPattern(KzsVgPaint paint, KzsVgImage pattern)
{
    KZS_NOT_IMPLEMENTED_YET;
}

/* Images */

KZ_INLINE KzsVgImage kzsVgCreateImage(KzsVgImageFormat fmt, kzInt width, kzInt height, kzUint quality)
{
    KZS_NOT_IMPLEMENTED_YET;
    return KZS_VG_INVALID_HANDLE;
}

KZ_INLINE void kzsVgDestroyImage(KzsVgImage image)
{
    KZS_NOT_IMPLEMENTED_YET;
}

KZ_INLINE void kzsVgClearImage(KzsVgImage image, kzInt x, kzInt y, kzInt width, kzInt height)
{
    KZS_NOT_IMPLEMENTED_YET;
}

KZ_INLINE void kzsVgImageSubData(KzsVgImage image, const void* data, kzInt dataStride, KzsVgImageFormat fmt,
    kzInt x, kzInt y, kzInt width, kzInt height)
{
    KZS_NOT_IMPLEMENTED_YET;
}

KZ_INLINE void kzsVgGetImageSubData(KzsVgImage image, void* data, kzInt dataStride, KzsVgImageFormat fmt,
    kzInt x, kzInt y, kzInt width, kzInt height)
{
    KZS_NOT_IMPLEMENTED_YET;
}

KZ_INLINE KzsVgImage kzsVgChildImage(KzsVgImage parent, kzInt x, kzInt y, kzInt width, kzInt height)
{
    KZS_NOT_IMPLEMENTED_YET;
    return KZS_VG_INVALID_HANDLE;
}

KZ_INLINE KzsVgImage kzsVgGetParent(KzsVgImage image)
{
    KZS_NOT_IMPLEMENTED_YET;
    return image;
}

KZ_INLINE void kzsVgCopyImage(KzsVgImage dst, kzInt dx, kzInt dy, KzsVgImage src, kzInt sx, kzInt sy,
    kzInt width, kzInt height, kzBool dither)
{
    KZS_NOT_IMPLEMENTED_YET;
}

KZ_INLINE void kzsVgDrawImage(KzsVgImage image)
{
    KZS_NOT_IMPLEMENTED_YET;
}

KZ_INLINE void kzsVgSetPixels(kzInt dx, kzInt dy, KzsVgImage src, kzInt sx, kzInt sy, kzInt width, kzInt height)
{
    KZS_NOT_IMPLEMENTED_YET;
}

KZ_INLINE void kzsVgWritePixels(const void* data, kzInt dataStride, KzsVgImageFormat fmt,
    kzInt dx, kzInt dy, kzInt width, kzInt height)
{
    KZS_NOT_IMPLEMENTED_YET;
}

KZ_INLINE void kzsVgGetPixels(KzsVgImage dst, kzInt dx, kzInt dy, kzInt sx, kzInt sy, kzInt width, kzInt height)
{
    KZS_NOT_IMPLEMENTED_YET;
}

KZ_INLINE void kzsVgReadPixels(void* data, kzInt dataStride, KzsVgImageFormat fmt,
    kzInt dx, kzInt dy, kzInt width, kzInt height)
{
    KZS_NOT_IMPLEMENTED_YET;
}

KZ_INLINE void kzsVgCopyPixels(kzInt dx, kzInt dy, kzInt sx, kzInt sy, kzInt width, kzInt height)
{
    KZS_NOT_IMPLEMENTED_YET;
}

/* Text and Font Operations */

KZ_INLINE KzsVgFont kzsVgCreateFont(kzInt gluphCapacityHint)
{
    KZS_NOT_IMPLEMENTED_YET;
    return KZS_VG_INVALID_HANDLE;
}

KZ_INLINE void kzsVgDestroyFont(KzsVgFont font)
{
    KZS_NOT_IMPLEMENTED_YET;
}

KZ_INLINE void kzsVgSetGlyphToPath(KzsVgFont font, kzUint glyphIndex, KzsVgPath path, kzBool inHinted,
    const kzFloat origin[2], const kzFloat escape[2])
{
    KZS_NOT_IMPLEMENTED_YET;
}

KZ_INLINE void kzsVgSetGlyphToImage(KzsVgFont font, kzUint glyphIndex, KzsVgImage image,
    const kzFloat origin[2], const kzFloat escape[2])
{
    KZS_NOT_IMPLEMENTED_YET;
}

KZ_INLINE void kzsVgClearGlyph(KzsVgFont font, kzUint glyphIndex)
{
    KZS_NOT_IMPLEMENTED_YET;
}

KZ_INLINE void kzsVgDrawGlyph(KzsVgFont font, kzUint glyphIndex, kzUint paintModes, kzBool allowAutoHinting)
{
    KZS_NOT_IMPLEMENTED_YET;
}

KZ_INLINE void kzsVgDrawGlyphs(KzsVgFont font, kzUint glyphCount, const kzUint* glyphIndices,
                               const kzFloat* adjustments_x, const kzFloat* adjustments_y,
                               kzUint paintModes, kzBool allowAutoHinting)
{
    KZS_NOT_IMPLEMENTED_YET;
}

/* Image Filter */

KZ_INLINE void kzsVgColorMatrix(KzsVgImage dst, KzsVgImage src, const kzFloat* matrix)
{
    KZS_NOT_IMPLEMENTED_YET;
}

KZ_INLINE void kzsVgConvolve(KzsVgImage dst, KzsVgImage src, kzInt kernelW, kzInt kernelH,
                             kzInt shiftX, kzInt shiftY, const kzS16* kernel,
                             kzFloat scale, kzFloat bias, KzsVgTilingMode tilingMode)
{
    KZS_NOT_IMPLEMENTED_YET;
}

KZ_INLINE void kzsVgSeparableConvolve(KzsVgImage dst, KzsVgImage src, kzInt kernelW, kzInt kernelH,
                                      kzInt shiftX, kzInt shiftY, const kzS16* kernelX, const kzS16* kernelY,
                                      kzFloat scale, kzFloat bias, KzsVgTilingMode tilingMode)
{
    KZS_NOT_IMPLEMENTED_YET;
}

KZ_INLINE void kzsVgGaussianBlur(KzsVgImage dst, KzsVgImage src, kzFloat stdDevX, kzFloat stdDevY, KzsVgTilingMode tilingMode)
{
    KZS_NOT_IMPLEMENTED_YET;
}

KZ_INLINE void kzsVgLookup(KzsVgImage dst, KzsVgImage src, const kzByte* redLUT, const kzByte* greenLUT,
                           const kzByte* blueLUT, const kzByte* alphaLUT, kzBool outputLinear, kzBool outputPremultiplied)
{
    KZS_NOT_IMPLEMENTED_YET;
}

KZ_INLINE void kzsVgLookupSingle(KzsVgImage dst, KzsVgImage src, const kzUint* LUT, KzsVgImageChannel sourceChannel,
                                 kzBool outputLinear, kzBool outputPremultiplied)
{
    KZS_NOT_IMPLEMENTED_YET;
}

/* Querying Hardware Capabilities */

KZ_INLINE KzsVgHardwareQueryResult kzsVgHardwareQuery(KzsVgHardwareQueryType key, kzInt setting)
{
    KZS_NOT_IMPLEMENTED_YET;
    return KZS_VG_HARDWARE_UNACCELERATED;
}

/* Querying Strings */

KZ_INLINE kzString kzsVgGetString(KzsVgStringID name)
{
    KZS_NOT_IMPLEMENTED_YET;
    return KZ_NULL;
}


KZ_HEADER_END


#endif
