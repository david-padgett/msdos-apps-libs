/* File        : AVLTRE2A.C
   Module      : AVL_TREE
   System      : None
   Description : The operation used to balance AVL Trees.
   Modified    : 03/21/91 DWP Created.
   Notes       :
*/

#include <stdlib.h>

#include "avltree0.h"

/* Procedure   : _AVL_TREE_Balance
   Description : Balances the AVL Tree that is associated with the specified node.  The node is either a recent insertion or the
                 farthest leaf associated with a recent deletion.  The AVL Tree associated with this node is not necessarily
                 unbalanced.
   Inputs      : Element = The element that has possibly caused the AVL Tree associated with it to become unbalanced.
   Updates     : Tree    = The tree to balance.
   Outputs     : Nothing.
   Returns     : Nothing.
   Modified    : 03/21/91 DWP Initial coding.
   Notes       :
*/

void _AVL_TREE_Balance(_AVL_TREE_ELEMENT * Element, _AVL_TREE * Tree) {

   _AVL_TREE_ELEMENT * current_element;
   _AVL_TREE_ELEMENT * parent_element;
   _AVL_TREE_ELEMENT * temporary_element;
   CARDINAL_16         current_depth;

   /* Loop until all of the elements in the current branch have been processed.  This is necessary to update the information used to
      balance the AVL Tree. */

   for (current_element = Element; current_element->Parent != NULL; current_element = parent_element) {

      /* Retrieve the parent element and determine how many levels are beneath the current element.  */

      parent_element = current_element->Parent;
      current_depth = max(current_element->Left_Subtree_Depth, current_element->Right_Subtree_Depth) + 1;

      if (current_element == parent_element->Left_Subtree) {

         /* Update the left sub-tree depth of the parent element and then determine if the parent element still adheres to the definition
            of an AVL Tree.  If it does, continue processing the current branch. */

         if (abs((parent_element->Left_Subtree_Depth = current_depth) - parent_element->Right_Subtree_Depth) < 2) {

            continue;

         }

         /* The right sub-tree of the current element must not be larger than the left sub-tree.  If it is, correct the problem.
            This rotation does not always need to be applied, but is needed to prevent the other rotation from causing the tree to
            become unbalanced. */

         if (current_element->Right_Subtree_Depth > current_element->Left_Subtree_Depth) {

            parent_element->Left_Subtree = current_element->Parent = temporary_element = current_element->Right_Subtree;
            current_element->Right_Subtree_Depth = temporary_element->Left_Subtree_Depth;

            if ((current_element->Right_Subtree = temporary_element->Left_Subtree) != NULL) {

               temporary_element->Left_Subtree->Parent = current_element;

            }

            temporary_element->Left_Subtree_Depth = max(current_element->Left_Subtree_Depth, current_element->Right_Subtree_Depth) + 1;
            temporary_element->Left_Subtree = current_element;
            temporary_element->Parent = parent_element;

            current_element = temporary_element;

         }

         /* This rotation allows the current element to become the parent of its parent element.  At this point, the sub-tree which has
            as its root the current element is too high by one level.  Performing this rotation will correct the problem. */

         parent_element->Left_Subtree_Depth = current_element->Right_Subtree_Depth;

         if ((parent_element->Left_Subtree = current_element->Right_Subtree) != NULL) {

            current_element->Right_Subtree->Parent = parent_element;

         }

         current_element->Right_Subtree_Depth = max(parent_element->Left_Subtree_Depth, parent_element->Right_Subtree_Depth) + 1;
         current_element->Right_Subtree = parent_element;
         current_element->Parent = parent_element->Parent;

         parent_element->Parent = current_element;

      }
      else {

         /* Update the right sub-tree depth of the parent element and then determine if the parent element still adheres to the
            definition of an AVL Tree.  If it does, continue processing the current branch. */

         if (abs((parent_element->Right_Subtree_Depth = current_depth) - parent_element->Left_Subtree_Depth) < 2) {

            continue;

         }

         /* The left sub-tree of the current element must not be larger than the right sub-tree.  If it is, correct the problem.
            This rotation does not always need to be applied, but is needed to prevent the other rotation from causing the tree to
            become unbalanced. */

         if (current_element->Left_Subtree_Depth > current_element->Right_Subtree_Depth) {

            parent_element->Right_Subtree = current_element->Parent = temporary_element = current_element->Left_Subtree;
            current_element->Left_Subtree_Depth = temporary_element->Right_Subtree_Depth;

            if ((current_element->Left_Subtree = temporary_element->Right_Subtree) != NULL) {

               temporary_element->Right_Subtree->Parent = current_element;

            }

            temporary_element->Right_Subtree_Depth = max(current_element->Left_Subtree_Depth, current_element->Right_Subtree_Depth) + 1;
            temporary_element->Right_Subtree = current_element;
            temporary_element->Parent = parent_element;
            current_element = temporary_element;

         }

         /* This rotation allows the current element to become the parent of its parent element.  At this point, the sub-tree which has
            as its root the current element is too high by one level.  Performing this rotation will correct the problem. */

         parent_element->Right_Subtree_Depth = current_element->Left_Subtree_Depth;

         if ((parent_element->Right_Subtree = current_element->Left_Subtree) != NULL) {

            current_element->Left_Subtree->Parent = parent_element;

         }

         current_element->Left_Subtree_Depth = max(parent_element->Left_Subtree_Depth, parent_element->Right_Subtree_Depth) + 1;
         current_element->Left_Subtree = parent_element;
         current_element->Parent = parent_element->Parent;

         parent_element->Parent = current_element;

      }

      /* If the current element has become the root element, update the root element pointer in the AVL Tree and exit. */

      if ((temporary_element = current_element->Parent) == NULL) {

         Tree->Root = current_element;
         break;

      }

      /* Since the parent element has been displaced, update the pointer that connected the parent element's parent to the parent
         element. */

      if (temporary_element->Left_Subtree == parent_element) {

         temporary_element->Left_Subtree = current_element;

      }
      else {

         temporary_element->Right_Subtree = current_element;

      }

   }

}
