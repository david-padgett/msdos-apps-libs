/* File        : LIST5.C
   Module      : LIST
   System      : None
   Description : A method for determining the size of a list.
   Modified    : 04/06/92 DWP Created.
   Notes       :
*/

#include <stdio.h>

#include "list0.h"

/* Function    : LIST_Size
   Description : Retrieves the number of elements in a list.
   Inputs      : List = The list to inspect.
   Updates     : Nothing.
   Outputs     : Size = The total number of elements in the list.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 04/02/92 DWP Initial coding.
   Notes       :
*/

int LIST_Size(LIST List, CARDINAL_32 * Size) {

   _LIST * list_descriptor;
   int     result;

   /* Validate the parameter 'List'.  Continue only if it is valid. */

   if (List == NULL) {

      result = LIST_PARAM;

   }
   else {

      /* Place the number of elements in the list into the parameter 'Size'. */

      list_descriptor = List;
      *(Size) = list_descriptor->Total_Elements;
      result = LIST_NOERR;

   }

   return (result);

}
