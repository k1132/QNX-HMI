/**
* \file
* Kanzi desktop.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZS_DESKTOP_H
#define KZS_DESKTOP_H

#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations. */
struct KzsDesktopNative;


/**
 * \struct KzsDesktop
 * Desktop object.
 */
struct KzsDesktop;


/** Creates a desktop. */
kzsError kzsDesktopCreate(struct KzsDesktop** out_desktop);
/** Deletes a desktop and frees all memory allocated for it. */
kzsError kzsDesktopDelete(struct KzsDesktop* desktop);

/** Gets number of available displays on the desktop. */
kzsError kzsDesktopGetDisplayCount(const struct KzsDesktop* desktop, kzUint* out_displayCount);

/** Returns the current desktop width in pixels. */
kzUint kzsDesktopGetCurrentWidth(const struct KzsDesktop* desktop);
/** Returns the current desktop height in pixels. */
kzUint kzsDesktopGetCurrentHeight(const struct KzsDesktop* desktop);

/** Returns the native desktop struct. */
struct KzsDesktopNative* kzsDesktopGetNative(const struct KzsDesktop* desktop);

/** Creates the platform dependent portion of the desktop. */
kzsError kzsDesktopNativeCreate(struct KzsDesktopNative** out_desktopNative);
/** Deletes the platform dependent portion of the desktop. */
kzsError kzsDesktopNativeDelete(struct KzsDesktopNative* desktopNative);

/** Gets number of available displays on the desktop. */
kzsError kzsDesktopNativeGetDisplayCount(const struct KzsDesktopNative* desktopNative, kzUint* out_displayCount);

/** Returns the current desktop width in pixels. */
kzUint kzsDesktopNativeGetCurrentWidth(const struct KzsDesktopNative* desktopNative);
/** Returns the current desktop height in pixels. */
kzUint kzsDesktopNativeGetCurrentHeight(const struct KzsDesktopNative* desktopNative);


KZ_HEADER_END


#endif
