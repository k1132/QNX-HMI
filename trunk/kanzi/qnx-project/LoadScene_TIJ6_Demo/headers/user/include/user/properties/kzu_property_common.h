/**
* \file
* Specifies property base struct.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_PROPERTY_COMMON_H
#define KZU_PROPERTY_COMMON_H


#include <system/kzs_types.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/** Datatype of property */
enum KzuPropertyDataType
{
    KZU_PROPERTY_DATA_TYPE_FLOAT, /**< Float value. */
    KZU_PROPERTY_DATA_TYPE_INT, /**< Integer. */
    KZU_PROPERTY_DATA_TYPE_BOOL, /**< Boolean. */
    KZU_PROPERTY_DATA_TYPE_COLOR, /**< Color. */
    KZU_PROPERTY_DATA_TYPE_VECTOR2, /**< 2-component vector. */
    KZU_PROPERTY_DATA_TYPE_VECTOR3, /**< 3-component vector. */
    KZU_PROPERTY_DATA_TYPE_VECTOR4, /**< 4-component vector. */
    KZU_PROPERTY_DATA_TYPE_MATRIX2X2, /**< Matrix2x2. */
    KZU_PROPERTY_DATA_TYPE_MATRIX3X3, /**< Matrix3x3. */
    KZU_PROPERTY_DATA_TYPE_MATRIX4X4, /**< Matrix4x4. */
    KZU_PROPERTY_DATA_TYPE_STRING, /**< String. */
    KZU_PROPERTY_DATA_TYPE_POINTER, /**< Pointer. */
    KZU_PROPERTY_DATA_TYPE_STRUCT, /**< Struct. */
    KZU_PROPERTY_DATA_TYPE_ARRAY, /**< Array. */
    KZU_PROPERTY_DATA_TYPE_RESOURCE_ID /**< Resource ID. */
};

/** Property field. */
enum KzuPropertyField
{
    KZU_PROPERTY_FIELD_WHOLE,            /**< Whole property. */
    KZU_PROPERTY_FIELD_TRANSLATION_X,    /**< Translation X component. */
    KZU_PROPERTY_FIELD_TRANSLATION_Y,    /**< Translation Y component. */
    KZU_PROPERTY_FIELD_TRANSLATION_Z,    /**< Translation Z component. */
    KZU_PROPERTY_FIELD_SCALE_X,          /**< Scale X component. */
    KZU_PROPERTY_FIELD_SCALE_Y,          /**< Scale Ycomponent. */
    KZU_PROPERTY_FIELD_SCALE_Z,          /**< Scale Z component. */
    KZU_PROPERTY_FIELD_ROTATION_X,       /**< Rotation X component. */
    KZU_PROPERTY_FIELD_ROTATION_Y,       /**< Rotation Y component. */
    KZU_PROPERTY_FIELD_ROTATION_Z,       /**< Rotation Z component. */
    KZU_PROPERTY_FIELD_COLOR_R,          /**< Color R field. */
    KZU_PROPERTY_FIELD_COLOR_G,          /**< Color G field. */
    KZU_PROPERTY_FIELD_COLOR_B,          /**< Color B field. */
    KZU_PROPERTY_FIELD_COLOR_A,          /**< Color A field. */
    KZU_PROPERTY_FIELD_VECTOR_X,         /**< Vector X field. */
    KZU_PROPERTY_FIELD_VECTOR_Y,         /**< Vector Y field. */
    KZU_PROPERTY_FIELD_VECTOR_Z,         /**< Vector Z field. */
    KZU_PROPERTY_FIELD_VECTOR_W          /**< Vector W field. */
};


KZ_HEADER_END


#endif
