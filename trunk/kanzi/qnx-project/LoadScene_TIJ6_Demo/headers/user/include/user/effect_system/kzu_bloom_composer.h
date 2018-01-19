/**
* \file
* Specifies a bloom composer.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_BLOOM_COMPOSER_H
#define KZU_BLOOM_COMPOSER_H


#include <user/resource/kzu_resource_common.h>

#include <system/debug/kzs_error.h>
#include <system/kzs_types.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations */
struct KzcMemoryManager;
struct KzuComposer;
struct KzuFactory;
struct KzuUIDomain;


/** Composer type identifier for bloom */
extern const KzuResourceType KZU_COMPOSER_TYPE_BLOOM;


/**
 * \struct KzuBloomComposer
 * Bloom composer to achieve bloom effect, inherited from KzuComposer.
 */
struct KzuBloomComposer;


/** Registers bloom composer to factory. */
kzsError kzuBloomComposerRegisterToFactory(const struct KzuFactory* factory);


/** Creates new bloom composer. */
kzsError kzuBloomComposerCreate(const struct KzcMemoryManager* memoryManager, kzString name, struct KzuUIDomain* uiDomain,
                                struct KzuBloomComposer** out_bloomComposer);

/** Casts bloom composer to composer. */
struct KzuComposer* kzuBloomComposerToComposer(struct KzuBloomComposer* bloomComposer);
/** Casts composer to bloom composer. */
struct KzuBloomComposer* kzuBloomComposerFromComposer(const struct KzuComposer* composer);


KZ_HEADER_END


#endif
