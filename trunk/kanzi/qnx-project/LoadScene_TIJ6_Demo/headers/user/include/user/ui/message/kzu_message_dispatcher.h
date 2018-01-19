/**
* \file
* Message dispatcher.
* Provides a system to exchange messages between different parts of an application.
* Messages can be used to notify of an event or request operations and data.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_MESSAGE_DISPATCHER_H
#define KZU_MESSAGE_DISPATCHER_H


#include "kzu_message_type.h"

#include <system/kzs_types.h>
#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations. */
struct KzcMemoryManager;
struct KzuInputManager;
struct KzuMessage;
struct KzuMessageType;
struct KzuObjectNode;
struct KzuPropertyManager;
struct KzuScene;
struct KzuTaskScheduler;


/** Timer mode. */
enum KzuTimerMessageMode
{
    KZU_TIMER_MESSAGE_MODE_ONCE,            /**< Timer will be called once after the specified interval elapses. Unsubscribe still needed. */
    KZU_TIMER_MESSAGE_MODE_REPEAT,          /**< Timer will be called repeatedly at specified intervals. */
                                            /**< Timers in this mode should be disabled when the application update cycle is called infrequently, */
                                            /**< for example in low power situations, as this generates excessive number of messages. */
    KZU_TIMER_MESSAGE_MODE_REPEAT_BATCH     /**< Same as KZU_TIMER_MESSAGE_MODE_REPEAT, but the system dispatches only the last message when a timer has several pending messages. */
};


/** A constant for kzuMessageDispatcherSetMessageLimit indicating that no message limit should be used. */
#define KZU_MESSAGE_DISPATCHER_NO_LIMIT 0


/**
 * \struct KzuMessageDispatcher
 * Message dispatcher object.
 */
struct KzuMessageDispatcher;


/** Message callback prototype. */
typedef kzsError (*KzuMessageHandlerFunction)(struct KzuMessage* message, void* userData);

/** Application message callback prototype. */
typedef kzsError (*KzuMessageDispatchFunction)(const struct KzuMessage* message, void* userData);


/** Create a message dispatcher. */
kzsError kzuMessageDispatcherCreate(const struct KzcMemoryManager* memoryManager, struct KzuMessageDispatcher** out_messageDispatcher);
/** Destroy a message dispatcher. */
kzsError kzuMessageDispatcherDelete(struct KzuMessageDispatcher* messageDispatcher);


/** Set an input manager for a dispatcher. */
void kzuMessageDispatcherSetInputManager(struct KzuMessageDispatcher* messageDispatcher, struct KzuInputManager* inputManager);
/** Get the input manager from a dispatcher. */
struct KzuInputManager* kzuMessageDispatcherGetInputManager(const struct KzuMessageDispatcher* messageDispatcher);
/** Set a task scheduler for a dispatcher. */
void kzuMessageDispatcherSetTaskScheduler(struct KzuMessageDispatcher* messageDispatcher, struct KzuTaskScheduler* taskScheduler);
/** Get the task scheduler from a dispatcher. */
struct KzuTaskScheduler* kzuMessageDispatcherGetTaskScheduler(const struct KzuMessageDispatcher* messageDispatcher);

/**
 * Sets the limitation of how many messages can be processed per frame. If the number of messages exceeds limitThreshold,
 * a warning is logged and the remaining messages are discarded. KZU_MESSAGE_DISPATCHER_NO_LIMIT disables the limitation (default).
 * After the threshold has been exceeded once, subsequent frames will process at most limitPerFrame messages to ensure good framerate.
 */
void kzuMessageDispatcherSetMessageLimit(struct KzuMessageDispatcher* messageDispatcher, kzUint limitThreshold, kzUint limitPerFrame);

/** Creates a message object.
 * \param messageDispatcher The message dispatcher to use.
 * \param messageType Type of the message.
 * \param out_Message A pointer set to point to the new message.
 */
kzsError kzuMessageDispatcherCreateMessage(struct KzuMessageDispatcher* messageDispatcher, const struct KzuMessageType* messageType, struct KzuMessage** out_Message);

/** Adds a message handler.
 * \param messageDispatcher The message dispatcher to use.
 * \param subscriptionSiteNode Object node that is associated with the message subscription created by this function.
 * \param messageType Type of the message to match.
 * \param messageSource Source of the message (as returned by kzuMessageGetSource) to match.
 * \param handlerFunction Function to call when a matching message appears.
 * \param userData User data pointer passed to handlerFunction.
 */
kzsError kzuMessageDispatcherAddHandler(const struct KzuMessageDispatcher* messageDispatcher, struct KzuObjectNode* subscriptionSiteNode,
                                        const struct KzuMessageType* messageType, struct KzuObjectNode* messageSource,
                                        KzuMessageHandlerFunction handlerFunction, void* userData);

