/**
 * \file
 * Color structure and operations.
 * 
 * Copyright 2008-2014 by Rightware. All rights reserved.
 */
#ifndef KZC_COLOR_H
#define KZC_COLOR_H


#include <system/wrappers/kzs_math.h>
#include <system/kzs_types.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/** Structure of 4-component RGBA color */
struct KzcColorRGBA
{
    kzFloat red;    /**< Red component      */
    kzFloat green;  /**< Green component    */
    kzFloat blue;   /**< Blue component     */
    kzFloat alpha;  /**< Alpha component    */
};



/** Constant invisible zero color. */
extern const struct KzcColorRGBA KZC_COLOR_BLACK_TRANSPARENT;
/** Constant zero color with full alpha. */
extern const struct KzcColorRGBA KZC_COLOR_BLACK;
/** Dark gray color. */
extern const struct KzcColorRGBA KZC_COLOR_DARK_GRAY;
/** Gray color. */
extern const struct KzcColorRGBA KZC_COLOR_GRAY;
/** White color. */
extern const struct KzcColorRGBA KZC_COLOR_WHITE;
/** Red color. */
extern const struct KzcColorRGBA KZC_COLOR_RED;
/** Green color. */
extern const struct KzcColorRGBA KZC_COLOR_GREEN;
/** Blue color. */
extern const struct KzcColorRGBA KZC_COLOR_BLUE;
/** Yellow color. */
extern const struct KzcColorRGBA KZC_COLOR_YELLOW;
/** Orange color. */
extern const struct KzcColorRGBA KZC_COLOR_ORANGE;
/** Lime color. */
extern const struct KzcColorRGBA KZC_COLOR_LIME;
/** Teal color. */
extern const struct KzcColorRGBA KZC_COLOR_TEAL;
/** Purple color. */
extern const struct KzcColorRGBA KZC_COLOR_PURPLE;
/** Pink color. */
extern const struct KzcColorRGBA KZC_COLOR_PINK;
/** Cyan color. */
extern const struct KzcColorRGBA KZC_COLOR_CYAN;


/** Sets a value for RGBA color. */
KZ_INLINE void kzcColorRGBASet(struct KzcColorRGBA* color, kzFloat red, kzFloat green, kzFloat blue, kzFloat alpha)
{
    color->red = red;
    color->green = green;
    color->blue = blue;
    color->alpha = alpha;
}

/** Scales color with given value */
KZ_INLINE void kzcColorRGBAScale(struct KzcColorRGBA* color, kzFloat scale)
{
    color->red *= scale;
    color->green *= scale;
    color->blue *= scale;
    color->alpha *= scale;
}

/** Copies color to other. */
KZ_INLINE void kzcColorRGBACopy(const struct KzcColorRGBA* sourceColor, struct KzcColorRGBA* destinationColor)
{
    destinationColor->red = sourceColor->red;
    destinationColor->green = sourceColor->green;
    destinationColor->blue = sourceColor->blue;
    destinationColor->alpha = sourceColor->alpha;
}

/** Adds color A to color B component-wise. */
KZ_INLINE void kzcColorRGBAAdd(const struct KzcColorRGBA* colorA, const struct KzcColorRGBA* colorB,
                               struct KzcColorRGBA* destinationColor)
{
    destinationColor->red = colorA->red + colorB->red;
    destinationColor->green = colorA->green + colorB->green;
    destinationColor->blue = colorA->blue + colorB->blue;
    destinationColor->alpha = colorA->alpha + colorB->alpha;
}

/** Adds scalar to a color. */
KZ_INLINE void kzcColorRGBAAddScalar(const struct KzcColorRGBA* color, kzFloat scalar, struct KzcColorRGBA* destinationColor)
{
    destinationColor->red = color->red + scalar;
    destinationColor->green = color->green + scalar;
    destinationColor->blue = color->blue + scalar;
    destinationColor->alpha = color->alpha + scalar;
}

/** Subtracts color A from color B component-wise. */
KZ_INLINE void kzcColorRGBASubtract(const struct KzcColorRGBA* colorA, const struct KzcColorRGBA* colorB,
                                    struct KzcColorRGBA* destinationColor)
{
    destinationColor->red = colorA->red - colorB->red;
    destinationColor->green = colorA->green - colorB->green;
    destinationColor->blue = colorA->blue - colorB->blue;
    destinationColor->alpha = colorA->alpha - colorB->alpha;
}

