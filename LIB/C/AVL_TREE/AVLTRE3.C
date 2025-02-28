/* File        : AVLTRE3.C
   Module      : AVL_TREE
   System      : None
   Description : The insertion operation for the AVL_TREE module.
   Modified    : 03/18/91 DWP Created.
   Notes       :
*/

#include <alloc.h>
#include <memory.h>
#include <stdio.h>

#include "avltree0.h"

/* Function    : AVL_TREE_Insert
   Description : Inserts data into an AVL Tree.
   Inputs      : Data                = The data to be inserted.
                 Comparison_Function = A user-defined function that determines the ordering of the tree.
                                          Description : Compares two elements of an AVL Tree.
                                          Inputs      : Obj1 = An exact copy of the parameter Data.
                                                        Obj2 = An element in the tree that is to be compared to the parameter Data.
                                          Updates     : Nothing.
                                          Outputs     : Nothing.
                                          Returns     : A value less than zero if Obj1 should occur before Obj2, a value of zero
                                                        if Obj1 and Obj2 are equal, and a value greater than zero if Obj1 should
                                                        occur after Obj2.
   Updates     : Tree                = The AVL Tree to insert into.
   Outputs     : Nothing.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 03/18/91 DWP Initial coding.
   Notes       :
*/

int AVL_TREE_Insert(void * Data, int (* Comparison_Function)(void * Obj1, void * Obj2), AVL_TREE Tree) {

   _AVL_TREE_ELEMENT * new_node;
   _AVL_TREE_ELEMENT * parent_node;
   int                 comparison_result, result;

   /* Attempt to create a new tree node.  The buffer that contains the data that is stored in the node is located immediately after
      the node itself.  */

   if ((new_node = malloc(sizeof(_AVL_TREE_ELEMENT) + ((_AVL_TREE *) Tree)->Element_Size)) == NULL) {

      result = AVL_NOMEM;

   }
   else {

      /* Update the AVL Tree node counter and then initialize the new node. */

      ((_AVL_TREE *) Tree)->Total_Elements++;
      new_node->Data = memcpy(new_node + 1, Data, ((_AVL_TREE *) Tree)->Element_Size);
      new_node->Left_Subtree_Depth = new_node->Right_Subtree_Depth = 0;
      new_node->Left_Subtree = new_node->Right_Subtree = new_node->Identical_Element_List = NULL;

      /* Determine where to place the new node in the tree. */

      comparison_result = 1;

      if ((new_node->Parent = parent_node = _AVL_TREE_Search(((_AVL_TREE *) Tree)->Root, Data, Comparison_Function, &comparison_result)) == NULL) {

         /* This is the first node to be inserted into the AVL Tree. */

         ((_AVL_TREE *) Tree)->Root = new_node;

      }
      else {

         if (comparison_result == 0) {

            /* The new node already exists in the AVL Tree so insert it at the beginning of the parent node's identical nodes
               list. */

            new_node->Identical_Element_List = parent_node->Identical_Element_List;
            parent_node->Identical_Element_List = new_node;

         }
         else {

            /* Determine which sub-tree of the parent node the new node belongs in.  The new node will be a leaf of its parent
               node. */

            if (comparison_result < 0) {

               parent_node->Left_Subtree = new_node;

            }
            else {

               parent_node->Right_Subtree = new_node;

            }

            /* Balance the AVL Tree. */

            _AVL_TREE_Balance(new_node, Tree);

         }

      }

      result = AVL_NOERR;

   }

   return (result);

}