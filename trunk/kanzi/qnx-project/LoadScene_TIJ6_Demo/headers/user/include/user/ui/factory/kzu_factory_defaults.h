/**
* \file
* Implements registering default objects to a factory.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/

#ifndef KZU_FACTORY_DEFAULTS_H
#define KZU_FACTORY_DEFAULTS_H


#include <system/kzs_types.h>
#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations. */
struct KzuFactory;


/** Registers default objects to given factory. */
kzsError kzuFactoryDefaultsRegisterObjects(const struct KzuFactory* factory);


KZ_HEADER_END


#endif
