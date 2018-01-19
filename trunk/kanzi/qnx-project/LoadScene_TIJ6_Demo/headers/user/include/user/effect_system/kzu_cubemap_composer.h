/**
* \file
* Specifies a composer which renders to a dynamic cubemap.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_CUBEMAP_COMPOSER_H
#define KZU_CUBEMAP_COMPOSER_H


#include <user/resource/kzu_resource_common.h>

#include <system/debug/kzs_error.h>
#include <system/kzs_types.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations */
struct KzcMemoryManager;
struct KzuCubemapRenderTargetTexture;
struct KzuComposer;
struct KzuFactory;
struct KzuUIDomain;
struct KzuObjectNode;


/** Composer type identifier for cubemap composer. */
extern const KzuResourceType KZU_COMPOSER_TYPE_CUBEMAP;


/**
 * \struct KzuCubemapComposer
 * Cubemap composer for rendering to a cubemap faces, inherited from KzuComposer.
 */
struct KzuCubemapComposer;


/** Registers cubemap composer to factory. */
kzsError kzuCubemapComposerRegisterToFactory(const struct KzuFactory* factory);


/** Creates new cubemap composer. */
kzsError kzuCubemapComposerCreate(const struct KzcMemoryManager* memoryManager, kzString name, struct KzuUIDomain* uiDomain,
                                  struct KzuCubemapComposer** out_cubemapComposer);

/** Casts cubemap composer to composer. */
struct KzuComposer* kzuCubemapComposerToComposer(struct KzuCubemapComposer* composer);
/** Casts composer to cubemap composer. */
struct KzuCubemapComposer* kzuCubemapComposerFromComposer(const struct KzuComposer* composer);

/** Returns the rendertarget cubemap texture from composer. */
struct KzuCubemapRenderTargetTexture* kzuCubemapComposerGetTexture(const struct KzuComposer* composer);

/** Attaches cubemap composer to viewer node. */
kzsError kzuCubemapComposerAttachToViewerNode(const struct KzuComposer* composer, struct KzuObjectNode* viewerNode);
/** Detaches cubemap composer from viewer node. */
kzsError kzuCubemapComposerDetachFromViewerNode(const struct KzuComposer* composer, struct KzuObjectNode* viewerNode);


KZ_HEADER_END


#endif
