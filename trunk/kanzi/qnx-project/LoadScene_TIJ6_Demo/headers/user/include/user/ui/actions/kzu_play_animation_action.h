/**
* \file
* Play animation action.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_PLAY_ANIMATION_ACTION_H
#define KZU_PLAY_ANIMATION_ACTION_H


#include "kzu_action_common.h"

#include <user/properties/kzu_property_base.h>

#include <system/kzs_types.h>
#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations. */
struct KzcMemoryManager;
struct KzuAction;
struct KzuUIDomain;


/** Action type identifier for animation action. */
extern const KzuActionType KZU_ACTION_TYPE_ANIMATION_ACTION;


/** Create a play animation action. */
kzsError kzuPlayAnimationActionCreate(const struct KzcMemoryManager* memoryManager, struct KzuUIDomain* uiDomain, struct KzuAction** out_action);


KZ_HEADER_END


#endif
