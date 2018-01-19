/**
 * \file
 * Input device handling. Keyboards, mice, touch screens, joysticks and similar devices.
 * 
 * Copyright 2008-2014 by Rightware. All rights reserved.
 */
#ifndef KZS_INPUT_H
#define KZS_INPUT_H


#include <system/kzs_types.h>
#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations. */
struct KzsWindow;
struct KzsEvent;
struct KzsEventQueue;
struct KzsEventQueueIterator;
struct KzsInputCursor;
struct KzsInputEventKey;
struct KzsInputEventPointer;
struct KzsInputEventTouch;
struct KzsWindowEventSimple;
struct KzsWindowEventResize;
struct KzsWindowEventOrientationChange;


/** List of window orientation. */
enum KzsWindowOrientation
{
    KZS_WINDOW_ORIENTATION_LANDSCAPE, /**< LANDSCAPE. */
    KZS_WINDOW_ORIENTATION_PORTRAIT, /**< PORTRAIT. */
    KZS_WINDOW_ORIENTATION_COUNT  /**< Last enum value for validation checks. */
};

/** Enumeration for different types of events. */
enum KzsEventType
{
    KZS_EVENT_NONE,                        /**< Should be handled as unused. */
    KZS_EVENT_KEY,                         /**< Key press or release. */
    KZS_EVENT_POINTER,                     /**< Pointer movement or press action. */
    KZS_EVENT_TOUCH,                       /**< Touch event. One finger or more. */
    KZS_EVENT_WINDOW_RESIZED,              /**< Window has been resized. */
    KZS_EVENT_WINDOW_FOCUS_LOST,           /**< Window has lost input focus but it may still be completely or partially visible. */
    KZS_EVENT_WINDOW_FOCUS_GAINED,         /**< Window has gained input focus and is fully visible. */
    KZS_EVENT_WINDOW_HIDDEN,               /**< Window has been minimized or completely hidden and/or a power saver or screen saver is enabled. Rendering should be disabled. */
    KZS_EVENT_WINDOW_RESOURCES_LOST,       /**< Window has lost the resources it has used. Application may need to be restarted or reinitialized. */
    KZS_EVENT_DISPLAY_ORIENTATION_CHANGED, /**< Display orientation has been changed. */
    KZS_EVENT_WINDOW_CLOSED,               /**< Window has been closed. */
    KZS_EVENT_APPLICATION_PAUSED,          /**< Application will be paused. */
    KZS_EVENT_APPLICATION_SUSPENDED,       /**< Application will be suspended by the operating system. */
    KZS_EVENT_APPLICATION_RESUMED,         /**< Application has been be resumed by the operating system. */
    KZS_EVENT_DEBUG_TOGGLE_HUD,            /**< Toggle HUD debug request. */
    KZS_EVENT_DEBUG_SET_HUD                /**< Set HUD debug request. */
};

/** Enumeration to select translation of events. */
enum KzsInputTranslation
{
    KZS_INPUT_TRANSLATE_NONE,                      /**< Do not translate anything, receive both touch and pointer events. */
    KZS_INPUT_TRANSLATE_POINTER_TO_TOUCH,          /**< Translate all pointer events to touch events. Disable pointer events. */
    KZS_INPUT_TRANSLATE_TOUCH_TO_POINTER,          /**< Translate all touch events to pointer events. Disable touch events. */
    KZS_INPUT_TRANSLATE_POINTER_TO_TOUCH_PRESERVE, /**< Translate all pointer events to touch events. Preserve pointer events. */
    KZS_INPUT_TRANSLATE_TOUCH_TO_POINTER_PRESERVE  /**< Translate all touch events to pointer events. Preserve pointer events. */
};

/** Enumeration for different states for a pointing device. */
enum KzsInputPointingDeviceState
{
    KZS_POINTING_DEVICE_STATE_DOWN, /**< Pressed. */
    KZS_POINTING_DEVICE_STATE_MOVE, /**< Pointer moved. Not all platforms support this, for example many touch screens. */
    KZS_POINTING_DEVICE_STATE_DRAG, /**< Pointer dragged. */
    KZS_POINTING_DEVICE_STATE_UP    /**< Released. */
};

/** Enumeration for the state of a single cursor (as opposed to the state of the whole device. */
enum KzsInputCursorState
{
    KZS_CURSOR_STATE_DOWN,       /**< First finger down. */
    KZS_CURSOR_STATE_STATIONARY, /**< First finger down. */
    KZS_CURSOR_STATE_MOVE,       /**< First finger down. */
    KZS_CURSOR_STATE_UP          /**< First finger down. */
};

