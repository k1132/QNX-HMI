/**
* \file
* Math wrappers.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZS_MATH_H
#define KZS_MATH_H


#include <system/kzs_types.h>
#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>

#include <math.h>
#include <float.h> /*lint -efile(766,float.h) This file is referenced by macros. */
#include <limits.h> /*lint -efile(766,limits.h) This file is referenced by macros. */
#include <stdlib.h>


KZ_HEADER_BEGIN


/* Disable warnings of using same local variable name as math.h might declare as global on at least win32 platform. */
/*lint -esym(578,y1) */

/** Mathematical constant pi. */
#define KZS_PI 3.1415926536f
/** Mathematical constant e. */
#define KZS_E  2.7182818285f
/** Natural logarithm of 2. */
#define KZS_LN_2 0.6931471806f


#ifndef QNX
/** Largest value for a floating point number */
#define KZ_FLOAT_MAXIMUM FLT_MAX
/** Most negative value for a floating point number */
#define KZ_FLOAT_MINIMUM (-FLT_MAX)
/** Smallest normalized value larger than positive zero. */
#define KZ_FLOAT_SMALLEST_POSITIVE FLT_MIN
/** Smallest float such that 1.0f + KZ_FLOAT_EPSILON != 1.0f. */
#define KZ_FLOAT_EPSILON FLT_EPSILON 
#else
/** Defines for QCC compilation */
#define KZ_FLOAT_MAXIMUM 3.40282347e+38f
#define KZ_FLOAT_MINIMUM (-KZ_FLOAT_MAXIMUM)
#define KZ_FLOAT_SMALLEST_POSITIVE 1.17549435e-38f
#define KZ_FLOAT_EPSILON 1.1920929e-07f
#endif

/** Largest value for integer. */
#define KZ_INT_MAXIMUM INT_MAX
/** Smallest value for integer. */
#define KZ_INT_MINIMUM INT_MIN

/** Largest value for unsigned integer. */
#define KZ_UINT_MAXIMUM UINT_MAX
/** Smallest value for unsigned integer. */
#define KZ_UINT_MINIMUM 0

/** Largest value for 32-bit unsigned integer. */
#define KZ_UINT32_MAXIMUM (~(kzU32)0)
/** Smallest value for 32-bit unsigned integer. */
#define KZ_UINT32_MINIMUM ((kzU32)0)

/** Largest value for 64-bit unsigned integer. */
#define KZ_UINT64_MAXIMUM (~(kzU64)0)
/** Smallest value for 64-bit unsigned integer. */
#define KZ_UINT64_MINIMUM ((kzU64)0)

/** Used for keeping strict aliasing when interpreting kzU32 as kzFloat. */
union KZ_FLOAT_UNION_TYPE
{
    kzU32 u;   /**< Unsigned integer bits of the floating point value. */
    kzS32 s;   /**< Signed integer bits of the floating point value. */
    kzFloat f; /**< Floating point value. */
};

/** \see KZS_NAN */
extern const union KZ_FLOAT_UNION_TYPE KZS_NAN_PRIVATE;
/** \see KZS_INFINITY */
extern const union KZ_FLOAT_UNION_TYPE KZS_INFINITY_PRIVATE;

/** Floating point value for Not a Number. */
#define KZS_NAN /*lint -e(740)*/ (KZS_NAN_PRIVATE.f)

/** Floating point value for positive infinity. Negative infinity is -KZS_INFINITY. */
#define KZS_INFINITY /*lint -e(740)*/ (KZS_INFINITY_PRIVATE.f)

/** Returns KZ_TRUE if x is NaN. */
KZ_INLINE kzBool kzsIsNan(kzFloat x)
{
    static const kzU32 nanMask = 0x7FFFFFFF;
    static const kzU32 nanMinimum = 0x7F800001;
    union KZ_FLOAT_UNION_TYPE y;
    y.f = x;
    return (y.u & nanMask) >= nanMinimum;
}

/** Returns KZ_TRUE if x is positive infinity. */
KZ_INLINE kzBool kzsIsPositiveInfinity(kzFloat x)
{
    return x > KZ_FLOAT_MAXIMUM;
}

