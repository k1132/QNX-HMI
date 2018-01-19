/**
* \file
* Byte buffer provides functionality for reading/writing arbitrary data from/to a chunk of memory.
* Every function is guarded with bounds checking to prevent accidental out of bounds access.
* Read buffer differs from write buffer in that the memory for it is write-protected (const).
* Bounds checking is done with assertions.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZC_BYTE_BUFFER_H
#define KZC_BYTE_BUFFER_H


#include <system/wrappers/kzs_memory.h>
#include <system/debug/kzs_error.h>
#include <system/kzs_types.h>
#include <system/debug/kzs_counter.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/** State of both read and write byte buffers. */
struct KzcByteBufferState_private
{
    kzSizeT size_private; /**< Size of the buffer. This is constant during the lifetime of a buffer. */
    kzSizeT offset_private; /**< Current offset in the buffer. This changes while the buffer is used. */
};

/**
 * Structure for a readable byte buffer. This struct is exposed in the API to allow creating them in the stack.
 * The members of the struct should never be accessed directly. Proper functions should be used instead.
 */
struct KzcByteReadBuffer
{
    struct KzcByteBufferState_private state_private; /**< State of this buffer. */
    const kzByte* data_private; /**< Pointer for the data of the buffer. */
};

/**
 * Structure for a readable byte buffer in backwards direction. This struct is exposed in the API to allow creating them in the stack.
 * The members of the struct should never be accessed directly. Proper functions should be used instead.
 */
struct KzcByteReadBackwardsBuffer
{
    struct KzcByteBufferState_private state_private; /**< State of this buffer. */
    const kzByte* data_private; /**< Pointer for the data of the buffer. */
};

/**
 * Structure for a writable byte buffer. This struct is exposed in the API to allow creating them in the stack.
 * The members of the struct should never be accessed directly. Proper functions should be used instead.
 */
struct KzcByteWriteBuffer
{
    struct KzcByteBufferState_private state_private; /**< State of this buffer. */
    kzByte* data_private; /**< Pointer for the data of the buffer. */
};

/**
 * Structure for a writable byte buffer in backwards direction. This struct is exposed in the API to allow creating them in the stack.
 * The members of the struct should never be accessed directly. Proper functions should be used instead.
 */
struct KzcByteWriteBackwardsBuffer
{
    struct KzcByteBufferState_private state_private; /**< State of this buffer. */
    kzByte* data_private; /**< Pointer for the data of the buffer. */
};


/** Initializes a byte buffer with given parameters. */
KZ_INLINE void kzcByteBufferInitialize_private(struct KzcByteBufferState_private* buffer, kzSizeT size)
{
    buffer->size_private = size;
    buffer->offset_private = 0;
}

/** Initializes a readable byte buffer pointing to the given buffer of given size. */
KZ_INLINE void kzcByteBufferInitializeRead(struct KzcByteReadBuffer* buffer, const void* pointer, kzSizeT size)
{
    kzcByteBufferInitialize_private(&buffer->state_private, size);
    buffer->data_private = (kzByte*)pointer;
}

/** Initializes a readable byte buffer for backwards direction ending at the given pointer. */
KZ_INLINE void kzcByteBufferInitializeBackwardsRead(struct KzcByteReadBackwardsBuffer* buffer, const void* pointer, kzSizeT size)
{
    kzcByteBufferInitialize_private(&buffer->state_private, size);
    buffer->data_private = (kzByte*)pointer;
}

/** Initializes a writable byte buffer pointing to the given buffer of given size. */
KZ_INLINE void kzcByteBufferInitializeWrite(struct KzcByteWriteBuffer* buffer, void* pointer, kzSizeT size)
{
    kzcByteBufferInitialize_private(&buffer->state_private, size);
    buffer->data_private = (kzByte*)pointer;
}

/** Initializes a reverse ordered writable byte buffer ending at the given pointer. */
KZ_INLINE void kzcByteBufferInitializeBackwardsWrite(struct KzcByteWriteBackwardsBuffer* buffer, void* pointer, kzSizeT size)
{
    kzcByteBufferInitialize_private(&buffer->state_private, size);
    buffer->data_private = (kzByte*)pointer;
}


/** Read arbitrary type from the given buffer. The size of the type is taken automatically. */
#define kzcByteBufferRead(buffer_param, value_param) kzcByteBufferRead_private(buffer_param, sizeof(value_param), (void*)&value_param)
/** Read arbitrary type from the given backwards buffer. The size of the type is taken automatically. */
#define kzcByteBufferBackwardsRead(buffer_param, value_param) kzcByteBufferBackwardsRead_private(buffer_param, sizeof(value_param), (void*)&value_param)
/** Write arbitrary type to the given buffer. The size of the type is taken automatically. */
#define kzcByteBufferWrite(buffer_param, value_param) kzcByteBufferWrite_private(buffer_param, sizeof(value_param), (void*)&value_param)
/** Write arbitrary type to the given backwards buffer. The size of the type is taken automatically. */
#define kzcByteBufferBackwardsWrite(buffer_param, value_param) kzcByteBufferBackwardsWrite_private(buffer_param, sizeof(value_param), (void*)&value_param)


/** \see kzcByteBufferRead */
KZ_INLINE void kzcByteBufferRead_private(struct KzcByteReadBuffer* buffer, kzSizeT size, void* out_value)
{
    kzsAssert(buffer->state_private.offset_private + size <= buffer->state_private.size_private);

    kzsMemcpy(out_value, buffer->data_private + buffer->state_private.offset_private, size);
    buffer->state_private.offset_private += size;

    kzsCounterIncrease("byteBufferRead");
}

