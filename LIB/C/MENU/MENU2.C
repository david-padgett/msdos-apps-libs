/* File        : MENU2.C
   Module      : MENU
   System      : None
   Description : A method for constructing lists.
   Modified    : 04/09/92 DWP Created.
   Notes       :
*/

#include <alloc.h>
#include <memory.h>

#include "menu0.h"

/* Function    : _MENU_Construct_List
   Description : Builds the option and description lists.
   Inputs      : List_Values = The values to place in the new list.
   Updates     : Nothing.
   Outputs     : Option_List = The list to initialize.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 04/09/92 DWP Initial coding.
   Notes       :
*/

int _MENU_Construct_List(char * List_Values, LIST * Option_List) {

   char *      list_element;
   CARDINAL_16 i, maximum_text_string_length, text_string_length;
   int         result;

   /* Determine the length of the longest menu option. */

   for (i = 0, text_string_length = 0, maximum_text_string_length = 0; i <= 32767 && memcmp(&(List_Values[i]), MENU_END_OF_TEXT, 2) != 0; i++) {

      if (memcmp(&(List_Values[i]), MENU_END_OF_OPTION, 2) != 0) {

         text_string_length++;

      }
      else {

         if (maximum_text_string_length < text_string_length) {

            maximum_text_string_length = text_string_length;

         }

         text_string_length = 0;
         i++;

      }

   }

   /* Allocate a temporary string as large as the longest menu option.  Continue only if the allocation is successful. */

   if (i > 32767 || (list_element = malloc(++maximum_text_string_length)) == NULL) {

      result = MENU_NOMEM;

   }
   else {

      /* Build the list.  If an error occurs while building the list, abort the process. */

      setmem(list_element, maximum_text_string_length, 0);
      result = LIST_Constructor(maximum_text_string_length, Option_List);

      for (i = 0; result == LIST_NOERR && memcmp(List_Values, MENU_END_OF_TEXT, 2) != 0; List_Values++) {

         if (memcmp(List_Values, MENU_END_OF_OPTION, 2) != 0) {

            list_element[i++] = *(List_Values);

         }
         else {

            result = LIST_Insert(list_element, LIST_LAST, *(Option_List));
            setmem(list_element, i, 0);
            i = 0;
            List_Values++;

         }

      }

      free(list_element);
      result = (result == LIST_NOERR) ? MENU_NOERR : MENU_EXTRN;

   }

   return (result);

}
