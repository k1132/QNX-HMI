/**
* \file
* Specifies a blur composer.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_BLUR_COMPOSER_H
#define KZU_BLUR_COMPOSER_H


#include <user/resource/kzu_resource_common.h>

#include <system/debug/kzs_error.h>
#include <system/kzs_types.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations */
struct KzcInputStream;
struct KzcMemoryManager;
struct KzuComposer;
struct KzuFactory;
struct KzuBinaryFileInfo;
struct KzuMaterial;
struct KzuUIDomain;
struct KzuRenderTargetTexture;
struct KzuResourceManager;


/** Composer type identifier for blur composer. */
extern const KzuResourceType KZU_COMPOSER_TYPE_BLUR;

/**
 * \struct KzuBlurComposer
 * Applies a blur effect.
 */
struct KzuBlurComposer;


/** Registers color adjustment composer to factory. */
kzsError kzuBlurComposerRegisterToFactory(const struct KzuFactory* factory);

/** Creates a blur composer. */
kzsError kzuBlurComposerCreate(const struct KzcMemoryManager* memoryManager, kzString name, struct KzuUIDomain* uiDomain,
                               struct KzuBlurComposer** out_blurComposer);

/** Gets blurred texture from blur composer, generated after apply is called. */
struct KzuRenderTargetTexture* kzuBlurComposerGetBlurredTexture(const struct KzuBlurComposer* blurComposer);
/** Gets screen target texture from blur composer, used in pass that is rendered on-screen. */
struct KzuRenderTargetTexture* kzuBlurComposerGetScreenTargetTexture(const struct KzuBlurComposer* blurComposer);

/** Casts blur composer to composer. */
struct KzuComposer* kzuBlurComposerToComposer(struct KzuBlurComposer* blitQuadComposer);
/** Casts composer to blur composer. */
struct KzuBlurComposer* kzuBlurComposerFromComposer(const struct KzuComposer* composer);


KZ_HEADER_END


#endif
