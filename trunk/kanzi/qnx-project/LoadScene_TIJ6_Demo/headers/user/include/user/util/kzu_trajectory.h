/**
* \file
* Trajectory. A path in 3d space.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_TRAJECTORY_H
#define KZU_TRAJECTORY_H


#include <user/resource/kzu_resource_common.h>

#include <system/debug/kzs_error.h>
#include <system/kzs_types.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/** Type of trajectory. */
enum KzuTrajectoryType
{
    KZU_TRAJECTORY_TYPE_SPLINE, /**< Series of points. Spline. */ 
    KZU_TRAJECTORY_TYPE_CIRCLE, /**< Circle. */ 
    KZU_TRAJECTORY_TYPE_LINE    /**< Line. */ 
};


/** Type of interpolation for spline trajectory. */
enum KzuTrajectoryInterpolationType
{
    KZU_TRAJECTORY_INTERPOLATION_TYPE_LINEAR,       /**< Linear interpolation. */ 
    KZU_TRAJECTORY_INTERPOLATION_TYPE_CATMULL_ROM,  /**< Catmull-Rom interpolation. */ 
    KZU_TRAJECTORY_INTERPOLATION_TYPE_HERMITE       /**< Hermite interpolation. */ 
};


/* Forward declarations */
struct KzcInputStream;
struct KzcMemoryManager;
struct KzcReparametrization;
struct KzcSpline;
struct KzcVector3;
struct KzuBinaryFileInfo;
struct KzuUIDomain;


/**
* \struct KzuTrajectory
* Structure to hold a trajectory.
*/
struct KzuTrajectory;


/** Resource type identifier for trajectory. */
extern const KzuResourceType KZU_RESOURCE_TYPE_TRAJECTORY;


/** Function type definition for function that can load a spline reference from .KZB input stream. */
typedef kzsError (*KzuTrajectoryLoadSplineCallback)(struct KzcInputStream* inputStream, void* userData, struct KzcSpline** out_spline);


/** Creates a trajectory with no data. */
kzsError kzuTrajectoryCreateEmpty(const struct KzcMemoryManager* memoryManager, const struct KzuUIDomain* uiDomain,
                                  kzString name, struct KzuTrajectory** out_trajectory);

/** 
* Creates a circle trajectory.
* \param memoryManager MemoryManager to allocate memory from.
* \param origin Origin of the circle trajectory.
* \param up Normal vector for the plane where the circle exists. The vector will be normalized internally.
* \param angle Rotation angle of the circle trajectory in its plane, in degrees.
* \param radius Radius of the circle.
*/
kzsError kzuTrajectoryCreateCircle(const struct KzcMemoryManager* memoryManager, struct KzcVector3 origin, struct KzcVector3 up,
                                   kzFloat angleInDegrees, kzFloat radius, const struct KzuUIDomain* uiDomain,
                                   kzString name, struct KzuTrajectory** out_trajectory);
/** 
* Creates a line trajectory.
* \param memoryManager MemoryManager to allocate memory from
* \param origin Origin of the line.
* \param direction Direction vector for the line. Direction will be normalized internally. 
* \param length Length of the line.
*/
kzsError kzuTrajectoryCreateLine(const struct KzcMemoryManager* memoryManager, struct KzcVector3 origin,
                                 struct KzcVector3 direction, kzFloat length, const struct KzuUIDomain* uiDomain,
                                 kzString name, struct KzuTrajectory** out_trajectory);

/** 
* Creates a spline trajectory.
* \param memoryManager MemoryManager to allocate memory from.
* \param spline Spline structure to use as trajectory.
*/
kzsError kzuTrajectoryCreateSpline(const struct KzcMemoryManager* memoryManager, struct KzcSpline* spline,
                                   const struct KzuUIDomain* uiDomain, kzString name, struct KzuTrajectory** out_trajectory);

/** Delete trajectory structure. */
kzsError kzuTrajectoryDelete(struct KzuTrajectory* trajectory);

/** Loads trajectory from KZB. */
kzsError kzuTrajectoryLoadFromKZB(struct KzuTrajectory* trajectory, struct KzcInputStream* inputStream, const struct KzuBinaryFileInfo* file);

/**
* Gets a point on trajectory by using absolute coordinates ranging from 0.0 to trajectory length.
* \param lengthParameter Point on the trajectory.
*/
kzsError kzuTrajectoryGetPointAbsolute(const struct KzuTrajectory* trajectory, kzFloat lengthParameter, struct KzcVector3* out_position);

/**
* Gets a point on trajectory by using relative coordinates.
* \param phaseParameter Point on the trajectory. 0.0f start, 1.0f end.
*/
kzsError kzuTrajectoryGetPointRelative(const struct KzuTrajectory* trajectory, kzFloat phaseParameter, struct KzcVector3* out_position);

/** Gets length of trajectory. */
kzFloat kzuTrajectoryGetLength(const struct KzuTrajectory* trajectory);


/** Returns true if trajectory is complete and usable. */
kzBool kzuTrajectoryIsComplete(const struct KzuTrajectory* trajectory);

/** 
 * Returns spline in case of trajectory having the spline. 
 * If type of the trajectory is not spline then NULL be returned.
 */
const struct KzcSpline* kzuTrajectoryGetSpline(const struct KzuTrajectory* trajectory);

/** Gets the number of counts recommended for visualizing the trajectory. */
kzsError kzuTrajectoryGetVisualizationPointCount(const struct KzuTrajectory* trajectory, kzUint* out_pointCount);
/** Gets a visualization point of the trajectory. */
kzsError kzuTrajectoryGetVisualizationPoint(const struct KzuTrajectory* trajectory, kzUint pointIndex, kzUint pointCount, struct KzcVector3* out_point);

/** Converts trajectory to resource. */
struct KzuResource* kzuTrajectoryToResource(const struct KzuTrajectory* trajectory);
/** Converts trajectory from resource. */
struct KzuTrajectory* kzuTrajectoryFromResource(const struct KzuResource* resource);
/** Casts trajectory from resource, KZ_NULL if invalid type. */
struct KzuTrajectory* kzuTrajectoryCastFromResource(const struct KzuResource* resource);


KZ_HEADER_END


#endif
