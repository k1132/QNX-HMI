/**
* \file
* User interface grid layout component.
*
* KzuUiGridLayout lays out its children in a grid which size is specified by ::KZU_PROPERTY_TYPE_GRID_LAYOUT_ROW_DEFINITIONS
* and ::KZU_PROPERTY_TYPE_GRID_LAYOUT_COLUMN_DEFINITIONS properties. If these properties are missing, the grid does not have
* any cells. The cell of a child can be fixed by ::KZU_PROPERTY_TYPE_GRID_LAYOUT_ROW and ::KZU_PROPERTY_TYPE_GRID_LAYOUT_COLUMN
* integer properties defined in the child (0 is the first row or column). If a child does not have both of these properties, the
* next free cell is used.
*
* Grid Layout Messages
* ----
* KzuUiGridLayout does not send or receive any messages.
*
* Grid Layout Properties
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
* ::KZU_PROPERTY_TYPE_GRID_LAYOUT_DIRECTION integer property defines the primary layouting direction. Its valid values are
* ::KZU_GRID_LAYOUT_DIRECTION_RIGHT and ::KZU_GRID_LAYOUT_DIRECTION_DOWN. This property specifies whether KzuUiGridLayout lays 
* out its children first left to right and then top to bottom (::KZU_GRID_LAYOUT_DIRECTION_RIGHT), or first top to bottom
* and then left to right (::KZU_GRID_LAYOUT_DIRECTION_DOWN). The default value is ::KZU_GRID_LAYOUT_DIRECTION_RIGHT.
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
* ::KZU_PROPERTY_TYPE_LAYOUT_DEPTH float property specifies the size of the grid in Z-axis direction.
*
* \see \ref kzu_grid_layer.h for the 2D version of this layout.
*
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_UI_GRID_LAYOUT_H
#define KZU_UI_GRID_LAYOUT_H


#include <user/scene_graph/kzu_object.h>
#include <user/ui/kzu_layout.h>

#include <system/kzs_types.h>
#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations. */
struct KzcMemoryManager;
struct KzcHashMap;
struct KzuUiComponentNode;
struct KzuFactory;
struct KzuUIDomain;

/**
 * \struct KzuUiGridLayout
 * Grid layout user interface component. Aligns objects in a grid.
 */
struct KzuUiGridLayout;


/** Object type for Grid Layout. */
extern const KzuObjectType KZU_OBJECT_TYPE_UI_GRID_LAYOUT;


/** Creates a grid layout with default settings.
* \param memoryManager The memory manager to use for memory allocations.
* \param name Name of the grid layout.
* \param uiDomain The UI domain to use.
* \param out_uiGridLayout Pointer that is set to point to the new grid layout.
* \return KZS_SUCCESS on success.
*/
kzsError kzuUiGridLayoutCreate(const struct KzcMemoryManager* memoryManager, kzString name, struct KzuUIDomain* uiDomain, struct KzuUiGridLayout** out_uiGridLayout);

/** Registers component type to factory. */
kzsError kzuUiGridLayoutRegisterToFactory(const struct KzuFactory* factory);

/** Casts from KzuUiGridLayout to KzuUiComponentNode. */
struct KzuUiComponentNode* kzuUiGridLayoutToUiComponentNode(const struct KzuUiGridLayout* gridLayout);

/** Casts from KzuUiComponentNode to KzuUiGridLayout. */
struct KzuUiGridLayout* kzuUiGridLayoutFromUiComponentNode(const struct KzuUiComponentNode* component);


/** Get the number of rows. */
kzUint kzuUiGridLayoutGetRowCount(const struct KzuUiGridLayout* gridLayout);

/** Get the number of columns. */
kzUint kzuUiGridLayoutGetColumnCount(const struct KzuUiGridLayout* gridLayout);

/** Get primary layout direction of grid layout. */
enum KzuUiGridLayoutDirection kzuUiGridLayoutGetLayoutDirection(const struct KzuUiGridLayout* layout);

/** Add a row at the end of the grid. */
kzsError kzuUiGridLayoutAddRow(const struct KzuUiGridLayout* gridLayout, enum KzuUiGridLayoutSizeMode sizeMode, kzFloat size);

/** Add a column at the end of the grid. */
kzsError kzuUiGridLayoutAddColumn(const struct KzuUiGridLayout* gridLayout, enum KzuUiGridLayoutSizeMode sizeMode, kzFloat size);

/** Removes the row at the end of the grid. */
kzsError kzuUiGridLayoutRemoveRow(const struct KzuUiGridLayout* gridLayout);

/** Removes the column at the end of the grid. */
kzsError kzuUiGridLayoutRemoveColumn(const struct KzuUiGridLayout* gridLayout);

/** Resizes the row with the given index.
* \param gridLayout The grid layout.
* \param index Index of the row to resize. If this is too big, the function can crash.
* \param sizeMode ::KzuUiGridLayoutSizeMode value specifying meaning of the size argument.
* \param size Height of the row. This number is ignored if sizeMode is ::KZU_UI_GRID_LAYOUT_SIZE_AUTO.
* \return KZS_SUCCESS on success.
*/
kzsError kzuUiGridLayoutResizeRow(const struct KzuUiGridLayout* gridLayout, kzUint index, enum KzuUiGridLayoutSizeMode sizeMode, kzFloat size);

/** Resizes the column with the given index.
* \param gridLayout The grid layout.
* \param index Index of the column to resize. If this is too big, the function can crash.
* \param sizeMode ::KzuUiGridLayoutSizeMode value specifying meaning of the size argument.
* \param size Width of the column. This number is ignored if sizeMode is ::KZU_UI_GRID_LAYOUT_SIZE_AUTO.
* \return KZS_SUCCESS on success.
*/
kzsError kzuUiGridLayoutResizeColumn(const struct KzuUiGridLayout* gridLayout, kzUint index, enum KzuUiGridLayoutSizeMode sizeMode, kzFloat size);

/** Get the calculated size of a row.
* \param gridLayout The grid layout.
* \param index Index of the row. If this is too big, the function can crash.
* \return Height of the row as previously calculated in the measure function.
*/
kzFloat kzuUiGridLayoutGetActualRowSize(const struct KzuUiGridLayout* gridLayout, kzUint rowIndex);

/** Get the calculated size of a column.
* \param gridLayout The grid layout.
* \param index Index of the column. If this is too big, the function can crash.
* \return Width of the column as previously calculated in the measure function.
*/
kzFloat kzuUiGridLayoutGetActualColumnSize(const struct KzuUiGridLayout* gridLayout, kzUint columnIndex);


KZ_HEADER_END


#endif
