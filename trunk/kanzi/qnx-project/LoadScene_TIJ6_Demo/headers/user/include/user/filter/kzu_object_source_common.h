/**
* \file
* Object source private members.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_OBJECT_SOURCE_COMMON_H
#define KZU_OBJECT_SOURCE_COMMON_H


#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/** Object source type. */
enum KzuObjectSourceType
{
    KZU_OBJECT_SOURCE_TYPE_FILTER, /**< Use filter as object source. */
    KZU_OBJECT_SOURCE_TYPE_COMBINER, /**< Object source combiner. */
    KZU_OBJECT_SOURCE_TYPE_SORT /**< Sorting object source. */
};

/** Measurement type for object sources. */
enum KzuObjectSourceMeasurement
{
    KZU_OBJECT_SOURCE_MEASUREMENT_OBJECT_SET_START, /**< Object set start. */
    KZU_OBJECT_SOURCE_MEASUREMENT_OBJECT_SET_APPLY, /**< Object set apply. */

    KZU_OBJECT_SOURCE_MEASUREMENT_OBJECT_TYPE_APPLY, /**< Object type apply. */

    KZU_OBJECT_SOURCE_MEASUREMENT_FRUSTUM_CULL_START, /**< Frustum cull start. */
    KZU_OBJECT_SOURCE_MEASUREMENT_FRUSTUM_CULL_APPLY, /**< Frustum cull apply. */

    KZU_OBJECT_SOURCE_MEASUREMENT_SORT_START, /**< Sort by Z start. */
    KZU_OBJECT_SOURCE_MEASUREMENT_SORT_APPLY, /**< Sort by Z apply. */

    KZU_OBJECT_SOURCE_MEASUREMENT_LOD_START,/**< LOD start. */
    KZU_OBJECT_SOURCE_MEASUREMENT_LOD_APPLY /**< LOD apply. */
};


KZ_HEADER_END


#endif
