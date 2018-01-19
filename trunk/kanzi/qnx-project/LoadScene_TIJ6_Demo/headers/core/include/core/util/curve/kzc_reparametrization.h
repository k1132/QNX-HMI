/**
* \file
* Implements curve reparametrization by curve length.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZC_REPARAMETRIZATION_H
#define KZC_REPARAMETRIZATION_H


#include <system/kzs_types.h>
#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations. */
struct KzcMemoryManager;
struct KzcSpline;

/**
* \struct KzcReparametrization
* Reparametrizes a curve by curve length.
*/
struct KzcReparametrization;


/** Creates a linear curve length reparametrization by curve length. */
kzsError kzcReparametrizationCreateLinear(const struct KzcMemoryManager* memoryManager, kzFloat curveLength,
                                          struct KzcReparametrization** out_reparametrization);

/**
* Creates a curve length reparametrization for a spline by sampling.
*
* First splits the curve into secant lines by sampling at 'minimumSamples' points. After that
* subdivides the secants as long as the relative error estimate is over 'relativeErrorMagnitude'
* and 'maximumSubdivisions' depth is not reached.
*/
kzsError kzcReparametrizationCreateFromSpline(const struct KzcMemoryManager* memoryManager,
                                              const struct KzcSpline* spline,
                                              kzUint minimumSamples, kzUint maximumSubdivisions, kzFloat relativeErrorMagnitude,
                                              struct KzcReparametrization** out_reparametrization);


/** Deletes a reparametrization. */
kzsError kzcReparametrizationDelete(struct KzcReparametrization* reparametrization);

/** Returns the phase that matches the given curve length in [0, length]. */
kzFloat kzcReparametrizationGetPhaseParameter(const struct KzcReparametrization* reparametrization, kzFloat lengthParameter);

/** Returns the curve length that matches the given phase in [0, 1]. */
kzFloat kzcReparametrizationGetLengthParameter(const struct KzcReparametrization* reparametrization, kzFloat phaseParamter);

/** Returns the curve length of the curve. */
kzFloat kzcReparametrizationGetCurveLength(const struct KzcReparametrization* reparametrization);


/**
* Returns number of sample points the reparametrization uses.
* Can in some cases be used as an approximation for complexity of the curve.
*/
kzUint kzcReparametrizationGetSampleCount(const struct KzcReparametrization* reparametrization);

/** Returns length parameter by index. */
kzFloat kzcReparametrizationGetLengthSampleByIndex(const struct KzcReparametrization* reparametrization, kzUint index);


KZ_HEADER_END


#endif
