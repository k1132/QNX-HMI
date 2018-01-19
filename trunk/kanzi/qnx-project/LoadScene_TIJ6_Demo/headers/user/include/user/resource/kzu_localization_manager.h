/**
 * \file
 * Localization manager.
 * 
 * Copyright 2008-2014 by Rightware. All rights reserved.
 */
#ifndef KZU_LOCALIZATION_MANAGER_H
#define KZU_LOCALIZATION_MANAGER_H


#include "kzu_localization_manager_base.h"

#include <system/debug/kzs_error.h>
#include <system/kzs_types.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations */
struct KzcDynamicArray;
struct KzcInputStream;
struct KzcMemoryManager;
struct KzuBinaryFileInfo;
struct KzuResource;


/**
 * \struct KzuLocalizationManager
 * Localization Manager is responsible for handling the concepts of default locale, active locale and
 * all available locales in the application. It also handles changing of the locale and provides listener
 * mechanism for notifications about changed locale. Localization Manager also provides access to the localization table.
 */
struct KzuLocalizationManager;


/** Callback function for receiving notifications when anything in the localization manager has changed. */
typedef kzsError (*KzuLocalizationUpdatedCallback)(struct KzuLocalizationManager* localizationManager, enum KzuLocalizationUpdateReason reason, void* userData);


/**
 * Creates a Localization manager. The initial active locale is set to KZ_NULL.
 * \param memoryManager Memory manager to use for creating the Localization manager.
 * \param out_localizationManager Newly created Localization manager, which the caller must delete with \ref kzuLocalizationManagerDelete().
 */
kzsError kzuLocalizationManagerCreate(const struct KzcMemoryManager* memoryManager, struct KzuLocalizationManager** out_localizationManager);

/** Deletes a Localization manager. */
kzsError kzuLocalizationManagerDelete(struct KzuLocalizationManager* localizationManager);


/**
 * Sets the active locale of the Localization manager.
 * \param activeLocale The new locale identifier. If KZ_NULL, all resource queries return the non-translated URL as if the resource has not been localized.
 */
kzsError kzuLocalizationManagerSetActiveLocale(struct KzuLocalizationManager* localizationManager, kzString activeLocale);

/**
 * Gets the active locale of the Localization manager.
 * \return The active locale of the Localization manager or KZ_NULL if no locale has been set.
 */
kzString kzuLocalizationManagerGetActiveLocale(const struct KzuLocalizationManager* localizationManager);

/**
 * Gets all available locales registered to the Localization manager.
 * \param out_availableLocales A list of names of kzString type. The returned dynamic array must be freed by the caller using \ref kzcDynamicArrayDelete().
 *                             The strings in the dynamic array are valid only as long as the locales exist in the localization manager.
 */
kzsError kzuLocalizationManagerGetAvailableLocales(const struct KzuLocalizationManager* localizationManager,
                                                   struct KzcDynamicArray** out_availableLocales);
/**
 * Checks if the given locale has been registered to the Localization manager.
 * \param locale The locale to check.
 */
kzBool kzuLocalizationManagerHasLocale(const struct KzuLocalizationManager* localizationManager, kzString locale);

/**
 * Checks if the given resource URL has been localized with the active locale.
 * \param resourceURL The queried resource URL.
 * \return KZ_TRUE if the resource URL has been localized with the active locale, KZ_FALSE otherwise.
 */
kzBool kzuLocalizationManagerIsResourceURLLocalized(const struct KzuLocalizationManager* localizationManager, kzString resourceURL);

/**
 * Checks if the given resource URL has been localized with the given locale.
 * \param locale The locale to use when querying if the resource URL has been localized.
 * \param resourceURL The queried resource URL.
 * \return KZ_TRUE if the resource URL has been localized with the given locale, KZ_FALSE otherwise.
 */
kzBool kzuLocalizationManagerIsResourceURLLocalizedForLocale(const struct KzuLocalizationManager* localizationManager,
                                                             kzString locale, kzString resourceURL);

