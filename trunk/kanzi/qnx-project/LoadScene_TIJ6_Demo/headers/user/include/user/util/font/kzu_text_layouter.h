/**
* \file
* Text layouter is used for laying out text to a constrained area.
* The text is splitted to several lines when necessary.
*
* Below is a common use scenario for the text layouting.
* initialization:
*     result = kzuBasicTextLayouterCreate(memoryManager, font, &textLayouter);
*     kzsErrorForward(result);
*
*     Optionally set text layout parameters such as alignment and maximum bounds
*
* when the text has changed or in initialization for static text:
*     result = kzuTextLayouterCreateLayout(textLayouter, memoryManager, text, &textLayout);
*     kzsErrorForward(result);
*
*     result = kzuFontPrepareTextLayout(textLayout, renderer);
*     kzsErrorForward(result);
*
* rendering:
*     result = kzuFontDrawTextLayout(textLayout, renderer, x, y);
*     kzsErrorForward(result);
*
* uninitialization:
*     result = kzuTextLayoutDelete(textLayout);
*     kzsErrorForward(result);
*
*     result = kzuTextLayouterDelete(textLayouter);
*     kzsErrorForward(result);
*     Text layouter can also be deleted already right after the text layout is created.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_TEXT_LAYOUTER_H
#define KZU_TEXT_LAYOUTER_H


#include <system/debug/kzs_error.h>
#include <system/kzs_types.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations */
struct KzcMemoryManager;
struct KzcRenderer;
struct KzuFont;
struct KzuTextLayout;


/**
* \struct KzuTextLayouter
* Structure for text layouting and rendering.
*/
struct KzuTextLayouter;


/** Horizontal alignment options for text layout. */
enum KzuTextHorizontalAlignment
{
    KZU_TEXT_HORIZONTAL_ALIGNMENT_LEFT, /**< Text is aligned right. */
    KZU_TEXT_HORIZONTAL_ALIGNMENT_RIGHT, /**< Text is aligned left. */
    KZU_TEXT_HORIZONTAL_ALIGNMENT_CENTER /**< Text is centered horizontally. */
};

/** Vertical alignment options for text layout. */
enum KzuTextVerticalAlignment
{
    KZU_TEXT_VERTICAL_ALIGNMENT_TOP, /**< Text is aligned top. */
    KZU_TEXT_VERTICAL_ALIGNMENT_BASELINE, /**< Text is aligned on the baseline of the first line of text. */
    KZU_TEXT_VERTICAL_ALIGNMENT_CENTER, /**< Text is centered vertically. */
    KZU_TEXT_VERTICAL_ALIGNMENT_BOTTOM /**< Text is aligned bottom. */
};

/** A constant to indicate that the text layout area is not restricted horizontally. */
#define KZU_TEXT_LAYOUT_NO_WIDTH_RESTRICTION 0
/** A constant to indicate that the text layout area is not restricted vertically. */
#define KZU_TEXT_LAYOUT_NO_HEIGHT_RESTRICTION 0


/** Creates a text layouter with the given font. */
kzsError kzuTextLayouterCreate(const struct KzcMemoryManager* memoryManager, struct KzuFont* font,
                               struct KzuTextLayouter** out_textLayouter);

/** Deletes the text layouter. */
kzsError kzuTextLayouterDelete(struct KzuTextLayouter* textLayouter);

/**
 * Sets the maximum width in pixels for the text layout area. Note that at least one character per line will always be layouted.
 * Use KZC_TEXT_LAYOUT_NO_WIDTH_RESTRICTION for unlimited width.
 */
void kzuTextLayouterSetMaximumWidth(struct KzuTextLayouter* textLayouter, kzFloat width);

/**
 * Sets the maximum number of characters per line for the text layout area.
 * Use KZC_TEXT_LAYOUT_NO_WIDTH_RESTRICTION for unlimited characters per line.
 */
void kzuTextLayouterSetMaximumCharactersPerLine(struct KzuTextLayouter* textLayouter, kzUint charactersPerLine);

/**
 * Sets the maximum height in pixels for the layout. Note that at least one line will always be layouted.
 * Use KZC_TEXT_LAYOUT_NO_HEIGHT_RESTRICTION for unlimited height.
 */
void kzuTextLayouterSetMaximumHeight(struct KzuTextLayouter* textLayouter, kzFloat height);

/**
 * Sets the maximum number of lines for the layout.
 * Use KZC_TEXT_LAYOUT_NO_HEIGHT_RESTRICTION for unlimited number of lines.
 */
void kzuTextLayouterSetMaximumLines(struct KzuTextLayouter* textLayouter, kzUint maximumLines);

/** Sets the terminator string used when both horizontal and vertical space is running out for the text layout. */
kzsError kzuTextLayouterSetTerminator(struct KzuTextLayouter* textLayouter, kzString terminator);

/** Sets the horizontal alignment of the text. */
void kzuTextLayouterSetHorizontalAlignment(struct KzuTextLayouter* textLayouter, enum KzuTextHorizontalAlignment alignment);

/** Sets the vertical alignment of the text. */
void kzuTextLayouterSetVerticalAlignment(struct KzuTextLayouter* textLayouter, enum KzuTextVerticalAlignment alignment);

/** Sets the line spacing. The value is relative to the font height, for example 1 is normal spacing and 2 is double spacing. */
void kzuTextLayouterSetLineSpacing(struct KzuTextLayouter* textLayouter, kzFloat lineSpacing);

/** Sets the character spacing. The value is relative to the character advance, for example 1 is the normal advance and 2 is double advance. */
void kzuTextLayouterSetCharacterSpacing(struct KzuTextLayouter* textLayouter, kzFloat characterSpacing);

/** Sets the fixed character width. */
void kzuTextLayouterSetFixedCharacterWidth(struct KzuTextLayouter* textLayouter, kzFloat fixedCharacterWidth);

/** Disables the fixed character width. */
void kzuTextLayouterDisableFixedCharacterWidth(struct KzuTextLayouter* textLayouter);

/**
 * Lays out the given text using the given text layouter.
 * The returned text layout can be directly rendered with the associated font
 * or the layout information can be read from the structure.
 */
kzsError kzuTextLayouterCreateLayout(const struct KzuTextLayouter* textLayouter, const struct KzcMemoryManager* memoryManager,
                                     kzString text, struct KzuTextLayout** out_textLayout);

/**
 * Helper function for performing the layout and drawing the result on the screen. If the same text is rendered more
 * than once, the layout and drawing should be done separately.
 * Parameters x and y specifies where the text layout is drawn and depends on the specified alignments of the text layouter.
 */
kzsError kzuTextLayouterDrawText(const struct KzuTextLayouter* textLayouter, const struct KzcMemoryManager* memoryManager,
                                 struct KzcRenderer* renderer, kzString text, kzFloat x, kzFloat y);

/**
 * Helper function for performing the layout and drawing the result to 3D space. If the same text is rendered more
 * than once, the layout and drawing should be done separately.
 */
kzsError kzuTextLayouterDrawText3D(const struct KzuTextLayouter* textLayouter, const struct KzcMemoryManager* memoryManager,
                                   struct KzcRenderer* renderer, kzString text);

/** Gets the font used for the text layout. */
struct KzuFont* kzuTextLayoutGetFont(const struct KzuTextLayout* textLayout);

/** Deletes the text layout. */
kzsError kzuTextLayoutDelete(struct KzuTextLayout* textLayout);


KZ_HEADER_END


#endif
