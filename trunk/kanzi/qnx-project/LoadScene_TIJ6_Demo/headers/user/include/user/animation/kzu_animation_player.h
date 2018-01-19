/**
* \file
* Animation player.
* KzuAnimationPlayer contains a collection of time line entries (KzuTimeLineEntry), which are used to track when to play the animations and how to blend
* animation values together when there are multiple simultaneous animations for the same property. The time line entries are automatically created
* when calling ::kzuAnimationPlayerAddAnimationItem() for adding a KzuAnimation, KzuAnimationClip or KzuTimeLineSequence to the animation player.
* Every KzuUIDomain has an animation player that is called the root player (accessible by using ::kzuUIDomainGetTaskScheduler() and ::kzuTaskSchedulerGetAnimationPlayer()).
* An animation player should be added as a child of the root player (by using ::kzuTaskSchedulerAttachAnimationPlayer()) when the animation player
* should start playing immediately. It is also possible to use the player manually by calling ::kzuAnimationPlayerUpdate() with desired delta times.
*
* KzuAnimationPlayer stores all of its time line entries into a KzuTimeLineSequence. This collection can be accessed with ::kzuAnimationPlayerGetTimeLineSequence() and
* replaced with ::kzuAnimationPlayerSetTimeLineSequence().
*
* A KzuAnimationPlayer is automatically created and added to the root player when attaching an animation to an object node with ::kzuObjectNodeAddAnimationItem().
* This animation player can be accessed with ::kzuObjectNodeGetAnimationPlayer(). It is also possible to create and run an animation player manually as the following
* example code shows.
*
* Animation Player Example Code
* ----
* The following example code demonstrates how it is possible to use an animation player manually for maximum control. Notice that in most cases using
* ::kzuObjectNodeAddAnimationItem() is enough (see the example code in \ref kzu_animation_clip.h and \ref kzu_animation.h).
\code{.c}
    kzsError KzuAnimationPlayerExample()
    {
        kzsError result;
        kzFloat timesAndValues[10] = { 0.0f, 0.0f,
                                       1.0f, 2.0f,
                                       2.0f, 10.0f,
                                       3.0f, 2.0f,
                                       4.0f, 0.0f };
        struct KzuAnimation* animation;
        kzUint i;
        struct KzuObjectNode* objectNode;
        struct KzuAnimationPlayer* animationPlayer;
        struct KzuTimeLineEntry* entry1, *entry2;

        result = kzuAnimationCreateFloatTarget(memoryManager, uiDomain, kzuPropertyTypeGetName(KZU_PROPERTY_TYPE_TRANSFORMATION),
                                               KZU_PROPERTY_FIELD_TRANSLATION_X, &animation);
        kzsErrorForward(result);

        for (i = 0; i < 10; i += 2)
        {
            struct KzuAnimationKeyFloat* key;
            struct KzuAnimationKey* animationKey;

            result = kzuAnimationKeyFloatCreate(memoryManager, timesAndValues[i], timesAndValues[i + 1],
                                                KZU_ANIMATION_INTERPOLATION_LINEAR, &key);
            kzsErrorForward(result);

            animationKey = kzuAnimationKeyFloatToAnimationKey(key);
            result = kzuAnimationAddKeyFrame(animation, animationKey);
            kzsErrorForward(result);
        }

        // Create a sphere to animate.
        {
            struct KzuMesh* mesh;
            struct KzuMeshNode* meshNode;

            result = kzuMeshCreateSphere(kzuUIDomainGetResourceManager(uiDomain), "Sphere", 7.0f, 32, 32, KZ_NULL, &mesh);
            kzsErrorForward(result);

            result = kzuMeshNodeCreate(memoryManager, "mesh node", uiDomain, mesh, &meshNode);
            kzsErrorForward(result);

            result = kzuResourceRelease(kzuMeshToResource(mesh));
            kzsErrorForward(result);

            objectNode = kzuMeshNodeToObjectNode(meshNode);
            result = kzuObjectNodeAddChild(kzuSceneToObjectNode(scene), objectNode);
            kzsErrorForward(result);
        }

        // Create an animation player and add the animation to it.
        result = kzuAnimationPlayerCreate(memoryManager, uiDomain, objectNode, &animationPlayer);
        kzsErrorForward(result);
        result = kzuAnimationPlayerAddAnimationItem(animationPlayer, kzuUIDomainGetPropertyManager(uiDomain),
                                                    kzuAnimationToAnimationItem(animation), KZ_FALSE, 1, &entry1);
        kzsErrorForward(result);
        // Add another animation 0.5s after the first animation.
        kzuAnimationPlayerSetTime(animationPlayer, 0.5f);
        result = kzuAnimationPlayerAddAnimationItem(animationPlayer, kzuUIDomainGetPropertyManager(uiDomain),
                                                    kzuAnimationToAnimationItem(animation), KZ_FALSE, 1, &entry2);
        kzsErrorForward(result);

        // When the animations are played at the same time, add their values together.
        kzuTimeLineEntrySetWeightBlendMode(entry1, KZU_TIME_LINE_ENTRY_WEIGHT_BLEND_MODE_ADDITIVE);
        kzuTimeLineEntrySetWeightBlendMode(entry2, KZU_TIME_LINE_ENTRY_WEIGHT_BLEND_MODE_ADDITIVE);

        // Start playing from 0s
        kzuAnimationPlayerSetTime(animationPlayer, 0.0f);

        // Verify that the animation changes the X translation of the sphere.
        for (i = 0; i < 6; ++i)
        {
            struct KzcMatrix4x4 transform;
            struct KzcVector3 translation;

            result = kzuAnimationPlayerUpdate(animationPlayer, i == 0 ? 0.0f : 1.0f); // the first step is 0
            kzsErrorForward(result);

            transform = kzuObjectNodeGetMatrix4x4PropertyDefault(objectNode, KZU_PROPERTY_TYPE_TRANSFORMATION);
            kzcMatrix4x4GetTranslation(&transform, &translation);
            switch (i)
            {
                case 0: // first and second animation has played for 0s
                    kzsAssert(kzsFabsf(translation.data[0] - 0.0f) < 0.001f);
                    break;
                case 1: // first animation has played for 1s, the second for 0.5s
                    kzsAssert(kzsFabsf(translation.data[0] - 3.0f) < 0.001f);
                    break;
                case 2: // first animation has played for 2s, the second for 1.5s
                    kzsAssert(kzsFabsf(translation.data[0] - 16.0f) < 0.001f);
                    break;
                case 3: // first animation has played for 3s, the second for 2.5s
                    kzsAssert(kzsFabsf(translation.data[0] - 8.0f) < 0.001f);
                    break;
                case 4: // first animation has played for 4s (end), the second for 3.5s
                    kzsAssert(kzsFabsf(translation.data[0] - 1.0f) < 0.001f);
                    break;
                case 5: // first animation has ended, the second for 4s (end)
                    kzsAssert(kzsFabsf(translation.data[0] - 0.0f) < 0.001f);
                    break;
                default:
                    kzsAssert(KZ_FALSE);
            }
        }

        result = kzuAnimationPlayerDelete(animationPlayer);
        kzsErrorForward(result);
        result = kzuResourceRelease(kzuAnimationItemToResource(kzuAnimationToAnimationItem(animation)));
        kzsErrorForward(result);

        kzsSuccess();
    }
\endcode
* 
* \see \ref kzu_time_line_entry.h, \ref kzu_time_line_sequence.h.
*
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_ANIMATION_PLAYER_H
#define KZU_ANIMATION_PLAYER_H


#include <user/common/kzu_user.h>

#include <core/util/collection/kzc_dynamic_array.h>

#include <system/kzs_types.h>
#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations. */
struct KzuTimeLineEntry;
struct KzuAnimationItem;
struct KzuPropertyManager;
struct KzuUIDomain;
struct KzuPropertyType;
struct KzuMessageDispatcher;
struct KzuTimeLineSequence;
struct KzuObjectNode;
struct KzcMemoryManager;
struct KzcHashMap;
struct KzuAnimationNode;


