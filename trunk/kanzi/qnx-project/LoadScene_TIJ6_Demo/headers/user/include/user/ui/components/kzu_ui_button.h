/**
* \file
* User interface button component.
* 
* KzuUiButton does not have any visual appearance itself, that is provided by the child or children of the component.
*
* All Kanzi buttons (KzuUiButton, KzuUiToggleButton, KzuButtonLayer, KzuToggleButtonLayer) provide a number of messages
* and properties based on received input events (such as touch screen input). In addition, there are a number of properties
* the user can set to affect behavior of the buttons.
*
* Button Messages
* ----
* ::KZU_MESSAGE_BUTTON_CLICK message is sent when a click (both press and release) happens on top of the button.
*
* ::KZU_MESSAGE_BUTTON_ENTER message is sent when the finger (or mouse pointer) enters the button.
*
* ::KZU_MESSAGE_BUTTON_LEAVE message is sent when the finger (or mouse pointer) leaves the button.
*
* ::KZU_MESSAGE_BUTTON_DOWN message is sent when the finger (or mouse button) press starts on top of the button, or when
* ::KZU_PROPERTY_TYPE_BUTTON_DOWN_ON_HOVER property is ::KZ_TRUE and the mouse pointer entered the button.
*
* ::KZU_MESSAGE_BUTTON_CANCEL message is sent when the finger (or mouse button) press started on top of the button
* and was released outside of the button.
*
* ::KZU_MESSAGE_BUTTON_LONG_PRESS message is sent if ::KZU_PROPERTY_TYPE_BUTTON_LONG_PRESS_INTERVAL is greater than zero
* and the finger (or mouse button) is pressed at least ::KZU_PROPERTY_TYPE_BUTTON_LONG_PRESS_INTERVAL milliseconds on top of the button.
*
* ::KZU_MESSAGE_TOGGLE_BUTTON_TOGGLED_ON message is sent if ::KZU_PROPERTY_TYPE_BUTTON_TOGGLE_STATE_COUNT is 2 and the
* button transitioned to state 1.
*
* ::KZU_MESSAGE_TOGGLE_BUTTON_TOGGLED_OFF message is sent if ::KZU_PROPERTY_TYPE_BUTTON_TOGGLE_STATE_COUNT is 2 and the
* button transitioned to state 0.
*
* ::KZU_MESSAGE_BUTTON_TOGGLE_STATE message is sent when ::KZU_PROPERTY_TYPE_BUTTON_TOGGLE_STATE_COUNT is greater than one
* and the button transitions from a toggle state to another. The message has one integer argument
* ::KZU_PROPERTY_TYPE_BUTTON_TOGGLE_STATE which tells the new state.
*
* Button Properties
* ----
* The button sets ::KZU_PROPERTY_TYPE_BUTTON__PRESSED property ::KZ_TRUE when the finger (or mouse button) is pressed on top of the button.
* The property value changes to ::KZ_FALSE when the finger is lifted or leaves the button. The default value is ::KZ_FALSE.
*
* ::KZU_PROPERTY_TYPE_BUTTON_TOGGLE_STATE_COUNT property tells the number of toggle states of the button. ::KzuToggleButtonLayer
* and ::KzuUiToggleButton set this property value to 2 by default, other buttons have this set to 0 by default.
* The button will transition from a toggle state to the next in order when ever a click happens on top of the button.
*
* ::KZU_PROPERTY_TYPE_BUTTON_DOWN_ON_HOVER property can be set ::KZ_TRUE when ::KZU_MESSAGE_BUTTON_DOWN is wanted on mouse pointer
* entering the button. I.e. ::KZU_MESSAGE_BUTTON_DOWN is sent even when the mouse button is not pressed down. The default value is ::KZ_FALSE.
*
* ::KZU_PROPERTY_TYPE_GESTURE_RECOGNIZER__MULTI_CLICK property can be set ::KZ_TRUE when double-click recognition is wanted.
* When the property is ::KZ_TRUE, the ::KZU_MESSAGE_MULTI_CLICK message is sent on double click of the button. The default value is ::KZ_FALSE.
*
* ::KZU_PROPERTY_TYPE_TOGGLE_BUTTON_STATE Boolean property is set ::KZ_TRUE if ::KZU_PROPERTY_TYPE_BUTTON_TOGGLE_STATE_COUNT is 2
* and the button transitioned to state 1. And it is set to ::KZ_FALSE if ::KZU_PROPERTY_TYPE_BUTTON_TOGGLE_STATE_COUNT is 2
* and the button transitioned to state 0. The property does not have an effect if ::KZU_PROPERTY_TYPE_BUTTON_TOGGLE_STATE_COUNT is not equal to 2.
* The default value is ::KZ_TRUE.
*
* ::KZU_PROPERTY_TYPE_BUTTON_TOGGLE_STATE integer property stores the current toggle state. The default value is 0.
*
* ::KZU_PROPERTY_TYPE_BUTTON_LONG_PRESS_INTERVAL can be set to greater than zero when ::KZU_MESSAGE_BUTTON_LONG_PRESS messages
* are wanted. The default value is 0.
*
* ::KZU_PROPERTY_TYPE_BUTTON_REPEAT_INTERVAL can be set to greater than zero when the button should repeatedly send
* ::KZU_MESSAGE_BUTTON_CLICK messages. The first ::KZU_MESSAGE_BUTTON_CLICK message is sent after the button has been pressed
* for at least ::KZU_PROPERTY_TYPE_BUTTON_REPEAT_INTERVAL milliseconds. After that, ::KZU_MESSAGE_BUTTON_CLICK is sent every
* ::KZU_PROPERTY_TYPE_BUTTON_REPEAT_INTERVAL milliseconds as long as the button is pressed. The default value is 0.
*
* Button Example Code
* ----
* The following code shows a way to create a KzuUiButton and execute a function when the user clicks on it.
\code{.c}
    static kzsError clickHandler(struct KzuMessage* message, void* userData)
    {
        struct KzuUiButton* button = (struct KzuUiButton*)userData;
        struct KzuObjectNode* buttonNode = kzuUiComponentNodeToObjectNode(kzuUiButtonToUiComponentNode(button));
        printf("Button '%s' clicked\n", kzuObjectNodeGetName(buttonNode));
        kzsSuccess();
    }

    kzsError buttonExample()
    {
        kzsError result;
        struct KzuUiButton* button;
        struct KzuObjectNode* buttonNode;
        struct KzuMessageDispatcher* dispatcher;
        struct KzuMesh* boxMesh;
        struct KzuMeshNode* boxNode;
        struct KzuRenderer* renderer = kzuEngineGetRenderer(engine);
        struct KzuMaterial* material = kzuRendererGetSolidColorMaterial(renderer);

        // ... code here to get 'scene', 'memoryManager', 'resourceManager' etc. from the application ...

        result = kzuUiButtonCreate(memoryManager, "button", uiDomain, &button);
        kzsErrorForward(result);

        // Add the button to the 3D scene.
        buttonNode = kzuUiComponentNodeToObjectNode(kzuUiButtonToUiComponentNode(button));
        result = kzuObjectNodeAddChild(kzuSceneToObjectNode(scene), buttonNode);
        kzsErrorForward(result);

        // The button is invisible until we add some mesh as its child, here a box mesh.
        result = kzuMeshCreateBox(resourceManager, "box mesh", 1.0f, 1.0f, 1.0f, material, &boxMesh);
        kzsErrorForward(result);

        result = kzuMeshNodeCreate(memoryManager, "box node", uiDomain, boxMesh, &boxNode);
        kzsErrorForward(result);

        result = kzuObjectNodeAddChild(buttonNode, kzuMeshNodeToObjectNode(boxNode));
        kzsErrorForward(result);

        // Mesh node has taken a reference to the mesh, release ours.
        result = kzuResourceRelease(kzuMeshToResource(boxMesh));
        kzsErrorForward(result);

        // Setup the click handler function.        
        dispatcher = kzuObjectNodeGetMessageDispatcher(buttonNode);
        result = kzuMessageDispatcherAddHandler(dispatcher, buttonNode, KZU_MESSAGE_BUTTON_CLICK,
                                                buttonNode, clickHandler, button);
        kzsErrorForward(result);

        // ... run the main loop of the application ...
        
        // Cleanup the button.
        result = kzuMessageDispatcherRemoveHandler(dispatcher, buttonNode, KZU_MESSAGE_BUTTON_CLICK,
                                                   clickHandler, button);
        kzsErrorForward(result);
        result = kzuObjectNodeDelete(buttonNode);
        kzsErrorForward(result);

        kzsSuccess();
    }
\endcode
*
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_UI_BUTTON_H
#define KZU_UI_BUTTON_H


#include <user/scene_graph/kzu_object_common.h>

#include <system/kzs_types.h>
#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations. */
struct KzcMemoryManager;
struct KzcHashMap;
struct KzuObjectNode;
struct KzuUiComponentNode;
struct KzuMessageDispatcher;
struct KzuFactory;
struct KzuUIDomain;


