/**
 * \file
 * Property accessors for KzuLayer.
 * 
 * Copyright 2008-2014 by Rightware. All rights reserved.
 */
#ifndef KZU_LAYER_PROPERTIES_H
#define KZU_LAYER_PROPERTIES_H


#include "kzu_layer.h"

#include <core/util/color/kzc_color.h>
#include <core/util/math/kzc_matrix3x3.h>
#include <core/util/math/kzc_vector2.h>

#include <system/kzs_types.h>
#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations */
struct KzuLayer;


/** Gets the value of property LayerAspectRatio in layer. */
kzFloat kzuLayerGetLayerAspectRatio(const struct KzuLayer* layer);
/** Sets the value of property LayerAspectRatio in layer. */
kzsError kzuLayerSetLayerAspectRatio(const struct KzuLayer* layer, kzFloat value);

/** Gets the value of property LayerContentStretch in layer. */
enum KzuLayerContentStretch kzuLayerGetLayerContentStretch(const struct KzuLayer* layer);
/** Sets the value of property LayerContentStretch in layer. */
kzsError kzuLayerSetLayerContentStretch(const struct KzuLayer* layer, enum KzuLayerContentStretch value);

/** Gets the value of property LayerLayoutTransformation in layer. */
struct KzcMatrix3x3 kzuLayerGetLayerLayoutTransformation(const struct KzuLayer* layer);
/** Sets the value of property LayerLayoutTransformation in layer. */
kzsError kzuLayerSetLayerLayoutTransformation(const struct KzuLayer* layer, const struct KzcMatrix3x3* value);

/** Gets the value of property LayerRenderTransformationOrigin in layer. */
struct KzcVector2 kzuLayerGetLayerRenderTransformationOrigin(const struct KzuLayer* layer);
/** Sets the value of property LayerRenderTransformationOrigin in layer. */
kzsError kzuLayerSetLayerRenderTransformationOrigin(const struct KzuLayer* layer, struct KzcVector2 value);

/** Gets the value of property LayerRenderTransformation in layer. */
struct KzcMatrix3x3 kzuLayerGetLayerRenderTransformation(const struct KzuLayer* layer);
/** Sets the value of property LayerRenderTransformation in layer. */
kzsError kzuLayerSetLayerRenderTransformation(const struct KzuLayer* layer, const struct KzcMatrix3x3* value);

/** Gets the value of property LayerBackgroundBrushColor in layer. */
struct KzcColorRGBA kzuLayerGetLayerBackgroundBrushColor(const struct KzuLayer* layer);
/** Sets the value of property LayerBackgroundBrushColor in layer. */
kzsError kzuLayerSetLayerBackgroundBrushColor(const struct KzuLayer* layer, struct KzcColorRGBA value);

/** Gets the value of property LayerOpacity in layer. */
kzFloat kzuLayerGetLayerOpacity(const struct KzuLayer* layer);
/** Sets the value of property LayerOpacity in layer. */
kzsError kzuLayerSetLayerOpacity(const struct KzuLayer* layer, kzFloat value);


KZ_HEADER_END


#endif
