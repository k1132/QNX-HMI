/**
* \file
* Equation solving utilities.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZC_SOLVE_H
#define KZC_SOLVE_H


#include <system/wrappers/kzs_math.h>
#include <system/kzs_types.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/**
 * Solves a first-order equation pair.
 *
 * The equations would be in the form:
 * a + xb + yc = 0
 * d + xe + yf = 0
 * abcdef are known, solve x and y.
 */
kzBool kzcSolveFirstOrderFunctionPair(kzFloat a, kzFloat b, kzFloat c, kzFloat d, kzFloat e, kzFloat f, kzFloat* out_x, kzFloat* out_y);

/**
* Solves a quadratic of form x^2 + P x + Q = 0. Avoids losing precision unnecessarily.
*
* If there are no solutions, out_solutions will be KZ_FALSE.
* Otherwise, out_solution1 will be the smaller solution and out_solution2 will be the greater solution.
*/
KZ_INLINE void kzcSolveNormalizedQuadratic(kzFloat P, kzFloat Q, kzBool* out_solutions, kzFloat* out_solution1, kzFloat* out_solution2)
{
    kzFloat D; /* Discriminant. */

    /* Represent equation as  x^2 - 2 P x + Q = 0. */
    P *= -0.5f;

    /* Check discriminant. */
    D = P * P - Q;
    if (D < 0.0f)
    {
        *out_solutions = KZ_FALSE;
    }
    else
    {
        /* Avoid losing precision to subtraction. */
        if (P >= 0.0f)
        {
            kzFloat solution = P + kzsSqrtf(D);
            *out_solution1 = Q / solution;
            *out_solution2 = solution;
        }
        else
        {
            kzFloat solution = P - kzsSqrtf(D);
            *out_solution1 = solution;
            *out_solution2 = Q / solution;
        }
        *out_solutions = KZ_TRUE;
    }
}

/**
* Solves a quadratic of form Ax^2 + Bx + C = 0. Avoids losing precision unnecessarily.
*
* If there are no solutions, out_solutions will be KZ_FALSE.
* Otherwise, out_solution1 will be the smaller solution and out_solution2 will be the greater solution.
*/
KZ_INLINE void kzcSolveQuadratic(kzFloat A, kzFloat B, kzFloat C, kzBool* out_solutions, kzFloat* out_solution1, kzFloat* out_solution2)
{
    kzcSolveNormalizedQuadratic(B / A, C / A, out_solutions, out_solution1, out_solution2);
}


KZ_HEADER_END


#endif
