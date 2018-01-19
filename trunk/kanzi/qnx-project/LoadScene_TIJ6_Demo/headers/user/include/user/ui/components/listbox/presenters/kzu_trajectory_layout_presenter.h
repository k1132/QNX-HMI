/**
* \file
* Trajectory layout presenter.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_TRAJECTORY_LAYOUT_PRESENTER_H
#define KZU_TRAJECTORY_LAYOUT_PRESENTER_H


#include <system/kzs_types.h>
#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations. */
struct KzuPresenter;
struct KzcMemoryManager;
struct KzuUiTrajectoryLayout;
struct KzuUiListBox;
struct KzuTrajectory;


/** Creates a trajectory list box presenter. */
kzsError kzuTrajectoryLayoutPresenterCreate(const struct KzcMemoryManager* memoryManager,
                                            struct KzuUiListBox* listBox,
                                            struct KzuUiTrajectoryLayout* layout,
                                            struct KzuPresenter** out_presenter);

/** Sets trajectory for the list box. */
kzsError kzuTrajectoryLayoutPresenterSetTrajectory(const struct KzuPresenter* presenter, struct KzuTrajectory* trajectory);
/** Gets trajectory from the list box. */
struct KzuTrajectory* kzuTrajectoryLayoutPresenterGetTrajectory(const struct KzuPresenter* presenter);

/** Tells the presenter whether the list box is currently being attached or detached. */
void kzuTrajectoryLayoutPresenterSetIsAttaching(const struct KzuPresenter* presenter, kzBool value);


KZ_HEADER_END


#endif
