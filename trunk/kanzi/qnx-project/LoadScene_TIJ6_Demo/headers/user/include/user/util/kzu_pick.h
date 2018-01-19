/**
* \file
* Color buffer based picking utility.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_PICK_H
#define KZU_PICK_H


#include <system/debug/kzs_error.h>
#include <system/kzs_types.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations */
struct KzuEngine;
struct KzuObjectNode;
struct KzuCameraNode;
struct KzcMemoryManager;
struct KzuScene;
struct KzuTransformedScene;
struct KzuMaterial;
struct KzuViewportLayer;
struct KzuUIDomain;


/**
* \struct KzuPick
* Structure to hold picking context.
*/
struct KzuPick;


/** Create a new picking context. */
kzsError kzuPickCreate(const struct KzcMemoryManager* memoryManager, const struct KzuEngine* engine, kzUint width, kzUint height, struct KzuPick** out_pick);
/** Initialized the pick by loading the picking material from the CoreAssets. */
kzsError kzuPickInitialize(struct KzuPick* pick, const struct KzuUIDomain* uiDomain);
/** Delete a picking context. */
kzsError kzuPickDelete(struct KzuPick* pick);
/** Enables or disables double-sided picking. Doublesided picking picks both front and back faces of geometry. */
void kzuPickEnableDoubleSided(struct KzuPick* pick, kzBool enable);
/** Returns KZ_TRUE if double-sided picking is enabled, KZ_FALSE otherwise. */
kzBool kzuPickIsDoubleSided(const struct KzuPick* pick);
/** Perform object picking using a color id buffer. */
kzsError kzuPick(struct KzuPick* pick, const struct KzuEngine* engine, const struct KzuTransformedScene* transformedScene,
                 kzUint windowWidth, kzUint windowHeight, kzUint positionX, kzUint positionY,
                 struct KzuObjectNode** out_node, kzUint* out_meshCluster);
/** As kzuPick, but get pickable area size from current engine screen. */
kzsError kzuPickWithScreen(struct KzuPick* pick, const struct KzuEngine* engine,
                           const struct KzuTransformedScene* transformedScene, kzUint positionX,
                           kzUint positionY, struct KzuObjectNode** out_node, kzUint* out_meshCluster);
/** Perform material picking using a material id buffer. */
kzsError kzuPickMaterial(struct KzuPick* pick, const struct KzuEngine* engine,
                 const struct KzuTransformedScene* transformedScene, kzUint windowWidth, kzUint windowHeight,
                 kzUint positionX, kzUint positionY, struct KzuMaterial** out_material);


KZ_HEADER_END


#endif
