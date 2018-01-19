/**
* \file
* 2D flow (layout) layer.
* 
* KzuFlowLayer lays out its children in the primary direction as long as there is space, and then moves to a new row
* in the secondary direction. Not unlike word wrapping in a word processor.
*
* \see \ref kzu_ui_flow_layout.h for a 3D version of this layer.
*
* Flow Layer Messages
* ----
* KzuFlowLayer does not send any messages.
* 
* Flow Layer Properties
* ----
* ::KZU_PROPERTY_TYPE_FLOW_LAYOUT_PRIMARY_DIRECTION property specifies the primary layouting direction. Its value type is
* the enum ::KzuFlowLayoutDirection. Values ::KZU_FLOW_LAYOUT_DIRECTION_NEAR_TO_FAR and ::KZU_FLOW_LAYOUT_DIRECTION_FAR_TO_NEAR
* are not supported. The default value is ::KZU_FLOW_LAYOUT_DIRECTION_LEFT_TO_RIGHT.
*
* ::KZU_PROPERTY_TYPE_FLOW_LAYOUT_SECONDARY_DIRECTION property specifies the secondary layouting direction. Its value type is
* the enum ::KzuFlowLayoutDirection. Values ::KZU_FLOW_LAYOUT_DIRECTION_NEAR_TO_FAR and ::KZU_FLOW_LAYOUT_DIRECTION_FAR_TO_NEAR
* are not supported. The default value is ::KZU_FLOW_LAYOUT_DIRECTION_TOP_TO_BOTTOM.
*
* ::KZU_PROPERTY_TYPE_LAYOUT_WIDTH property specifies the extent of the left-to-right and right-to-left (X-axis) direction.
*
* ::KZU_PROPERTY_TYPE_LAYOUT_HEIGHT property specifies the extent of the top-to-bottom and bottom-to-top (Y-axis) direction.
*
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_FLOW_LAYER_H
#define KZU_FLOW_LAYER_H


#include <user/scene_graph/kzu_object_common.h>
#include <user/ui/components/kzu_ui_flow_layout.h>


KZ_HEADER_BEGIN


/* Forward declarations. */
struct KzcMemoryManager;
struct KzuFactory;
struct KzuLayer;
struct KzuUIDomain;
struct KzuFlowLayer;


/** Object type for the flow layer. */
extern const KzuObjectType KZU_OBJECT_TYPE_FLOW_LAYER;


/** Creates a flow layer.
* \param memoryManager The memory manager to use for memory allocations.
* \param name Name of the flow layer.
* \param uiDomain The UI domain to use.
* \param out_flowLayer Pointer that is set to point to the new flow layer.
* \return KZS_SUCCESS on success.
*/
kzsError kzuFlowLayerCreate(const struct KzcMemoryManager* memoryManager, kzString name,
                            struct KzuUIDomain* uiDomain, struct KzuFlowLayer** out_flowLayer);
/** Registers flow layer to the factory. */
kzsError kzuFlowLayerRegisterToFactory(const struct KzuFactory* factory);

/** Converts KzuLayer to KzuFlowLayer. */
struct KzuFlowLayer* kzuFlowLayerFromLayer(const struct KzuLayer* layer);
/** Converts KzuFlowLayer to KzuLayer. */
struct KzuLayer* kzuFlowLayerToLayer(const struct KzuFlowLayer* flowLayer);

/** Get the primary direction of the flow layout from the ::KZU_PROPERTY_TYPE_FLOW_LAYOUT_PRIMARY_DIRECTION property. */
enum KzuFlowLayoutDirection kzuFlowLayerGetPrimaryDirection(const struct KzuFlowLayer* flowLayer);
/** Get the secondary direction of the flow layout from the ::KZU_PROPERTY_TYPE_FLOW_LAYOUT_SECONDARY_DIRECTION property. */
enum KzuFlowLayoutDirection kzuFlowLayerGetSecondaryDirection(const struct KzuFlowLayer* flowLayer);


KZ_HEADER_END


#endif
