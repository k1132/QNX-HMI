/**
 * \file
 * Application interface. The functions declared here have no implementation in the Kanzi engine framework.
 * Instead the application must provide the implementations.
 * 
 * Copyright 2008-2014 by Rightware. All rights reserved.
 */
#ifndef KZA_APPLICATION_INTERFACE_H
#define KZA_APPLICATION_INTERFACE_H


#include <system/display/kzs_surface.h>
#include <system/display/kzs_window.h>
#include <system/kzs_types.h>
#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations. */
struct KzaApplication;
struct KzaSystemProperties;
struct KzaApplicationChangeEvent;
struct KzuWindow;


/** Constraint for limiting the number of frames per second the Engine is rendering. */
struct KzaApplicationFPSConstraints
{
    kzBool enabled; /**< Is the FPS limit enabled. The default value is ::KZ_FALSE. */
    kzUint maximumFPS; /**< Maximum FPS when the limit is enabled. The default value is 120. */
};

/** Configurable application properties. */
struct KzaApplicationProperties
{
    kzUint memoryPoolCount; /**< Number of memory pools to allocate in the pooled memory manager. The default value is 1.
                                 This can be set to zero to disable the pooled memory manager. */
    kzUint memoryPoolSize; /**< Size of a single memory pool in bytes. The total allocated memory for the pooled memory manager
                                is therefore memoryPoolCount * memoryPoolSize bytes. The default value is 2 megabytes.
                                Notice that Kanzi itself will use about 1.5 megabytes of this space, depending on ::KZU_ENGINE_DEFAULT_QUICK_MEMORY_SIZE,
                                ::KZC_RENDERER_UNIFORM_CACHE_SIZE, ::KZC_RENDERER_PER_FRAME_MEMORY_MANAGER_SIZE, KZC_RENDERER_MAX_ZERO_FLOAT_ARRAY_SIZE
                                defined in kzc_renderer.c, kzuCoreAssetDataSize defined in kzu_core_asset_data.c and several different structure sizes. */
    kzBool useThreadedMemoryManager; /**< If ::KZ_TRUE, the pooled memory manager is made thread-safe. The default value is ::KZ_FALSE. */
    struct KzsWindowProperties windowProperties; /**< Configuration for the primary window of the application framework. */
    struct KzsSurfaceProperties surfaceProperties; /**< Properties for the surface of the primary window. */
    kzMutableString binaryNameStorage; /**< Dynamically allocated memory for the binary name. KZ_NULL when statically allocated. */
    kzString binaryName; /**< Path to either the binary config file listing all .kzb files that are loaded to project, or a path to a single .kzb file.
                              The default value is ::KZ_NULL. */
    kzBool gridEnabled; /**< If ::KZ_TRUE, the grid is enabled by default in the preview system. The default value is ::KZ_FALSE. */
    kzBool debugObjectsEnabled; /**< Are debug objects enabled by default in the preview system. The default value is ::KZ_FALSE. */
    kzBool freeCameraEnabled; /**< Is free camera enabled by default in the preview system.
                                   The default value is ::KZ_TRUE if ::kzaApplicationCreateForToolModule() is used, otherwise ::KZ_FALSE. */
    kzBool pickingEnabled; /**< Is picking enabled by default in the preview system.
                                The default value is ::KZ_TRUE if ::kzaApplicationCreateForToolModule() is used, otherwise ::KZ_FALSE. */
    kzBool transformGizmoEnabled; /**< Is transform gizmo enabled by default in the preview system.
                                       The default value is ::KZ_TRUE if ::kzaApplicationCreateForToolModule() is used, otherwise ::KZ_FALSE. */
    kzBool boundingBoxEnabled; /**< Is bounding box enabled by default in the preview system. The default value is ::KZ_FALSE. */
    kzBool fpsInfoEnabled; /**< Is FPS info enabled by default in the preview system. The default value is ::KZ_FALSE. */
    kzBool logVisualizationEnabled; /**< If ::KZ_TRUE, the application log is drawn in the preview system. The default value is ::KZ_FALSE. */
    kzBool lightWeightInitializationEnabled; /**< Is lightweight initialization enabled (no default shaders). The default value is ::KZ_FALSE. */
    kzBool overdrawVisualizationEnabled; /**< Is overdraw visualization enabled. The default value is ::KZ_FALSE. */
    kzBool animationVisualizationEnabled; /**< Is animation visualization enabled. The default value is ::KZ_FALSE. */
    kzBool functionCallProfilingEnabled; /**< Is function call specific profiling enabled. When ::KZ_TRUE, prints to the console a function call tree with
                                              cumulative times, occurring every 100th frame. Does not print anything when
                                              ::KzaApplicationProperties::animationVisualizationEnabled is ::KZ_TRUE. */
    kzBool loadingTimeProfilingEnabled; /**< Is loading time profiling enabled. When ::KZ_TRUE, after the startup prints to the console a duration of loading times. */
    kzBool previewSystemEnabled; /**< Is the preview system enabled by default. When ::KZ_FALSE, debug composer, profiling HUD, transform gizmo, preview camera
                                      and selection handling & rendering is disabled.
                                      The default value is ::KZ_TRUE if ::kzaApplicationCreateForToolModule() is used, otherwise ::KZ_FALSE. */
    kzBool extensionOutputEnabled; /**< Is the list of graphics related extensions printed when launching the application, useful for debugging which
                                        extensions are supported by platform. The default value is ::KZ_FALSE. */
    struct KzaApplicationFPSConstraints fpsConstraints; /**< Timer controller for application. */

