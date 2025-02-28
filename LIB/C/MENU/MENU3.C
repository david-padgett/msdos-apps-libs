/* File        : MENU3.C
   Module      : MENU
   System      : None
   Description : A method for displaying a menu in the vertical direction.
   Modified    : 04/02/92 DWP Created.
   Notes       :
*/

#include <stdio.h>

#include "menu0.h"

/* Function    : MENU_Display
   Description : Displays a menu in the vertical direction.
   Inputs      : Menu            = The menu to display.
                 Selected_Option = The menu option that is currently the default, or highlighted, option.
   Updates     : Nothing.
   Outputs     : Nothing.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 04/02/92 DWP Initial coding.
   Notes       :
*/

int MENU_Display(MENU Menu, CARDINAL_16 Selected_Option) {

   _MENU * menu_descriptor;
   int     result;

   /* Validate the parameter 'Menu'.  Continue only if it is valid. */

   if (Menu == NULL || (menu_descriptor = Menu) == NULL) {

      result = MENU_PARAM;

   }
   else {

      /* Display the menu, if necessary.  Continue only if no errors occurred. */

      if (menu_descriptor->Status == MENU_ACTIVE) {

         result = MENU_NOERR;

      }
      else {

         if ((result = _MENU_Display_Menu(menu_descriptor)) == MENU_NOERR) {

            menu_descriptor->Status = MENU_ACTIVE;

         }

      }

      if (result == MENU_NOERR) {

         /* Normalize the previously selected option.  */

         if (menu_descriptor->Current_Option != 0 && menu_descriptor->Current_Option != Selected_Option) {

            result = _MENU_Display_Option(menu_descriptor, menu_descriptor->Current_Option, MENU_NORMALIZE_TEXT);

         }

         /* Highlight the currently selected option. */

         if (result == MENU_NOERR && Selected_Option != 0) {

            result = _MENU_Display_Option(menu_descriptor, Selected_Option, MENU_HIGHLIGHT_TEXT);
            menu_descriptor->Current_Option = Selected_Option;

         }

      }

   }

   return (result);

}
