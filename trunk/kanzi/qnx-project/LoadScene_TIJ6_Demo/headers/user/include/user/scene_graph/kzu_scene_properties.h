/**
 * \file
 * Property accessors for KzuScene.
 * 
 * Copyright 2008-2014 by Rightware. All rights reserved.
 */
#ifndef KZU_SCENE_PROPERTIES_H
#define KZU_SCENE_PROPERTIES_H


#include "kzu_scene.h"

#include <system/kzs_types.h>
#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations */
struct KzuScene;


/** Gets the value of property StartupScriptFunctionName in scene. */
kzString kzuSceneGetStartupScriptFunctionName(const struct KzuScene* scene);
/** Sets the value of property StartupScriptFunctionName in scene. */
kzsError kzuSceneSetStartupScriptFunctionName(const struct KzuScene* scene, kzString value);

/** Gets the value of property DefaultPickingCamera in scene. */
void* kzuSceneGetDefaultPickingCamera(const struct KzuScene* scene);
/** Sets the value of property DefaultPickingCamera in scene. */
kzsError kzuSceneSetDefaultPickingCamera(const struct KzuScene* scene, void* value);

/** Gets the value of property DefaultCamera in scene. */
void* kzuSceneGetDefaultCamera(const struct KzuScene* scene);
/** Sets the value of property DefaultCamera in scene. */
kzsError kzuSceneSetDefaultCamera(const struct KzuScene* scene, void* value);

/** Gets the value of property OverrideCamera in scene. */
void* kzuSceneGetOverrideCamera(const struct KzuScene* scene);
/** Sets the value of property OverrideCamera in scene. */
kzsError kzuSceneSetOverrideCamera(const struct KzuScene* scene, void* value);


KZ_HEADER_END


#endif
