/**
 * \file
 * Node manager for binary tree.
 * This file provides possibility to create binary tree with more control on the internal node handling.
 * 
 * Copyright 2008-2014 by Rightware. All rights reserved.
 */
#ifndef KZC_BINARY_TREE_NODE_MANAGER_H
#define KZC_BINARY_TREE_NODE_MANAGER_H


#include <core/util/collection/kzc_comparator.h>

#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/** Structure of a BinaryTreeNode. */
struct KzcBinaryTreeNode
{
    struct KzcBinaryTreeNode* parent; /**< Parent node of the node. */
    struct KzcBinaryTreeNode* left; /**< Left child node of the node. */
    struct KzcBinaryTreeNode* right; /**< Right child node of the node. */
    void* element; /**< Data of the node. */
};


/* Forward declarations */
struct KzcBinaryTree;


/** Swaps the content of the two nodes. */
typedef void (*KzcNodeSwapFunction)(struct KzcBinaryTreeNode* first, struct KzcBinaryTreeNode* second);


/** Creates a new initially empty binary tree with given node management functions. */
kzsError kzcBinaryTreeCreateManaged(const struct KzcMemoryManager* manager, KzcComparatorFunction comparator,
                                      KzcNodeSwapFunction swapHandler, struct KzcBinaryTree** out_binaryTree);

/** Deletes a binary tree without removing the nodes in it. */
kzsError kzcBinaryTreeDeleteManaged(struct KzcBinaryTree* binaryTree);

/** Gets the root node of the tree. */
struct KzcBinaryTreeNode* kzcBinaryTreeGetRoot(const struct KzcBinaryTree* binaryTree);

/** Sets the root node of the tree. */
void kzcBinaryTreeSetRoot(struct KzcBinaryTree* binaryTree, struct KzcBinaryTreeNode* node);

/** Adds the specified node to the binary tree. */
kzsError kzcBinaryTreeAddNode(struct KzcBinaryTree* binaryTree, struct KzcBinaryTreeNode* node);

/**
 * Removes the specified node from the binary tree.
 * To simplify the removal process, the removed node might not actually be the given one due to node swapping in the tree.
 * The actual removed node is the return value.
 */
struct KzcBinaryTreeNode* kzcBinaryTreeRemoveNode(struct KzcBinaryTree* binaryTree, struct KzcBinaryTreeNode* node);

/** Returns the first node in the tree. */
struct KzcBinaryTreeNode* kzcBinaryTreeGetFirstNode(const struct KzcBinaryTree* binaryTree);
/** Returns the last node in the tree. */
struct KzcBinaryTreeNode* kzcBinaryTreeGetLastNode(const struct KzcBinaryTree* binaryTree);

/** Gets the node with equal value with the given one according to the ordering of the tree. */
struct KzcBinaryTreeNode* kzcBinaryTreeGetEqualNode(const struct KzcBinaryTree* binaryTree, const void* element);
/** Gets the node with the highest element lower than the given one according to the ordering of the tree. */
struct KzcBinaryTreeNode* kzcBinaryTreeGetLowerNode(const struct KzcBinaryTree* binaryTree, const void* element);
/** Gets the node with the highest element lower or equal than the given one according to the ordering of the tree. */
struct KzcBinaryTreeNode* kzcBinaryTreeGetLowerOrEqualNode(const struct KzcBinaryTree* binaryTree, const void* element);
/** Gets the node with the lowest element higher than the given one according to the ordering of the tree. */
struct KzcBinaryTreeNode* kzcBinaryTreeGetHigherNode(const struct KzcBinaryTree* binaryTree, const void* element);
/** Gets the node with the lowest element higher or equal than the given one according to the ordering of the tree. */
struct KzcBinaryTreeNode* kzcBinaryTreeGetHigherOrEqualNode(const struct KzcBinaryTree* binaryTree, const void* element);


KZ_HEADER_END


#endif
