/**
* \file
* Windows API definitions that may not be visible in older Microsoft SDKs.
*
* The contents of this file are taken from MSDN.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZS_WINAPI_H
#define KZS_WINAPI_H


#include <windows.h>

#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


#ifdef __MINGW32__
#define __in
#define __out
#endif

#if _MSC_VER < 1600

#define TWF_FINETOUCH 0x00000001
#define TWF_WANTPALM 0x00000002

#define TABLET_CONFIG_NONE 0x00000000 /**< The input digitizer does not have touch capabilities. */
#define NID_INTEGRATED_TOUCH 0x00000001    /**< An integrated touch digitizer is used for input. */
#define NID_EXTERNAL_TOUCH 0x00000002 /**< An external touch digitizer is used for input. */
#define NID_INTEGRATED_PEN 0x00000004 /**< An integrated pen digitizer is used for input. */
#define NID_EXTERNAL_PEN 0x00000008 /**< An external pen digitizer is used for input. */
#define NID_MULTI_INPUT 0x00000040 /**< An input digitizer with support for multiple inputs is used for input. */
#define NID_READY 0x00000080 /**< The input digitizer is ready for input. If this value is unset, it may mean that the tablet service is stopped, the digitizer is not supported, or digitizer drivers have not been installed. */

#define TOUCHEVENTF_MOVE 0x0001 /**< Movement has occurred. Cannot be combined with TOUCHEVENTF_DOWN. */
#define TOUCHEVENTF_DOWN 0x0002    /**< The corresponding touch point was established through a new contact. Cannot be combined with TOUCHEVENTF_MOVE or TOUCHEVENTF_UP. */
#define TOUCHEVENTF_UP 0x0004 /**< A touch point was removed. */
#define TOUCHEVENTF_INRANGE    0x0008 /**< A touch point is in range. This flag is used to enable touch hover support on compatible hardware. Applications that do not want support for hover can ignore this flag. */
#define TOUCHEVENTF_PRIMARY    0x0010 /**< Indicates that this TOUCHINPUT structure corresponds to a primary contact point. See the following text for more information on primary touch points. */
#define TOUCHEVENTF_NOCOALESCE 0x0020 /**< When received using GetTouchInputInfo, this input was not coalesced. */
#define TOUCHEVENTF_PALM 0x0080 /**< The touch event came from the user's palm. */

#define TOUCHINPUTMASKF_CONTACTAREA 0x0004 /**< cxContact and cyContact are valid. See the following text for more information on primary touch points. */
#define TOUCHINPUTMASKF_EXTRAINFO 0x0002 /**< dwExtraInfo is valid. */
#define TOUCHINPUTMASKF_TIMEFROMSYSTEM 0x0001 /**< The system time was set in the TOUCHINPUT structure. */

#define SM_DIGITIZER 94

#define WM_TOUCH 0x0240
#define WM_GESTURE 0x0119

#endif

#define TABLET_DISABLE_PRESSANDHOLD        0x00000001
#define TABLET_DISABLE_PENTAPFEEDBACK      0x00000008
#define TABLET_DISABLE_PENBARRELFEEDBACK   0x00000010
#define TABLET_DISABLE_TOUCHUIFORCEON      0x00000100
#define TABLET_DISABLE_TOUCHUIFORCEOFF     0x00000200
#define TABLET_DISABLE_TOUCHSWITCH         0x00008000
#define TABLET_DISABLE_FLICKS              0x00010000
#define TABLET_ENABLE_FLICKSONCONTEXT      0x00020000
#define TABLET_ENABLE_FLICKLEARNINGMODE    0x00040000
#define TABLET_DISABLE_SMOOTHSCROLLING     0x00080000
#define TABLET_DISABLE_FLICKFALLBACKKEYS   0x00100000
#define TABLET_ENABLE_MULTITOUCHDATA       0x01000000

#define MICROSOFT_TABLETPENSERVICE_PROPERTY     "MicrosoftTabletPenServiceProperty"

#if _MSC_VER < 1600

DECLARE_HANDLE(HTOUCHINPUT);


typedef struct _TOUCHINPUT {
    LONG      x;
    LONG      y;
    HANDLE    hSource;
    DWORD     dwID;
    DWORD     dwFlags;
    DWORD     dwMask;
    DWORD     dwTime;
    ULONG_PTR dwExtraInfo;
    DWORD     cxContact;
    DWORD     cyContact;
} TOUCHINPUT, *PTOUCHINPUT;


enum KzsWindowsFunctionStyle
{
    KZS_WINDOWS_FUNCTION_ANSI,
    KZS_WINDOWS_FUNCTION_UNICODE
};

#endif

extern BOOL (WINAPI *kzsWinapiCloseTouchInputHandle)(__in HTOUCHINPUT hTouchInput);
extern BOOL (WINAPI *kzsWinapiGetTouchInputInfo)(__in HTOUCHINPUT hTouchInput, __in UINT cInputs, __out PTOUCHINPUT pInputs, __in kzInt cbSize);
extern BOOL (WINAPI *kzsWinapiRegisterTouchWindow)(__in HWND hWnd, __in ULONG ulFlags);
extern HGLRC (WINAPI *kzsWglCreateContext)(HDC hdc);
extern BOOL (WINAPI *kzsWglMakeCurrent)(HDC hdc, HGLRC hglrc);
extern BOOL (WINAPI *kzsWglDeleteContext)(HGLRC hglrc);
extern kzInt (WINAPI *kzsWglChoosePixelFormat)(HDC hdc, const PIXELFORMATDESCRIPTOR *ppfd);
extern BOOL (WINAPI *kzsWglSetPixelFormat)(HDC hdc, kzInt iPixelFormat, const PIXELFORMATDESCRIPTOR *ppfd);
extern const kzByte* (WINAPI *kzsWin32GlGetString)(kzUint name);
extern PROC (WINAPI* kzsWglGetProcAddress)(LPCSTR name);
extern BOOL (WINAPI* kzsWglChoosePixelFormatARB)(HDC hdc, const kzInt *piAttribIList, const FLOAT *pfAttribFList, UINT nMaxFormats, kzInt *piFormats, UINT *nNumFormats);

/** Get the addresses of all necessary functions not visible in the basic WINAPI. */
kzBool kzsWindowsLoadFunctions(HMODULE* out_module);

/** Unload the specified module (hencefrom functions were loaded). */
kzBool kzsWindowsUnloadFunctions(HMODULE module);


KZ_HEADER_END


#endif