/** Subtracts a scalar from a color. */
KZ_INLINE void kzcColorRGBASubstractScalar(const struct KzcColorRGBA* color, kzFloat scalar, struct KzcColorRGBA* destinationColor)
{
    destinationColor->red = color->red - scalar;
    destinationColor->green = color->green - scalar;
    destinationColor->blue = color->blue - scalar;
    destinationColor->alpha = color->alpha - scalar;
}

/** Multiplies color A by color B component-wise. */
KZ_INLINE void kzcColorRGBAMultiply(const struct KzcColorRGBA* colorA, const struct KzcColorRGBA* colorB,
                                    struct KzcColorRGBA* destinationColor)
{
    destinationColor->red = colorA->red * colorB->red;
    destinationColor->green = colorA->green * colorB->green;
    destinationColor->blue = colorA->blue * colorB->blue;
    destinationColor->alpha = colorA->alpha * colorB->alpha;
}

/** Multiplies a color by a scalar. */
KZ_INLINE void kzcColorRGBAMultiplyScalar(const struct KzcColorRGBA* color, kzFloat scalar, struct KzcColorRGBA* destinationColor)
{
    destinationColor->red = color->red * scalar;
    destinationColor->green = color->green * scalar;
    destinationColor->blue = color->blue * scalar;
    destinationColor->alpha = color->alpha * scalar;
}

/** Divides color A by color B component-wise. */
KZ_INLINE void kzcColorRGBADivide(const struct KzcColorRGBA* colorA, const struct KzcColorRGBA* colorB, struct KzcColorRGBA* destinationColor)
{
    destinationColor->red = colorA->red / colorB->red;
    destinationColor->green = colorA->green / colorB->green;
    destinationColor->blue = colorA->blue / colorB->blue;
    destinationColor->alpha = colorA->alpha / colorB->alpha;
}

/** Divides a color by a scalar. */
KZ_INLINE void kzcColorRGBADivideScalar(const struct KzcColorRGBA* color, kzFloat scalar, struct KzcColorRGBA* destinationColor)
{
    destinationColor->red = color->red / scalar;
    destinationColor->green = color->green / scalar;
    destinationColor->blue = color->blue / scalar;
    destinationColor->alpha = color->alpha / scalar;
}

/** Finds modulo of division of color A by color B component-wise. */
KZ_INLINE void kzcColorRGBAModulo(const struct KzcColorRGBA* colorA, const struct KzcColorRGBA* colorB, struct KzcColorRGBA* destinationColor)
{
    destinationColor->red = kzsFmod(colorA->red, colorB->red);
    destinationColor->green = kzsFmod(colorA->green, colorB->green);
    destinationColor->blue = kzsFmod(colorA->blue, colorB->blue);
    destinationColor->alpha = kzsFmod(colorA->alpha, colorB->alpha);
}

/** Finds modulo of division of color by a scalar. */
KZ_INLINE void kzcColorRGBAModuloScalar(const struct KzcColorRGBA* color, kzFloat scalar, struct KzcColorRGBA* destinationColor)
{
    destinationColor->red = kzsFmod(color->red, scalar);
    destinationColor->green = kzsFmod(color->green, scalar);
    destinationColor->blue = kzsFmod(color->blue, scalar);
    destinationColor->alpha = kzsFmod(color->alpha, scalar);
}

/** Abs of a color. */
KZ_INLINE void kzcColorRGBAAbs(const struct KzcColorRGBA* color, struct KzcColorRGBA* out_color)
{
    out_color->red = kzsFabsf(color->red);
    out_color->green = kzsFabsf(color->green);
    out_color->blue = kzsFabsf(color->blue);
    out_color->alpha = kzsFabsf(color->alpha);
}

/** Ceil of a color. */
KZ_INLINE void kzcColorRGBACeil(const struct KzcColorRGBA* color, struct KzcColorRGBA* out_color)
{
    out_color->red = kzsCeilf(color->red);
    out_color->green = kzsCeilf(color->green);
    out_color->blue = kzsCeilf(color->blue);
    out_color->alpha = kzsCeilf(color->alpha);
}

/** Floor of a color. */
KZ_INLINE void kzcColorRGBAFloor(const struct KzcColorRGBA* color, struct KzcColorRGBA* out_color)
{
    out_color->red = kzsFloorf(color->red);
    out_color->green = kzsFloorf(color->green);
    out_color->blue = kzsFloorf(color->blue);
    out_color->alpha = kzsFloorf(color->alpha);
}

/** Round of a color. */
KZ_INLINE void kzcColorRGBARound(const struct KzcColorRGBA* color, struct KzcColorRGBA* out_color)
{
    out_color->red = kzsRoundf(color->red);
    out_color->green = kzsRoundf(color->green);
    out_color->blue = kzsRoundf(color->blue);
    out_color->alpha = kzsRoundf(color->alpha);
}

