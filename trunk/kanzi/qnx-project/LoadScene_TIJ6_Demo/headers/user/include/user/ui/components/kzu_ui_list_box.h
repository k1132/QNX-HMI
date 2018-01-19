/**
* \file
* List box user interface component. ::KzuUiListBox provides a list model (with some control features) for layouts. Normally KzuUiListBox is a child of KzuUiScrollView
* and interacts with it via messages.
*
* The list box is supplied with a ::KzuObjectGenerator to provide elements for the list box
* (see the Virtual_list_box example project for an example of a custom object generator),
* and with a ::KzuItemGenerator to provide items that will hold the actual elements.
*
* Whenever the elements of a ::KzuObjectGenerator change, ::kzuUiListBoxItemReplaced, ::kzuUiListBoxItemAdded
* or ::kzuUiListBoxItemRemoved needs to be called.
*
* List Box Messages
* ----
* ::KZU_MESSAGE_LIST_BOX_TARGET_CHANGED message is sent when the ::KZU_PROPERTY_TYPE_LIST_BOX_SELECTION_BEHAVIOR property
* has value ::KZU_UI_LIST_BOX_SELECTION_BEHAVIOR_BRING_CENTER and the user clicks on an item, and when the list box
* receives message ::KZU_MESSAGE_SCROLL_VIEW_SNAP_REQUEST and the presenter supports focus. The ::KZU_MESSAGE_LIST_BOX_TARGET_CHANGED message
* has one integer argument ::KZU_MESSAGE_ARGUMENT__LIST_BOX__ITEM_INDEX that has the index of the selected item.
*
* ::KZU_MESSAGE_LIST_BOX_ITEM_VISIBLE message is sent for each visible item when ::kzuUiListBoxUpdateVisibleRange_protected is called
* with a non-empty range (normally the presenter takes care of this). The message has one pointer argument ::KZU_MESSAGE_ARGUMENT__LIST_BOX__ITEM
* which is a pointer to the visible list element.
*
* ::KZU_MESSAGE_LIST_BOX_ITEM_HIDDEN message is sent for each hidden item when ::kzuUiListBoxUpdateVisibleRange_protected is called
* (normally the presenter takes care of this). The message has one pointer argument ::KZU_MESSAGE_ARGUMENT__LIST_BOX__ITEM
* which is a pointer to the hidden list element.
*
* ::KZU_MESSAGE_LIST_BOX_ITEM_SELECTED message is sent when a list box item is clicked (i.e. the list box receives a ::KZU_MESSAGE_CLICK message
* normally sent by the scroll view parent). The message has two integer arguments:
* ::KZU_MESSAGE_ARGUMENT__LIST_BOX__SELECTION is the index of the new selected item and ::KZU_MESSAGE_ARGUMENT__LIST_BOX__PREVIOUS_SELECTION is the
* index of the previous selected item.
*
* ::KZU_MESSAGE_SCROLL_VIEW_SET_SCROLL_TARGET message is sent (for the scroll view parent) when the ::KZU_PROPERTY_TYPE_LIST_BOX_SELECTION_BEHAVIOR property
* has value ::KZU_UI_LIST_BOX_SELECTION_BEHAVIOR_BRING_CENTER and the user clicks on an item, and when the list box
* receives message ::KZU_MESSAGE_SCROLL_VIEW_SNAP_REQUEST. The message has one ::KzcVector2 argument which is the new scroll target.
*
* ::KZU_MESSAGE_SCROLL_VIEW_SET_SCROLL message is sent when ::kzuUiListBoxBringItemCenter is called with smooth == ::KZ_FALSE argument. The
* message has one ::KzcVector2 argument ::KZU_MESSAGE_ARGUMENT__SCROLL_VIEW__SCROLL_POSITION that is the new scroll position.
*
* List Box Properties
* ----
* ::KZU_PROPERTY_TYPE_LIST_BOX_OBJECT_GENERATOR_TYPE_NAME string property can be set to use a custom object generator, instead of ::KzuObjectGeneratorDefault.
* The value should be a name of the object generator as previously registered to ::KzuFactory.
*
* ::KZU_PROPERTY_TYPE_LIST_BOX_ITEM_CONTAINER_GENERATOR_TYPE_NAME string property can be set to use a custom item container generator, instead of ::KzuItemGeneratorDefault.
* The value should be a name of the item container generator as previously registered to ::KzuFactory.
*
* ::KZU_PROPERTY_TYPE_LIST_BOX_SELECTION_BEHAVIOR integer property can be set to ::KZU_UI_LIST_BOX_SELECTION_BEHAVIOR_BRING_CENTER or
* ::KZU_UI_LIST_BOX_SELECTION_BEHAVIOR_DO_NOTHING. If the value is ::KZU_UI_LIST_BOX_SELECTION_BEHAVIOR_BRING_CENTER, the list box will automatically center the clicked item
* (provided that it has a ::KzuUiScrollView parent). The default value is ::KZU_UI_LIST_BOX_SELECTION_BEHAVIOR_DO_NOTHING.
*
* \see \ref kzu_ui_scroll_view.h, \ref kzu_object_generator.h.
*
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_UI_LIST_BOX_H
#define KZU_UI_LIST_BOX_H


#include <user/ui/kzu_ui_component_base.h>
#include <user/ui/components/listbox/kzu_object_generator_common.h>
#include <user/ui/components/listbox/kzu_item_container_generator_common.h>

#include <system/kzs_types.h>
#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/** List box selection index represents no selection. */
#define KZU_UI_LIST_BOX_NO_ITEM (-1)


