/**
* \file
* Time line entry.
* 
* Private functions and structures of the timeline entry.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_TIME_LINE_ENTRY_PRIVATE_H
#define KZU_TIME_LINE_ENTRY_PRIVATE_H

#include <user/properties/kzu_property_common.h>

#include <system/kzs_types.h>
#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations */
struct KzuAnimationKey;
struct KzuAnimationPlayer;
struct KzuAnimationClip;
struct KzuAnimationItem;
struct KzuAnimation;
struct KzuAnimationNode;
struct KzuTimeLineSequence;
struct KzuPropertyType;
struct KzuPropertyManager;
struct KzcMemoryManager;
struct KzuObjectNode;
struct KzuAnimationPlayerModifierStackEntry;
struct KzcHashMap;
struct KzcDynamicArray;


/** Returns if updating this entry is required, i.e. values needs to be refreshed .*/
kzBool kzuTimeLineEntryIsUpdateRequired_private(const struct KzuTimeLineEntry* timeLineEntry);
/** Refresh property driven animation so that it will be updated next time. */
void kzuTimeLineEntryRefreshPropertyDrivenAnimation_private(struct KzuTimeLineEntry* timeLineEntry);

/** Clears all caches related to timeline entry. */
kzsError kzuTimeLineEntryClearCache_private(struct KzuTimeLineEntry* timeLineEntry);

/** Private function for setting animation item for entry. */
kzsError kzuTimeLineEntrySetAnimationItem_private(struct KzuTimeLineEntry* entry, struct KzuAnimationItem* item);

/** Resolves input object for the property driven timeline entry. The input object will be stored into timeline entry.
 * \param player Player to run the entry, can be null if cachedObject is not null.
 * \param timeLineEntry Entry to resolve the input property type.
 * \param cachedInputObject If input object is already cached, it can be passed directly.
 */
kzsError kzuTimeLineEntryResolveInputPropertyTypeObject_private(const struct KzuAnimationPlayer* player, struct KzuTimeLineEntry* timeLineEntry, void* cachedObject);


/** Begins the update of the property driven animation for specified player. */
void kzuTimeLineEntryPropertyDrivenAnimationBegin_private(struct KzuTimeLineEntry* timeLineEntry, struct KzuAnimationPlayer* player);
/** Marks property driven animation finished, i.e. it needs not to be refreshed next frame, unless property has been changed. */
void kzuTimeLineEntryUpdateFinished_private(struct KzuTimeLineEntry* timeLineEntry);

/** Stores cached animation. */
kzsError kzuTimeLineEntryStoreCachedAnimation_private(struct KzuTimeLineEntry* timeLineEntry, struct KzuAnimation* animation, struct KzuAnimationPlayer* player,
                                                      void* object, struct KzuPropertyType* propertyType, kzFloat time);
/** Gets cached animation target. */
kzBool kzuTimeLineEntryGetCachedAnimationTarget_private(const struct KzuTimeLineEntry* timeLineEntry, const struct KzuAnimation* animation, const struct KzuAnimationPlayer* player,
    void** out_object, struct KzuPropertyType** out_propertyType);

/** Gets a list of value modifiers attached to a timeline entry. */
kzsError kzuTimeLineEntryGetValueModifiers_private(const struct KzcMemoryManager* memoryManager, const struct KzuTimeLineEntry* timeLineEntry, const struct KzuAnimationPlayer* player, struct KzcDynamicArray** out_valueModifiers);
/** Gets value modifier from timeline entry & player. */
kzBool kzuTimeLineEntryGetValueModifier_private(const struct KzuTimeLineEntry* timeLineEntry, const struct KzuAnimationPlayer* player, const void* object, const struct KzuPropertyType* propertyType,
                                                enum KzuPropertyField attribute, struct KzuAnimationPlayerModifierStackEntry** out_modifierStackEntry);
/** Clears all cached animations. */
kzsError kzuTimeLineEntryClearCachedAnimations_private(struct KzuTimeLineEntry* timeLineEntry);
/** Clears entry specific caches, such as animations. */
kzsError kzuTimeLineEntryClearEntryCaches_private(struct KzuTimeLineEntry* entry);

/** Sets property manager for timeline entry. */
kzsError kzuTimeLineEntrySetPropertyManager_private(struct KzuTimeLineEntry* timeLineEntry, struct KzuPropertyManager* propertyManager);
/** Sets owner timeline sequence for timeline entry. */
void kzuTimeLineEntrySetOwnerSequence_private(struct KzuTimeLineEntry* timeLineEntry, struct KzuTimeLineSequence* sequence);
/** Returns owner timeline sequence from timeline entry. */
struct KzuTimeLineSequence* kzuTimeLineEntryGetOwnerSequence_private(const struct KzuTimeLineEntry* timeLineEntry);

/** Sets reference node for timeline entry. */
void kzuTimeLineEntrySetReferenceNode_private(struct KzuTimeLineEntry* timeLineEntry, struct KzuAnimationNode* node);
/** Returns reference node from timeline entry. */
void* kzuTimeLineEntryGetReferenceNode_private(const struct KzuTimeLineEntry* timeLineEntry);


/** Key structure for storing modifier stack entry. */
struct KzuTimeLineEntryModifierStackKey
{
    void* object; /**< Object reference. */
    struct KzuPropertyType* propertyType; /**< Property type reference. */
    enum KzuPropertyField attribute; /**< Attribute reference. */
};

/** Hash code implementation for modifier stack entry keys. */
kzU32 kzuTimeLineEntryHashCodeFromModifierStack_private(const void* key);
/** Comparator for modifier stack keys. */
kzInt kzuTimeLineEntryCompareModifierStackKeys_private(const void* first, const void* second);


KZ_HEADER_END


#endif
