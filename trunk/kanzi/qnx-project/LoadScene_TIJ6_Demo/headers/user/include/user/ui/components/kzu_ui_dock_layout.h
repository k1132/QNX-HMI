/**
* \file
* Dock layout component.
*
* KzuUiDockLayout lays out its children left, right, top or bottom side of the layout area according to the child's ::KZU_PROPERTY_TYPE_DOCK_LAYOUT_DOCKING_SIDE property
* in the order the children were added. The children do not overlap each other, however, they will be assigned zero sizes after the space runs out.
*
* Dock Layout Messages
* ----
* KzuUiDockLayout does not send or receive any messages.
*
* Dock Layout Properties
* ----
* ::KZU_PROPERTY_TYPE_DOCK_LAYOUT_LAST_CHILD_FILL Boolean property specifies whether the last child should be given all the remaining space
* (::KZ_TRUE) or just the desired size (::KZ_FALSE). The default value is ::KZ_FALSE.
*
* ::KZU_PROPERTY_TYPE_DOCK_LAYOUT_DOCKING_SIDE integer property can be set in a child of KzuUiDockLayout to specify which side of the remaining layout area the child
* should be placed. The value should be one of the ::KzuDockLayoutDockingSide values. The default value is ::KZU_DOCK_LAYOUT_DOCK_LEFT.
*
* ::KZU_PROPERTY_TYPE_LAYOUT_WIDTH float property specifies the size of the layout area in X-axis direction.
*
* ::KZU_PROPERTY_TYPE_LAYOUT_HEIGHT float property specifies the size of the layout area in Y-axis direction.
*
* ::KZU_PROPERTY_TYPE_LAYOUT_DEPTH float property specifies the size of the layout area in Z-axis direction.
*
* \see \ref kzu_dock_layer.h for the 2D version of this component. 
*
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_UI_DOCK_LAYOUT_H
#define KZU_UI_DOCK_LAYOUT_H


#include <user/scene_graph/kzu_object_common.h>
#include <user/layers/kzu_dock_layer.h>

#include <system/kzs_types.h>
#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations. */
struct KzcMemoryManager;
struct KzuObjectNode;
struct KzuUiComponentNode;
struct KzuFactory;
struct KzuUIDomain;


/**
 * \struct KzuUiDockLayout
 * Dock layout component. Children are placed on left, right, top or bottom based on their
 * ::KZU_PROPERTY_TYPE_DOCK_LAYOUT_DOCKING_SIDE property.
 */
struct KzuUiDockLayout;


/** Object type for dock layout. */
extern const KzuObjectType KZU_OBJECT_TYPE_UI_DOCK_LAYOUT;


/** Creates a dock layout with default settings. */
kzsError kzuUiDockLayoutCreate(const struct KzcMemoryManager* memoryManager, kzString name,
                               struct KzuUIDomain* uiDomain, struct KzuUiDockLayout** out_dockLayout);

/** Registers component type to factory. */
kzsError kzuUiDockLayoutRegisterToFactory(const struct KzuFactory* factory);

/** Casts to UiComponentNode. */
struct KzuUiComponentNode* kzuUiDockLayoutToUiComponentNode(const struct KzuUiDockLayout* dockLayout);

/** Casts to UiDockLayout. */
struct KzuUiDockLayout* kzuUiDockLayoutFromUiComponentNode(const struct KzuUiComponentNode* component);

/** Returns the last child fill flag. If true, the last child of the dock is given all the remaining free space. */
kzBool kzuUiDockLayoutGetLastChildFill(const struct KzuUiDockLayout* dockLayout);

/** Returns the docking side property value of a child of the dock. */
enum KzuDockLayoutDockingSide kzuUiDockLayoutGetDockingSide(const struct KzuObjectNode* child);


KZ_HEADER_END


#endif
