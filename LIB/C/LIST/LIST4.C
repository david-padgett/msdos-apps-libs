/* File        : LIST4.C
   Module      : LIST
   System      : None
   Description : A method for removing items from a list.
   Modified    : 03/10/92 DWP Created.
   Notes       :
*/

#include <alloc.h>
#include <memory.h>
#include <stdio.h>

#include "list0.h"

/* Function    : LIST_Delete
   Description : Removes an item from a list.
   Inputs      : Position = The position of the item to be deleted.
   Updates     : List     = The list to remove an item from.
   Outputs     : Element  = The item which was removed from the list.  If this parameter is initially NULL, then the deleted item
                            is not copied into this parameter.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 03/10/92 DWP Initial coding.
   Notes       :
*/

int LIST_Delete(CARDINAL_32 Position, LIST List, void * Element) {

   _LIST *      list_descriptor;
   _LIST_NODE * list_node;
   void *       list_element;
   int          result;

   /* Validate the parameters 'List', 'Position', and 'Element'.  Continue only if all three are valid. */

   if ((list_descriptor = List) == NULL || list_descriptor->Total_Elements == 0 || (Position != LIST_LAST && Position > list_descriptor->Total_Elements)) {

      result = LIST_PARAM;

   }
   else {

      result = LIST_NOERR;

      /* Adjust the parameter 'Position', if necessary. */

      if (list_descriptor->Total_Elements == 1 || (Position == LIST_CURRENT && list_descriptor->Current_Element_Number == LIST_FIRST)) {

         Position = LIST_FIRST;

      }
      else {

         if (Position == LIST_CURRENT && list_descriptor->Current_Element_Number == list_descriptor->Total_Elements) {

            Position = LIST_LAST;

         }
         else {

            if (Position != LIST_CURRENT && Position != LIST_FIRST && Position != LIST_LAST) {

               result = LIST_Retrieve(List, Position, &list_element);
               Position = LIST_CURRENT;

            }

         }

      }

      /* Delete the specified item if no errors occurred during the possible call to LIST_Retrieve(). */

      if (result == LIST_NOERR) {

         switch (Position) {

            /* Delete the item that was last referenced. */

            case LIST_CURRENT :

               list_node = list_descriptor->Current_Element;
               list_node->Previous_Element->Next_Element = list_node->Next_Element;
               list_node->Next_Element->Previous_Element = list_node->Previous_Element;
               break;

            /* Delete the first item in the list. */

            case LIST_FIRST :

               list_node = list_descriptor->First_Element;
               list_descriptor->First_Element = list_node->Next_Element;

               if (list_descriptor->Total_Elements == 1) {

                  list_descriptor->Last_Element =  NULL;

               }
               else {

                  list_node->Next_Element->Previous_Element = NULL;

               }

               break;

            /* Delete the last item in the list. */

            case LIST_LAST :

               list_node = list_descriptor->Last_Element;
               list_descriptor->Last_Element = list_node->Previous_Element;
               list_node->Previous_Element->Next_Element = NULL;
               break;

         }

         /* Decrement the total elements counter and return the data and list node buffers to the heap. */

         (list_descriptor->Total_Elements)--;

         if (Element != NULL) {

            memcpy(Element, list_node->Data, list_descriptor->Element_Size);

         }

         free(list_node->Data);
         free(list_node);

      }

   }

   return (result);

}