    kzUint loadingThreadCount; /**< Loader thread count for resources, default 0 (loads everything in main thread). */
    kzUint loadingThreadsMemoryManagerSize; /**< Memory manager size for loading threads, needs to be large enough as the loader thread's hold the loaded resources. If specified 0 and loadingThreadCount is larger than 0, takes half of the pooled memory manager size. */ 
    kzBool useMemoryMappedLoading; /**< Use memory mapping when loading KZB files. The default value is ::KZ_FALSE. */ 
    kzUint defaultDisplayIndex; /**< Index of the display that full screen windows will be created on by default. */
    kzString startupLocale; /**< Locale to use when launching the application. */

    /** Function callback for initialization. This function is called as soon as possible after the Application framework has been created and configured. */
    kzsError (*onStartup)(struct KzaApplication* application);

    /** Function callback for deinitialization. This function is called when the application is shutting down and the ::KzaApplication object is still valid. */
    kzsError (*onShutdown)(struct KzaApplication* application);

    /** Function callback for initialization that is using the .KZB data. This function is called right after the .KZB binaries have been loaded. */
    kzsError (*onProjectLoaded)(struct KzaApplication* application);

    /** Function callback for updating logic. This function is called for every frame.
     * \param application The application structure.
     * \param deltaTime The delta time passed to ::kzaApplicationUpdate(). By default this is the time elapsed since the previous frame in milliseconds.
     */
    kzsError (*onUpdate)(struct KzaApplication* application, kzUint deltaTime);

    /** Function callback for rendering. This function is called for every frame before any other rendering function. */
    kzsError (*onPreRender)(const struct KzaApplication* application);

    /** Function callback for rendering. This function is called for every frame after the root layer has been rendered
        but before the preview system is rendered. */
    kzsError (*onPostRender)(const struct KzaApplication* application);

    /* Event handlers. */

    /** Event callback for application state changes. */
    kzsError (*onApplicationEvent)(struct KzaApplication* application, struct KzaApplicationChangeEvent* changeEvent);

    /** Event callback for pointing device (e.g. mouse or touch screen) input events. */
    kzsError (*onPointerInputEvent)(struct KzaApplication* application, const struct KzsInputEventPointer* inputData);
    
    /** Event callback for keyboard input events. */
    kzsError (*onKeyInputEvent)(struct KzaApplication* application, const struct KzsInputEventKey* inputData);

    /** Event callback for window events. */
    kzsError (*onWindowEvent)(struct KzaApplication* application, enum KzsEventType eventType, const struct KzuWindow* window);
};


/**
* Application configuration function. This function is called from ::kzaMain() when
* the application is started, but before it is initialized. 
* This function must be implemented in the application that uses the application framework.
* The user can specify the application window properties, allocated RAM size, and set up various callback functions
* in ::kzApplicationConfigure() to control the execution later at desired points.
* \param systemProperties Command line arguments from the operating system.
* \param configuration Application properties that can be modified inside ::kzApplicationConfigure() to set up
*        callback functions, window properties, RAM size etc.
*/
void kzApplicationConfigure(const struct KzaSystemProperties* systemProperties, struct KzaApplicationProperties* configuration); /*lint -efunc(715,818,kzApplicationConfigure) Warning disabled for call-backs. */


KZ_HEADER_END


#endif