/** Square root of a color component-wise. */
KZ_INLINE void kzcColorRGBASqrt(const struct KzcColorRGBA* color, struct KzcColorRGBA* out_color)
{
    out_color->red = kzsSqrtf(color->red);
    out_color->green = kzsSqrtf(color->green);
    out_color->blue = kzsSqrtf(color->blue);
    out_color->alpha = kzsSqrtf(color->alpha);
}

/** Raises a color to power of 'exponent' component-wise. */
KZ_INLINE void kzcColorRGBAPow(const struct KzcColorRGBA* color, kzFloat exponent, struct KzcColorRGBA* out_color)
{
    out_color->red = kzsPowf(color->red, exponent);
    out_color->green = kzsPowf(color->green, exponent);
    out_color->blue = kzsPowf(color->blue, exponent);
    out_color->alpha = kzsPowf(color->alpha, exponent);
}

/** Returns new KzcColorRGBA according to r, g, b, a values. */
KZ_INLINE struct KzcColorRGBA kzcColorRGBA(kzFloat r, kzFloat g, kzFloat b, kzFloat a)
{
    struct KzcColorRGBA color;
    kzcColorRGBASet(&color, r, g, b, a);
    return color;
}

/** Returns the component maximum of two colors. */
KZ_INLINE struct KzcColorRGBA kzcColorRGBAMax(const struct KzcColorRGBA* colorA, const struct KzcColorRGBA* colorB)
{
    return kzcColorRGBA(kzsMaxf(colorA->red, colorB->red),
        kzsMaxf(colorA->green, colorB->green),
        kzsMaxf(colorA->blue, colorB->blue),
        kzsMaxf(colorA->alpha, colorB->alpha));
}

/** Returns the component minimum of two colors. */
KZ_INLINE struct KzcColorRGBA kzcColorRGBAMin(const struct KzcColorRGBA* colorA, const struct KzcColorRGBA* colorB)
{
    return kzcColorRGBA(kzsMinf(colorA->red, colorB->red),
        kzsMinf(colorA->green, colorB->green),
        kzsMinf(colorA->blue, colorB->blue),
        kzsMinf(colorA->alpha, colorB->alpha));
}

/** Returns the component-wise step() of two colors. */
KZ_INLINE struct KzcColorRGBA kzcColorRGBAStep(const struct KzcColorRGBA* colorA, const struct KzcColorRGBA* colorB)
{
    return kzcColorRGBA(kzsStepf(colorA->red, colorB->red),
        kzsStepf(colorA->green, colorB->green),
        kzsStepf(colorA->blue, colorB->blue),
        kzsStepf(colorA->alpha, colorB->alpha));
}


/** Compares if two colors are equal. */
kzBool kzcColorRGBAIsEqual(const struct KzcColorRGBA* color1, const struct KzcColorRGBA* color2);

/** Converts RGB color to HSL. */
void kzcColorRGBAToHSL(const struct KzcColorRGBA* color, kzFloat* out_hue, kzFloat* out_saturation, kzFloat* out_lightness);

/** Converts HSL to RGBA color. Alpha will be 1.0f. */
struct KzcColorRGBA kzcColorRGBAFromHSL(kzFloat hue, kzFloat saturation, kzFloat lightness);

/** Blends 2 colors, blend percentage clamped to [0, 1]. */
struct KzcColorRGBA kzcColorRGBABlend(const struct KzcColorRGBA* colorA, const struct KzcColorRGBA* colorB, kzFloat blendValue);

/** Interpolates 2 colors, gives an interpolated color. This function approaches colorB from colorA by stepping the individual components
    by interpolationValue. For example:
    colorA (1.0, 0.5, 0.0, 1.0), colorB (0.0, 1.0, 0.0, 1.0) with interpolationValue of 0.1 gives:
    result = (1.0 - 0.1, 0.5 + 0.1, 0.0 + 0.0, 1.0 + 0.0) = (0.9, 0.6, 0.0, 0.0).
    */
struct KzcColorRGBA kzcColorRGBAInterpolate(const struct KzcColorRGBA* colorA, const struct KzcColorRGBA* colorB, kzFloat interpolationValue);

/** Sets an individual component by index. Clamps the value to 0-1 range. */
void kzcColorRGBASetComponent(struct KzcColorRGBA* color, kzUint component, kzFloat value);


KZ_HEADER_END


#endif