/** Enumeration for different states for a touch device. */
enum KzsInputTouchState
{
    KZS_TOUCH_STATE_BEGIN,    /**< First finger down. */
    KZS_TOUCH_STATE_CONTINUE, /**< Gesture or touch event in progress. */
    KZS_TOUCH_STATE_END       /**< Last finger up. */
};

/** Orientation angles for pointing devices in degrees. */
enum KzsInputOrientation
{
    KZS_INPUT_ORIENTATION_ANGLE_0,  /**< 0 degrees. */
    KZS_INPUT_ORIENTATION_ANGLE_180 /**< 180 degrees. */
};

/** Enumeration for different states for a key device. */
enum KzsInputKeyDeviceState
{
    KZS_KEY_DEVICE_STATE_DOWN,  /**< Pressed. */
    KZS_KEY_DEVICE_STATE_UP,    /**< Released. */
    KZS_KEY_DEVICE_STATE_REPEAT /**< Key is being held. */
};


/** Iterator for event queues. */
struct KzsEventQueueIterator
{
    kzInt index;                       /**< Index to current event. */
    const struct KzsEventQueue* queue; /**< Queue to iterate in. */
};


#define KZS_POINTING_DEVICE_BUTTON_PRIMARY   (1)      /**< Primary pointer button, e.g. usually mouse left on Windows. */
#define KZS_POINTING_DEVICE_BUTTON_SECONDARY (1 << 1) /**< Secondary pointer button, e.g. usually mouse right on Windows. */
#define KZS_POINTING_DEVICE_BUTTON_TERTIARY  (1 << 2) /**< Tertiary pointer button, e.g. usually mouse middle on Windows. */
#define KZS_POINTING_DEVICE_BUTTON_ROLL_UP   (1 << 3) /**< Roll up pointer button. */
#define KZS_POINTING_DEVICE_BUTTON_ROLL_DOWN (1 << 4) /**< Roll down pointer button. */

/** Platform independent key enumeration */
enum KzsInputKey
{
        /* Unknown keys are used for unmapped keys. */
    KZS_KEY_UNKNOWN = 0,

        /* Keys used for numeric input */   
    KZS_KEY_0,
    KZS_KEY_1,
    KZS_KEY_2,
    KZS_KEY_3,
    KZS_KEY_4,
    KZS_KEY_5,
    KZS_KEY_6,
    KZS_KEY_7,
    KZS_KEY_8,
    KZS_KEY_9,
    KZS_KEY_COMMA,
    KZS_KEY_PERIOD,
    KZS_KEY_DECIMAL_SEPARATOR,      /**< allows for locale specific separator key mapping */
    KZS_KEY_THOUSANDS_SEPARATOR,    /**< allows for locale specific separator key mapping */

        /* Keys used for text input */
    KZS_KEY_A,
    KZS_KEY_B,
    KZS_KEY_C,
    KZS_KEY_D,
    KZS_KEY_E,
    KZS_KEY_F,
    KZS_KEY_G,
    KZS_KEY_H,
    KZS_KEY_I,
    KZS_KEY_J,
    KZS_KEY_K,
    KZS_KEY_L,
    KZS_KEY_M,
    KZS_KEY_N,
    KZS_KEY_O,
    KZS_KEY_P,
    KZS_KEY_Q,
    KZS_KEY_R,
    KZS_KEY_S,
    KZS_KEY_T,
    KZS_KEY_U,
    KZS_KEY_V,
    KZS_KEY_W,
    KZS_KEY_X,
    KZS_KEY_Y,
    KZS_KEY_Z,

    KZS_KEY_SPACE,
    KZS_KEY_BACKSPACE,
    KZS_KEY_ENTER,
    KZS_KEY_TAB,
    KZS_KEY_ESC,
    
    KZS_KEY_CAPS_LOCK,
    KZS_KEY_NUM_LOCK,
    KZS_KEY_PRINT_SCREEN,
    KZS_KEY_SCROLL_LOCK,
    KZS_KEY_BREAK,

    KZS_KEY_INSERT,
    KZS_KEY_DELETE,
    KZS_KEY_HOME,
    KZS_KEY_END,
    KZS_KEY_PAGE_UP,
    KZS_KEY_PAGE_DOWN,

    KZS_KEY_PLUS,
    KZS_KEY_MINUS,
    KZS_KEY_MULTIPLY,
    KZS_KEY_DIVIDE,

