/**
* \file
* Specifies a composer structure, which is set of render passes that are processed in order.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_COMPOSER_BASE_H
#define KZU_COMPOSER_BASE_H


#include <user/common/kzu_user.h>
#include <user/resource/kzu_resource_base.h>

#include <system/kzs_types.h>
#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations */
struct KzcDynamicArray;
struct KzcInputStream;
struct KzcMemoryManager;
struct KzuBinaryFileInfo;
struct KzuComposer;
struct KzuComposerEffectData;
struct KzuUIDomain;
struct KzuPropertyManager;
struct KzuRenderer;
struct KzuRenderContextStack;
struct KzuRenderTarget;
struct KzuUIDomain;
struct KzuRenderTargetTexture;
struct KzuTransformedScene;


/** Defines functions for different object node types. */
struct KzuComposerClass
{
    /** Initialize function for the composer */
    kzsError (*kzuComposerInitialize)(struct KzuComposer* composer);

    /** Uninitialize function for the composer */
    kzsError (*kzuComposerUninitialize)(struct KzuComposer* composer);

    /** Delete function for the composer */
    kzsError (*kzuComposerDelete)(struct KzuComposer* composer);

    /** Apply function for the composer */
    kzsError (*kzuComposerApply)(struct KzuComposer* composer, struct KzuRenderer* renderer, const struct KzuTransformedScene* transformedScene,
                                 struct KzuRenderContextStack* renderContextStack);
};


/** Structure for composer. */
struct KzuComposer
{
    struct KzuResource resource; /**< Inherited from resource. */
    const struct KzuComposerClass* composerClass; /**< Composer class, containing functions needed and specifies the type. */

    kzMutableString name;                         /**< Name of the composer. */
    struct KzcDynamicArray* children;             /**< Children of this composer. */
    struct KzuPropertyManager* propertyManager;   /**< Property manager of this composer. */

    struct KzuRenderTarget* renderTarget; /**< Render target. */
    struct KzuRenderTargetTexture* renderTargetTexture; /**< Render target texture created by the composer. */
};


/** Creates a new composer. */
kzsError kzuComposerCreate_protected(const struct KzuUIDomain* uiDomain, const struct KzuComposerClass* composerClass, kzString name, struct KzuComposer* composer);
/** Deletes a composer. */
kzsError kzuComposerDelete_protected(const struct KzuComposer* composer);

/** Iterates composer children. */
kzsError kzuComposerApplyChildren_protected(const struct KzuComposer* composer, struct KzuRenderer* renderer, const struct KzuTransformedScene* transformedScene,
                                            struct KzuRenderContextStack* renderContextStack);


KZ_HEADER_END


#endif
