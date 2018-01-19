/**
* \file
* Time line entry.
* 
* Describes how animation clips or sequences are used on their parent time line.
* Allows multiple playback modes and adjusting the playback rates.
* 
* Time Line Entry Messages
* ----
* ::KZU_MESSAGE_TIMELINE_ENTRY_STARTED message is sent when the time line entry starts playback. The message has the following three arguments.
* ::KZU_MESSAGE_ARGUMENT__ANIMATION_ITEM pointer argument is the KzuAnimationItem passed to ::kzuTimeLineEntryCreateAnimationItem().
* ::KZU_MESSAGE_ARGUMENT__TIMELINE_ENTRY pointer argument is the KzuTimeLineEntry itself. ::KZU_MESSAGE_ARGUMENT__TIMELINE_ENTRY_PLAYBACK
* pointer argument is a pointer to a KzuTimeLineEntryPlayback structure, it is used internally by Kanzi.
*
* ::KZU_MESSAGE_TIMELINE_ENTRY_PROGRESSED message is sent periodically when the time line entry is still playing. It has the following four arguments.
* ::KZU_MESSAGE_ARGUMENT__ANIMATION_ITEM pointer argument is the KzuAnimationItem passed to ::kzuTimeLineEntryCreateAnimationItem().
* ::KZU_MESSAGE_ARGUMENT__TIMELINE_ENTRY pointer argument is the KzuTimeLineEntry itself. ::KZU_MESSAGE_ARGUMENT__TIMELINE_ENTRY_PLAYBACK
* pointer argument is a pointer to a KzuTimeLineEntryPlayback structure, it is used internally by Kanzi. ::KZU_MESSAGE_ARGUMENT__ANIMATION_ITEM_TIME
* float argument is the time how long the time line entry has been playing.
*
* ::KZU_MESSAGE_TIMELINE_ENTRY_PLAYED_TO_END message is sent every time the time line entry has played to the end. If the entry repeats several times,
* the message is sent after each repetition. It is not sent if the animation item
* is a time line sequence. The message has the following two arguments. ::KZU_MESSAGE_ARGUMENT__ANIMATION_ITEM pointer argument is the KzuAnimationItem
* passed to ::kzuTimeLineEntryCreateAnimationItem(). ::KZU_MESSAGE_ARGUMENT__TIMELINE_ENTRY pointer argument is the KzuTimeLineEntry itself.
*
* ::KZU_MESSAGE_TIMELINE_ENTRY_FINISHED message is sent when the time line entry has finished all its repetitions and will be deleted.
* The message has the following three arguments. ::KZU_MESSAGE_ARGUMENT__ANIMATION_ITEM pointer argument is the KzuAnimationItem passed to
* ::kzuTimeLineEntryCreateAnimationItem(). ::KZU_MESSAGE_ARGUMENT__TIMELINE_ENTRY pointer argument is the KzuTimeLineEntry itself.
* ::KZU_MESSAGE_ARGUMENT__TIMELINE_ENTRY_PLAYBACK pointer argument is a pointer to a KzuTimeLineEntryPlayback structure, it is used internally by Kanzi.
*
* Time Line Entry Properties
* ----
* ::KZU_PROPERTY_TYPE_TIMELINE_ENTRY_WEIGHT float property specifies the time line entry's relative weight when the weight blend mode is
* ::KZU_TIME_LINE_ENTRY_WEIGHT_BLEND_MODE_WEIGHTED_AVERAGE_SUM. It can be read and written with ::kzuTimeLineEntryGetWeight() and ::kzuTimeLineEntrySetWeight().
*
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_TIME_LINE_ENTRY_H
#define KZU_TIME_LINE_ENTRY_H

#include <user/properties/kzu_property_common.h>

#include <system/kzs_types.h>
#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/** Sets time line entry to loop repeatedly. */
#define KZU_TIME_LINE_ENTRY_LOOP_INFINITELY -1


