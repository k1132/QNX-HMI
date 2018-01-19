/**
* \file
* Kanzi native input device implementation
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZS_INPUT_DEVICE_NATIVE_H
#define KZS_INPUT_DEVICE_NATIVE_H


#include <system/debug/kzs_error.h>
#include <system/input/kzs_input.h>
#include <system/display/kzs_desktop.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/**
 * \struct KzsInputDeviceNative
 * Native implementation of input device.
 */
struct KzsInputDeviceNative;


extern struct KzsEventQueue* g_activeEventQueue; /**< Context parameter for Win32 message handler callback functions. */


/** Creates an input device. */
kzsError kzsInputDeviceNativeCreate(const struct KzsDesktop* desktop, struct KzsInputDeviceNative** device_out);

/** Deletes an input device. */
kzsError kzsInputDeviceNativeDelete(struct KzsInputDeviceNative* device);

/** Enqueues input data from input device. */
kzsError kzsInputDeviceNativeGatherData(struct KzsInputDeviceNative* device, struct KzsEventQueue* queue);


KZ_HEADER_END


#endif
