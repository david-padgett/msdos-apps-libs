/* File        : LIST3.C
   Module      : LIST
   System      : None
   Description : A method for retrieving items from a list.
   Modified    : 03/10/92 DWP Created.
   Notes       :
*/

#include <stdio.h>

#include "list0.h"

/* Function    : LIST_Retrieve
   Description : Retrieves an item from a list.
   Inputs      : List     = The list to retrieve an item from.
                 Position = The position of the item to be retrieved.
   Updates     : Nothing.
   Outputs     : Element  = The item which was retrieved from the list.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 03/10/92 DWP Initial coding.
   Notes       :
*/

int LIST_Retrieve(LIST List, CARDINAL_32 Position, void ** Element) {

   _LIST * list_descriptor;
   int     displacement, result;

   /* Validate the parameters 'List' and 'Element'.  Continue only if they are both valid. */

   if ((list_descriptor = List) == NULL || Element == NULL) {

      result = LIST_PARAM;

   }
   else {

      /* Validate the parameter 'Position'.  Continue only if it is valid. */

      if ((Position > list_descriptor->Total_Elements && Position != LIST_NEXT && Position != LIST_LAST) || (Position == LIST_NEXT && list_descriptor->Current_Element_Number == list_descriptor->Total_Elements)) {

         result = LIST_EOLST;

      }
      else {

         /* Adjust the parameter 'Position', if necessary. */

         if (Position == LIST_NEXT) {

            Position = list_descriptor->Current_Element_Number + 1;

         }

         if (Position == LIST_LAST) {

            Position = list_descriptor->Total_Elements;

         }

         /* Attempt to shorten the distance between the item to be retrieved and the current item. */

         if (Position < list_descriptor->Current_Element_Number) {

            if (Position < list_descriptor->Current_Element_Number - Position) {

               list_descriptor->Current_Element = list_descriptor->First_Element;
               list_descriptor->Current_Element_Number = LIST_FIRST;

            }

         }
         else {

            if (list_descriptor->Total_Elements - Position < Position - list_descriptor->Current_Element_Number) {

               list_descriptor->Current_Element = list_descriptor->Last_Element;
               list_descriptor->Current_Element_Number = list_descriptor->Total_Elements;

            }

         }

         /* Locate the item to be retrieved. */

         for (displacement = (Position >= list_descriptor->Current_Element_Number) ? 1 : -1; list_descriptor->Current_Element_Number != Position; list_descriptor->Current_Element_Number += displacement) {

            list_descriptor->Current_Element = (displacement == 1) ? list_descriptor->Current_Element->Next_Element : list_descriptor->Current_Element->Previous_Element;

         }

         result = LIST_NOERR;

      }

   }

   /* Assign the parameter 'Element' to the retrieved item only if no errors occurred. */

   *(Element) = (result == LIST_NOERR) ? list_descriptor->Current_Element->Data : NULL;

   return (result);

}
