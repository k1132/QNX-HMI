/**
* \file
* Monolithic window.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_MONOLITHIC_WINDOW_H
#define KZU_MONOLITHIC_WINDOW_H


#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declaration. */
struct KzcMemoryManager;


/**
 * \struct KzuMonolithicWindow
 * A Window designed for graphical unit tests.
 */
struct KzuMonolithicWindow;


/** Create window object. */
kzsError kzuMonolithicWindowCreate(const struct KzcMemoryManager* memoryManager, kzUint width, kzUint height, struct KzuMonolithicWindow** out_window);
/** Delete window. */
kzsError kzuMonolithicWindowDelete(struct KzuMonolithicWindow* window);

/** Updates window content. */
kzsError kzuMonolithicWindowUpdate(struct KzuMonolithicWindow* window);


KZ_HEADER_END


#endif
