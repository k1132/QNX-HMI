/**
* \file
* User interface component List Box Item.
*
* KzuUiListBoxItem is a container for a list box element. It stores an index to the ::KzuPresenter for the element.
* Normally the ::KzuItemGenerator of a ::KzuUiListBox creates KzuUiListBoxItems on request.
*
* \see \ref kzu_item_generator.h, \ref kzu_presenter.h.
*
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_UI_LIST_BOX_ITEM_H
#define KZU_UI_LIST_BOX_ITEM_H


#include <user/scene_graph/kzu_object_common.h>

#include <system/kzs_types.h>
#include <system/debug/kzs_error.h>
#include <system/wrappers/kzs_math.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations. */
struct KzcMemoryManager;
struct KzuUiComponentNode;
struct KzuFactory;
struct KzuUIDomain;


/**
 * \struct KzuUiListBoxItem
 * List Box Item for List Box. Wrapper component for storing item object nodes.
 */
struct KzuUiListBoxItem;


/** Object type for list box item. */
extern const KzuObjectType KZU_OBJECT_TYPE_UI_LIST_BOX_ITEM;

/** Unitialized value for list box item presenter index. */
#define KZU_UI_LIST_BOX_ITEM_NO_PRESENTER_INDEX KZ_UINT_MAXIMUM

/** Creates a raw list box item with default settings. */
kzsError kzuUiListBoxItemCreate(const struct KzcMemoryManager* memoryManager, kzString name, struct KzuUIDomain* uiDomain, struct KzuUiListBoxItem** out_listBoxItem);

/** Registers component type to factory. */
kzsError kzuUiListBoxItemRegisterToFactory(const struct KzuFactory* factory);


/** Casts to UiComponentNode. */
struct KzuUiComponentNode* kzuUiListBoxItemToUiComponentNode(const struct KzuUiListBoxItem* listBoxItem);

/** Casts to UiListBoxItem. */
struct KzuUiListBoxItem* kzuUiListBoxItemFromUiComponentNode(const struct KzuUiComponentNode* component);

/** Sets the index of the item for the presenter. */
void kzuUiListBoxItemSetPresenterIndex(struct KzuUiListBoxItem* listBoxItem, kzUint presenterIndex);

/** Returns the index set for the presenter. */
kzUint kzuUiListBoxItemGetPresenterIndex(const struct KzuUiListBoxItem* listBoxItem);


KZ_HEADER_END


#endif
