/* File        : LIST6.C
   Module      : LIST
   System      : None
   Description : A method for finding an element in a list.
   Modified    : 01/16/2025 DWP Created.
   Notes       :
*/

#include <stdio.h>

#include "list0.h"

/* Function    : LIST_Find
   Description : Retrieves the first list element matching the specified data.
   Inputs      : List                = The list to search.
		 Comparison_Function = A user-defined function that compares a list element to a value.
		    Description : Compares two elements to determine their relationship.
		    Inputs      : Data         = The element to be located.
				  List_Element = The current element in the list.
				  Position     = The zero-based index position of the element in the list.
		    Updates     : Nothing.
		    Outputs     : Nothing.
		    Returns     : Zero if the objects match, non-zero otherwise.
		 Data                = The data to be located in the list.
		 List_Element        = The list element that matches the data, or NULL if the data is not in the list.
		 Position            = The position of the matching element in the list.
   Updates     : Nothing.
   Outputs     : List_Element = The list element that matches the specified value.
		 Position = The 0-based index position of the element in the list.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 01/16/2025 DWP Initial coding.
   Notes       :
*/

int LIST_Find(LIST List, int (* Comparison_Function)(void *List_Element, void *Data, CARDINAL_32 Position), void *Data, void **List_Element, CARDINAL_32 *Position) {

   _LIST *      list_descriptor;
   _LIST_NODE * list_node;
   CARDINAL_32  position;
   int          result = LIST_EOLST;

   /* Validate the parameters.  Continue only if it is valid. */

   if (List == NULL || Comparison_Function == NULL || Data == NULL || List_Element == NULL || Position == NULL) {

      result = LIST_PARAM;

   }
   else {

      list_descriptor = List;
      position = -1;

      for (list_node = list_descriptor->First_Element; list_node != NULL; list_node = list_node->Next_Element) {
	position += 1;
	if (Comparison_Function(Data, list_node->Data, position) == 0) {
	   result = LIST_NOERR;
	   break;
	}
      }

      *(List_Element) = list_node != NULL ? list_node->Data : NULL;
      *(Position) = list_node != NULL ? position : (CARDINAL_32) -1;
   }

   return (result);

}
