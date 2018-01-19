/**
* \file
* Specifies a stereoscopic composer.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_STEREOSCOPIC_COMPOSER_H
#define KZU_STEREOSCOPIC_COMPOSER_H


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


/** Composer type identifier for stereoscopic. */
extern const KzuResourceType KZU_COMPOSER_TYPE_STEREOSCOPIC;


/**
 * \struct KzuStereoscopicComposer
 * Stereoscopic rendering composer, inherited from KzuComposer.
 */
struct KzuStereoscopicComposer;


/** Registers stereoscopic composer to factory. */
kzsError kzuStereoscopicComposerRegisterToFactory(const struct KzuFactory* factory);

/** Creates new stereoscopic composer. */
kzsError kzuStereoscopicComposerCreate(const struct KzcMemoryManager* memoryManager, kzString name, struct KzuUIDomain* uiDomain,
                                       struct KzuStereoscopicComposer** out_stereoscopicComposer);

/** Casts stereoscopic composer to composer. */
struct KzuComposer* kzuStereoscopicComposerToComposer(struct KzuStereoscopicComposer* stereoscopicComposer);
/** Casts composer to stereoscopic composer. */
struct KzuStereoscopicComposer* kzuStereoscopicComposerFromComposer(const struct KzuComposer* composer);


KZ_HEADER_END


#endif
