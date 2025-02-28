/* File        : AVLTREE.H
   Module      : AVL_TREE
   System      : None
   Description : The definition header file for the AVL_TREE module.
   Modified    : 03/18/91 DWP Created.
   Notes       :
*/

#ifndef _AVL_TREE_MODULE
#define _AVL_TREE_MODULE

#include "Standard\standard.h"

/* Type definitions. */

typedef enum   _AVL_TREE_ERROR_CODES {AVL_NOERR, AVL_NOMEM, AVL_INVKY, AVL_FAULT} AVL_TREE_ERROR_CODES;
typedef void * AVL_TREE;

/* Procedures and Functions. */

int  AVL_TREE_Constructor(CARDINAL_16 Element_Size, AVL_TREE * Tree);
void AVL_TREE_Destructor(AVL_TREE * Tree);
int  AVL_TREE_Insert(void * Data, int (* Comparison_function)(void * Obj1, void * Obj2), AVL_TREE Tree);
int  AVL_TREE_Delete(void * Key, int (* Comparison_function)(void * Obj1, void * Obj2), AVL_TREE Tree);

#endif
