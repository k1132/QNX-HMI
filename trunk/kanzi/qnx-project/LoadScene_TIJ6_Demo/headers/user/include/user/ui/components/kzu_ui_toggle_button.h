/**
* \file
* User interface toggle button component.
*
* KzuUiToggleButton is a 3D button layout that has ::KZU_PROPERTY_TYPE_BUTTON_TOGGLE_STATE_COUNT set to 2 by default. The documentation
* in \ref kzu_ui_button.h is valid for this component also.
*
* \see \ref kzu_toggle_button_layer.h for the 2D version of this component, \ref kzu_ui_button.h for documentation concerning all Kanzi buttons.
*
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_UI_TOGGLE_BUTTON_H
#define KZU_UI_TOGGLE_BUTTON_H


#include <user/scene_graph/kzu_object_common.h>
#include <user/scene_graph/kzu_object.h>

#include <system/kzs_types.h>
#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations. */
struct KzcMemoryManager;
struct KzcHashMap;
struct KzuUiComponentNode;
struct KzuPropertyManager;
struct KzuMessageDispatcher;
struct KzuFactory;
struct KzuUIDomain;


/**
 * \struct KzuUiToggleButton
 * Toggle button user interface component.
 *
 * \see \ref kzu_ui_button.h for documentation concerning all Kanzi buttons.
 */
struct KzuUiToggleButton;


/** Object type for toggle button. */
extern const KzuObjectType KZU_OBJECT_TYPE_UI_TOGGLE_BUTTON;


/** Creates a toggle button with default settings. */
kzsError kzuUiToggleButtonCreate(const struct KzcMemoryManager* memoryManager, kzString name, struct KzuUIDomain* uiDomain, struct KzuUiToggleButton** out_toggleButton);

/** Registers component type to factory. */
kzsError kzuUiToggleButtonRegisterToFactory(const struct KzuFactory* factory);

/** Casts to UiComponentNode. */
struct KzuUiComponentNode* kzuUiToggleButtonToUiComponentNode(const struct KzuUiToggleButton* toggleButton);

/** Casts to UiToggleButton. */
struct KzuUiToggleButton* kzuUiToggleButtonFromUiComponentNode(const struct KzuUiComponentNode* component);

/** Sets toggle button state. */
kzsError kzuUiToggleButtonSetState(const struct KzuUiToggleButton* toggleButton, kzBool enabled);

/** Gets toggle button state. */
kzBool kzuUiToggleButtonGetState(const struct KzuUiToggleButton* toggleButton);


KZ_HEADER_END


#endif
