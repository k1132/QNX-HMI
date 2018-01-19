/**
 * \file
 * Property accessors for KzuObjectNode.
 * 
 * Copyright 2008-2014 by Rightware. All rights reserved.
 */
#ifndef KZU_OBJECT_PROPERTIES_H
#define KZU_OBJECT_PROPERTIES_H


#include "kzu_object.h"

#include <core/util/math/kzc_matrix4x4.h>
#include <core/util/math/kzc_vector2.h>

#include <system/kzs_types.h>
#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations */
struct KzuObjectNode;


/** Gets the value of property RenderTransformation in objectNode. */
struct KzcMatrix4x4 kzuObjectNodeGetRenderTransformation(const struct KzuObjectNode* objectNode);
/** Sets the value of property RenderTransformation in objectNode. */
kzsError kzuObjectNodeSetRenderTransformation(const struct KzuObjectNode* objectNode, const struct KzcMatrix4x4* value);

/** Gets the value of property LayoutWidth in objectNode if the property is set. */
kzBool kzuObjectNodeGetLayoutWidth(const struct KzuObjectNode* objectNode, kzFloat* out_value);
/** Sets the value of property LayoutWidth in objectNode. */
kzsError kzuObjectNodeSetLayoutWidth(const struct KzuObjectNode* objectNode, kzFloat value);

/** Gets the value of property LayoutHeight in objectNode if the property is set. */
kzBool kzuObjectNodeGetLayoutHeight(const struct KzuObjectNode* objectNode, kzFloat* out_value);
/** Sets the value of property LayoutHeight in objectNode. */
kzsError kzuObjectNodeSetLayoutHeight(const struct KzuObjectNode* objectNode, kzFloat value);

/** Gets the value of property LayoutDepth in objectNode if the property is set. */
kzBool kzuObjectNodeGetLayoutDepth(const struct KzuObjectNode* objectNode, kzFloat* out_value);
/** Sets the value of property LayoutDepth in objectNode. */
kzsError kzuObjectNodeSetLayoutDepth(const struct KzuObjectNode* objectNode, kzFloat value);

/** Gets the value of property LayoutHorizontalAlignment in objectNode. */
enum KzuObjectNodeHorizontalAlignment kzuObjectNodeGetLayoutHorizontalAlignment(const struct KzuObjectNode* objectNode);
/** Sets the value of property LayoutHorizontalAlignment in objectNode. */
kzsError kzuObjectNodeSetLayoutHorizontalAlignment(const struct KzuObjectNode* objectNode, enum KzuObjectNodeHorizontalAlignment value);

/** Gets the value of property LayoutVerticalAlignment in objectNode. */
enum KzuObjectNodeVerticalAlignment kzuObjectNodeGetLayoutVerticalAlignment(const struct KzuObjectNode* objectNode);
/** Sets the value of property LayoutVerticalAlignment in objectNode. */
kzsError kzuObjectNodeSetLayoutVerticalAlignment(const struct KzuObjectNode* objectNode, enum KzuObjectNodeVerticalAlignment value);

/** Gets the value of property LayoutDepthAlignment in objectNode. */
enum KzuObjectNodeDepthAlignment kzuObjectNodeGetLayoutDepthAlignment(const struct KzuObjectNode* objectNode);
/** Sets the value of property LayoutDepthAlignment in objectNode. */
kzsError kzuObjectNodeSetLayoutDepthAlignment(const struct KzuObjectNode* objectNode, enum KzuObjectNodeDepthAlignment value);

/** Gets the value of property LayoutHorizontalMargin in objectNode. */
struct KzcVector2 kzuObjectNodeGetLayoutHorizontalMargin(const struct KzuObjectNode* objectNode);
/** Sets the value of property LayoutHorizontalMargin in objectNode. */
kzsError kzuObjectNodeSetLayoutHorizontalMargin(const struct KzuObjectNode* objectNode, struct KzcVector2 value);

