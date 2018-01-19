/**
* \file
* Heads up display for displaying debug information.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_HUD_H
#define KZU_HUD_H


#include <system/debug/kzs_error.h>
#include <system/kzs_types.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


#define KZU_HUD_RENDER_FLAG_FPS (1 << 0) /**< HUD render flag for displaying FPS number. */
#define KZU_HUD_RENDER_FLAG_BATCH_COUNT (1 << 1) /**< HUD render flag for displaying number of batches. */
#define KZU_HUD_RENDER_FLAG_TRIANGLE_COUNT (1 << 2) /**< HUD render flag for displaying number of triangles. */
#define KZU_HUD_RENDER_FLAG_TEXTURE_SWITCHES (1 << 3) /**< HUD render flag for displaying number of texture switches. */
#define KZU_HUD_RENDER_FLAG_SHADER_SWITCHES (1 << 4) /**< HUD render flag for displaying number of shader switches. */
#define KZU_HUD_RENDER_FLAG_VIEW_CAMERA (1 << 5) /**< HUD render flag for displaying the name of the view camera. */
#define KZU_HUD_RENDER_FLAG_ANIMATION_TIME (1 << 6) /**< HUD render flag for displaying time spent for animations. */
#define KZU_HUD_RENDER_FLAG_MEMORY_CONSUMPTION (1 << 7) /**< HUD render flag for displaying memory consumption. */
#define KZU_HUD_RENDER_FLAG_FRAME_BUFFER_SWITCHES (1 << 8) /**< HUD render flag for displaying FBO switches. */
#define KZU_HUD_RENDER_FLAG_BUFFER_SWITCHES (1 << 9) /**< HUD render flag for displaying buffer (VBO + IBO) switches. */
#define KZU_HUD_RENDER_FLAG_HEAVYWEIGHT_CALLS (1 << 10) /**< HUD render flag for displaying heavyweight call count (buffer[sub]data, tex[sub]image2d). */


/* Forward declarations */
struct KzcMemoryManager;
struct KzcRenderer;
struct KzcVector2;
struct KzuAnimationPlayer;
struct KzuBitmapFontSystem;
struct KzuFont;
struct KzuRenderer;
struct KzuUIDomain;
struct KzuResourceManager;
struct KzuTextLayouter;


/**
* \struct KzuHud
* Structure to hold heads up display content.
*/
struct KzuHud;


/** Create a new hud. */
kzsError kzuHudCreate(const struct KzcMemoryManager* memoryManager, struct KzuHud** out_hud);
/** Is HUD initialized, i.e. is font system set. */
kzBool kzuHudIsInitialized(const struct KzuHud* hud);
/** Initialize resources in hud. */
kzsError kzuHudCreateResources(struct KzuHud* hud, const struct KzuUIDomain* uiDomain, struct KzuBitmapFontSystem* fontSystem);
/** Delete a hud context. */
kzsError kzuHudDelete(struct KzuHud* hud);

/** Updates hud. Should be called once per rendered frame. */
kzsError kzuHudUpdate(struct KzuHud* hud, kzFloat fps, kzUint batchCount, kzUint triangleCount, kzUint textureSwitchCount, kzUint frameBufferSwitchCount,
                        kzUint shaderSwitchCount, kzUint uniformsSent, kzUint bufferSwitchCount, kzUint heavyweightCallCount, kzString viewCameraPath, kzFloat animationPlayerTime,
                        kzUint resourceVramConsumption, kzUint resourceRamConsumption);
/** Adds custom text line to HUD. Buffer of custom text lines is cleared after each kzuHudUpdate. */
kzsError kzuHudAddCustomTextLine(struct KzuHud* hud, kzString customString);

/** Render the hud. */
kzsError kzuHudRenderDebugInfo(const struct KzuHud* hud, struct KzuRenderer* renderer, const struct KzcMemoryManager* quickMemoryManager, const struct KzcVector2* offset, const struct KzcVector2* limits,
                               kzBool backgroundToDynamicText);

/** Render the log. */
kzsError kzuHudRenderLog(const struct KzuHud* hud, const struct KzuRenderer* renderer, 
                        const struct KzcMemoryManager* quickMemoryManager, const struct KzcVector2* offset, const struct KzcVector2* limits);

/** Draws single text line. */
kzsError kzuHudDrawText(struct KzuFont* font, const struct KzuTextLayouter* textLayouter, const struct KzcMemoryManager* memoryManager,
                        struct KzcRenderer* renderer, kzString text, kzFloat x, kzFloat y, kzBool isOutlinedShadow, kzFloat* out_ySpace);

/** Render the animation player info. */
kzsError kzuHudRenderAnimationPlayerInfo(const struct KzuHud* hud, struct KzuRenderer* renderer, 
                                         const struct KzcMemoryManager* quickMemoryManager, const struct KzcVector2* offset, const struct KzcVector2* limits,
                                         const struct KzuAnimationPlayer* rootAnimationPlayer);

/** Sets log visualization enabled in hud. */
void kzuHudSetLogVisualizationEnabled(struct KzuHud* hud, kzBool enabled);

/** Returns if log visualization is enabled on HUD. */
kzBool kzuHudIsLogVisualizationEnabled(const struct KzuHud* hud);

/** Sets render flags for hud. */
void kzuHudSetRenderFlags(struct KzuHud* hud, kzU32 flags);

/** Gets the default font from hud. */
struct KzuFont* kzuHudGetFont(const struct KzuHud* hud);


KZ_HEADER_END


#endif
