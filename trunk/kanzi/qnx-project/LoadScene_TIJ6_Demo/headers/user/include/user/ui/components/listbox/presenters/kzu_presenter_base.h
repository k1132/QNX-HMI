/**
* \file
* Defines base class for items that handle scrolling of layouts.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_PRESENTER_BASE_H
#define KZU_PRESENTER_BASE_H


#include <system/kzs_types.h>
#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations. */
struct KzcMemoryManager;
struct KzuPresenter;
struct KzuUiListBoxItem;
struct KzuPresenterClass;
struct KzuPresenterData;
struct KzuPresenter;
struct KzcVector3;
struct KzcVector2;
struct KzuObjectNode;


/** Creates base for a presenter. */
kzsError kzuPresenterCreate_protected(const struct KzcMemoryManager* memoryManager, const struct KzuPresenterClass* presenterClass,
                                      struct KzuPresenterData* presenterData, struct KzuPresenter** out_presenter);

/** Finds the child of the layout object with the specified presenter index. */
kzsError kzuPresenterGetItem_protected(const struct KzuObjectNode* layoutObject, kzUint presenterIndex, struct KzuObjectNode** out_objectNode);

/** Base delete implementation. */
kzsError kzuPresenterDelete_protected(const struct KzuPresenter* presenter);

/** Base snap implementation. Sets snapping position to original target position and item index to -1. */
kzsError kzuPresenterSnap_protected(const struct KzuPresenter* presenter, const struct KzcVector2* position, struct KzcVector2* out_position, kzInt* out_itemIndex);

/** Base set scroll implementation. Does nothing. */
kzsError kzuPresenterSetScroll_protected(const struct KzuPresenter* presenter, const struct KzcVector2* scroll);

/** Base get scroll bounds implementation. Does not limit scrolling. */
kzsError kzuPresenterGetScrollBounds_protected(const struct KzuPresenter* presenter, kzFloat* out_scrollMinimumX, kzFloat* out_scrollMaximumX,
                                               kzFloat* out_scrollMinimumY, kzFloat* out_scrollMaximumY);

/** Base implementation for bringing an item to the center. Outputs zero offset. */
kzsError kzuPresenterBringItemCenter_protected(const struct KzuPresenter* presenter, kzUint itemIndex, struct KzcVector2* out_scrollValue);

/** Base update implementation. Does nothing. */
kzsError kzuPresenterUpdate_protected(const struct KzuPresenter* presenter);


/** Base implementation for item added callback. Does nothing. */
kzsError kzuPresenterItemAdded_protected(const struct KzuPresenter* presenter, kzUint index,
                                         const struct KzcVector3* newItemSize);
/** Base implementation for item removed callback. Does nothing. */
kzsError kzuPresenterItemRemoved_protected(const struct KzuPresenter* presenter, kzUint index,
                                           const struct KzcVector3* oldItemSize);
/** Base implementation for item replaced callback. Does nothing. */
kzsError kzuPresenterItemReplaced_protected(const struct KzuPresenter* presenter, kzUint index,
                                            const struct KzcVector3* oldItemSize, const struct KzcVector3* newItemSize);


KZ_HEADER_END


#endif