/** Gets the value of property LayoutVerticalMargin in objectNode. */
struct KzcVector2 kzuObjectNodeGetLayoutVerticalMargin(const struct KzuObjectNode* objectNode);
/** Sets the value of property LayoutVerticalMargin in objectNode. */
kzsError kzuObjectNodeSetLayoutVerticalMargin(const struct KzuObjectNode* objectNode, struct KzcVector2 value);

/** Gets the value of property LayoutDepthMargin in objectNode. */
struct KzcVector2 kzuObjectNodeGetLayoutDepthMargin(const struct KzuObjectNode* objectNode);
/** Sets the value of property LayoutDepthMargin in objectNode. */
kzsError kzuObjectNodeSetLayoutDepthMargin(const struct KzuObjectNode* objectNode, struct KzcVector2 value);

/** Gets the value of property HitTestable in objectNode. */
kzBool kzuObjectNodeIsHitTestable(const struct KzuObjectNode* objectNode);
/** Sets the value of property HitTestable in objectNode. */
kzsError kzuObjectNodeSetHitTestable(const struct KzuObjectNode* objectNode, kzBool value);

/** Gets the value of property HitTestableContainer in objectNode. */
kzBool kzuObjectNodeIsHitTestableContainer(const struct KzuObjectNode* objectNode);
/** Sets the value of property HitTestableContainer in objectNode. */
kzsError kzuObjectNodeSetHitTestableContainer(const struct KzuObjectNode* objectNode, kzBool value);

/** Gets the value of property Visible in objectNode. */
kzBool kzuObjectNodeIsVisible(const struct KzuObjectNode* objectNode);
/** Sets the value of property Visible in objectNode. */
kzsError kzuObjectNodeSetVisible(const struct KzuObjectNode* objectNode, kzBool value);

/** Gets the value of property FrustumCullMargin in objectNode. */
kzFloat kzuObjectNodeGetFrustumCullMargin(const struct KzuObjectNode* objectNode);
/** Sets the value of property FrustumCullMargin in objectNode. */
kzsError kzuObjectNodeSetFrustumCullMargin(const struct KzuObjectNode* objectNode, kzFloat value);

/** Gets the value of property Enabled in objectNode. */
kzBool kzuObjectNodeIsEnabled(const struct KzuObjectNode* objectNode);
/** Sets the value of property Enabled in objectNode. */
kzsError kzuObjectNodeSetEnabled(const struct KzuObjectNode* objectNode, kzBool value);

/** Gets the value of property Focusable in objectNode. */
kzBool kzuObjectNodeIsFocusable(const struct KzuObjectNode* objectNode);
/** Sets the value of property Focusable in objectNode. */
kzsError kzuObjectNodeSetFocusable(const struct KzuObjectNode* objectNode, kzBool value);

/** Gets the value of property Focused in objectNode. */
kzBool kzuObjectNodeIsFocused(const struct KzuObjectNode* objectNode);
/** Sets the value of property Focused in objectNode. */
kzsError kzuObjectNodeSetFocused(const struct KzuObjectNode* objectNode, kzBool value);

/** Gets the value of property PartialRenderingForceRender in objectNode. */
kzBool kzuObjectNodeIsPartialRenderingForceRender(const struct KzuObjectNode* objectNode);
/** Sets the value of property PartialRenderingForceRender in objectNode. */
kzsError kzuObjectNodeSetPartialRenderingForceRender(const struct KzuObjectNode* objectNode, kzBool value);

/** Gets the value of property PartialRenderingStencilObject in objectNode. */
void* kzuObjectNodeGetPartialRenderingStencilObject(const struct KzuObjectNode* objectNode);
/** Sets the value of property PartialRenderingStencilObject in objectNode. */
kzsError kzuObjectNodeSetPartialRenderingStencilObject(const struct KzuObjectNode* objectNode, void* value);


KZ_HEADER_END


#endif
