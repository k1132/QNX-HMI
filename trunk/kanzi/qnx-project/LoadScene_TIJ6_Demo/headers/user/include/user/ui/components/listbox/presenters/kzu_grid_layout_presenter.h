/**
* \file
* Grid layout presenter.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_GRID_LAYOUT_PRESENTER_H
#define KZU_GRID_LAYOUT_PRESENTER_H


#include <system/kzs_header.h>
#include <system/kzs_types.h>
#include <system/debug/kzs_error.h>


KZ_HEADER_BEGIN


/* Forward declarations. */
struct KzuPresenter;
struct KzcMemoryManager;
struct KzuUiGridLayout;
struct KzuUiListBox;


/** Creates a grid layout presenter. */
kzsError kzuGridLayoutPresenterCreate(const struct KzcMemoryManager* memoryManager,
                                      struct KzuUiListBox* listBox,
                                      struct KzuUiGridLayout* layout,
                                      struct KzuPresenter** out_presenter);

/** Returns the layout object of a grid list box presenter. */
struct KzuUiGridLayout* kzuGridLayoutPresenterGetLayout(const struct KzuPresenter* gridListBoxPresenter);


KZ_HEADER_END


#endif