/* Forward declarations */
struct KzuAnimationKey;
struct KzuAnimationPlayer;
struct KzuAnimationClip;
struct KzuAnimationItem;
struct KzuAnimation;
struct KzuTimeLineSequence;
struct KzuPropertyType;
struct KzuPropertyManager;
struct KzcMemoryManager;
struct KzuObjectNode;
struct KzcHashMap;
struct KzcDynamicArray;


/** Playback type of the contained animation clip. */
enum KzuTimeLineEntryPlaybackMode
{
    KZU_TIME_LINE_ENTRY_PLAYBACK_MODE_NORMAL,  /**< Plays animation normally from the start to end. */
    KZU_TIME_LINE_ENTRY_PLAYBACK_MODE_REVERSE, /**< Plays animation in reverse from the end to start. */
    KZU_TIME_LINE_ENTRY_PLAYBACK_MODE_PINGPONG /**< Plays animation first normally, then in reverse. */
};

/** Blend mode for weight. */
enum KzuTimeLineEntryWeightBlendMode
{
    KZU_TIME_LINE_ENTRY_WEIGHT_BLEND_MODE_NONE, /**< No blending. */
    KZU_TIME_LINE_ENTRY_WEIGHT_BLEND_MODE_WEIGHTED_AVERAGE_SUM, /**< Weighted average sum. */
    KZU_TIME_LINE_ENTRY_WEIGHT_BLEND_MODE_ADDITIVE /**< Additive. */
};


/**
 * \struct KzuTimeLineEntry
 * Time line entry.
 * The starting and ending times in time line entry are relative to parent sequence's time line.
 */
struct KzuTimeLineEntry;


/** Playback structure for timeline entry, ::KZ_NULL when the entry has been deleted. Used internally by KzuStateManager. */
struct KzuTimeLineEntryPlayback
{
    struct KzuTimeLineEntry* entry; /**< A pointer to the time line entry. */
};


/** Creates new time line entry based on given animation item. */
kzsError kzuTimeLineEntryCreateAnimationItem(const struct KzcMemoryManager* memoryManager, struct KzuPropertyManager* propertyManager, kzFloat start,
                                             struct KzuAnimationItem* animationItem, struct KzuTimeLineEntry** out_timeLineEntry);
/** Acquires playback reference from a time line entry. Throws an error if entry is already associated with a playback. */
kzsError kzuTimeLineEntryAcquirePlayback(struct KzuTimeLineEntry* timeLineEntry, struct KzuTimeLineEntryPlayback** out_playBack);
/** Releases a playback reference. */
kzsError kzuTimeLineEntryReleasePlayback(struct KzuTimeLineEntryPlayback* playback);
/** Deallocates memory required for a time line entry. */
kzsError kzuTimeLineEntryDelete(struct KzuTimeLineEntry* timeLineEntry);


/** Sets the time line entry to be deleted after its playback has finished. False by default. */
void kzuTimeLineEntrySetDeleteAfterPlayback(struct KzuTimeLineEntry* timeLineEntry, kzBool delete_entry);
/** Returns true if time line entry is set to be deleted after its playback has finished. */
kzBool kzuTimeLineEntryGetDeleteAfterPlayback(const struct KzuTimeLineEntry* timeLineEntry);
/** Sets if the time line entry was running during the previous frame before the current frame. Used internally by Kanzi. */
void kzuTimeLineEntrySetActiveLastFrame(struct KzuTimeLineEntry* timeLineEntry, kzBool active);
/** Returns true if time line entry was active on frame before this frame. */
kzBool kzuTimeLineEntryGetActiveLastFrame(const struct KzuTimeLineEntry* timeLineEntry);


/** Gets animation clip from time line entry.
 * \return The KzuAnimationClip of the entry or ::KZ_NULL if the entry's animation item is not of type ::KZU_ANIMATION_ITEM_TYPE_CLIP. */
