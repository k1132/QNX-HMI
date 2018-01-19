/**
 * \file
 * Application framework events.
 * 
 * Copyright 2008-2014 by Rightware. All rights reserved.
 */
#ifndef KZA_APPLICATION_EVENTS_H
#define KZA_APPLICATION_EVENTS_H


#include <system/kzs_types.h>
#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations. */
struct KzuMessage;


/** Message handler for message dispatcher. */
kzsError kzaApplicationHandleSetBooleanProperty(const struct KzuMessage* message, void* userData);

KZ_HEADER_END


#endif
