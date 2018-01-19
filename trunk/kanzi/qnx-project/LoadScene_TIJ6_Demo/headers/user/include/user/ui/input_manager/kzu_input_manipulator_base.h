/**
* \file
* Input manipulator base class.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_INPUT_MANIPULATOR_BASE_H
#define KZU_INPUT_MANIPULATOR_BASE_H


#include <user/ui/input_manager/kzu_input_manipulator.h>

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


/** Input manipulator class. */
struct KzuInputManipulatorClass
{
    /** Attach function for input manipulators. */
    kzsError (*kzuInputManipulatorAttach)(struct KzuInputManipulator* inputManipulator);

    /** Detach function for input manipulators. */
    kzsError (*kzuInputManipulatorDetach)(struct KzuInputManipulator* inputManipulator);

    /** Delete function for input manipulators. */
    kzsError (*kzuInputManipulatorDelete)(struct KzuInputManipulator* inputManipulator);

    /** Touch inside function for input manipulators. */
    kzsError (*kzuInputManipulatorTouchInside)(struct KzuInputManipulator* inputManipulator, struct KzuMessage* message);

    /** Touch outside function for input manipulators. */
    kzsError (*kzuInputManipulatorTouchOutside)(struct KzuInputManipulator* inputManipulator, struct KzuMessage* message);

    /** Cancel function for input manipulators. */
    kzsError (*kzuInputManipulatorCancel)(struct KzuInputManipulator* inputManipulator);

    /** Reset function for input manipulators. */
    kzsError (*kzuInputManipulatorReset)(struct KzuInputManipulator* inputManipulator);

    /** Fail callback function for input manipulators. */
    kzsError (*kzuInputManipulatorOnFail)(struct KzuInputManipulator* inputManipulator);
};

/** Input manipulator. */
struct KzuInputManipulator
{
    const struct KzuInputManipulatorClass* manipulatorClass; /**< Class of the input manipulator. */
    struct KzuObjectNode* objectNode; /**< Object node reference. */
    struct KzuInputManager* inputManager; /**< Input manager reference. */
    enum KzuInputManipulatorState state;            /**< The state of the manipulator. */
    kzBool handled;                                 /**< The handled flag to identify input phases. */
    struct KzuInputManipulator* failManipulator;    /**< The input manipulator that has to fail for this manipulator to succeed. */
    struct KzuInputManipulator* dependManipulator;  /**< The input manipulator that will be notified in case this manipulator fails. */
};


/** Create base input manipulator. */
kzsError kzuInputManipulatorCreate_protected(struct KzuInputManipulator* inputManipulator, const struct KzuInputManipulatorClass* inputManipulatorClass,
                                             struct KzuPropertyManager* propertyManager);

/** Add hit test information arguments to a message from a touch point. */
kzsError kzuInputManipulatorAddHitTestArguments_protected(const struct KzuInputManipulator* inputManipulator, const struct KzuMessage* message, const struct KzuInputTouchPoint* touchPoint);

/** Base attach function for input manipulators. */
kzsError kzuInputManipulatorAttach_protected(struct KzuInputManipulator* inputManipulator);

/** Base detach function for input manipulators. */
kzsError kzuInputManipulatorDetach_protected(struct KzuInputManipulator* inputManipulator);

/** Base delete function for input manipulators. */
kzsError kzuInputManipulatorDelete_protected(struct KzuInputManipulator* inputManipulator);

/** Base touch inside function for input manipulators. */
kzsError kzuInputManipulatorTouchInside_protected(struct KzuInputManipulator* inputManipulator, struct KzuMessage* message);

/** Base touch outside function for input manipulators. */
kzsError kzuInputManipulatorTouchOutside_protected(struct KzuInputManipulator* inputManipulator, struct KzuMessage* message);

/** Base cancel function for input manipulators. */
kzsError kzuInputManipulatorCancel_protected(struct KzuInputManipulator* inputManipulator);

/** Base reset function for input manipulators. */
kzsError kzuInputManipulatorReset_protected(struct KzuInputManipulator* inputManipulator);

/** Base fail callback function for input manipulators. */
kzsError kzuInputManipulatorOnFail_protected(struct KzuInputManipulator* inputManipulator);


KZ_HEADER_END


#endif
