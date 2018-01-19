/**
 * \file
 * Specifies a shadow map rendering utility, that is used for rendering shadows based on depth pass rendered from light.
 * 
 * Copyright 2008-2014 by Rightware. All rights reserved.
 */
#ifndef KZU_SHADOW_MAP_H
#define KZU_SHADOW_MAP_H


#include <system/debug/kzs_error.h>
#include <system/wrappers/kzs_opengl_base.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations. */
struct KzcMemoryManager;
struct KzuRenderer;
struct KzuRenderTargetTexture;
struct KzuScene;


/**
 * \struct KzuShadowMap
 * Rendering utility for shadow map; Preparation and applying for material.
 */
struct KzuShadowMap;


/** Creates shadow map. */
kzsError kzuShadowMapCreate(const struct KzcMemoryManager* memoryManager, struct KzuShadowMap** out_shadowMap);
/** Deletes shadow map. */
kzsError kzuShadowMapDelete(struct KzuShadowMap* shadowMap);

/** Prepares shadow map from current renderer state. */
kzsError kzuShadowMapPrepare(struct KzuShadowMap* shadowMap, const struct KzuRenderer* renderer, kzUint width, kzUint height);
/** Applies shadow map for rendering, on given index. Index must be < 4 or it is ignored */
kzsError kzuShadowMapApply(struct KzuShadowMap* shadowMap, const struct KzuRenderer* renderer, const struct KzuScene* scene, kzUint index);
/** Detaches shadow maps, so that shadow maps generated are no more used as texture properties. */
kzsError kzuShadowMapDetach(const struct KzuScene* scene);

/** Gets shadow map texture from shadow map. */
struct KzuRenderTargetTexture* kzuShadowMapGetShadowMapTexture(const struct KzuShadowMap* shadowMap);


KZ_HEADER_END


#endif