/** \see kzcByteBufferBackwardsRead */
KZ_INLINE void kzcByteBufferBackwardsRead_private(struct KzcByteReadBackwardsBuffer* buffer, kzSizeT size, void* out_value)
{
    kzsAssert(buffer->state_private.offset_private + size <= buffer->state_private.size_private);

    buffer->state_private.offset_private += size;
    kzsMemcpy(out_value, buffer->data_private - buffer->state_private.offset_private, size);

    kzsCounterIncrease("byteBufferRead");
}

/** \see kzcByteBufferWrite */
KZ_INLINE void kzcByteBufferWrite_private(struct KzcByteWriteBuffer* buffer, kzSizeT size, const void* value)
{
    kzsAssert(buffer->state_private.offset_private + size <= buffer->state_private.size_private);

    kzsMemcpy(buffer->data_private + buffer->state_private.offset_private, value, size);
    buffer->state_private.offset_private += size;

    kzsCounterIncrease("byteBufferWrite");
}

/** \see kzcByteBufferBackwardsWrite */
KZ_INLINE void kzcByteBufferBackwardsWrite_private(struct KzcByteWriteBackwardsBuffer* buffer, kzSizeT size, const void* value)
{
    kzsAssert(buffer->state_private.offset_private + size <= buffer->state_private.size_private);

    buffer->state_private.offset_private += size;
    kzsMemcpy(buffer->data_private - buffer->state_private.offset_private, value, size);

    kzsCounterIncrease("byteBufferWrite");
}

/** Allocate a chunk of read-only memory of given size from the given buffer. */
KZ_INLINE const void* kzcByteBufferAllocateReadPointer(struct KzcByteReadBuffer* buffer, kzSizeT size)
{
    const void* pointer;

    kzsAssert(buffer->state_private.offset_private + size <= buffer->state_private.size_private);

    pointer = buffer->data_private + buffer->state_private.offset_private;
    buffer->state_private.offset_private += size;

    return pointer;
}

/** Allocate a chunk of read-only memory of given size from the given buffer. */
KZ_INLINE const void* kzcByteBufferBackwardsAllocateReadPointer(struct KzcByteReadBackwardsBuffer* buffer, kzSizeT size)
{
    const void* pointer;

    kzsAssert(buffer->state_private.offset_private + size <= buffer->state_private.size_private);

    buffer->state_private.offset_private += size;
    pointer = buffer->data_private - buffer->state_private.offset_private;

    return pointer;
}

/** Allocate a chunk of memory of given size from the given buffer. */
KZ_INLINE void* kzcByteBufferAllocateWritePointer(struct KzcByteWriteBuffer* buffer, kzSizeT size)
{
    void* pointer;

    kzsAssert(buffer->state_private.offset_private + size <= buffer->state_private.size_private);

    pointer = buffer->data_private + buffer->state_private.offset_private;
    buffer->state_private.offset_private += size;

    return pointer;
}

/** Allocate a chunk of memory of given size from the given buffer. */
KZ_INLINE void* kzcByteBufferBackwardsAllocateWritePointer(struct KzcByteWriteBackwardsBuffer* buffer, kzSizeT size)
{
    void* pointer;

    kzsAssert(buffer->state_private.offset_private + size <= buffer->state_private.size_private);

    buffer->state_private.offset_private += size;
    pointer = buffer->data_private - buffer->state_private.offset_private;

    return pointer;
}


/** Reset the buffer offset back to zero. */
#define kzcByteBufferReset(buffer_param) kzcByteBufferReset_private(&(buffer_param)->state_private)
/** \see kzcByteBufferReset */
KZ_INLINE void kzcByteBufferReset_private(struct KzcByteBufferState_private* buffer)
{
    buffer->offset_private = 0;
}


/** Skip given amount of bytes in the buffer. */
#define kzcByteBufferSkip(buffer_param, offset_param) kzcByteBufferSkip_private(&(buffer_param)->state_private, offset_param)
/** \see kzcByteBufferSkip */
KZ_INLINE void kzcByteBufferSkip_private(struct KzcByteBufferState_private* buffer, kzSizeT offset)
{
    kzsAssert(buffer->offset_private + offset <= buffer->size_private);
    
    buffer->offset_private += offset;
}


/** Get the current offset in the buffer. */
#define kzcByteBufferGetOffset(buffer_param) kzcByteBufferGetOffset_private(&(buffer_param)->state_private)
/** \see kzcByteBufferGetOffset */
KZ_INLINE kzUint kzcByteBufferGetOffset_private(const struct KzcByteBufferState_private* buffer)
{
    return buffer->offset_private;
}


/** Set the current offset in the buffer. */
#define kzcByteBufferSetOffset(buffer_param, offset_param) kzcByteBufferSetOffset_private(&(buffer_param)->state_private, offset_param)
/** \see kzcByteBufferSetOffset */
KZ_INLINE void kzcByteBufferSetOffset_private(struct KzcByteBufferState_private* buffer, kzSizeT offset)
{
    kzsAssert(offset <= buffer->size_private);

    buffer->offset_private = offset;
}


/** Check if the buffer has been read or written completely. */
#define kzcByteBufferIsFinished(buffer_param) kzcByteBufferIsFinished_private(&(buffer_param)->state_private)
/** \see kzcByteBufferIsFinished */
KZ_INLINE kzBool kzcByteBufferIsFinished_private(const struct KzcByteBufferState_private* buffer)
{
    kzsAssert(buffer->offset_private <= buffer->size_private);

    return buffer->offset_private == buffer->size_private;
}


KZ_HEADER_END


#endif
