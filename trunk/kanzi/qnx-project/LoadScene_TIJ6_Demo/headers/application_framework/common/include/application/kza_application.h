/**
 * \file
 * Application framework.
 *
 * The Kanzi application framework provides a way for developing custom applications based on Kanzi.
 * It is also possible to write a Kanzi-based application without the application framework, as the Custom_framework
 * example application shows, but using the application framework can save the developer a lot of effort.
 *
 * Notice that some of the following functions are reserved for the tool module that implements the
 * preview application under Kanzi Studio.
 *
 * Structure of a Kanzi-based Application
 * ----
 * The following code shows how a typical application built on the Kanzi application framework is structured.
 * The code has the basic structure and explanations instead of the complete actual code.
 * The reader can consult the various Kanzi example applications for actual working code examples.
 * Notice that the Kanzi application framework library provides the C main()
 * function that calls the ::kzaMain() function that calls the user-provided ::kzApplicationConfigure() function.
 \code{.c}
     kzsError keyInputEventHandler(struct KzaApplication* application, const struct KzsInputEventKey* inputData)
     {
         // Handle any keyboard input.
         if (kzsInputEventKeyGetButton(inputData) == KZS_KEY_ESC)
            kzaApplicationQuit(application);
         kzsSuccess();
     }
     kzsError shutdown(struct KzaApplication* application)
     {
         // Clean up code before the application exits.
         kzsSuccess();
     }
     kzsError projectLoaded(struct KzaApplication* application)
     {
         // Set up the user application code.
         // If there is no .KZB file that was loaded, create the 3D scene and layers here.
         kzsSuccess();
     }
     void kzApplicationConfigure(const struct KzaSystemProperties* systemProperties,
                                 struct KzaApplicationProperties* configuration)
     {
         // modify configuration to change window properties, RAM usage and set up callback functions.
         configuration->memoryPoolSize = 20 * 1024 * 1024;
         configuration->windowProperties.width = 800;
         configuration->windowProperties.height = 480;
         configuration->windowProperties.style = KZS_WINDOW_STYLE_RESIZABLE;
         configuration->onProjectLoaded = projectLoaded;
         configuration->onShutdown = shutdown;
         configuration->onKeyInputEvent = keyInputEventHandler;
     }
 \endcode
 * Using a Non-Kanzi Main Loop
 * ----
 * It is also possible to use the Kanzi application framework without using the main loop in ::kzaMain().
 * The following example code shows one way. The kzApplicationConfigure() function sets up the onProjectLoaded
 * callback function that sets up a timer handler that implements the custom main loop.
 \code{.c}
     kzsError mainLoop(struct KzaApplication* application)
     {
         kzsError result;
         kzUint previousTime = kzsTimeGetCurrentTimestamp();

         while (kzaApplicationGetState(application) == KZA_APPLICATION_STATE_RUNNING)
         {
             kzUint deltaTime;

             result = kzaApplicationGatherInput(application);
             kzsErrorForward(result);

             {
                 kzUint currentTime = kzsTimeGetCurrentTimestamp();
                 deltaTime = currentTime - previousTime;
                 previousTime = currentTime;
             }

             result = kzaApplicationUpdate(application, deltaTime);
             kzsErrorForward(result);

             result = kzaApplicationRender(application);
             kzsErrorForward(result);

             // Optional frame rate limit.
             result = kzaApplicationLimitFrameRate(application);
             kzsErrorForward(result);
         }

         kzsSuccess();
     }
     kzsError nonKanziMainLoop(struct KzuMessage* message, void* userData)
     {
         kzsError result;
         struct KzaApplication* application = (struct KzaApplication*)userData;
         struct KzuMessageDispatcher* messageDispatcher;

         messageDispatcher = kzuUIDomainGetMessageDispatcher(kzaApplicationGetUIDomain(application));
         result = kzuMessageDispatcherRemoveTimerHandler(messageDispatcher, nonKanziMainLoop, application);
         kzsErrorForward(result);
         for (;;)
         {
             KzaApplicationState state = kzaApplicationGetState(application);
             if (state == KZA_APPLICATION_STATE_RUNNING)
             {
                 result = mainLoop(application);
                 if (result != KZS_SUCCESS)
                     kzaApplicationSetState(application, KZA_APPLICATION_STATE_ERROR);
             }
             else if (state == KZA_APPLICATION_STATE_SUSPENDED)
             {
                 result = kzaApplicationIdle(application);
                 if (result != KZS_SUCCESS)
                     kzaApplicationSetState(application, KZA_APPLICATION_STATE_ERROR);
             }
             else
                 break;
         }

         kzsSuccess();
     }
     kzsError nonKanziMainLoopOnProjectLoaded(struct KzaApplication* application)
     {
         kzsError result;
         struct KzuMessageDispatcher* messageDispatcher;

         messageDispatcher = kzuUIDomainGetMessageDispatcher(kzaApplicationGetUIDomain(application));
         result = kzuMessageDispatcherAddTimerHandler(messageDispatcher, 1,
                                                      KZU_TIMER_MESSAGE_MODE_ONCE, nonKanziMainLoop, application);
         kzsErrorForward(result);

         kzsSuccess();
     }
     void kzApplicationConfigure(const struct KzaSystemProperties* systemProperties,
                                 struct KzaApplicationProperties* configuration)
     {
         // modify configuration to change window properties, RAM usage and set up callback functions.
         configuration->onProjectLoaded = nonKanziMainLoopOnProjectLoaded;
     }
 \endcode
 *
 * Copyright 2008-2014 by Rightware. All rights reserved.
 */
