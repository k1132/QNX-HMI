/**
* \file
* Binary directory for .kzb format.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_BINARY_DIRECTORY_H
#define KZU_BINARY_DIRECTORY_H


#include "kzu_binary_common.h"

#include <core/util/io/kzc_io_stream.h>
#include <core/util/collection/kzc_hash_set.h>

#include <system/kzs_types.h>
#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/** Current binary format version. */
#define KZU_BINARY_FORMAT_VERSION 106


/* Forward declarations. */
struct KzuBinaryDirectoryFilter;
struct KzcMemoryManager;
struct KzcInputStream;
struct KzcDynamicArray;


#define KZU_BINARY_FILE_INFO_FLAG_LOAD_ON_DEMAND (1 << 1) /**< This flag is no longer used. */
#define KZU_BINARY_FILE_INFO_FLAG_CACHED_RESOURCE (1 << 2) /**< If the flag is true, the object will not be released when calling kzuProjectClear. */
#define KZU_BINARY_FILE_INFO_FLAG_IMAGE_USED_IN_CUBE_MAPS (1 << 4) /**< This flag is only available in images. If the flag is true, the image is used in a cube map and should not be flipped internally. */
#define KZU_BINARY_FILE_INFO_FLAG_IMAGE_PREMULTIPLIED_ALPHA (1 << 5) /**< This flag is only available in images. If the flag is true, the image has premultiplied alpha. */
#define KZU_BINARY_DIRECTORY_DEFAULT_FILE_FLAG_MASK 0xFF /**< Default mask to pass all flags. */


/** License type restrictions. */
enum KzuBinaryLicenseRestriction
{
    KZU_BINARY_LICENSE_RESTRICTION_SHOW_SPLASH_SCREEN, /**< Splash screen will be shown during startup. */
    KZU_BINARY_LICENSE_RESTRICTION_SHOW_WATERMARK /**< Watermark will be displayed on top of everything else. */
};


/**
 * \struct KzuBinarySource
 * Specifies a source where file content can be read with an input stream.
 */
struct KzuBinarySource;

/**
 * \struct KzuBinaryFileInfo
 * Represents a single file inside a directory.
 */
struct KzuBinaryFileInfo;

/**
 * \struct KzuBinaryFolderInfo
 * Represents a single folder inside a directory.
 */
struct KzuBinaryFolderInfo;

/**
 * \struct KzuBinaryDirectory
 * Directory of a single .kzb binary or a merged result of several .kzb binaries.
 */
struct KzuBinaryDirectory;


/* Binary source */

/**
 * Gets a full file path for the given reference index from the binary source.
 * \return Full file path of the reference with the given index or KZ_NULL if index == 0.
 */
kzString kzuBinarySourceGetReferencedFilePath(const struct KzuBinarySource* source, kzUint index);

/**
 * Invalidates the given binary source. After invalidating a source it will be impossible to load the files from it,
 * but the references can be queried.
 */
kzsError kzuBinarySourceInvalidate(struct KzuBinarySource* source);


/* Binary file info */

/** Gets the name of a file. */
kzString kzuBinaryFileInfoGetName(const struct KzuBinaryFileInfo* file);

/** Gets a directory of the binary file info. */
struct KzuBinaryDirectory* kzuBinaryFileInfoGetDirectory(const struct KzuBinaryFileInfo* file);

/** Gets the binary source of a file. */
struct KzuBinarySource* kzuBinaryFileInfoGetSource(const struct KzuBinaryFileInfo* file);

/** Gets the size of a file. */
kzUint kzuBinaryFileInfoGetSize(const struct KzuBinaryFileInfo* file);

/** Gets the type of a file. */
enum KzuBinaryFileType kzuBinaryFileInfoGetType(const struct KzuBinaryFileInfo* file);

/** Gets the path of a file. */
kzString kzuBinaryFileInfoGetPath(const struct KzuBinaryFileInfo* file);

/** Gets flags from binary file. */
kzU32 kzuBinaryFileInfoGetFlags(const struct KzuBinaryFileInfo* file);

/** Returns true if the file should be cached. */
kzBool kzuBinaryFileInfoIsCached(const struct KzuBinaryFileInfo* file);

/** Returns true if the file is an image file that is used in cubemaps. */
kzBool kzuBinaryFileInfoIsImageUsedInCubemaps(const struct KzuBinaryFileInfo* file);

/** Returns true if the file is an image file that has premultiplied alpha. */
kzBool kzuBinaryFileInfoIsImagePremultipliedAlpha(const struct KzuBinaryFileInfo* file);


/* Binary folder info */

/** Gets the name of a folder. */
kzString kzuBinaryFolderInfoGetName(const struct KzuBinaryFolderInfo* folder);

/**
 * Gets the sub folders of a folder.
 * \return Hash map of kzString -> KzuBinaryDirectoryFolder entries.
 */
