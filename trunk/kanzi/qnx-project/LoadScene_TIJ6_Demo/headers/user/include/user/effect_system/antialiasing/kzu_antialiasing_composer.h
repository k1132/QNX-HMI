/**
* \file
* Specifies a antialiasing composer.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_ANTIALIASING_COMPOSER_H
#define KZU_ANTIALIASING_COMPOSER_H


#include <user/resource/kzu_resource_common.h>

#include <system/debug/kzs_error.h>
#include <system/kzs_types.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/** Type of antialiasing composer. */
enum KzuAntialiasingComposerType
{
    KZU_ANTIALIASING_COMPOSER_TYPE_FSAA, /**< FSAA antialiasing type. */
    KZU_ANTIALIASING_COMPOSER_TYPE_DITHER_AA, /**< Dither antialiasing type. */
    KZU_ANTIALIASING_COMPOSER_TYPE_TEMPORAL_AA, /**< Temporal antialiasing type. */
    KZU_ANTIALIASING_COMPOSER_TYPE_FXAA /**< FXAA antialiasing type. */
};


/* Forward declarations */
struct KzcMemoryManager;
struct KzuComposer;
struct KzuFactory;
struct KzuUIDomain;


/** Composer type identifier for antialiasing. */
extern const KzuResourceType KZU_COMPOSER_TYPE_ANTIALIASING;


/**
 * \struct KzuAntialiasingComposer
 * Anti-aliasing composer, inherited from KzuComposer.
 */
struct KzuAntialiasingComposer;


/** Registers antialiasing composer to factory. */
kzsError kzuAntialiasingComposerRegisterToFactory(const struct KzuFactory* factory);


/** Creates new antialiasing composer. */
kzsError kzuAntialiasingComposerCreate(const struct KzcMemoryManager* memoryManager, kzString name, struct KzuUIDomain* uiDomain,
                                       struct KzuAntialiasingComposer** out_aaComposer);

/** Sets antialiasing composer to moving / standing. */
void kzuAntialiasingComposerSetMovingState(struct KzuAntialiasingComposer* aaComposer, kzBool isMoving);


/** Casts antialiasing composer to composer. */
struct KzuComposer* kzuAntialiasingComposerToComposer(struct KzuAntialiasingComposer* composer);
/** Casts composer to antialiasing composer. */
struct KzuAntialiasingComposer* kzuAntialiasingComposerFromComposer(const struct KzuComposer* composer);


KZ_HEADER_END


#endif
