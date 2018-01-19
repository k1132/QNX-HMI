/**
 * \file
 * Performance profiler.
 * 
 * Copyright 2008-2014 by Rightware. All rights reserved.
 */
#ifndef KZS_PROFILING_H
#define KZS_PROFILING_H


#include <system/debug/kzs_error.h>
#include <system/kzs_types.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


#if 1
/**
* Enable profiling globally.
* This define controls whether profiling features are 'compiled in' into the code. To actually use profiling,
* it must still be enabled run-time.
*/
#define KZS_PROFILING_ENABLED
#endif


/**
* \struct KzsProfilingCommand
* A profiling command that is either Begin, Continue, End or NextSample.
*/
struct KzsProfilingCommand;


/** Profiling command types. */
enum KzsProfilingCommandType
{
    KZS_PROFILING_COMMAND_BEGIN,       /**< Begin of a block. */
    KZS_PROFILING_COMMAND_END,         /**< End of a block. */
    KZS_PROFILING_COMMAND_CONTINUE,    /**< Continuing a block. */
    KZS_PROFILING_COMMAND_NEXT_SAMPLE  /**< Next sample starts. */
};


/** Returns the type of a profiling command. */
enum KzsProfilingCommandType kzsProfilingCommandGetType(const struct KzsProfilingCommand* command);

/** If the command is a begin or a continue command, returns the name of the block. */
kzString kzsProfilingCommandGetName(const struct KzsProfilingCommand* command);
/**
* Returns the time difference between two profiling commands. The returned value is end->time - begin->time.
* The first parameter must be a begin or a continue command. The second parameter must be an end command.
*/
kzU64 kzsProfilingCommandGetTimeDifference(const struct KzsProfilingCommand* begin, const struct KzsProfilingCommand* end);

/** Initializes profiling. */
kzsError kzsProfilingInitialize(void);
/** Uninitializes profiling. */
kzsError kzsProfilingUninitialize(void);

/** Returns whether profiling is initialized. */
kzBool kzsProfilingIsInitialized(void);

/** Enables or disables profiling. 
  * To disable profiling, this function should be called with FALSE parameter value
  *  as many times as it was called with TRUE parameter value. 
  */
void kzsProfilingSetEnabled(kzBool enabled);
/** Returns whether profiling is enabled. */
kzBool kzsProfilingIsEnabled(void);

/** Resets profiling statistics. */
void kzsProfilingReset(void);
/** Increases the sample count. This makes the profiler calculate averages over the measured samples. */
void kzsProfilingNextSample(void);

/** Processes the current profiling command buffer. Should be called outside of all profiling blocks. */
kzsError kzsProfilingProcessCommandBuffer(void);

/** Returns the root node of the profiling tree. */
const struct KzsProfilingTreeNode* kzsProfilingTreeGetRoot(void);

/** Returns the number of times the full cycle was sampled. \see kzsProfilingNextSample. */
kzUint kzsProfilingTreeGetSampleCount(void);

/** Returns the parent node of the given profiling node, or KZ_NULL if the node is the root node. */
const struct KzsProfilingTreeNode* kzsProfilingTreeNodeGetParent(const struct KzsProfilingTreeNode* node);
/** Returns the first child node of the given profiling node, or KZ_NULL if the node has no children. */
const struct KzsProfilingTreeNode* kzsProfilingTreeNodeGetFirstChild(const struct KzsProfilingTreeNode* node);
/** Returns the next sibling node of the given profiling node, or KZ_NULL if the node is the last child. */
const struct KzsProfilingTreeNode* kzsProfilingTreeNodeGetNextSibling(const struct KzsProfilingTreeNode* node);
    
/** Gets the name of the given profiling node. */
kzString kzsProfilingTreeNodeGetName(const struct KzsProfilingTreeNode* node);
/** Gets the hit count of the given profiling node. */
kzUint kzsProfilingTreeNodeGetHitCount(const struct KzsProfilingTreeNode* node);
/** Gets the total time of the given profiling node. */
kzU64 kzsProfilingTreeNodeGetTotalTime(const struct KzsProfilingTreeNode* node);
/** Gets the sum of squared times of the given profiling node. */
kzU64 kzsProfilingTreeNodeGetTotalSquaredTime(const struct KzsProfilingTreeNode* node);
/** Gets the minimum time spent in the given profiling node. */
kzU64 kzsProfilingTreeNodeGetMinimumTime(const struct KzsProfilingTreeNode* node);
/** Gets the maximum time spent in the given profiling node. */
kzU64 kzsProfilingTreeNodeGetMaximumTime(const struct KzsProfilingTreeNode* node);


#ifdef KZS_PROFILING_ENABLED


/** Starts profiling a specified block or function. */
#define kzsProfilingBegin(name_param) kzsProfilingBeginMeasure_private(name_param);

/**
* Continues profiling a block or function that was ended for some reason, such as flattening a recursion in the tree.
* Continue differs from begin by not increasing hit count.
*/
#define kzsProfilingContinue(name_param) kzsProfilingContinueMeasure_private(name_param);

/** Ends profiling of the current block or function. */
#define kzsProfilingEnd(name_param) kzsProfilingEndMeasure_private(name_param);


/** Private implementation of kzsProfilingBegin. */
void kzsProfilingBeginMeasure_private(kzString name);
/** Private implementation of kzsProfilingContinue. */
void kzsProfilingContinueMeasure_private(kzString name);
/** Private implementation of kzsProfilingEnd. */
void kzsProfilingEndMeasure_private(kzString name);


#else


/** \cond */
#define kzsProfilingBegin(name_param) (void)0
#define kzsProfilingContinue(name_param) (void)0
#define kzsProfilingEnd(name_param) (void)0
/** \endcond */


#endif


KZ_HEADER_END


#endif
