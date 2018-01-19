/**
 * \file
 * Standard message types.
 * 
 * Copyright 2008-2014 by Rightware. All rights reserved.
 */
#ifndef KZU_GENERAL_MESSAGES_H
#define KZU_GENERAL_MESSAGES_H


#include <user/ui/message/kzu_message_type.h>

#include <system/kzs_types.h>
#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations */
struct KzcHashMap;
struct KzcMemoryManager;
struct KzuMessageType;
struct KzuObjectNode;


/*lint -esym(956, KZU_MESSAGE_*) Suppress warning of global non-const variables. */

/** Set Property Value. Sets a property value to a float property or a float attribute a structured property. */
extern const struct KzuMessageType* KZU_MESSAGE_SET_PROPERTY_VALUE;

/** Set Float Value in Property. Sets a float value to a float property or a float attribute a structured property. */
extern const struct KzuMessageType* KZU_MESSAGE_SET_FLOAT_PROPERTY;

/** Set Property Value. Sets a Boolean value to a Boolean property. */
extern const struct KzuMessageType* KZU_MESSAGE_SET_BOOLEAN_PROPERTY;

/** Toggle Boolean Property. Switches the value of Boolean property. */
extern const struct KzuMessageType* KZU_MESSAGE_TOGGLE_BOOLEAN_PROPERTY;

/** Set Property Value. Sets the value of a texture property. */
extern const struct KzuMessageType* KZU_MESSAGE_SET_TEXTURE_PROPERTY;

/** Play Animation. Creates a new dynamic animation entry to the background sequence of the active scene. */
extern const struct KzuMessageType* KZU_MESSAGE_ANIMATION_PLAYER_PLAY_ANIMATION;

/** Instantiate Prefab. Instantiates a prefab template to a child of a given target node. Becomes effectively the last child in the list. */
extern const struct KzuMessageType* KZU_MESSAGE_SCREEN_INSTANTIATE_PREFAB;

/** Remove Node. Removes node from scene graph. */
extern const struct KzuMessageType* KZU_MESSAGE_SCREEN_REMOVE_NODE;

/** Replace Node. Replaces given node with a prefab instance. */
extern const struct KzuMessageType* KZU_MESSAGE_SCREEN_REPLACE_NODE;

/** Preload Resources. Preloads all resources in given resource dictionaries. */
extern const struct KzuMessageType* KZU_MESSAGE_SCREEN_PRELOAD_RESOURCES;

/** Set Locale. Sets the currently active locale. */
extern const struct KzuMessageType* KZU_MESSAGE_SCREEN_SET_LOCALE;

/** Write Log. Write message into log. */
extern const struct KzuMessageType* KZU_MESSAGE_WRITE_LOG;

/** Scroll View: Set Scroll Target. Sets the scrolling target of the scroll view. */
extern const struct KzuMessageType* KZU_MESSAGE_SCROLL_VIEW_SET_SCROLL_TARGET;

/** Scroll View: Set Current Scroll. Sets the current scroll position of the scroll view. */
extern const struct KzuMessageType* KZU_MESSAGE_SCROLL_VIEW_SET_SCROLL;

/** State Manager: Go To State. Attempts to go to a state in a state manager. */
extern const struct KzuMessageType* KZU_MESSAGE_STATE_MANAGER_GO_TO_STATE;

/** State Manager: Go To Next Defined State. Attempts to go to a state that is defined after the current one in a state manager. */
extern const struct KzuMessageType* KZU_MESSAGE_STATE_MANAGER_GO_TO_NEXT_DEFINED_STATE;

/** State Manager: Go To Previous Defined State. Attempts to go to a state that is defined before the current one in a state manager. */
extern const struct KzuMessageType* KZU_MESSAGE_STATE_MANAGER_GO_TO_PREVIOUS_DEFINED_STATE;