/** Returns KZ_TRUE if x is negative infinity. */
KZ_INLINE kzBool kzsIsNegativeInfinity(kzFloat x)
{
    return x < KZ_FLOAT_MINIMUM;
}

/** Returns KZ_TRUE if x is an infinity. */
KZ_INLINE kzBool kzsIsInfinity(kzFloat x)
{
    return kzsIsNegativeInfinity(x) || kzsIsPositiveInfinity(x);
}

/** Returns KZ_TRUE if x is the specific IEEE floating point negative infinity constant. */
KZ_INLINE kzBool kzsIsIEEENegativeInfinity(kzFloat x)
{
    return (x == -KZS_INFINITY); /*lint !e777 */
}

/** Returns KZ_TRUE if x is the specific IEEE floating point positive infinity constant. */
KZ_INLINE kzBool kzsIsIEEEPositiveInfinity(kzFloat x)
{
    return (x == KZS_INFINITY); /*lint !e777 */
}

/** Returns sine of given angle. */
KZ_INLINE kzFloat kzsSinf(kzFloat angleInRadians)
{
    return (kzFloat)sin((kzDouble)angleInRadians);
}

/** Returns cosine of given angle. */
KZ_INLINE kzFloat kzsCosf(kzFloat angleInRadians)
{
    return (kzFloat)cos((kzDouble)angleInRadians);
}

/** Returns inverse sine from floating point number between -1 and 1. */
KZ_INLINE kzFloat kzsAsinf(kzFloat x)
{
    return (kzFloat)asin((kzDouble)x);
}

/** Returns inverse cosine from floating point number between -1 and 1. */
KZ_INLINE kzFloat kzsAcosf(kzFloat x)
{
    return (kzFloat)acos((kzDouble)x);
}

/** Returns tangent of given angle. */
KZ_INLINE kzFloat kzsTanf(kzFloat angleInRadians)
{
    return (kzFloat)tan((kzDouble)angleInRadians);
}

/** Returns atan from floating point number. */
KZ_INLINE kzFloat kzsAtanf(kzFloat x)
{
    return (kzFloat)atan((kzDouble)x);
}

/** Returns atan2 from floating point number. */
KZ_INLINE kzFloat kzsAtan2f(kzFloat y, kzFloat x)
{
    return (kzFloat)atan2((kzDouble)y, (kzDouble)x);
}

/** Returns square root of given value. */
KZ_INLINE kzFloat kzsSqrtf(kzFloat value)
{
    return (kzFloat)sqrt((kzDouble)value);
}

/** Returns the signum of given value. */
KZ_INLINE kzFloat kzsSignf(kzFloat value)
{
    return (value < 0.0f) ? -1.0f : 1.0f;
}

/**
* Floating point remainder of value divided by divisor.
* The result may be negative for negative values.
*/
KZ_INLINE kzFloat kzsFmod(kzFloat value, kzFloat divisor)
{
    return (kzFloat)fmod((kzDouble)value, (kzDouble)divisor);
}

/** Breaks floating point number to integral and fractional part. Returns fractional part as return value and sets intPart to integral part. */
KZ_INLINE kzFloat kzsModf(kzFloat value, kzFloat* intPart)
{
    kzDouble intPartTemp;
    kzFloat result = (kzFloat)modf((kzDouble)value, &intPartTemp);
    *intPart = (kzFloat)intPartTemp;
    return result;
}

/**
 * Returns modulo dividend % divisor for signed numbers in a way that negative numbers are
 * treated as an extension instead of mirroring compared to positive numbers.
 * For example kzsRemainder(-16, 5) = 4
 */
KZ_INLINE kzUint kzsRemainder(kzInt dividend, kzUint divisor)
{
    kzInt remainder = dividend % (kzInt)divisor;
    
    if(remainder < 0)
    {
        remainder += (kzInt)divisor;
    }

    return (kzUint)remainder;
}

