/**
* \file
* Implements an object that calculates average speed from its measurement data.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_SPEED_MEASURER_H
#define KZU_SPEED_MEASURER_H


#include <system/debug/kzs_error.h>
#include <system/kzs_types.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations. */

/**
* \struct KzuSpeedMeasurer
* Measures local average speed of movement.
*/
struct KzcMemoryManager;
struct KzuSpeedMeasurer;


/** Creates a speed measurer with the given properties. */
kzsError kzuSpeedMeasurerCreate(const struct KzcMemoryManager* memoryManager, kzUint maxMeasurements,
                                kzUint maxAveragingTime, struct KzuSpeedMeasurer** out_measurer);
/** Deletes a speed measurer. */
kzsError kzuSpeedMeasurerDelete(struct KzuSpeedMeasurer* measurer);


/** Resets measurement data. */
void kzuSpeedMeasurerReset(struct KzuSpeedMeasurer* measurer);

/** Adds a new measurement to the measurer. */
void kzuSpeedMeasurerAddMeasurement(struct KzuSpeedMeasurer* measurer, kzFloat position, kzUint timestamp);

/**
* Calculates average speed from measurements in units / second.
* Returns KZ_FALSE and 0.0f if there were not enough measurements.
*/
kzBool kzuSpeedMeasurerGetSpeed(const struct KzuSpeedMeasurer* measurer, kzUint measurementTime, kzFloat* out_speed);


KZ_HEADER_END


#endif
