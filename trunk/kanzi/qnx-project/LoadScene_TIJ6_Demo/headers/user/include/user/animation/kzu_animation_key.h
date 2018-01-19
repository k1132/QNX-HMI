/**
* \file
* Single key frame of animation data.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_ANIMATION_KEY_H
#define KZU_ANIMATION_KEY_H


#include <core/util/math/kzc_vector2.h>

#include <system/kzs_types.h>
#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/** Used interpolation method for animation key frame. */
enum KzuAnimationInterpolation
{
    KZU_ANIMATION_INTERPOLATION_STEP,   /**< Interpolation step. */
    KZU_ANIMATION_INTERPOLATION_LINEAR, /**< Interpolation linear. */ 
    KZU_ANIMATION_INTERPOLATION_BEZIER, /**< Interpolation Bezier. */
    KZU_ANIMATION_INTERPOLATION_SMOOTHSTEP /**< Interpolation smoothstep. */ 
};

/** Key frame value source, in additional to regular timeline keyframes the value can be fetch from source/target value. */
enum KzuAnimationKeyValueSource
{
    KZU_ANIMATION_KEY_VALUE_SOURCE_TIMELINE, /**< Key frame value fetch from timeline. */
    KZU_ANIMATION_KEY_VALUE_SOURCE_ANIMATED_OBJECT_CURRENT_VALUE, /**< Key frame value fetch from animated object current value. */
    KZU_ANIMATION_KEY_VALUE_SOURCE_TARGET_OBJECT_CURRENT_VALUE /**< Key frame value fetch from target object current value. */
};


/* Forward declarations. */
struct KzcMatrix4x4;
struct KzcMemoryManager;
struct KzuPropertyManager;
struct KzuResource;
struct KzuTexture;


/**
 * \struct KzuAnimationKey
 * Animation key frame base class.
 */ 
struct KzuAnimationKey;

/**
 * \struct KzuAnimationKeyFloat
 * Float animation key.
 */
struct KzuAnimationKeyFloat;

/**
 * \struct KzuAnimationKeyFloatWithTangents
 * Animation key frame for Bezier and Hermite interpolation. 
 * Can hold tangents or Bezier control points.
 */ 
struct KzuAnimationKeyFloatWithTangents;

/**
 * \struct KzuAnimationKeyMatrix4x4
 * Animation key frame for matrix animations.
 */
struct KzuAnimationKeyMatrix4x4;

/**
 * \struct KzuAnimationKeyTexture
 * Animation key frame for texture animations. 
 */
struct KzuAnimationKeyTexture;


/** Creates animation key.
* \param memoryManager The memory manager to use.
* \param time The time when the animation has value 'value'.
* \param value The value the animation has at time 'time'.
* \param interpolation This must be ::KZU_ANIMATION_INTERPOLATION_STEP, ::KZU_ANIMATION_INTERPOLATION_LINEAR or ::KZU_ANIMATION_INTERPOLATION_SMOOTHSTEP.
* \param out_animationKey A pointer that is set to point to the new animation key.
* \return ::KZS_SUCCESS on success.
*/
kzsError kzuAnimationKeyFloatCreate(const struct KzcMemoryManager* memoryManager, kzFloat time, kzFloat value, 
                                    enum KzuAnimationInterpolation interpolation, struct KzuAnimationKeyFloat** out_animationKey);
/** Creates an animation key, which represents a point on a Bezier curve and up to two Bezier control points.
* The Bezier curve will go through the point (time, value). The 'inPoint' parameter defines a Bezier control point in case
* the animation key before 'time' also defines a Bezier point. Similarly, the 'outPoint' is used as an additional Bezier control
* point if there is a Bezier animation key after 'time'. 
*
* For example, if there are two Bezier animation keys A and B and A's 'time' (A_time) is smaller than B's 'time' (B_time), then
* A and B together define a cubic Bezier curve which starting point is (A_time, A_value), the first control point is
* (A_outPoint.data[0], A_outPoint.data[1]), the second control point is (B_inPoint.data[0], B_inPoint.data[1]) and the end point
* is (B_time, B_value). Now, if there is a third Bezier animation key C and C_time > B_time, then there would be another cubic
* Bezier curve defined by (B_time, B_value), (B_outPoint.data[0], B_outPoint.data[1]), (C_inPoint.data[0], C_inPoint.data[1]),
* and (C_time, C_value).
*
* If the animation key before 'time' is not of Bezier type, the animation value will transition linearly from that point to (time, value).
* Similarly, if the animation key after 'time' is not of Bezier type, the animation value will transition linearly from (time, value)
* to that point.
*
* \param memoryManager The memory manager to use.
* \param time The time when the curve has value 'value'.
* \param value The value the curve has at time 'time'.
* \param interpolation This must be ::KZU_ANIMATION_INTERPOLATION_BEZIER.
* \param inPoint A Bezier control point that is used in case there is a Bezier animation key before 'time'.
* \param outPoint A Bezier control point that is used in case there is a Bezier animation key after 'time'.
* \param out_animationKey A pointer that is set to point to the new animation key.
* \return ::KZS_SUCCESS on success.
*/
kzsError kzuAnimationKeyFloatWithTangentsCreate(const struct KzcMemoryManager* memoryManager, kzFloat time, kzFloat value, 
                                          enum KzuAnimationInterpolation interpolation, struct KzcVector2 inPoint, 
                                          struct KzcVector2 outPoint, struct KzuAnimationKeyFloatWithTangents** out_animationKey);

/** Creates new animation key for texture animation. */
kzsError kzuAnimationKeyTextureCreate(const struct KzcMemoryManager* memoryManager, kzFloat time, struct KzuTexture* outputTexture, 
                                      struct KzuAnimationKeyTexture** out_animationKeyTexture);

