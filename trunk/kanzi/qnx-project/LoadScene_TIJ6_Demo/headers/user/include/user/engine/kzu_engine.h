/**
* \file
* Structure for engine. Contains pipeline specific assets (current scene, renderer), timer, etc.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_ENGINE_H
#define KZU_ENGINE_H


#include <system/kzs_types.h>
#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/** Amount of quick memory used by engine. */
#define KZU_ENGINE_DEFAULT_QUICK_MEMORY_SIZE    (1 << 20)

/** Default vertex buffer pool size. */
#define KZU_ENGINE_DEFAULT_VERTEX_BUFFER_POOL_SIZE (1 << 22)
/** Default index buffer pool size. */
#define KZU_ENGINE_DEFAULT_INDEX_BUFFER_POOL_SIZE (1 << 20)

/** Engine loading time measurement constants. */
enum KzuEngineLoadingMeasurement
{
    KZU_ENGINE_LOADING_MEASUREMENT_RENDERER /**< Renderer loading time. */
};


/* Forward declaration structures. */
struct KzcDynamicArray;
struct KzcMemoryManager;
struct KzcStopwatch;
struct KzuCanvas;
struct KzuPropertyManager;
struct KzuPropertyCollection;
struct KzuRenderer;
struct KzuResourceManager;
struct KzuScene;
struct KzuUIDomain;
struct KzuTransformedScene;


/**
* \struct KzuEngine
* Structure for graphics engine core functionality. Handles the state machine, pipeline and storage specific functionality.
*/
struct KzuEngine;


/** Create a new engine and necessary components for it, such as renderer and its default materials. */
kzsError kzuEngineCreate(const struct KzcMemoryManager* memoryManager, kzUint quickMemorySize, struct KzuUIDomain* uiDomain, struct KzuEngine** out_engine);
/** Deletes an engine. */
kzsError kzuEngineDelete(struct KzuEngine* engine);
/** Creates lightweight version of engine, which does only necessary initialization to operate engine (no default materials created). */
kzsError kzuEngineCreateLightweight(const struct KzcMemoryManager* memoryManager, kzUint quickMemorySize, struct KzuUIDomain* uiDomain, struct KzuEngine** out_engine);

/** Updates engine state. Should be called once per frame. */
kzsError kzuEngineUpdate(struct KzuEngine* engine);

/** Create transform gizmo. */
kzsError kzuEngineCreateTransformGizmo(struct KzuEngine* engine);
/** Get the transform gizmo (may return NULL). */
struct KzuTransformGizmo* kzuEngineGetTransformGizmo(const struct KzuEngine* engine);

/** Sets active canvas for engine. */
void kzuEngineSetActiveCanvas(struct KzuEngine* engine, const struct KzuCanvas* canvas);
/** Gets active canvas that engine has. */
const struct KzuCanvas* kzuEngineGetActiveCanvas(const struct KzuEngine* engine);

/** Starts a frame for engine rendering. */
kzsError kzuEngineBeginFrame(struct KzuEngine* engine);
/** Ends a frame for engine rendering . */
kzsError kzuEngineEndFrame(struct KzuEngine* engine);
/** Sets minimum delta time for engine. */
void kzuEngineSetMinimumDeltaTime(struct KzuEngine* engine, kzUint minimumDeltaTime);
/** Enforces minimum delta time for engine. */
kzsError kzuEngineLimitFrameRate(struct KzuEngine* engine);
/** Returns the wall time interval between the two latest updates. */
kzUint kzuEngineGetDeltaWallTime(const struct KzuEngine* engine);

/** Updates engine FPS calculations. Should be called once per frame. */
void kzuEngineMeasurePerformance(struct KzuEngine* engine);
/** Gets frames per second from engine (FPS), measuring the overall frames per second. */
kzFloat kzuEngineGetFramesPerSecond(const struct KzuEngine* engine);
/** Sets GPU calls enabled / disabled. */
void kzuEngineSetGPUCallsEnabled(struct KzuEngine* engine, kzBool enabled);

/** Returns user renderer from engine. */
struct KzuRenderer* kzuEngineGetRenderer(const struct KzuEngine* engine);

/** Gets loading time measurement from engine. */
kzUint kzuEngineGetLoadingTime(const struct KzuEngine* engine, enum KzuEngineLoadingMeasurement measurement);


KZ_HEADER_END


#endif
