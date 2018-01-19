/**
 * \file
 * Preview camera system base structure.
 *
 * Copyright 2008-2014 by Rightware. All rights reserved.
 */
#ifndef KZU_PREVIEW_CAMERA_SYSTEM_BASE_H
#define KZU_PREVIEW_CAMERA_SYSTEM_BASE_H


#include <system/debug/kzs_error.h>
#include <system/kzs_types.h>


/* Forward declarations. */
struct KzcMatrix4x4;

/** Preview camera callback prototype for updating camera state from preview camera. */
typedef kzsError (*KzuPreviewCameraUpdateStateFunction)(struct KzcMatrix4x4* transformation, void* userData);


#endif