        /* Arrow keys for navigation (8-directional on some devices?) */
    KZS_KEY_ARROW_UP,
    KZS_KEY_ARROW_DOWN,
    KZS_KEY_ARROW_LEFT,
    KZS_KEY_ARROW_RIGHT,
    
        /* Numpad keys on a common IBM keyboard */
    KZS_KEY_NUM_0,
    KZS_KEY_NUM_1,
    KZS_KEY_NUM_2,
    KZS_KEY_NUM_3,
    KZS_KEY_NUM_4,
    KZS_KEY_NUM_5,
    KZS_KEY_NUM_6,
    KZS_KEY_NUM_7,
    KZS_KEY_NUM_8,
    KZS_KEY_NUM_9,
    KZS_KEY_NUM_DIVIDE,
    KZS_KEY_NUM_MULTIPLY,
    KZS_KEY_NUM_PLUS,
    KZS_KEY_NUM_MINUS,
    KZS_KEY_NUM_COMMA,
    KZS_KEY_NUM_ENTER,
    
        /* Function keys on a common IBM keyboard */
    KZS_KEY_F1,
    KZS_KEY_F2,
    KZS_KEY_F3,
    KZS_KEY_F4,
    KZS_KEY_F5,
    KZS_KEY_F6,
    KZS_KEY_F7,
    KZS_KEY_F8,
    KZS_KEY_F9,
    KZS_KEY_F10,
    KZS_KEY_F11,
    KZS_KEY_F12,

        /* Sound volume control keys */
    KZS_KEY_VOLUME_UP,
    KZS_KEY_VOLUME_DOWN,

        /* Unnamed buttons, usually on phones etc */
    KZS_KEY_SOFTKEY1,  
    KZS_KEY_SOFTKEY2,
    KZS_KEY_SOFTKEY3,
    KZS_KEY_SOFTKEY4,
    
        /* Generic names for modifier keys such as shift, ctrl, alt, Fn, command, super, etc. */
    KZS_KEY_MODIFIER1, 
    KZS_KEY_MODIFIER2,
    KZS_KEY_MODIFIER3,
    
        /* Specific modifier key names on a common IBM keyboard */
    KZS_KEY_RIGHT_ALT,
    KZS_KEY_RIGHT_CONTROL,
    KZS_KEY_RIGHT_SHIFT,
    KZS_KEY_RIGHT_WINDOWS_KEY,
    KZS_KEY_LEFT_ALT,
    KZS_KEY_LEFT_CONTROL,
    KZS_KEY_LEFT_SHIFT,
    KZS_KEY_LEFT_WINDOWS_KEY,
    KZS_KEY_MENU_KEY,
    
        /* Key names for Finnish 105-key IBM keyboard */
    KZS_KEY_SECTION,        /**< left of 1 */
    KZS_KEY_QUOTE,          /**< left of enter, below */
    KZS_KEY_LESS_THAN,      /**< left of Z */
    KZS_KEY_UMLAUT,         /**< left of enter, above */
    KZS_KEY_AUML,           /**< right of OUML */
    KZS_KEY_OUML,           /**< right of L */   
    KZS_KEY_ARING,          /**< right of P */
    KZS_KEY_ACCENT,          /**< left of backspace */

        /* Key names for game controller */
    KZS_KEY_BUTTON_A,
    KZS_KEY_BUTTON_B,
    KZS_KEY_BUTTON_C,
    KZS_KEY_BUTTON_X,
    KZS_KEY_BUTTON_Y,
    KZS_KEY_BUTTON_Z,
    KZS_KEY_BUTTON_L1,
    KZS_KEY_BUTTON_L2,
    KZS_KEY_BUTTON_R1,
    KZS_KEY_BUTTON_R2,
    KZS_KEY_BUTTON_SELECT,
    KZS_KEY_BUTTON_START,
    KZS_KEY_BUTTON_THUMBL,
    KZS_KEY_BUTTON_THUMBR,
    KZS_KEY_BUTTON_MODE,

    KZS_KEY_COUNT
};


/** Callback function type for event handling. */ 
typedef kzsError (*KzsEventHandleFunction)(const struct KzsEventQueue* queue, void* userData);


/** Creates a new event queue. */
kzsError kzsEventQueueCreate(struct KzsEventQueue** queue_out);
/** Frees memory allocated for a input event queue. */
void kzsEventQueueDelete(struct KzsEventQueue* queue);

