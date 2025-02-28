/* File        : LIST1.C
   Module      : LIST
   System      : None
   Description : The constructor and destructor methods for the LIST module.
   Modified    : 03/05/92 DWP Created.
   Notes       :
*/

#include <alloc.h>
#include <stdio.h>

#include "list0.h"

/* Function    : LIST_Constructor
   Description : Initializes an instance of the LIST data type.
   Inputs      : Element_Size = The maximum size of an element in the new list.
   Updates     : Nothing.
   Outputs     : List         = The list to initialize.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 03/05/92 DWP Initial coding.
   Notes       :
*/

int LIST_Constructor(CARDINAL_16 Element_Size, LIST * List) {

   _LIST * list_descriptor;
   int     result;

   /* Validate the parameters 'Element_Size' and 'List'.  Continue only if they are both valid. */

   if (Element_Size == 0 || List == NULL) {

      result = LIST_PARAM;

   }
   else {

      /* Attempt to allocate space for the new list descriptor.  Continue only if the allocation was successful. */

      if ((list_descriptor = malloc(sizeof(_LIST))) == NULL) {

         result = LIST_NOMEM;

      }
      else {

         list_descriptor->Element_Size = Element_Size;
         list_descriptor->First_Element = NULL;
         list_descriptor->Last_Element = NULL;
         list_descriptor->Current_Element = NULL;
         list_descriptor->Current_Element_Number = 0;
         list_descriptor->Total_Elements = 0;

         result = LIST_NOERR;

      }

   }

   /* Assign a value to the output parameter 'List'. */

   *(List) = (result == LIST_NOERR) ? list_descriptor : NULL;

   return (result);

}

/* Function    : LIST_Destructor
   Description : Deactivates an instance of the LIST data type.
   Inputs      : Nothing.
   Updates     : List = The list to deactivate.
   Outputs     : Nothing.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 03/05/92 DWP Initial coding.
   Notes       :
*/

int LIST_Destructor(LIST * List) {

   _LIST * list_descriptor;
   int     result;

   /* Validate the 'List' parameter.  Continue only if it is valid. */

   if ((list_descriptor = *(List)) == NULL) {

      result = LIST_PARAM;

   }
   else {

      /* Delete all of the items in the list. */

      for (result = LIST_NOERR; list_descriptor->Total_Elements > 0 && result == LIST_NOERR;) {

         result = LIST_Delete(LIST_FIRST, list_descriptor, NULL);

      }

      *(List) = NULL;

   }

   return (result);

}
