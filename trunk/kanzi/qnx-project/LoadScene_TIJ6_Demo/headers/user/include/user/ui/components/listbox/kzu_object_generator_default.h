/**
* \file
* Default object generator. Contains a list of user created objects.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_OBJECT_GENERATOR_DEFAULT_H
#define KZU_OBJECT_GENERATOR_DEFAULT_H


#include <user/ui/components/listbox/kzu_object_generator.h>
#include <user/ui/components/listbox/kzu_object_generator_common.h>

#include <system/debug/kzs_error.h>
#include <system/kzs_types.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations. */
struct KzuObjectGenerator;
struct KzuFactory;
struct KzuUIDomain;


/** Default ObjectGenerator for ListBox. Requires the user to manually add items. */
struct KzuObjectGeneratorDefault;


/** Type identifier for default object generator. */
extern const KzuObjectGeneratorType KZU_OBJECT_GENERATOR_TYPE_DEFAULT;


/** Creates an object generator. */
kzsError kzuObjectGeneratorDefaultCreate(const struct KzcMemoryManager* memoryManager, struct KzuUIDomain* uiDomain,
                                         struct KzuObjectGenerator** out_generator);

/** Registers object generator to factory. */
kzsError kzuObjectGeneratorDefaultRegisterToFactory(const struct KzuFactory* factory);

/** Casts default object generator to object generator. */
struct KzuObjectGenerator* kzuObjectGeneratorDefaultToObjectGenerator(const struct KzuObjectGeneratorDefault* generator);

/** Casts object generator to default object generator. */
struct KzuObjectGeneratorDefault* kzuObjectGeneratorDefaultFromObjectGenerator(const struct KzuObjectGenerator* generator);


KZ_HEADER_END


#endif
