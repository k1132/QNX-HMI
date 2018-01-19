/**
* \file
* Text layouter class and virtual/base functions.
*
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_TEXT_LAYOUTER_BASE_H
#define KZU_TEXT_LAYOUTER_BASE_H


#include "kzu_text_layouter.h"

#include <system/debug/kzs_error.h>
#include <system/kzs_types.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations */
struct KzcMemoryManager;
struct KzuFont;
struct KzuTextLayout;
struct KzuTextLayouter;


/** Defines functions for different text layouter implementations. */
struct KzuTextLayouterClass
{
    /** Deletes the text layouter. */
    kzsError (*destructor)(struct KzuTextLayouter* textLayouter);

    /** Creates a text layout using this text layouter. */
    kzsError (*createLayout)(const struct KzuTextLayouter* textLayouter, const struct KzcMemoryManager* memoryManager,
                             kzString text, struct KzuTextLayout** out_textLayout);
};


struct KzuTextLayouter
{
    const struct KzuTextLayouterClass* textLayouterClass; /**< Class of the text layouter. */
    struct KzuFont* font; /**< Font used for layouting the text. */
    enum KzuTextHorizontalAlignment horizontalAlignment; /**< Horizontal alignment. */
    enum KzuTextVerticalAlignment verticalAlignment; /**< Vertical alignment. */
    kzFloat maximumWidth; /**< Maximum width in pixels or KZC_TEXT_LAYOUT_NO_WIDTH_RESTRICTION if no maximum specified. */
    kzUint maximumCharactersPerLine; /**< Maximum width in characters or KZC_TEXT_LAYOUT_NO_WIDTH_RESTRICTION if no maximum specified. */
    kzFloat maximumHeight; /**< Maximum height in pixels or KZC_TEXT_LAYOUT_NO_HEIGHT_RESTRICTION if no maximum specified. */
    kzUint maximumLines; /**< Maximum height in lines or KZC_TEXT_LAYOUT_NO_HEIGHT_RESTRICTION if no maximum specified. */
    kzFloat lineSpacing; /**< Line spacing in multiples of line height. */
    kzFloat characterSpacing; /**< Character spacing in multiples of character advance. */
    kzBool fixedCharacterWidthEnabled; /**< Is fixed character width specified. */
    kzFloat fixedCharacterWidth; /**< Fixed character width if it has been enabled. */
    kzMutableString terminator; /**< Terminator string to use if the given text does not fit to the given maximum size. */
};


/** Base function for initializing a text layouter. */
kzsError kzuTextLayouterCreate_protected(struct KzuTextLayouter* textLayouter, const struct KzuTextLayouterClass* textLayouterClass,
                                         struct KzuFont* font);

/** Base function for deleting a text layouter. */
kzsError kzuTextLayouterDestructor_protected(struct KzuTextLayouter* textLayouter);


/** Base function for creating a text layout. */
kzsError kzuTextLayouterCreateLayout_protected(const struct KzuTextLayouter* textLayouter, const struct KzcMemoryManager* memoryManager,
                                               kzString text, struct KzuTextLayout** out_textLayout);


KZ_HEADER_END


#endif