#ifndef KZA_APPLICATION_H
#define KZA_APPLICATION_H


#include "kza_application_preview_options.h"

#include <core/util/collection/kzc_dynamic_array.h>

#include <system/display/kzs_surface.h>
#include <system/kzs_types.h>
#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations. */
struct KzsWindowProperties;
struct KzsDisplay;
struct KzuCanvas;
struct KzuFont;
struct KzcMatrix4x4;
struct KzuFactory;
struct KzuCameraNode;
struct KzuHud;
struct KzuScreen;
struct KzuLayer;
struct KzuObjectNode;
struct KzuScript;
struct KzuScene;
struct KzuWindow;
/**
 * \struct KzaApplication
 * Internal Kanzi application framework data structure.
 */
struct KzaApplication;
struct KzaPlatform;
struct KzuPreviewSystem;
struct KzuComposer;


/** Enumeration for different application states. */
enum KzaApplicationState
{
    KZA_APPLICATION_STATE_UNINITIALIZED,    /**< The application is not yet initialized. */
    KZA_APPLICATION_STATE_RUNNING,          /**< The application is running normally. */
    KZA_APPLICATION_STATE_SUSPENDED,        /**< The application is suspended. The OpenGL graphics context is destroyed. */
    KZA_APPLICATION_STATE_QUITTING,         /**< The application is in the process of quitting without errors. */
    KZA_APPLICATION_STATE_ERROR             /**< The application has encountered an error and exits immediately. */
};

/** Enumeration for different event types. */
enum KzaApplicationChangeEventType
{
    KZA_APPLICATION_RESTARTED, /**< Application restart requested. */
    KZA_APPLICATION_RESUMED,   /**< Application resumed from pause or suspension. */
    KZA_APPLICATION_PAUSED,    /**< Application paused. */
    KZA_APPLICATION_SUSPENDED  /**< Application suspended. */
};


/** Read-only values from the system. */
struct KzaSystemProperties
{
    kzString* programArguments; /**< An array of program arguments from the system. The first element in the array contains the full path and
                                     executable name (if applicable) and the actual command line arguments start from the second element onwards. */
    kzUint programArgumentCount; /**< Number of arguments in the array. */
    kzBool skipSystemInitialization;  /**< Skip system initialization (used in unit tests). */
};

/** Change events. */
struct KzaApplicationChangeEvent
{
    enum KzaApplicationChangeEventType type; /**< Type of change event. */
};


/** Function pointer to the function which calls tool full reload. */
typedef void (*KzaApplicationToolReloadHandler)(void);


