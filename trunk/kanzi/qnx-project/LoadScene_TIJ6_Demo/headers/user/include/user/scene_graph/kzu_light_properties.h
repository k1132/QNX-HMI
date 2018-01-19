/**
 * \file
 * Property accessors for KzuLightNode.
 * 
 * Copyright 2008-2014 by Rightware. All rights reserved.
 */
#ifndef KZU_LIGHT_PROPERTIES_H
#define KZU_LIGHT_PROPERTIES_H


#include "kzu_light.h"

#include <system/kzs_types.h>
#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations */
struct KzuLightNode;


/** Gets the value of property Enabled in lightNode. */
kzBool kzuLightNodeIsEnabled(const struct KzuLightNode* lightNode);
/** Sets the value of property Enabled in lightNode. */
kzsError kzuLightNodeSetEnabled(const struct KzuLightNode* lightNode, kzBool value);


KZ_HEADER_END


#endif
