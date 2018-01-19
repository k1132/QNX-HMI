/**
* \file
* User interface trajectory layout component.
*
* KzuUiTrajectoryLayout lays out its children on a user-specified ::KzuTrajectory.
*
* Trajectory Layout Messages
* ----
* KzuUiTrajectoryLayout does not send or receive any messages.
*
* Trajectory Layout Properties
* ----
* ::KZU_PROPERTY_TYPE_TRAJECTORY string property specifies the resource ID of the ::KzuTrajectory to use in the trajectory layout.
*
* ::KZU_PROPERTY_TYPE_TRAJECTORY_LAYOUT_FIXED_DISTANCE float property can be set to specify a fixed distance between the children. If the property
* is not set, the whole trajectory length is used and the children are placed an equal distance apart from each other.
*
* ::KZU_PROPERTY_TYPE_TRAJECTORY_LAYOUT_ALIGN_TO_TANGENT Boolean property specifies whether the children are aligned according to the tangent of
* the trajectory in the child's offset. The default value is ::KZ_FALSE.
*
* ::KZU_PROPERTY_TYPE_STATIC_TRAJECTORY_OFFSET float property can be set in a child of the trajectory layout. It specifies a static offset
* for the child in the layout's ::KzuTrajectory. The value should be in the range [0, 1].
*
* ::KZU_PROPERTY_TYPE_VISIBLE_AMOUNT_IN_PARENT float property is set by the trajectory layout in every child of the layout.
* It tells how much of the child is inside the trajectory layout's clipping area. Its value is in the range [0, 1].
*
* ::KZU_PROPERTY_TYPE_TRAJECTORY_OFFSET float property is set by the trajectory layout in every child of the layout.
* It tells the child's current offset in the layout's ::KzuTrajectory. The value is in the range [0, 1].
*
* ::KZU_PROPERTY_TYPE_TRAJECTORY_LAYOUT_CLIP_START_OFFSET_PROPORTIONAL float property specifies an offset (in proportional range [0, 1])
* to the beginning of the clipping area of the trajectory layout. This property affects the ::KZU_PROPERTY_TYPE_VISIBLE_AMOUNT_IN_PARENT
* property setting only. The default value is 0.
*
* ::KZU_PROPERTY_TYPE_TRAJECTORY_LAYOUT_CLIP_END_OFFSET_PROPORTIONAL float property specifies an offset (in proportional range [0, 1])
* to the end of the clipping area of the trajectory layout. This property affects the ::KZU_PROPERTY_TYPE_VISIBLE_AMOUNT_IN_PARENT
* property setting only. The default value is 1.
*
* ::KZU_PROPERTY_TYPE_TRAJECTORY_LAYOUT_SCROLL_OFFSET_PROPORTIONAL float property specifies an offset (in proportional range [0, 1])
* to the first child on the trajectory. The default value is 0.
*
* \see \ref kzu_trajectory.h.
*
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_UI_TRAJECTORY_LAYOUT_H
#define KZU_UI_TRAJECTORY_LAYOUT_H


#include <user/scene_graph/kzu_object_common.h>

#include <system/kzs_types.h>
#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations. */
struct KzcMemoryManager;
struct KzcHashMap;
struct KzuTrajectory;
struct KzuUiComponentNode;
struct KzuPropertyManager;
struct KzuMessageDispatcher;
struct KzuFactory;
struct KzuObjectNode;
struct KzuUIDomain;
struct KzuBoundingVolume;


/**
 * \struct KzuUiTrajectoryLayout
 * Trajectory layout user interface component. Aligns objects in a trajectory.
 */
struct KzuUiTrajectoryLayout;


/** Object type for trajectory layout. */
extern const KzuObjectType KZU_OBJECT_TYPE_UI_TRAJECTORY_LAYOUT;


/** Creates a trajectory layout with default settings. */
kzsError kzuUiTrajectoryLayoutCreate(const struct KzcMemoryManager* memoryManager, kzString name, struct KzuUIDomain* uiDomain, struct KzuUiTrajectoryLayout** out_trajectoryLayout);
/** Registers component type to factory. */
kzsError kzuUiTrajectoryLayoutRegisterToFactory(const struct KzuFactory* factory);

/** Casts to UiComponentNode. */
struct KzuUiComponentNode* kzuUiTrajectoryLayoutToUiComponentNode(const struct KzuUiTrajectoryLayout* trajectoryLayout);

/** Casts to UiTrajectoryLayout. */
struct KzuUiTrajectoryLayout* kzuUiTrajectoryLayoutFromUiComponentNode(const struct KzuUiComponentNode* component);

/** Converts a proportional offset to a length offset. */
kzFloat kzuUiTrajectoryLayoutProportionalToLength(const struct KzuUiTrajectoryLayout* trajectoryLayout, kzFloat proportionalOffset);
/** Converts a unit length offset to a proportional offset. */
kzFloat kzuUiTrajectoryLayoutLengthToProportional(const struct KzuUiTrajectoryLayout* trajectoryLayout, kzFloat lengthOffset);

/** Gets proportional offset of an object. */
kzsError kzuUiTrajectoryLayoutGetObjectOffset(const struct KzuUiTrajectoryLayout* trajectoryLayout, const struct KzuObjectNode* objectNode, kzFloat* out_value);

/** Returns offset of start of clipping area of trajectory, in proportional range. */
kzFloat kzuUiTrajectoryLayoutGetClipStartOffset(const struct KzuUiTrajectoryLayout* trajectoryLayout);
/** Returns offset of end of clipping area of trajectory, in proportional range. */
kzFloat kzuUiTrajectoryLayoutGetClipEndOffset(const struct KzuUiTrajectoryLayout* trajectoryLayout);
/** Returns length of the trajectory. */
kzFloat kzuUiTrajectoryLayoutGetCurveLength(const struct KzuUiTrajectoryLayout* trajectoryLayout);

/** Sets trajectory layout's scroll offset in proportional range. */
kzsError kzuUiTrajectoryLayoutSetScrollOffset(const struct KzuUiTrajectoryLayout* trajectoryLayout, kzFloat proportionalOffset);
/** Gets trajectory layout's scroll offset in proportional range. */
kzFloat kzuUiTrajectoryLayoutGetScrollOffset(const struct KzuUiTrajectoryLayout* trajectoryLayout);

/** Gets fixed distance variable of trajectory layout, in absolute units from zero offset. Returns whether the property was set. */
kzBool kzuUiTrajectoryLayoutGetFixedDistance(const struct KzuUiTrajectoryLayout* trajectoryLayout, kzFloat* out_fixedDistance);
/** Sets fixed distance variable of trajectory layout, in absolute units from zero offset. */
kzsError kzuUiTrajectoryLayoutSetFixedDistance(const struct KzuUiTrajectoryLayout* trajectoryLayout, kzFloat fixedDistance);

/** Gets the trajectory attached to the trajectory layout. */
struct KzuTrajectory* kzuUiTrajectoryLayoutGetTrajectory(const struct KzuUiTrajectoryLayout* trajectoryLayout);
/** Sets the trajectory attached to the trajectory layout. */
kzsError kzuUiTrajectoryLayoutSetTrajectory(struct KzuUiTrajectoryLayout* trajectoryLayout, struct KzuTrajectory* trajectory);

/** Bounding volume getter implementation. */
kzsError kzuUiTrajectoryLayoutGetBoundingVolume_protected(const struct KzuObjectNode* objectNode, struct KzuBoundingVolume* out_boundingVolume);


KZ_HEADER_END


#endif