/** Profiling constant string for regular animation samples. */
#define KZU_ANIMATION_PLAYER_PROFILING_SAMPLE_COMPOSE_REGULAR "kzuAnimationPlayerComposeAnimationSampleRegular"
/** Profiling constant string for blended animation samples. */
#define KZU_ANIMATION_PLAYER_PROFILING_SAMPLE_COMPOSE_BLEND "kzuAnimationPlayerComposeBlendSample"
/** Profiling constant string for updating whole animation player. */
#define KZU_ANIMATION_PLAYER_PROFILING_UPDATE "kzuAnimationPlayerUpdate"
/** Profiling constant string for updating entries. */
#define KZU_ANIMATION_PLAYER_PROFILING_UPDATE_ENTRIES "kzuAnimationPlayerUpdateEntries"
/** Profiling constant string for sorting entries. */
#define KZU_ANIMATION_PLAYER_PROFILING_SORT_ENTRIES "kzuAnimationPlayerSortEntries"
/** Profiling constant string for building graph cache. */
#define KZU_ANIMATION_PLAYER_PROFILING_GRAPH_CACHE "kzuAnimationPlayerRemoveGraphCache"
/** Profiling constant string for player invalidation. */
#define KZU_ANIMATION_PLAYER_PROFILING_IS_INVALIDATED "kzuAnimationPlayerIsInvalidated"


