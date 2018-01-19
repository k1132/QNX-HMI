/**
* \file
* Virtual item list. Provides a list-like interface to a virtual collection of virtual items.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_VIRTUAL_ITEM_LIST_H
#define KZU_VIRTUAL_ITEM_LIST_H


#include <system/debug/kzs_error.h>
#include <system/kzs_types.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations. */
struct KzuObjectGenerator;
struct KzuUiListBox;
struct KzcVector3;
struct KzcMemoryManager;


/**
* \struct KzuVirtualItemList
* A virtual collection of items that supports iteration.
*/
struct KzuVirtualItemList;


/** Preferred element when exact match cannot be found. */
enum KzuVirtualItemListDirectionPreference
{
    KZU_VIRTUAL_ITEM_LIST_PREFER_PREVIOUS, /**< Prefer previous element. */
    KZU_VIRTUAL_ITEM_LIST_PREFER_NEXT /**< Prefer next element. */
};


/**
* Function that returns a one-dimensional width of a virtual item, based on it's dimensions.
*
* As an example, if used in a horizontal layout the function should return object's width.
* This value is used for determining how much space an item will need in the virtual item list.
*/
typedef kzFloat (*KzuVirtualItemWidthFunction)(const struct KzcVector3* size);

/** Function that returns size of an item in the list box. */
typedef kzsError (*KzuVirtualItemSizeFunction)(kzUint index, void* userData, struct KzcVector3* out_size);

/** Function that returns item count of a list box. */
typedef kzUint (*KzuVirtualItemCountFunction)(void* userData);


/**
* Iterator for KzuVirtualItemList.
* Keeps track of index, offset and item width of the item the iterator is pointing to.
*
* Note: This struct is to be used through the functions provided in kzu_virtual_item_list.h
*       The struct may change arbitrarily at any time and is public only to allow creation in stack.
*/
struct KzuVirtualItemIterator
{
    struct KzuVirtualItemList* itemList; /**< The virtual list iterated by the iterator. */
    
    kzInt index;          /**< How many indices the iterator has been moved. */
    kzFloat offset;       /**< How much the iterator has been moved. */
    kzFloat width;        /**< Width of the current item. */
    kzBool valid;         /**< Is iterator valid. */
};


/**
* Interval iterator for KzuVirtualItemList.
* Keeps track of indices, offsets and item widths at the ends of the interval.
*
* Handles operations with special care on the interval aspect.
*.
* Note: This struct is to be used through the functions provided in kzu_virtual_item_list.h
*       The struct may change arbitrarily at any time and is public only to allow creation in stack.
*/
struct KzuVirtualItemIntervalIterator
{
    struct KzuVirtualItemIterator leftIterator; /**< Iterator to the left end of the interval. */
    struct KzuVirtualItemIterator rightIterator; /**< Iterator to the right end of the interval. */
};


/** Returns whether the virtual item iterator is valid. */
kzBool kzuVirtualItemIteratorIsValid(const struct KzuVirtualItemIterator* iterator);

/** Sets the iterator invalid. */
void kzuVirtualItemIteratorInvalidate(struct KzuVirtualItemIterator* iterator);

/** Asks the iterator to update its width. */
kzsError kzuVirtualItemIteratorUpdateWidth(struct KzuVirtualItemIterator* iterator);

/** Gets offset of the right edge of the item pointed by the the iterator. */
kzFloat kzuVirtualItemIteratorGetRightEdge(const struct KzuVirtualItemIterator* iterator);

/** Gets offset of the center of the item pointed by the iterator. */
kzFloat kzuVirtualItemIteratorGetCenter(const struct KzuVirtualItemIterator* iterator);

/** Gets offset of the left edge of the item pointed by the iterator. */
kzFloat kzuVirtualItemIteratorGetLeftEdge(const struct KzuVirtualItemIterator* iterator);

/** Gets index of the item pointed by the iterator. */
kzUint kzuVirtualItemIteratorGetIndex(const struct KzuVirtualItemIterator* iterator);