/** Get an iterator over an event queue. */
struct KzsEventQueueIterator kzsEventQueueGetIterator(const struct KzsEventQueue* queue);
/** Internal iteration. */
kzBool kzsEventQueueIteratorIterate_private(struct KzsEventQueueIterator* it);
/** Iterate an event queue iterator.
*
* Return true if this value is still valid.
*/
#define kzsEventQueueIteratorIterate(it) kzsEventQueueIteratorIterate_private(&it)
/** Internal iteration get value. */
struct KzsEvent* kzsEventQueueIteratorGetValue_private(const struct KzsEventQueueIterator* it);
/** Get the current value of an event queue iterator. */
#define kzsEventQueueIteratorGetValue(it) kzsEventQueueIteratorGetValue_private(&it)

/** Get nth event from an event queue. */
struct KzsEvent* kzsEventQueueGetEvent(const struct KzsEventQueue* queue, kzUint index);
/** Get the number of events in an event queue. */
kzUint kzsEventQueueGetEventCount(const struct KzsEventQueue* queue);

/** Clear all events from an event queue. */
void kzsEventQueueClear(struct KzsEventQueue* queue);

/** Swap contents of two queues. */
void kzsEventQueueSwap(struct KzsEventQueue* queue1, struct KzsEventQueue* queue2);

/** Renders an event idempotent. */
void kzsEventInvalidate(struct KzsEvent* event);

/** Adds a new event into the queue. */
struct KzsEvent* kzsEventQueueAddRawEvent(struct KzsEventQueue* queue, const struct KzsEvent* event);

/** Adds a new key event into the queue with input values. */
struct KzsEvent* kzsEventQueueAddKeyEvent(struct KzsEventQueue* queue, kzUint button,
                                          enum KzsInputKeyDeviceState state);
/** Adds a new pointer event into the queue with input values.
*
* If translating to touch events, add a touch event with one cursor instead. */
struct KzsEvent* kzsEventQueueAddPointerEvent(struct KzsEventQueue* queue, kzInt x, kzInt y,
                                              kzU32 buttons, enum KzsInputPointingDeviceState state);
/** Adds a new touch event
*
* The touch event generated will have a specified number of cursors. The cursors must be filled separately to the
* event structure returned from this function. */
struct KzsEvent* kzsEventQueueAddTouchEvent(struct KzsEventQueue* queue, kzUint numCursors);
/** As add touch event, but with a state already set now. */
struct KzsEvent* kzsEventQueueAddTouchEventWithState(struct KzsEventQueue* queue, kzUint numCursors,
                                                     enum KzsInputTouchState state);
/** Adds a new window event into the queue. */
struct KzsEvent* kzsEventQueueAddSimpleWindowEvent(struct KzsEventQueue* queue, enum KzsEventType type, struct KzsWindow* window);
/** Adds a new window resize event into the queue. */
struct KzsEvent* kzsEventQueueAddWindowResizeEvent(struct KzsEventQueue* queue, struct KzsWindow* window, kzUint width, kzUint height);

/** Adds a new orientation change event into the queue. */
struct KzsEvent* kzsEventQueueAddWindowOrientationChangeEvent(struct KzsEventQueue* queue, struct KzsWindow* window, enum KzsWindowOrientation orientation);

/** Adds a new application paused event. */
struct KzsEvent* kzsEventQueueAddApplicationPausedEvent(struct KzsEventQueue* queue);
/** Adds a new application suspended event. */
struct KzsEvent* kzsEventQueueAddApplicationSuspendedEvent(struct KzsEventQueue* queue);
/** Adds a new application resumed event. */
struct KzsEvent* kzsEventQueueAddApplicationResumedEvent(struct KzsEventQueue* queue);

/** Adds a new toggle HUD debug event into the queue. */
struct KzsEvent* kzsEventQueueAddToggleHUDDebugEvent(struct KzsEventQueue* queue);
/** Adds a new set HUD debug event into the queue. */
struct KzsEvent* kzsEventQueueAddSetHUDDebugEvent(struct KzsEventQueue* queue, kzInt onoff);

/** Get the pointer event from an input event. */
const struct KzsInputEventPointer* kzsInputEventGetPointingDeviceData(const struct KzsEvent* event);
/** Get key event from an input event. */
const struct KzsInputEventKey* kzsInputEventGetKeyDeviceData(const struct KzsEvent* event);
/** Get touch event from an input event. */
const struct KzsInputEventTouch* kzsInputEventGetTouchData(const struct KzsEvent* event);
/** Get the event type. */
enum KzsEventType kzsEventGetType(const struct KzsEvent* event);

