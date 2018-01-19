/**
* \file
* Pinch manipulator.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_PINCH_MANIPULATOR_H
#define KZU_PINCH_MANIPULATOR_H


#include <system/kzs_types.h>
#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations. */
struct KzuInputManipulator;
struct KzuObjectNode;
struct KzuPropertyManager;
struct KzcMemoryManager;


/** Create pinch gesture manipulator. */
kzsError kzuPinchManipulatorCreate(const struct KzcMemoryManager* memoryManager, struct KzuPropertyManager* propertyManager, struct KzuInputManipulator** out_inputManipulator);
/** Set the threshold the fingers have to move away from each other before scale is recognized. Default is 5 screen units. */
kzsError kzuPinchManipulatorSetScaleRecognitionThreshold(struct KzuInputManipulator* inputManipulator, kzFloat threshold);
/** Set the threshold the fingers have to rotate around the midpoint before rotation is recognized. Default is 5 screen units along the circle. */
kzsError kzuPinchManipulatorSetRotationRecognitionThreshold(struct KzuInputManipulator* inputManipulator, kzFloat threshold);


KZ_HEADER_END


#endif