struct KzuAnimationClip* kzuTimeLineEntryGetAnimationClip(const struct KzuTimeLineEntry* entry);
/** Gets the animation item from a time line entry. */
struct KzuAnimationItem* kzuTimeLineEntryGetAnimationItem(const struct KzuTimeLineEntry* entry);
/** Gets a list of animations that the time line entry references into, extracted from clips and animations, sequence not supported.
 * \param timeLineEntry The time line entry containing the animations.
 * \param out_animations A pointer that is set to point to a KzcDynamicArray of KzuAnimation objects. Do not modify this list.
 * \return ::KZS_SUCCESS on success.
 */
kzsError kzuTimeLineEntryGetAnimations(struct KzuTimeLineEntry* timeLineEntry, struct KzcDynamicArray** out_animations);


/** Updates a time line entry. This function is normally called from kzuAnimationPlayerUpdate().
 * \param player The animation player.
 * \param timeLineEntry The entry to update.
 * \param time Time in seconds, relative to the entry's starting time (time 0.0 is the beginning of the entry).
 * \return ::KZS_SUCCESS on success.
 */
kzsError kzuTimeLineEntryUpdate(struct KzuAnimationPlayer* player, struct KzuTimeLineEntry* timeLineEntry, kzFloat time);
/** Finishes a time line entry, i.e. marks it for deletion it and sends the ::KZU_MESSAGE_TIMELINE_ENTRY_FINISHED message,
 * restores original values if necessary.
 * \return ::KZS_SUCCESS on success.
 */
kzsError kzuTimeLineEntryFinish(struct KzuTimeLineEntry* timeLineEntry, struct KzuAnimationPlayer* player);
/** Returns if given entry is finished. */
kzBool kzuTimeLineEntryIsFinished(const struct KzuTimeLineEntry* timeLineEntry);


/** Sets restoring for original values for time line entry.
 * Restoring values means removing the effect of animations belonging to the time line entry when the entry is finished.
 * The default value is ::KZ_FALSE.
 */
void kzuTimeLineEntrySetRestoreOriginalValues(struct KzuTimeLineEntry* timeLineEntry, kzBool restoreOriginalValues);
/** Returns if the time line entry will restore original values after playback. */
kzBool kzuTimeLineEntryIsRestoreOriginalValues(const struct KzuTimeLineEntry* timeLineEntry);


/** Sets the playback mode. The default is ::KZU_TIME_LINE_ENTRY_PLAYBACK_MODE_NORMAL. */
void kzuTimeLineEntrySetPlaybackMode(struct KzuTimeLineEntry* timeLineEntry, enum KzuTimeLineEntryPlaybackMode type);
/** Returns the playback mode of a time line entry.
 * \param timeLineEntry The time line entry.
 * \return The playback mode or ::KZU_TIME_LINE_ENTRY_PLAYBACK_MODE_NORMAL if using a property driven animation.
 */
enum KzuTimeLineEntryPlaybackMode kzuTimeLineEntryGetPlaybackMode(const struct KzuTimeLineEntry* timeLineEntry);

/** Sets the input type for a time line entry.
 * Set both inputObject and inputObjectRelativePath to ::KZ_NULL to use time as input (default). 
 * \param timeLineEntry The time line entry.
 * \param inputPropertyType The type of the property.
 * \param inputObject The object that hosts the input property or ::KZ_NULL to use inputObjectRelativePath instead.
 * \param inputObjectRelativePath A relative path to the object that hosts the input property or ::KZ_NULL to use inputObject directly.
 * \param inputTargetAttribute The part of the property to use or ::KZU_PROPERTY_FIELD_WHOLE to use the whole property.
 * \return ::KZS_SUCCESS on success.
 */
kzsError kzuTimeLineEntrySetInputType(struct KzuTimeLineEntry* timeLineEntry, struct KzuPropertyType* inputPropertyType, void* inputObject,
                                      kzString inputObjectRelativePath, enum KzuPropertyField inputTargetAttribute);
