/**
* \file
* Animation sequence.
* A sequence of time line entries (KzuTimeLineEntry). Used to group several time line entries together for playback.
*
* KzuTimeLineSequence inherits from KzuAnimationItem. This means KzuTimeLineSequence can be added to a KzuAnimationPlayer as one of the
* time line entries and a time line sequence can include other time line sequences.
* 
* \see \ref kzu_animation_player.h.
*
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_TIME_LINE_SEQUENCE_H
#define KZU_TIME_LINE_SEQUENCE_H


#include <system/kzs_types.h>
#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations */
struct KzcDynamicArray;
struct KzcHashMap;
struct KzcInputStream;
struct KzcMemoryManager;
struct KzuAnimationClip;
struct KzuAnimationKey;
struct KzuAnimationItem;
struct KzuAnimationPlayer;
struct KzuBinaryFileInfo;
struct KzuUIDomain;
struct KzuTimeLineEntry;


/**
 * \struct KzuTimeLineSequence
 * A sequence of animation to play.
 * Contains the playing times and targets. Can be used to produce complex reusable animation sequences.
 */
struct KzuTimeLineSequence;


/** Creates new time line sequence. */
kzsError kzuTimeLineSequenceCreate(const struct KzcMemoryManager* memoryManager, struct KzuUIDomain* uiDomain, struct KzuTimeLineSequence** out_timeLineSequence);

/** Loads time line sequence from KZB. */
kzsError kzuTimeLineSequenceLoadFromKZB(struct KzuTimeLineSequence* timeLineSequence, struct KzcInputStream* inputStream, const struct KzuBinaryFileInfo* file);


/** Updates animation in the time line sequence. */
kzsError kzuTimeLineSequenceUpdate(struct KzuAnimationPlayer* player, const struct KzuTimeLineSequence* timeLineEntry, kzFloat time);

/**
 * Sorts the animations the animation sequence. 
 * This function must be called if starting times of animations are modified.
 */
kzsError kzuTimeLineSequenceSortAnimations(const struct KzuTimeLineSequence* sequence);

/**
* Adds new time line entry to the sequence. The time line entry added to sequence should not be shared. 
* After the call sequence takes ownership of the structure and deletes it upon deletion of the sequence.
*/
kzsError kzuTimeLineSequenceAddEntry(struct KzuTimeLineSequence* sequence, struct KzuTimeLineEntry* timeLineEntry);
/** Returns KZ_TRUE if sequence contains given KzuTimeLineEntry. KZ_FALSE if does not. */
kzBool kzuTimeLineSequenceContainsEntry(const struct KzuTimeLineSequence* sequence, const struct KzuTimeLineEntry* timeLineEntry);
/** Removes a time line entry from sequence. Returns error if element is not found. */
kzsError kzuTimeLineSequenceRemoveEntry(const struct KzuTimeLineSequence* sequence, struct KzuTimeLineEntry* timeLineEntry);
/** Returns KZ_TRUE if sequence contains given KzuAnimationItem. KZ_FALSE if does not. */
kzBool kzuTimeLineSequenceContainsAnimationItem(const struct KzuTimeLineSequence* sequence, const struct KzuAnimationItem* animationItem);
/** Removes timeline entry containing animation item. Returns error if not found. If there are multiple entries containing the given item, it will
    remove the first one found. */
kzsError kzuTimeLineSequenceRemoveAnimationItem(const struct KzuTimeLineSequence* sequence, const struct KzuAnimationItem* animationClip);

/** Gets the active animation count on given time from given time line. */
kzUint kzuTimeLineSequenceGetActiveTimeLineEntryCount(const struct KzuTimeLineSequence* sequence, kzFloat time);

/** Removes all time line entries from the sequence. */
kzsError kzuTimeLineSequenceRemoveAllTimeLineEntries(const struct KzuTimeLineSequence* sequence);

/** Gets duration of the time line sequence. */
kzFloat kzuTimeLineSequenceGetDuration(const struct KzuTimeLineSequence* sequence);

/** Gets entry at given index from sequence, KZ_NULL if not found. */
struct KzuTimeLineEntry* kzuTimeLineSequenceGetEntryAtIndex(const struct KzuTimeLineSequence* sequence, kzUint index);
/** Gets number of entries from timeline sequence. */
kzUint kzuTimeLineSequenceGetEntryCount(const struct KzuTimeLineSequence* sequence);
/** Gets the timeline entry array from the sequence recursively, including children if there's additional sequences as children. */
kzsError kzuTimeLineSequenceGetEntriesRecursively(const struct KzcMemoryManager* memoryManager, const struct KzuTimeLineSequence* sequence, struct KzcDynamicArray** out_dynamicArray);


/** Cast animation clip->animation item. */
struct KzuAnimationItem* kzuTimeLineSequenceToAnimationItem(const struct KzuTimeLineSequence* timeLineSequence);
/** Cast animation item->animation clip. */
struct KzuTimeLineSequence* kzuTimeLineSequenceFromAnimationItem(const struct KzuAnimationItem* animationItem);
/** Removes entry from timeline. */
kzsError kzuTimeLineSequenceRemoveEntryFromTimeLine_private(const struct KzuTimeLineSequence* timeLineSequence, const struct KzuTimeLineEntry* timeLineEntry);


KZ_HEADER_END


#endif
