/**
* \file
* User interface component.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_UI_COMPONENT_H
#define KZU_UI_COMPONENT_H


#include <user/scene_graph/kzu_object_common.h>

#include <system/debug/kzs_error.h>
#include <system/kzs_types.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations. */
struct KzcDynamicArray;
struct KzcInputStream;
struct KzcMemoryManager;
struct KzcVector3;
struct KzuBinaryFileInfo;
struct KzuFactory;
struct KzuMessageDispatcher;
struct KzuObjectNode;
struct KzuPropertyManager;
struct KzuPropertyType;
struct KzuScene;
struct KzuTransformedObjectNode;
struct KzuUiEventListener;
struct KzuUIDomain;


/**
* \struct KzuUiComponentNode
* Structure for graphical user interface component node, inherited from KzuObjectNode.
* A UI component node is a layout containing other UI components, empty nodes or mesh nodes.
* 
* The UI component performs laying out in two phases: the measure and arrange phase.
* In the measure phase, the UI component goes through its children and gets their desired size and based on them
* calculates the total desired size of the component.
* In the arrange phase, the UI component is given its actual size and it arranges (places) all its children by setting
* their layout transform and actual size.
*/
struct KzuUiComponentNode;


/** Object type identifier for component objects. */
extern const KzuObjectType KZU_OBJECT_TYPE_UI_COMPONENT;


/** Calls the measure function of the user interface component.
* \param componentNode The UI component to measure.
* \param out_coreDesiredSize The desired size of the component calculated in the measure function of the component.
* \return KZS_SUCCESS on success.
*/
kzsError kzuUiComponentNodeMeasure(struct KzuUiComponentNode* componentNode, struct KzcVector3* out_coreDesiredSize);
/** Calls the arrange function of the user interface component.
* The actual size of the component must be set before calling this function.
* \param componentNode The UI component to arrange.
* \return KZS_SUCCESS on success.
*/
kzsError kzuUiComponentNodeArrange(struct KzuUiComponentNode* componentNode);

/** Casts UI component node from object node. */
struct KzuUiComponentNode* kzuUiComponentNodeFromObjectNode(const struct KzuObjectNode* objectNode);
/** Casts UI component node to object node. */
struct KzuObjectNode* kzuUiComponentNodeToObjectNode(const struct KzuUiComponentNode* componentNode);


KZ_HEADER_END


#endif
