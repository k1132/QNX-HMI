/**
* \file
* Utility for calculating 2D pixel coordinate from 3D point and camera projection.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_PROJECTION_H
#define KZU_PROJECTION_H


#include <system/debug/kzs_error.h>
#include <system/kzs_types.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations. */
struct KzuCameraNode;
struct KzcVector3;
struct KzcDynamicArray;


/** Projection vec3 in world coordinates to actual pixel coordinates. Result in X, Y pixel coordinates using mathematical coordinate
    system from bottom-left growing to top-right. */
kzsError kzuProjectionVector3ToPixelCoordinates(const struct KzcVector3* vectorInWorldCoordinates, struct KzuCameraNode* cameraNode,
                                                const struct KzcDynamicArray* transformedObjects,
                                                kzInt viewportX, kzInt viewportY, kzUint viewportWidth, kzUint viewportHeight,
                                                kzInt* out_x, kzInt* out_y);


KZ_HEADER_END


#endif
