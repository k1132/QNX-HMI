/**
* \file
* Specifies a Depth Of Field composer.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_DOF_COMPOSER_H
#define KZU_DOF_COMPOSER_H


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


/** Composer type identifier for DOF. */
extern const KzuResourceType KZU_COMPOSER_TYPE_DOF;


/**
 * \struct KzuDOFComposer
 * DOF composer to achieve depth of field effect, inherited from KzuComposer.
 */
struct KzuDOFComposer;


/** Registers DOF composer to factory. */
kzsError kzuDOFComposerRegisterToFactory(const struct KzuFactory* factory);


/** Creates new DOF composer. */
kzsError kzuDOFComposerCreate(const struct KzcMemoryManager* memoryManager, kzString name, struct KzuUIDomain* uiDomain,
                              struct KzuDOFComposer** out_dofComposer);

/** Casts DOF composer to composer. */
struct KzuComposer* kzuDOFComposerToComposer(struct KzuDOFComposer* dofComposer);
/** Casts composer to DOF composer. */
struct KzuDOFComposer* kzuDOFComposerFromComposer(const struct KzuComposer* composer);


KZ_HEADER_END


#endif
