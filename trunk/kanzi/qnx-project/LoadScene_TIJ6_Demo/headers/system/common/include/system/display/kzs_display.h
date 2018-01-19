/**
* \file
* Display device.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZS_DISPLAY_H
#define KZS_DISPLAY_H


#include <system/debug/kzs_error.h>
#include <system/kzs_types.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations. */
struct KzsDesktop;
struct KzsDisplayNative;


/**
 * \struct KzsDisplay
 * Display device object.
 */
struct KzsDisplay;


/** Creates a display with a previously created native display. */
kzsError kzsDisplayCreateFromNative(struct KzsDisplayNative* displayNative, kzUint displayID, struct KzsDisplay** out_display);

/** Creates a display and also the native display. */
kzsError kzsDisplayCreate(const struct KzsDesktop* desktop, kzUint displayID, struct KzsDisplay** out_display);

/** Deletes a display and frees all memory allocated for it. */
kzsError kzsDisplayDelete(struct KzsDisplay* display);

/** Returns the current width of the display in pixels. */
kzUint kzsDisplayGetCurrentWidth(const struct KzsDisplay* display);

/** Returns the current height of the display in pixels. */
kzUint kzsDisplayGetCurrentHeight(const struct KzsDisplay* display);

/** Returns the native display struct. */
struct KzsDisplayNative* kzsDisplayGetNative(const struct KzsDisplay* display);

/** Creates the platform independent portion of the display. */
kzsError kzsDisplayNativeCreate(const struct KzsDesktop* desktop, kzUint displayID, struct KzsDisplayNative** out_displayNative);

/** Deletes the platform independent portion of the display. */
kzsError kzsDisplayNativeDelete(struct KzsDisplayNative* displayNative);

/** Returns the current width of the display in pixels. */
kzUint kzsDisplayNativeGetCurrentWidth(const struct KzsDisplayNative* displayNative);

/** Returns the current height of the display in pixels. */
kzUint kzsDisplayNativeGetCurrentHeight(const struct KzsDisplayNative* displayNative);


KZ_HEADER_END


#endif
