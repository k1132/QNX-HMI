/**
* \file
* Specifies a composer structure, which is set of render passes that are processed in order.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_COMPOSER_H
#define KZU_COMPOSER_H


#include <user/resource/kzu_resource_common.h>
#include <core/util/collection/kzc_dynamic_array.h>

#include <system/kzs_types.h>
#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations */
struct KzcDynamicArray;
struct KzcInputStream;
struct KzcMemoryManager;
struct KzuBinaryFileInfo;
struct KzuFactory;
struct KzuUIDomain;
struct KzuPropertyManager;
struct KzuPropertyType;
struct KzuRenderer;
struct KzuRenderContextStack;
struct KzuRenderTarget;
struct KzuResource;
struct KzuResourceManager;
struct KzuTransformedScene;


/** 
 * \struct KzuComposer
 * Composer combines set of render passes which are rendered sequentially.
 */
struct KzuComposer;


/** Resource type identifier for composer */
extern const KzuResourceType KZU_RESOURCE_TYPE_COMPOSER;


/** Deletes a composer. */
kzsError kzuComposerDelete(const struct KzuComposer* composer);

/** Loads composer from KZB. */
kzsError kzuComposerLoadFromKZB(const struct KzuComposer* composer, struct KzcInputStream* inputStream,
                                const struct KzuBinaryFileInfo* file);

/** Initializes a composer. */
kzsError kzuComposerInitialize(struct KzuComposer* composer);
/** Uninitializes a composer. */
kzsError kzuComposerUninitialize(struct KzuComposer* composer);
                                            
/** Returns composer's type */
KzuResourceType kzuComposerGetType(const struct KzuComposer* composer);

/** Get the property manager of a composer. */
struct KzuPropertyManager* kzuComposerGetPropertyManager(const struct KzuComposer* composer);

/** Adds a child to composer. */
kzsError kzuComposerAddChild(const struct KzuComposer* composer, const struct KzuComposer* childComposer);
/** Add child composer at given index in parent. */
kzsError kzuComposerAddChildAtIndex(const struct KzuComposer* composer, kzUint index, const struct KzuComposer* childComposer);
/** Removes a child from composer. */
kzsError kzuComposerRemoveChild(const struct KzuComposer* composer, const struct KzuComposer* childComposer);
/** Gets render passes from composer. */
struct KzcDynamicArrayIterator kzuComposerGetChildren(const struct KzuComposer* composer);
/** Removes all children from composer. */
kzsError kzuComposerRemoveAllChildren(const struct KzuComposer* composer);

/** Gets a child composer from composer at given index. If index is out of range KZ_NULL is returned. */
struct KzuComposer* kzuComposerGetChildComposer(const struct KzuComposer* composer, kzUint index);
/** Returns the amount of render passes in composer. */
kzUint kzuComposerGetChildCount(const struct KzuComposer* composer);

/** Applies a composer for rendering. */
kzsError kzuComposerApply(struct KzuComposer* composer, struct KzuRenderer* renderer, const struct KzuTransformedScene* transformedScene,
                          struct KzuRenderContextStack* renderContextStack);

/** Gets composer's name. */
kzMutableString kzuComposerGetName(const struct KzuComposer* composer);

/** Sets render target for composer. KZ_NULL for screen. */
kzsError kzuComposerSetRenderTarget(struct KzuComposer* composer, struct KzuRenderTarget* renderTarget);
/** Gets render target from composer, KZ_NULL for screen. */
struct KzuRenderTarget* kzuComposerGetRenderTarget(const struct KzuComposer* composer);

/** 
 * Sets property manager for composer.
 * Warning: This function is deprecated and will be removed in future release.
 */
void kzuComposerSetPropertyManager(struct KzuComposer* composer, struct KzuPropertyManager* propertyManager);


/** Converts composer to resource. */
struct KzuResource* kzuComposerToResource(const struct KzuComposer* composer);
/** Converts composer from resource. */
struct KzuComposer* kzuComposerFromResource(const struct KzuResource* resource);
/** Casts composer from resource, KZ_NULL if invalid type. */
struct KzuComposer* kzuComposerCastFromResource(const struct KzuResource* resource);


KZ_HEADER_END


#endif
