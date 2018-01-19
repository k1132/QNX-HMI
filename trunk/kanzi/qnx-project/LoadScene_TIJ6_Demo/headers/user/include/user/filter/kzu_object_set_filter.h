/**
* \file
* Specifies object set filter.
* Object set filter accepts or rejects all specified objects and all their ancestors.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_OBJECT_SET_FILTER_H
#define KZU_OBJECT_SET_FILTER_H


#include <system/kzs_types.h>
#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations */
struct KzcInputStream;
struct KzcMemoryManager;
struct KzuBinaryFileInfo;
struct KzuObjectNode;
struct KzuObjectSource;
struct KzuUIDomain;


/** Creates object set filter. */
kzsError kzuObjectSetFilterCreate(const struct KzcMemoryManager* memoryManager,  struct KzuUIDomain* uiDomain,
                                  kzString name, struct KzuObjectSource** out_objectSource);

/** Initializes an object set filter. */
kzsError kzuObjectSetFilterInitialize(struct KzuObjectSource* objectSource, struct KzuObjectSource* input, kzBool isExclusive);

/** Adds objects to object set filter. */
kzsError kzuObjectSetFilterAddObjects(const struct KzuObjectSource* objectSource, kzUint objectCount, struct KzuObjectNode* const* objects);

/** Adds new object to object set filter. */
kzsError kzuObjectSetFilterAddObject(const struct KzuObjectSource* objectSource, const struct KzuObjectNode* objectNode);

/** Returns KZ_TRUE if object set contains given object. */
kzBool kzuObjectSetFilterContainsObject(const struct KzuObjectSource* objectSource, const struct KzuObjectNode* objectNode);

/** Removes an object from an object set filter. */
kzsError kzuObjectSetFilterRemoveObject(const struct KzuObjectSource* objectSource, const struct KzuObjectNode* objectNode);

/** Tells if objects source if the object set filter. */
kzBool kzuObjectSourceIsObjectSetFilter(const struct KzuObjectSource* objectSource);

/** Returns collections of objects of object source. */
struct KzcHashSet* kzuObjectSetFilterGetObjects_private(const struct KzuObjectSource* objectSource);


KZ_HEADER_END


#endif
