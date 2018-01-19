/**
 * \file
 * Binary search tree.
 * 
 * Copyright 2008-2014 by Rightware. All rights reserved.
 */
#ifndef KZC_BINARY_TREE_H
#define KZC_BINARY_TREE_H


#include "kzc_comparator.h"

#include <system/kzs_types.h>
#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations */
struct KzcMemoryManager;
struct KzcBinaryTreeNode;


/**
 * \struct KzcBinaryTree
 * Structure of a binary tree.
 */
struct KzcBinaryTree;


/** Read-only iterator for binary tree. */
struct KzcBinaryTreeIterator
{
    const struct KzcBinaryTree* tree_private; /**< Binary tree associated with this iterator. */
    const struct KzcBinaryTreeNode* node_private; /**< Current node being iterated. */
    const struct KzcBinaryTreeNode* next_private; /**< Next node to iterate. */
};


/** Creates a new initially empty binary tree.
 * \param memoryManager The memory manager to use for allocating the tree and any nodes to it.
 * \param comparator A function that is used to compare two elements and specify the order of elements in the tree.
 * \param out_binaryTree A pointer that is set to point to the new binary tree.
 * \return ::KZS_SUCCESS on success.
 */
kzsError kzcBinaryTreeCreate(const struct KzcMemoryManager* memoryManager, KzcComparatorFunction comparator,
                               struct KzcBinaryTree** out_binaryTree);

/** Frees the memory allocated for the binary tree. */
kzsError kzcBinaryTreeDelete(struct KzcBinaryTree* binaryTree);

/** Adds the specified element to the binary tree. The element must not already exist in the tree.
 * \return ::KZC_ERROR_DUPLICATE_ELEMENT if the element already exists in the tree, ::KZS_SUCCESS on success.
 */
kzsError kzcBinaryTreeAdd(struct KzcBinaryTree* binaryTree, void* element);

/**
 * Removes the specified element from the binary tree.
 * Decides equality by using the ::KzcComparatorFunction previously passed to ::kzcBinaryTreeCreate().
 * \return ::KZC_ERROR_ELEMENT_NOT_FOUND if the element is not found, ::KZS_SUCCESS on success.
 */
kzsError kzcBinaryTreeRemove(struct KzcBinaryTree* binaryTree, const void* element);

/** Returns the number of elements in the binary tree. */
kzUint kzcBinaryTreeGetSize(const struct KzcBinaryTree* binaryTree);

/** Returns the first element in the tree. */
void* kzcBinaryTreeGetFirst(const struct KzcBinaryTree* binaryTree);
/** Returns the last element in the tree. */
void* kzcBinaryTreeGetLast(const struct KzcBinaryTree* binaryTree);


/** Returns an iterator for all elements in the binary tree. */
struct KzcBinaryTreeIterator kzcBinaryTreeGetIterator(const struct KzcBinaryTree* binaryTree);

/** Finds the next entry in the attached binary tree. Returns KZ_TRUE if next entry is found, otherwise KZ_FALSE. */
#define kzcBinaryTreeIterate(iterator_param) kzcBinaryTreeIterate_private(&iterator_param)
/** Returns the value of the binary tree entry pointed by the iterator. */
#define kzcBinaryTreeIteratorGetValue(iterator_param) kzcBinaryTreeIteratorGetValue_private(&iterator_param)

/** \see kzcBinaryTreeIterate */
kzBool kzcBinaryTreeIterate_private(struct KzcBinaryTreeIterator* iterator);
/** \see kzcBinaryTreeIteratorGetValue */
void* kzcBinaryTreeIteratorGetValue_private(const struct KzcBinaryTreeIterator* iterator);


/** Gets the biggest element that is smaller than the given element.
 * The ::KzcComparatorFunction previously passed to ::kzcBinaryTreeCreate() specifies the order.
 */
void* kzcBinaryTreeGetLower(const struct KzcBinaryTree* binaryTree, const void* element);
/** Gets the biggest element that is smaller or equal than the given element.
 * The ::KzcComparatorFunction previously passed to ::kzcBinaryTreeCreate() specifies the order.
 */
void* kzcBinaryTreeGetLowerOrEqual(const struct KzcBinaryTree* binaryTree, const void* element);
/** Gets the smallest element that is bigger than the given element.
 * The ::KzcComparatorFunction previously passed to ::kzcBinaryTreeCreate() specifies the order.
 */
void* kzcBinaryTreeGetHigher(const struct KzcBinaryTree* binaryTree, const void* element);
/** Gets the smallest element that is bigger or equal than the given element.
 * The ::KzcComparatorFunction previously passed to ::kzcBinaryTreeCreate() specifies the order.
 */
void* kzcBinaryTreeGetHigherOrEqual(const struct KzcBinaryTree* binaryTree, const void* element);

/** Clears the tree by removing all nodes from it. */
kzsError kzcBinaryTreeClear(struct KzcBinaryTree* binaryTree);


KZ_HEADER_END


#endif