struct KzcHashMap* kzuBinaryFolderInfoGetSubFolders(const struct KzuBinaryFolderInfo* folder);

/**
 * Gets the files of a folder.
 * \return Hash map of kzString -> KzuBinaryDirectoryFile entries.
 */
struct KzcHashMap* kzuBinaryFolderInfoGetFiles(const struct KzuBinaryFolderInfo* folder);

/** Gets all files recursively from a folder. The files are added to the given dynamic array. */
kzsError kzuBinaryFolderInfoGetAllFiles(const struct KzuBinaryFolderInfo* folder, struct KzcDynamicArray* files);

/**
 * Gets a specific sub folder from a folder.
 * \param name Name of the sub folder.
 * \return Returns a sub folder or KZ_NULL if a sub folder with the given name was not found.
 */
struct KzuBinaryFolderInfo* kzuBinaryFolderInfoGetSubFolder(const struct KzuBinaryFolderInfo* folder, kzString name);

/**
 * Gets a specific sub file from a folder.
 * \param name Name of the file.
 * \return Returns a file or KZ_NULL if a file with the given name was not found.
 */
struct KzuBinaryFileInfo* kzuBinaryFolderInfoGetFile(const struct KzuBinaryFolderInfo* folder, kzString name);


/* Binary directory */

/** Creates an empty directory. Content can be added to the directory with kzuBinaryDirectoryMerge(). */
kzsError kzuBinaryDirectoryCreateEmpty(const struct KzcMemoryManager* memoryManager, struct KzuBinaryDirectory** out_directory);

/** Creates a directory and fills the content from a .kzb file. Returns a binary directory and an associated binary source. out_binarySource can be KZ_NULL. */
kzsError kzuBinaryDirectoryCreateFromFile(const struct KzcMemoryManager* memoryManager, kzString filePath, 
                                          struct KzuBinaryDirectory** out_directory, struct KzuBinarySource** out_binarySource);

/** Creates a directory and fills the content from a .kzb memory mapped file. Returns a binary directory and an associated binary source. out_binarySource can be KZ_NULL. */
kzsError kzuBinaryDirectoryCreateFromMemoryMappedFile(const struct KzcMemoryManager* memoryManager, kzString filePath, 
                                                      struct KzuBinaryDirectory** out_directory, struct KzuBinarySource** out_binarySource);

/** Creates a directory and fills the content from a .kzb resource file. Returns a binary directory and an associated binary source. out_binarySource can be KZ_NULL. */
kzsError kzuBinaryDirectoryCreateFromFileResource(const struct KzcMemoryManager* memoryManager, kzString resourcePath, 
                                                  struct KzuBinaryDirectory** out_directory, struct KzuBinarySource** out_binarySource);

/** Creates a directory and fills the content from memory buffer with .kzb content. Returns a binary directory and an associated binary source. out_binarySource can be KZ_NULL. */
kzsException kzuBinaryDirectoryCreateFromMemory(const struct KzcMemoryManager* memoryManager, const kzByte* buffer, kzUint size, 
                                                struct KzuBinaryDirectory** out_directory, struct KzuBinarySource** out_binarySource);

/** Deletes a directory. */
kzsError kzuBinaryDirectoryDelete(struct KzuBinaryDirectory* directory);


/** Clears a directory. */
kzsError kzuBinaryDirectoryClear(struct KzuBinaryDirectory* directory);

/**
 * Checks if the binary directory is empty. A directory is not empty if it was created with some other function than kzuBinaryDirectoryCreateEmpty
 * or a non-empty directory was merged to an empty directory.
 */
kzBool kzuBinaryDirectoryIsEmpty(const struct KzuBinaryDirectory* directory);

/**
 * Merges the content of two directories.
 * Note: This function will completely delete sourceDirectory rendering any references to it invalid.
 * This is to ensure that each directory entry is owned by only one directory.
 * \param mergedFiles If this parameter is not NULL, all merged files are recorded in this dynamic array of KzuBinaryFileInfo objects.
 */
kzsError kzuBinaryDirectoryMerge(struct KzuBinaryDirectory* targetDirectory, struct KzuBinaryDirectory* sourceDirectory,
                                 struct KzcDynamicArray* mergedFiles);

/** 
 * Copies shortcuts from one binary directory to another. 
 * If target directory have the same shortcut, the shortcut will not be overwritten.
 */
kzsError kzuBinaryDirectoryCopyShortcuts(const struct KzuBinaryDirectory* targetDirectory, const struct KzuBinaryDirectory* sourceDirectory);

/** Gets the root folder of a directory. */
struct KzuBinaryFolderInfo* kzuBinaryDirectoryGetRootFolder(const struct KzuBinaryDirectory* directory);

/** Gets the directory name. */
kzString kzuBinaryDirectoryGetName(const struct KzuBinaryDirectory* directory);

/** Gets an iterator of all deleted files in a directory. */
struct KzcHashSetIterator kzuBinaryDirectoryGetDeletedFiles(const struct KzuBinaryDirectory* directory);

