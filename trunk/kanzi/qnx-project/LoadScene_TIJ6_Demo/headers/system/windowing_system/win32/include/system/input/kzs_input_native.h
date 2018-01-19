/**
* \file
* Kanzi input, win32 specific implementation
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZS_INPUT_NATIVE_H
#define KZS_INPUT_NATIVE_H


#include <system/kzs_types.h>
#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>

#include <windows.h>


KZ_HEADER_BEGIN


/* Forward declaration structures. */
struct KzsEventQueue;
struct KzsInputPointingDevice;
struct KzsWindow;


/** Message handler for native input. */
kzsError kzsInputNativeHandleMessage(struct KzsWindow* window, struct KzsEventQueue* queue, HWND hWnd, UINT message, WPARAM wparam, LPARAM lparam, kzBool* out_handled);
/** Low-level message handler for native input. Expects g_activeEventQueue to be a valid input event queue. */
kzsError kzsWindowNativeWndProcHandler(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam, kzBool* out_handled);


KZ_HEADER_END


#endif
