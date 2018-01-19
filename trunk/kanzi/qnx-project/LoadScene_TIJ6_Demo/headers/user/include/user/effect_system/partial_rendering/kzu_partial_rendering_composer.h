/**
* \file
* Specifies a partial rendering composer.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_PARTIAL_RENDERING_COMPOSER_H
#define KZU_PARTIAL_RENDERING_COMPOSER_H


#include <user/resource/kzu_resource_common.h>

#include <system/debug/kzs_error.h>
#include <system/kzs_types.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations. */
struct KzcMatrix4x4;
struct KzcMemoryManager;
struct KzuComposer;
struct KzuFactory;
struct KzuLayer;
struct KzuPartialRenderingLayer;
struct KzuPartialRenderingObjectInfo;
struct KzuUIDomain;


/**
 * \struct KzuPartialRenderingComposer
 * PartialRendering composer to achieve partial rendering effect, inherited from KzuComposer.
 */
struct KzuPartialRenderingComposer;


/** Composer type identifier for partial rendering. */
extern const KzuResourceType KZU_COMPOSER_TYPE_PARTIAL_RENDERING;


/** Specifies list of modes where partial rendering mask can be. */
enum KzuPartialRenderingComposerMaskPhase
{
    KZU_PARTIAL_RENDERING_COMPOSER_MASK_PHASE_NONE = 0,
    KZU_PARTIAL_RENDERING_COMPOSER_MASK_PHASE_INTERNAL_TRANSPARENT_CONTENT = 1,
    KZU_PARTIAL_RENDERING_COMPOSER_MASK_PHASE_OCCLUSION_MASK_TRANSPARENT = 2,
    KZU_PARTIAL_RENDERING_COMPOSER_MASK_PHASE_INTERNAL_OPAQUE_CONTENT = 3,
    KZU_PARTIAL_RENDERING_COMPOSER_MASK_PHASE_OCCLUSION_MASK_OPAQUE = 4
};


/** Registers partial rendering composer to factory. */
kzsError kzuPartialRenderingComposerRegisterToFactory(const struct KzuFactory* factory);


/** Creates new partial rendering composer. */
kzsError kzuPartialRenderingComposerCreate(const struct KzcMemoryManager* memoryManager, kzString name, struct KzuUIDomain* uiDomain,
                                           struct KzuPartialRenderingComposer** out_partialRenderingComposer);

/** Returns if composer is partial rendering composer. */
kzBool kzuComposerIsPartialRenderingComposer(const struct KzuComposer* composer);

/** Casts partial rendering composer to composer. */
struct KzuComposer* kzuPartialRenderingComposerToComposer(struct KzuPartialRenderingComposer* composer);
/** Casts composer to partial rendering composer. */
struct KzuPartialRenderingComposer* kzuPartialRenderingComposerFromComposer(const struct KzuComposer* composer);

/** Get previous camera matrix. */
struct KzcMatrix4x4 kzuPartialRenderingComposerGetPreviousCameraMatrix(const struct KzuPartialRenderingComposer* partialRenderingComposer);
/** Tell if objects have changed for this partial rendering composer. */
kzBool kzuPartialRenderingComposerGetObjectsChanged(const struct KzuPartialRenderingComposer* partialRenderingComposer);
/** Set whether objects have been changed within the scene being rendered. */
void kzuPartialRenderingComposerSetObjectsChanged(struct KzuPartialRenderingComposer* partialRenderingComposer, kzBool objectsChanged);
/** Get object info collection. */
struct KzcHashMap* kzuPartialRenderingComposerGetObjectsInfo(const struct KzuPartialRenderingComposer* partialRenderingComposer);
/** Sets partial rendering composer for current frame. */
void kzuPartialRenderingComposerSetCurrentPartialRenderingLayer(struct KzuPartialRenderingComposer* partialRenderingComposer,
                                                                struct KzuPartialRenderingLayer* layer);
/** Is force reset set on a partial rendering composer? */
kzBool kzuPartialRenderingComposerIsForceReset(const struct KzuPartialRenderingComposer* partialRenderingComposer);
/** Set force reset state for a partial rendering composer. */
void kzuPartialRenderingComposerSetForceReset(struct KzuPartialRenderingComposer* partialRenderingComposer, kzBool forceReset);

/** Sets mask rendering phase enabled for partial rendering composer. */
void kzuPartialRenderingComposerSetMaskRenderingPhase(struct KzuPartialRenderingComposer* partialRenderingComposer, enum KzuPartialRenderingComposerMaskPhase maskRendering);


/** Sets owner (caller) layer for the partial rendering, will be reset after each render. This is to make sure that partial rendering composer is called from partial rendering layer. */
void kzuPartialRenderingComposerSetOwnerLayer_private(struct KzuPartialRenderingComposer* partialRenderingComposer, struct KzuLayer* owner);


KZ_HEADER_END


#endif