/** Gets a file with the given shortcut or full path from a binary directory. Note that because of shortcut objects, the returned file may exist in different path than requested. */
kzsException kzuBinaryDirectoryGetFile(const struct KzcMemoryManager* memoryManager, const struct KzuBinaryDirectory* directory, kzString filePath, struct KzuBinaryFileInfo** out_file);

/** Gets flags from binary directory. */
kzU32 kzuBinaryDirectoryGetFlags(const struct KzuBinaryDirectory* directory);

/** Gets a folder with given path from binary directory. E.g. "Objects/" would return Object library. */
kzsException kzuBinaryDirectoryGetFolder(const struct KzuBinaryDirectory* directory, kzString folderPath, struct KzuBinaryFolderInfo** out_folder);

/** Opens a given file for reading. */
kzsException kzuBinaryDirectoryOpenFile(const struct KzcMemoryManager* memoryManager, const struct KzuBinaryFileInfo* file,
                                    struct KzcInputStream** out_inputStream);

/** Opens a given file for reading with the specified endianness. */
kzsException kzuBinaryDirectoryOpenFileWithEndianness(const struct KzcMemoryManager* memoryManager, const struct KzuBinaryFileInfo* file,
                                                  enum KzcIOStreamEndianness endianness, struct KzcInputStream** out_inputStream);

/** Returns binary data from file.*/
kzsError kzuBinaryDirectoryReadFile(const struct KzcMemoryManager* memoryManager, const struct KzuBinaryFileInfo* file, kzByte** out_data);

/**
 * Opens a given file for reading with reference positions returned in an array.
 * The references in the file can be queried with the functions kzuBinaryFileInfoGetSource() and kzuBinarySourceGetReferencedFilePath().
 * \param out_referencePositions This array will be filled with positions of each reference in the file.
 *                               If this parameter is KZ_NULL, the position information is ignored and the array is not created.
 *                               The caller must free the array with kzcMemoryFreeArray afterwards.
 */
kzsException kzuBinaryDirectoryOpenFileWithReferences(const struct KzcMemoryManager* memoryManager,
                                                      const struct KzuBinaryFileInfo* file, kzUint** out_referencePositions,
                                                      enum KzcIOStreamEndianness endianness, struct KzcInputStream** out_inputStream);

/**
 * Gets all file paths referenced by the given file. The paths are returned in an array of strings, which the caller
 * must delete after done using it.
 */
kzsError kzuBinaryDirectoryGetFileReferences(const struct KzcMemoryManager* memoryManager,
                                             const struct KzuBinaryFileInfo* file, kzString** out_references);

/** Gets all binary sources from directory. */
struct KzcHashSetIterator kzuBinaryDirectoryGetBinarySources(const struct KzuBinaryDirectory* directory);

/** Gets a string description of a given file. This is for debugging purposes only. */
kzsError kzuBinaryDirectoryGetFileDebugDescription(const struct KzuBinaryFileInfo* file, kzMutableString* out_description);

/** Search for the given file path from shortcuts. If it is found, return the target path of the shortcut. Otherwise return filePath. */
kzString kzuBinaryDirectoryGetActualPath(const struct KzuBinaryDirectory* directory, kzString filePath);

/** Gets file from property type library, using optimized search. */
kzsException kzuBinaryDirectoryGetFileFromPropertyTypeLibrary(const struct KzuBinaryDirectory* directory, kzString name,
                                                              struct KzuBinaryFileInfo** out_file);
/** Gets file from animation library, using optimized search. */
kzsException kzuBinaryDirectoryGetFileFromAnimationLibrary(const struct KzuBinaryDirectory* directory, kzString filePath,
                                                           struct KzuBinaryFileInfo** out_file);
/** Gets file from mesh library, using optimized search. */
kzsException kzuBinaryDirectoryGetFileFromMeshLibrary(const struct KzuBinaryDirectory* directory, kzString filePath,
                                                      struct KzuBinaryFileInfo** out_file);

/** Loads reference. */
kzsError kzuBinaryDirectoryReadReference(struct KzcInputStream* inputStream, const struct KzuBinaryFileInfo* file, kzString* out_path);
/** Sets file flag mask for binary directory files. Results loaded files to have flags with formula: flags = file.flags & directory.mask */
void kzuBinaryDirectorySetFileFlagMask(struct KzuBinaryDirectory* binaryDirectory, kzU32 fileFlagMask);
/** Gets file flag mask from directory. */
kzU32 kzuBinaryDirectoryGetFileFlagMask(const struct KzuBinaryDirectory* directory);


/** Checks if any of the loaded binaries have the given license restriction enabled. */
kzBool kzuBinaryDirectoryHasLicenseRestriction(const struct KzuBinaryDirectory* directory, enum KzuBinaryLicenseRestriction licenseRestriction);


KZ_HEADER_END


#endif
