/**
* \file
* Binary base header.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_BINARY_COMMON_H
#define KZU_BINARY_COMMON_H


#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/** Path separator character in binary file. */
#define KZU_BINARY_PATH_SEPARATOR '/'


/** Type of a binary file. */
enum KzuBinaryFileType
{
    KZU_BINARY_FILE_TYPE_INVALID = -1, /**< Invalid file type. */

    /* Generic files: 0-9 */
    KZU_BINARY_FILE_TYPE_BINARY = 0,     /**< Arbitrary binary file. */
    KZU_BINARY_FILE_TYPE_UTF8_TEXT = 1,  /**< UTF8 text file. */
    KZU_BINARY_FILE_TYPE_ASCII_TEXT = 2, /**< ASCII text file. */
    KZU_BINARY_FILE_TYPE_SHORTCUT = 5,   /**< Shortcut. This file type is for internal functionality and should not be used when loading shortcuts. Use the actual object type that the shortcut refers instead. */

    /* Image files: 10-49 */
    KZU_BINARY_FILE_TYPE_IMAGE_PNG = 10,    /**< PNG image file. */
    KZU_BINARY_FILE_TYPE_IMAGE_JPEG = 11,   /**< JPEG image file. */
    KZU_BINARY_FILE_TYPE_IMAGE_RAW_1D = 12, /**< RAW 1D image file. */
    KZU_BINARY_FILE_TYPE_IMAGE_RAW_2D = 13, /**< RAW 2D image file. */
    KZU_BINARY_FILE_TYPE_IMAGE_RAW_3D = 14, /**< RAW 3D image file. */
    KZU_BINARY_FILE_TYPE_IMAGE_ETC = 15,    /**< ETC image file. */
    KZU_BINARY_FILE_TYPE_IMAGE_MIPMAP = 16, /**< Mipmap image file. */
    KZU_BINARY_FILE_TYPE_IMAGE_DXT = 17,    /**< DXT image file. */
    KZU_BINARY_FILE_TYPE_IMAGE_ATC = 18,    /**< ATC image file. */
    KZU_BINARY_FILE_TYPE_IMAGE_PVRTC = 19,    /**< PowerVR compressed texture file. */

    /* Scene graph: 100-999 */
    KZU_BINARY_FILE_TYPE_SCENE = 100, /**< Scene. */
    /* Object types: 110-499 */
    KZU_BINARY_FILE_TYPE_EMPTY_NODE = 110,        /**< Empty node. */
    KZU_BINARY_FILE_TYPE_MESH_NODE = 120,         /**< Mesh node. */
    KZU_BINARY_FILE_TYPE_CAMERA_NODE = 130,       /**< Camera node. */
    KZU_BINARY_FILE_TYPE_LIGHT_NODE = 140,        /**< Light node. */
    KZU_BINARY_FILE_TYPE_LOD_SELECTOR_NODE = 150, /**< LOD node. */
    KZU_BINARY_FILE_TYPE_UI_COMPONENT_NODE = 160, /**< UI component node. */
    KZU_BINARY_FILE_TYPE_INSTANCIATOR_NODE = 170, /**< Instanciator node. */
    KZU_BINARY_FILE_TYPE_LAYER = 180,             /**< Layer. */
    KZU_BINARY_FILE_TYPE_PREFAB_OBJECT_PLACEHOLDER = 190, /**< Prefab placeholder node. */
    KZU_BINARY_FILE_TYPE_PREFAB_LAYER_PLACEHOLDER = 191, /**< Prefab layer placeholder. */
    KZU_BINARY_FILE_TYPE_SCREEN = 200, /**< Screen node.. */

    /* Objects: 500-899 */
    KZU_BINARY_FILE_TYPE_MESH = 500,        /**< Arbitrary triangle mesh. */
    KZU_BINARY_FILE_TYPE_MESH_PLANE = 510,  /**< Plane mesh. */
    KZU_BINARY_FILE_TYPE_MESH_SPHERE = 511, /**< Sphere mesh. */
    KZU_BINARY_FILE_TYPE_MESH_BOX = 512,    /**< Box mesh. */

    /* Properties: 1000-1099 */
    KZU_BINARY_FILE_TYPE_PROPERTY_TYPE = 1000,  /**< Property type. */
    KZU_BINARY_FILE_TYPE_PROPERTY_GROUP = 1010, /**< Property group. */
    KZU_BINARY_FILE_TYPE_MESSAGE_TYPE = 1050,   /**< Message type. */
            
    /* Rendering: 1100-1199 */
    KZU_BINARY_FILE_TYPE_COMPOSER = 1100,      /**< Composer. */
    KZU_BINARY_FILE_TYPE_SHADER = 1120,        /**< Shader. */
    KZU_BINARY_FILE_TYPE_MATERIAL = 1121,      /**< Material. */
            
    /* Object sources: 1200-1299 */
    KZU_BINARY_FILE_TYPE_OBJECT_SOURCE = 1200, /**< Object source. */
            
    /* Animations: 1300-1399 */
    KZU_BINARY_FILE_TYPE_ANIMATION_DATA = 1300,    /**< Animation data. */
    KZU_BINARY_FILE_TYPE_ANIMATION_CLIP = 1301,    /**< Animation clip. */
    KZU_BINARY_FILE_TYPE_TIMELINE_SEQUENCE = 1302, /**< Timeline sequence. */
    KZU_BINARY_FILE_TYPE_ANIMATION_CHILD_CLIP = 1303,   /**< Animation child clip. */

    /* Other resources: 2000- */
    KZU_BINARY_FILE_TYPE_PROJECT = 2000,         /**< Project. */
    KZU_BINARY_FILE_TYPE_TEXTURE = 2020,         /**< Texture. */
    KZU_BINARY_FILE_TYPE_BITMAP_FONT = 2030,     /**< Bitmap font. */
    KZU_BINARY_FILE_TYPE_TRUETYPE_FONT = 2031,   /**< Truetype font. */
    KZU_BINARY_FILE_TYPE_SPLINE = 2050,          /**< Spline. */
    KZU_BINARY_FILE_TYPE_TRAJECTORY = 2060,      /**< Trajectory. */
    KZU_BINARY_FILE_TYPE_PREFAB_TEMPLATE = 2080, /**< Prefab template. */
    KZU_BINARY_FILE_TYPE_STYLE = 2090,           /**< Style. */
    KZU_BINARY_FILE_TYPE_STATE_MANAGER = 2100,   /**< State manager. */
    KZU_BINARY_FILE_TYPE_TEXT = 2110,            /**< Text. */
    KZU_BINARY_FILE_TYPE_LOCALIZATION_TABLE = 2120  /**< Localization table. */
};


/** Returns if a specified file type is a resource (KzuResource). */
kzBool kzuBinaryFileTypeIsResource(enum KzuBinaryFileType fileType);


KZ_HEADER_END


#endif
