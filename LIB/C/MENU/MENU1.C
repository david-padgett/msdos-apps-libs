/* File        : MENU1.C
   Module      : MENU
   System      : None
   Description : The constructor and destructor methods for the MENU module.
   Modified    : 07/09/92 DWP Created.
   Notes       :
*/

#include <alloc.h>
#include <memory.h>

#include "menu0.h"

/* Procedure   : MENU_Constructor
   Description : Initializes a menu.
   Inputs      : Option_List                      = A list of menu options.
                 Option_Row                       = The row on which to display the first menu option.
                 Option_Column                    = The starting column on which to display the first menu option.
		 Option_Primary_Color             = The primary color of un-highlighted menu option text.
		 Option_Secondary_Color           = The secondary color of un-highlighted menu option text.
		 Option_Highlight_Primary_Color   = The primary color of highlighted menu option text.
                 Option_Highlight_Secondary_Color = The secondary color of highlighted menu option text.
                 Description_List                 = A list of descriptions of the menu options.
                 Description_Row                  = The row on which to display the first description.
                 Description_Column               = The starting column on which to display the first description.
                 Description_Primary_Color        = The primary color of description text.
                 Description_Secondary_Color      = The secondary color of description text.
                 Text_Descriptor                  = The interface to the CRT.
   Updates     : Nothing.
   Outputs     : Menu                             = The menu to initialize.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 04/09/92 DWP Initial coding.
   Notes       :
*/

int MENU_Constructor(char * Option_List, CARDINAL_16 Option_Row, CARDINAL_16 Option_Column, CARDINAL_16 Option_Primary_Color, CARDINAL_16 Option_Secondary_Color, CARDINAL_16 Option_Highlight_Primary_Color, CARDINAL_16 Option_Highlight_Secondary_Color, char * Description_List, CARDINAL_16 Description_Row, CARDINAL_16 Description_Column, CARDINAL_16 Description_Primary_Color, CARDINAL_16 Description_Secondary_Color, TEXT Text_Descriptor, MENU * Menu) {

   _MENU * menu_descriptor;
   int     result;

   if (Option_List == NULL || Text_Descriptor == NULL || Menu == NULL) {

      result = MENU_PARAM;

   }
   else {

      /* Allocate space for the new menu.  Exit if there is not enough memory. */

      if ((menu_descriptor = malloc(sizeof(_MENU))) == NULL) {

         result = MENU_NOMEM;

      }
      else {

         setmem(menu_descriptor, sizeof(_MENU), 0);

         if ((result = _MENU_Construct_List(Option_List, &(menu_descriptor->Option_List))) != MENU_NOERR || (result = _MENU_Construct_Coordinates_List(menu_descriptor)) != MENU_NOERR || (Description_List != NULL && Description_List[0] != '\0' && (result = _MENU_Construct_List(Description_List, &(menu_descriptor->Description_List))) != MENU_NOERR)) {

            if (MENU_Destructor((MENU *) menu_descriptor) != MENU_NOERR) {

               result = MENU_INTRN;

            }

         }
         else {

            menu_descriptor->Option_Row = Option_Row;
            menu_descriptor->Option_Column = Option_Column;
            menu_descriptor->Option_Primary_Color = Option_Primary_Color;
            menu_descriptor->Option_Secondary_Color = Option_Secondary_Color;
            menu_descriptor->Option_Highlight_Primary_Color = Option_Highlight_Primary_Color;
            menu_descriptor->Option_Highlight_Secondary_Color = Option_Highlight_Secondary_Color;

            menu_descriptor->Description_Row = Description_Row;
            menu_descriptor->Description_Column = Description_Column;
            menu_descriptor->Description_Primary_Color = Description_Primary_Color;
            menu_descriptor->Description_Secondary_Color = Description_Secondary_Color;

            menu_descriptor->Text_Descriptor = Text_Descriptor;

            menu_descriptor->Current_Option = 0;
            menu_descriptor->Status = MENU_INACTIVE;

         }

      }

      *(Menu) = menu_descriptor;

   }

   return (result);

}

/* Procedure   : MENU_Destructor
   Description : Undefines the specified list.
   Inputs      : Nothing.
   Updates     : Menu = The menu to undefine.
   Outputs     : Nothing.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 04/09/92 DWP Initial coding.
   Notes       :
*/

int MENU_Destructor(MENU * Menu) {

   _MENU * menu_descriptor;
   int     result;

   if (Menu == NULL || (menu_descriptor = *(Menu)) == NULL) {

      result = MENU_PARAM;

   }
   else {

      if (LIST_Destructor(&(menu_descriptor->Option_List)) != LIST_NOERR || (menu_descriptor->Description_List != NULL && LIST_Destructor(&(menu_descriptor->Description_List)) != LIST_NOERR) || LIST_Destructor(&(menu_descriptor->Option_Screen_Coordinates_List)) != LIST_NOERR) {

         result = MENU_EXTRN;

      }
      else {

         result = MENU_NOERR;

      }

      free(menu_descriptor);
      *(Menu) = NULL;

   }

   return (result);

}
