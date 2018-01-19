/**
* \file
* Animation player private functions.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_ANIMATION_PLAYER_PRIVATE_H
#define KZU_ANIMATION_PLAYER_PRIVATE_H


#include <user/properties/kzu_property_common.h>
#include <user/properties/kzu_property_manager.h>
#include <user/animation/kzu_time_line_entry.h>

#include <system/kzs_types.h>
#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations. */
struct KzuAnimationPlayer;
struct KzuAnimationSample;
struct KzuPropertyManager;
struct KzuPropertyType;
struct KzuTimeLineEntry;
struct KzuTimeLineSequence;


/** Specifies structure for modifier stack entry. */
struct KzuAnimationPlayerModifierStackEntry
{
    void* object; /**< Object in modifier stack. */
    struct KzuPropertyType* propertyType; /**< Property type in modifier stack. */
    struct KzuPropertyManager* propertyManager; /**< Attached property manager. */
    struct KzuAnimationPlayer* player; /**< Associated animation player. */
    kzFloat value; /**< Stored value. */
    kzFloat startValue; /**< Value in beginning. */
    kzBool relative; /**< If the entry is relative. */
    enum KzuPropertyField attribute; /**< Stored attribute. */
    struct KzuTimeLineEntry* timelineEntry;  /**< Associated KzuTimeLineEntry. */
};

/** Animation sample, used for composing 1 or multiple inputs to single output value. */
struct KzuAnimationSample
{
    kzFloat value; /**< Calculated output value for the sample. */
    struct KzuTimeLineEntry* timeLineEntry; /**< Entry used in animation. */
    struct KzuAnimation* animation; /**< Pointer to animation. */
    kzFloat relativeTime; /**< Relative time for the animation, gathered from the animation clip. */
    kzFloat time; /**< Time in which the animation was updated. */
    kzBool relative; /**< Is the animation specified relative to the base value. */

    struct KzuAnimationPlayer* player; /**< Player for the sample. */
    struct KzuPropertyType* propertyType; /**< Animated property type. */
    struct KzuPropertyManager* propertyManager; /**< Property manager. */
    enum KzuPropertyField attribute; /**< Animated attribute. */
    void* targetObject; /**< Target object of the sample. */
    void* propertyInputObject; /**< Input object of the sample. */
    kzMutableString propertyInputObjectPath; /**< Input object path for the sample. */

    kzBool consumed; /**< Is the blend value consumed, internally used in output calculation step. */
    kzBool invalidMultiSample; /**< Is this multi sampled output invalid. */
};



/** Gets time of timeline entry, based on player time. For property driven animations this should be 0.0f. */
kzFloat kzuTimeLineEntryGetTime_private(const struct KzuTimeLineEntry* timeLineEntry, kzFloat playerTime);

/** Sets context object for animation player. Can be object node, material, group or anything that can be animated. */
void kzuAnimationPlayerSetContextObject_private(struct KzuAnimationPlayer* player, const void* contextObject);
/** Returns context object from animation player. Can be object node, material, group or anything that can be animated. */
const void* kzuAnimationPlayerGetContextObject_private(const struct KzuAnimationPlayer* player);



/** Private function for setting animation player animate relatively (relative as taking the original value into account, used in relative animation clips). */
void kzuAnimationPlayerSetAnimationRelative_private(struct KzuAnimationPlayer* player, kzBool relative);
/** Private function for getting information if animation player is animating relatively (relative as taking the original value into account). */
kzBool kzuAnimationPlayerIsAnimationRelative_private(const struct KzuAnimationPlayer* player);


/** Sets currently active entry for player. */
void kzuAnimationPlayerSetCurrentEntry_private(struct KzuAnimationPlayer* player, struct KzuTimeLineEntry* entry);
/** Gets currently updated entry from player. */
struct KzuTimeLineEntry* kzuAnimationPlayerGetCurrentEntry_private(const struct KzuAnimationPlayer* player);
/** Sets relative time for animation player, used in animation clips. */
void kzuAnimationPlayerSetRelativeAnimationItemTime_private(struct KzuAnimationPlayer* player, kzFloat relativeTime);


