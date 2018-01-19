/**
* \file
* Specifies a shadow map composer.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_SHADOW_MAP_COMPOSER_H
#define KZU_SHADOW_MAP_COMPOSER_H


#include <user/resource/kzu_resource_common.h>

#include <system/debug/kzs_error.h>
#include <system/kzs_types.h>
#include <system/kzs_header.h>


/* Forward declarations */
struct KzcMemoryManager;
struct KzuComposer;
struct KzuFactory;
struct KzuMaterial;
struct KzuUIDomain;


/** Composer type identifier for shadow map. */
extern const KzuResourceType KZU_COMPOSER_TYPE_SHADOW_MAP;


/**
 * \struct KzuShadowMapComposer
 * Shadow map composer, inherited from KzuComposer.
 */
struct KzuShadowMapComposer;


/** Registers shadow map composer to factory. */
kzsError kzuShadowMapComposerRegisterToFactory(const struct KzuFactory* factory);


/** Creates new shadow map composer. */
kzsError kzuShadowMapComposerCreate(const struct KzcMemoryManager* memoryManager, kzString name, struct KzuUIDomain* uiDomain,
                                    struct KzuShadowMapComposer** out_shadowMapComposer);

/** Adds shadow material mapping to shadow map composer. When original material is the one that receives shadow in rendering, it's replaced with destination material. 
    If original material is already assigned with mapping, new value will override it. */
kzsError kzuShadowMapComposerAddShadowMaterialMapping(const struct KzuShadowMapComposer* shadowMapComposer, const struct KzuMaterial* originalMaterial, const struct KzuMaterial* destinationMaterial);
/** Removes shadow material mapping from associated material. Nothing is done if no mapping is found. */
kzsError kzuShadowMapComposerRemoveShadowMaterialMapping(const struct KzuShadowMapComposer* shadowMapComposer, const struct KzuMaterial* originalShadowMaterial);

/** Adds depth material mapping to shadow map composer. When original material is the one that is used in shadow casters' depth pass, it's replaced with destination material. 
    If original material is already assigned with mapping, new value will override it. */
kzsError kzuShadowMapComposerAddDepthMaterialMapping(const struct KzuShadowMapComposer* shadowMapComposer, const struct KzuMaterial* originalMaterial, const struct KzuMaterial* destinationMaterial);
/** Removes depth material mapping from associated material. Nothing is done if no mapping is found. */
kzsError kzuShadowMapComposerRemoveDepthMaterialMapping(const struct KzuShadowMapComposer* shadowMapComposer, const struct KzuMaterial* originalDepthMaterial);


/** Casts shadow map composer to composer. */
struct KzuComposer* kzuShadowMapComposerToComposer(struct KzuShadowMapComposer* composer);
/** Casts composer to shadow map composer. */
struct KzuShadowMapComposer* kzuShadowMapComposerFromComposer(const struct KzuComposer* composer);


#endif
