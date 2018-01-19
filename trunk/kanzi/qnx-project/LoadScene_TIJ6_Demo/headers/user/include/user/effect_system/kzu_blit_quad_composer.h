/**
* \file
* Specifies a blit quad composer.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_BLIT_QUAD_COMPOSER_H
#define KZU_BLIT_QUAD_COMPOSER_H


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


/** Composer type identifier for color adjustment */
extern const KzuResourceType KZU_COMPOSER_TYPE_BLIT_QUAD;

/**
 * \struct KzuBlitQuadComposer
 * Blits a quad on-screen with specified material, inherited from KzuComposer.
 */
struct KzuBlitQuadComposer;


/** Registers color adjustment composer to factory. */
kzsError kzuBlitQuadComposerRegisterToFactory(const struct KzuFactory* factory);

/** Createst a blit quad composer. */
kzsError kzuBlitQuadComposerCreate(const struct KzcMemoryManager* memoryManager, kzString name, struct KzuUIDomain* uiDomain,
                                   struct KzuBlitQuadComposer** out_blitQuadComposer);

/** Casts blit quad composer to composer. */
struct KzuComposer* kzuBlitQuadComposerToComposer(struct KzuBlitQuadComposer* blitQuadComposer);
/** Casts composer to blit quad composer. */
struct KzuBlitQuadComposer* kzuBlitQuadComposerFromComposer(const struct KzuComposer* composer);


KZ_HEADER_END


#endif
