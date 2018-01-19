/**
* \file
* A script container file.
* Holds the content of single script file.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_SCRIPT_H
#define KZU_SCRIPT_H


#include <system/kzs_types.h>
#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations. */
struct KzcMemoryManager;
struct KzuAnimation;
struct KzcHashMap;


/** Type of bounding volume. */
enum KzuScriptingLanguage
{
    KZU_SCRIPTING_LANGUAGE_INVALID /**< Invalid scripting language. */
};

/** Type of bounding volume. */
enum KzuScriptDataType
{
    KZU_SCRIPT_DATA_TYPE_BINARY, /**< Script content is precompiled binary. */
    KZU_SCRIPT_DATA_TYPE_SOURCE  /**< Script content is text. */
};


/**
* \struct KzuScript
* Structure for a script file.
*/
struct KzuScript;


/** Creates and initializes script structure. */
kzsError kzuScriptCreateBinary(const struct KzcMemoryManager* memoryManager, kzString name, enum KzuScriptingLanguage language, const void* data, kzUint dataSize, 
                               struct KzuScript** out_script);
/** Creates and initializes script structure. */
kzsError kzuScriptCreateSource(const struct KzcMemoryManager* memoryManager, kzString name, enum KzuScriptingLanguage language, kzString text, 
                               struct KzuScript** out_script);

/** Deletes script structure. */
kzsError kzuScriptDelete(struct KzuScript* script);


/** Gets the data type from script. */
enum KzuScriptDataType kzuScriptGetDataType(const struct KzuScript* script);
/** Gets the set language from script. */
enum KzuScriptingLanguage kzuScriptGetLanguage(const struct KzuScript* script);


/** Gets the script source from script. Throws error if the data type is not source. */
kzsError kzuScriptGetSource(const struct KzuScript* script, kzString* out_source);
/** Gets the script data from script. Throws error if the data type is not binary. */
kzsError kzuScriptGetBinary(const struct KzuScript* script, void** out_binary, kzUint* out_size);


KZ_HEADER_END


#endif
