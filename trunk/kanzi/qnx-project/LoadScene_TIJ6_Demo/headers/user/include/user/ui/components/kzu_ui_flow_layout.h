/**
* \file
* UI flow (wrapping) layout component.
*
* KzuUiFlowLayout lays out its children in the primary direction as long as there is space, and then moves to a new row
* in the secondary direction. Not unlike word wrapping in a word processor.
*
* \see \ref kzu_flow_layer.h for a 2D version of this component.
*
* Flow Layout Messages
* ----
* KzuUiFlowLayout does not send any messages.
* 
* Flow Layout Properties
* ----
* ::KZU_PROPERTY_TYPE_FLOW_LAYOUT_PRIMARY_DIRECTION property specifies the primary layouting direction. Its value type is
* the enum ::KzuFlowLayoutDirection. The default value is ::KZU_FLOW_LAYOUT_DIRECTION_LEFT_TO_RIGHT.
*
* ::KZU_PROPERTY_TYPE_FLOW_LAYOUT_SECONDARY_DIRECTION property specifies the secondary layouting direction. Its value type is
* the enum ::KzuFlowLayoutDirection. The default value is ::KZU_FLOW_LAYOUT_DIRECTION_TOP_TO_BOTTOM.
*
* ::KZU_PROPERTY_TYPE_LAYOUT_WIDTH property specifies the extent of the left-to-right and right-to-left (X-axis) direction.
*
* ::KZU_PROPERTY_TYPE_LAYOUT_HEIGHT property specifies the extent of the top-to-bottom and bottom-to-top (Y-axis) direction.
*
* ::KZU_PROPERTY_TYPE_LAYOUT_DEPTH property specifies the extent of the near-to-far and far-to-near (Z-axis) direction.
*
* Copyright 2013-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_UI_FLOW_LAYOUT_H
#define KZU_UI_FLOW_LAYOUT_H


#include <user/scene_graph/kzu_object_common.h>

#include <system/debug/kzs_error.h>
#include <system/kzs_types.h>


KZ_HEADER_BEGIN


/** Direction (or axis) of the layout, used in both primary and secondary direction. */
enum KzuFlowLayoutDirection {
    /* X axis */
    KZU_FLOW_LAYOUT_DIRECTION_LEFT_TO_RIGHT, /**< Left to right direction. */
    KZU_FLOW_LAYOUT_DIRECTION_RIGHT_TO_LEFT, /**< Left to right direction. */
    /* Y axis */
    KZU_FLOW_LAYOUT_DIRECTION_TOP_TO_BOTTOM, /**< Top to bottom direction. */
    KZU_FLOW_LAYOUT_DIRECTION_BOTTOM_TO_TOP, /**< Bottom to top direction. */
    /* Z axis */
    KZU_FLOW_LAYOUT_DIRECTION_NEAR_TO_FAR, /**< Near to far direction. */
    KZU_FLOW_LAYOUT_DIRECTION_FAR_TO_NEAR /**< Far to near direction. */
};


/* Forward declarations. */
struct KzcMemoryManager;
struct KzuObjectNode;
struct KzuUiComponentNode;
struct KzuFactory;
struct KzuUIDomain;


/**
 * \struct KzuUiFlowLayout
 * Flow layout component. Stacks objects in x, y, or z axis direction as long as there is
 * space available, after that moves to the next "line" (think of text wrapping).
 */
struct KzuUiFlowLayout;


/** Object type for flow layout. */
extern const KzuObjectType KZU_OBJECT_TYPE_UI_FLOW_LAYOUT;


/** Creates a flow layout with default settings.
* \param memoryManager The memory manager to use for memory allocations.
* \param name Name of the flow layout.
* \param uiDomain The UI domain to use.
* \param out_flowLayout Pointer that is set to point to the new flow layout.
* \return KZS_SUCCESS on success.
*/
kzsError kzuUiFlowLayoutCreate(const struct KzcMemoryManager* memoryManager, kzString name, struct KzuUIDomain* uiDomain, struct KzuUiFlowLayout** out_flowLayout);

/** Registers component type to factory. */
kzsError kzuUiFlowLayoutRegisterToFactory(const struct KzuFactory* factory);

/** Casts from KzuUiFlowLayout to KzuUiComponentNode. */
struct KzuUiComponentNode* kzuUiFlowLayoutToUiComponentNode(const struct KzuUiFlowLayout* flowLayout);

/** Casts from KzuUiComponentNode to KzuUiFlowLayout. */
struct KzuUiFlowLayout* kzuUiFlowLayoutFromUiComponentNode(const struct KzuUiComponentNode* component);

/**
 * Get the primary direction of the flow layout from the ::KZU_PROPERTY_TYPE_FLOW_LAYOUT_PRIMARY_DIRECTION property.
 * When there is no more space in the primary direction, additional items flow to the secondary direction.
 */
enum KzuFlowLayoutDirection kzuUiFlowLayoutGetPrimaryDirection(const struct KzuUiFlowLayout* flowLayout);

/**
 * Get the secondary direction of the flow layout from the ::KZU_PROPERTY_TYPE_FLOW_LAYOUT_SECONDARY_DIRECTION property.
 * When there is no more space in the primary direction, additional items flow to the secondary direction.
 */
enum KzuFlowLayoutDirection kzuUiFlowLayoutGetSecondaryDirection(const struct KzuUiFlowLayout* flowLayout);


KZ_HEADER_END


#endif
