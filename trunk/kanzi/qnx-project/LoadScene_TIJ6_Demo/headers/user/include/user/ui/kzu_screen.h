/**
* \file
* Screen object represents the window area that is drawn by Kanzi. KzuScreen inherits from KzuObjectNode. 
* The KzuScreen object is usually the topmost object node and its only child is the KzuViewportLayer root layer.
* 
* Screen Messages
* ----
* KzuScreen listens to the ::KZU_MESSAGE_SCREEN_INSTANTIATE_PREFAB message that instantiates a prefab template. The message has the following four arguments.
* ::KZU_MESSAGE_ARGUMENT__INSTANTIATE_PREFAB__SOURCE_PREFAB resource ID argument specifies the prefab template to instantiate.
* ::KZU_MESSAGE_ARGUMENT__INSTANTIATE_PREFAB__TARGET_NODE string argument specifies an object node path to the object node that will be the instance of
* the prefab template. ::KZU_MESSAGE_ARGUMENT__INSTANTIATE_PREFAB__INSTANTIATING_NODE pointer argument specifies an existing prefab instance that is used 
* instead of creating a new one (this argument is optional). ::KZU_MESSAGE_ARGUMENT__INSTANTIATE_PREFAB__NAME string argument
* specifies the name for the new prefab instance. If the name is an empty string, it will be generated automatically.
*
* KzuScreen listens to the ::KZU_MESSAGE_SCREEN_REMOVE_NODE message that deletes an object node. The message has only one argument,
* ::KZU_MESSAGE_ARGUMENT__REMOVE_NODE__TARGET_NODE, which is an object node path string specifying the object node to delete.
*
* KzuScreen listens to the ::KZU_MESSAGE_SCREEN_REPLACE_NODE message that replaces an object node with a prefab instance. The message has the following
* four arguments. ::KZU_MESSAGE_ARGUMENT__REPLACE_NODE__NODE_TO_BE_REPLACED string argument specifies an object node path to the object node that should
* be replaced and deleted. ::KZU_MESSAGE_ARGUMENT__REPLACE_NODE__REPLACING_PREFAB resource ID argument specifies the prefab template to use.
* ::KZU_MESSAGE_ARGUMENT__REPLACE_NODE__REPLACING_NODE pointer argument specifies an existing prefab instance that is used instead of creating a new one
* (this argument is optional). ::KZU_MESSAGE_ARGUMENT__REPLACE_NODE__NAME string argument specifies the name for the new prefab instance. If the name
* is an empty string, it will be generated automatically.
*
* Screen Properties
* ----
* ::KZU_PROPERTY_TYPE_WINDOW_WIDTH float property specifies the 3D viewport width, depending on ::KZU_PROPERTY_TYPE_WINDOW_METRICS_TYPE, in either
* absolute pixel value or proportional value of the window's width.
*
* ::KZU_PROPERTY_TYPE_WINDOW_HEIGHT float property specifies the 3D viewport height, depending on ::KZU_PROPERTY_TYPE_WINDOW_METRICS_TYPE, in either
* absolute pixel value or proportional value of the window's height.
*
* ::KZU_PROPERTY_TYPE_WINDOW_METRICS_TYPE integer property specifies whether the window size properties ::KZU_PROPERTY_TYPE_WINDOW_WIDTH and
* ::KZU_PROPERTY_TYPE_WINDOW_HEIGHT specify absolute or relative sizes. The property value should be either ::KZU_WINDOW_METRICS_ABSOLUTE or
* ::KZU_WINDOW_METRICS_RELATIVE. The default value is ::KZU_WINDOW_METRICS_ABSOLUTE.
*
* ::KZU_PROPERTY_TYPE_SCREEN_ORIENTATION integer property specifies whether the window is drawn in landscape (::KZS_WINDOW_ORIENTATION_LANDSCAPE)
* or portrait (::KZS_WINDOW_ORIENTATION_PORTRAIT). The property value only affects how the window width and height are interpreted (in portrait,
* the window height specifies the 3D viewport width and the window width specifies the 3D viewport height), it does not cause Kanzi to rotate the 3D scene.
* The default value is ::KZS_WINDOW_ORIENTATION_LANDSCAPE.
*
* ::KZU_PROPERTY_TYPE_LAYER_RENDER_ON_DEMAND Boolean property specifies whether or not Kanzi redraws all layers only when they have changed. The default
* value is ::KZ_FALSE.
*
* \see \ref kzu_object.h, \ref kzu_viewport_layer.h.
*
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_SCREEN_H
#define KZU_SCREEN_H


#include <user/scene_graph/kzu_object_common.h>

#include <system/debug/kzs_error.h>
#include <system/input/kzs_input.h>
#include <system/kzs_types.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations */
struct KzcInputStream;
struct KzcMemoryManager;
struct KzuBinaryFileInfo;
struct KzuFactory;
struct KzuLayer;
struct KzuObjectNode;
struct KzuUIDomain;


/** Window metrics enumeration. */
enum KzuWindowMetricsType
{
    KZU_WINDOW_METRICS_ABSOLUTE = 0,
    KZU_WINDOW_METRICS_RELATIVE = 1,
    KZU_WINDOW_METRICS_TYPE_COUNT  /**< Last enum value for validity checks. */
};


/**
 * \struct KzuScreen
 * Screen represents the drawable area in a window. Inherited from KzuObjectNode.
 */
struct KzuScreen;


/** Object type identifier for screen objects. */
extern const KzuObjectType KZU_OBJECT_TYPE_SCREEN;


/** Create screen object. */
kzsError kzuScreenCreate(const struct KzcMemoryManager* memoryManager, kzString name, 
                         struct KzuUIDomain* uiDomain, struct KzuScreen** out_screen);

/** Registers screen type to factory. */
kzsError kzuScreenRegisterToFactory(const struct KzuFactory* factory);


/** Get screen from object node. */
struct KzuScreen* kzuScreenFromObjectNode(const struct KzuObjectNode* objectNode);
/** Returns an object node from screen. */
struct KzuObjectNode* kzuScreenToObjectNode(const struct KzuScreen* screen);
/** Sets root layer to screen. */
kzsError kzuScreenSetRootLayer(const struct KzuScreen* screen, const struct KzuLayer* rootLayer);
/** Gets root layer from screen. */
struct KzuLayer* kzuScreenGetRootLayer(const struct KzuScreen* screen);

/** Attaches the screen and its children recursively. */
kzsError kzuScreenAttach(const struct KzuScreen* screen);

/** Tell if an object node is a screen. */
kzBool kzuObjectNodeIsScreen(const struct KzuObjectNode* objectNode);


#include "kzu_screen_properties.h"


KZ_HEADER_END


#endif
