/**
 * \file
 * Platform-specific globals and constants for Android platform
 * 
 * Copyright 2008-2014 by Rightware. All rights reserved.
 */
#ifndef KZS_ANDROID_H
#define KZS_ANDROID_H


#include <system/kzs_header.h>


KZ_HEADER_BEGIN


#include <jni.h>

/* Newline character on Android platform. String because newline might be several char on some platform. */
#define KZ_NEWLINE (kzString)"\n"

/* Globally available Java Virtual Machine object */
extern JavaVM* g_kzsJavaVM;

/* User-defined Android view class derived from com.rightware.kanzi.KanziView */
extern jclass g_kzsViewClass; 

/* Instance of the user-defined Android view class currently in use */
extern jobject g_kzsView; 

/* User-defined Android activity class derived from com.rightware.kanzi.KanziActivity */
extern jclass g_kzsActivityClass; 

/* Instance of the user-defined Android activity class */
extern jobject g_kzsActivity; 

/* Returns a JNIEnv attached to the current thread. */
JNIEnv* getCurrentJNIEnvironment(void);


KZ_HEADER_END


#endif
