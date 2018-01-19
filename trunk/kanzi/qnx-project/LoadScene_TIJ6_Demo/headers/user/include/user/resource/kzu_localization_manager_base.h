/**
 * \file
 * Localization manager base definitions.
 * 
 * Copyright 2008-2014 by Rightware. All rights reserved.
 */
#ifndef KZU_LOCALIZATION_MANAGER_BASE_H
#define KZU_LOCALIZATION_MANAGER_BASE_H


#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/**
 * Reasons why a localization update callback was called. Note that the implementation may combine multiple updates
 * in localization tables into a single update callback. In this case only ACTIVE_TABLE_UPDATED without
 * INACTIVE_TABLE_UPDATED callback can be triggered if both the active and one or more inactive tables have been modified.
 *
 * \see KzuLocalizationUpdatedCallback
 * \see kzuLocalizationManagerAddListener
 */
enum KzuLocalizationUpdateReason
{
    KZU_LOCALIZATION_UPDATE_REASON_LOCALE_CHANGED, /**< The active locale has been changed. */
    KZU_LOCALIZATION_UPDATE_REASON_ACTIVE_TABLE_UPDATED, /**< Active localization table has been changed. */
    KZU_LOCALIZATION_UPDATE_REASON_INACTIVE_TABLE_UPDATED /**< Some localization table other than the active one has been changed. */
};


KZ_HEADER_END


#endif
