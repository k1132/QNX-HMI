/**
* \file
* Long press manipulator.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_LONG_PRESS_MANIPULATOR_H
#define KZU_LONG_PRESS_MANIPULATOR_H


#include <system/kzs_types.h>
#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations. */
struct KzuInputManipulator;
struct KzuPropertyManager;
struct KzcMemoryManager;


/** Create a long press gesture manipulator. */
kzsError kzuLongPressManipulatorCreate(const struct KzcMemoryManager* memoryManager, struct KzuPropertyManager* propertyManager, struct KzuInputManipulator** out_inputManipulator);
/** Set long press duration in milliseconds. Default is 500ms. */
kzsError kzuLongPressManipulatorSetPressDuration(struct KzuInputManipulator* inputManipulator, kzUint pressDuration);


KZ_HEADER_END


#endif