/** Same as kzsRemainder, but for floating point numbers.
*
* Results are undefined if divisor is not greater than zero. */
KZ_INLINE kzFloat kzsRemainderf(kzFloat dividend, kzFloat divisor)
{
    kzFloat remainder;

    kzsAssert(divisor > 0.0f);

    remainder = (kzFloat)fmod((kzDouble)dividend, (kzDouble)divisor);
    
    if(remainder < 0.0f)
    {
        remainder += divisor;
    }

    return remainder;
}

/** Raises 'value' to the power of 'exponent'. */
KZ_INLINE kzFloat kzsPowf(kzFloat value, kzFloat exponent)
{
    return (kzFloat)pow((kzDouble)value, (kzDouble)exponent);
}

/** Raises e (base of natural logarithm) to the power of 'value'. */
KZ_INLINE kzFloat kzsExpf(kzFloat value)
{
    return (kzFloat)exp((kzDouble)value);
}

/** Returns base 10 logarithm of given floating point value. */
KZ_INLINE kzFloat kzsLog10f(kzFloat value)
{
    return (kzFloat)log10((kzDouble)value);
}

/** Returns natural logarithm of given double value. */
KZ_INLINE kzDouble kzsLogE(kzDouble value)
{
    return (kzDouble)log(value);
}

/** Returns natural logarithm of given floating point value. */
KZ_INLINE kzFloat kzsLogEf(kzFloat value)
{
    return (kzFloat)log((kzDouble)value);
}

/** Returns the largest integer not greater than value as float. */
KZ_INLINE kzFloat kzsFloorf(kzFloat value)
{
    return (kzFloat)floor((kzDouble)value);
}

/** Returns the largest integer not greater than value as integer. */
KZ_INLINE kzInt kzsIFloorf(kzFloat value)
{
    kzInt intValue = (kzInt)value;
    return (kzFloat)intValue <= value ? intValue : intValue - 1;
}

/** Returns the floating point value rounded as per normal rounding rules. */
KZ_INLINE kzFloat kzsRoundf(kzFloat value)
{
    return (kzFloat)floor((kzDouble)(value + 0.5f));
}

/** Returns the smallest integer no less than value in float. */
KZ_INLINE kzFloat kzsCeilf(kzFloat value)
{
    return (kzFloat)ceil((kzDouble)value);
}

/** Returns the smallest integer no less than value in integer. */
KZ_INLINE kzInt kzsICeilf(kzFloat value)
{
    kzInt intValue = (kzInt)value;
    return (kzFloat)intValue >= value ? intValue : intValue + 1;
}

/** Returns absolute value from integer value. */
KZ_INLINE kzUint kzsAbs(kzInt value)
{
    return (kzUint)(value >= 0 ? value : -value);
}

/** Returns absolute value from floating point number. */
KZ_INLINE kzFloat kzsFabsf(kzFloat value)
{
    return (kzFloat)fabs((kzDouble)value);
}

/** Clamps float value to given range */
KZ_INLINE kzFloat kzsClampf(kzFloat value, kzFloat minimum, kzFloat maximum)
{
    kzsAssert(maximum >= minimum);
    return (value <= minimum) ? minimum : ((value >= maximum) ? maximum : value);
}

/** Clamps integer value to given range */
KZ_INLINE kzInt kzsClampi(kzInt value, kzInt minimum, kzInt maximum)
{
    kzsAssert(maximum >= minimum);
    return (value <= minimum) ? minimum : ((value >= maximum) ? maximum : value);
}

/** Clamps unsigned integer value to given range */
KZ_INLINE kzUint kzsClampui(kzUint value, kzUint minimum, kzUint maximum)
{
    kzsAssert(maximum >= minimum);
    return (value <= minimum) ? minimum : ((value >= maximum) ? maximum : value);
}

/** Linearly interpolate between [a,b] where t should be in range [0,1]. */
KZ_INLINE kzFloat kzsLerpf(kzFloat minimum, kzFloat maximum, kzFloat t)
{
    kzsAssert(maximum >= minimum);
    return minimum + t * (maximum - minimum);
}

/** Converts degrees to radians. */
KZ_INLINE kzFloat kzsDegreesToRadians(kzFloat angleInDegrees)
{
    return angleInDegrees * KZS_PI / 180.0f;
}

