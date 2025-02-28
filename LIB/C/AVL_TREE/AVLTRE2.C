/* File        : AVLTREE2.C
   Module      : AVL_TREE
   System      : None
   Description : Miscellaneous operations for the AVL_TREE module.
   Modified    :
   Notes       :
*/

#include "avltree0.h"

/* Function    : _AVL_TREE_Search
   Description : Searches for an element in an AVL Tree.
   Inputs      : Tree                = The tree to search.
		 Data                = The data to search for.
		 Comparison_Function = A user-defined function that determines the ordering of the tree.
					  Description : Compares two elements of an AVL Tree to determine their relationship.
					  Inputs      : Obj1 = An exact copy of the parameter Data.
							Obj2 = An element in the tree that is to be compared to the parameter Data.
					  Update      : Nothing.
					  Outputs     : Nothing.
					  Returns     : A value less than zero if Obj1 should occur before Obj2, a value of zero if
							Obj1 and Obj2 are equal, and a value greater than zero if Obj1 should occur
							after Obj2.
   Updates     : Nothing.
   Outputs     : Comparison_Result   = The result of the last successful call to the comparison function.
   Returns     : The AVL Tree node that comes closest to matching the specified data.
   Modified    : 03/18/91 DWP Initial coding.
   Notes       :
*/

_AVL_TREE_ELEMENT * _AVL_TREE_Search(_AVL_TREE_ELEMENT * Tree, void * Data, int (* Comparison_Function)(void * Obj1, void * Obj2), int * Comparison_Result) {

   _AVL_TREE_ELEMENT * result;

   /* Loop until the specified node is found or until there are no more nodes to search. */

   for (result = Tree; result != NULL;) {

      /* Determine which sub-tree should be searched further. */

      if ((*(Comparison_Result) = Comparison_Function(Data, result->Data)) < 0 && result->Left_Subtree != NULL) {

	 result = result->Left_Subtree;

      }
      else {

	 if (*(Comparison_Result) > 0 && result->Right_Subtree != NULL) {

	    result = result->Right_Subtree;

	 }
	 else {

	    /* Either an exact match was found or no further searching is possible. */

	    break;

	 }

      }

   }

   return (result);

}
