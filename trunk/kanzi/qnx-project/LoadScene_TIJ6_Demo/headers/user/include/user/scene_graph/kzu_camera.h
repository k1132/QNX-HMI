/**
* \file
* Represents camera (viewer) in scene graph. KzuCameraNode inherits from KzuObjectNode.
*
* Camera Messages
* ----
* KzuCameraNode does not send or receive any messages.
*
* Camera Properties
* ----
* ::KZU_PROPERTY_TYPE_CAMERA_PROJECTION_TYPE integer property specifies the camera projection type. The value should be one of ::KzuProjectionType values.
* The default value is ::KZU_PROJECTION_PERSPECTIVE.
*
* ::KZU_PROPERTY_TYPE_CAMERA_ORTHOGONAL_COORDINATE_SYSTEM_TYPE integer property specifies the orthogonal coordinate system.
* The value should be one of ::KzuOrthogonalCoordinateSystem values. The value has an effect only when using an orthogonal projection.
* In the absolute mode, the camera uses pixel coordinates. In the relative mode, the camera displays an area whose width is -1..1 scaled with 
* ::KZU_PROPERTY_TYPE_CAMERA_ORTHOGONAL_PLANE_HEIGHT. The default value is ::KZU_ORTHOGONAL_COORDINATE_SYSTEM_RELATIVE.
*
* ::KZU_PROPERTY_TYPE_CAMERA_ASPECT_RATIO float property specifies the camera's aspect ratio. This property has an effect only when
* ::KZU_PROPERTY_TYPE_CAMERA_DISABLE_ASPECT_RATIO is ::KZ_FALSE. The default value is 1.666667.
*
* ::KZU_PROPERTY_TYPE_CAMERA_DISABLE_ASPECT_RATIO Boolean property specifies whether or not to use the aspect ratio setting from the viewport in render pass.
* If the value is ::KZ_FALSE, the aspect ratio is read from the ::KZU_PROPERTY_TYPE_CAMERA_ASPECT_RATIO property of the camera. The default value is ::KZ_TRUE.
*
* ::KZU_PROPERTY_TYPE_CAMERA_ZNEAR float property specifies the distance of the near clipping plane from the camera. Objects closer to the camera are not displayed.
* The default value is 0.1.
*
* ::KZU_PROPERTY_TYPE_CAMERA_ZFAR float property specifies the distance of the far clipping plane from the camera. Objects that are farther away than the far clipping 
* plane from the camera are not shown. The default value is 100.0.
*
* ::KZU_PROPERTY_TYPE_CAMERA_ORTHOGONAL_PLANE_HEIGHT float property specifies a value used for scaling the view area of a relative orthographic camera.
*
* ::KZU_PROPERTY_TYPE_CAMERA_FOV_TYPE integer property specifies whether the ::KZU_PROPERTY_TYPE_CAMERA_FOV property specifies the field-of-view in 
* horizontal or vertical direction. The default value is ::KZU_CAMERA_FIELD_OF_VIEW_HORIZONTAL.
*
* ::KZU_PROPERTY_TYPE_CAMERA_FOV float property specifies the field-of-view angle in degrees. Depending on ::KZU_PROPERTY_TYPE_CAMERA_FOV_TYPE the value
* specifies the angle in horizontal or vertical direction. The default value is 45.
*
* ::KZU_PROPERTY_TYPE_CAMERA_ORIENTATION_ANGLE is not used.
*
* ::KZU_PROPERTY_TYPE_CAMERA_SCREEN_SPACE_SHIFT ::KzcVector2 property specifies how much the camera should shift the projected scene in X and Y direction.
* This can be used for anti-aliasing. The default value is {0, 0}.
*
* \see \ref kzu_object.h for KzuObjectNode documentation.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_CAMERA_H
#define KZU_CAMERA_H


#include <user/scene_graph/kzu_object_common.h>

#include <core/util/math/kzc_plane.h>
#include <core/util/math/kzc_matrix4x4.h>

#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/** Enumeration for camera's field of view type */
enum KzuFieldOfViewType
{
    KZU_CAMERA_FIELD_OF_VIEW_HORIZONTAL,    /**< Horizontal field of view. */
    KZU_CAMERA_FIELD_OF_VIEW_VERTICAL,      /**< Vertical field of view. */
    KZU_FIELD_OF_VIEW_TYPE_COUNT  /**< Last enum value for value validity checks. */
};

/** Enumeration for camera's projection type */
enum KzuProjectionType
{
    KZU_PROJECTION_PERSPECTIVE, /**< Perspective projection */
    KZU_PROJECTION_ORTHOGRAPHIC, /**< Orthogonal projection */
    KZU_PROJECTION_TYPE_COUNT  /**< Last enum value for value validity checks. */
};