/** Converts radians to degrees. */
KZ_INLINE kzFloat kzsRadiansToDegrees(kzFloat angleInRadians)
{
    return angleInRadians * 180.0f / KZS_PI;
}

/* Non-standard library functions */

/** Check whether value is in [min, max] (an interval inclusive of the limit points) */
KZ_INLINE kzBool kzsIsInClosedInterval(kzFloat value, kzFloat minimum, kzFloat maximum)
{
    kzsAssert(maximum >= minimum);
    return (value >= minimum) && (value <= maximum);
}

/** Check if two floats are equal. */
KZ_INLINE kzBool kzsFloatIsEqual(kzFloat valueA, kzFloat valueB)
{
    /* The following comparison ensures that kzsFloatIsEqual(-0.0f, 0.0f) == KZ_TRUE. */
    return valueA == valueB; /*lint !e777 */
}

/** Check if two IEEE 754 binary32 floats are equal up to a given number of ulps. */
KZ_INLINE kzBool kzsFloatIsAlmostEqualUlps(kzFloat valueA, kzFloat valueB, kzUint maxUlps)
{
    kzBool result = KZ_FALSE;
    union KZ_FLOAT_UNION_TYPE bitsA;
    union KZ_FLOAT_UNION_TYPE bitsB;
    kzInt intA;
    kzInt intB;
    kzUint intDiff;

    /* This function assumes IEEE 754 binary32 floating point representation. */
    kzsAssert(sizeof(kzS32) == sizeof(kzFloat));

    /* Convert to integer representation. */
    bitsA.f = valueA;
    bitsB.f = valueB;
    intA = (kzInt)bitsA.s;
    intB = (kzInt)bitsB.s;

    /* Make lexicographically ordered as a twos-complement int. */
    if (intA < 0)
    {
        intA = KZ_INT_MINIMUM - intA;
    }

    if (intB < 0)
    {
        intB = KZ_INT_MINIMUM - intB;
    }

    intDiff = kzsAbs(intA - intB);
    if (intDiff <= maxUlps)
    {
        result = KZ_TRUE;
    }

    return result;
}

/** Check if two floats are equal up to a given difference. */
KZ_INLINE kzBool kzsFloatIsAlmostEqualAbsolute(kzFloat valueA, kzFloat valueB, kzFloat maxAbsoluteDifference)
{
    kzBool result = KZ_FALSE;

    kzFloat diff = kzsFabsf(valueA - valueB);
    if (diff <= maxAbsoluteDifference)
    {
        result = KZ_TRUE;
    }

    return result;
}

/** Check if two floats are equal up to a given difference scaled by the larger value. */
KZ_INLINE kzBool kzsFloatIsAlmostEqualRelative(kzFloat valueA, kzFloat valueB, kzFloat maxRelativeDifference)
{
    kzBool result = KZ_FALSE;
    kzFloat largest;

    kzFloat diff = kzsFabsf(valueA - valueB);

    valueA = kzsFabsf(valueA);
    valueB = kzsFabsf(valueB);

    largest = (valueB > valueA) ? valueB : valueA;

    if (diff <= largest * maxRelativeDifference)
    {
        result = KZ_TRUE;
    }

    return result;
}

/** Check if two floats are approximately equal. */
KZ_INLINE kzBool kzsFloatIsAlmostEqual(kzFloat valueA, kzFloat valueB)
{
    kzBool result = KZ_FALSE;

    if (kzsFloatIsEqual(valueA, valueB))
    {
        /* Assures that values are almost equal whenever they are equal. */
        result = KZ_TRUE;
    }
    else if (kzsFloatIsAlmostEqualAbsolute(valueA, valueB, KZ_FLOAT_EPSILON))
    {
        /* Absolute comparison should work well with denormal numbers. */
        result = KZ_TRUE;
    }
    else if (kzsFloatIsAlmostEqualUlps(valueA, valueB, 4))
    {
        /* OpenCL specifies 4 ulps as the worst acceptable tolerance for many functions. */
        result = KZ_TRUE;
    }

    return result;
}

