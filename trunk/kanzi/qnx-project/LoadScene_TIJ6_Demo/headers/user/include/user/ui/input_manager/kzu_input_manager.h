/**
* \file
* Input manager.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_INPUT_MANAGER_H
#define KZU_INPUT_MANAGER_H


#include <core/util/math/kzc_ray.h>

#include <system/kzs_types.h>
#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations. */
struct KzsEvent;
struct KzcMemoryManager;
struct KzcVector2;
struct KzuLayer;
struct KzuRenderer;
struct KzuMessageDispatcher;
struct KzuInputManipulator;


/** Input manager. */
struct KzuInputManager;


/** Maximum supported number of touch points. */
#define KZU_INPUT_MANAGER_MAX_TOUCH_POINTS      10
/** Invalid touch point identifier. */
#define KZU_INPUT_TOUCH_INVALID_ID              ((kzUint)-1)


/** Touch point state. */
enum KzuInputTouchPointState
{
    KZU_INPUT_TOUCH_POINT_STATE_DOWN        = 0,    /** The point has been created by touching the screen. */
    KZU_INPUT_TOUCH_POINT_STATE_STATIONARY  = 1,    /** The point has not moved since last report. */
    KZU_INPUT_TOUCH_POINT_STATE_MOVE        = 2,    /** The point has moved since last report. */
    KZU_INPUT_TOUCH_POINT_STATE_UP          = 3     /** The point has been released. */
};

/** Touch point description. */
struct KzuInputTouchPoint
{
    kzUint id; /**< Touch ID. */
    enum KzuInputTouchPointState state; /**< Touch state. */
    kzFloat x; /**< Touch x coordinate. */
    kzFloat y; /**< Touch y coordinate. */
    struct KzuObjectNode* objectNode; /**< Hit test object node. */
    struct KzcRay ray; /**< Hit test ray. */
    kzFloat distance; /**< Hit test distance. */
};


/** Create an input manager. */
kzsError kzuInputManagerCreate(const struct KzcMemoryManager* memoryManager, struct KzuInputManager** out_inputManager);
/** Delete an input manager. */
kzsError kzuInputManagerDelete(struct KzuInputManager* inputManager);

/** Process a low level input event. */
kzsError kzuInputManagerProcessInputEvent(struct KzuInputManager* inputManager, const struct KzsEvent* inputEvent,
                                          struct KzuMessageDispatcher* messageDispatcher, const struct KzuLayer* layer);

/** Captures raw touch events to specified object node. Pass KZ_NULL to release capture. Raw touch capture has no effect on manipulators. */
kzsError kzuInputManagerCaptureTouch(struct KzuInputManager* inputManager, struct KzuObjectNode* objectNode);

/** Returns the raw touch event capturer node. Returns KZ_NULL if no capturer has been set. */
struct KzuObjectNode* kzuInputManagerGetTouchCaptureObject(const struct KzuInputManager* inputManager);

/** Remove input manipulator dependencies from input manager. */
kzsError kzuInputManagerRemoveManipulator(const struct KzuInputManager* inputManager, struct KzuInputManipulator* inputManipulator);
/** Notification of manipulator state change. */
kzsError kzuInputManagerNotifyManipulatorStateChange(const struct KzuInputManager* inputManager, struct KzuInputManipulator* inputManipulator);

/** Attempts to set focus to an object. */
kzsError kzuInputManagerSetFocus(struct KzuInputManager* inputManager, struct KzuObjectNode* objectNode);
/** Gets the focus object. */
struct KzuObjectNode* kzuInputManagerGetFocus(const struct KzuInputManager* inputManager);


KZ_HEADER_END


#endif