/** Sets effective weight blend mode to the player. */
void kzuAnimationPlayerSetCurrentWeightBlendMode_private(struct KzuAnimationPlayer* player,  enum KzuTimeLineEntryWeightBlendMode weightBlendMode);
/** Gets effective weight blend mode from entry. */
enum KzuTimeLineEntryWeightBlendMode kzuAnimationPlayerGetCurrentWeightBlendMode_private(const struct KzuAnimationPlayer* player);
/** Sets blend animation value. */
kzsError kzuAnimationPlayerCreateAnimationSample_private(struct KzuAnimationPlayer* player, struct KzuPropertyManager* propertyManager, 
                                                         struct KzuAnimation* animation, kzFloat time, enum KzuPropertyField attribute, struct KzuAnimationSample** out_sample);
/** Composes blend animations from the animations that have been specified for player. */
kzsError kzuAnimationPlayerComposeAnimationSamples_private(struct KzuAnimationPlayer* player);
/** Deletes entry from animation player, must not be called anywhere else than inside kzuAnimationPlayerUpdate. */
kzsError kzuAnimationPlayerMarkEntryDeleted_private(struct KzuAnimationPlayer* player, struct KzuTimeLineEntry* entry);

/** Property modifier callback. */
kzsError kzuAnimationPlayerPropertyModifierCallback_private(const void* object, const struct KzuPropertyType* propertyType, void* valueSource, enum KzuPropertyNotificationReason reason, void* userData);
/** Remove a dead entry from the animation player, to remove value preservation from player. */
kzsError kzuAnimationPlayerRemoveDeadEntryPropertyModifier_private(const struct KzuAnimationPlayer* player, const struct KzuPropertyManager* propertyManager, 
                                                                   const void* object, const struct KzuPropertyType* propertyType, enum KzuPropertyField attribute,
                                                                   const struct KzuTimeLineEntry* timelineEntry);
/** Adds alive entry modifier. */
kzsError kzuAnimationPlayerAddAliveEntryPropertyModifier_private(const struct KzuAnimationPlayer* player, struct KzuAnimationPlayerModifierStackEntry* modifierStackEntry);
/** Removes alive entry modifier. */
kzsError kzuAnimationPlayerRemoveAliveEntryPropertyModifier_private(const struct KzuAnimationPlayer* player, struct KzuAnimationPlayerModifierStackEntry* modifierStackEntry);

/** Returns if animation player update is in progress. */
kzBool kzuAnimationPlayerIsUpdateInProgress_private(const struct KzuAnimationPlayer* player);

/** Sets effective animation target for animation player. */
void kzuAnimationPlayerSetEffectiveAnimationTarget_private(struct KzuAnimationPlayer* player, void* targetObject, struct KzuPropertyType* propertyType);
/** Returns effective target object from animation player. */
void* kzuAnimationPlayerGetEffectiveAnimationTargetObject_private(const struct KzuAnimationPlayer* player);
/** Returns effective target object property type from animation player. */
struct KzuPropertyType* kzuAnimationPlayerGetEffectiveAnimationTargetPropertyType_private(const struct KzuAnimationPlayer* player);
/** Helper function for calculating value for single sample. */
kzsError kzuAnimationPlayerCalculateValueForSample_private(struct KzuAnimationSample* sample, kzBool* out_validSample);
/** Clears entry graph of animation player. */
kzsError kzuAnimationPlayerClearEntryGraph_private(struct KzuAnimationPlayer* player);

/** Kanzi internal function for KzuTimeLineEntry. */
void kzuAnimationNodeClearEntry_private(struct KzuAnimationNode* animationNode);


KZ_HEADER_END


#endif
