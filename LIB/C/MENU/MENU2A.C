/* File        : MENU2A.C
   Module      : MENU
   System      : None
   Description : A method for constructing lists.
   Modified    : 04/09/92 DWP Created.
   Notes       :
*/

#include <memory.h>

#include "menu0.h"

/* Function    : _MENU_Construct_Coordinates_List
   Description : Builds the option coordinates list.
   Inputs      : Menu_Descriptor = The menu being initialized.
   Updates     : Nothing.
   Outputs     : Nothing.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 04/09/92 DWP Initial coding.
   Notes       :
*/

int _MENU_Construct_Coordinates_List(_MENU * Menu_Descriptor) {

   _MENU_OPTION_COORDINATES option_coordinates;
   CARDINAL_32              current_option, total_options;
   CARDINAL_16              i;
   char *                   current_option_text;
   int                      result;

   /* Initialize the coordinates record. */

   option_coordinates.Row = 0;
   option_coordinates.Column = 0;

   /* Initialize the screen coordinates list and place the first coordinates entry into the list. */

   result = LIST_Constructor(sizeof(_MENU_OPTION_COORDINATES), &(Menu_Descriptor->Option_Screen_Coordinates_List)) || LIST_Size(Menu_Descriptor->Option_List, &total_options);

   if (result == LIST_NOERR) {

      result = LIST_Insert(&option_coordinates, LIST_LAST, Menu_Descriptor->Option_Screen_Coordinates_List);

   }

   /* Parse the options list. */

   for (current_option = 1; result == LIST_NOERR && current_option < total_options; current_option++) {

      /* Get the next menu option in the list. */

      if ((result = LIST_Retrieve(Menu_Descriptor->Option_List, current_option, (void **) &current_option_text)) == LIST_NOERR) {

         /* Process the current menu option. */

         for (i = 0; i <= 32767 && current_option_text[i] != '\0'; i++) {

            /* Adjust the row if a vertical tab control sequence was encountered. */

            if (memcmp(&(current_option_text[i]), MENU_VERTICAL_TAB, 2) == 0) {

               i += MENU_CONTROL_SEQUENCE_LENGTH;
               option_coordinates.Row += (INTEGER_16) current_option_text[i];
               option_coordinates.Column = 0;

            }
            else {


               /* Adjust the column if a horizontal tab control sequence was encountered. */

               if (memcmp(&(current_option_text[i]), MENU_HORIZONTAL_TAB, 2) == 0) {

                  i += MENU_CONTROL_SEQUENCE_LENGTH;
                  option_coordinates.Column += (INTEGER_16) current_option_text[i];

               }
               else {

                  if (memcmp(&(current_option_text[i]), MENU_PRIMARY_COLOR, 2) == 0 || memcmp(&(current_option_text[i]), MENU_SECONDARY_COLOR, 2) == 0) {

                     i+= MENU_CONTROL_SEQUENCE_LENGTH - 1;

                  }
                  else {

                     option_coordinates.Column++;

                  }

               }

            }

         }

         /* Place the new coordinate data in the coordinate list. */

         result = LIST_Insert(&option_coordinates, LIST_LAST, Menu_Descriptor->Option_Screen_Coordinates_List);

      }

   }

   result = (result == LIST_NOERR) ? MENU_NOERR : MENU_EXTRN;

   return (result);

}
