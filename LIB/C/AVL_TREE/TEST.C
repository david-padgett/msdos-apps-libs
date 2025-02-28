/* File        : TEST.C
   Module      : AVL_TREE
   System      : None
   Description : A test program for the AVL_TREE module.
   Modified    : 03/25/91 DWP Created.
   Notes       :
*/

#include <conio.h>
#include <ctype.h>
#include <stdlib.h>

#include "KB\kb.h"
#include "Math\math.h"
#include "avltree0.h"

/* Function    : Comparison_Function
   Description : This function is for testing purposes only.  It should be removed when the module has been completed.  This is the
		 comparison function for the test AVL TREE that contains letters of the alphabet.
   Inputs      : Obj1 = The first of the two letters to compare.
		 Obj2 = The second of the two letters to compare.
   Updates     : Nothing.
   Outputs     : Nothing.
   Returns     : A value less than zero if Obj1 is less than Obj2, a value of zero if Obj1 is equal to Obj2, and a value greater
		 than zero if Obj1 is greater than Obj2.
   Modified    : 03/22/91 DWP Initial coding.
   Notes       :
*/

int Comparison_Function(void * Obj1, void * Obj2) {

   return (*((char *) Obj1) - *((char *) Obj2));
}

/* Procedure   : Print_Data
   Description : Displays an AVL Tree starting at the root.  The tree is descended until all of the nodes have been visited.
		 Currently, this is used for debugging, but may be useful as a method traverse an AVL Tree.
   Inputs      : Tree = The AVL Tree that is to be traversed.
   Updates     : Nothing.
   Outputs     : Nothing.
   Returns     : Nothing.
   Modified    : 03/22/91 DWP Initial coding.
   Notes       :
*/

void Print_Data(AVL_TREE * Tree) {

   _AVL_TREE_ELEMENT * node;
   int                 i, level, maximum_level, maximum_nodes, max_nodes, current_node, space, total_nodes, start_space;

   /* Do all levels. */

   maximum_level = max(((_AVL_TREE *) Tree)->Root->Left_Subtree_Depth, ((_AVL_TREE *) Tree)->Root->Right_Subtree_Depth);
   total_nodes = (int) MATH_Integer_Power(2L, (long) maximum_level);
   printf("Max Level : %d\nMax Nodes : %d\n", maximum_level, total_nodes);

   for (level = 0; level <= maximum_level; level++) {

      maximum_nodes = (int) MATH_Integer_Power(2L, (long) level);

      for (i = maximum_level, space = 3; i > level; i--) {

	 space = (space * 2) + 1;

      }

      start_space = ((((total_nodes - 1) * 4) + 1) - (((maximum_nodes - 1) * space) + maximum_nodes)) / 2;
      printf("%*s", start_space, "");

      for (current_node = 0; current_node < maximum_nodes; current_node++) {

	 for (node = ((_AVL_TREE *) Tree)->Root, max_nodes = maximum_nodes, i = current_node; max_nodes > 1 && node != NULL;) {

	    max_nodes /= 2;

	    if (i < max_nodes) {

	       node = node->Left_Subtree;

	    }
	    else {

	       node = node->Right_Subtree;
	       i -= max_nodes;

	    }

	 }

	 printf("%c%*s", (node != NULL) ? *((char *) node->Data) : ' ', space, "");

      }

      putchar('\n');

   }

}

/* Function    : main
   Description : This function is for testing purposes only.  It should be removed when the module has been completed.
   Inputs      : Nothing.
   Updates     : Nothing.
   Outputs     : Nothing.
   Returns     : Always returns a value of zero.
   Modified    : 03/22/91 DWP Initial coding.
   Notes       :
*/

int main(int argc, char *argv[]) {

   AVL_TREE     tree;
   char         ch, ch_list[256];
   unsigned int key;
   int          i, j, result;

   clrscr();
   AVL_TREE_Constructor(sizeof(int), &tree);

   for (i = 0; TRUE;) {

      ch = 'A' + i++;

      if (ch > 'Z') {

	 break;

      }

/*
      if ((key = KB_Read()) == KB_ESC) {

	 if (toupper(argv[2][0]) != 'N') {

	    break;

	 }

      }

      ch = (char) key;

      for (j = 0; j <= i; j++) {

	 if (ch_list[j] == ch) {

	    break;

	 }

      }

      if (j > i) {

	 ch_list[i++] = ch;
	 ch_list[i] = '\0';
*/
	 if ((result = AVL_TREE_Insert(&ch, Comparison_Function, tree)) != AVL_NOERR) {

	    printf("\n\nAVL Tree Error: %d\n\n", result);
	    break;

	 }

	 if (toupper(argv[1][0]) != 'N') {

	    printf("\n%s\nTtl. Nodes = %d\nLeft Depth = %d  Right Depth = %d\n", ch_list, i, ((_AVL_TREE *) tree)->Root->Left_Subtree_Depth, ((_AVL_TREE *) tree)->Root->Right_Subtree_Depth);
	    Print_Data(tree);

	 }
/*
      }
*/
   }

   return (0);

}