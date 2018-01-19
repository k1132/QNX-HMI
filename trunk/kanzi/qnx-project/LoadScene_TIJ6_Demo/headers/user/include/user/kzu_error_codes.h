/**
 * \file
 * User layer error codes.
 * 
 * Copyright 2008-2014 by Rightware. All rights reserved.
 */
#ifndef KZU_ERROR_CODES_H
#define KZU_ERROR_CODES_H


#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* User layer error codes have reserved range of 30000 - 39999 */

/* Binary loader error codes. (30100 - 30199) */
#define KZU_EXCEPTION_FILE_NOT_FOUND (kzsException)(-30101) /**< Given file was not found from a binary. */
#define KZU_ERROR_INVALID_BINARY_DATA (kzsError)30102 /**< Encountered invalid binary data while reading .kzb. */
#define KZU_ERROR_WRONG_BINARY_FILE_TYPE (kzsError)30103 /**< Wrong binary file type for given file. */
#define KZU_EXCEPTION_WRONG_BINARY_FILE_TYPE (kzsException)(-30103) /**< Wrong binary file type for given file. */
#define KZU_ERROR_INVALID_FILE_PATH (kzsError)30104 /**< Invalid file path. */
#define KZU_ERROR_INCOMPLETE_BINARY_FILE (kzsError)(30105) /**< Binary file is truncated and does not contain requested data. */
#define KZU_EXCEPTION_INCOMPLETE_BINARY_FILE (kzsException)(-30105) /**< Binary file is truncated and does not contain requested data. */

/* Scene specific error codes. (30200 - 30299) */
#define KZU_ERROR_INVALID_SCENE_DATA (kzsError)30201 /**< Scene contains invalid data. */
#define KZU_ERROR_INVALID_SCENE_GRAPH (kzsError)30202 /**< Scene graph contains invalid data. */
#define KZU_EXCEPTION_INVALID_ADD_CHILD_OPERATION (kzsException)(-30203) /**< Operation for adding child is invalid. */

/* Property specific error codes (30300 - 30399) */
#define KZU_ERROR_PROPERTY_NOT_FOUND (kzsError)30301 /**< Requested property was not found. */
#define KZU_ERROR_INVALID_PROPERTY (kzsError)30302 /**< Property was invalid. */
#define KZU_ERROR_PROPERTY_NOTIFICATION_HANDLER_NOT_FOUND (kzsError)30303 /**< Property notification handler not found. */
#define KZU_ERROR_WRONG_PROPERTY_DATA_TYPE (kzsError)30304 /**< Property data type was wrong in the context. */

/* Material specific error codes (30400 - 30499) */
#define KZU_ERROR_INVALID_SHADER_TYPE (kzsError)30401 /**< Invalid shader type. */

/* Mesh specific error codes (30500 - 30599) */
#define KZU_ERROR_MESH_TOO_MUCH_BONES (kzsError)30501 /**< Too much bones on mesh. */
#define KZU_ERROR_MESH_INVALID_VERTEX_ATTRIBUTE_MAPPING (kzsError)30502 /**< Invalid vertex attribute mapping for mesh. */

/* Project error codes (30600 - 30699) */
#define KZU_ERROR_PROJECT_LOADING_FAILED (kzsError)30601 /**< Failed to load project. */
#define KZU_ERROR_PROJECT_OBJECT_NOT_FOUND (kzsError)30602 /**< Requested object not found from project. */
#define KZU_ERROR_PROJECT_CORE_ASSET_NOT_FOUND (kzsError)30604 /**< Core asset was not found. */

/* Object node error codes (30700 - 30799) */
#define KZU_ERROR_OBJECT_NODE_CHILD_INFO_NOT_FOUND (kzsError)30701 /**< Failed to find child link type. */
#define KZU_ERROR_OBJECT_NODE_NOT_FOUND (kzsError)30702 /**< Object node not found. */
#define KZU_ERROR_OBJECT_NODE_RESOURCE_DICTIONARY_CONFLICT (kzsError)30703 /**< Conflict in resource dictionary. */
#define KZU_ERROR_OBJECT_NODE_RESOURCE_DICTIONARY_INVALID_ID (kzsError)30704 /**< Invalid resource id specified for the operation. */

