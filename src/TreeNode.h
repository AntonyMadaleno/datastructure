/**
 * @file TreeNode.h
 * @brief Header for struct TreeNode
 * @author Antony Madaleno
 * @version 1.0
 * @date 12-01-2023
 *
 * Header pour les struct de TreeNode
 *
 */

#pragma once
#include <stdbool.h>

/**
 * @struct TreeNode
 */
typedef struct TreeNode
{
    TreeNode * nexts; /// List of nodes following this one
    TreeNode * prev; /// pointer to previous node 
    float value; /// value contained by said node
} TreeNode;