/** Returns whether the iterator has a next item. */
kzBool kzuVirtualItemIteratorHasNext(const struct KzuVirtualItemIterator* iterator);

/** Returns whether the iterator has a previous item. */
kzBool kzuVirtualItemIteratorHasPrevious(const struct KzuVirtualItemIterator* iterator);

/** Gets index of the item after the item pointed by the iterator. */
kzUint kzuVirtualItemIteratorGetNextIndex(const struct KzuVirtualItemIterator* iterator);

/** Gets index of the item before the item pointed by the iterator. */
kzUint kzuVirtualItemIteratorGetPreviousIndex(const struct KzuVirtualItemIterator* iterator);

/** Iterates to the next item. */
kzsError kzuVirtualItemIteratorNext(struct KzuVirtualItemIterator* iterator);

/** Iterates to the previous item. */
kzsError kzuVirtualItemIteratorPrevious(struct KzuVirtualItemIterator* iterator);

/**
* Iterates the iterator such that the target offset is between iterator's left and right edges.
* If this is not possible, prefers the item in the preferred direction.
*/
kzsError kzuVirtualItemIteratorIterateToOffset(struct KzuVirtualItemIterator* iterator, kzFloat target,
                                               enum KzuVirtualItemListDirectionPreference directionPreference);


/** Patches the iterator to be consistent after an item addition. */
kzsError kzuVirtualItemIteratorPatchItemAdded(struct KzuVirtualItemIterator* iterator, kzUint addedItemIndex,
                                              const struct KzcVector3* addedItemSize);

/** Patches the iterator to be consistent after an item addition. */
kzsError kzuVirtualItemIteratorPatchItemRemoved(struct KzuVirtualItemIterator* iterator, kzUint removedItemIndex,
                                                const struct KzcVector3* removedItemSize);

/** Patches the iterator to be consistent after an item addition. */
kzsError kzuVirtualItemIteratorPatchItemReplaced(struct KzuVirtualItemIterator* iterator, kzUint replacedItemIndex,
                                                 const struct KzcVector3* removedItemSize, const struct KzcVector3* addedItemSize);

/** Patches the iterator to be consistent after a spacing change. */
kzsError kzuVirtualItemIteratorPatchSpacingChanged(struct KzuVirtualItemIterator* iterator, kzFloat oldSpacing);


/** Returns whether the virtual item iterator is valid. */
kzBool kzuVirtualItemIntervalIteratorIsValid(const struct KzuVirtualItemIntervalIterator* iterator);

/** Sets the iterator invalid. */
void kzuVirtualItemIntervalIteratorInvalidate(struct KzuVirtualItemIntervalIterator* iterator);

/** Returns a copy of the interval iterator's first edge iterator. */
struct KzuVirtualItemIterator kzuVirtualItemIntervalIteratorGetLeftIterator(const struct KzuVirtualItemIntervalIterator* iterator);

/** Returns a copy of the interval iterator's right edge iterator. */
struct KzuVirtualItemIterator kzuVirtualItemIntervalIteratorGetRightIterator(const struct KzuVirtualItemIntervalIterator* iterator);

/**
* Iterates the interval iterator's ends such that the left target offset will be between left iterator's left and right edges,
* and the right target offset will be between right iterator's left and right edges.
*
* If this is not possible, prefers the items in the preferred directions.
*/
kzsError kzuVirtualItemIntervalIteratorIterateToOffset(struct KzuVirtualItemIntervalIterator* iterator,
                                                       kzFloat leftTarget, enum KzuVirtualItemListDirectionPreference leftDirectionPreference,
                                                       kzFloat rightTarget, enum KzuVirtualItemListDirectionPreference rightDirectionPreference);
/**
* Returns the number of elements in the interval, including the edge elements.
* \see kzuVirtualItemListGetIntervalElementCount.
*/
kzUint kzuVirtualItemIntervalIteratorGetElementCount(const struct KzuVirtualItemIntervalIterator* iterator);


