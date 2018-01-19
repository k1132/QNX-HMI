/**
 * \file
 * Application framework splash screen.
 * 
 * Copyright 2008-2014 by Rightware. All rights reserved.
 */
#ifndef KZA_SPLASH_H
#define KZA_SPLASH_H


#include <system/kzs_types.h>
#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations */
struct KzcMemoryManager;
struct KzcRenderer;
struct KzuCanvas;
struct KzuResourceManager;


/**
 * \struct KzaSplashScreen
 * Splash screen structure.
 */
struct KzaSplashScreen;


/** Creates splash screen structure. */
kzsError kzaSplashScreenCreate(const struct KzcMemoryManager* memoryManager, const struct KzuResourceManager* resourceManager,
                               struct KzcRenderer* renderer, struct KzaSplashScreen** out_splashScreen);

/** Deletes splash screen structure. */
kzsError kzaSplashScreenDelete(struct KzaSplashScreen* splashScreen, struct KzcRenderer* renderer);

/** Renders splash screen. */
kzsError kzaSplashScreenRender(struct KzaSplashScreen* splashScreen, struct KzcRenderer* renderer, const struct KzuCanvas* canvas);

/** Clears splash screen remains, that might have been stayed from splash screen rendering. */
void kzaSplashScreenClear(struct KzaSplashScreen* splashScreen, struct KzcRenderer* renderer);


KZ_HEADER_END


#endif
