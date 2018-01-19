/**
* \file
* Multi-click manipulator.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_MULTI_CLICK_MANIPULATOR_H
#define KZU_MULTI_CLICK_MANIPULATOR_H


#include <system/kzs_types.h>
#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations. */
struct KzuInputManipulator;
struct KzuObjectNode;
struct KzuPropertyManager;
struct KzcMemoryManager;


/** Create a multiclick gesture manipulator. */
kzsError kzuMultiClickManipulatorCreate(const struct KzcMemoryManager* memoryManager, struct KzuPropertyManager* propertyManager, struct KzuInputManipulator** out_inputManipulator);
/** Set multiclick timeout in milliseconds. Default is 250ms. */
kzsError kzuMultiClickManipulatorSetTimeout(struct KzuInputManipulator* inputManipulator, kzUint timeout);


KZ_HEADER_END


#endif
