/* File        : MENU2A.C
   Module      : MENU
   System      : None
   Description : A method for displaying a list of menu options.
   Modified    : 04/06/92 DWP Created.
   Notes       :
*/

#include "menu0.h"

/* Function    : _MENU_Display_Menu
   Description : Displays a menu.
   Inputs      : Menu_Descriptor = The menu to display.
   Updates     : Nothing.
   Outputs     : Nothing.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 04/06/92 DWP Initial coding.
   Notes       :
*/

int _MENU_Display_Menu(_MENU * Menu_Descriptor) {

   CARDINAL_32 total_menu_options;
   CARDINAL_16 current_menu_option;
   int         result;

   if (LIST_Size(Menu_Descriptor->Option_List, &total_menu_options) != LIST_NOERR) {

      result = MENU_EXTRN;

   }
   else {

      /* Print the menu options. */

      for (current_menu_option = 1, result = MENU_NOERR; result == MENU_NOERR && current_menu_option <= total_menu_options; current_menu_option++) {

         result = _MENU_Display_Option(Menu_Descriptor, current_menu_option, MENU_NORMALIZE_TEXT);

      }

   }

   return (result);

}

