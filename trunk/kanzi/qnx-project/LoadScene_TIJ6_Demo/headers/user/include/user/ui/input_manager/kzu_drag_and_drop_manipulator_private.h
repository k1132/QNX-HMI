/**
* \file
* Drag and drop manipulator.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_DRAG_AND_DROP_MANIPULATOR_PRIVATE_H
#define KZU_DRAG_AND_DROP_MANIPULATOR_PRIVATE_H


#include <system/kzs_types.h>
#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations. */
struct KzuInputManipulator;
struct KzuObjectNode;
struct KzuPropertyManager;
struct KzcMemoryManager;


/** Create drag and drop gesture manipulator. */
kzsError kzuDragAndDropManipulatorCreate(const struct KzcMemoryManager* memoryManager, struct KzuPropertyManager* propertyManager, struct KzuInputManipulator** out_inputManipulator);
/** Set long press duration before drag and drop starts in milliseconds. Default is 500ms. */
kzsError kzuDragAndDropManipulatorSetPressDuration(struct KzuInputManipulator* inputManipulator, kzUint pressDuration);


KZ_HEADER_END


#endif
