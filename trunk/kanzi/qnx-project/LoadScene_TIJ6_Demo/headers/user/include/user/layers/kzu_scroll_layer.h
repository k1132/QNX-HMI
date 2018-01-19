/**
 * \file
 * Scroll layer class. KzuScrollLayer is a 2D version of KzuUiScrollView. It actually wraps a KzuUiScrollView inside it.
 *
 * Scroll Layer Messages
 * ----
 * KzuScrollLayer does not send or receive any messages.
 *
 * Scroll Layer Properties
 * ----
 * ::KZU_PROPERTY_TYPE_SCROLL_LAYER_SCROLL_AXIS ::KzcVector2 property can be used to change the internal ::KzuUiScrollView's
 * ::KZU_PROPERTY_TYPE_SCROLL_VIEW_SCROLL_AXIS property.
 *
 * ::KZU_PROPERTY_TYPE_SCROLL_LAYER_SENSITIVITY float property can be used to change the internal ::KzuUiScrollView's
 * ::KZU_PROPERTY_TYPE_SCROLL_VIEW_SENSITIVITY property.
 *
 * ::KZU_PROPERTY_TYPE_SCROLL_LAYER_SLIDING_ACCELERATION_COEFFICIENT float property can be used to change the internal ::KzuUiScrollView's  
 * ::KZU_PROPERTY_TYPE_SCROLL_VIEW_SLIDING_ACCELERATION_COEFFICIENT property.
 *
 * ::KZU_PROPERTY_TYPE_SCROLL_LAYER_SLIDING_DRAG_COEFFICIENT float property can be used to change the internal ::KzuUiScrollView's
 * ::KZU_PROPERTY_TYPE_SCROLL_VIEW_SLIDING_DRAG_COEFFICIENT property.
 *
 * ::KZU_PROPERTY_TYPE_SCROLL_LAYER_DRAGGING_ACCELERATION_COEFFICIENT float property can be used to change the internal ::KzuUiScrollView's
 * ::KZU_PROPERTY_TYPE_SCROLL_VIEW_DRAGGING_ACCELERATION_COEFFICIENT property.
 *
 * ::KZU_PROPERTY_TYPE_SCROLL_LAYER_DRAGGING_DRAG_COEFFICIENT float property can be used to change the internal ::KzuUiScrollView's
 * ::KZU_PROPERTY_TYPE_SCROLL_VIEW_DRAGGING_DRAG_COEFFICIENT property.
 *
 * ::KZU_PROPERTY_TYPE_SCROLL_LAYER_DRAGGING_IMPULSE_FACTOR float property can be used to change the internal ::KzuUiScrollView's
 * ::KZU_PROPERTY_TYPE_SCROLL_VIEW_DRAGGING_IMPULSE_FACTOR property.
 *
 * ::KZU_PROPERTY_TYPE_SCROLL_LAYER_SWIPE_DISTANCE float property can be used to change the internal ::KzuUiScrollView's
 * ::KZU_PROPERTY_TYPE_SCROLL_VIEW_SWIPE_DISTANCE property.
 *
 * ::KZU_PROPERTY_TYPE_SCROLL_LAYER_SCROLLING Boolean property can be used to read the internal ::KzuUiScrollView's
 * ::KZU_PROPERTY_TYPE_SCROLL_VIEW_SCROLLING property.
 *
 * ::KZU_PROPERTY_TYPE_SCROLL_LAYER_SCROLL_POSITION ::KzcVector2 property can be used to read the internal ::KzuUiScrollView's
 * ::KZU_PROPERTY_TYPE_SCROLL_VIEW_SCROLL_POSITION property.
 *
 * ::KZU_PROPERTY_TYPE_SCROLL_LAYER_SCROLL_TARGET_POSITION ::KzcVector2 property can be used to read the internal ::KzuUiScrollView's
 * ::KZU_PROPERTY_TYPE_SCROLL_VIEW_SCROLL_TARGET_POSITION property.
 *
 * ::KZU_PROPERTY_TYPE_SCROLL_LAYER_SCROLL_SPEED ::KzcVector2 property can be used to read the internal ::KzuUiScrollView's
 * ::KZU_PROPERTY_TYPE_SCROLL_VIEW_SCROLL_SPEED property.
 *
 * Example Code
 * ----
 * The following example code shows how the KzuScrollLayer can be used to animate a ::KzuEmptyLayer in X axis direction.
 * The code uses an expression validator (see \ref kzu_expression_validator.h) to modify the
 * ::KZU_PROPERTY_TYPE_SCROLL_LAYER_SCROLL_POSITION value before it is
 * written to the target property ::KZU_PROPERTY_TYPE_LAYER_LAYOUT_TRANSFORMATION of the empty layer. Here,
 * ::kzuScrollLayerScrollToPosition() is used to scroll a distance in the beginning. After the initial scrolling, the
 * user can scroll the empty layer by dragging with the mouse (or finger) on top of the scroll layer.
 *
 * \code{.c}
    kzsError scrollLayerExample()
    {
        kzsError result;
        struct KzuObjectNode* scrollLayerNode;
        struct KzuScrollLayer* scrollLayer;
        struct KzuViewportLayer* rootLayer;
        struct KzuEmptyLayer* emptyLayer;
        struct KzuObjectNode* emptyLayerNode;
        struct KzuBindingRule* bindingRule;
        struct KzuBindingValidator* expressionValidator;
        struct KzuScreen* screen = kzaApplicationGetScreen(application);

        result = kzuScrollLayerCreate(memoryManager, "Scroll Layer", uiDomain, &scrollLayer);
        kzsErrorForward(result);
        scrollLayerNode = kzuLayerToObjectNode(kzuScrollLayerToLayer(scrollLayer));

        result = kzuViewportLayerCreate(memoryManager, "root layer", uiDomain, &rootLayer);
        kzsErrorForward(result);
        result = kzuObjectNodeAddChild(kzuScreenToObjectNode(screen),
                                       kzuLayerToObjectNode(kzuViewportLayerToLayer(rootLayer)));
        kzsErrorForward(result);
        result = kzuObjectNodeAddChild(kzuLayerToObjectNode(kzuViewportLayerToLayer(rootLayer)), scrollLayerNode);
        kzsErrorForward(result);

        result = kzuEmptyLayerCreate(memoryManager, "empty layer", uiDomain, &emptyLayer);
        kzsErrorForward(result);

        emptyLayerNode = kzuLayerToObjectNode(kzuEmptyLayerToLayer(emptyLayer));
        result = kzuObjectNodeAddChild(kzuLayerToObjectNode(kzuViewportLayerToLayer(rootLayer)), emptyLayerNode);
        kzsErrorForward(result);

        result = kzuBindingRuleCreateForProperty(memoryManager, uiDomain, "../Scroll Layer",
                                                 KZU_PROPERTY_TYPE_SCROLL_LAYER_SCROLL_POSITION,
                                                 KZU_PROPERTY_FIELD_VECTOR_X,
                                                 KZU_PROPERTY_TYPE_LAYER_LAYOUT_TRANSFORMATION,
                                                 KZU_PROPERTY_FIELD_TRANSLATION_X, &bindingRule);

        // Use an expression validator to multiply the scroll position value by a constant.
        result = kzuExpressionValidatorCreate(memoryManager, propertyManager, &expressionValidator);
        kzsErrorForward(result);

        result = kzuPropertyManagerSetInt(propertyManager, expressionValidator,
                                          KZU_PROPERTY_TYPE_EXPRESSION_VALIDATOR__OPERATION,
                                          KZU_EXPRESSION_VALIDATOR_OPERATION_MULTIPLY);
        kzsErrorForward(result);
        result = kzuPropertyManagerSetInt(propertyManager, expressionValidator,
                                          KZU_PROPERTY_TYPE_EXPRESSION_VALIDATOR__ARGUMENT_1,
                                          KZU_EXPRESSION_VALIDATOR_ARGUMENT_TYPE_TEMPORARY_REGISTER_0);
        kzsErrorForward(result);
        result = kzuPropertyManagerSetInt(propertyManager, expressionValidator,
                                          KZU_PROPERTY_TYPE_EXPRESSION_VALIDATOR__ARGUMENT_2,
                                          KZU_EXPRESSION_VALIDATOR_ARGUMENT_TYPE_CONSTANT_REGISTER_0);
        kzsErrorForward(result);

        // Write the multiplier to the constant register.
        {
            struct KzuVariant* multiplier;
            result = kzuVariantCreate(memoryManager, &multiplier);
            kzsErrorForward(result);
            result = kzuVariantSetFloat(multiplier, 2.5f);
            kzsErrorForward(result);
            result = kzuBindingRuleAddConstantRegister(bindingRule, multiplier);
            kzsErrorForward(result);
            result = kzuVariantDelete(multiplier);
            kzsErrorForward(result);
        }

        result = kzuBindingRuleAddValidator(bindingRule, expressionValidator);
        kzsErrorForward(result);

        result = kzuObjectNodeAddBinding(emptyLayerNode, bindingRule);
        kzsErrorForward(result);

        {
            struct KzcVector2 scrollPosition;
            struct KzcVector2 scrollTarget;

            result = kzuScrollLayerGetScroll(scrollLayer, &scrollPosition);
            kzsErrorForward(result);

            // Scroll 100 pixels forward (times the multiplier).
            scrollTarget.data[0] = scrollPosition.data[0] + 100.0f;
            scrollTarget.data[1] = scrollPosition.data[1];

            result = kzuScrollLayerScrollToPosition(scrollLayer, &scrollTarget);
            kzsErrorForward(result);
        }

        // Go to the main loop etc.

        kzsSuccess();
    }
 * \endcode
 *
 * \see \ref kzu_ui_scroll_view.h for the 3D version of this layer.
 *
 * Copyright 2008-2014 by Rightware. All rights reserved.
 */
