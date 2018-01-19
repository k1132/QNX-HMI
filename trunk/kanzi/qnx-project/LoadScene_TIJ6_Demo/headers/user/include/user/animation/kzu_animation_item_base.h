/**
* \file
* Animation item
* Private functions of base class for animations, clips and timeline.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_ANIMATION_ITEM_BASE_H
#define KZU_ANIMATION_ITEM_BASE_H


#include "kzu_animation_item.h"

#include <user/resource/kzu_resource_base.h>

#include <system/debug/kzs_error.h>
#include <system/kzs_types.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations. */
struct KzuAnimationPlayer;
struct KzuUIDomain;
struct KzcMemoryManager;


/** Defines functions for different object node types. */
struct KzuAnimationItemClass
{
    /** Update function for the animation */
    kzsError (*kzuAnimationItemUpdate)(struct KzuAnimationPlayer* animationPlayer, const struct KzuAnimationItem* animationItem,
                                       kzFloat time);
    /** Prepares animation item to be updated. */
    kzsError (*kzuAnimationItemPrepare)(struct KzuAnimationPlayer* animationPlayer, const struct KzuAnimationItem* animationItem);
    /** Gets duration of the animation item. */
    kzFloat (*kzuAnimationItemGetDuration)(const struct KzuAnimationItem* animationItem);
    /** Finishes animation item, i.e. animation item ends. */
    kzsError (*kzuAnimationItemFinish)(struct KzuAnimationPlayer* animationPlayer, const struct KzuAnimationItem* animationItem);
    /** Deletes animation item */
    kzsError (*kzuAnimationItemDelete)(struct KzuAnimationItem* animationItem);
    /** Starts animation item. */
    kzsError (*kzuAnimationItemStart)(struct KzuAnimationPlayer* animationPlayer, const struct KzuAnimationItem* animationItem);
    /** Clears animation item cache. */
    kzsError (*kzuAnimationItemClearCache)(const struct KzuAnimationItem* animationItem);
};


/** Structure for animation item. */
struct KzuAnimationItem
{
    struct KzuResource resource; /**< Inherited from resource. */
    struct KzuUIDomain* uiDomain; /**< UI Domain. */

    enum KzuAnimationItemType type; /**< Type of the animation item. */
    kzMutableString name; /**< Name for the animation item. */

    kzBool changeFlagSet; /**< Is the change flag set. */

    struct KzuAnimationItemClass animationItemClass; /**< Class of the animation item. E.g. animation, clip or sequence. */
};


/** Creates new animation item. */
kzsError kzuAnimationItemCreate_protected(struct KzuAnimationItem* animationItem, struct KzuUIDomain* uiDomain, enum KzuAnimationItemType type,
                                          kzString name, const struct KzuAnimationItemClass* itemClass);

/** Deletes animation item. */
kzsError kzuAnimationItemDelete_protected(struct KzuAnimationItem* animationItem);

/** Sets UI domain to animation item. */
void kzuAnimationItemSetUIDomain_protected(struct KzuAnimationItem* animationItem, struct KzuUIDomain* uiDomain);


KZ_HEADER_END


#endif