/** Slider: Decrease Value. Decreases the value of the slider. Event handler argument: the amount to decrease the value. */
extern const struct KzuMessageType* KZU_MESSAGE_SLIDER_DECREASE_VALUE;

/** Slider: Increase Value. Increases the value of the slider. Event handler argument: the amount to increase the value. */
extern const struct KzuMessageType* KZU_MESSAGE_SLIDER_INCREASE_VALUE;

/** Slider: SetValue. Sets the value of the slider. Event handler argument: the new value to be used. */
extern const struct KzuMessageType* KZU_MESSAGE_SLIDER_SET_VALUE;

/** Toggle Button: Switch State. Toggles the state of the toggle button. */
extern const struct KzuMessageType* KZU_MESSAGE_TOGGLE_BUTTON_SWITCH_STATE;

/** Transition Layer: Start Transition. Starts a transition between layers. */
extern const struct KzuMessageType* KZU_MESSAGE_TRANSITION_LAYER_START_TRANSITION;

/** Locale Changed. Triggered when the active locale has been changed. */
extern const struct KzuMessageType* KZU_MESSAGE_SCREEN_LOCALE_CHANGED;

/** Preloading Of Resources Completed. Triggered when the loading of resources you selected in the Preload Resources action is completed. */
extern const struct KzuMessageType* KZU_MESSAGE_SCREEN_PRELOADING_OF_RESOURCES_COMPLETED;

/** Transition Layer: Transition Started. Transition has been started between layers. */
extern const struct KzuMessageType* KZU_MESSAGE_TRANSITION_LAYER_TRANSITION_STARTED;

/** Transition Layer: Transition Finished. Transition has been finished between layers. */
extern const struct KzuMessageType* KZU_MESSAGE_TRANSITION_LAYER_TRANSITION_FINISHED;

/** Scroll View: Scroll Started. Occurs when the scroll position of a scroll view starts changing. */
extern const struct KzuMessageType* KZU_MESSAGE_SCROLL_VIEW_SCROLL_STARTED;

/** Scroll View: Scroll Ended. Occurs when the scroll position of a scroll view stops changing. */
extern const struct KzuMessageType* KZU_MESSAGE_SCROLL_VIEW_SCROLL_FINISHED;

/** Scroll View: User Scroll Started. Occurs when the user starts scrolling a scroll view. */
extern const struct KzuMessageType* KZU_MESSAGE_SCROLL_VIEW_USER_SCROLL_STARTED;

/** Scroll View: User Scroll Ended. Occurs when the user stops scrolling a scroll view. */
extern const struct KzuMessageType* KZU_MESSAGE_SCROLL_VIEW_USER_SCROLL_FINISHED;

/** Scroll View: Scrolled. Occurs when the scroll position of a scroll view changes. */
extern const struct KzuMessageType* KZU_MESSAGE_SCROLL_VIEW_SCROLLED;

/** Scroll View: Snap Request. Occurs when a scroll view requests snapping target from hosting component. */
extern const struct KzuMessageType* KZU_MESSAGE_SCROLL_VIEW_SNAP_REQUEST;

/** List Box: Item Selected. Occurs when an item is selected. */
extern const struct KzuMessageType* KZU_MESSAGE_LIST_BOX_ITEM_SELECTED;

/** List Box: Item Visible. Occurs when an item becomes visible. */
extern const struct KzuMessageType* KZU_MESSAGE_LIST_BOX_ITEM_VISIBLE;

/** List Box: Item Hidden. Occurs when an item becomes hidden. */
extern const struct KzuMessageType* KZU_MESSAGE_LIST_BOX_ITEM_HIDDEN;

/** List Box: Target Changed. Occurs when list box gets a new target item. */
extern const struct KzuMessageType* KZU_MESSAGE_LIST_BOX_TARGET_CHANGED;

/** Slider: Value Changed. Occurs when the value of the slider is changed. Event handler argument: the new value of the slider. */
extern const struct KzuMessageType* KZU_MESSAGE_SLIDER_VALUE_CHANGED;