/** Gets the input type of a time line entry. ::KZ_NULL to not use the output parameter. 
 * \param out_propertyManager Property manager used in property driven animation, ::KZ_NULL if none.
 * \param out_inputPropertyType Property type used for animation, ::KZ_NULL for time-based animation.
 * \param out_inputObject Object used for property targeting, ::KZ_NULL if none.
 * \param out_inputObjectPath Path used for property object targeting, ::KZ_NULL if none.
 * \param out_inputTargetAttribute Target attribute in property driven animation, ::KZU_PROPERTY_FIELD_WHOLE for none.
*/
void kzuTimeLineEntryGetInputType(const struct KzuTimeLineEntry* timeLineEntry, struct KzuPropertyType** out_inputPropertyType,
                                  void** out_inputObject, kzMutableString* out_inputObjectPath,
                                  enum KzuPropertyField* out_inputTargetAttribute);
/** Gets input property type from entry. */
struct KzuPropertyType* kzuTimeLineEntryGetInputPropertyType(const struct KzuTimeLineEntry* timeLineEntry);
/** Returns the input object from a time line entry or ::KZ_NULL if none. */
void* kzuTimeLineEntryGetInputObject(const struct KzuTimeLineEntry* timeLineEntry);


/** Sets the repeat count for a time line entry. Use the value -1 for an infinite repeat. */
void kzuTimeLineEntrySetRepeatCount(struct KzuTimeLineEntry* timeLineEntry, kzInt repeatCount);
/** Returns the repeat count of a time line entry. */
kzInt kzuTimeLineEntryGetRepeatCount(const struct KzuTimeLineEntry* timeLineEntry);
/** Gets the current repeat index at given time from a time line entry.
 * For example, if the repeat count is 2, returns 0 if it's playing the 1st repeat, 1 if the 2nd repeat and so on.
 */
kzInt kzuTimeLineEntryGetCurrentRepeatIndex(const struct KzuTimeLineEntry* timeLineEntry, kzFloat time);


/** Sets a new starting time for a time line entry and moves the ending time accordingly. The animation duration will not be modified.
 * \param timeLineEntry The time line entry.
 * \param Time in seconds in animation player time.
 */
void kzuTimeLineEntrySetStartingTime(struct KzuTimeLineEntry* timeLineEntry, kzFloat time);
/** Gets the starting time of a time line entry.
 * \return Time in seconds in animation player time.
 */
kzFloat kzuTimeLineEntryGetStartingTime(const struct KzuTimeLineEntry* timeLineEntry);


/** Sets a duration modifier. For example, setting this to 2 will result in animation playing half of the normal speed. */
void kzuTimeLineEntrySetDurationScale(struct KzuTimeLineEntry* timeLineEntry, kzFloat durationModifier);
/** Gets the duration of one repeat of the time line entry. */
kzFloat kzuTimeLineEntryGetDuration(const struct KzuTimeLineEntry* timeLineEntry);
/** Gets the end time of a time line entry. This operation is not simple getter it needs to do some calculations. Avoid using very heavily.
 * \param timeLineEntry The time line entry.
 * \return Time in seconds in animation player time.
 */
kzFloat kzuTimeLineEntryGetEndingTime(const struct KzuTimeLineEntry* timeLineEntry);
/** Returns whether or not the time line entry is active at the given time.
 * \param timeLineEntry The time line entry.
 * \param time Time in seconds in animation player time.
 * \return ::KZ_TRUE if the time line entry is active at the specified time or if the force update flag
 *         has been set true with kzuTimeLineEntrySetForceUpdate(). Otherwise ::KZ_FALSE.
 */
kzBool kzuTimeLineEntryIsActiveAtTime(const struct KzuTimeLineEntry* timeLineEntry, kzFloat time);
/** \return ::KZ_TRUE if the time line entry has been played to the end (including the last frame), otherwise ::KZ_FALSE. */
kzBool kzuTimeLineEntryIsPlayedToEnd(const struct KzuTimeLineEntry* timeLineEntry);

