/**
* \file
* Click manipulator.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_CLICK_MANIPULATOR_H
#define KZU_CLICK_MANIPULATOR_H


#include <system/kzs_types.h>
#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations. */
struct KzuInputManipulator;
struct KzuObjectNode;
struct KzuPropertyManager;
struct KzcMemoryManager;


/** Create a click manipulator. */
kzsError kzuClickManipulatorCreate(const struct KzcMemoryManager* memoryManager, struct KzuPropertyManager* propertyManager, struct KzuInputManipulator** out_inputManipulator);
/** Enable or disable click begin on hovering. */
void kzuClickManipulatorSetHoverToBegin(struct KzuInputManipulator* inputManipulator, kzBool hoverToBegin);


KZ_HEADER_END


#endif
