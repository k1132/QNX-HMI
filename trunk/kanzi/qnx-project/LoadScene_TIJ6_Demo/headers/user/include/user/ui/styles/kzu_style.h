/**
* \file
* Style.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_STYLE_H
#define KZU_STYLE_H


#include <user/properties/kzu_property_manager.h>
#include <user/resource/kzu_resource_common.h>
#include <user/scene_graph/kzu_object_common.h>

#include <core/util/collection/kzc_dynamic_array.h>
#include <core/util/collection/kzc_hash_map.h>

#include <system/kzs_types.h>
#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations. */
struct KzuPropertyManager;
struct KzuPropertyType;
struct KzuObjectNode;
struct KzuResourceManager;
struct KzuBinaryFileInfo;
struct KzcInputStream;
struct KzcDynamicArray;
struct KzcHashMap;
struct KzcMemoryManager;
struct KzuObjectNodeAppliedStyleEntry;
struct KzuUIDomain;


/**
 * \struct KzuStyle
 * Style applying properties, triggers and bindings to nodes.
 */
struct KzuStyle;


/** Resource type identifier for style */
extern const KzuResourceType KZU_RESOURCE_TYPE_STYLE;


/** Create an empty style. */
kzsError kzuStyleCreateEmpty(struct KzuResourceManager* resourceManager, struct KzuPropertyManager* propertyManager,
                             kzString name, struct KzuStyle** out_style);

/** Create a style. */
kzsError kzuStyleCreate(struct KzuResourceManager* resourceManager, struct KzuPropertyManager* propertyManager,
                        kzString name, struct KzuStyle* parentStyle, KzuObjectType objectType,
                        const void* properties, const struct KzcDynamicArray* bindings,
                        const struct KzcDynamicArray* triggers, struct KzuStyle** out_style);

/** Copy a style. */
kzsError kzuStyleCopy(struct KzuResourceManager* resourceManager, const struct KzuStyle* sourceStyle, struct KzuStyle** out_style);

/** Load a style from kzb. */
kzsError kzuStyleLoadFromKZB(struct KzuStyle* style, struct KzcInputStream* inputStream, const struct KzuBinaryFileInfo* file);


/** Get the property manager of a style. */
struct KzuPropertyManager* kzuStyleGetPropertyManager(const struct KzuStyle* style);

/** Get the properties of a style. */
struct KzcHashMapIterator kzuStyleGetProperties(const struct KzuStyle* style);
/** Get value source for a property type. */
void* kzuStyleGetValueSource(const struct KzuStyle* style, const struct KzuPropertyType* propertyType);

/** Apply a style. */
kzsError kzuStyleApply(struct KzuObjectNodeAppliedStyleEntry* appliedStyleEntry, struct KzuObjectNode* objectNode);
/** Unapply a style. */
kzsError kzuStyleUnapply(const struct KzuObjectNodeAppliedStyleEntry* appliedStyleEntry, const struct KzuObjectNode* objectNode);
/** Apply all styles to an object node. */
kzsError kzuStyleApplyAll(struct KzuObjectNode* applyObjectNode);

/** Converts style to resource. */
struct KzuResource* kzuStyleToResource(const struct KzuStyle* style);
/** Converts style from resource. */
struct KzuStyle* kzuStyleFromResource(const struct KzuResource* resource);
/** Casts style from resource, KZ_NULL if invalid type. */
struct KzuStyle* kzuStyleCastFromResource(const struct KzuResource* resource);
/** Returns if given resource is style. */
kzBool kzuResourceIsStyle(const struct KzuResource* resource);

/** Gets bindings of style. */
struct KzcDynamicArrayIterator kzuStyleGetBindings(const struct KzuStyle* style);
/** Gets triggers of style. */
struct KzcDynamicArrayIterator kzuStyleGetTriggers(const struct KzuStyle* style);

/** Set style properties precedence. */
void kzuStyleSetPrecedence(struct KzuStyle* style, enum KzuPropertyValuePrecedence precedence);

/** Set UI domain to style. */
void kzuStyleSetUIDomain(struct KzuStyle* style, const struct KzuUIDomain* uiDomain);


KZ_HEADER_END


#endif
