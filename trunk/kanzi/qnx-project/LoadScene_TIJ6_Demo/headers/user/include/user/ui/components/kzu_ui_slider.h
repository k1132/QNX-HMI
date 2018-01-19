/**
* \file
* User interface slider.
*
* KzuUiSlider is a layout that works with two children, a rail and a knob, which are the first and second child respectively.
* Normally the Kanzi Studio creates these children automatically as empty nodes, and other objects can then be set as
* children of these empty nodes.
* The knob moves along a user-specified axis, it is the KzuUiSlider user's job to make it look like it moves along the rail.
*
* Slider Messages
* ----
* ::KZU_MESSAGE_SLIDER_VALUE_CHANGED message is sent whenever the slider's value changes. It has one float argument ::KZU_MESSAGE_ARGUMENT__SLIDER__VALUE
* telling the slider's current value.
*
* ::KZU_MESSAGE_SLIDER_DRAG_STARTED message is sent when the user starts to drag the slider. It has one float argument ::KZU_MESSAGE_ARGUMENT__SLIDER__VALUE
* telling the slider's current value.
*
* ::KZU_MESSAGE_SLIDER_DRAG_FINISHED message is sent when the user stops dragging the slider. It has one float argument ::KZU_MESSAGE_ARGUMENT__SLIDER__VALUE
* telling the slider's current value.
*
* The slider handles ::KZU_MESSAGE_SLIDER_INCREASE_VALUE message with one float argument ::KZU_MESSAGE_ARGUMENT__SET_PROPERTY__FLOAT_VALUE that is
* added to the slider's current value.
*
* The slider handles ::KZU_MESSAGE_SLIDER_DECREASE_VALUE message with one float argument ::KZU_MESSAGE_ARGUMENT__SET_PROPERTY__FLOAT_VALUE that is
* subtracted from the slider's current value.
*
* The slider handles ::KZU_MESSAGE_SLIDER_SET_VALUE message with one float argument ::KZU_MESSAGE_ARGUMENT__SET_PROPERTY__FLOAT_VALUE that will be set
* as the slider's current value.
*
* Slider Properties
* ----
* ::KZU_PROPERTY_TYPE_SLIDER_DIRECTION integer property can be set to change the movement axis of the slider. The value should be one of the values
* in ::KzuUiSliderDirection. The default value is ::KZU_UI_SLIDER_DIRECTION_X.
*
* ::KZU_PROPERTY_TYPE_SLIDER_EXPAND_DIRECTION integer property can be set to expand the input sensitive area of the slider. The value should be one of the values
* in ::KzuUiSliderExpandDirection. If the value specifies an axis, that axis' coordinate is assumed to always hit the slider in input events.
*
* ::KZU_PROPERTY_TYPE_SLIDER_MINIMUM_VALUE float property specifies the minimum slider value. The default value is 0.
*
* ::KZU_PROPERTY_TYPE_SLIDER_MAXIMUM_VALUE float property specifies the minimum slider value. The default value is 1.
*
* ::KZU_PROPERTY_TYPE_SLIDER_VALUE float property specifies the slider's value. It should be between the values of ::KZU_PROPERTY_TYPE_SLIDER_MINIMUM_VALUE and
* ::KZU_PROPERTY_TYPE_SLIDER_MAXIMUM_VALUE properties. The default value is 0.5.
* The property is changed by the slider itself when the knob is dragged but it can also be changed by the user.
*
* ::KZU_PROPERTY_TYPE_SLIDER_INVERT_DIRECTION Boolean property can be set to swap the slider's minimum and maximum ends. The default value is ::KZ_FALSE.
*
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_UI_SLIDER_H
#define KZU_UI_SLIDER_H


#include <user/scene_graph/kzu_object_common.h>

#include <system/kzs_types.h>
#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations. */
struct KzcMemoryManager;
struct KzcHashMap;
struct KzuUiComponentNode;
struct KzuPropertyManager;
struct KzuMessageDispatcher;
struct KzuFactory;
struct KzuUIDomain;


