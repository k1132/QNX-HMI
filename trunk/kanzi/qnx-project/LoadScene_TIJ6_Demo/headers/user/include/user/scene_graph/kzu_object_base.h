/**
* \file
* Object node private members.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_OBJECT_BASE_H
#define KZU_OBJECT_BASE_H


#include <user/scene_graph/kzu_object_common.h>

#include <core/util/math/kzc_matrix4x4.h>
#include <core/util/collection/kzc_dynamic_array.h>

#include <system/kzs_types.h>
#include <system/kzs_header.h>
#include <user/properties/kzu_property_manager.h>


KZ_HEADER_BEGIN


/* Forward declarations */
struct KzcInputStream;
struct KzuBinaryFileInfo;
struct KzuBindingRule;
struct KzuBoundingVolume;
struct KzuObjectNode;
struct KzuObjectNodeAppliedStyleEntry;
struct KzuObjectNodeLayoutData;
struct KzuRenderer;
struct KzuResource;
struct KzuStateManager;
struct KzuStyle;
struct KzuTransformedObjectNode;
struct KzuTrigger;
struct KzuUIDomain;


/** Defines functions for different object node types. */
struct KzuObjectNodeClass
{
    KzuObjectType parentType; /**< Pointer to the parent class. KZ_NULL for the first base class. */

    /** Initialize function for object node. */
    kzsError (*kzuObjectNodeInitialize)(struct KzuObjectNode* objectNode);

    /** Uninitialize function for object node. */
    kzsError (*kzuObjectNodeUninitialize)(struct KzuObjectNode* objectNode);

    /** Callback function when an object node becomes attached. */
    kzsError (*kzuObjectNodeOnAttached)(struct KzuObjectNode* objectNode);

    /** Callback function when an object node becomes detached. */
    kzsError (*kzuObjectNodeOnDetached)(struct KzuObjectNode* objectNode);

    /** Callback function that is called when object's property change or is removed. */
    kzsError (*kzuObjectNodeOnPropertyChanged)(struct KzuObjectNode* objectNode, const struct KzuPropertyType* propertyType, enum KzuPropertyNotificationReason reason);

    /** Copier function for the object node. */
    kzsError (*kzuObjectNodeCopy)(const struct KzuObjectNode* sourceObjectNode, struct KzuObjectNode* targetObjectNode);

    /** Renderer function for the object node. */
    kzsError (*kzuObjectNodeRender)(const struct KzuObjectNode* objectNode, struct KzuRenderer* renderer,
                                    const struct KzuTransformedObjectNode* transformedObjectNode, struct KzcMatrix4x4* worldTransformation);

    /** Function for getting bounding volume from object node. */
    kzsError (*kzuObjectNodeGetBoundingVolume)(const struct KzuObjectNode* objectNode, struct KzuBoundingVolume** out_boundingVolume);

    /** Function for loading the object node from KZB file. */
    kzsError (*kzuObjectNodeLoadFromKZB)(struct KzuObjectNode* objectNode, struct KzcInputStream* inputStream, const struct KzuBinaryFileInfo* file);
};

/** Object node resource entry. */
struct KzuObjectNodeResource
{
    kzMutableString id;     /**< Resource identifier. */
    kzMutableString resourceUrl; /**< Resource manager URL for the resource. */
};

/** Object node resource dictionary. */
struct KzuObjectNodeResourceDictionary
{
    struct KzcHashMap* resourcesByName; /**< Object node resources by their ids. <kzString, KzuObjectNodeResource>. */
};

/** Object node applied style entry. */
struct KzuObjectNodeAppliedStyleEntry
{
    struct KzuStyle* style; /**< Style. */
    kzBool manual; /**< Is the style applied manually. */
    kzBool abandoned; /**< Is entry abandoned? */
};

/** Object node binding entry. */
struct KzuObjectNodeBindingEntry
{
    struct KzuBindingRule* bindingRule; /**< Binding rule. */
    const void* owner; /**< Owner of the binding rule. */
};

/** Object node trigger entry. */
struct KzuObjectNodeTriggerEntry
{
    struct KzuTrigger* trigger; /**< Trigger. */
    const void* owner; /**< Owner of the trigger. */
};

