/**
* \file
* OpenVG base header.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZS_OPENVG_BASE_H
#define KZS_OPENVG_BASE_H


#include <system/kzs_types.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


#define KZ_OPENVG_NONE      0 /**< No OpenVG version specified. */
#define KZ_OPENVG_1_1       1 /**< OpenVG 1.1 version. */

#ifndef KZ_OPENVG_VERSION
#error KZ_OPENVG_VERSION undefined
#endif


/** Global variable for controlling if OpenVG calls are enabled. */
extern kzBool g_kzsEnableOpenVGCalls;


/** Macro to use for starting OpenVG calls to allow disabling them with a control flag. */
#define KZS_OPENVG_CALL_BEGIN \
    if(g_kzsEnableOpenVGCalls) { /*lint --e{904}*/

/** Macro to use for enging OpenVG calls to allow disabling them with a control flag. */
#define KZS_OPENVG_CALL_END \
    }

/** Macro to use for enging OpenVG calls with a return value to allow disabling them with a control flag. */
#define KZS_OPENVG_CALL_END_RETURN_VALUE(x) \
    } return x;


/** Sets OpenVG calls enabled / disabled. */
void kzsOpenVGCallsSetEnabled(kzBool enabled);
/** Checks if OpenVG calls are enabled. */
kzBool kzsOpenVGCallsIsEnabled(void);


KZ_HEADER_END


#endif