/** Patches the interval iterator to be consistent after an item addition. */
kzsError kzuVirtualItemIntervalIteratorPatchItemAdded(struct KzuVirtualItemIntervalIterator* iterator, kzUint addedItemIndex,
                                                      const struct KzcVector3* addedItemSize);

/** Patches the interval iterator to be consistent after an item removal. */
kzsError kzuVirtualItemIntervalIteratorPatchItemRemoved(struct KzuVirtualItemIntervalIterator* iterator, kzUint removedItemIndex,
                                                        const struct KzcVector3* removedItemSize);

/** Patches the interval iterator to be consistent after an item replacement. */
kzsError kzuVirtualItemIntervalIteratorPatchItemReplaced(struct KzuVirtualItemIntervalIterator* iterator, kzUint replacedItemIndex,
                                                         const struct KzcVector3* removedItemSize, const struct KzcVector3* addedItemSize);

/** Patches the interval iterator to be consistent after a spacing change. */
kzsError kzuVirtualItemIntervalIteratorPatchSpacingChanged(struct KzuVirtualItemIntervalIterator* iterator, kzFloat oldSpacing);


/**
* Creates a virtual item list that uses the given list box to provide item data.
*
* \param widthFunction Returns width from an object size.
* \param sizeFunction Returns size of an object by index.
* \param countFunction Returns total item count of virtual item list.
*/
kzsError kzuVirtualItemListCreate(const struct KzcMemoryManager* memoryManager,
                                  KzuVirtualItemWidthFunction widthFunction,
                                  KzuVirtualItemSizeFunction sizeFunction, void* sizeFunctionUserData,
                                  KzuVirtualItemCountFunction countFunction, void* countFunctionUserData,
                                  struct KzuVirtualItemList** out_itemList);
/** Deletes a virtual item list. */
kzsError kzuVirtualItemListDelete(struct KzuVirtualItemList* itemList);

/** Sets whether the virtual item list is looping. */
void kzuVirtualItemListSetLooping(struct KzuVirtualItemList* itemList, kzBool looping);
/** Gets whether the virtual item list is looping. */
kzBool kzuVirtualItemListIsLooping(const struct KzuVirtualItemList* itemList);

/** Sets spacing between items in the virtual item list. */
void kzuVirtualItemListSetSpacing(struct KzuVirtualItemList* itemList, kzFloat spacing);
/** Gets spacing between items in the virtual item list. */
kzFloat kzuVirtualItemListGetSpacing(const struct KzuVirtualItemList* itemList);


/**
* Gets the number of elements that are in between the left and right iterators, including the iterators.
*
* For example:
*     - kzuVirtualItemListGetIntervalElementCount(iterator, iterator) returns 1.
*     - kzuVirtualItemListGetIntervalElementCount(current, next) returns 2.
*
* Calling this function with invalid iterators results in undefined behavior.
*/
kzUint kzuVirtualItemListGetIntervalElementCount(const struct KzuVirtualItemIterator* leftIterator,
                                                 const struct KzuVirtualItemIterator* rightIterator);

/** Gets period length of virtual item list if it is known. Otherwise returns KZ_FALSE. */
kzBool kzuVirtualItemListGetPeriodLength(const struct KzuVirtualItemList* itemList, kzFloat* out_period);

/**
* Gets an iterator to the virtual item list.
* The iterator will point to the first item of the list, or be invalid.
*/
kzsError kzuVirtualItemListGetIterator(struct KzuVirtualItemList* itemList, struct KzuVirtualItemIterator* out_iterator);

/**
* Gets an interval iterator to the virtual item list.
* The iterator will be an empty interval with both ends pointing to the first item of the list, or invalid.
*/
kzsError kzuVirtualItemListGetIntervalIterator(struct KzuVirtualItemList* itemList, struct KzuVirtualItemIntervalIterator* out_iterator);


KZ_HEADER_END


#endif