/**
 * \struct KzuUiButton
 * Button user interface component.
 *
 */
struct KzuUiButton;


/** Object type for button. */
extern const KzuObjectType KZU_OBJECT_TYPE_UI_BUTTON;


/** Creates a button with default settings.
* \param memoryManager The memory manager to use for memory allocations.
* \param name Name of the button.
* \param uiDomain The UI domain to use.
* \param out_button Pointer that is set to point to the new button.
* \return ::KZS_SUCCESS on success.
*/
kzsError kzuUiButtonCreate(const struct KzcMemoryManager* memoryManager, kzString name, struct KzuUIDomain* uiDomain, struct KzuUiButton** out_button);

/** Registers component type to factory. */
kzsError kzuUiButtonRegisterToFactory(const struct KzuFactory* factory);

/** Casts from KzuUiButton to KzuUiComponentNode. */
struct KzuUiComponentNode* kzuUiButtonToUiComponentNode(const struct KzuUiButton* button);

/** Casts from KzuUiComponentNode to KzuUiButton. */
struct KzuUiButton* kzuUiButtonFromUiComponentNode(const struct KzuUiComponentNode* component);


/** Gets the value of the ::KZU_PROPERTY_TYPE_BUTTON_LONG_PRESS_INTERVAL property of a KzuUiButton. */
kzFloat kzuUiButtonGetLongReleaseInterval(const struct KzuUiButton* button);

/** Gets the value of the ::KZU_PROPERTY_TYPE_BUTTON_REPEAT_INTERVAL property of a KzuUiButton. */
kzFloat kzuUiButtonGetRepeatInterval(const struct KzuUiButton* button);


KZ_HEADER_END


#endif