/** Enumeration for orthogonal coordinate system. */
enum KzuOrthogonalCoordinateSystem
{
    KZU_ORTHOGONAL_COORDINATE_SYSTEM_ABSOLUTE,  /**< Absolute orthogonal projection. */
    KZU_ORTHOGONAL_COORDINATE_SYSTEM_RELATIVE,  /**< Relative orthogonal projection. */
    KZU_ORTHOGONAL_COORDINATE_SYSTEM_COUNT    /**< Last enum value for value validity checks. */
};

/** Enumeration for defined frustum planes. */
enum KzuFrustumPlane
{
    KZU_FRUSTUM_PLANE_NEAR,     /**< Near frustum plane. */
    KZU_FRUSTUM_PLANE_FAR,      /**< Far frustum plane. */
    KZU_FRUSTUM_PLANE_TOP,      /**< Top frustum plane. */
    KZU_FRUSTUM_PLANE_BOTTOM,   /**< Bottom frustum plane. */
    KZU_FRUSTUM_PLANE_LEFT,     /**< Left frustum plane. */
    KZU_FRUSTUM_PLANE_RIGHT     /**< Right frustum plane. */
};

#define KZU_FRUSTUM_PLANE_COUNT 6 /**< Number of frustum planes. */


/** Object type identifier for camera objects. */
extern const KzuObjectType KZU_OBJECT_TYPE_CAMERA;


/* Forward declaration structures. */
struct KzcInputStream;
struct KzcMatrix4x4;
struct KzcVector3;
struct KzcMemoryManager;
struct KzuBinaryFileInfo;
struct KzuObjectNode;
struct KzuFactory;
struct KzuUIDomain;


/**
 * \struct KzuCameraNode
 * Camera in scene graph, inherited from KzuObjectNode.
 */
struct KzuCameraNode;


/** Creates new camera node. */
kzsError kzuCameraNodeCreate(const struct KzcMemoryManager* memoryManager, kzString name, 
                             struct KzuUIDomain* uiDomain, struct KzuCameraNode** out_cameraNode);
/** Deletes a camera node. */
kzsError kzuCameraNodeDelete(const struct KzuCameraNode* cameraNode);

/** Registers camera node type to factory. */
kzsError kzuCameraNodeRegisterToFactory(const struct KzuFactory* factory);


/** Gets a camera node from object node. */
struct KzuCameraNode* kzuCameraNodeFromObjectNode(const struct KzuObjectNode* objectNode);
/** Returns an object node from camera node. */
struct KzuObjectNode* kzuCameraNodeToObjectNode(const struct KzuCameraNode* cameraNode);

/** Sets orthogonal projection for camera. */
kzsError kzuCameraNodeSetOrthogonalProjection(const struct KzuCameraNode* cameraNode, enum KzuOrthogonalCoordinateSystem coordinateSystem);
/** Sets perspective projection for camera. */
kzsError kzuCameraNodeSetPerspectiveProjection(const struct KzuCameraNode* cameraNode);
/** Sets aspect ratio for camera. */
kzsError kzuCameraNodeSetAspectRatio(const struct KzuCameraNode* cameraNode, kzFloat aspectRatio);
/** Gets aspect ratio from camera. */
kzFloat kzuCameraNodeGetAspectRatio(const struct KzuCameraNode* cameraNode);

/** Sets inherited aspect ratio value for camera. */
void kzuCameraNodeSetInheritedAspectRatio(struct KzuCameraNode* cameraNode, kzFloat inheritedAspectRatio);

/** Creates a look at matrix for camera. */
kzsError kzuCameraNodeLookAt(const struct KzuCameraNode* cameraNode, struct KzcVector3 position, 
                             struct KzcVector3 lookAtPoint, struct KzcVector3 upVector);
/** Creates frustum planes for camera node. */
void kzuCameraNodeCalculateFrustumPlanes(const struct KzuCameraNode* cameraNode, const struct KzcMatrix4x4* cameraViewMatrix,
                                  struct KzcPlane* out_frustumPlanes);
/** Utility for calculating ortho projection from values. */
void kzuCameraNodeCalculateOrthogonalProjectionFromValues(kzFloat left, kzFloat right, kzFloat top, kzFloat bottom, 
                                                    enum KzuOrthogonalCoordinateSystem coordinateSystem, 
                                                    enum KzuFieldOfViewType fovType, kzFloat orthoHeight, kzFloat aspectRatio,
                                                    struct KzcMatrix4x4* out_projectionMatrix);
/** Creates a orthogonal projection for camera. */
void kzuCameraNodeCalculateOrthogonalProjection(const struct KzuCameraNode* cameraNode, kzFloat left, kzFloat right, kzFloat top, kzFloat bottom,
                                            struct KzcMatrix4x4* out_projectionMatrix);
/** Creates a projection for camera. */
void kzuCameraNodeCalculateProjectionMatrix(const struct KzuCameraNode* cameraNode, struct KzcMatrix4x4* out_projectionMatrix);

/** Clones a camera data from source. */
kzsError kzuCameraNodeCloneData(const struct KzuCameraNode* sourceCameraNode, struct KzuCameraNode* destinationCameraNode);


#include "kzu_camera_properties.h"


KZ_HEADER_END


#endif