/**
 * Base structure for object node. Contains information of node type (mesh, light, camera, ...), transformation,
 * list of child object nodes and set of properties.
 */
struct KzuObjectNode
{
    const struct KzuObjectNodeClass* objectNodeClass; /**< Class of the object node. */

    kzBool isRenderable; /**< Is object renderable. */
    kzBool isAttached; /**< Is object attached to screen or an object in scene graph. */
    kzBool isDetaching; /**< This flag is KZ_TRUE during kzuObjectNodeOnDetached virtual function call and KZ_FALSE otherwise. */

    struct KzuObjectNode* parent; /**< Parent of the object. */
    struct KzcDynamicArray* children; /**< Direct children of the object. <KzuObjectNode> */
    kzMutableString name; /**< Name of the object node. */
    struct KzuUIDomain* uiDomain; /**< UIDomain of the object node. */
    struct KzuObjectNodeResourceDictionary resourceDictionary; /**< Object node resource dictionary. */
    struct KzcDynamicArray* anonymousResources; /**< Object node anonymous resources, currently consists of styles. <KzuResource>. */
    struct KzcHashMap* anonymousResourceURLs; /**< Object node anonymous resource URLs. <kzString, KzuResource>. */
    struct KzcDynamicArray* appliedStyles;  /**< Styles applied to this object node. <KzuObjectNodeAppliedStyleEntry> */
    struct KzuStateManagerRuntime* stateManagerRuntime; /**< State manager runtime state. */
    struct KzcDynamicArray* inputManipulators;  /**< Object node input manipulators. <KzuInputManipulator> */
    struct KzcDynamicArray* triggers; /**< Object node triggers. <KzuObjectNodeTriggerEntry> */
    struct KzcDynamicArray* bindings; /**< Object node bindings. <KzuObjectNodeBindingEntry> */
    kzU32 changeFlags; /**< A collection of system defined (layout, render) and user defined change flags. */
    kzU32 childChangeFlags; /**< A collection of system defined (layout, render) and user defined change flags for any children. */
    struct KzuObjectNodeLayoutData* uiData; /**< UI data for the object. */
    kzBool initialized; /**< Is object node initialized. */
    struct KzcMatrix4x4 finalTransformation; /**< Cached transformation of the object. */

    struct KzuAnimationPlayer* animationPlayer; /**< Object specific animation player. */
    struct KzuInputManipulator* clickManipulator; /**< Click manipulator that is added in onAttached if enable click property is set. */
};

/** Initializes an object node. Should be called from Initialize function of a child class before anything else is done. */
kzsError kzuObjectNodeInitialize_protected(struct KzuObjectNode* objectNode);

/** Uninitializes an object node. Should be called from Uninitialize function of a child class after everything else is done. */
kzsError kzuObjectNodeUninitialize_protected(struct KzuObjectNode* objectNode);

/** Returns KZ_TRUE if object node already has been initialized. */
kzBool kzuObjectNodeIsInitialized_protected(const struct KzuObjectNode* objectNode);

/** Called when an object node becomes attached. */
kzsError kzuObjectNodeOnAttached_protected(struct KzuObjectNode* objectNode);

/** Called when an object node becomes detached. */
kzsError kzuObjectNodeOnDetached_protected(struct KzuObjectNode* objectNode);

/** Attaches the given state manager to an object node. */
kzsError kzuObjectNodeAttachStateManager_private(struct KzuObjectNode* objectNode, struct KzuStateManager* stateManager);

/** Detaches the state manager of an object node. */
kzsError kzuObjectNodeDetachStateManager_private(struct KzuObjectNode* objectNode);

/** Default implementation for property change callback. */
kzsError kzuObjectNodeOnPropertyChanged_protected(struct KzuObjectNode* objectNode, const struct KzuPropertyType* propertyType, enum KzuPropertyNotificationReason reason);

/** Default implementation for bounding volume getter. */
kzsError kzuObjectNodeGetBoundingVolume_protected(const struct KzuObjectNode* objectNode, struct KzuBoundingVolume** out_boundingVolume);

