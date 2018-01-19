/**
* \file
* Specifies renderer types.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_RENDERER_TYPES_H
#define KZU_RENDERER_TYPES_H


#include <system/kzs_types.h>


KZ_HEADER_BEGIN

/** Enumeration for face culling mode. */
enum KzuCullMode
{
    KZU_CULL_MODE_NONE,  /**< No culling. */
    KZU_CULL_MODE_BACK,  /**< Cull back faces. */
    KZU_CULL_MODE_FRONT  /**< Cull front faces. */
};

/** Enumeration for color write mode. */
enum KzuColorWriteMode
{
    KZU_COLOR_WRITE_NONE,       /**< No write for color channels. */
    KZU_COLOR_WRITE_RGB,        /**< Write to RGB color channels. */
    KZU_COLOR_WRITE_RGBA,       /**< Write to RGBA color channels. */
    KZU_COLOR_WRITE_GRAYSCALE,  /**< Write gray scale. */
    KZU_COLOR_WRITE_RED,        /**< Write R (red) only. */
    KZU_COLOR_WRITE_GREEN,      /**< Write G (green) only. */
    KZU_COLOR_WRITE_BLUE,       /**< Write B (blue) only. */
    KZU_COLOR_WRITE_ALPHA       /**< Write A (alpha) only. */
};

/** Enumeration for stencil operation. */
enum KzuStencilOperation
{
    KZU_STENCIL_OPERATION_KEEP = 0, /**< No operations for stencil buffer. */
    KZU_STENCIL_OPERATION_ZERO = 1, /**< Zero the stencil buffer. */
    KZU_STENCIL_OPERATION_REPLACE = 2, /**< Replace. */
    KZU_STENCIL_OPERATION_INCREASE = 3, /**< Incr. */
    KZU_STENCIL_OPERATION_INCREASE_WRAP = 4, /**< Incr wrap. */
    KZU_STENCIL_OPERATION_DECREASE = 5, /**< Decr. */
    KZU_STENCIL_OPERATION_DECREASE_WRAP = 6, /**< Decr wrap. */
    KZU_STENCIL_OPERATION_INVERT = 7 /**< Invert */
};

/** Enumeration for stencil function. */
enum KzuStencilFunction
{
    KZU_STENCIL_FUNCTION_NEVER = 0,               /**< Always false. */
    KZU_STENCIL_FUNCTION_ALWAYS = 1,              /**< Always true. */
    KZU_STENCIL_FUNCTION_LESS = 2,                /**< ref < stencil. */
    KZU_STENCIL_FUNCTION_LEQUAL = 3,              /**< ref <= stencil. */
    KZU_STENCIL_FUNCTION_GREATER = 4,             /**< ref > stencil. */
    KZU_STENCIL_FUNCTION_GEQUAL = 5,              /**< ref >= stencil. */
    KZU_STENCIL_FUNCTION_EQUAL = 6,               /**< ref = stencil. */
    KZU_STENCIL_FUNCTION_NOT_EQUAL = 7            /**< ref != stencil. */
};

KZ_HEADER_END


#endif
