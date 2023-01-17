/**
 * @file ListNode.h
 * @brief Header for struct ListNode
 * @author Antony Madaleno
 * @version 1.0
 * @date 12-01-2023
 *
 * Header pour les struct de ListNode
 *
 */

#pragma once
#include <stdbool.h>

/**
 * @struct ListNode
 * @brief ListNode contain a value (float) and 2 pointer to other ListNodes (prev and next) 
 */
typedef struct ListNode
{
    ListNode * next;
    ListNode * prev;
    float value;
} ListNode;