void kzuTimeLineEntrySetIsPlayedToEnd(struct KzuTimeLineEntry* timeLineEntry, kzBool isPlayedToEnd);

/** Sets the relative weight for a time line entry. */
kzsError kzuTimeLineEntrySetWeight(const struct KzuTimeLineEntry* timeLineEntry, kzFloat weight);
/** Gets the relative weight of a time line entry. */
kzFloat kzuTimeLineEntryGetWeight(const struct KzuTimeLineEntry* timeLineEntry);

/** Sets the weight blend mode for a time line entry. */
void kzuTimeLineEntrySetWeightBlendMode(struct KzuTimeLineEntry* timeLineEntry, enum KzuTimeLineEntryWeightBlendMode weightBlendMode);
/** Gets the weight blend mode of a time line entry. */
enum KzuTimeLineEntryWeightBlendMode kzuTimeLineEntryGetWeightBlendMode(const struct KzuTimeLineEntry* timeLineEntry);

/** Sets message dispatching enabled for entry, by default enabled. Can optimize the performance if no time line messages are listened. */
void kzuTimeLineEntrySetMessageDispatchingEnabled(struct KzuTimeLineEntry* entry, kzBool enabled);


/** Sets the context object for a time line entry, can be a material, a render pass or anything that can be animated.
 * For object nodes, kzuTimeLineEntrySetContextObjectPath() should be used instead.
 * 
 * Normally, the context object is the object that receives the ::KZU_MESSAGE_ANIMATION_PLAYER_PLAY_ANIMATION message.
 * When the object path set with kzuTimeLineEntrySetTargetObjectPath() is relative, the context object is the starting point
 * of the relative path.
 */
kzsError kzuTimeLineEntrySetContextObject(struct KzuTimeLineEntry* timeLineEntry, const void* contextObject, kzBool isResource);
/** Gets the context object of a time line entry. */
const void* kzuTimeLineEntryGetContextObject(const struct KzuTimeLineEntry* timeLineEntry);
/** Sets the context object path for a time line entry.
 * The path should be relative to the animation clip's target object path.
 *
 * Normally, the context object is the object that receives the ::KZU_MESSAGE_ANIMATION_PLAYER_PLAY_ANIMATION message.
 * When the object path set with kzuTimeLineEntrySetTargetObjectPath() is relative, the context object is the starting point
 * of the relative path.
 * \param timeLineEntry The time line entry.
 * \param targetObjectPath Object path to the context object.
 * \return ::KZS_SUCCESS on success.
 */
kzsError kzuTimeLineEntrySetContextObjectPath(struct KzuTimeLineEntry* timeLineEntry, kzString targetObjectPath);
/** Gets the context object path of a time line entry. */
kzString kzuTimeLineEntryGetContextObjectPath(const struct KzuTimeLineEntry* timeLineEntry);
/** \return ::KZ_TRUE if the context object of the given time line entry is a KzuResource, otherwise ::KZ_FALSE. */
kzBool kzuTimeLineEntryIsContextObjectResource(const struct KzuTimeLineEntry* timeLineEntry);


/** Sets the target object path for an animation in the time line entry. */
kzsError kzuTimeLineEntrySetTargetObjectPath(struct KzuTimeLineEntry* timeLineEntry, const struct KzuAnimation* animation, kzString path);
/** Gets the target object path for an animation in the time line entry. */
kzString kzuTimeLineEntryGetTargetObjectPath(const struct KzuTimeLineEntry* timeLineEntry, const struct KzuAnimation* animation);


/** Forces the entry to be updated. Disables the behavior of animation player not updating property value if entry < startTime or entry > endTime. */
void kzuTimeLineEntrySetForceUpdate(struct KzuTimeLineEntry* entry, kzBool forceUpdate);





KZ_HEADER_END


#endif
