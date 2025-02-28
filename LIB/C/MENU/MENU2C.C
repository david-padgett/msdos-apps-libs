/* File        : MENU2B.C
   Module      : MENU
   System      : None
   Description : A method for displaying menu options.
   Modified    : 04/07/92 DWP Created.
   Notes       :
*/

#include <memory.h>

#include "menu0.h"

/* Function    : _MENU_Display_Option
   Description : Displays the currently selected option of a menu.
   Inputs      : Menu_Descriptor = The menu to manipulate.
                 Option          = The option to display.
                 Display_Type    = Indicates the display attribute of the menu option to be displayed.
   Updates     : Nothing.
   Outputs     : Nothing.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    :
   Notes       :
*/

int _MENU_Display_Option(_MENU * Menu_Descriptor, CARDINAL_16 Option, _MENU_OPTION_DISPLAY_TYPES Display_Type) {

   _MENU_OPTION_COORDINATES * option_coordinates;
   char *                     current_option_text;
   CARDINAL_16                i, primary_color, secondary_color;
   int                        result;

   /* Validate the parameters.  Continue only if they are all valid. */

   if (Menu_Descriptor == NULL || Option == 0 || (Display_Type != MENU_NORMALIZE_TEXT &&  Display_Type != MENU_HIGHLIGHT_TEXT)) {

      result = MENU_PARAM;

   }
   else {

      /* Retrieve the currently highlighted option.  Continue only if no errors occurred. */

      if (LIST_Retrieve(Menu_Descriptor->Option_List, Option, (void **) &current_option_text) != LIST_NOERR || LIST_Retrieve(Menu_Descriptor->Option_Screen_Coordinates_List, Option, (void **) &option_coordinates) != LIST_NOERR) {

         result = MENU_EXTRN;

      }
      else {

         /* Position the cursor and set the correct text color attribute. */

         if (TEXT_Set_Cursor_Position(Menu_Descriptor->Option_Row + option_coordinates->Row, Menu_Descriptor->Option_Column + option_coordinates->Column, Menu_Descriptor->Text_Descriptor) != TEXT_NOERR || TEXT_Set_Text_Color((Display_Type == MENU_NORMALIZE_TEXT) ? Menu_Descriptor->Option_Primary_Color : Menu_Descriptor->Option_Highlight_Primary_Color, Menu_Descriptor->Text_Descriptor) != TEXT_NOERR) {

            result = MENU_EXTRN;

         }
         else {

            /* Print the menu option. */

            for (i = 0; i < 32767 && current_option_text[i] != '\0';) {

               if (memcmp(&(current_option_text[i]), MENU_PRIMARY_COLOR, 2) == 0 || memcmp(&(current_option_text[i]), MENU_SECONDARY_COLOR, 2) == 0) {

                  if (Display_Type == MENU_NORMALIZE_TEXT) {

                     primary_color = Menu_Descriptor->Option_Primary_Color;
                     secondary_color = Menu_Descriptor->Option_Secondary_Color;

                  }
                  else {

                     primary_color = Menu_Descriptor->Option_Highlight_Primary_Color;
                     secondary_color = Menu_Descriptor->Option_Highlight_Secondary_Color;

                  }

                  if (TEXT_Set_Text_Color((memcmp(&(current_option_text[i]), MENU_PRIMARY_COLOR, 2) == 0) ? primary_color : secondary_color, Menu_Descriptor->Text_Descriptor) != TEXT_NOERR) {

                     result = MENU_EXTRN;
                     break;

                  }

                  i += MENU_CONTROL_SEQUENCE_LENGTH;

               }
               else {

                  if (memcmp(&(current_option_text[i]), MENU_VERTICAL_TAB, 2) == 0 || memcmp(&(current_option_text[i]), MENU_HORIZONTAL_TAB, 2) == 0) {

                     i += MENU_CONTROL_SEQUENCE_LENGTH + sizeof(char);

                  }
                  else {

                     if (TEXT_Print_Character(current_option_text[i++], Menu_Descriptor->Text_Descriptor) != TEXT_NOERR) {

                        result = MENU_EXTRN;
                        break;

                     }

                  }

               }

            }

            Menu_Descriptor->Current_Option = Option;
            result = MENU_NOERR;

         }

      }

   }

   return (result);

}