/**
 * \struct KzuAnimationPlayer
 * Animation Player.
 * Player contains collection of time line entries, which are used to track when to play the animations.
 */
struct KzuAnimationPlayer;


/** Allocates memory for animation player and initializes it.
 * \param memoryManager The memory manager to use.
 * \param uiDomain The UI domain to use.
 * \param attachedObjectNode Object node that owns the animation player. ::KZ_NULL if none, in this case message dispatching is not supported.
 * \param out_animationPlayer A pointer that is set to point to the new animation player on success.
 * \return ::KZS_SUCCESS on success.
 */
kzsError kzuAnimationPlayerCreate(const struct KzcMemoryManager* memoryManager, struct KzuUIDomain* uiDomain,
                                  struct KzuObjectNode* attachedObjectNode, struct KzuAnimationPlayer** out_animationPlayer);
/** Deallocates memory reserved for animation player. */
kzsError kzuAnimationPlayerDelete(struct KzuAnimationPlayer* animationPlayer);
/** Gets UI domain associated to animation player. */
struct KzuUIDomain* kzuAnimationPlayerGetUIDomain(const struct KzuAnimationPlayer* player);

/** Updates animations in player.
 * \param player The animation player.
 * \param deltaTime Seconds elapsed since the last update.
 * \return ::KZS_SUCCESS on success.
 */
kzsError kzuAnimationPlayerUpdate(struct KzuAnimationPlayer* player, kzFloat deltaTime);
/** Sets the animation player to the given time.
 * \param player The animation player.
 * \param time The time in seconds.
 */
void kzuAnimationPlayerSetTime(struct KzuAnimationPlayer* player, kzFloat time);

/** Sets pause state of the animation player. */
void kzuAnimationPlayerSetPaused(struct KzuAnimationPlayer* player, kzBool paused);
/** Check whether or not the animation player is paused.
 * \param player The animation player.
 * \return ::KZ_TRUE if the player is currently paused. ::KZ_FALSE if not.
 */
kzBool kzuAnimationPlayerIsPaused(const struct KzuAnimationPlayer* player);
/** Sets pausing enabled for player. Disabling pausing can be useful for players that are not wanted to be paused when main player pauses, such as preview camera animations. */
void kzuAnimationPlayerSetPausingEnabled(struct KzuAnimationPlayer* player, kzBool pausingEnabled);
/** Returns current time of the animation player. */
kzFloat kzuAnimationPlayerGetTime(const struct KzuAnimationPlayer* player);

/** Sets animation player enabled, so that all its animations will be effectively executed and child players will be evaluated. */
void kzuAnimationPlayerSetEnabled(struct KzuAnimationPlayer* player, kzBool enabled);
/** Returns if animation player is enabled. */
kzBool kzuAnimationPlayerIsEnabled(const struct KzuAnimationPlayer* player);