/** Creates animation key for matrix4x4 animation. */
kzsError kzuAnimationKeyMatrix4x4Create(const struct KzcMemoryManager* memoryManager, kzFloat time, const struct KzcMatrix4x4* outputMatrix,
                                        struct KzuAnimationKeyMatrix4x4** out_animationKeyMatrix);

/** Deallocates memory reserved for animation key. */
kzsError kzuAnimationKeyDelete(struct KzuAnimationKey* animationKey);

/** Gets time from a given KzuAnimationKey. */
kzFloat kzuAnimationKeyGetTime(const struct KzuAnimationKey* key);

/** Gets output value from a given KzuAnimationFloatKey. */
kzFloat kzuAnimationKeyFloatGetValue(const struct KzuAnimationKeyFloat* key);

/** Private function for setting value source for animation key frame. */
kzsError kzuAnimationKeySetValueSource_private(struct KzuAnimationKey* key, enum KzuAnimationKeyValueSource source, struct KzuResource* resource);
/** Gets value source from animation key. */
enum KzuAnimationKeyValueSource kzuAnimationKeyGetValueSource(const struct KzuAnimationKey* key);

/** Sets value for animation key float. */
void kzuAnimationKeyFloatSetValue(struct KzuAnimationKeyFloat* key, kzFloat value);
/** Gets target object from key frame value source. */
struct KzuResource* kzuAnimationKeyGetValueSourceTargetObject(const struct KzuAnimationKey* key);

/** Sets target object path. */
kzsError kzuAnimationKeySetTargetObjectPath(struct KzuAnimationKey* key, enum KzuAnimationKeyValueSource source, kzString path);
/** Sets target object path. */
kzString kzuAnimationKeyGetTargetObjectPath(const struct KzuAnimationKey* key);

/** Type casts KzuAnimationKeyFloat to KzuAnimationKey. */
struct KzuAnimationKey* kzuAnimationKeyFloatToAnimationKey(const struct KzuAnimationKeyFloat* key);
/** Type casts KzuAnimationKeyFloat from KzuAnimationKey. */
struct KzuAnimationKeyFloat* kzuAnimationKeyFloatFromAnimationKey(const struct KzuAnimationKey* key);

/** Type casts KzuAnimationKeyFloatWithTangents to KzuAnimationKey. */
struct KzuAnimationKey* kzuAnimationKeyFloatWithTangentsToAnimationKey(const struct KzuAnimationKeyFloatWithTangents* key);
/** Type casts KzuAnimationKeyFloatWithTangents from KzuAnimationKey. */
struct KzuAnimationKeyFloatWithTangents* kzuAnimationKeyFloatWithTangentsFromAnimationKey(const struct KzuAnimationKey* key);

/** Type casts KzuAnimationKeyTexture to KzuAnimationKey. */
struct KzuAnimationKey* kzuAnimationKeyTextureToAnimationKey(const struct KzuAnimationKeyTexture* key);
/** Type casts KzuAnimationKeyTexture from KzuAnimationKey. */
struct KzuAnimationKeyTexture* kzuAnimationKeyToAnimationKeyTexture(const struct KzuAnimationKey* key);

/** Type casts KzuAnimationKeyMatrix4x4 to KzuAnimationKey. */
struct KzuAnimationKey* kzuAnimationKeyMatrix4x4ToAnimationKey(const struct KzuAnimationKeyMatrix4x4* key);
/** Type casts KzuAnimationKeyMatrix4x4 from KzuAnimationKey. */
struct KzuAnimationKeyMatrix4x4* kzuAnimationKeyToAnimationKeyMatrix4x4(const struct KzuAnimationKey* key);

/** Returns the output value from given point input, which is located between the two keys. */
kzFloat kzuAnimationKeyFloatInterpolate(kzFloat input, struct KzuAnimationKeyFloat* keyStart, 
                                                struct KzuAnimationKeyFloat* keyEnd);

/** Returns the interpolated output value from input point, which is between the given two keys. */
void kzuAnimationKeyMatrix4x4Interpolate(kzFloat input, const struct KzuAnimationKeyMatrix4x4* keyStart, 
                                                 const struct KzuAnimationKeyMatrix4x4* keyEnd, struct KzcMatrix4x4* out_matrix);

/** Returns the texture from given key frames. The interpolation is made with step interpolation. */
struct KzuTexture* kzuAnimationKeyTextureInterpolate(const struct KzuAnimationKeyTexture* keyStart, 
                                                             const struct KzuAnimationKeyTexture* keyEnd);

/** Returns linearly interpolated value between given two values. */
kzFloat kzuAnimationInterpolateLinear(kzFloat time, kzFloat startValue, kzFloat endValue, kzFloat startTime, kzFloat endTime);

/** Returns smoothstep interpolated value between given two values. */
kzFloat kzuAnimationInterpolateSmoothstep(kzFloat time, kzFloat startValue, kzFloat endValue, kzFloat startTime, kzFloat endTime);

/** Returns cubic Bezier interpolated value from given values. */
kzFloat kzuAnimationInterpolateBezier(kzFloat time, kzFloat startValue, kzFloat endValue, kzFloat startTime, kzFloat endTime, 
                                      const struct KzcVector2* outTangent, const struct KzcVector2* inTangent);

/** Returns hermite interpolated value from given values. */
kzFloat kzuAnimationInterpolateHermite(kzFloat time, kzFloat startValue, kzFloat endValue, kzFloat startTime, kzFloat endTime, 
                                       const struct KzcVector2* outTangent, const struct KzcVector2* inTangent);


KZ_HEADER_END


#endif
