/**
 * \file
 * This file defines macros KZ_HEADER_BEGIN and KZ_HEADER_END, which should be included in all other header files.
 * 
 * Copyright 2008-2014 by Rightware. All rights reserved.
 */
#ifndef KZS_HEADER_H
#define KZS_HEADER_H


#ifdef __cplusplus
#define KZ_HEADER_BEGIN extern "C" {
#define KZ_HEADER_END }
#else
#define KZ_HEADER_BEGIN
#define KZ_HEADER_END
#endif


#endif