/** Creates the application framework and internal memory managers.
 * By default, a system memory manager and a pooled memory manager that has a single memory pool of 2 megabytes in
 * size is created, unless otherwise configured in the user-provided ::kzApplicationConfigure() function or
 * "application.cfg" configuration file (with "ApplicationMemoryManagerSize" and "ApplicationMemoryPoolCount" configuration keys).
 * The ::kzApplicationConfigure() function is called after the system memory manager (accessible with ::kzaApplicationGetSystemMemoryManager())
 * is created and before the pooled memory manager (accessible with ::kzaApplicationGetApplicationMemoryManager()) is created.
 * The pooled memory manager is not created if ::KzaApplicationProperties::memoryPoolCount is set to zero (in that case,
 * ::kzaApplicationGetApplicationMemoryManager() returns the system memory manager).
 *
 * \see \ref kzc_memory_pooled.h, \ref kzc_memory_system.h.
 */
kzsError kzaApplicationCreate(const struct KzaSystemProperties* systemProperties, struct KzaApplication** out_application);
/** Creates the application framework. Uses the system memory manager and enables the preview system.
 * This function is used in the preview tool module.  */
kzsError kzaApplicationCreateForToolModule(const struct KzaSystemProperties* systemProperties, struct KzaApplication** out_application);
/** Deletes the application framework. */
kzsError kzaApplicationDelete(struct KzaApplication* application);

/** Initialization. Loads metadata, including properties and messages from all .KZB files. */
kzsError kzaApplicationInitialize(struct KzaApplication* application);
/** Uninitialize. Frees memory allocated at initialization time. */
kzsError kzaApplicationUninitialize(struct KzaApplication* application);

/** Graphics initialization. Must be done after window attachment. */
kzsError kzaApplicationInitializeGL(struct KzaApplication* application);
/** Uninitialize graphics. Must be done before window detachment. */
kzsError kzaApplicationUninitializeGL(struct KzaApplication* application);

/** Initializes the OpenGL context. */
kzsError kzaApplicationInitializeGLContext(struct KzaApplication* application);
/** Uninitializes the OpenGL context.
 * \param application A valid application structure.
 * \param temporary If ::KZ_TRUE, the GPU resources are only invalidated, not undeployed, thus they will be redeployed
 *        automatically after the next ::kzaApplicationInitializeGLContext() call.
 * \return ::KZS_SUCCESS on success.
 */
kzsError kzaApplicationUninitializeGLContext(struct KzaApplication* application, kzBool temporary);

/** Initializes the application, loads the .KZB file and calls the onProjectLoaded callback unless the application is already initialized.
 * \param application A valid application structure.
 * \param canvas The canvas whose KzuScreen is loaded.
 * \return ::KZS_SUCCESS on success. An error can be returned if something goes wrong during initialization, loading or
 *         if the onProjectLoaded callback returns an error.
 */
kzsError kzaApplicationInitializeProject(struct KzaApplication* application, struct KzuCanvas* canvas);
/** Set default viewport parameters. */
kzsError kzaApplicationSetDefaultViewport(const struct KzaApplication* application, const struct KzuCanvas* canvas);
/** Re-layout application without validating or invalidating the layout.
* This means the layout is only calculated for nodes that already have their layout invalidated.
* Also, the application is prepared for the next ::kzaApplicationRender() call by calculating the transformed scene.
* This function can be useful after loading a project in the user part of application update, and wanting to use the
* objects acquired from that project immediately. Do not call this function unless you REALLY know what you're doing. */
kzsError kzaApplicationReLayout(const struct KzaApplication* application, const struct KzuCanvas* canvas);

/** Starts the application main loop if the current application state is ::KZA_APPLICATION_STATE_RUNNING.
 * The function returns (asserts in the debug build) immediately if the application state
 * is not ::KZA_APPLICATION_STATE_RUNNING when the function is entered. Otherwise, it runs the loop until
 * the state changes and then returns.
 * The application main loop basically consists of series of ::kzaApplicationGatherInput(),
 * ::kzaApplicationUpdate() and ::kzaApplicationRender() calls. There is also a small sleep to ensure that
 * the application spends at least the time set with ::kzaApplicationSetMinimumDeltaTime() between rendered frames.
 * \return ::KZS_SUCCESS on success. 
 */