/* Forward declarations. */
struct KzcMemoryManager;
struct KzcHashMap;
struct KzcVector3;
struct KzuUiComponentNode;
struct KzuUiScrollView;
struct KzuFactory;
struct KzuObjectNode;
struct KzuPresenter;
struct KzuTrajectory;
struct KzuUiComponentNodeClass;
struct KzuObjectGenerator;
struct KzuItemGenerator;
struct KzuUIDomain;

/**
* \struct KzuUiListBox
* List box user interface component. Provides list box functionality for layouts.
*
* The list box is supplied with a kzuObjectGenerator to provide elements for the list box,
* and with a kzuItemGenerator to provide items that will hold the actual elements.
*
* Whenever the elements of a kzuObjectGenerator change, ::kzuUiListBoxItemReplaced, ::kzuUiListBoxItemAdded
* or ::kzuUiListBoxItemRemoved needs to be called.
*/
struct KzuUiListBox;


/** Object type for list box. */
extern const KzuObjectType KZU_OBJECT_TYPE_UI_LIST_BOX;


/** List box node's UI component node class. */
extern const struct KzuUiComponentNodeClass KZU_UI_LIST_BOX_CLASS;


/** Sets list box behavior on object selection. */
enum KzuUiListBoxSelectionBehavior
{
    KZU_UI_LIST_BOX_SELECTION_BEHAVIOR_DO_NOTHING,    /**< Does not change scroll position when selection changes. */
    KZU_UI_LIST_BOX_SELECTION_BEHAVIOR_BRING_CENTER   /**< Centers object when selected. */
};


/** Creates a raw list box with default settings. */
kzsError kzuUiListBoxCreate(const struct KzcMemoryManager* memoryManager, kzString name, struct KzuUIDomain* uiDomain, struct KzuUiListBox** out_listBox);

/** Registers component type to factory. */
kzsError kzuUiListBoxRegisterToFactory(const struct KzuFactory* factory);


/** Casts to UiComponentNode. */
struct KzuUiComponentNode* kzuUiListBoxToUiComponentNode(const struct KzuUiListBox* listBox);

/** Casts to UiListBox. */
struct KzuUiListBox* kzuUiListBoxFromUiComponentNode(const struct KzuUiComponentNode* component);


/** Sets list box's object generator. */
kzsError kzuUiListBoxSetObjectGeneratorType(struct KzuUiListBox* uiListBox, KzuObjectGeneratorType objectGeneratorType);

/** Sets list box's item generator. */
kzsError kzuUiListBoxSetItemContainerGeneratorType(struct KzuUiListBox* uiListBox, KzuItemContainerGeneratorType itemContainerGeneratorType);


/** Returns list box's object generator that can be used for adding or removing items from the list box. */
struct KzuObjectGenerator* kzuUiListBoxGetObjectGenerator(const struct KzuUiListBox* listBox);

/** Returns list box's item generator. */
struct KzuItemGenerator* kzuUiListBoxGetItemContainerGenerator(const struct KzuUiListBox* listBox);


/** Returns the total item count of the list box. Includes all virtual items. */
kzUint kzuUiListBoxGetItemCount(const struct KzuUiListBox* listBox);

/** Returns ::KZ_TRUE if the list box has no items. */
kzBool kzuUiListBoxIsEmpty(const struct KzuUiListBox* listBox);

/** Returns size of the item at the given index. */
kzsError kzuUiListBoxGetObjectSize(const struct KzuUiListBox* listBox, kzUint index, struct KzcVector3* out_size);

/** Returns index of the given item. If the object does not exist currently, returns ::KZU_UI_LIST_BOX_NO_ITEM. */
kzsError kzuUiListBoxGetIndex(const struct KzuUiListBox* listBox, const struct KzuObjectNode* item, kzInt* out_itemIndex);

