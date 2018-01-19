/**
* \file
* 2D user interface grid layout component.
* 
* KzuGridLayer lays out its children in a grid which size is specified by ::KZU_PROPERTY_TYPE_GRID_LAYOUT_ROW_DEFINITIONS
* and ::KZU_PROPERTY_TYPE_GRID_LAYOUT_COLUMN_DEFINITIONS properties. If these properties are missing, the grid does not have
* any cells. The cell of a child can be fixed by ::KZU_PROPERTY_TYPE_GRID_LAYOUT_ROW and ::KZU_PROPERTY_TYPE_GRID_LAYOUT_COLUMN
* integer properties defined in the child (0 is the first row or column). If a child does not have both of these properties, the
* next free cell is used.
*
* Grid Layer Messages
* ----
* KzuGridLayer does not send or receive any messages.
*
* Grid Layer Properties
* ----
* ::KZU_PROPERTY_TYPE_GRID_LAYOUT_ROW_DEFINITIONS string property defines the rows of the grid. The string has a special
* format of "[\*f|f];[\*f|f]..." where each row definition is separated by a ';' character, 'f' signifies a float number and '*' signifies
* a weighed (proportional) height. For example, "1.0;2.0;3.0" defines three rows with heights of 1.0, 2.0 and 3.0 respectively.
* ";;" specifies three rows that all have heights calculated from their content. "*1.0;*2.0;*3.0" specifies three rows where
* the first row has 1/6 of the total height (::KZU_PROPERTY_TYPE_LAYOUT_HEIGHT), the second 2/6 and the third 3/6.
*
* ::KZU_PROPERTY_TYPE_GRID_LAYOUT_COLUMN_DEFINITIONS string property defines the columns of the grid. The same string format
* as for ::KZU_PROPERTY_TYPE_GRID_LAYOUT_ROW_DEFINITIONS is used but for column widths.
*
* ::KZU_PROPERTY_TYPE_GRID_LAYOUT_ROW integer property can be set in a child of the grid layout. Its value is the number of
* the row where the child should be placed, starting from 0.
*
* ::KZU_PROPERTY_TYPE_GRID_LAYOUT_COLUMN integer property can be set in a child of the grid layout. Its value is the number of
* the column where the child should be placed, starting from 0.
*
* ::KZU_PROPERTY_TYPE_GRID_LAYOUT_ROW_SPAN integer property can be set in a child of the grid layout. Its value is the number
* of rows the child should occupy in the grid. Notice that this value cannot be larger than the remaining number of rows.
*
* ::KZU_PROPERTY_TYPE_GRID_LAYOUT_COLUMN_SPAN integer property can be set in a child of the grid layout. Its value is the number
* of columns the child should occupy in the grid. Notice that this value cannot be larger than the remaining number of columns.
*
* ::KZU_PROPERTY_TYPE_LAYOUT_WIDTH float property specifies the size of the grid in X-axis direction.
*
* ::KZU_PROPERTY_TYPE_LAYOUT_HEIGHT float property specifies the size of the grid in Y-axis direction.
*
* \see \ref kzu_ui_grid_layout.h for the 3D version of this layout.
*
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_GRID_LAYER_H
#define KZU_GRID_LAYER_H


#include <user/scene_graph/kzu_object_common.h>
#include <user/ui/kzu_layout.h>


KZ_HEADER_BEGIN


/* Forward declarations. */
struct KzcMemoryManager;
struct KzuFactory;
struct KzuLayer;
struct KzuUIDomain;
struct KzuGridLayer;


/** Object type for stack layout. */
extern const KzuObjectType KZU_OBJECT_TYPE_GRID_LAYER;


/** Creates an stack layer. */
kzsError kzuGridLayerCreate(const struct KzcMemoryManager* memoryManager, kzString name, struct KzuUIDomain* uiDomain, struct KzuGridLayer** out_stackLayer);
/** Registers stack layer to the factory. */
kzsError kzuGridLayerRegisterToFactory(const struct KzuFactory* factory);

/** Converts layer to stack layer. */
struct KzuGridLayer* kzuGridLayerFromLayer(const struct KzuLayer* layer);
/** Converts stack layer to layer. */
struct KzuLayer* kzuGridLayerToLayer(const struct KzuGridLayer* stackLayer);

/** Get actual size of a grid layer column. */
kzFloat kzuGridLayerGetActualColumnSize(const struct KzuGridLayer* gridLayer, kzUint columnIndex);
/** Get actual size of a grid layer row. */
kzFloat kzuGridLayerGetActualRowSize(const struct KzuGridLayer* gridLayer, kzUint rowIndex);
/** Get number of columns in the grid layer. */
kzUint kzuUiGridLayerGetColumnCount(const struct KzuGridLayer* gridLayer);
/** Get number of rows in the grid layer. */
kzUint kzuUiGridLayerGetRowCount(const struct KzuGridLayer* gridLayer);

/** Add new column (as the last column). */
kzsError kzuGridLayerAddColumn(const struct KzuGridLayer* gridLayer, enum KzuUiGridLayoutSizeMode sizeMode,
                               kzFloat size);
/** Add new row (as the last row). */
kzsError kzuGridLayerAddRow(const struct KzuGridLayer* gridLayer, enum KzuUiGridLayoutSizeMode sizeMode,
                            kzFloat size);
/** Remove the last column of a grid layer. */
kzsError kzuUiGridLayerRemoveColumn(const struct KzuGridLayer* gridLayer);
/** Remove the last row of a grid layer. */
kzsError kzuUiGridLayerRemoveRow(const struct KzuGridLayer* gridLayer);
/** Resize a grid layer column. */
kzsError kzuGridLayerResizeColumn(const struct KzuGridLayer* gridLayer, kzUint index, enum KzuUiGridLayoutSizeMode sizeMode,
                                  kzFloat size);
/** Resize a grid layer row. */
kzsError kzuGridLayerResizeRow(const struct KzuGridLayer* gridLayer, kzUint index, enum KzuUiGridLayoutSizeMode sizeMode,
                               kzFloat size);


KZ_HEADER_END


#endif
