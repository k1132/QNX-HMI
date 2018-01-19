/**
* \file
* Default item generator.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_ITEM_GENERATOR_DEFAULT_H
#define KZU_ITEM_GENERATOR_DEFAULT_H


#include <user/ui/components/listbox/kzu_item_generator.h>

#include <system/debug/kzs_error.h>
#include <system/kzs_types.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations. */
struct KzuItemGenerator;
struct KzuFactory;


/** Type identifier for default item container generator. */
extern const KzuItemContainerGeneratorType KZU_ITEM_CONTAINER_GENERATOR_TYPE_DEFAULT;


/** Creates a default item container generator. */
kzsError kzuItemGeneratorDefaultCreate(const struct KzcMemoryManager* memoryManager, struct KzuUIDomain* uiDomain,
                                       struct KzuItemGenerator** out_generator);

/** Registers item container generator to factory. */
kzsError kzuItemGeneratorDefaultRegisterToFactory(const struct KzuFactory* factory);


KZ_HEADER_END


#endif