#ifndef KZU_SCROLL_LAYER_H
#define KZU_SCROLL_LAYER_H


#include <user/scene_graph/kzu_object_common.h>

#include <system/debug/kzs_error.h>
#include <system/kzs_types.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations. */
struct KzcMemoryManager;
struct KzuFactory;
struct KzuLayer;
struct KzuUIDomain;
struct KzcVector2;

/**
 * \struct KzuScrollLayer
 * Scroll Layer is the 2D version of the Scroll View component.
 */
struct KzuScrollLayer;

/** Object type for scroll layers. */
extern const KzuObjectType KZU_OBJECT_TYPE_SCROLL_LAYER;


/** Creates a scroll layer. */
kzsError kzuScrollLayerCreate(const struct KzcMemoryManager* memoryManager, kzString name, struct KzuUIDomain* uiDomain,
                              struct KzuScrollLayer** out_scrollLayer);
/** Registers scroll layer to the factory. */
kzsError kzuScrollLayerRegisterToFactory(const struct KzuFactory* factory);

/** Converts a layer into a scroll layer. */
struct KzuScrollLayer* kzuScrollLayerFromLayer(const struct KzuLayer* layer);
/** Converts a scroll layer into a layer. */
struct KzuLayer* kzuScrollLayerToLayer(const struct KzuScrollLayer* scrollLayer);


