/**
 * \file
 * Property accessors for KzuCameraNode.
 * 
 * Copyright 2008-2014 by Rightware. All rights reserved.
 */
#ifndef KZU_CAMERA_PROPERTIES_H
#define KZU_CAMERA_PROPERTIES_H


#include "kzu_camera.h"

#include <core/util/math/kzc_vector2.h>

#include <system/kzs_types.h>
#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations */
struct KzuCameraNode;


/** Gets the value of property DisableAspectRatio in cameraNode. */
kzBool kzuCameraNodeIsDisableAspectRatio(const struct KzuCameraNode* cameraNode);
/** Sets the value of property DisableAspectRatio in cameraNode. */
kzsError kzuCameraNodeSetDisableAspectRatio(const struct KzuCameraNode* cameraNode, kzBool value);

/** Gets the value of property ZNear in cameraNode. */
kzFloat kzuCameraNodeGetZNear(const struct KzuCameraNode* cameraNode);
/** Sets the value of property ZNear in cameraNode. */
kzsError kzuCameraNodeSetZNear(const struct KzuCameraNode* cameraNode, kzFloat value);

/** Gets the value of property ZFar in cameraNode. */
kzFloat kzuCameraNodeGetZFar(const struct KzuCameraNode* cameraNode);
/** Sets the value of property ZFar in cameraNode. */
kzsError kzuCameraNodeSetZFar(const struct KzuCameraNode* cameraNode, kzFloat value);

/** Gets the value of property ProjectionType in cameraNode. */
enum KzuProjectionType kzuCameraNodeGetProjectionType(const struct KzuCameraNode* cameraNode);
/** Sets the value of property ProjectionType in cameraNode. */
kzsError kzuCameraNodeSetProjectionType(const struct KzuCameraNode* cameraNode, enum KzuProjectionType value);

/** Gets the value of property OrthogonalCoordinateSystemType in cameraNode. */
enum KzuOrthogonalCoordinateSystem kzuCameraNodeGetOrthogonalCoordinateSystemType(const struct KzuCameraNode* cameraNode);
/** Sets the value of property OrthogonalCoordinateSystemType in cameraNode. */
kzsError kzuCameraNodeSetOrthogonalCoordinateSystemType(const struct KzuCameraNode* cameraNode, enum KzuOrthogonalCoordinateSystem value);

/** Gets the value of property OrthogonalPlaneHeight in cameraNode. */
kzFloat kzuCameraNodeGetOrthogonalPlaneHeight(const struct KzuCameraNode* cameraNode);
/** Sets the value of property OrthogonalPlaneHeight in cameraNode. */
kzsError kzuCameraNodeSetOrthogonalPlaneHeight(const struct KzuCameraNode* cameraNode, kzFloat value);

/** Gets the value of property FovType in cameraNode. */
enum KzuFieldOfViewType kzuCameraNodeGetFovType(const struct KzuCameraNode* cameraNode);
/** Sets the value of property FovType in cameraNode. */
kzsError kzuCameraNodeSetFovType(const struct KzuCameraNode* cameraNode, enum KzuFieldOfViewType value);

/** Gets the value of property Fov in cameraNode. */
kzFloat kzuCameraNodeGetFov(const struct KzuCameraNode* cameraNode);
/** Sets the value of property Fov in cameraNode. */
kzsError kzuCameraNodeSetFov(const struct KzuCameraNode* cameraNode, kzFloat value);

/** Gets the value of property OrientationAngle in cameraNode. */
kzFloat kzuCameraNodeGetOrientationAngle(const struct KzuCameraNode* cameraNode);
/** Sets the value of property OrientationAngle in cameraNode. */
kzsError kzuCameraNodeSetOrientationAngle(const struct KzuCameraNode* cameraNode, kzFloat value);

/** Gets the value of property ScreenSpaceShift in cameraNode. */
struct KzcVector2 kzuCameraNodeGetScreenSpaceShift(const struct KzuCameraNode* cameraNode);
/** Sets the value of property ScreenSpaceShift in cameraNode. */
kzsError kzuCameraNodeSetScreenSpaceShift(const struct KzuCameraNode* cameraNode, struct KzcVector2 value);


KZ_HEADER_END


#endif
