/**
* \file
* Pan manipulator.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_PAN_MANIPULATOR_H
#define KZU_PAN_MANIPULATOR_H


#include <system/kzs_types.h>
#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations. */
struct KzuInputManipulator;
struct KzuObjectNode;
struct KzuPropertyManager;
struct KzcMemoryManager;


/** Create pan gesture manipulator. */
kzsError kzuPanManipulatorCreate(const struct KzcMemoryManager* memoryManager, struct KzuPropertyManager* propertyManager, struct KzuInputManipulator** out_inputManipulator);
/** Set the threshold the finger has to move before pan is recognized. Default is 5 screen units in either direction. */
kzsError kzuPanManipulatorSetRecognitionThreshold(struct KzuInputManipulator* inputManipulator, kzFloat thresholdX, kzFloat thresholdY);


KZ_HEADER_END


#endif