kzsError kzaApplicationRun(struct KzaApplication* application);
/** Starts the application idle loop if the current application state is ::KZA_APPLICATION_STATE_SUSPENDED.
 * This function calls ::kzaApplicationUninitializeGLContext() in the beginning and ::kzaApplicationInitializeGLContext()
 * in the end if the application moved to the ::KZA_APPLICATION_STATE_RUNNING state.
 * The application only handles input while it is in the idle loop, it does not draw anything.
 * The function returns (asserts in the debug build) immediately if the application state
 * is not ::KZA_APPLICATION_STATE_SUSPENDED when the function is entered. Otherwise, it runs the loop until
 * the state changes and then returns.
 * \return ::KZS_SUCCESS on success.
 */
kzsError kzaApplicationIdle(struct KzaApplication* application);
/** Render application. This will render all the application windows. ::KzaApplicationProperties::onPreRender() and
 * ::KzaApplicationProperties::onPostRender() callbacks will be called for each window.
 * \return ::KZS_SUCCESS on success.
 */
kzsError kzaApplicationRender(const struct KzaApplication* application);
/** Gathers input events from the underlying window system to the application framework's event queue.
 * Normally this is called from ::kzaApplicationRun() or ::kzaApplicationIdle().
 * \return ::KZS_SUCCESS on success.
 */
kzsError kzaApplicationGatherInput(const struct KzaApplication* application);
/** Update application and scene graph state and handle various events.
 * This includes handling timer events, input events, resource loading, window events and laying out the scene graph nodes.
 * \return ::KZS_SUCCESS on success.
 */
kzsError kzaApplicationUpdate(struct KzaApplication* application, kzUint currentDeltaTime);

/** Sets the minimum delta time that limits the frame rate. */
void kzaApplicationSetMinimumDeltaTime(struct KzaApplication* application, kzUint minimumDeltaTime);
/** Enforces the frame rate limit by causing a sleep if called more often than allowed by the minimum delta time.
* \return ::KZS_SUCCESS on success.
*/
kzsError kzaApplicationLimitFrameRate(struct KzaApplication* application);

/** Gets the input event queue populated by ::kzaApplicationGatherInput(). */
struct KzsEventQueue* kzaApplicationGetEventQueue(const struct KzaApplication* application);

/** Set the application input event translation. */
void kzaApplicationSetInputEventTranslation(struct KzaApplication* application, enum KzsInputTranslation translation);
/** Get the application input event translation. */
enum KzsInputTranslation kzaApplicationGetInputEventTranslation(const struct KzaApplication* application);

/** Get the application input manager. The input manager is used when the application handles input events.
 * The manager e.g. creates messages for keyboard events and figures out where to send pointer events.
 */
struct KzuInputManager* kzaApplicationGetInputManager(const struct KzaApplication* application);
/** Get the application task scheduler. */
struct KzuTaskScheduler* kzaApplicationGetTaskScheduler(const struct KzaApplication* application);

/** Suspends the application and sets it to the ::KZA_APPLICATION_STATE_SUSPENDED state.
 * If the application is executing ::kzaMain(), it will go to the idle loop (see ::kzaApplicationIdle()).
 * \return ::KZS_SUCCESS on success.
 */
kzsError kzaApplicationSuspend(struct KzaApplication* application);
/** Resumes to the application and sets it to the ::KZA_APPLICATION_STATE_RUNNING state.
 * If the application is executing ::kzaMain(), it will go to the main loop (see ::kzaApplicationRun()).
 * \return ::KZS_SUCCESS on success.
 */
kzsError kzaApplicationResume(struct KzaApplication* application);


/** Marks GPU resources as released (undeployed) without actually releasing them.
* \return ::KZS_SUCCESS on success.
*/
kzsError kzaApplicationInvalidateGPUResources(const struct KzaApplication* application);


/** Creates the preview system and enables the preview features which were specified in the
 * applicationProperties parameter of the ::kzApplicationConfigure() function.
 * \return ::KZS_SUCCESS on success.
 */
kzsError kzaApplicationInitializePreviewFeatures(struct KzaApplication* application);


/** Gets the current state of the application. */
enum KzaApplicationState kzaApplicationGetState(const struct KzaApplication* application);
/** Sets the current state of the application. */
void kzaApplicationSetState(struct KzaApplication* application, enum KzaApplicationState state);

/** Request application framework to shut down the application. Does not quit immediately. */
void kzaApplicationQuit(struct KzaApplication* application);

