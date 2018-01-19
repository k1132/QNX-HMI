/**
* \file
* Input manipulator.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_INPUT_MANIPULATOR_H
#define KZU_INPUT_MANIPULATOR_H


#include <system/kzs_types.h>
#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations. */
struct KzuObjectNode;
struct KzuPropertyManager;
struct KzuInputManipulator;
struct KzuInputTouchPoint;
struct KzuInputManager;
struct KzuMessage;
struct KzcMemoryManager;


/** Input manipulator state. */
enum KzuInputManipulatorState
{
    KZU_INPUT_MANIPULATOR_STATE_READY,              /**< The manipulator is in initial state. */
    KZU_INPUT_MANIPULATOR_STATE_POSSIBLE,           /**< The manipulator has started processing, but no gesture is recognized yet. The system can fail the manipulator automatically. */
    KZU_INPUT_MANIPULATOR_STATE_BEGIN,              /**< The manipulator has recognized a continuous gesture. */
    KZU_INPUT_MANIPULATOR_STATE_CHANGE,             /**< The manipulator has recognized changes in a continuous gesture. */
    KZU_INPUT_MANIPULATOR_STATE_END,                /**< The manipulator has finished recognizing a gesture. */
    KZU_INPUT_MANIPULATOR_STATE_FAIL,               /**< The manipulator has failed recognizing a gesture. */
    KZU_INPUT_MANIPULATOR_STATE_DELAYED,            /**< Not used at this time. */
    KZU_INPUT_MANIPULATOR_STATE_CANCELED            /**< Not used at this time. */
};


/**
 * \struct KzuInputManipulator
 * Input manipulator.
 */
struct KzuInputManipulator;


/** Attach an input manipulator to an object node. Called automatically when manipulator is added to an object node. */
kzsError kzuInputManipulatorAttach(struct KzuInputManipulator* inputManipulator, struct KzuObjectNode* objectNode);
/** Detach an input manipulator. Called automatically when manipulator is removed from an object node. */
kzsError kzuInputManipulatorDetach(struct KzuInputManipulator* inputManipulator);
/** Delete an input manipulator. */
kzsError kzuInputManipulatorDelete(struct KzuInputManipulator* inputManipulator);
/** Get the object node an input manipulator is attached to. */
struct KzuObjectNode* kzuInputManipulatorGetObjectNode(const struct KzuInputManipulator* inputManipulator);
/** Get the state of a manipulator. */
enum KzuInputManipulatorState kzuInputManipulatorGetState(const struct KzuInputManipulator* inputManipulator);
/** Set the state of a manipulator. */
kzsError kzuInputManipulatorSetState(struct KzuInputManipulator* inputManipulator, enum KzuInputManipulatorState state);
/** Sets the manipulator that is required to fail before this manipulator can succeed. */
void kzuInputManipulatorRequireToFail(struct KzuInputManipulator* inputManipulator, struct KzuInputManipulator* manipulatorToFail);
/** Gets the fail manipulator. */
struct KzuInputManipulator* kzuInputManipulatorGetFailManipulator(const struct KzuInputManipulator* inputManipulator);
/** Gets the depend manipulator. */
struct KzuInputManipulator* kzuInputManipulatorGetDependManipulator(const struct KzuInputManipulator* inputManipulator);

/** Notify manipulator of touches happening inside the subtree of the manipulator. */
kzsError kzuInputManipulatorTouchInside(struct KzuInputManipulator* inputManipulator, struct KzuMessage* message);
/** Notify manipulator of touches happening outside the subtree of the manipulator. */
kzsError kzuInputManipulatorTouchOutside(struct KzuInputManipulator* inputManipulator, struct KzuMessage* message);
/** Notify manipulator of touch canceling. */
kzsError kzuInputManipulatorCancel(struct KzuInputManipulator* inputManipulator);
/** Reset manipulator. */
kzsError kzuInputManipulatorReset(struct KzuInputManipulator* inputManipulator);

/** Get the change flag of a manipulator. Used internally. */
kzBool kzuInputManipulatorIsHandled(const struct KzuInputManipulator* inputManipulator);
/** Set the change flag of a manipulator. Used internally. */
void kzuInputManipulatorSetHandled(struct KzuInputManipulator* inputManipulator, kzBool handled);
/** Attach or detach an input manager to a manipulator during recognition. Used internally. */
kzsError kzuInputManipulatorSetInputManager(struct KzuInputManipulator* inputManipulator, struct KzuInputManager* inputManager);
/** Get the attached input manager of a manipulator. Used internally. */
struct KzuInputManager* kzuInputManipulatorGetInputManager(const struct KzuInputManipulator* inputManipulator);

/** Send message utility, providing predictable state manager transitions due to message queue processing. */
kzsError kzuInputManipulatorSendMessage(struct KzuMessage* message, struct KzuObjectNode* objectNode);


KZ_HEADER_END


#endif
