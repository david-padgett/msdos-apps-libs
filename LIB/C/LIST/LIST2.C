/* File        : LIST2.C
   Module      : LIST
   System      : None
   Description : A method for adding elements to a list.
   Modified    : 03/09/92 DWP Created.
   Notes       :
*/

#include <alloc.h>
#include <memory.h>
#include <stdio.h>

#include "list0.h"

/* Function    : LIST_Insert
   Description : Inserts an item into a list.
   Inputs      : Element  = The item to add to the list.
                 Position = The position in which to insert the item into the list.
   Updates     : List     = The list to add an item to.
   Outputs     : Nothing.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 03/09/92 DWP Initial coding.
   Notes       :
*/

int LIST_Insert(void * Element, CARDINAL_32 Position, LIST List) {

   _LIST *      list_descriptor;
   _LIST_NODE * list_node;
   void *       list_element;
   int          result;

   /* Verify the 'List' and 'Element' parameters.  Continue only if they are both valid. */

   if ((list_descriptor = List) == NULL || Element == NULL) {

      result = LIST_PARAM;

   }
   else {

      /* Allocate memory for the new list node and for the element storage buffer.  Continue only of both allocations succeed. */

      if ((list_node = malloc(sizeof(_LIST_NODE))) == NULL || (list_node->Data = malloc(list_descriptor->Element_Size)) == NULL) {

         if (list_node != NULL) {

            free(list_node);

         }

         result = LIST_NOMEM;

      }
      else {

         result = LIST_NOERR;

         /* Adjust the parameter 'Position', if necessary.  This reduces the complexity of the actual insertion code. */

         if (list_descriptor->Total_Elements == 0 || (Position == LIST_CURRENT && list_descriptor->Current_Element_Number == LIST_FIRST)) {

            Position = LIST_FIRST;

         }
         else {

            if (list_descriptor->Total_Elements < Position || (Position == LIST_CURRENT && list_descriptor->Current_Element_Number == LIST_LAST)) {

               Position = LIST_LAST;

            }
            else {

               if (Position != LIST_CURRENT && Position != LIST_FIRST && Position != LIST_LAST) {

                  result = LIST_Retrieve(List, Position, &list_element);

               }

            }

         }

         /* Insert the new item only if no errors occurred during the possible call to LIST_Retrieve(). */

         if (result == LIST_NOERR || result == LIST_EOLST) {

            memcpy(list_node->Data, Element, list_descriptor->Element_Size);
            (list_descriptor->Total_Elements)++;

            switch (Position) {

               /* Insert the new item into the current position in the list. */

               case LIST_CURRENT :

                  list_node->Previous_Element = list_descriptor->Current_Element->Previous_Element;
                  list_node->Previous_Element->Next_Element = list_node;
                  list_node->Next_Element = list_descriptor->Current_Element;
                  list_node->Next_Element->Previous_Element = list_node;
                  list_descriptor->Current_Element = list_node;
                  break;

               /* Insert the new item at the beginning of the list. */

               case LIST_FIRST :

                  if (list_descriptor->First_Element != NULL) {

                     list_descriptor->First_Element->Previous_Element = list_node;

                  }

                  list_node->Previous_Element = NULL;
                  list_node->Next_Element = list_descriptor->First_Element;
                  list_descriptor->First_Element = list_node;

                  if (list_descriptor->Last_Element == NULL) {

                     list_descriptor->Last_Element = list_node;

                  }

                  list_descriptor->Current_Element_Number = LIST_FIRST;
                  break;

               /* Insert the new item at the end of the list. */

               case LIST_LAST :

                  list_descriptor->Last_Element->Next_Element = list_node;
                  list_node->Previous_Element = list_descriptor->Last_Element;
                  list_node->Next_Element = NULL;
                  list_descriptor->Last_Element = list_node;
                  list_descriptor->Current_Element_Number = list_descriptor->Total_Elements;
                  break;

            }

            /* Make the new item the current, or last referenced, item in the list. */

            list_descriptor->Current_Element = list_node;

         }

      }

   }

   return (result);

}
