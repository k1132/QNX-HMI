/**
* \file
* Core component for smooth interpolation in code.
* Uses Runge-Kutta methods and suitable differential equations to smoothly interpolate
* between input data.
*
* Supports multiple interpolation modes such as looping/non-looping.
*
* Copyright 2008-2014 by Rightware. All rights reserved.
*/

#ifndef KZC_INTERPOLATED_VALUE_H
#define KZC_INTERPOLATED_VALUE_H


#include <system/debug/kzs_error.h>
#include <system/kzs_types.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations. */
struct KzcMemoryManager;

/**
 * \struct KzcInterpolatedValue
 * Provides smooth and reactive interpolation towards a dynamic target value.
 */
struct KzcInterpolatedValue;


/**
 * Creates an interpolated value integrator.
 * Larger acceleration coefficient leads to faster interpolation, larger drag coefficient lowers maximum speed.
 */
kzsError kzcInterpolatedValueCreate(const struct KzcMemoryManager* memoryManager, kzFloat startingValue,
                                    kzFloat accelerationCoefficient, kzFloat dragCoefficient,
                                    struct KzcInterpolatedValue** out_interpolatedValue);

/** Deletes an interpolated value integrator. */
kzsError kzcInterpolatedValueDelete(struct KzcInterpolatedValue* interpolatedValue);

/** Initializes simulation variables. */
void kzcInterpolatedValueInitializeBoundMode(struct KzcInterpolatedValue* interpolatedValue, kzFloat accelerationCoefficient, kzFloat dragCoefficient);

/** Sets minimum value for interpolator. */
void kzcInterpolatedValueSetMinimumValue(struct KzcInterpolatedValue* interpolatedValue, kzFloat minimumValue);

/** Gets minimum value of interpolator. */
kzFloat kzcInterpolatedValueGetMinimumValue(const struct KzcInterpolatedValue* interpolatedValue);

/** Sets maximum value for interpolator. */
void kzcInterpolatedValueSetMaximumValue(struct KzcInterpolatedValue* interpolatedValue, kzFloat maximumValue);

/** Gets maximum value of interpolator. */
kzFloat kzcInterpolatedValueGetMaximumValue(const struct KzcInterpolatedValue* interpolatedValue);

/**
 * Sets maximum time step for the interpolator.
 * Simulation time is split into time slices of at most this length.
 */
void kzcInterpolatedValueSetMaximumTimeStep(struct KzcInterpolatedValue* interpolatedValue, kzFloat maximumStep);

/**
 * Gets maximum time step of the interpolator.
 * Simulation time is split into time slices of at most this length.
 */
kzFloat kzcInterpolatedValueGetMaximumTimeStep(const struct KzcInterpolatedValue* interpolatedValue);


/** Sets interpolator to loop between minimum and maximum value. */
void kzcInterpolatedValueSetLooping(struct KzcInterpolatedValue* interpolatedValue, kzBool state);

/** Return interpolator's looping state. */
kzBool kzcInterpolatedValueIsLooping(const struct KzcInterpolatedValue* interpolatedValue);


/**
 * Normalizes interpolator's value to [minimumValue, maximumValue].
 * Calling this function manually is normally not required.
 */
void kzcInterpolatedValueEnforceBounds(struct KzcInterpolatedValue* interpolatedValue);


/**
 * Returns current value of the interpolator.
 * The value is normalized to the allowed range if a looping interpolator is used.
 */
kzFloat kzcInterpolatedValueGetValue(const struct KzcInterpolatedValue* interpolatedValue);

/**
 * Sets current value of the interpolator.
 * If resetInterpolation is KZ_TRUE, sets target to the new value and resets speed.
 */
void kzcInterpolatedValueSetValue(struct KzcInterpolatedValue* interpolatedValue, kzFloat value, kzBool resetInterpolation);


/** Sets current speed of the interpolated value. */
void kzcInterpolatedValueSetSpeed(struct KzcInterpolatedValue* interpolatedValue, kzFloat speed);

/** Returns current speed of the interpolated value. */
kzFloat kzcInterpolatedValueGetSpeed(const struct KzcInterpolatedValue* interpolatedValue);

/** Adds 'speedDelta' to current speed of the interpolated value. */
void kzcInterpolatedValueModifySpeed(struct KzcInterpolatedValue* interpolatedValue, kzFloat speedDelta);


/* Simulation functions. */

/** Integrates simulation for 'timeDelta' milliseconds. */
kzsError kzcInterpolatedValueUpdate(struct KzcInterpolatedValue* interpolatedValue, kzUint timeDelta);

/** Returns KZ_TRUE if interpolation has ended for now, i.e. target reached and speed close to zero. */
kzBool kzcInterpolatedValueInterpolationEnded(const struct KzcInterpolatedValue* interpolatedValue);


/**
 * Returns target value of the interpolator.
 * The value is normalized to the allowed range if a looping interpolator is used.
 *
 * Function kzcInterpolatedValueGetTargetNonNormalized should be used instead if the target value will be set back with kzcInterpolatedValueSetTarget.
 */
kzFloat kzcInterpolatedValueGetTarget(const struct KzcInterpolatedValue* interpolatedValue);

/**
 * Returns current non-normalized target value of the interpolator.
 * If the interpolator is looping, the target value may be out of bounds to indicate direction and repetition.
 *
 * This call should be used instead of kzcInterpolatedValueGetTarget if the target value will be set back with kzcInterpolatedValueSetTarget.
 */
kzFloat kzcInterpolatedValueGetTargetNonNormalized(const struct KzcInterpolatedValue* interpolatedValue);

/**
 * Sets target value of the interpolator.
 * If the interpolator is looping, the target value may be out bounds to indicate direction and repetition.
 */
void kzcInterpolatedValueSetTarget(struct KzcInterpolatedValue* interpolatedValue, kzFloat target);

/** Adds 'targetDelta' to target value of the interpolator. */
void kzcInterpolatedValueModifyTarget(struct KzcInterpolatedValue* interpolatedValue, kzFloat targetDelta);


KZ_HEADER_END


#endif