/**
* Gets the object at the given index in a list box using the default object generator.
* For other object generators \see KzuObjectGenerator.
*/
kzsError kzuUiListBoxGetObject(const struct KzuUiListBox* listBox, kzUint index, struct KzuObjectNode** out_objectNode);
/**
* Inserts an object at the given index in a list box using the default object generator.
* For other object generators \see KzuObjectGenerator.
*/
kzsError kzuUiListBoxInsertObject(const struct KzuUiListBox* listBox, kzUint index, struct KzuObjectNode* objectNode);
/**
* Removes an object at the given index from a list box using the default object generator.
* For other object generators \see KzuObjectGenerator.
*/
kzsError kzuUiListBoxRemoveObject(const struct KzuUiListBox* listBox, kzUint index);
/**
* Replaces the object at the given index from a list box using the default object generator.
* For other object generators \see KzuObjectGenerator.
*/
kzsError kzuUiListBoxReplaceObject(const struct KzuUiListBox* listBox, kzUint index, struct KzuObjectNode* newObjectNode);
/**
* Adds an object at the end of a list box using the default object generator.
* For other object generators \see KzuObjectGenerator.
*/
kzsError kzuUiListBoxAddObject(const struct KzuUiListBox* listBox, struct KzuObjectNode* objectNode);
/**
* Removes the last object from a list box using the default object generator.
* For other object generators \see KzuObjectGenerator.
*/
kzsError kzuUiListBoxRemoveLastObject(const struct KzuUiListBox* listBox);


/**
* Centers list box to the given item. Sets focus.
* \itemIndex itemIndex Index of item to be centered. Must be at most itemCount - 1.
* \param smooth If KZ_TRUE, the transition will be smooth. If KZ_FALSE, the transition will be immediate.
*/
kzsError kzuUiListBoxBringItemCenter(const struct KzuUiListBox* listBox, kzUint itemIndex, kzBool smooth);


/**
* Returns the currently focused item, i.e. the item that is closest to the selector offset. If no items are focused, returns KZ_NULL.
* To query index of the item, \see kzuUiListBoxGetIndex.
*/
kzsError kzuUiListBoxGetFocus(const struct KzuUiListBox* listBox, struct KzuObjectNode** out_item);


/** Gets current selection of the list box. */
kzsError kzuUiListBoxGetSelection(const struct KzuUiListBox* listBox, kzInt* out_selection);

/** Sets current selection of the list box. Acts according to current selection behavior. */
kzsError kzuUiListBoxSetSelection(struct KzuUiListBox* listBox, kzInt selection);


/** Gets list box's behavior on object selection. */
enum KzuUiListBoxSelectionBehavior kzuUiListBoxGetSelectionBehavior(const struct KzuUiListBox* listBox);

/** Sets list box's behavior on object selection. */
kzsError kzuUiListBoxSetSelectionBehavior(const struct KzuUiListBox* listBox, enum KzuUiListBoxSelectionBehavior selectionBehavior);


/** Gets layout presenter of the list box. */
struct KzuPresenter* kzuUiListBoxGetPresenter(const struct KzuUiListBox* listbox);

/** Sets layout presenter for the list box. */
kzsError kzuUiListBoxSetPresenter(struct KzuUiListBox* listbox, struct KzuPresenter* presenter, kzBool transferOwnership);


/** Gets the scroll view node that controls scrolling of the list box. */
struct KzuUiScrollView* kzuUiListBoxGetScrollView(const struct KzuUiListBox* listBox);

/** Sets the scroll view node that controls scrolling of the list box. */
kzsError kzuUiListBoxSetScrollView(struct KzuUiListBox* listbox, struct KzuUiScrollView* scrollView);


/** Informs the list box that an item was added at the given index. */
kzsError kzuUiListBoxItemAdded(struct KzuUiListBox* listBox, kzUint index);

/** Informs the list box that an item was removed from the given index. */
kzsError kzuUiListBoxItemRemoved(struct KzuUiListBox* listBox, kzUint index);

/** Informs the list box that an item at the given index was replaced. The list box doesn't use the old item after this, so it can be immediately released. */
kzsError kzuUiListBoxItemReplaced(struct KzuUiListBox* listBox, kzUint index);


/** Default implementation for object generator interface. Notify list box about a replaced item. */
KZ_CALLBACK kzsError kzuUiListBoxObjectGeneratorItemReplaced_protected(struct KzuObjectNode* listBox, kzUint index);

/** Default implementation for object generator interface. Notify list box about a removed item. */
KZ_CALLBACK kzsError kzuUiListBoxObjectGeneratorItemRemoved_protected(struct KzuObjectNode* listBox, kzUint index);

/** Default implementation for object generator interface. Notify list box about an added item. */
KZ_CALLBACK kzsError kzuUiListBoxObjectGeneratorItemAdded_protected(struct KzuObjectNode* listBox, kzUint index);


KZ_HEADER_END


#endif
