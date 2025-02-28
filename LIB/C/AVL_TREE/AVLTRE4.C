/* File        : AVLTRE4.C
   Module      : AVL_TREE
   System      : None
   Description : A method for deleting a node from an AVL Tree.
   Modified    : 03/21/91 DWP Created.
   Notes       :
*/

#include <alloc.h>

#include "avltree0.h"

/* Function    : AVL_TREE_Delete
   Description : Deletes the specified node from the specified AVL Tree.
   Inputs      : Key                 = The key whose node is to be removed.
                 Comparison_Function = A user-defined function that determines the ordering of the tree.
                                          Description : Compares two elements of an AVL Tree.
                                          Inputs      : Obj1 = An exact copy of the parameter Key.
                                                        Obj2 = An element in the tree that is to be compared to the parameter data.
                                          Updates     : Nothing.
                                          Outputs     : Nothing.
                                          Returns     : A value less than zero if Obj1 should occur before Obj2, a value of zero
                                                        if Obj1 and Obj2 are equal, and a value greater than zero if Obj1 should
                                                        occur after Obj2.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Updates     : Tree                = The AVL Tree to delete from.
   Outputs     : Nothing.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 03/21/91 DWP Initial coding.
   Notes       :
*/

int AVL_TREE_Delete(void * Key, int (* Comparison_Function)(void * Obj1, void * Obj2), AVL_TREE Tree) {

   _AVL_TREE_ELEMENT * current_node;
   _AVL_TREE_ELEMENT * parent_node;
   _AVL_TREE_ELEMENT * temporary_node;
   _AVL_TREE_ELEMENT * traversal_node;
   int                 Comparison_Result, result;

   /* Locate the node that is to be deleted.  Exit if the node cannot be found. */

   if ((current_node = _AVL_TREE_Search(((_AVL_TREE *) Tree)->Root, Key, Comparison_Function, &Comparison_Result)) == NULL) {

      result = AVL_INVKY;

   }
   else {

      /* Return the data storage buffer to the heap.  Initialize the pointer to the parent node. */

      parent_node = current_node->Parent;

      /* Determine how the tree should be re-ordered.  First attempt to connect the left sub-tree to the parent.  If that is not
         possible, attempt to connect the right sub-tree to the parent.  If that is not possible, then the node was a leaf and no
         re-ordering is necessary. */

      if (current_node->Left_Subtree_Depth > current_node->Right_Subtree_Depth) {

         temporary_node = current_node->Left_Subtree;

         if (parent_node->Left_Subtree == current_node) {

            parent_node->Left_Subtree = temporary_node;

         }
         else {

            parent_node->Right_Subtree = temporary_node;

         }

         temporary_node->Parent = parent_node;

         for (traversal_node = current_node->Right_Subtree; traversal_node->Left_Subtree != NULL; traversal_node = traversal_node->Left_Subtree) {
         }

      }

      /* Return the memory belonging to the node to the heap. */

      free(current_node);
      result = AVL_NOERR;

   }

   return (result);

}