/**
 * \struct KzuUiSlider
 * Slider user interface component. Can be used for controlling a value.
 */
struct KzuUiSlider;


/** Object type for Slider. */
extern const KzuObjectType KZU_OBJECT_TYPE_UI_SLIDER;


/** Slider direction. */
enum KzuUiSliderDirection
{
    KZU_UI_SLIDER_DIRECTION_X = 0, /**< Slider direction X. */
    KZU_UI_SLIDER_DIRECTION_Y = 1, /**< Slider direction Y. */
    KZU_UI_SLIDER_DIRECTION_Z = 2 /**< Slider direction Z. */
};

/** Slider expand direction. */
enum KzuUiSliderExpandDirection
{
    KZU_UI_SLIDER_EXPAND_DIRECTION_X = 0, /**< Slider expand direction X. */
    KZU_UI_SLIDER_EXPAND_DIRECTION_Y = 1, /**< Slider expand direction Y. */
    KZU_UI_SLIDER_EXPAND_DIRECTION_Z = 2, /**< Slider expand direction Z. */
    KZU_UI_SLIDER_EXPAND_DIRECTION_ONLY_SLIDER_DIRECTION = 3, /**< Slider expand only in direction of sliders movement. */
    KZU_UI_SLIDER_EXPAND_DIRECTION_NONE = 4 /**< Slider does not expand on drag. */
};


/** Creates a slider with default settings. */
kzsError kzuUiSliderCreate(const struct KzcMemoryManager* memoryManager, kzString name,
                           struct KzuUIDomain* uiDomain, struct KzuUiSlider** out_slider);

/** Registers component type to factory. */
kzsError kzuUiSliderRegisterToFactory(const struct KzuFactory* factory);

/** Casts to UiComponentNode. */
struct KzuUiComponentNode* kzuUiSliderToUiComponentNode(const struct KzuUiSlider* slider);

/** Casts to UiSlider. */
struct KzuUiSlider* kzuUiSliderFromUiComponentNode(const struct KzuUiComponentNode* component);


/** Sets the slider value. The given value should be in range [0.0, 1.0], i.e. the the slider bounds and direction are ignored. Also sends a slider value changed message. */
kzsError kzuUiSliderSetValueExternal(const struct KzuUiSlider* slider, kzFloat value);

/** Gets the empty object node under which the slider knob must be placed. */
struct KzuObjectNode* kzuUiSliderGetKnob(const struct KzuUiSlider* slider);

/** Gets the empty object node under which the slider rail must be placed. */
struct KzuObjectNode* kzuUiSliderGetBar(const struct KzuUiSlider* slider); 

/** Gets slider value. */
kzFloat kzuUiSliderGetValue(const struct KzuUiSlider* slider);
/** Sets the slider value. The given value should be in range [Slider Minimum Value, Slider Maximum Value]. */
kzsError kzuUiSliderSetValue(const struct KzuUiSlider* slider, kzFloat value); 

/** Gets slider expand direction on drag. This is the hidden axis where the objects collision box is expanded when user drags slider. */
enum KzuUiSliderExpandDirection kzuUiSliderGetExpandOnDragDirection(const struct KzuUiSlider* slider);
/** Sets slider expand direction on drag. This is the hidden axis where the objects collision box is expanded when user drags slider. */
kzsError kzuUiSliderSetExpandOnDragDirection(const struct KzuUiSlider* slider, enum KzuUiSliderExpandDirection direction); 

/** Gets slider direction. */
enum KzuUiSliderDirection kzuUiSliderGetDirection(const struct KzuUiSlider* slider);
/** Sets slider direction. */
kzsError kzuUiSliderSetDirection(const struct KzuUiSlider* slider, enum KzuUiSliderDirection direction); 


KZ_HEADER_END


#endif
