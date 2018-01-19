/**
* \file
* Specifies a composer structure, which is set of render passes that are processed in order.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_EMPTY_COMPOSER_H
#define KZU_EMPTY_COMPOSER_H


#include <user/resource/kzu_resource_common.h>

#include <system/kzs_types.h>
#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations */
struct KzcMemoryManager;
struct KzuComposer;
struct KzuFactory;
struct KzuUIDomain;


/** Composer type identifier for render pass. */
extern const KzuResourceType KZU_COMPOSER_TYPE_EMPTY;


/** Registers empty composer to the factory. */
kzsError kzuEmptyComposerRegisterToFactory(const struct KzuFactory* factory);


/** Creates a new empty composer object. */
kzsError kzuEmptyComposerCreate(const struct KzcMemoryManager* memoryManager, kzString name, struct KzuUIDomain* uiDomain,
                                struct KzuComposer** out_composer);


KZ_HEADER_END


#endif
