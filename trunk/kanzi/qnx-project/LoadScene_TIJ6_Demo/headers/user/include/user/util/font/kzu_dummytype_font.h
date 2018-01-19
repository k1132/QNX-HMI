/**
* \file
* Dummy truetype font implementation.
*
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_DUMMYTYPE_FONT_H
#define KZU_DUMMYTYPE_FONT_H


#include "kzu_font_common.h"

#include <core/util/color/kzc_color.h>

#include <system/debug/kzs_error.h>
#include <system/wrappers/kzs_opengl_base.h>
#include <system/kzs_types.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declaration structures. */
struct KzuTruetypeSystem;
struct KzuFont;
struct KzuTextLayout;
struct KzuUIDomain;
struct KzcMemoryManager;
struct KzcRenderer;
struct KzcRectangle;


/**
 * \struct KzuDummytypeSystem
 * Structure for dummy truetype font system. This system is a placeholder for applications that don't need fonts.
 */
struct KzuDummytypeSystem;

/**
* \struct KzuDummytypeFont
* Dummy font structure.
*/
struct KzuDummytypeFont;


/** Font type identifier for dummy font type. */
extern const KzuFontType KZU_FONT_TYPE_DUMMYTYPE;


/** Creates a dummy font type system. */
kzsError kzuDummytypeSystemCreate(const struct KzcMemoryManager* memoryManager, struct KzuUIDomain* uiDomain, struct KzuDummytypeSystem** out_dummytypeSystem);

/** Deletes a Dummy font type system. */
kzsError kzuDummytypeSystemDelete(struct KzuDummytypeSystem* dummytypeSystem);

/** Type casts a generic TrueType font system to more specific dummy font type system. */
struct KzuDummytypeSystem* kzuDummytypeSystemFromTruetypeSystem(struct KzuTruetypeSystem* truetypeSystem);

/** Type casts a dummy font type system to more generic TrueType font system. */
struct KzuTruetypeSystem* kzuDummytypeSystemToTruetypeSystem(struct KzuDummytypeSystem* dummytypeSystem);


KZ_HEADER_END


#endif