/** Get the identifier of the touch cursor. */
kzUint kzsInputCursorGetId(const struct KzsInputCursor* inputdata);
/** Gets the pressure of the touch cursor. */
kzFloat kzsInputCursorGetPressure(const struct KzsInputCursor* inputData);
/** Gets the radius of the touch cursor. */
kzFloat kzsInputCursorGetRadius(const struct KzsInputCursor* inputData);
/** Get the x coordinate of touch cursor. */
kzFloat kzsInputCursorGetX(const struct KzsInputCursor* inputData);
/** Get the y coordinate of touch cursor. */
kzFloat kzsInputCursorGetY(const struct KzsInputCursor* inputData);
/** Get the state of the touch cursor. */
enum KzsInputCursorState kzsInputCursorGetState(const struct KzsInputCursor* inputdata);

/** Gets the raw button code of the key device. */
kzUint kzsInputEventKeyGetButtonRaw(const struct KzsInputEventKey* inputData);
/** Gets the translated button of the key device. */
enum KzsInputKey kzsInputEventKeyGetButton(const struct KzsInputEventKey* inputData);
/** Gets the state of the key device. */
enum KzsInputKeyDeviceState kzsInputEventKeyGetState(const struct KzsInputEventKey* inputData);

/** Gets the bitfield of the buttons of the active pointing device.
 * \param inputData Input data pointer.
 * \return Bitmask of pointing device buttons, defined as KZS_POINTING_DEVICE_BUTTON_ *.
 */
kzU32 kzsInputEventPointerGetButtons(const struct KzsInputEventPointer* inputData);
/** Gets the state of the active pointing device. */
enum KzsInputPointingDeviceState kzsInputEventPointerGetState(const struct KzsInputEventPointer* inputData);
/** Gets the x coordinate of the active pointing device. */
kzInt kzsInputEventPointerGetX(const struct KzsInputEventPointer* inputData);
/** Gets the y coordinate of the active pointing device. */
kzInt kzsInputEventPointerGetY(const struct KzsInputEventPointer* inputData);

/** Get the nth cursor form a touch event. */
struct KzsInputCursor* kzsInputEventTouchGetCursor(const struct KzsInputEventTouch* inputData, kzUint cursorIdx);
/** Get the number of cursors in this event. */
kzUint kzsInputEventTouchGetCursorCount(const struct KzsInputEventTouch* inputData);
/** Get the touch state.
*
* Note that touch state goes DOWN when the first finger touches the screen and UP when the last finger leaves.
* Everything in-between is drag. */
enum KzsInputTouchState kzsInputEventTouchGetState(const struct KzsInputEventTouch* inputData);
/** Add a cursor to a touch event.
*
* The queue is needed for potential mirroring of the event.
*
* Returns true if there was space for the cursor, false otherwise.
*
* If translating pointer events, add a pointer event instead and mark the touch event as unusable.
*
* If the event is not a touch event, do nothing unless translating. */
kzBool kzsInputEventTouchSetCursor(struct KzsEventQueue* queue, struct KzsEvent* event, kzUint cursorIndex,
                                   kzUint cursorId, kzFloat x, kzFloat y, kzFloat pressure, kzFloat radius, enum KzsInputCursorState state);
/** Set the state of touch event.
*
* This function takes a generic event structure for consistency.
*
* If the event is not a touch event, do nothing. */
void kzsInputEventTouchSetState(struct KzsEvent* event, enum KzsInputTouchState state);

/** Get the target window of the event. */
struct KzsWindow* kzsWindowEventGetTarget(const struct KzsEvent* event);
/** Get the window width of a resize event. */
kzUint kzsWindowEventResizeGetWidth(const struct KzsEvent* event);
/** Get the window height of a resize event. */
kzUint kzsWindowEventResizeGetHeight(const struct KzsEvent* event);
/** Get the window orientation of a orientation change event. */
enum KzsWindowOrientation kzsWindowEventOrientationChangeGetOrientation(const struct KzsEvent* event);

/** Returns the translated key. */
enum KzsInputKey kzsInputNativeGetTranslatedKey(kzUint button);

/** Get set HUD event data from an event. */
const struct KzsDebugEventSetHUD* kzsEventGetSetHUDData(const struct KzsEvent* event);

/** Returns set HUD debug event parameter. */
kzInt kzsSetHUDDebugEventGetOnOff(const struct KzsDebugEventSetHUD* inputData);


KZ_HEADER_END


#endif
