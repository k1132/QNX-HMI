/**
* \file
* Binary reader utilities.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_BINARY_UTIL_H
#define KZU_BINARY_UTIL_H


#include <system/kzs_types.h>
#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations */
struct KzcImage;
struct KzcInputStream;
struct KzcMemoryManager;
struct KzuBinaryDirectory;
struct KzuBinaryFileInfo;
struct KzuPropertyManager;
struct KzuPropertyType;
struct KzuResourceManager;
struct KzuUIDomain;
struct KzuVariant;


/** Type of property container reference. */
enum KzuPropertyContainerReferenceType
{
    KZU_PROPERTY_CONTAINER_REFERENCE_OBJECT_NODE = 0, /**< Object node reference type. */
    KZU_PROPERTY_CONTAINER_REFERENCE_PROJECT_ITEM = 1 /**< Project item reference type. */
};


/** Reads a kzb string from the given input stream. A new string object is allocated and must be freed by the caller. */
kzsException kzuBinaryReadString(const struct KzcMemoryManager* memoryManager, struct KzcInputStream* inputStream,
                                 kzMutableString* out_string);

/** Reads a boolean from kzb format including the padding. */
kzsException kzuBinaryReadBoolean(struct KzcInputStream* inputStream, kzBool* out_value);

/** Gets a resource URL from the given binary directory and a resource path in it. The returned resource URL must be freed with kzcStringDelete(). */
kzsError kzuBinaryGetResourceURL(const struct KzcMemoryManager* memoryManager, const struct KzuBinaryDirectory* directory,
                                 kzString resourcePath, kzMutableString* out_resourceURL);

/**
 * Reads a resource reference from the given input stream opened from the given file info.
 * Returns the URL corresponding the reference. The returned resource URL must be freed with kzcStringDelete().
 */
kzsException kzuBinaryReadResourceReference(const struct KzcMemoryManager* memoryManager, struct KzcInputStream* inputStream, const struct KzuBinaryFileInfo* fileInfo, kzMutableString* out_resourceURL);

/** Gets a resource URL corresponding the given binary file info. The returned resource URL must be freed with kzcStringDelete(). */
kzsError kzuBinaryGetResourceURLFromFile(const struct KzcMemoryManager* memoryManager, const struct KzuBinaryFileInfo* fileInfo,
                                         kzMutableString* out_resourceURL);

/** Loads property from binary. */
kzsError kzuBinaryReadProperty(struct KzcInputStream* inputStream, const struct KzuBinaryFileInfo* file,
                               const void* object, struct KzuPropertyManager* propertyManager,
                               struct KzuResourceManager* resourceManager, struct KzuPropertyType** out_propertyType);
/** Loads property from binary in a thread-safe manner. If the property references resources, this function will only store the URL instead of acquiring the resource. */
kzsError kzuBinaryReadPropertySafe(struct KzcInputStream* inputStream, const struct KzuBinaryFileInfo* file,
                                   const void* object, struct KzuPropertyManager* propertyManager,
                                   struct KzuResourceManager* resourceManager, struct KzuPropertyType** out_propertyType);

/** Read a variant value. */
kzsError kzuBinaryReadVariant(struct KzcInputStream* inputStream, const struct KzuBinaryFileInfo* file,
                              struct KzuVariant* variant, const struct KzuPropertyManager* propertyManager,
                              struct KzuResourceManager* resourceManager);

/** Loads a list of properties from binary. */
kzsError kzuBinaryReadProperties(struct KzcInputStream* inputStream, const struct KzuBinaryFileInfo* file,
                                 const void* object, struct KzuPropertyManager* propertyManager,
                                 struct KzuResourceManager* resourceManager);

/**
 * Loads a list of properties from binary.
 * Unlike kzuBinaryReadProperties, this function does not remove existing properties but instead only flags them as removed.
 * In addition changed properties are flagged as changed.
 */
kzsError kzuBinaryReadObjectNodeProperties(struct KzcInputStream* inputStream, const struct KzuBinaryFileInfo* file,
                                           const void* object, struct KzuPropertyManager* propertyManager,
                                           struct KzuResourceManager* resourceManager);

/**
 * Loads a list of properties from binary without acquiring the resources of pointer properties.
 * A KZ_NULL or a list of property group URLs (kzMutableString) are stored in out_propertyGroupURLs.
 */
kzsError kzuBinaryReadPropertiesSafe(struct KzcInputStream* inputStream, const struct KzuBinaryFileInfo* file,
                                     const void* object, struct KzuPropertyManager* propertyManager,
                                     struct KzuResourceManager* resourceManager);


/** Loads image from binary. */
kzsException kzuBinaryReadImage(const struct KzcMemoryManager* memoryManager, struct KzuBinaryDirectory* directory, kzString path, struct KzcImage** out_image);


/** Reads the given file as a text file and returns the content. */
kzsException kzuBinaryReadTextFile(const struct KzcMemoryManager* memoryManager,
                                   const struct KzuBinaryFileInfo* file, kzMutableString* out_text);


/** Loads binary directory metadata (property types, message types, localization tables). */
kzsError kzuBinaryLoadMetaData(const struct KzuBinaryDirectory* directory, const struct KzuUIDomain* uiDomain);

/** Loads message type from binary. */
kzsException kzuBinaryLoadMessageType(const struct KzuBinaryDirectory* directory, kzString path);
/** Loads message type from binary file. */
kzsException kzuBinaryLoadMessageTypeFromFile(const struct KzuBinaryDirectory* directory, const struct KzuBinaryFileInfo* file);

/** Loads property type from binary. */
kzsException kzuBinaryCreatePropertyType(const struct KzuBinaryDirectory* directory, kzString path);
/** Loads property type from binary file. */
kzsException kzuBinaryCreatePropertyTypeFromFile(const struct KzuBinaryDirectory* directory, const struct KzuBinaryFileInfo* file);

/** Loads a localization table from binary. */
kzsException kzuBinaryLoadLocalizationTable(const struct KzuBinaryDirectory* directory, const struct KzuBinaryFileInfo* file,
                                            const struct KzuUIDomain* uiDomain);


KZ_HEADER_END


#endif
