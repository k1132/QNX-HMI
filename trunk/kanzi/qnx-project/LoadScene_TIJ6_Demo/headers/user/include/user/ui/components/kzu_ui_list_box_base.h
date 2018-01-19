/**
 * \file
 * Base functions for List box component.
 *
 * Copyright 2008-2014 by Rightware. All rights reserved.
 */
#ifndef KZU_UI_LIST_BOX_BASE_H
#define KZU_UI_LIST_BOX_BASE_H


#include <user/ui/kzu_ui_component_base.h>

#include <system/kzs_types.h>
#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations. */
struct KzcMemoryManager;
struct KzuObjectNode;
struct KzuPropertyType;
struct KzuUiComponentNode;
struct KzuUiComponentNodeClass;


/** List box. */
struct KzuUiListBox
{
    struct KzuUiComponentNode componentNode; /**< Inherited from KzuUiComponentNode. */
    struct KzuPresenter* presenter; /**< Controls presentation of objects. */
    struct KzuUiScrollView* scrollView; /**< Controls scrolling of list box. */

    kzInt selectedItem; /**< Current selection. */

    kzBool ownsPresenter; /**< Should list box delete presenter at uninitialize. */

    struct KzcHashMap* itemInfosByIndices; /**< Item infos by item indices. <kzUint, KzuUiListBoxItemInfo*>. */
    struct KzcHashMap* itemInfosByItems;   /**< Item infos by item pointers. <KzuUiListBoxItem*, KzuUiListBoxItemInfo*>. */
    struct KzcHashMap* itemInfosByObjects; /**< Item infos by objects. <kzuObjectNode*, KzuUiListBoxItemInfo*>. */
    struct KzcHashMap* itemInfosByObjectsBuffer; /**< Double buffer for itemInfosByObjects. <KzuObjectNode*, KzuUiListBoxItemInfo*>. */
    kzUint beginIndex; /**< Index of the first item. */
    kzUint itemCount; /**< Number of items. */

    struct KzuObjectGenerator* objectGenerator; /**< Generates and handles objects for list box. */
    kzMutableString objectGeneratorTypeName; /**< Name of the used ObjectGenerator. */
    struct KzuItemGenerator* itemGenerator; /**< Generates and handlers list box items for list box. */
    kzMutableString itemContainerGeneratorTypeName; /**< Name of the used ítem generator. */

    kzUint totalItemCount; /**< How many elements the list box has in total. */
    kzBool forceUpdate; /**< Forces re-update even with previous range when items have been added, removed, or replaced. */
};


/** Filter function that returns KZ_TRUE if a child object of the list box should be interpreted as a list box item. */
typedef kzBool (*KzuUiListBoxItemFilterFunction)(struct KzuObjectNode* objectNode, void* userData);

/** Resets members of list box to their state at construction. */
void kzuUiListBoxReset_protected(struct KzuUiListBox* listBox);

/** Adds children of a list box as items of the list box if the object generator supports the list interface. */
kzsError kzuUiListBoxAddChildrenAsItems_protected(struct KzuUiListBox* listBox, KzuUiListBoxItemFilterFunction filterFunction,
                                                  void* userData);

/** Moves list box items of a list box back as its children. */
kzsError kzuUiListBoxUndoAddChildrenAsItems_protected(const struct KzuUiListBox* listBox);

/** Binds a given source property in the list box to the given target property in the given list box child object. */
kzsError kzuUiListBoxBindChildProperty_protected(struct KzuObjectNode* childObject, kzString relativePathToListBox,
                                                 const struct KzuPropertyType* sourceProperty, const struct KzuPropertyType* targetProperty);

/**
* Sets the items in the given range to be visible items and hides all others.
* If beginIndex + itemCount is at least the total number of items, the range is interpreted to be looping past the end.
*
* It is an error to try to display the same item twice.
*
* Send messages about items entering or leaving the range.
*/
kzsError kzuUiListBoxUpdateVisibleRange_protected(struct KzuUiListBox* listBox, kzUint beginIndex, kzUint itemCount);

/** Same as kzuUiListBoxUpdateVisibleRange_protected but does not send messages. */
kzsError kzuUiListBoxUpdateVisibleRangeQuiet_protected(struct KzuUiListBox* listBox, kzUint beginIndex, kzUint itemCount);

/** Updates list box's total item count. */
kzsError kzuUiListBoxUpdateTotalItemCount_protected(struct KzuUiListBox* listBox);


/** Initializes a list box. */
KZ_CALLBACK kzsError kzuUiListBoxInitialize_protected(struct KzuObjectNode* objectNode);

/** Uninitializes a list box. */
KZ_CALLBACK kzsError kzuUiListBoxUninitialize_protected(struct KzuObjectNode* objectNode);

/** List box on attached implementation. */
KZ_CALLBACK kzsError kzuUiListBoxOnAttached_protected(struct KzuObjectNode* objectNode);

/** List box on detached implementation. */
KZ_CALLBACK kzsError kzuUiListBoxOnDetached_protected(struct KzuObjectNode* objectNode);

/** Measures a list box. */
KZ_CALLBACK kzsError kzuUiListBoxMeasure_protected(struct KzuUiComponentNode* componentNode, struct KzcVector3* out_coreDesiredSize);

/** Arranges a list box. */
KZ_CALLBACK kzsError kzuUiListBoxArrange_protected(struct KzuUiComponentNode* componentNode);

/** Creates a list box with the given component node class. */
kzsError kzuUiListBoxFactoryCreateCustom_protected(const struct KzcMemoryManager* memoryManager, kzString name,
                                                   struct KzuUIDomain* uiDomain, const struct KzuUiComponentNodeClass* componentNodeClass,
                                                   struct KzuUiListBox** out_listBox);


KZ_HEADER_END


#endif
