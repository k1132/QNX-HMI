/**
* \file
* Task scheduler for periodically calling a set of functions.
* When the application framework is used, Kanzi will automatically create a task scheduler accessible with ::kzaApplicationGetTaskScheduler().
* That is used for e.g. playing animations.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_TASK_SCHEDULER_H
#define KZU_TASK_SCHEDULER_H


#include <system/debug/kzs_error.h>
#include <system/kzs_types.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations. */
struct KzcMemoryManager;
struct KzuAnimationPlayer;
struct KzuObjectNode;
/** \struct KzuTaskScheduler
 * Task scheduler for periodically calling a set of functions.
 */
struct KzuTaskScheduler;


/**
 * Scheduled task function.
 * \param deltaTime Elapsed time in milliseconds.
 * \param userData Arbitrary pointer previously passed to ::kzuTaskSchedulerAddRecurringTask().
 * \param out_done Set this to ::KZ_TRUE to remove the task from the scheduler or ::KZ_FALSE to keep the the task in execution.
 * \return The function should return ::KZS_SUCCESS on success. If it returns an error, execution of tasks is aborted and
 *         the error is passed forward.
 */
typedef kzsError (*KzuTaskFunction)(kzUint deltaTime, void* userData, kzBool* out_done);


/** Create a new task scheduler. */
kzsError kzuTaskSchedulerCreate(const struct KzcMemoryManager* memoryManager, struct KzuTaskScheduler** out_taskScheduler);

/** Delete a task scheduler. */
kzsError kzuTaskSchedulerDelete(struct KzuTaskScheduler* taskScheduler);

/** Add a recurring task to the task scheduler.
 * \param taskScheduler The task scheduler to use.
 * \param taskFunction The function to call periodically.
 * \param userParameters Arbitrary pointer that will be passed to the task function.
 * \return ::KZS_SUCCESS on success.
 */
kzsError kzuTaskSchedulerAddRecurringTask(const struct KzuTaskScheduler* taskScheduler, KzuTaskFunction taskFunction, void* userParameters);

/** Attach an animation player to the master animation player in the task scheduler. */
kzsError kzuTaskSchedulerAttachAnimationPlayer(const struct KzuTaskScheduler* taskScheduler, struct KzuAnimationPlayer* animationPlayer);

/** Sets the root animation player for task scheduler. */
void kzuTaskSchedulerSetRootAnimationPlayer_private(struct KzuTaskScheduler* taskScheduler, struct KzuAnimationPlayer* rootPlayer);
/** Get the master animation player for this task scheduler. */
struct KzuAnimationPlayer* kzuTaskSchedulerGetAnimationPlayer(const struct KzuTaskScheduler* taskScheduler);

/** Remove a task from the task scheduler.
 * \param taskScheduler The task scheduler to use.
 * \param taskFunction The function to remove from execution.
 * \param userParameters The pointer that was specified when the task was added to the task scheduler.
 * \return ::KZU_ERROR_SCHEDULER_TASK_NOT_FOUND if the function with the userParameters was not found. ::KZS_SUCCESS on success.
 */
kzsError kzuTaskSchedulerRemoveTask(const struct KzuTaskScheduler* taskScheduler, KzuTaskFunction taskFunction, const void* userParameters);

/** Execute all tasks in the task scheduler.
 * \param taskScheduler The task scheduler to use.
 * \param deltaTime Usually this should be milliseconds elapsed since the last execution, but other values can also be used
 *        to e.g. control animations.
 * \param rootNode The root node of the scheduler. Normally this should be the ::KzuScreen of the application.
 *        This is used to disable animations that are attached to nodes under other root nodes, such as nodes which do not
 *        belong to any scene.
 * \return ::KZS_SUCCESS on success. Any error returned by a task function.
 */
kzsError kzuTaskSchedulerExecuteAllTasks(struct KzuTaskScheduler* taskScheduler, kzUint deltaTime, struct KzuObjectNode* rootNode);


KZ_HEADER_END


#endif
