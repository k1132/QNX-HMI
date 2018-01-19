/**
* \file
* Kanzi input device implementation.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZS_INPUT_DEVICE_H
#define KZS_INPUT_DEVICE_H


#include <system/debug/kzs_error.h>
#include <system/input/kzs_input.h>
#include <system/display/kzs_desktop.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/**
 * \struct KzsInputDevice
 * Input device object.
 */
struct KzsInputDevice;


/** Creates an input device. */
kzsError kzsInputDeviceCreate(const struct KzsDesktop* desktop, struct KzsInputDevice** device_out);

/** Deletes an input device. */
kzsError kzsInputDeviceDelete(struct KzsInputDevice* device);

/** Enqueues input data from input device. */
kzsError kzsInputDeviceGatherData(const struct KzsInputDevice* device, struct KzsEventQueue* queue);


KZ_HEADER_END


#endif
