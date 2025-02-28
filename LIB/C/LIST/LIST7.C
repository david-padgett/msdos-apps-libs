/* File        : LIST7.C
   Module      : LIST
   System      : None
   Description : A method for iterating over the elements in a list.
   Modified    : 01/16/2025 DWP Created.
   Notes       :
*/

#include <stdio.h>

#include "list0.h"

/* Function    : LIST_Iterate
   Description : Iterates over the elements in a list.
   Inputs      : List = The list to inspect.
		 Iterator_Function = A user-defined function that is invoked for each element in the list.
		    Description : Performs an action on an element in the list.
		    Inputs      : List_Element = The next element in the list.
				  Data         = User-defined data that augments interaction with the list element.
				  Position     = The position of the element in the list.
		    Updates     : Nothing.
		    Outputs     : Nothing.
		    Returns     : TRUE if iteration should continue, FALSE otherwise.
		 Data                = User-defined data that augments interaction with the list element.
   Updates     : Nothing.
   Outputs     : Nothing.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 01/16/2025 DWP Initial version.
   Notes       :
*/

int LIST_Iterate(LIST List, int (* Iterator_Function)(void *List_Element, void *Data, CARDINAL_32 Position), void *Data) {

   _LIST *      list_descriptor;
   _LIST_NODE * list_node;
   CARDINAL_32  position;
   int          result;

   /* Validate the parameters.  Continue only if it is valid. */

   if (List == NULL || Iterator_Function == NULL) {

      result = LIST_PARAM;

   }
   else {

       // TODO: Implement feature.

       list_descriptor = List;
       result = LIST_NOERR;
      position = -1;

      for (list_node = list_descriptor->First_Element; list_node != NULL; list_node = list_node->Next_Element) {
	position += 1;
	if (Iterator_Function(list_node->Data, Data, position) != 0) {
	   break;
	}
      }

   }

   return (result);

}
