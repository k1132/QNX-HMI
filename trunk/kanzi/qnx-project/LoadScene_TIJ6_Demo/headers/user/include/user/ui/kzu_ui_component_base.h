/**
* \file
* UI component node private members.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/

#ifndef KZU_UI_COMPONENT_BASE_H
#define KZU_UI_COMPONENT_BASE_H


#include <user/scene_graph/kzu_object_base.h>

#include <system/kzs_types.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations. */
struct KzuUiComponentNode;


/** Class definition for UI components. */
struct KzuUiComponentNodeClass
{
    /** Inherited from ObjectNode. */
    struct KzuObjectNodeClass objectNodeClass;

    /** Measures desired size of the UI component. */
    kzsError (*kzuUiComponentNodeMeasure)(struct KzuUiComponentNode* componentNode, struct KzcVector3* out_coreDesiredSize);

    /** Arranges UI component to space reserved for it. */
    kzsError (*kzuUiComponentNodeArrange)(struct KzuUiComponentNode* componentNode);

    /** Validates UI component for rendering. Called when flags affecting render are set on a component. This function is not used currently but is reserved to reduce API incompatibilities. */
    kzsError (*kzuUiComponentNodeValidateRender)(struct KzuUiComponentNode* componentNode);
};


struct KzuUiComponentNode
{
    struct KzuObjectNode objectNode; /**< Inherited from object node that contains transformation and child data. */
};


/** Creates a UI component. */
kzsError kzuUiComponentNodeCreate_protected(const struct KzcMemoryManager* memoryManager, kzString name, struct KzuUIDomain* uiDomain,
                                          const struct KzuUiComponentNodeClass* componentNodeClass, 
                                          struct KzuUiComponentNode* componentNode);

/** Initializes a UI component. */
kzsError kzuUiComponentNodeInitialize_protected(struct KzuObjectNode* objectNode);
/** Uninitializes a UI component. */
kzsError kzuUiComponentNodeUninitialize_protected(struct KzuObjectNode* objectNode);
/** Implementation of UI component property change callback. */
kzsError kzuUiComponentNodeOnPropertyChanged_protected(struct KzuObjectNode* objectNode, const struct KzuPropertyType* propertyType, enum KzuPropertyNotificationReason reason);
/** Default measure implementation. */
kzsError kzuUiComponentNodeMeasure_protected(struct KzuUiComponentNode* componentNode, struct KzcVector3* out_coreDesiredSize);
/** Default implementation of measure for a layout that accommodates all children at its center. */
kzsError kzuUiComponentNodeCenteredMeasure_protected(struct KzuUiComponentNode* componentNode, struct KzcVector3* out_coreDesiredSize);
/** Default implementation of arrange for a layout that accommodates all children at its center. */
kzsError kzuUiComponentNodeCenteredArrange_protected(struct KzuUiComponentNode* componentNode);
/** Default arrange implementation. */
kzsError kzuUiComponentNodeArrange_protected(struct KzuUiComponentNode* componentNode);
/** Default validate render implementation. */
kzsError kzuUiComponentNodeValidateRender_protected(struct KzuUiComponentNode* componentNode);
/** Default component copy implementation. */
kzsError kzuUiComponentNodeCopy_protected(const struct KzuObjectNode* sourceObjectNode, struct KzuObjectNode* targetObjectNode);
/** Default render implementation. */
kzsError kzuUiComponentNodeRender_protected(const struct KzuObjectNode* objectNode, struct KzuRenderer* renderer,
                                            const struct KzuTransformedObjectNode* transformedObjectNode, 
                                            struct KzcMatrix4x4* worldTransformation);
/** Default bounding volume getter implementation. */
kzsError kzuUiComponentNodeGetBoundingVolume_protected(const struct KzuObjectNode* objectNode, struct KzuBoundingVolume** out_boundingVolume);

/** Default implementation for loading UI component node from KZB. */
kzsError kzuUiComponentNodeLoadFromKZB_protected(struct KzuObjectNode* objectNode, struct KzcInputStream* inputStream,
                                                 const struct KzuBinaryFileInfo* file);


/** User interface component's object node class. */
extern const struct KzuObjectNodeClass KZU_UI_COMPONENT_NODE_CLASS;


KZ_HEADER_END


#endif