/** Check whether value in (min, max) (an interval range exclusive of the limit points)  */
KZ_INLINE kzBool kzsIsInOpenInterval(kzFloat value, kzFloat minimum, kzFloat maximum)
{
    kzsAssert(maximum >= minimum);
    return (value > minimum) && (value < maximum);
}

/** Returns the smaller of two integers. */
KZ_INLINE kzInt kzsMin(kzInt a, kzInt b)
{
    return (a < b) ? a : b;
}

/** Returns the greater of two integers. */
KZ_INLINE kzInt kzsMax(kzInt a, kzInt b)
{
    return (a > b) ? a : b;
}

/** Returns the smaller of two unsigned integers. */
KZ_INLINE kzUint kzsMinU(kzUint a, kzUint b)
{
    return (a < b) ? a : b;
}

/** Returns the greater of two unsigned integers. */
KZ_INLINE kzUint kzsMaxU(kzUint a, kzUint b)
{
    return (a > b) ? a : b;
}

/** Returns the smaller of two floats. */
KZ_INLINE kzFloat kzsMinf(kzFloat a, kzFloat b)
{
    return (a < b) ? a : b;
}

/** Returns the greater of two floats. */
KZ_INLINE kzFloat kzsMaxf(kzFloat a, kzFloat b)
{
    return (a > b) ? a : b;
}

/**
* Returns the step function of two integers.
* \return 1 if b >= a, 0 otherwise.
*/
KZ_INLINE kzInt kzsStep(kzInt a, kzInt b)
{
    return (a > b) ? 0 : 1;
}

/**
* Returns the step function of two unsigned integers.
* \return 1 if b >= a, 0 otherwise.
*/
KZ_INLINE kzUint kzsStepU(kzUint a, kzUint b)
{
    return (a > b) ? 0 : 1;
}

/**
* Returns the step function of two floats.
* \return 1.0f if b >= a, 0.0f otherwise.
*/
KZ_INLINE kzFloat kzsStepf(kzFloat a, kzFloat b)
{
    return (a > b) ? 0.0f : 1.0f;
}

/** Sorts values in buffer using quick sort. */
KZ_INLINE void kzsQsort(void* buffer, kzUint itemCount, kzUint itemSize, kzInt (*comparator)(const void* left, const void* right))
{
    qsort(buffer, itemCount, itemSize, comparator);
}

/** Casts a float to unsigned int. */
KZ_INLINE kzUint kzsFloatToUint(kzFloat value)
{
    return (kzUint)(kzInt)value; /* Direct casting of float to unsigned integer is problematic on some platforms. */
}

/** Casts an unsigned int to float. */
KZ_INLINE kzFloat kzsUintToFloat(kzUint value)
{
    return (kzFloat)(kzInt)value; /* Direct casting of float to unsigned integer is problematic on some platforms. */
}

/** Rounds a float to the nearest integer. */
KZ_INLINE kzInt kzsFloatRoundToInt(kzFloat value)
{
    return (kzInt)kzsFloorf(value + 0.5f);
}

/** Rounds a float to the nearest unsigned integer. */
KZ_INLINE kzUint kzsFloatRoundToUint(kzFloat value)
{
    return kzsFloatToUint(kzsFloorf(value + 0.5f));
}

/** Swaps two arbitrary elements of arbitrary size. */
KZ_INLINE void kzsSwap(void* element1, void* element2, kzUint elementSize)
{
    kzUint bytesLeft = elementSize;
    kzUint offset = 0;

    while (bytesLeft >= sizeof(void*))
    {
        void* temp = *((void**)element1 + offset);
        *((void**)element1 + offset) = *((void**)element2 + offset);
        *((void**)element2 + offset) = temp;
        ++offset;
        bytesLeft -= sizeof(void*);
    }

    offset *= sizeof(void*);

    while (bytesLeft > 0)
    {
        kzU8 temp = *((kzU8*)element1 + offset);
        *((kzU8*)element1 + offset) = *((kzU8*)element2 + offset);
        *((kzU8*)element2 + offset) = temp;
        ++offset;
        --bytesLeft;
    }
}


KZ_HEADER_END


#endif
