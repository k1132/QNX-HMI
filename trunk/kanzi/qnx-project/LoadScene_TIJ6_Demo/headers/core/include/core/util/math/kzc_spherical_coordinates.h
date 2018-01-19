/**
* \file
* Spherical coordinate system utilities.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZC_SPHERE_COORDINATES_H
#define KZC_SPHERE_COORDINATES_H


#include <core/util/math/kzc_vector3.h>

#include <system/kzs_types.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/** Returns the cartesian coordinates from given spherical coordinates. */
struct KzcVector3 kzcSphericalCoordinatesToCartesian(kzFloat radius, kzFloat phi, kzFloat theta);

/** Returns spherical coordinates for given cartesian coordinates. */
void kzcSphericalCoordinatesFromCartesian(struct KzcVector3 cartesian, kzFloat* out_radius, kzFloat* out_phi, kzFloat* out_theta);


KZ_HEADER_END


#endif