/** Default render function. Does nothing. */
kzsError kzuObjectNodeRender_protected(const struct KzuObjectNode* objectNode, struct KzuRenderer* renderer,
                                       const struct KzuTransformedObjectNode* transformedObjectNode, struct KzcMatrix4x4* worldTransformation);
/** Default copy function implementation. */
kzsError kzuObjectNodeCopy_protected(const struct KzuObjectNode* sourceObjectNode, struct KzuObjectNode* targetObjectNode);


/** Creates a new object node. */
kzsError kzuObjectNodeCreate_protected(const struct KzcMemoryManager* memoryManager, struct KzuUIDomain* uiDomain, 
                                       const struct KzuObjectNodeClass* objectNodeClass, kzString name, struct KzuObjectNode* objectNode);

/** Copy bindings from one object node to another. */
kzsError kzuObjectNodeCopyBindings_private(const struct KzcMemoryManager* memoryManager, const struct KzuObjectNode* sourceObjectNode,
                                           struct KzuObjectNode* targetObjectNode);
/** Copy triggers from one object node to another. */
kzsError kzuObjectNodeCopyTriggers_private(const struct KzcMemoryManager* memoryManager, const struct KzuObjectNode* sourceObjectNode,
                                           struct KzuObjectNode* targetObjectNode);
/** Copy resources from one object node to another. */
kzsError kzuObjectNodeCopyResources_private(const struct KzuObjectNode* sourceObjectNode, struct KzuObjectNode* targetObjectNode, kzBool preserveTarget);

/** Applies a style to an object node. Returns a style entry that is used to unapply the style. */
kzsError kzuObjectNodeApplyStyle(struct KzuObjectNode* objectNode, struct KzuStyle* style, struct KzuObjectNodeAppliedStyleEntry** out_appliedStyleEntry);
/** Unapplies a style from an object node. */
kzsError kzuObjectNodeUnapplyStyle(const struct KzuObjectNode* objectNode, struct KzuObjectNodeAppliedStyleEntry* appliedStyleEntry);
/** Apply all styles for an object node. */
kzsError kzuObjectNodeApplyStyles(struct KzuObjectNode* objectNode);
/** Unapplies and removes all applied styles. */
kzsError kzuObjectNodeUnapplyStyles(const struct KzuObjectNode* objectNode);
/** Applies styles recursively. */
kzsError kzuObjectNodeApplyStylesRecursive(struct KzuObjectNode* objectNode);
/** Unapplies styles recursively. */
kzsError kzuObjectNodeUnapplyStylesRecursive(const struct KzuObjectNode* objectNode);

/** Loads object node from binary. */
kzsError kzuObjectNodeLoadFromKZB_protected(struct KzuObjectNode* objectNode, struct KzcInputStream* inputStream,
                                            const struct KzuBinaryFileInfo* file);
/** Loads a trigger from stream. */
kzsError kzuObjectNodeLoadTrigger_protected(struct KzcInputStream* inputStream, struct KzuUIDomain* uiDomain,
                                            const struct KzuBinaryFileInfo* file, struct KzuTrigger** out_trigger);
/** Loads a binding from stream. */
kzsError kzuObjectNodeLoadBinding_protected(struct KzcInputStream* inputStream, struct KzuUIDomain* uiDomain,
                                            const struct KzuBinaryFileInfo* file, struct KzuBindingRule** out_bindingRule);

/** Attaches an object node and its children recursively. */
kzsError kzuObjectNodeAttachRecursive_protected(struct KzuObjectNode* objectNode);
/** Detaches an object node and its children recursively. */
kzsError kzuObjectNodeDetachRecursive_protected(struct KzuObjectNode* objectNode);


/** Sets a new UI domain for object node. */
kzsError kzuObjectNodeSetUiDomain_protected(struct KzuObjectNode* objectNode, struct KzuUIDomain* uiDomain);

/** Class type for object nodes. */
extern const struct KzuObjectNodeClass KZU_OBJECT_NODE_CLASS;


KZ_HEADER_END


#endif
