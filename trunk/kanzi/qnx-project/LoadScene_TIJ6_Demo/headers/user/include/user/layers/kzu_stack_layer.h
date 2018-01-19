/**
* \file
* 2D user interface stack layout component.
* 
* KzuStackLayer lays out its children along a user-specified axis in order.
*
* Stack Layer Messages
* ----
* KzuStackLayer does not send or receive any messages.
*
* Stack Layer Properties
* ----
* ::KZU_PROPERTY_TYPE_STACK_LAYOUT_DIRECTION integer property specifies the stack layer axis. The stack layer size cannot be restricted along the layout axis
* (::KzuFlowLayer can be used for that). The value should either ::KZU_STACK_LAYOUT_DIRECTION_X or ::KZU_STACK_LAYOUT_DIRECTION_Y.
* The default value is ::KZU_STACK_LAYOUT_DIRECTION_X.
*
* ::KZU_PROPERTY_TYPE_STACK_LAYOUT_REVERSED Boolean property can be set to reverse the layout direction along the layout axis. The default value is ::KZ_FALSE.
*
* \see \ref kzu_ui_stack_layout.h for the 3D version of this layout, \ref kzu_flow_layer.h.
*
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_STACK_LAYER_H
#define KZU_STACK_LAYER_H


#include <user/scene_graph/kzu_object_common.h>
#include <user/ui/kzu_layout.h>


KZ_HEADER_BEGIN


/* Forward declarations. */
struct KzcMemoryManager;
struct KzuFactory;
struct KzuLayer;
struct KzuUIDomain;
struct KzuStackLayer;


/** Object type for stack layout. */
extern const KzuObjectType KZU_OBJECT_TYPE_STACK_LAYER;


/** Creates an stack layer. */
kzsError kzuStackLayerCreate(const struct KzcMemoryManager* memoryManager, kzString name, struct KzuUIDomain* uiDomain, struct KzuStackLayer** out_stackLayer);
/** Registers stack layer to the factory. */
kzsError kzuStackLayerRegisterToFactory(const struct KzuFactory* factory);

/** Converts layer to stack layer. */
struct KzuStackLayer* kzuStackLayerFromLayer(const struct KzuLayer* layer);
/** Converts stack layer to layer. */
struct KzuLayer* kzuStackLayerToLayer(const struct KzuStackLayer* stackLayer);

/** Get the direction of the stack layout. */
enum KzuStackLayoutDirection kzuStackLayerGetDirection(const struct KzuStackLayer* stackLayer);
/** Get the reversed property of the stack layout. */
kzBool kzuStackLayerIsReversed(const struct KzuStackLayer* stackLayer);


KZ_HEADER_END


#endif
