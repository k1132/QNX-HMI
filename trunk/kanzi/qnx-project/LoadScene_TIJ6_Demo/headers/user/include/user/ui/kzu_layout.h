/**
 * \file
 * Basic layouting definitions. Common for both 3D and 2D layouts.
 * 
 * Copyright 2008-2014 by Rightware. All rights reserved.
 */
#ifndef KZU_UI_LAYOUT_H
#define KZU_UI_LAYOUT_H


#include <system/kzs_types.h>
#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declaration. */
struct KzcDynamicArray;
struct KzcMemoryManager;
struct KzuObjectNode;
struct KzuPropertyType;
struct KzuBoundingVolume;


/** Grid layout size mode for rows and columns. */
enum KzuUiGridLayoutSizeMode
{
    KZU_UI_GRID_LAYOUT_SIZE_USER    = 0,        /**< User specified size. */
    KZU_UI_GRID_LAYOUT_SIZE_AUTO    = 1,        /**< Size based on content. */
    KZU_UI_GRID_LAYOUT_SIZE_WEIGHED = 2         /**< Size based on content with a weight factor applied. */
};

/** Stack layout direction enumeration. */
enum KzuStackLayoutDirection
{
    KZU_STACK_LAYOUT_DIRECTION_X = 0, /**< Layout direction X. */
    KZU_STACK_LAYOUT_DIRECTION_Y = 1, /**< Layout direction Y. */
    KZU_STACK_LAYOUT_DIRECTION_Z = 2  /**< Layout direction Z. */
};

/** Direction of layout of grid layout. */
enum KzuUiGridLayoutDirection
{
    KZU_GRID_LAYOUT_DIRECTION_RIGHT = 0, /**< Layout first right, then down. */
    KZU_GRID_LAYOUT_DIRECTION_DOWN = 1   /**< Layout first down, then right. */
};

/**
 * Grid layouting size definition.
 * Used by both grid layout and grid layer.
 */
struct KzuUiGridLayoutDefinition
{
    enum KzuUiGridLayoutSizeMode mode; /**< Layout size mode. */
    kzFloat userSize; /**< User size. */
    kzFloat maxSize; /**< Maximum size. */
    kzFloat offset; /**< Offset. */
};

/** Information used to store the state between function calls when locating objects. */
struct KzuUiGridLayoutObjectLocationWorkspace
{
    enum KzuUiGridLayoutDirection direction; /**< Direction of layout. */
    kzUint columnCount;                      /**< Column count of layout. */
    kzUint rowCount;                         /**< Row count of layout. */
    kzUint row;                              /**< Row of the next location. */
    kzUint column;                           /**< Column of the next location. */
};

/** Gets an address property. Returns whether it was found. */
kzBool kzuUiGridLayoutGetAddressProperty_private(const struct KzuObjectNode* objectNode, const struct KzuPropertyType* propertyType, kzUint minValue, kzUint* out_address);
/** Gets location of the given object. Requires a workspace to store state between calls. */
void kzuUiGridLayoutGetObjectLocation_private(const struct KzuObjectNode* objectNode, struct KzuUiGridLayoutObjectLocationWorkspace* workspace,
                                              kzUint* out_row, kzUint* out_column);
/** Initialize an object location workspace. Used in laying out grid items. */
kzsError kzuGridLayoutObjectLocationWorkspace_private(const struct KzuObjectNode* objectNode, kzUint rowCount, kzUint columnCount,
                                                      struct KzuUiGridLayoutObjectLocationWorkspace* workspace);

/** Get the address (row or column index) from a child of a grid layout. */
kzUint kzuUiGridLayoutGetAddressProperty(const struct KzuObjectNode* objectNode, const struct KzuPropertyType* propertyType,
                                         kzUint minValue);
/** Get a column for an object in a grid. */
kzUint kzuUiGridLayoutGetObjectColumn(const struct KzuObjectNode* gridLayoutItem);
/** Set a column for an object in a grid. */
kzsError kzuUiGridLayoutSetObjectColumn(const struct KzuObjectNode* gridLayoutItem, kzUint column);
/** Get column span for an object in a grid. */
kzUint kzuUiGridLayoutGetObjectColumnSpan(const struct KzuObjectNode* gridLayoutItem);
/** Set column span for an object in a grid. */
kzsError kzuUiGridLayoutSetObjectColumnSpan(const struct KzuObjectNode* gridLayoutItem, kzUint columnSpan);
/** Get a row for an object in a grid. */
kzUint kzuUiGridLayoutGetObjectRow(const struct KzuObjectNode* gridLayoutItem);
/** Set a row for an object in a grid. */
kzsError kzuUiGridLayoutSetObjectRow(const struct KzuObjectNode* gridLayoutItem, kzUint row);
/** Get row span for an object in a grid. */
kzUint kzuUiGridLayoutGetObjectRowSpan(const struct KzuObjectNode* gridLayoutItem);
/** Set row span for an object in a grid. */
kzsError kzuUiGridLayoutSetObjectRowSpan(const struct KzuObjectNode* gridLayoutItem, kzUint rowSpan);

/** Calculate grid layout weighed sizes. */
void kzuUiGridLayoutCalculateWeighedSizes(const struct KzcDynamicArray* definitions, kzFloat weightMultiplier);
/** Calculate grid layout offsets. */
void kzuUiGridLayoutCalculateOffsets(const struct KzcDynamicArray* definitions);
/** Find maximum accumulated space from grid layout definitions. */
kzFloat kzuUiGridLayoutFindMaximumAccumulated(const struct KzcDynamicArray* definitions);

/** Delete a dynamic array consisting of grid layout definitions. */
kzsError kzuUiGridLayoutDefinitionArrayDelete(struct KzcDynamicArray* definitionArray);
/** Parse grid layout definition array from property string. */
kzsError kzuUiGridLayoutParseDefinitions(const struct KzcMemoryManager* memoryManager,
                                         kzString definitionCollection, struct KzcDynamicArray* definitions);
/** Reset grid layout definition array and calculate assigned weight. */
kzFloat kzuUiGridLayoutResetDefinitionsAndCalculateWeights(const struct KzcDynamicArray* definitions);

/** Bounding volume getter shared between 3D layouts. */
kzsError kzuUiLayoutGetBoundingVolume(const struct KzuObjectNode* objectNode, struct KzuBoundingVolume* out_boundingVolume);


KZ_HEADER_END

#endif
