/**
* \file
* Configuration for drawable surfaces and windows.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZS_SURFACE_CONFIGURATION_H
#define KZS_SURFACE_CONFIGURATION_H


#include <system/debug/kzs_error.h>
#include <system/display/kzs_surface.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations. */
struct KzsDesktop;
struct KzsSurfaceConfigurationNative;

/**
 * \struct KzsSurfaceConfiguration
 * Configuration data for surfaces and windows.
 */
struct KzsSurfaceConfiguration;

/** Graphics languages for a surface. */
enum KzsSurfaceType
{
    KZS_SURFACE_TYPE_DEFAULT,      /**< Surface rendering API is unspecified. */
    KZS_SURFACE_TYPE_VG_ONLY,      /**< Surface is target for OpenVG rendering. */
    KZS_SURFACE_TYPE_ES2_ONLY,     /**< Surface is target for OpenGLES 2.0 rendering. */
    KZS_SURFACE_TYPE_GL_ONLY,      /**< Surface is target for OpenGL rendering. */
    KZS_SURFACE_TYPE_VG_AND_ES2    /**< Reserved for future use. */
};


/** Properties for a surface. */
struct KzsSurfaceProperties
{
    enum KzsSurfaceType type;  /**< Graphics language for rendering on this surface. */

    kzInt bitsColorR;          /**< Size of red color channel in bits. Set to KZS_SURFACE_PROPERTY_DONT_CARE for automatic selection. */
    kzInt bitsColorG;          /**< Size of green color channel in bits. Set to KZS_SURFACE_PROPERTY_DONT_CARE for automatic selection. */
    kzInt bitsColorB;          /**< Size of blue color channel in bits. Set to KZS_SURFACE_PROPERTY_DONT_CARE for automatic selection. */
    kzInt bitsAlpha;           /**< Size of alpha channel in bits. Set to KZS_SURFACE_PROPERTY_DONT_CARE for automatic selection.*/

    kzInt bitsStencil;         /**< Size of stencil buffer in bits. Set to KZS_SURFACE_PROPERTY_DONT_CARE for automatic selection. */
    kzInt bitsDepthBuffer;     /**< Size of depth buffer in bits. Set to KZS_SURFACE_PROPERTY_DONT_CARE for automatic selection. */

    kzInt antiAliasing;        /**< Number of anti-aliasing samples used. Use 0 to turn AA off. Set to KZS_SURFACE_PROPERTY_DONT_CARE for automatic selection.*/
    kzInt swapBehaviorCopy;   /**< During the swap buffer, are the buffers swapped (switched) or copied, 1 for copy, 0 for swap, KZS_SURFACE_PROPERTY_DONT_CARE for automatic selection. */
};


/** Gets default properties for surface. */
struct KzsSurfaceProperties kzsSurfaceGetDefaultProperties(void);

/** Logs the surface properties. */
kzsError kzsSurfacePropertiesLog(const struct KzsSurfaceProperties* properties, kzString prefix, kzUint logLevel);

/** Creates a configuration for surfaces for a windows. */
kzsError kzsSurfaceConfigurationCreate(const struct KzsDesktop* desktop, const struct KzsSurfaceProperties* surfaceProperties,
                                       struct KzsSurfaceConfiguration** out_configuration);

/** Deletes a surface configuration and frees all memory allocated for it. */
kzsError kzsSurfaceConfigurationDelete(struct KzsSurfaceConfiguration* configuration);

/** Gets native portion of a surface configuration. */
const struct KzsSurfaceConfigurationNative* kzsSurfaceConfigurationGetNative(const struct KzsSurfaceConfiguration* configuration);

/** Creates a native surface configuration. */
kzsError kzsSurfaceConfigurationNativeCreate(const struct KzsDesktop* desktop, const struct KzsSurfaceProperties* surfaceProperties,
                                             struct KzsSurfaceConfigurationNative** out_configurationNative);

/** Deletes a native surface configuration and frees all memory allocated for it. */
kzsError kzsSurfaceConfigurationNativeDelete(struct KzsSurfaceConfigurationNative* configurationNative);

/* Lists native surface configurations for specifying image attributes, used in kzsSurfaceNativeCreateImage. */

#define KZS_SURFACE_TARGET_NATIVE_ANDROID 0x3140 /**< Native android surface target. */
#define KZS_SURFACE_TARGET_NATIVE_PIXMAP 0x30B0 /**< Native pixmap target. */
#define KZS_SURFACE_TARGET_TEXTURE_2D 0x30B1 /**< Texture2D target. */

#define KZS_SURFACE_ATTRIBUTE_WIDTH 0x3057 /**< Width attribute. */
#define KZS_SURFACE_ATTRIBUTE_HEIGHT 0x3056 /**< Height attribute. */
#define KZS_SURFACE_ATTRIBUTE_MATCH_FORMAT 0x3043 /**< Match format (color format) attribute. */
#define KZS_SURFACE_ATTRIBUTE_IMAGE_PRESERVED 0x30D2 /**< Is image preserved over frames. */
#define KZS_SURFACE_ATTRIBUTE_NONE 0x3038 /**< Ends the array specification. */

#define KZS_SURFACE_ATTRIBUTE_FORMAT_RGBA_8888 0x30C3 /**< RGBA8888 format. */
#define KZS_SURFACE_ATTRIBUTE_FORMAT_RGB_565 0x30C1 /**< RGB565 format. */

#define KZS_SURFACE_ATTRIBUTE_TEXTURE_LEVEL 0x30BC /**< Texture level. */


KZ_HEADER_END


#endif