/** Gets the application desktop. */
const struct KzsDesktop* kzaApplicationGetDesktop(const struct KzaApplication* application);

/** Gets the application displays. The items are of type <struct KzsDisplay*> */
struct KzsDisplay* kzaApplicationGetDisplay(const struct KzaApplication* application, kzUint index);

/** Gets the application surface configuration. */
const struct KzsSurfaceConfiguration* kzaApplicationGetSurfaceConfiguration(const struct KzaApplication* application);

/** Gets the user data associated with the application. */
void* kzaApplicationGetUserData(const struct KzaApplication* application);
/** Sets the user data associated with the application. Used for application specific structures for example. */
void kzaApplicationSetUserData(struct KzaApplication* application, void* userData);

/** Gets the application property manager. */
struct KzuPropertyManager* KzaApplicationGetPropertyManager(const struct KzaApplication* application);

/** Gets the application system memory manager of the application. */
struct KzcMemoryManager* kzaApplicationGetSystemMemoryManager(const struct KzaApplication* application);
/** Gets the memory manager of the application.
 * \param application A valid application structure.
 * \return Either the pooled or system memory manager created in ::kzaApplicationCreate().
 */
struct KzcMemoryManager* kzaApplicationGetApplicationMemoryManager(const struct KzaApplication* application);


/** Set tool reload callback and other tool information to application. This must not be called from application code.
* \return ::KZS_SUCCESS on success.
*/
kzsError kzaApplicationSetToolData(struct KzaApplication* application, KzaApplicationToolReloadHandler toolReloadFunction, kzString binaryName);
/** Check whether the Kanzi Studio is present.
* \return ::KZ_TRUE if the running application is integrated to the Kanzi Studio, otherwise ::KZ_FALSE.
*/
kzBool kzaToolIsPresent(const struct KzaApplication* application);
/** Requests a full reload from Kanzi Studio. */
void kzaToolRequestReload(const struct KzaApplication* application);

/** Gets the view camera of the current scene. */
struct KzuCameraNode* kzaApplicationGetViewCamera(const struct KzaApplication* application);
/** Gets the engine from application. */
struct KzuEngine* kzaApplicationGetEngine(const struct KzaApplication* application);
/** Gets the number of windows in application window set. */
kzUint kzaApplicationGetWindowCount(const struct KzaApplication* application);
/** Adds one window to the application window set.
* \return ::KZS_SUCCESS on success.
*/
kzsError kzaApplicationAddWindow(const struct KzaApplication* application, const struct KzuWindow* window);
/** Removes one window from the application window set.
* \return ::KZS_SUCCESS on success.
*/
kzsError kzaApplicationDeleteWindow(const struct KzaApplication* application, kzUint index);
/** Gets one window from application window set. */
struct KzuWindow* kzaApplicationGetWindow(const struct KzaApplication* application, kzUint index);
/** Gets the canvas from a window of the given index. */
struct KzuCanvas* kzaApplicationGetCanvas(const struct KzaApplication* application, kzUint windowIndex);
/** Gets the factory from application. */
struct KzuFactory* kzaApplicationGetFactory(const struct KzaApplication* application);
/** Gets the UI domain from application. */
struct KzuUIDomain* kzaApplicationGetUIDomain(const struct KzaApplication* application);
/** Gets the default display from application. */
struct KzsDisplay* kzaApplicationGetDefaultDisplay(const struct KzaApplication* application);

/**
 * Makes application to load a new binary from given binary name in the beginning of next update loop.
 * \param binaryName Path to either the binary config file listing all .kzb files that are loaded to project, or a path to a single .kzb file.
 * \return ::KZS_SUCCESS on success.
 */
kzsError kzaApplicationSetBinary(struct KzaApplication* application, kzString binaryName);

/** Get the master animation player from the task scheduler. */
struct KzuAnimationPlayer* kzaApplicationGetAnimationPlayer(const struct KzaApplication* application);
/** Get the current time from the main animation player of the task scheduler. */
kzFloat kzaApplicationGetAnimationPlayerTime(const struct KzaApplication* application);
/** Sets the time to all scenes under current root layer and the main animation player of the task scheduler.
* \return ::KZS_SUCCESS on success.
*/
kzsError kzaApplicationSetAnimationPlayerTime(struct KzaApplication* application, kzFloat time);