/**
 * Returns a localized resource URL for the given resource URL using the currently active locale.
 * \param resourceURL The queried resource URL.
 * \return Returns a localized version of the resource URL or resourceURL as it is if it has not been localized with the active locale.
 */ 
kzString kzuLocalizationManagerGetLocalizedResourceURL(const struct KzuLocalizationManager* localizationManager, kzString resourceURL);

/**
 * Returns a localized resource URL for the given resource URL using the specified locale.
 * \param locale The locale to use when querying the localized version of the resource URL.
 * \param resourceURL The queried resource URL.
 * \return Returns a localized version of the resource URL or resourceURL as it is if it has not been localized with the given locale.
 */ 
kzString kzuLocalizationManagerGetLocalizedResourceURLForLocale(const struct KzuLocalizationManager* localizationManager,
                                                                kzString locale, kzString resourceURL);


/** Adds a listener to receive notifications about localization changes. */
kzsError kzuLocalizationManagerAddListener(struct KzuLocalizationManager* localizationManager,
                                           KzuLocalizationUpdatedCallback callback, void* userData);

/** Removes a listener receiving notifications about localization changes. */
kzsError kzuLocalizationManagerRemoveListener(struct KzuLocalizationManager* localizationManager,
                                              KzuLocalizationUpdatedCallback callback, void* userData);


/**
 * Adds a locale to the Localization manager. Initially no localization entries for that locale will be present in the localization table.
 * This function does nothing if the locale already exists in the Localization manager.
 * \param locale Locale to be added.
 */
kzsError kzuLocalizationManagerAddLocale(struct KzuLocalizationManager* localizationManager, kzString locale);

/**
 * Removes a locale from the Localization manager. All localization entries for that locale are also removed from the localization table.
 * \param locale Locale to be removed.
 * \return Throws an error if the given locale is not registered to the Localization manager.
 */
kzsError kzuLocalizationManagerRemoveLocale(struct KzuLocalizationManager* localizationManager, kzString locale);

/**
 * Adds a localized resource URL to the Localization manager localization table.
 * This function also registers the locale if it has not yet been registered to the Localization manager.
 * This function overwrites any previously added localization entry with the same locale and resourceURL.
 * Call ::kzuLocalizationUpdateTable or ::kzuLocalizationUpdateAllTables after all localized URLs have been added to make the changes effective.
 * \param locale Locale of the localized resource.
 * \param resourceURL Non-localized resource URL.
 * \param localizedResourceURL Localized resource URL.
 */
kzsError kzuLocalizationManagerAddLocalizedResourceURL(struct KzuLocalizationManager* localizationManager, kzString locale,
                                                       kzString resourceURL, kzString localizedResourceURL);

/**
 * Removes a localized resource URL from the Localization manager localization table.
 * Call ::kzuLocalizationUpdateTable or ::kzuLocalizationUpdateAllTables after all localized URLs have been removed to make the changes effective.
 * \param locale Locale of the localized resource.
 * \param resourceURL Non-localized resource URL.
 * \return Throws an error if the resource URL has not been localized for the given locale or the locale has not been registered to the Localization manager.
 */
kzsError kzuLocalizationManagerRemoveLocalizedResourceURL(struct KzuLocalizationManager* localizationManager, kzString locale,
                                                          kzString resourceURL);

/**
 * Updates the localization table for the given locale.
 * This function must be called after adding or removing localized resources to make the changes effective.
 */
kzsError kzuLocalizationManagerUpdateTable(struct KzuLocalizationManager* localizationManager, kzString locale);

/**
 * Updates the localization tables for all locales registered to the Localization manager.
 * This function must be called after adding or removing localized resources to make the changes effective.
 */
kzsError kzuLocalizationManagerUpdateAllTables(struct KzuLocalizationManager* localizationManager);


/** Loads a localization table from KZB to the Localization manager. This function is for internal use only. */
kzsError kzuLocalizationManagerLoadLocalizationTableFromKZB(struct KzuLocalizationManager* localizationManager,
                                                            struct KzcInputStream* inputStream, const struct KzuBinaryFileInfo* file);


KZ_HEADER_END


#endif
