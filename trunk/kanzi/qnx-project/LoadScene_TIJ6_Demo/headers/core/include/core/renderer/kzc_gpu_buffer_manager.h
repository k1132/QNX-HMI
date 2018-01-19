/**
* \file
* GPU buffer manager.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZC_GPU_BUFFER_MANAGER_H
#define KZC_GPU_BUFFER_MANAGER_H

#include <system/kzs_types.h>
#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


#if 1
/** Is the GPU buffer manager in use. */
#define KZC_GPU_BUFFER_MANAGER_ENABLED
#endif


/* Forward declarations. */
struct KzcMemoryManager;
struct KzcRenderer;

/**
 * \struct KzcGPUBufferMemoryHandle
 * Handle to memory block in buffer object available for the user.
 */
struct KzcGPUBufferMemoryHandle;

/**
 * \struct KzcGPUBufferManager
 * Structure for core layer renderer.
 */
struct KzcGPUBufferManager;

/** Type enumeration of the buffer. */
enum KzcGPUBufferManagerType
{
    KZC_GPU_BUFFER_MANAGER_TYPE_VERTEX, /**< Vertex buffer. */
    KZC_GPU_BUFFER_MANAGER_TYPE_INDEX /**< Index buffer. */
};

/**
 * \struct KzcGPUBufferManagerStatistics
 * Statistics of GPU buffer manager usage.
 */
struct KzcGPUBufferManagerStatistics
{
    const struct KzcGPUBufferManager* bufferManager; /**< Owner buffer manager. */
    enum KzcGPUBufferManagerType bufferType; /**< Type of the statistics. */
    kzUint poolsCount; /**< Number of memory pools. */
    kzUint availableMemorySize; /**< Available memory size. */
    kzUint usedMemorySize; /**< How much memory is used. */
    kzUint availableMemoryBlocksCount; /**< Number of available memory blocks. */
    kzUint usedMemoryBlocksCount; /**< Number of used memory blocks. */
    kzUint maximumAvailableBlockSize; /**< Maximum size block available. */
};


/** 
 * Creates a new buffer manager. 
 * \param vertexBufferPoolSize - default size of vertex buffer pool (== VBO). If equal to 0, the no default buffer will be created, 
 *  and new pool will be created for each uploaded data.
 * \param indexBufferPoolSize - default size of index buffer pool (== IBO). If equal to 0, the no default buffer will be created, 
 *  and new pool will be created for each uploaded data.
 */
kzsError kzcGPUBufferManagerCreate(const struct KzcMemoryManager* memoryManager, struct KzcRenderer* renderer, 
                                   kzUint vertexBufferPoolSize, kzUint indexBufferPoolSize,
                                   struct KzcGPUBufferManager** out_bufferManager);

/** Deletes buffer manager. */
kzsError kzcGPUBufferManagerDelete(struct KzcGPUBufferManager* bufferManager);

/** Invalidates GPU memory manager by this manager. All pools will be removed and handles to this manager will became invalid. */
kzsError kzcGPUBufferManagerInvalidateGPUMemory(struct KzcGPUBufferManager* bufferManager);

/** 
 * Uploads vertex data to VBO. 
 * If there is no available memory left in existing VBO's, the new one will be created. 
 * \param handle to uploaded vertex data (owned by GPU buffer manager so user should not delete it).
 */
kzsError kzcGPUBufferManagerUploadData(struct KzcGPUBufferManager* bufferManager, enum KzcGPUBufferManagerType bufferType, const void* data, kzUint size, 
                                       const struct KzcGPUBufferMemoryHandle** out_handle);
/** 
 * Frees vertex data in VBO. 
 * \param handle to uploaded vertex data. The handle will be deleted by GPU buffer manager and should not be used after calling this function.
 */
kzsError kzcGPUBufferManagerFreeData(const struct KzcGPUBufferManager* bufferManager, const struct KzcGPUBufferMemoryHandle* handle);

/** Gets type of buffer object referenced by specified handle. */
enum KzcGPUBufferManagerType kzcGPUBufferMemoryHandleGetBufferType(const struct KzcGPUBufferMemoryHandle* handle);
/** Gets handle of buffer object referenced by specified handle. */
kzUint kzcGPUBufferMemoryHandleGetBufferHandle(const struct KzcGPUBufferMemoryHandle* handle);
/** Gets offset in bytes in buffer object for the memory referenced by specified handle. */
kzUint kzcGPUBufferMemoryHandleGetDataOffset(const struct KzcGPUBufferMemoryHandle* handle);

/** 
 * Returns statistics for GPU buffer manager. User is responsible for deleting returned struct instance. 
 * \param statistics - pointer to KzcGpuBufferManagerStatistics struct instance which will be filled with statistics data.
 */
void kzcGPUBufferManagerGetStatistics(const struct KzcGPUBufferManager* bufferManager, enum KzcGPUBufferManagerType bufferType, struct KzcGPUBufferManagerStatistics* statistics);
/** Prints out statistics for GPU buffer manager. */
void kzcGPUBufferManagerDumpStatistics(const struct KzcGPUBufferManager* bufferManager, kzBool dumpPoolBlocks);


KZ_HEADER_END


#endif
