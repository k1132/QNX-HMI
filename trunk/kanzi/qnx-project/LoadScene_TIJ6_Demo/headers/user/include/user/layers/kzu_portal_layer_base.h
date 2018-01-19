/**
* \file
* Private layer data.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_PORTAL_LAYER_BASE_H
#define KZU_PORTAL_LAYER_BASE_H


#include "kzu_layer_base.h"


KZ_HEADER_BEGIN


/** Portal layer class. */
struct KzuPortalLayer
{
    struct KzuLayer layer;                        /**< Inherited from layer. */

    struct KzuViewportLayer* parentViewport;      /**< Viewport layer we're looking into. */
    struct KzuScene* scene;                       /**< Scene acquired from an upper viewport layer. */ 
    struct KzuTransformedScene* transformedScene; /**< Transformed scene acquired from an upper viewport layer. */

    struct KzcRectangle subRectangle;             /**< Cached sub-rectangle compared to parent. */
    kzBool subRectangleCached;                    /**< Has sub-rectangle been calculated? */
    kzBool subRectangleEnabled;                   /**< Axis-aligned, can draw using sub-rectangle. */
};


/** Portal layer class. */
extern const struct KzuLayerClass KZU_PORTAL_LAYER_CLASS;


/** Portal layer initialize implementation. */
kzsError kzuPortalLayerInitialize_protected(struct KzuObjectNode* objectNode);

/** Portal layer measure implementation. */
kzsError kzuPortalLayerMeasure_protected(struct KzuLayer* layer, const struct KzcVector2* availableSize, struct KzcVector2* out_measuredSize);

/**
 * Refreshes the sub-rectangle matrix of the portal layer.
 * Returns true if rectangle is correct and portal can be drawn, false otherwise.
 */
kzBool kzuPortalLayerRefreshSubRectangle_protected(struct KzuPortalLayer* portalLayer);


KZ_HEADER_END


#endif