/* LOD specific error codes (30800 - 30899) */
#define KZU_ERROR_INVALID_LOD_DATA (kzsError)30801 /**< Level Of Detail data is invalid. */

/* Layer specific error codes (30900 - 30999) */
#define KZU_ERROR_LAYER_NO_TEXTURE_PROVIDED (kzsError)30901 /**< No texture provided from a layer that was supposed to provide one. */

/* Factory specific error codes (31000-31099) */
#define KZU_EXCEPTION_FACTORY_OBJECT_TYPE_NOT_FOUND (kzsException)(-30900) /**< Object type not registered to factory. */

/* Scheduling error codes (31100 - 31199) */
#define KZU_ERROR_SCHEDULER_TASK_NOT_FOUND (kzsError)31101 /**< Task not found from scheduler. */

/* Message error codes (31200 - 31299) */

/* Composer specific error codes (31300 - 31399). */
#define KZU_ERROR_INVALID_COMPOSER_RENDER_TARGET_SIZE (kzsError)31201 /**< Invalid render target size for composer. */

/* Util / font error codes (31400 - 31499) */
#define KZU_ERROR_FONT_INVALID_DATA (kzsError)31401 /**< Font data is corrupt. */
#define KZU_ERROR_ITYPE_FAILED (kzsError)31402 /**< Error with iType. */
#define KZU_ERROR_FREETYPE_FAILED (kzsError)31403 /**< Error with FreeType. */
#define KZU_ERROR_FONT_SHADER_NOT_INITIALIZED (kzsError)31404 /**< Uninitialized font shader. */
#define KZU_ERROR_WTSHAPER_FAILED (kzsError)31405 /**< Error with WTShaper. */

/* License restriction error codes (31500 - 31599). */
#define KZU_ERROR_LICENSE_RESTRICTION (kzsError)31501 /**< Operation is not allowed with the given license type. */

/* Resource manager error codes (31600 - 31699). */
#define KZU_ERROR_RESOURCE_LOADING_NOT_SUPPORTED (kzsError)31601 /**< A resource cannot be loaded because that operation is not supported by the resource. */
#define KZU_ERROR_RESOURCE_NOT_LOADED (kzsError)31602 /**< An operation with a resource failed because the resource has not yet been loaded. */
#define KZU_ERROR_INVALID_RESOURCE_PATH (kzsError)31603 /**< Invalid resource path was given. */
#define KZU_ERROR_INVALID_RESOURCE_CAST (kzsError)31604 /**< Invalid resource cast. */
#define KZU_ERROR_UNBALANCED_ACQUIRE_RELEASE (kzsError)31605 /**< Unbalanced acquire-release count. */
#define KZU_ERROR_PROTOCOL_ALREAY_REGISTERED (kzsError)31606 /**< Trying to register a resource handler protocol, which has already been registered. */

/* List box specific error codes (31700 - 31799). */
#define KZU_ERROR_LIST_BOX_DUPLICATE_ITEM (kzsError)31701 /**< An object was inserted into a list box twice. */

/* Binding error codes (31800 - 31899). */
#define KZU_ERROR_EXPRESSION_VALIDATOR_ARGUMENTS_DO_NOT_MATCH (kzsError)31801 /**< Request for arithmetic on unmatching arguments.*/
#define KZU_ERROR_EXPRESSION_VALIDATOR_REDUNDANT_CAST (kzsError)31802 /**< Unnecessary cast from a type to itself. */
#define KZU_ERROR_EXPRESSION_VALIDATOR_INVALID_OPERATION_CODE (kzsError)(31803) /**< Expression validator operation code is unknown. */
#define KZU_ERROR_VALIDATOR_CHANGED_AFTER_ATTACH (kzsError)(31804) /**< Expression validator operation code is unknown. */


KZ_HEADER_END


#endif
