/**
* \file
* The base class for animation related classes.
* The base class for KzuAnimation, KzuAnimationClip and KzuTimeLineSequence.
* 
* \see \ref kzu_animation.h, \ref kzu_animation_clip.h, \ref kzu_time_line_sequence.h.
*
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_ANIMATION_ITEM_H
#define KZU_ANIMATION_ITEM_H


#include <user/resource/kzu_resource_common.h>

#include <system/debug/kzs_error.h>
#include <system/kzs_types.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/** Types of animation items. */
enum KzuAnimationItemType
{
    KZU_ANIMATION_ITEM_TYPE_ANIMATION = 0,
    KZU_ANIMATION_ITEM_TYPE_CLIP,
    KZU_ANIMATION_ITEM_TYPE_TIME_LINE_SEQUENCE
};


/* Forward declarations. */
struct KzuAnimationPlayer;


/** 
 * \struct KzuAnimationItem
 * Animation item is the base class of KzuAnimation, KzuAnimationClip and KzuTimeLineSequence.
 */
struct KzuAnimationItem;


/** Resource type identifier for animation item. */
extern const KzuResourceType KZU_RESOURCE_TYPE_ANIMATION_ITEM;


/** Gets type of animation item. */
enum KzuAnimationItemType kzuAnimationItemGetType(const struct KzuAnimationItem* animationItem);

/** Updates animation item. */
kzsError kzuAnimationItemUpdate(struct KzuAnimationPlayer* animationPlayer, const struct KzuAnimationItem* animationItem,
                                kzFloat targetTime);

/** Prepares animation item for update. */
kzsError kzuAnimationItemPrepare(struct KzuAnimationPlayer* animationPlayer, const struct KzuAnimationItem* animationItem);
/** Finishes an animation item. */
kzsError kzuAnimationItemFinish(struct KzuAnimationPlayer* animationPlayer, const struct KzuAnimationItem* animationItem);
/** Deletes animation item. */
kzsError kzuAnimationItemDelete(struct KzuAnimationItem* animationItem);
/** Starts (launches) animation item. */
kzsError kzuAnimationItemStart(struct KzuAnimationPlayer* animationPlayer, const struct KzuAnimationItem* animationItem);
/** Clears the animation item caches. */
kzsError kzuAnimationItemClearCache(const struct KzuAnimationItem* animationItem);

/** Gets duration of the animation item. */
kzFloat kzuAnimationItemGetDuration(const struct KzuAnimationItem* animationItem);
/** Sets change flag for animation item. */
void kzuAnimationItemSetChangeFlag(struct KzuAnimationItem* animationItem, kzBool isSet);
/** Returns if animation item change flag is set. */
kzBool kzuAnimationItemIsChangeFlagSet(const struct KzuAnimationItem* animationItem);


/** Sets name for the animation clip. */
kzsError kzuAnimationItemSetName(struct KzuAnimationItem* animationItem, kzString name);
/** Gets name from the animation clip. */
kzString kzuAnimationItemGetName(const struct KzuAnimationItem* animationItem);

/** Converts animation item to resource. */
struct KzuResource* kzuAnimationItemToResource(const struct KzuAnimationItem* animationItem);
/** Converts animation item from resource. */
struct KzuAnimationItem* kzuAnimationItemFromResource(const struct KzuResource* resource);
/** Casts animation item from resource, returns ::KZ_NULL if the resource is of invalid type. */
struct KzuAnimationItem* kzuAnimationItemCastFromResource(const struct KzuResource* resource);


KZ_HEADER_END


#endif