/** Adds a message handler for tunneling phase. */
kzsError kzuMessageDispatcherAddTunnellingHandler(const struct KzuMessageDispatcher* messageDispatcher, struct KzuObjectNode* subscriptionSiteNode,
                                                  const struct KzuMessageType* messageType, struct KzuObjectNode* messageSource,
                                                  KzuMessageHandlerFunction handlerFunction, void* userData);

/** Checks if a handler subscription is valid. */
kzsError kzuMessageDispatcherIsHandlerSubscriptionValid(const struct KzuMessageDispatcher* messageDispatcher, const struct KzuObjectNode* subscriptionSiteNode,
                                                        const struct KzuMessageType* messageType, KzuMessageHandlerFunction handlerFunction, const void* userData, kzBool* out_valid);

/** Removes a message handler. */
kzsError kzuMessageDispatcherRemoveHandler(const struct KzuMessageDispatcher* messageDispatcher, const struct KzuObjectNode* subscriptionSiteNode,
                                           const struct KzuMessageType* messageType, KzuMessageHandlerFunction handlerFunction, const void* userData);

/** Dispatches a message. The associated handlers are called when kzuMessageDispatcherDispatchQueuedMessages is called. */
kzsError kzuMessageDispatcherDispatchMessage(const struct KzuMessageDispatcher* messageDispatcher, struct KzuMessage* message, struct KzuObjectNode* source);

/** Dispatches a message. The associated handlers are called immediately. */
kzsError kzuMessageDispatcherDispatchMessageSynchronous(const struct KzuMessageDispatcher* messageDispatcher, struct KzuMessage* message, struct KzuObjectNode* source);

/** Dispatches queued messages. Generally should be called once per frame. */
kzsError kzuMessageDispatcherDispatchQueuedMessages(struct KzuMessageDispatcher* messageDispatcher);

/** Notifies the message dispatcher that an object node is being destroyed.
 *  This will cancel all messages where the specified node is the source of the message or the current site during routing. */
kzsError kzuMessageDispatcherNotifyObjectDeleted(const struct KzuMessageDispatcher* messageDispatcher, const struct KzuObjectNode* objectNode);

/** Registers a timer handler.
 * \param messageDispatcher The message dispatcher to use.
 * \param interval timeout in milliseconds in case of a one-shot timer, and the interval in case of a repeating timer.
 * \param mode KZU_TIMER_MESSAGE_MODE_ONCE, KZU_TIMER_MESSAGE_MODE_REPEAT or KZU_TIMER_MESSAGE_MODE_REPEAT_BATCH. KZU_TIMER_MESSAGE_MODE_REPEAT_BATCH is
 *             recommended for a repeating timer because it calls handlerFunction only once when the interval has been exceeded several times over.
 * \param handlerFunction The function to call when the timer expires.
 * \param userData User data pointer passed to handlerFunction.
 */
kzsError kzuMessageDispatcherAddTimerHandler(const struct KzuMessageDispatcher* messageDispatcher, kzUint interval, enum KzuTimerMessageMode mode,
                                             KzuMessageHandlerFunction handlerFunction, void* userData);
/** Unregisters a timer handler. */
kzsError kzuMessageDispatcherRemoveTimerHandler(const struct KzuMessageDispatcher* messageDispatcher, KzuMessageHandlerFunction handlerFunction, const void* userData);

/** Returns current time of message dispatcher in milliseconds. */
kzUint kzuMessageDispatcherGetTime(const struct KzuMessageDispatcher* messageDispatcher); 

/** Sets property manager for message dispatcher. */
void kzuMessageDispatcherSetCurrentData(struct KzuMessageDispatcher* messageDispatcher, struct KzuPropertyManager* propertyManager);
/** Set the user data passed to the callbacks set with kzuMessageDispatcherSetCallbackUserData and kzuMessageDispatcherSetHandlerSetFloatProperty. */
void kzuMessageDispatcherSetCallbackUserData(struct KzuMessageDispatcher* messageDispatcher, void *userData);
/** Set a callback to handle the KZU_MESSAGE_SET_BOOLEAN_PROPERTY and KZU_MESSAGE_TOGGLE_BOOLEAN_PROPERTY messages. */
void kzuMessageDispatcherSetHandlerSetBooleanProperty(struct KzuMessageDispatcher* messageDispatcher, KzuMessageDispatchFunction function);
/** Set a callback to handle the KZU_MESSAGE_SET_FLOAT_PROPERTY message. */
void kzuMessageDispatcherSetHandlerSetFloatProperty(struct KzuMessageDispatcher* messageDispatcher, KzuMessageDispatchFunction function);


KZ_HEADER_END


#endif
