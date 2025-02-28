/* File        : LIST5A.C
   Module      : LIST
   System      : None
   Description : A method for determining the most recently accessed element of a list.
   Modified    : 04/06/92 DWP Created.
   Notes       :
*/

#include <stdio.h>

#include "list0.h"

/* Function    : LIST_Current
   Description : Retrieves the position of the most recently accessed element of a list.
   Inputs      : List     = The list to inspect.
   Updates     : Nothing.
   Outputs     : Position = The position of the most recently accessed element of the list.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 04/06/92 DWP Initial coding.
   Notes       :
*/

int LIST_Current(LIST List, CARDINAL_32 * Position) {

   _LIST * list_descriptor;
   int     result;

   /* Validate the parameter 'List'.  Continue only if it is valid. */

   if (List == NULL) {

      result = LIST_PARAM;

   }
   else {

      /* Place the number of elements in the list into the parameter 'Size'. */

      list_descriptor = List;
      *(Position) = list_descriptor->Current_Element_Number;
      result = LIST_NOERR;

   }

   return (result);

}
