/**
* \file
* Defines base class for items that handle scrolling of layouts.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_PRESENTER_H
#define KZU_PRESENTER_H


#include <core/util/math/kzc_vector2.h>

#include <system/kzs_types.h>
#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations. */
struct KzcMemoryManager;
struct KzuPresenter;
struct KzuObjectNode;


/** Presenter configuration. */
struct KzuPresenterConfiguration
{
    kzBool supportsFocus; /**< Does presenter support focus. */
};


/** Presenter class. */
struct KzuPresenterClass
{
    struct KzuPresenterConfiguration configuration; /**< Presenter configuration. */

    /** Deletes presenter. */
    kzsError (*kzuPresenterDelete)(struct KzuPresenter* presenter);

    /**
    * Snaps presenter to an item in the given direction from given position.
    * Returns snapped item index and scroll position.
    * If snapping happened towards no object, index will be -1.
    * No value will be written to those output variables that are KZ_NULL.
    * The changeTarget should be KZ_TRUE, if the list box target should be changed to the snapped item.
    */
    kzsError (*kzuPresenterSnap)(const struct KzuPresenter* presenter, const struct KzcVector2* position, const struct KzcVector2* direction,
                                 kzBool changeTarget, struct KzcVector2* out_position, kzInt* out_itemIndex);

    /** Sets new scroll value for the presenter. */
    kzsError (*kzuPresenterSetScroll)(const struct KzuPresenter* presenter, const struct KzcVector2* scroll);

    /** Returns allowed scrolling area of presenter. */
    kzsError (*kzuPresenterGetScrollBounds)(const struct KzuPresenter* presenter, kzFloat* out_scrollMinimumX, kzFloat* out_scrollMaximumX,
                                            kzFloat* out_scrollMinimumY, kzFloat* out_scrollMaximumY);

    /** Outputs a scroll value such that the given item is in the center. */
    kzsError (*kzuPresenterBringItemCenter)(const struct KzuPresenter* presenter, kzUint itemIndex, struct KzcVector2* out_scrollValue);

    /** Adds the specified list box item to the layout. */
    kzsError (*kzuPresenterAddToLayout)(const struct KzuPresenter* presenter, struct KzuObjectNode* listBoxItem);
    /** Removes the specified list box item from the layout. */
    kzsError (*kzuPresenterRemoveFromLayout)(const struct KzuPresenter* presenter, struct KzuObjectNode* listBoxItem);
    /** Removes all list box items from the layout. */
    kzsError (*kzuPresenterClearLayout)(const struct KzuPresenter* presenter);

    /** Updates layout's object nodes. */
    kzsError (*kzuPresenterUpdate)(const struct KzuPresenter* presenter);

    /** Informs the presenter that an item was added to the virtual item list at the given index. */
    kzsError (*kzuPresenterItemAdded)(const struct KzuPresenter* presenter, kzUint index);

    /** Informs the presenter that an item was removed from the virtual item list from the given index. */
    kzsError (*kzuPresenterItemRemoved)(const struct KzuPresenter* presenter, kzUint index);

    /** Informs the presenter that an item in the virtual item list at the given index was replaced. */
    kzsError (*kzuPresenterItemReplaced)(const struct KzuPresenter* presenter, kzUint index);
};


/** Presenter data. */
struct KzuPresenterData
{
    const struct KzuPresenterClass* presenterClass; /**< Class of the presenter data. */
};


/**
* Controls presentation of scrolling for layout ui components.
* Also takes care of snapping for layout ui components.
*/
struct KzuPresenter
{
    struct KzuPresenterData* data; /**< Data of the presenter. */
};


/** Deletes a presenter. */
kzsError kzuPresenterDelete(struct KzuPresenter* presenter);

/** Returns whether the presenter supports focus. */
kzBool kzuPresenterSupportsFocus(const struct KzuPresenter* presenter);


/** Sets scroll value. */
kzsError kzuPresenterSetScroll(const struct KzuPresenter* presenter, const struct KzcVector2* scroll);

/**
* Snaps towards given direction from given position.
* Returns snapping target and index of the object that scrolling snapped to, unless they're given as KZ_NULL.
* The changeTarget should be KZ_TRUE if the list box target is changed to the snapped item.
*
* If snapping happened towards no object, index will be -1.
*/
kzsError kzuPresenterSnap(const struct KzuPresenter* presenter, const struct KzcVector2* position, const struct KzcVector2* direction, kzBool changeTarget, struct KzcVector2* out_position, kzInt* out_itemIndex);

/** Gets scroll bounds for the layout. */
kzsError kzuPresenterGetScrollBounds(const struct KzuPresenter* presenter, kzFloat* out_scrollMinimumX, kzFloat* out_scrollMaximumX,
                                     kzFloat* out_scrollMinimumY, kzFloat* out_scrollMaximumY);


/** Outputs a scroll value such that the given item moves to the center. */
kzsError kzuPresenterBringItemCenter(const struct KzuPresenter* presenter, kzUint itemIndex, struct KzcVector2* out_scrollValue);


/** Adds the specified list box item to the layout. */
kzsError kzuPresenterAddToLayout(const struct KzuPresenter* presenter, struct KzuObjectNode* listBoxItem);

/** Removes the specified list box item from the layout. */
kzsError kzuPresenterRemoveFromLayout(const struct KzuPresenter* presenter, struct KzuObjectNode* listBoxItem);

/** Removes all list box items from the layout. */
kzsError kzuPresenterClearLayout(const struct KzuPresenter* presenter);

/** Updates presenter's state and visible items. */
kzsError kzuPresenterUpdate(const struct KzuPresenter* presenter);

/** Informs the presenter that an item was added to the virtual item list at the given index. */
kzsError kzuPresenterItemAdded(const struct KzuPresenter* presenter, kzUint index);

/** Informs the presenter that an item was removed from the virtual item list from the given index. */
kzsError kzuPresenterItemRemoved(const struct KzuPresenter* presenter, kzUint index);

/** Informs the presenter that an item in the virtual item list at the given index was replaced. */
kzsError kzuPresenterItemReplaced(const struct KzuPresenter* presenter, kzUint index);


KZ_HEADER_END


#endif
