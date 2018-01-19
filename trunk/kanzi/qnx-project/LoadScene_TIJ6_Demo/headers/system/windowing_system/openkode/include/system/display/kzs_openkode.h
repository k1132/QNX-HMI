/**
* \file
* OpenKODE functions.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZS_OPENKODE_H
#define KZS_OPENKODE_H


#include <KD/kd.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/** Log current OpenKODE error code and return from the function with the given error code, if the test is false. */
#define kzsKDErrorTest(test, new_error, logMessage) KZ_MULTILINE_MACRO \
    if (!(test))                                                       \
    {                                                                  \
        KDint kdError = kdGetError();                                  \
        kdSetError(0); /* kdGetError does not reset error code. */     \
        if (kdError != 0)                                              \
        {                                                              \
            kzsKDErrorNotify(kdError);                                 \
        }                                                              \
        kzsErrorThrow(new_error, logMessage);                          \
    }                                                                  \
KZ_MULTILINE_MACRO_END


/** Logs the current OpenKODE error code. */
void kzsKDErrorNotify(KDint error);


KZ_HEADER_END


#endif
