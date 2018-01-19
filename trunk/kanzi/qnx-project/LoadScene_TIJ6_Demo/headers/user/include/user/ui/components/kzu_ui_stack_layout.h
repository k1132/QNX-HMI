/**
* \file
* User interface stack layout component.
*
* KzuUiStackLayout lays out its children along a user-specified axis in order.
*
* Stack Layout Messages
* ----
* KzuUiStackLayout does not send or receive any messages.
*
* Stack Layout Properties
* ----
* ::KZU_PROPERTY_TYPE_STACK_LAYOUT_DIRECTION integer property specifies the stack layout axis. The stack layout size cannot be restricted along the layout axis
* (::KzuUiFlowLayout can be used for that). The value should be one of ::KzuStackLayoutDirection values. The default value is ::KZU_STACK_LAYOUT_DIRECTION_X.
*
* ::KZU_PROPERTY_TYPE_STACK_LAYOUT_REVERSED Boolean property can be set to reverse the layout direction along the layout axis. The default value is ::KZ_FALSE.
*
* \see \ref kzu_stack_layer.h for the 2D version of this component, \ref kzu_ui_flow_layout.h.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_UI_STACK_LAYOUT_H
#define KZU_UI_STACK_LAYOUT_H


#include <user/scene_graph/kzu_object_common.h>
#include <user/ui/kzu_layout.h>


KZ_HEADER_BEGIN


/* Forward declarations. */
struct KzcMemoryManager;
struct KzcHashMap;
struct KzuObjectNode;
struct KzuUiComponentNode;
struct KzuPropertyManager;
struct KzuMessageDispatcher;
struct KzuFactory;
struct KzuUIDomain;


/**
 * \struct KzuUiStackLayout
 * Stack layout user interface component. Aligns objects in a stack.
 */
struct KzuUiStackLayout;


/** Object type for stack layout. */
extern const KzuObjectType KZU_OBJECT_TYPE_UI_STACK_LAYOUT;


/** Creates a stack layout with default settings. */
kzsError kzuUiStackLayoutCreate(const struct KzcMemoryManager* memoryManager, kzString name, struct KzuUIDomain* uiDomain, struct KzuUiStackLayout** out_stackLayout);

/** Registers component type to factory. */
kzsError kzuUiStackLayoutRegisterToFactory(const struct KzuFactory* factory);

/** Casts to UiComponentNode. */
struct KzuUiComponentNode* kzuUiStackLayoutToUiComponentNode(const struct KzuUiStackLayout* stackLayout);

/** Casts to UiStackLayout. */
struct KzuUiStackLayout* kzuUiStackLayoutFromUiComponentNode(const struct KzuUiComponentNode* component);


/** Get the direction of the stack layout. */
enum KzuStackLayoutDirection kzuUiStackLayoutGetDirection(const struct KzuUiStackLayout* stackLayout);

/** Get the reversed property of the stack layout. */
kzBool kzuUiStackLayoutIsReversed(const struct KzuUiStackLayout* stackLayout);


KZ_HEADER_END


#endif
