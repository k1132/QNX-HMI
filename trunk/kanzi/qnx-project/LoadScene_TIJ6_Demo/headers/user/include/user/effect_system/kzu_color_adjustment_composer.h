/**
* \file
* Specifies a color adjustment composer.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_COLOR_ADJUSTMENT_COMPOSER_H
#define KZU_COLOR_ADJUSTMENT_COMPOSER_H


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
extern const KzuResourceType KZU_COMPOSER_TYPE_COLOR_ADJUSTMENT;


/**
 * \struct KzuColorAdjustmentComposer
 * Color adjustment composer to achieve HSL, brightness, contrast and gamma adjustments, inherited from KzuComposer.
 */
struct KzuColorAdjustmentComposer;


/** Registers color adjustment composer to factory. */
kzsError kzuColorAdjustmentComposerRegisterToFactory(const struct KzuFactory* factory);


/** Creates new Color Adjustment composer. */
kzsError kzuColorAdjustmentComposerCreate(const struct KzcMemoryManager* memoryManager, kzString name, struct KzuUIDomain* uiDomain,
                                          struct KzuColorAdjustmentComposer** out_colorAdjustmentComposer);

/** Casts color adjustment composer to composer. */
struct KzuComposer* kzuColorAdjustmentComposerToComposer(struct KzuColorAdjustmentComposer* colorAdjustmentComposer);
/** Casts composer to color adjustment composer. */
struct KzuColorAdjustmentComposer* kzuColorAdjustmentComposerFromComposer(const struct KzuComposer* composer);


KZ_HEADER_END


#endif
