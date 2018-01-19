/**
* \file
* Specifies frustum cull filter.
* Frustum cull filter accepts objects whose bounding volume is at least partially inside current view frustum.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_FRUSTUM_CULL_FILTER_H
#define KZU_FRUSTUM_CULL_FILTER_H


#include <system/kzs_types.h>
#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations */
struct KzcMemoryManager;
struct KzuObjectSource;
struct KzuUIDomain;


/** Creates frustum cull filter. */
kzsError kzuFrustumCullFilterCreate(const struct KzcMemoryManager* memoryManager, struct KzuUIDomain* uiDomain,
                                    struct KzuObjectSource* input, kzString name, struct KzuObjectSource** out_objectSource);


KZ_HEADER_END


#endif
