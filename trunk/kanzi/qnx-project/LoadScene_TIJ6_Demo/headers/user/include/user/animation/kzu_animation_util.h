/**
* \file
* Animation utilities
* Utility functions for specifying animations.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_ANIMATION_UTIL_H
#define KZU_ANIMATION_UTIL_H

#include <user/properties/kzu_property_common.h>

#include "kzu_animation_key.h"

#include <system/debug/kzs_error.h>
#include <system/kzs_types.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations. */
struct KzuAnimationItem;
struct KzuPropertyManager;
struct KzuPropertyType;
struct KzuUIDomain;
struct KzcColorRGBA;
struct KzcVector3;
struct KzcMatrix3x3;
struct KzcMatrix4x4;


/** Binary container type. */
enum KzuPropertyBinaryDataType
{
    KZU_BINARY_DATA_TYPE_FLOAT = 0,
    KZU_BINARY_DATA_TYPE_TEXTURE = 1,
    KZU_BINARY_DATA_TYPE_MATRIX4X4 = 2
};

/** Binary target attribute type. */
enum KzuPropertyBinaryTargetAttribute
{
    KZU_PROPERTY_BINARY_TARGET_ATTRIBUTE_TRANSLATION_X = 0,
    KZU_PROPERTY_BINARY_TARGET_ATTRIBUTE_TRANSLATION_Y = 1,
    KZU_PROPERTY_BINARY_TARGET_ATTRIBUTE_TRANSLATION_Z = 2,
    KZU_PROPERTY_BINARY_TARGET_ATTRIBUTE_SCALE_X = 3,
    KZU_PROPERTY_BINARY_TARGET_ATTRIBUTE_SCALE_Y = 4,
    KZU_PROPERTY_BINARY_TARGET_ATTRIBUTE_SCALE_Z = 5,
    KZU_PROPERTY_BINARY_TARGET_ATTRIBUTE_ROTATION_Z = 6,
    KZU_PROPERTY_BINARY_TARGET_ATTRIBUTE_ROTATION_Y = 7,
    KZU_PROPERTY_BINARY_TARGET_ATTRIBUTE_ROTATION_X = 8,
    KZU_PROPERTY_BINARY_TARGET_ATTRIBUTE_WHOLE_PROPERTY = 9,
    KZU_PROPERTY_BINARY_TARGET_ATTRIBUTE_COLOR_R = 10,
    KZU_PROPERTY_BINARY_TARGET_ATTRIBUTE_COLOR_G = 11,
    KZU_PROPERTY_BINARY_TARGET_ATTRIBUTE_COLOR_B = 12,
    KZU_PROPERTY_BINARY_TARGET_ATTRIBUTE_COLOR_A = 13,
    KZU_PROPERTY_BINARY_TARGET_ATTRIBUTE_VECTOR_X = 14,
    KZU_PROPERTY_BINARY_TARGET_ATTRIBUTE_VECTOR_Y = 15,
    KZU_PROPERTY_BINARY_TARGET_ATTRIBUTE_VECTOR_Z = 16,
    KZU_PROPERTY_BINARY_TARGET_ATTRIBUTE_VECTOR_W = 17
};


/** Creates target color animation item. */
kzsError kzuAnimationItemCreateColorAnimation(struct KzuUIDomain* uiDomain, kzString relativePath,
                                              const struct KzuPropertyType* propertyType,
                                              const struct KzcColorRGBA* colorStart, const struct KzcColorRGBA* colorEnd,
                                              kzFloat duration, enum KzuAnimationInterpolation interpolation,
                                              struct KzuAnimationItem** out_animationItem);

/** Creates vector3 animation item. */
kzsError kzuAnimationItemCreateVector3Animation(struct KzuUIDomain* uiDomain, kzString relativePath,
                                                const struct KzuPropertyType* propertyType,
                                                const struct KzcVector3* positionStart, const struct KzcVector3* positionEnd,
                                                kzFloat duration, enum KzuAnimationInterpolation interpolation,
                                                struct KzuAnimationItem** out_animationItem);

/** Creates target float animation item. */
kzsError kzuAnimationItemCreateFloatAnimation(struct KzuUIDomain* uiDomain, kzString relativePath,
                                              const struct KzuPropertyType* propertyType,
                                              kzFloat valueStart, kzFloat valueEnd,
                                              kzFloat duration, enum KzuAnimationInterpolation interpolation,
                                              struct KzuAnimationItem** out_animationItem);

/** Creates target matrix3x3 animation item. */
kzsError kzuAnimationItemCreateMatrix3x3Animation(struct KzuUIDomain* uiDomain, kzString relativePath,
                                                  const struct KzuPropertyType* propertyType,
                                                  const struct KzcMatrix3x3* valueStart, const struct KzcMatrix3x3* valueEnd,
                                                  kzFloat duration, enum KzuAnimationInterpolation interpolation,
                                                  struct KzuAnimationItem** out_animationItem);

/** Creates target matrix3x3 animation item. */
kzsError kzuAnimationItemCreateMatrix3x3AnimationSRT(struct KzuUIDomain* uiDomain, kzString relativePath,
                                                     const struct KzuPropertyType* propertyType,
                                                     const struct KzcVector2* scaleStart, kzFloat rotateStart, const struct KzcVector2* translationStart,
                                                     const struct KzcVector2* scaleEnd, kzFloat rotateEnd, const struct KzcVector2* translationEnd,
                                                     kzFloat duration, enum KzuAnimationInterpolation interpolation,
                                                     struct KzuAnimationItem** out_animationItem);

/** Creates target matrix4x4 animation item. */
kzsError kzuAnimationItemCreateMatrix4x4Animation(struct KzuUIDomain* uiDomain, kzString relativePath,
                                                  const struct KzuPropertyType* propertyType,
                                                  const struct KzcMatrix4x4* valueStart, const struct KzcMatrix4x4* valueEnd,
                                                  kzFloat duration, enum KzuAnimationInterpolation interpolation,
                                                  struct KzuAnimationItem** out_animationItem);

/** Creates target matrix4x4 animation item. */
kzsError kzuAnimationItemCreateMatrix4x4SRTAnimation(struct KzuUIDomain* uiDomain, kzString relativePath,
                                                     const struct KzuPropertyType* propertyType,
                                                     const struct KzcVector3* scaleStart, const struct KzcVector3* rotationStart, const struct KzcVector3* translationStart,
                                                     const struct KzcVector3* scaleEnd, const struct KzcVector3* rotationEnd, const struct KzcVector3* translationEnd,
                                                     kzFloat duration, enum KzuAnimationInterpolation interpolation,
                                                     struct KzuAnimationItem** out_animationItem);


/** Find out corresponding binary data type for binary target attribute. */
kzsError kzuPropertyBinaryTargetAttributeConvertToBinaryDataType(const struct KzuPropertyType* propertyType, 
                                                                 enum KzuPropertyBinaryTargetAttribute targetAttribute,
                                                                 enum KzuPropertyBinaryDataType* out_binaryDataType);

/** Find out corresponding target attribute for binary target attribute. */
kzsError kzuPropertyBinaryTargetAttributeConvertToTargetAttribute(const struct KzuPropertyType* propertyType,
                                                                  enum KzuPropertyBinaryTargetAttribute binaryTargetAttribute,
                                                                  enum KzuPropertyField* out_targetAttribute);


KZ_HEADER_END


#endif
