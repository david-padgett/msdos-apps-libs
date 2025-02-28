/* File        : AVLTREE1.C
   Module      : AVL_TREE
   System      : None
   Description : The constructor and destructor operations of an AVL Tree.
   Modified    : 03/18/91 DWP Created.
   Notes       :
*/

#include <alloc.h>

#include "avltree0.h"

/* Function    : AVL_TREE_Constructor
   Description : Initializes the specified AVL Tree.
   Inputs      : Element_Size = The size of the data each node will contain.
   Updates     : Nothing.
   Outputs     : Tree         = The tree to initialize.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 03/18/91 DWP Initial coding.
   Notes       :
*/

int AVL_TREE_Constructor(CARDINAL_16 Element_Size, AVL_TREE * Tree) {

   _AVL_TREE * avl_tree;
   int         result;

   if ((avl_tree = malloc(sizeof(_AVL_TREE))) == NULL) {

      result = AVL_NOMEM;

   }
   else {

      avl_tree->Root = NULL;
      avl_tree->Total_Elements = 0L;
      avl_tree->Element_Size = Element_Size;
      result = AVL_NOERR;
      *(Tree) = avl_tree;

   }

   return (result);

}

/* Procedure   : AVL_TREE_Destructor
   Description : Destroys the specified AVL Tree.
   Inputs      : Nothing.
   Updates     : Tree = The AVL Tree to destroy.
   Outputs     : Nothing.
   Returns     : Nothing.
   Modified    : 03/18/91 DWP Initial coding.
   Notes       :
*/

void AVL_TREE_Destructor(AVL_TREE * Tree) {

   *(Tree) = NULL;
}
