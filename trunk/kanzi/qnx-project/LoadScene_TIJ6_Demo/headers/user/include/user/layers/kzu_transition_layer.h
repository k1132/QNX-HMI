/**
* \file
* Transition Layer class. KzuTransitionLayer provides an animated transition between two layers.
* 
* Transition Layer Messages
* ----
* ::KZU_MESSAGE_TRANSITION_LAYER_TRANSITION_STARTED message is sent when the transition starts. It has two arguments 
* ::KZU_MESSAGE_ARGUMENT__TRANSITION_LAYER__TRANSITION_STARTED__SOURCE_LAYER and ::KZU_MESSAGE_ARGUMENT__TRANSITION_LAYER__TRANSITION_STARTED__TARGET_LAYER
* specifying the transition source and target layer.
*
* ::KZU_MESSAGE_TRANSITION_LAYER_TRANSITION_FINISHED message is sent when the transition ends. It has two arguments 
* ::KZU_MESSAGE_ARGUMENT__TRANSITION_LAYER__TRANSITION_FINISHED__SOURCE_LAYER and ::KZU_MESSAGE_ARGUMENT__TRANSITION_LAYER__TRANSITION_FINISHED__TARGET_LAYER
* specifying the transition source and target layer.
*
* KzuTransitionLayer receives the ::KZU_MESSAGE_TRANSITION_LAYER_START_TRANSITION message. The message can have two arguments
* ::KZU_MESSAGE_ARGUMENT__TRANSITION_LAYER__START_TRANSITION__MODE and ::KZU_MESSAGE_ARGUMENT__TRANSITION_LAYER__START_TRANSITION__TARGET_LAYER. The
* ::KZU_MESSAGE_ARGUMENT__TRANSITION_LAYER__START_TRANSITION__MODE argument's value should be one of ::KzuLayerTransitionMode values. The
* ::KZU_LAYER_TRANSITION_MODE_NEXT and ::KZU_LAYER_TRANSITION_MODE_PREVIOUS values specify the direction of the transition. If the value is
* ::KZU_LAYER_TRANSITION_MODE_CUSTOM, the ::KZU_MESSAGE_ARGUMENT__TRANSITION_LAYER__START_TRANSITION__TARGET_LAYER argument specifies the transition target layer.
*
* Transition Layer Properties
* ----
* ::KZU_PROPERTY_TYPE_TRANSITION_LAYER_TARGET pointer property specifies the transition target layer.
*
* ::KZU_PROPERTY_TYPE_TRANSITION_LAYER_SOURCE pointer property specifies the source layer from which the transition is performed to the target layer.
*
* ::KZU_PROPERTY_TYPE_TRANSITION_LAYER_PHASE float property specifies the current phase of the transition in range [0, 1] from source layer to target layer.
* Can be controlled either via program code or using animation.
*
* ::KZU_PROPERTY_TYPE_TRANSITION_LAYER_DURATION float property specifies how long the transition takes in seconds. Only meaningful if using the default linear
* animation that is created if the animation clip is not specified.
*
* ::KZU_PROPERTY_TYPE_TRANSITION_LAYER_ANIMATION resource ID property specifies the ::KzuAnimationItem to use as the transition.
*
* ::KZU_PROPERTY_TYPE_TRANSITION_LAYER_MATERIAL resource ID property specifies the ::KzuMaterial to use when rendering the transition layer.
*
* ::KZU_PROPERTY_TYPE_TRANSITION_LAYER_MATERIAL_FIRST_TEXTURE string property specifies the property name of a (shader) property that specifies the 
* first texture of the transition material.
*
* ::KZU_PROPERTY_TYPE_TRANSITION_LAYER_MATERIAL_SECOND_TEXTURE string property specifies the property name of a (shader) property that specifies the
* second texture of the transition material.
*
* ::KZU_PROPERTY_TYPE_TRANSITION_LAYER_MATERIAL_FIRST_CONTENT_TEXCOORD string property specifies the property name of a (shader) property that specifies the 
* first content texture coordinates of the transition layer material.
*
* ::KZU_PROPERTY_TYPE_TRANSITION_LAYER_MATERIAL_SECOND_CONTENT_TEXCOORD string property specifies the property name of a (shader) property that specifies the 
* second content texture coordinates of the transition layer material.
*
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_TRANSITION_LAYER_H
#define KZU_TRANSITION_LAYER_H


#include <user/scene_graph/kzu_object_base.h>


KZ_HEADER_BEGIN


/* Forward declaration. */
struct KzcMemoryManager;
struct KzuFactory;
struct KzuLayer;
struct KzuMessageDispatcher;
struct KzuUIDomain;
struct KzuPropertyManager;
struct KzuRenderer;
struct KzuMaterial;
struct KzuTransitionLayer;


/** Transitioning mode. */
enum KzuLayerTransitionMode
{
    KZU_LAYER_TRANSITION_MODE_NEXT,     /**< Next child. */
    KZU_LAYER_TRANSITION_MODE_PREVIOUS, /**< Previous child. */
    KZU_LAYER_TRANSITION_MODE_CUSTOM    /**< Child to transition explicitly specified. */
};


/** Object type for transition layers. */
extern const KzuObjectType KZU_OBJECT_TYPE_TRANSITION_LAYER;


/** Convert layer to transition layer. */
struct KzuTransitionLayer* kzuTransitionLayerFromLayer(const struct KzuLayer* layer);
/** Convert transition layer to layer. */
struct KzuLayer* kzuTransitionLayerToLayer(const struct KzuTransitionLayer* transitionLayer);

/** Create a transition layer. */
kzsError kzuTransitionLayerCreate(const struct KzcMemoryManager* memoryManager, kzString name, struct KzuUIDomain* uiDomain,
                                  struct KzuTransitionLayer** out_transitionLayer);
/** Register transition layer to the factory. */
kzsError kzuTransitionLayerRegisterToFactory(const struct KzuFactory* factory);

/** Sets transition material for transition layer. */
kzsError kzuTransitionLayerSetTransitionMaterial(struct KzuTransitionLayer* transitionLayer, struct KzuMaterial* material);


KZ_HEADER_END


#endif
