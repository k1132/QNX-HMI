/**
* \file
* Plane structure and operations.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZC_PLANE_H
#define KZC_PLANE_H


#include <system/kzs_types.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations */
struct KzcVector3;
struct KzcRay;


/** Structure for a plane. Mathematically, a plane is defined as: a*x + b*y + c*z + d = 0. */
struct KzcPlane
{
    kzFloat a; /**< X component of normal. */
    kzFloat b; /**< Y component of normal. */
    kzFloat c; /**< Z component of normal. */
    kzFloat d; /**< Negative distance component. */
};


/** Creates a plane structure from a point (x,y,z) on the plane and negative distance from origin. */
KZ_INLINE struct KzcPlane kzcPlane(kzFloat x, kzFloat y, kzFloat z, kzFloat negativeDistance)
{
    struct KzcPlane plane;
    plane.a = x;
    plane.b = y;
    plane.c = z;
    plane.d = negativeDistance;

    return plane;
}

/** Constructs a plane from point and normal. The normal must be of unit length. */
void kzcPlaneCreateFromPointAndNormal(struct KzcPlane* plane, const struct KzcVector3* point, const struct KzcVector3* normal);

/** Gets point's distance to plane. */
kzFloat kzcPlaneDistanceToPoint(const struct KzcPlane* plane, const struct KzcVector3* point);

/**
* Gets ray and plane intersection point.
* The plane and the ray are tested for parallelness using the tolerance value.
* If the tolerance test does not pass, output values are filled with NaNs and KZ_FALSE is returned.
*/
kzBool kzcPlaneRayIntersection(const struct KzcPlane* plane, const struct KzcRay* ray, kzFloat parallelTolerance, kzFloat* out_distance, struct KzcVector3* out_intersectionPoint);

/** Project a direction vector onto a plane. */
void kzcPlaneProjectDirectionVector3(const struct KzcPlane* plane, const struct KzcVector3* vector, struct KzcVector3* out_vector);

/** Project a position vector onto the plane. */
void kzcPlaneProjectPositionVector3(const struct KzcPlane* plane, const struct KzcVector3* position, struct KzcVector3* out_position);


/** Outputs plane normal into out_normal. */
void kzcPlaneGetNormal(const struct KzcPlane* plane, struct KzcVector3* out_normal);


KZ_HEADER_END


#endif
