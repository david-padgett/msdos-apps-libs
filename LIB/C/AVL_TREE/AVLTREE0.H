/* File        : AVLTREE0.H
   Module      : AVL_TREE
   System      : None
   Description : The implementation header file for the AVL_TREE module.
   Modified    : 03/18/91 DWP Created.
   Notes       :
*/

#include <stdio.h>

#include "avl_tree.h"

/* The definition of an AVL Tree element. */

typedef struct __AVL_TREE_ELEMENT {

   /* The data associated with the node. */

   void *                      Data;

   /* The total number of nodes in the left sub-tree, and the left sub-tree itself. */

   CARDINAL_16                 Left_Subtree_Depth;
   struct __AVL_TREE_ELEMENT * Left_Subtree;

   /* The total number of nodes in the right sub-tree, and the right
      sub-tree itself. */

   CARDINAL_16                 Right_Subtree_Depth;
   struct __AVL_TREE_ELEMENT * Right_Subtree;

   /* The parent tree. */

   struct __AVL_TREE_ELEMENT * Parent;

   /* The identical node list. */

   struct __AVL_TREE_ELEMENT * Identical_Element_List;

} _AVL_TREE_ELEMENT;

/* The definition of an AVL Tree. */

typedef struct __AVL_TREE {

   _AVL_TREE_ELEMENT * Root;
   CARDINAL_32         Total_Elements;
   CARDINAL_16         Element_Size;

} _AVL_TREE;

/* Procedures and Functions. */

_AVL_TREE_ELEMENT * _AVL_TREE_Search(_AVL_TREE_ELEMENT * Tree, void * Data, int (* Comparison_Function)(void * Obj1, void * Obj2), int * Comparison_Result);
void                _AVL_TREE_Balance(_AVL_TREE_ELEMENT * Node, _AVL_TREE * Tree);
