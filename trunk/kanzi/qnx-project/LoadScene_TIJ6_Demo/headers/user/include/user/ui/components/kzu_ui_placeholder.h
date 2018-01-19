/**
* \file
* User interface placeholder component.
* 
* KzuUiPlaceholder is a ::KzuUiComponentNode without any functionality except that it can act as the parent
* of other objects. The 2D counterpart is \ref kzu_empty_layer.h.
*
* \see \ref kzu_empty_node.h, \ref kzu_empty_layer.h.
*
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_UI_PLACEHOLDER_H
#define KZU_UI_PLACEHOLDER_H


#include <user/scene_graph/kzu_object_common.h>

#include <system/kzs_types.h>
#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations. */
struct KzcMemoryManager;
struct KzuObjectNode;
struct KzuUiComponentNode;
struct KzuMessageDispatcher;
struct KzuFactory;


/**
 * \struct KzuUiPlaceholder
 * Placeholder user interface component.
 */
struct KzuUiPlaceholder;


/** Registers component type to factory. */
kzsError kzuUiPlaceholderRegisterToFactory(const struct KzuFactory* factory);


/** Object type for UI component placeholder. */
extern const KzuObjectType KZU_OBJECT_TYPE_UI_PLACEHOLDER;


KZ_HEADER_END


#endif
