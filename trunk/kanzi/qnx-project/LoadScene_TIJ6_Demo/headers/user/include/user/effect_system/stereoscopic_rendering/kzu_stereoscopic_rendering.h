/**
* \file
* Specifies a stereoscopic rendering modes.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_STEREOSCOPIC_RENDERING_H
#define KZU_STEREOSCOPIC_RENDERING_H


#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/** List of stereoscopic rendering modes. */
enum KzuStereoscopicRenderingMode
{
    KZU_STEREOSCOPIC_RENDERING_ANAGLYPHIC_RED_CYAN, /**< Anaglyphic red-cyan rendering. */
    KZU_STEREOSCOPIC_RENDERING_VERTICAL_LINE_INTERLACED, /**< Vertical line interlaced. */
    KZU_STEREOSCOPIC_RENDERING_HORIZONTAL_LINE_INTERLACED, /**< Horizontal line interlaced. */
    KZU_STEREOSCOPIC_RENDERING_TOP_BOTTOM, /**< Top bottom viewports */
    KZU_STEREOSCOPIC_RENDERING_BOTTOM_TOP, /**< Bottom top viewports */
    KZU_STEREOSCOPIC_RENDERING_LEFT_RIGHT, /**< Left right viewports */
    KZU_STEREOSCOPIC_RENDERING_RIGHT_LEFT, /**< Right left viewports */
    KZU_STEREOSCOPIC_RENDERING_VERTICAL_LINE_INTERLACED_R2G1B2_R1G2B1, /**< Vertical line interlaced with swapped G components. */
    KZU_STEREOSCOPIC_RENDERING_FRAME_INTERLEAVING, /**< Frame interleaving. */
    KZU_STEREOSCOPIC_RENDERING_DISABLED /**< Disabled stereoscopic rendering. */
};


KZ_HEADER_END


#endif