/** Enable or disable X axis handling. */
kzsError kzuScrollLayerSetAxisEnabledX(const struct KzuScrollLayer* scrollLayer, kzBool state);
/** Enable or disable Y axis handling. */
kzsError kzuScrollLayerSetAxisEnabledY(const struct KzuScrollLayer* scrollLayer, kzBool state);

/** Set scroll value to loop between bounds, in X axis. */
void kzuScrollLayerSetLoopingX(const struct KzuScrollLayer* scrollLayer, kzBool state);
/** Set scroll value to loop between bounds, in Y axis. */
void kzuScrollLayerSetLoopingY(const struct KzuScrollLayer* scrollLayer, kzBool state);

/** Sets bounds for X axis for scroll. The scroll value can be dragged past them temporarily if not looped. */
void kzuScrollLayerSetScrollBoundsX(const struct KzuScrollLayer* scrollLayer, kzFloat minimum, kzFloat maximum);
/** Sets bounds for Y axis for scroll. The scroll value can be dragged past them temporarily if not looped. */
void kzuScrollLayerSetScrollBoundsY(const struct KzuScrollLayer* scrollLayer, kzFloat minimum, kzFloat maximum);

/**
* Sets new scroll target value for the scroll layer and jumps to it immediately.
*/
kzsError kzuScrollLayerJumpToPosition(const struct KzuScrollLayer* scrollLayer, const struct KzcVector2* scrollPosition);
/**
* Sets new scroll target for the scroll layer and start scrolling towards the target.
*
* If a scroll layer's axis is looping in an interval, its corresponding coordinate may be out of the interval to indicate
* e.g. scrolling direction.
*/
kzsError kzuScrollLayerScrollToPosition(const struct KzuScrollLayer* scrollLayer, const struct KzcVector2* scrollTarget);
/**
* Sets new scroll target for the scroll layer and start scrolling towards the target.
*
* If a scroll layer's axis is looping in an interval, the shortest path to the target value is chosen.
*/
kzsError kzuScrollLayerScrollToPositionLooping(const struct KzuScrollLayer* scrollLayer, const struct KzcVector2* scrollTarget);

/**
* Gets the current scroll value of the scroll layer.
*
* If a scroll layer's axis is looping in an interval, its corresponding coordinate is normalized to be inside the interval.
*/
kzsError kzuScrollLayerGetScroll(const struct KzuScrollLayer* scrollLayer, struct KzcVector2* out_scrollPosition);
/**
* Gets the current scroll target of the scroll layer.
*
* If a scroll layer's axis is looping in an interval, its corresponding coordinate may be out of the interval to indicate
* e.g. scrolling direction.
*/
kzsError kzuScrollLayerGetScrollTarget(const struct KzuScrollLayer* scrollLayer, struct KzcVector2* out_scrollTarget);
/**
* Gets the current scroll target of the scroll layer.
*
* If a scroll layer's axis is looping in an interval, its corresponding coordinate is normalized to be inside the interval.
*/
kzsError kzuScrollLayerGetScrollTargetLooping(const struct KzuScrollLayer* scrollLayer, struct KzcVector2* out_scrollTarget);


/** Updates scrolling configuration. */
kzsError kzuScrollLayerRefreshScrollConfiguration(const struct KzuScrollLayer* scrollLayer);
/** Updates recognition threshold. */
kzsError kzuScrollLayerRefreshThreshold(const struct KzuScrollLayer* scrollLayer);


KZ_HEADER_END


#endif
