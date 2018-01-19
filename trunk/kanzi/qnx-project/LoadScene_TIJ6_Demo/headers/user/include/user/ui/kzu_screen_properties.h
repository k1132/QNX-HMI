/**
 * \file
 * Property accessors for KzuScreen.
 * 
 * Copyright 2008-2014 by Rightware. All rights reserved.
 */
#ifndef KZU_SCREEN_PROPERTIES_H
#define KZU_SCREEN_PROPERTIES_H


#include "kzu_screen.h"

#include <system/kzs_types.h>
#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations */
struct KzuScreen;


/** Gets the value of property WindowMetricsType in screen. */
enum KzuWindowMetricsType kzuScreenGetWindowMetricsType(const struct KzuScreen* screen);
/** Sets the value of property WindowMetricsType in screen. */
kzsError kzuScreenSetWindowMetricsType(const struct KzuScreen* screen, enum KzuWindowMetricsType value);

/** Gets the value of property WindowWidth in screen. */
kzFloat kzuScreenGetWindowWidth(const struct KzuScreen* screen);
/** Sets the value of property WindowWidth in screen. */
kzsError kzuScreenSetWindowWidth(const struct KzuScreen* screen, kzFloat value);

/** Gets the value of property WindowHeight in screen. */
kzFloat kzuScreenGetWindowHeight(const struct KzuScreen* screen);
/** Sets the value of property WindowHeight in screen. */
kzsError kzuScreenSetWindowHeight(const struct KzuScreen* screen, kzFloat value);

/** Gets the value of property ScreenOrientation in screen. */
enum KzsWindowOrientation kzuScreenGetScreenOrientation(const struct KzuScreen* screen);
/** Sets the value of property ScreenOrientation in screen. */
kzsError kzuScreenSetScreenOrientation(const struct KzuScreen* screen, enum KzsWindowOrientation value);

/** Gets the value of property LayerRenderOnDemand in screen. */
kzBool kzuScreenIsLayerRenderOnDemand(const struct KzuScreen* screen);
/** Sets the value of property LayerRenderOnDemand in screen. */
kzsError kzuScreenSetLayerRenderOnDemand(const struct KzuScreen* screen, kzBool value);


KZ_HEADER_END


#endif