/** Reloads the current project with the given byte array. Called from tool module.
* \return ::KZS_SUCCESS on success.
*/
kzsError kzaApplicationReloadProject(struct KzaApplication* application, kzUint byteCount, const kzByte* bytes);
/** Reloads the current project from the given file path. Called from tool module.
* \return ::KZS_SUCCESS on success.
*/
kzsError kzaApplicationReloadProjectFromFile(struct KzaApplication* application, kzString binaryPath);
/** Reloads the current project from the given resource file.
* \return ::KZS_SUCCESS on success.
*/
kzsError kzaApplicationReloadProjectFromFileResource(struct KzaApplication* application, kzString resourceFile);
/** Patches the current project with the given byte array. Called from tool module.
* \return ::KZS_SUCCESS on success.
*/
kzsError kzaApplicationPatchProject(struct KzaApplication* application, kzUint byteCount, const kzByte* bytes);
/** Patches the current project from the given file path. Called from tool module.
* \return ::KZS_SUCCESS on success.
*/
kzsError kzaApplicationPatchProjectFromFile(struct KzaApplication* application, kzString binaryPath);
/** Patches the current project from the given resource file.
* \return ::KZS_SUCCESS on success.
*/
kzsError kzaApplicationPatchProjectFromFileResource(struct KzaApplication* application, kzString resourceFile);

/**
 * Sets the startup screen. Change is effective immediately.
 * By default, changes should happen after next update pass, do not call this function from message handlers.
 * \return ::KZS_SUCCESS on success.
 */
kzsError kzaApplicationSetStartupScreen(const struct KzaApplication* application, struct KzuScreen* screen);

/**
 * Sets the root layer. Change is effective immediately.
 * By default, changes should happen after next update pass, do not call this function from message handlers.
 * \return ::KZS_SUCCESS on success.
 */
kzsError kzaApplicationSetRootLayer(const struct KzaApplication* application, const struct KzuLayer* layer);
/** Sets the root layer. Change is effective after next update pass.
* \return ::KZS_SUCCESS on success.
*/
kzsError kzaApplicationSetRootLayerAsync(const struct KzaApplication* application, const struct KzuLayer* layer);
/** Gets root layer from the application. */
struct KzuLayer* kzaApplicationGetRootLayer(const struct KzaApplication* application);

/** Gets the startup screen of the application. */
struct KzuScreen* kzaApplicationGetScreen(const struct KzaApplication* application);


/** Prints renderer info.
* \return ::KZS_SUCCESS on success.
*/
kzsError kzaApplicationPrintRendererInfo(const struct KzaApplication* application);


/** Gets system properties from application. */
struct KzaSystemProperties* kzaApplicationGetSystemProperties(struct KzaApplication* application);

/** Gets window properties from application once configured. */
struct KzsWindowProperties* kzaApplicationGetWindowProperties(struct KzaApplication* application);

/** Gets application properties from application once configured. */
struct KzaApplicationProperties* kzaApplicationGetProperties(struct KzaApplication* application);

/** \return The debug composer or ::KZ_NULL. */
struct KzuComposer* kzaApplicationGetDebugComposer(const struct KzaApplication* application);

/** Application framework entry point. This function creates and initializes the ::KzaApplication object,
 * creates and shows an application window, initializes the OpenGL and renderer, sets the application
 * to the ::KZA_APPLICATION_STATE_RUNNING state, and goes to the main loop. In the main loop, the function
 * will execute ::kzaApplicationRun() when the application is in the ::KZA_APPLICATION_STATE_RUNNING state
 * and ::kzaApplicationIdle() when the application is in the ::KZA_APPLICATION_STATE_SUSPENDED state.
 *
 * The next time the caller can control the execution is when ::kzApplicationConfigure() is called. The
 * caller can set up various callback functions in ::kzApplicationConfigure() to control the execution
 * later at desired points. Usually ::KzaApplicationProperties::onProjectLoaded() is the most convenient
 * callback for initializing the user application code.
 *
 * \param systemProperties Command line arguments from the operating system. This structure can be later
 *        retrieved with ::kzaApplicationGetSystemProperties().
 */
kzsError kzaMain(const struct KzaSystemProperties* systemProperties);


KZ_HEADER_END


#endif
