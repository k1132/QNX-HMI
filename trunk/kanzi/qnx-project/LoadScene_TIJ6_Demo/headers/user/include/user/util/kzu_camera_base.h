/**
 * \file
 * Common structures for util cameras.
 *
 * Copyright 2008-2014 by Rightware. All rights reserved.
 */
#ifndef KZU_CAMERA_BASE_H
#define KZU_CAMERA_BASE_H


#include <core/util/math/kzc_quaternion.h>
#include <core/util/math/kzc_vector3.h>

#include <system/kzs_types.h>


/** Camera transformation attributes. */
struct KzuCameraTransformationAttributes
{
    struct KzcQuaternion baseOrientation; /**< Base orientation of camera in parent's space. */
    struct KzcVector3 position;           /**< Position of camera in base orientation space. */
    kzFloat rotationX;                    /**< Rotation of camera around X-axis in base orientation space. */
    kzFloat rotationY;                    /**< Rotation of camera around Y-axis in base orientation space. */
};


#endif
