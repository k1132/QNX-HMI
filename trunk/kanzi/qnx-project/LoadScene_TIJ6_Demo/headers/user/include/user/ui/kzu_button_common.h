/**
* \file
* Common button code. Shared between KzuUiButton, KzuUiToggleButton, KzuButtonLayer, KzuToggleButtonLayer.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_BUTTON_COMMON_H
#define KZU_BUTTON_COMMON_H

#include <user/scene_graph/kzu_object_common.h>
#include <user/layers/kzu_layer.h>

#include <core/util/math/kzc_vector2.h>
#include <core/util/math/kzc_vector3.h>

#include <system/kzs_types.h>
#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations. */
struct KzcMemoryManager;
struct KzcHashMap;
struct KzuObjectNode;
struct KzuUiComponentNode;
struct KzuMessageDispatcher;
struct KzuFactory;
struct KzuUIDomain;


/** ButtonCommon's private data struct that is stored in each button object */
struct KzuButtonCommonData
{
    struct KzuInputManipulator* clickManipulator; /**< click manipulator */
    struct KzuInputManipulator* multiClickManipulator; /**< multiclick manipulator */
    struct KzuInputManipulator* longPressManipulator; /**< long press manipulator */
    kzBool mouseDown; /**< Variable tracking the "mouse" button. */
    struct KzuObjectNode* objectNode;  /**< The object node. */
};


/** Initializer for a KzuLayer button. */
kzsError kzuButtonCommonInitialize2D(struct KzuObjectNode* button);
/** Uninitializer for a KzuLayer button. */
kzsError kzuButtonCommonUninitialize2D(struct KzuObjectNode* button);
/** Measure function for a KzuLayer button. */
kzsError kzuButtonCommonMeasure2D(struct KzuLayer* button, const struct KzcVector2* availableSize, struct KzcVector2* out_size);
/** Arrange function for a KzuLayer button. */
kzsError kzuButtonCommonArrange2D(struct KzuLayer* button);

/** Initializer for a KzuUiComponentNode button. */
kzsError kzuButtonCommonInitialize3D(struct KzuObjectNode* button);
/** Uninitializer for a KzuUiComponentNode button. */
kzsError kzuButtonCommonUninitialize3D(struct KzuObjectNode* button);
/** Measure function for a KzuUiComponentNode button. */
kzsError kzuButtonCommonMeasure3D(struct KzuUiComponentNode* button, struct KzcVector3* out_size);
/** Arrange function for a KzuUiComponentNode button. */
kzsError kzuButtonCommonArrange3D(struct KzuUiComponentNode* button);

/** OnAttached function for 3D. */
kzsError kzuButtonCommonOnAttached3D(struct KzuObjectNode* button, struct KzuButtonCommonData* data);
/** OnAttached function for 2D. */
kzsError kzuButtonCommonOnAttached2D(struct KzuObjectNode* button, struct KzuButtonCommonData* data);
/** OnDetached function for 3D. */
kzsError kzuButtonCommonOnDetached3D(struct KzuObjectNode* button, struct KzuButtonCommonData* data);
/** OnDetached function for 2D. */
kzsError kzuButtonCommonOnDetached2D(struct KzuObjectNode* button, struct KzuButtonCommonData* data);

/** Sets the current toggle state of the button. */
kzsError kzuButtonCommonSetToggleState(const struct KzuObjectNode* button, kzUint state);
/** Returns the current toggle state of the button. */
kzUint kzuButtonCommonGetToggleState(const struct KzuObjectNode* button);
/** Sets the number of toggle states the button has. Also resets the current toggle state to zero. */
kzsError kzuButtonCommonSetToggleStateCount(const struct KzuObjectNode* button, kzUint state);
/** Returns the number of toggle states the button has. */
kzUint kzuButtonCommonGetToggleStateCount(const struct KzuObjectNode* button);

/** Gets the long release interval property of a button. */
kzFloat kzuButtonCommonGetLongPressInterval(const struct KzuObjectNode* button);

/** Gets the repeat interval property of a button. */
kzFloat kzuButtonCommonGetRepeatInterval(const struct KzuObjectNode* button);


KZ_HEADER_END


#endif
