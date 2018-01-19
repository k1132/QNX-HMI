/**
* \file
* Basic text layouter is the default implementation of KzuTextLayouter.
*
* \see kzu_text_layouter.h
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_BASIC_TEXT_LAYOUTER_H
#define KZU_BASIC_TEXT_LAYOUTER_H


#include <system/debug/kzs_error.h>
#include <system/kzs_types.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations */
struct KzcMemoryManager;
struct KzuFont;
struct KzuTextLayouter;


/** Creates a basic text layouter with the given font. */
kzsError kzuBasicTextLayouterCreate(const struct KzcMemoryManager* memoryManager, struct KzuFont* font,
                                    struct KzuTextLayouter** out_textLayouter);


KZ_HEADER_END


#endif
