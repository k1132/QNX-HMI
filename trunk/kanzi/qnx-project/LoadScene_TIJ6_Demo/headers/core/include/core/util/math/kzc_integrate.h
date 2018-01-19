/**
* \file
* Integration tools.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZC_INTEGRATE_H
#define KZC_INTEGRATE_H


#include <system/kzs_types.h>
#include <system/kzs_header.h>
#include <system/debug/kzs_error.h>


KZ_HEADER_BEGIN


/**
* Integrates a variable whose derivative decays exponentially over a given time step.
*
* Updates 'value' and 'derivative' with their values after the given amount of time.
* Parameter halfLife is the half life of the derivative.
*
* Example:  Movement of value 'x' starts with speed 'v' and 'v' halves every 2 seconds.
* Solution: kzcIntegrateExponentialDecay(&x, &v, 2.0f, deltaTimeMs / 1000.0f);
*/
void kzcIntegrateExponentialDecay(kzFloat* value, kzFloat* derivative, kzFloat halfLife, kzFloat timeStep);


KZ_HEADER_END


#endif