/** Adds new time line entry to the player. */
kzsError kzuAnimationPlayerAddTimeLineEntry(struct KzuAnimationPlayer* player, struct KzuTimeLineEntry* timeLineEntry);
/** Removes time line entry from the player if entry is found. 
 * \param removeRecursively Removes and inspects entry also child players.
 */
kzsError kzuAnimationPlayerRemoveTimeLineEntry(struct KzuAnimationPlayer* player, struct KzuTimeLineEntry* timeLineEntry, kzBool removeRecursively);
/** Sets a time line sequence to the player. */
kzsError kzuAnimationPlayerSetTimeLineSequence(struct KzuAnimationPlayer* player, struct KzuTimeLineSequence* timeLineSequence);
/** Returns time line sequence from the player. */
struct KzuTimeLineSequence* kzuAnimationPlayerGetTimeLineSequence(const struct KzuAnimationPlayer* player);

/** Adds animation clip to player's current time. */
kzsError kzuAnimationPlayerAddAnimationItem(struct KzuAnimationPlayer* player, struct KzuPropertyManager* propertyManager, struct KzuAnimationItem* animationItem, kzBool reverse,
                                            kzInt repeatCount, struct KzuTimeLineEntry** out_entry);

/** Finds animation item from player, returns the first found hit. */
kzsError kzuAnimationPlayerFindAnimationItem(struct KzuAnimationPlayer* player, const struct KzuAnimationItem* animationItem, struct KzuAnimationPlayer** out_animationPlayer, struct KzuTimeLineEntry** out_timeLineEntry);


/** Returns boolean indicating if given time line entry is finished on the animation players time line. */
kzBool kzuAnimationPlayerGetTimeLineEntryFinished(const struct KzuAnimationPlayer* player, const struct KzuTimeLineEntry* timeLineEntry);

/** Adds child animation player for parent animation player. */
kzsError kzuAnimationPlayerAddChildPlayer(struct KzuAnimationPlayer* parentPlayer, struct KzuAnimationPlayer* childPlayer);
/** Removes child player from parent. */
kzsError kzuAnimationPlayerRemoveFromParent(struct KzuAnimationPlayer* player);
/** Removes player from all its child players. */
void kzuAnimationPlayerRemoveFromChildren(struct KzuAnimationPlayer* player);
/** Gets child animation players from player. */
struct KzcDynamicArrayIterator kzuAnimationPlayerGetChildPlayers(const struct KzuAnimationPlayer* player);
/** Returns the parent player. KZ_NULL if no parent. */
struct KzuAnimationPlayer* kzuAnimationPlayerGetParentPlayer(const struct KzuAnimationPlayer* player);
/** Gets root player from animation player. Returns self if this is the root. */
struct KzuAnimationPlayer* kzuAnimationPlayerGetRootPlayer(struct KzuAnimationPlayer* player);
/** Invalidates cached entry graph of the animation player. */
void kzuAnimationPlayerInvalidateEntryGraph(struct KzuAnimationPlayer* player);

/** Clears timeline entries from the animation player.
* \param clearChildren are the children cleared recursively.
*/
kzsError kzuAnimationPlayerClearTimeLineEntries(struct KzuAnimationPlayer* player, kzBool clearChildren);
/** Refresh all property driven animations recursively. */
void kzuAnimationPlayerRefreshPropertyDrivenAnimations(const struct KzuAnimationPlayer* player);

/** Private function for getting attached object node from animation player. */
struct KzuObjectNode* kzuAnimationPlayerGetAttachedObjectNode(const struct KzuAnimationPlayer* player);
/** Gets message dispatcher from animation player. */
struct KzuMessageDispatcher* kzuAnimationPlayerGetMessageDispatcher(const struct KzuAnimationPlayer* player);

/** Returns quick memory manager from animation player. */
struct KzcMemoryManager* kzuAnimationPlayerGetQuickMemoryManager(struct KzuAnimationPlayer* player);


KZ_HEADER_END


#endif
