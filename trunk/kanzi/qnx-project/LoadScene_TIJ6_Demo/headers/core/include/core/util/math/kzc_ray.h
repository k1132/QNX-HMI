/**
* \file
* Ray utility.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZC_RAY_H
#define KZC_RAY_H


#include <core/util/math/kzc_vector3.h>

#include <system/kzs_types.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations */
struct KzcMatrix4x4;


/** Structure for ray. Ray is defined by starting point and direction */
struct KzcRay
{
    struct KzcVector3 origin;       /**< Origin of the ray. */
    struct KzcVector3 direction;    /**< Direction of the ray, normalized. */
};


/** Constructs a ray from point and direction vector. Normalizes the direction vector */
KZ_INLINE void kzcRaySet(const struct KzcVector3 origin, const struct KzcVector3 direction, struct KzcRay* out_ray)
{
    out_ray->origin = origin;
    out_ray->direction = direction;
    kzcVector3Normalize(&out_ray->direction);
}

/** Test intersection between ray and sphere and return distance. */
kzBool kzcRaySphereIntersection(const struct KzcRay* ray, const struct KzcVector3* spherePosition,
                                const kzFloat sphereRadius, kzFloat* out_distance);

/** Test intersection between ray and bounding box. */
kzBool kzcRayBoundingBoxIntersection(const struct KzcRay* ray, const struct KzcVector3* boundingBoxMinimum, 
                                     const struct KzcVector3* boundingBoxMaximum, 
                                     const struct KzcMatrix4x4* boxOrientation, kzFloat* out_distance);

/** Test intersection between ray and bounding box back faces. */
kzBool kzcRayBoundingBoxBackfaceIntersection(const struct KzcRay* ray, const struct KzcVector3* boundingBoxMinimum, 
                                             const struct KzcVector3* boundingBoxMaximum, 
                                             const struct KzcMatrix4x4* boxOrientation, kzFloat* out_distance);

/**
* Tests intersection between ray and cylinder aligned in the given unit-axis, ranging [-height/2, height/2].
* 
* The cylinder is first transformed with the given transformation matrix.
*/
kzBool kzcRayCylinderIntersection(const struct KzcRay* ray, kzFloat cylinderRadius, kzFloat cylinderHeight,
                                  const struct KzcVector3* cylinderAxis, const struct KzcMatrix4x4* cylinderTransform,
                                  kzFloat* out_distance);
                                  
/** Transform a ray by a 4x4 matrix. */
void kzcRayTransform(struct KzcRay* ray, const struct KzcMatrix4x4* transform);


KZ_HEADER_END


#endif
