/**
* \file
* UI Domain.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_UI_DOMAIN_H
#define KZU_UI_DOMAIN_H


#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations. */
struct KzuBinaryDirectory;
struct KzuBinaryFileInfo;
struct KzuFactory;
struct KzuLocalizationManager;
struct KzuMessageDispatcher;
struct KzuPropertyManager;
struct KzuResourceManager;
struct KzuTaskScheduler;
struct KzuTextRenderer;
struct KzcMemoryManager;


/**
 * \struct KzuUIDomain
 * Metadata.
 */
struct KzuUIDomain;


/** Creates a UIDomain object. */
kzsError kzuUIDomainCreate(const struct KzcMemoryManager* memoryManager, struct KzuPropertyManager* propertyManager,
                           struct KzuResourceManager* resourceManager, struct KzuMessageDispatcher* messageDispatcher,
                           struct KzuTaskScheduler* taskScheduler, struct KzuTextRenderer* textRenderer,
                           struct KzuFactory* factory, struct KzuUIDomain** out_uiDomain);

/** Deletes a UIDomain object. */
kzsError kzuUIDomainDelete(struct KzuUIDomain* uiDomain);


/** Sets the Localization manager for UIDomain. */
kzsError kzuUIDomainSetLocalizationManager(struct KzuUIDomain* uiDomain, struct KzuLocalizationManager* localizationManager);


/** Gets the property manager from UIDomain. */
struct KzuPropertyManager* kzuUIDomainGetPropertyManager(const struct KzuUIDomain* uiDomain);
/** Gets the resource manager from UIDomain. */
struct KzuResourceManager* kzuUIDomainGetResourceManager(const struct KzuUIDomain* uiDomain);
/** Gets the Localization manager from UIDomain. */
struct KzuLocalizationManager* kzuUIDomainGetLocalizationManager(const struct KzuUIDomain* uiDomain);
/** Gets the message dispatcher from UIDomain. */
struct KzuMessageDispatcher* kzuUIDomainGetMessageDispatcher(const struct KzuUIDomain* uiDomain);
/** Gets the task scheduler from UIDomain. */
struct KzuTaskScheduler* kzuUIDomainGetTaskScheduler(const struct KzuUIDomain* uiDomain);
/** Gets the text renderer from UIDomain. */
struct KzuTextRenderer* kzuUIDomainGetTextRenderer(const struct KzuUIDomain* uiDomain);
/** Gets the factory from UIDomain. */
struct KzuFactory* kzuUIDomainGetFactory(const struct KzuUIDomain* uiDomain);

/** Loads settings from directory. */
kzsError kzuUIDomainLoadSettingsFromDirectory(const struct KzuUIDomain* uiDomain, const struct KzuBinaryDirectory* directory);
/** Loads settings from file. */
kzsException kzuUIDomainLoadSettingsFromFile(const struct KzuUIDomain* uiDomain, const struct KzuBinaryFileInfo* file);


KZ_HEADER_END


#endif
