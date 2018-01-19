/**
 * \file
 * Application framework windows handling.
 * 
 * Copyright 2008-2014 by Rightware. All rights reserved.
 */
#ifndef KZA_WINDOW_H
#define KZA_WINDOW_H


#include <system/kzs_types.h>
#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations. */
struct KzaApplication;
struct KzuWindow;
struct KzsSurface;
struct KzsWindowProperties;
struct KzsSurfaceConfiguration;


/** Create a new application windows. */
kzsError kzaWindowCreate(struct KzaApplication* application, struct KzsWindowProperties* windowProperties,
                         const struct KzsSurfaceConfiguration* configuration, struct KzuWindow** out_window);


KZ_HEADER_END


#endif
