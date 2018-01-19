/**
 * \file
 * Utility functions for acquiring resources
 * 
 * Copyright 2008-2014 by Rightware. All rights reserved.
 */
#ifndef KZU_OBJECT_RESOURCES_H
#define KZU_OBJECT_RESOURCES_H


#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations */
struct KzuTexture;
struct KzuObjectNode;
struct KzuMaterial;
struct KzuComposer;
struct KzuMesh;
struct KzuTrajectory;
struct KzuText;
struct KzuFont;
struct KzuPrefabTemplate;
struct KzuAnimationItem;
struct KzuStyle;
struct KzuStateManager;


/** Acquires texture resource from object node. */
kzsError kzuObjectNodeAcquireTexture(const struct KzuObjectNode* objectNode, kzString resourceId, struct KzuTexture** out_texture);

/** Acquires material resource from object node. */
kzsError kzuObjectNodeAcquireMaterial(const struct KzuObjectNode* objectNode, kzString resourceId, struct KzuMaterial** out_material);

/** Acquires composer resource from object node. */
kzsError kzuObjectNodeAcquireComposer(const struct KzuObjectNode* objectNode, kzString resourceId, struct KzuComposer** out_composer);

/** Acquires mesh resource from object node. */
kzsError kzuObjectNodeAcquireMesh(const struct KzuObjectNode* objectNode, kzString resourceId, struct KzuMesh** out_mesh);

/** Acquires trajectory resource from object node. */
kzsError kzuObjectNodeAcquireTrajectory(const struct KzuObjectNode* objectNode, kzString resourceId, struct KzuTrajectory** out_trajectory);

/** Acquires text resource from object node. */
kzsError kzuObjectNodeAcquireText(const struct KzuObjectNode* objectNode, kzString resourceId, struct KzuText** out_text);

/** Acquires font resource from object node. */
kzsError kzuObjectNodeAcquireFont(const struct KzuObjectNode* objectNode, kzString resourceId, struct KzuFont** out_font);

/** Acquires prefab template resource from object node. */
kzsError kzuObjectNodeAcquirePrefabTemplate(const struct KzuObjectNode* objectNode, kzString resourceId, struct KzuPrefabTemplate** out_prefabTemplate);

/** Acquires animation item resource from object node. */
kzsError kzuObjectNodeAcquireAnimationItem(const struct KzuObjectNode* objectNode, kzString resourceId, struct KzuAnimationItem** out_animationItem);

/** Acquires style resource from object node. */
kzsError kzuObjectNodeAcquireStyle(const struct KzuObjectNode* objectNode, kzString resourceId, struct KzuStyle** out_style);

/** Acquires state manager resource from object node. */
kzsError kzuObjectNodeAcquireStateManager(const struct KzuObjectNode* objectNode, kzString resourceId, struct KzuStateManager** out_stateManager);


KZ_HEADER_END


#endif
