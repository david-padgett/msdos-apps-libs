/* File        : TEST.C
   Module      : MENU
   System      : None
   Description : A test driver for the MENU module.
   Modified    : 03/19/92 DWP Created.
   Notes       :
*/

#include <conio.h>
#include <stdio.h>

#include "Text_Int\text_int.h"
#include "menu.h"

/* Function    : main
   Description : The main entry point for the test driver program.
   Inputs      : Nothing.
   Updates     : Nothing.
   Outputs     : Nothing.
   Returns     : Always returns a value of zero.
   Modified    : 03/19/92 DWP Initial coding.
   Notes       :
*/

int main(int argc, char * argv[]) {

   MENU        menu;
   TEXT        text;
   char *      menu1 = "Option."     MENU_SECONDARY_COLOR "1 " MENU_PRIMARY_COLOR MENU_VERTICAL_TAB "\x1" MENU_END_OF_OPTION
                       "Option.."    MENU_SECONDARY_COLOR "2 " MENU_PRIMARY_COLOR MENU_VERTICAL_TAB "\x1" MENU_END_OF_OPTION
                       "Option..."   MENU_SECONDARY_COLOR "3 " MENU_PRIMARY_COLOR MENU_VERTICAL_TAB "\x1" MENU_END_OF_OPTION
                       "Option...."  MENU_SECONDARY_COLOR "4 " MENU_PRIMARY_COLOR MENU_VERTICAL_TAB "\x1" MENU_END_OF_OPTION
                       "Option....." MENU_SECONDARY_COLOR "5 " MENU_PRIMARY_COLOR MENU_END_OF_OPTION MENU_END_OF_TEXT;
   char *      menu2 = "Choice " MENU_SECONDARY_COLOR "1" MENU_PRIMARY_COLOR MENU_HORIZONTAL_TAB "\x1" MENU_END_OF_OPTION
                       "Choice " MENU_SECONDARY_COLOR "2" MENU_PRIMARY_COLOR MENU_HORIZONTAL_TAB "\x1" MENU_END_OF_OPTION
                       "Choice " MENU_SECONDARY_COLOR "3" MENU_PRIMARY_COLOR MENU_HORIZONTAL_TAB "\x1" MENU_END_OF_OPTION
                       "Choice " MENU_SECONDARY_COLOR "4" MENU_PRIMARY_COLOR MENU_HORIZONTAL_TAB "\x1" MENU_END_OF_OPTION
                       "Choice " MENU_SECONDARY_COLOR "5" MENU_PRIMARY_COLOR MENU_END_OF_OPTION MENU_END_OF_TEXT;
   char *      desc1 = "desc.1 "     MENU_END_OF_OPTION
                       "desc..2 "    MENU_END_OF_OPTION
                       "desc...3 "   MENU_END_OF_OPTION
                       "desc....4 "  MENU_END_OF_OPTION
                       "desc.....5 " MENU_END_OF_OPTION MENU_END_OF_TEXT;

   CARDINAL_16 selected_option = 1;

   if (argc == 1 && argv[1] == NULL) {

      if (TEXT_Constructor(BGI_GotoYX, BGI_GotoY, BGI_GotoX, BGI_WhereY, BGI_WhereX, BGI_TextAttr, BGI_GetTextInfo, BGI_ClrScr, BGI_Print_Character, BGI_Print_String, &text) == TEXT_NOERR) {

         if (TEXT_Clear_Text_Window(text) == TEXT_NOERR) {

            MENU_Constructor(menu1, 5, 5, LIGHTCYAN, LIGHTRED, 0x70, 0x7c, desc1, 20, 5, WHITE, GREEN, text, &menu);
            MENU_Display(menu, selected_option);
            MENU_Destructor(&menu);

            MENU_Constructor(menu2, 20, 5, LIGHTCYAN, LIGHTRED, 0x70, 0x7c, desc1, 20, 5, WHITE, GREEN, text, &menu);
            MENU_Display(menu, selected_option);
            MENU_Destructor(&menu);

         }

      }
   }

   return (0);

}