/** Slider: Drag Started. Occurs when the sliding event begins. Event handler argument: the first value of this slider event. */
extern const struct KzuMessageType* KZU_MESSAGE_SLIDER_DRAG_STARTED;

/** Slider: Drag Finished. Occurs when the sliding event ends. Event handler argument: the last value of the slider. */
extern const struct KzuMessageType* KZU_MESSAGE_SLIDER_DRAG_FINISHED;

/** State Manager: State Entered. Occurs when a state manager has entered a state. */
extern const struct KzuMessageType* KZU_MESSAGE_STATE_MANAGER_ENTERED_STATE;

/** State Manager: State Left. Occurs when a state manager has left a state. */
extern const struct KzuMessageType* KZU_MESSAGE_STATE_MANAGER_LEFT_STATE;

/** State Manager: Transition Started. Occurs when a state manager begins a transition to a state. */
extern const struct KzuMessageType* KZU_MESSAGE_STATE_MANAGER_TRANSITION_STARTED;

/** State Manager: Transition Finished. Occurs when a state manager finishes a transition to a state. */
extern const struct KzuMessageType* KZU_MESSAGE_STATE_MANAGER_TRANSITION_FINISHED;

/** Toggle Button: Toggled Off. Occurs when the toggle button is toggled off. */
extern const struct KzuMessageType* KZU_MESSAGE_TOGGLE_BUTTON_TOGGLED_OFF;

/** Toggle Button: Toggled On. Occurs when the toggle button is toggled on. */
extern const struct KzuMessageType* KZU_MESSAGE_TOGGLE_BUTTON_TOGGLED_ON;

/** Button: Toggle State. Occurs when the button's toggle state changes. */
extern const struct KzuMessageType* KZU_MESSAGE_BUTTON_TOGGLE_STATE;

/** Button: Down. Occurs when the button is pressed. */
extern const struct KzuMessageType* KZU_MESSAGE_BUTTON_DOWN;

/** Button: Click. Occurs when a finger is lifted on top of a button that was previously pressed and when a pressed button's repeat interval expires. */
extern const struct KzuMessageType* KZU_MESSAGE_BUTTON_CLICK;

/** Button: Cancel. Occurs when a finger is lifted outside of a button that was previously pressed. */
extern const struct KzuMessageType* KZU_MESSAGE_BUTTON_CANCEL;

/** Button: Enter. Occurs when a finger that presses a button enters the button's area. */
extern const struct KzuMessageType* KZU_MESSAGE_BUTTON_ENTER;

/** Button: Leave. Occurs when a finger that presses a button leaves the button's area. */
extern const struct KzuMessageType* KZU_MESSAGE_BUTTON_LEAVE;

/** Button: Long Press. Occurs when a long press on the button happens. */
extern const struct KzuMessageType* KZU_MESSAGE_BUTTON_LONG_PRESS;

/** Click. Occurs when the pointer is pressed and is released on top of the component and no other gesture has been recognized. */
extern const struct KzuMessageType* KZU_MESSAGE_CLICK;

/** Double Click. Occurs when the pointer is pressed and released twice within 250ms on top of the control and no other gesture has been recognized. */
extern const struct KzuMessageType* KZU_MESSAGE_MULTI_CLICK;

/** Click Begin. Occurs when the pointer is pressed down on top of the component. */
extern const struct KzuMessageType* KZU_MESSAGE_CLICK_BEGIN;

/** Click Cancel. Occurs when a started click cancels. This occurs, for example, when user pressed button down and slides finger away and releases press. */
extern const struct KzuMessageType* KZU_MESSAGE_CLICK_CANCEL;

/** Click Enter. Occurs when the pointer or touch enters the click manipulator. */
extern const struct KzuMessageType* KZU_MESSAGE_CLICK_ENTER;

