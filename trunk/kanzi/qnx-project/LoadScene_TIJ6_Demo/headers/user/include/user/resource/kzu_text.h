/**
 * \file
 * Text resource.
 *
 * Copyright 2008-2014 by Rightware. All rights reserved.
 */
#ifndef KZU_TEXT_H
#define KZU_TEXT_H

#include <user/resource/kzu_resource_common.h>

#include <system/debug/kzs_error.h>
#include <system/kzs_types.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations */
struct KzcInputStream;
struct KzcMemoryManager;
struct KzuUIDomain;
struct KzuBinaryFileInfo;


/**
* \struct KzuText
* Structure to hold text.
*/
struct KzuText;


/** Resource type identifier for text. */
extern const KzuResourceType KZU_RESOURCE_TYPE_TEXT;


/** Creates a text resource. */
kzsError kzuTextCreate(const struct KzcMemoryManager* memoryManager, const struct KzuUIDomain* uiDomain,
                       kzString name, kzString text, struct KzuText** out_text);

/** Deletes a text resource. */
kzsError kzuTextDelete(struct KzuText* text);

/** Loads text resource from KZB. */
kzsError kzuTextLoadFromKZB(struct KzuText* text, struct KzcInputStream* inputStream, const struct KzuBinaryFileInfo* file);

/** Gets text resource text. */
kzString kzuTextGetText(const struct KzuText* text);


/** Converts text resource to resource. */
struct KzuResource* kzuTextToResource(const struct KzuText* text);
/** Converts resource to text resource. */
struct KzuText* kzuTextFromResource(const struct KzuResource* resource);
/** Casts resource to text resource, KZ_NULL if invalid type. */
struct KzuText* kzuTextCastFromResource(const struct KzuResource* resource);


KZ_HEADER_END


#endif