/** Click Leave. Occurs when the pointer or touch leaves the click manipulator. */
extern const struct KzuMessageType* KZU_MESSAGE_CLICK_LEAVE;

/** Long Press. Occurs when the pointer is pressed down on the button and 500ms has been passed. */
extern const struct KzuMessageType* KZU_MESSAGE_LONG_PRESS;

/** Node Attached to Graph. Occurs when the node is initialized and attached to the scene graph, normally when the application is launched. */
extern const struct KzuMessageType* KZU_MESSAGE_ON_ATTACHED;

/** Drag and drop started. */
extern const struct KzuMessageType* KZU_MESSAGE_DRAG_AND_DROP_STARTED;

/** Drag and drop finished. */
extern const struct KzuMessageType* KZU_MESSAGE_DRAG_AND_DROP_FINISHED;

/** Drag and drop moved. */
extern const struct KzuMessageType* KZU_MESSAGE_DRAG_AND_DROP_MOVED;

/** Key down. */
extern const struct KzuMessageType* KZU_MESSAGE_KEY_DOWN;

/** Key up. */
extern const struct KzuMessageType* KZU_MESSAGE_KEY_UP;

/** Manipulator touch. */
extern const struct KzuMessageType* KZU_MESSAGE_MANIPULATOR_TOUCH_INSIDE;

/** Manipulator touch outside. */
extern const struct KzuMessageType* KZU_MESSAGE_MANIPULATOR_TOUCH_OUTSIDE;

/** Delete object node. */
extern const struct KzuMessageType* KZU_MESSAGE_OBJECT_DELETE;

/** Pan started. */
extern const struct KzuMessageType* KZU_MESSAGE_PAN_STARTED;

/** Pan finished. */
extern const struct KzuMessageType* KZU_MESSAGE_PAN_FINISHED;

/** Pan moved. */
extern const struct KzuMessageType* KZU_MESSAGE_PAN_MOVED;

/** Pinch started. */
extern const struct KzuMessageType* KZU_MESSAGE_PINCH_STARTED;

/** Pinch finished. */
extern const struct KzuMessageType* KZU_MESSAGE_PINCH_FINISHED;

/** Pinch moved. */
extern const struct KzuMessageType* KZU_MESSAGE_PINCH_MOVED;

/** Swipe. */
extern const struct KzuMessageType* KZU_MESSAGE_SWIPE;

/** Timeline entry started. */
extern const struct KzuMessageType* KZU_MESSAGE_TIMELINE_ENTRY_STARTED;

/** Timeline entry finished. */
extern const struct KzuMessageType* KZU_MESSAGE_TIMELINE_ENTRY_FINISHED;

/** Timeline entry has been progressed when active. */
extern const struct KzuMessageType* KZU_MESSAGE_TIMELINE_ENTRY_PROGRESSED;

/** Timeline entry has been played to the end. */
extern const struct KzuMessageType* KZU_MESSAGE_TIMELINE_ENTRY_PLAYED_TO_END;

/** Timer. */
extern const struct KzuMessageType* KZU_MESSAGE_TIMER;

/** Touch begin. */
extern const struct KzuMessageType* KZU_MESSAGE_TOUCH_BEGIN;

/** Touch end. */
extern const struct KzuMessageType* KZU_MESSAGE_TOUCH_END;

/** Touch cancel. */
extern const struct KzuMessageType* KZU_MESSAGE_TOUCH_CANCEL;

/** Touch moved. */
extern const struct KzuMessageType* KZU_MESSAGE_TOUCH_MOVE;

/** Preview camera system camera mode. */
extern const struct KzuMessageType* KZU_MESSAGE_PREVIEW_CAMERA_SYSTEM_SET_CAMERA_MODE;


/** Creates standard message types. */
kzsError kzuGeneralMessagesCreate(const struct KzcMemoryManager* memoryManager);


KZ_HEADER_END


#endif
