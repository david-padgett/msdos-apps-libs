/* File        : COMM1.C
   Module      : COMM
   System      :
   Description :
   Modified    : 03/30/91 DWP Created.
*/

#include <conio.h>
#include <errno.h>

#include "kb\kb.h"
#include "menu\menu.h"
#include "text\text.h"

/* Function    : bgi_interface_function
   Description : The function used by the MENU module to interface with the
                 Borland Graphics Interface package.
   Expects     : activity = The activity to perform, [MENU_ACTIVATE |
                            MENU_DEACTIVATE | MENU_OUTPUT |
                            MENU_PROCESS_KEY].
                 options  = A list containing the options for a menu.  This
                            parameter should only be used when the activity
                            being performed is MENU_ACTIVATE.
                 window   = The window the menu is being displayed in.
                 text     = The text to be printed.  This parameter should
                            only be used when the activity being performed is
                            MENU_OUTPUT.
   Returns     : Always returns zero.
   Modified    : 01/10/91 DWP Initial coding.
   Notes       :
*/
INTEGER_16 bgi_interface_function(CARDINAL_16 activity, void *data, void *parameter_list) {
   TEXT        *text;
   CARDINAL_16 key;
   INTEGER_16  result = EZERO;

   if (activity == MENU_PROCESS_KEY) {
      key = *((CARDINAL_16 *) data);
   }
   else {
      text = (TEXT *) data;
   }

   switch (activity) {
      case MENU_ACTIVATE    :
                              break;
      case MENU_DEACTIVATE  :
                              break;

                              /* User defined output. */

      case MENU_OUTPUT      : textattr(TEXT_retrieve_color(text));
                              gotoxy(TEXT_retrieve_column(text), TEXT_retrieve_row(text));
                              cprintf(TEXT_retrieve_text(text));
                              TEXT_modify_column(text, wherex());
                              TEXT_modify_row(text, wherey());
                              break;

                              /* User defined keys. */

      case MENU_PROCESS_KEY : if (key == KB_LEFT || key == KB_RIGHT) {
                                 result = key;
                              }
                              else {
                                 if (key > 0) {
                                     putchar('');
                                 }
                                 if (parameter_list != NULL) {
                                    printf("");
                                 }
                              }
                              break;
   }

   return (result);
}

/* Procedure   : COMM_main
   Description :
   Expects     :
   Returns     : Nothing.
   Modified    : 03/30/91 DWP Initial coding.
   Notes       :
*/
void COMM_main(void) {
   MENU        main_menu, file_menu, dial_menu, transfer_menu, configure_menu, help_menu;
   char        *main_options_list[] = {"File", "Dial", "Transfer", "Configure", "Help", NULL};
   char        *main_descriptions_list[] = {"", "", "", "", "", NULL};
   CARDINAL_16 main_quick_pick_list[] = {0x2166, 0x2064, 0x1474, 0x2e63, 0x2368, 0};
   char        *file_options_list[] = {"Open", "Save", "Print", "Exit", NULL};
   char        *file_descriptions_list[] = {"", "", "", "", NULL};
   CARDINAL_16 file_quick_pick_list[] = {0, 0, 0, 0, 0};
   char        *dial_options_list[] = {"From List", "Manual", "Disconnect", NULL};
   char        *dial_descriptions_list[] = {"", "", "", NULL};
   CARDINAL_16 dial_quick_pick_list[] = {0, 0, 0};
   char        *transfer_options_list[] = {"Send", "Receive", NULL};
   char        *transfer_descriptions_list[] = {"", "", NULL};
   CARDINAL_16 transfer_quick_pick_list[] = {0, 0, 0};
   char        *configure_options_list[] = {"Baud", "Parity", "Data Bits", "Stop Bits", NULL};
   char        *configure_descriptions_list[] = {"", "", "", "", NULL};
   CARDINAL_16 configure_quick_pick_list[] = {0, 0, 0, 0, 0};
   char        *help_options_list[] = {"Topic", "Index", NULL};
   char        *help_descriptions_list[] = {"", "", NULL};
   CARDINAL_16 help_quick_pick_list[] = {0, 0, 0};
   INTEGER_16  main_option, file_option, dial_option, transfer_option, configure_option, help_option, i, result;
   BOOLEAN     exit_flag;

   clrscr();

   MENU_Constructor(&main_menu, main_options_list, NULL, 1, 1, (BLACK << 4) | LIGHTCYAN, (BLACK << 4) | LIGHTRED, (LIGHTGRAY << 4) | BLACK, main_descriptions_list, NULL, 25, 1, (BLACK << 4) | YELLOW, main_quick_pick_list, 0, 0, 0, bgi_interface_function);
   MENU_Constructor(&file_menu, file_options_list, NULL, 3, 1, (BLACK << 4) | LIGHTCYAN, (BLACK << 4) | LIGHTRED, (LIGHTGRAY << 4) | BLACK, file_descriptions_list, NULL, 25, 1, (BLACK << 4) | YELLOW, file_quick_pick_list, 0, 0, 0, bgi_interface_function);
   MENU_Constructor(&dial_menu, dial_options_list, NULL, 3, 6, (BLACK << 4) | LIGHTCYAN, (BLACK << 4) | LIGHTRED, (LIGHTGRAY << 4) | BLACK, dial_descriptions_list, NULL, 25, 1, (BLACK << 4) | YELLOW, dial_quick_pick_list, 0, 0, 0, bgi_interface_function);
   MENU_Constructor(&transfer_menu, transfer_options_list, NULL, 3, 11, (BLACK << 4) | LIGHTCYAN, (BLACK << 4) | LIGHTRED, (LIGHTGRAY << 4) | BLACK, transfer_descriptions_list, NULL, 25, 1, (BLACK << 4) | YELLOW, transfer_quick_pick_list, 0, 0, 0, bgi_interface_function);
   MENU_Constructor(&configure_menu, configure_options_list, NULL, 3, 20, (BLACK << 4) | LIGHTCYAN, (BLACK << 4) | LIGHTRED, (LIGHTGRAY << 4) | BLACK, configure_descriptions_list, NULL, 25, 1, (BLACK << 4) | YELLOW, configure_quick_pick_list, 0, 0, 0, bgi_interface_function);
   MENU_Constructor(&help_menu, help_options_list, NULL, 3, 30, (BLACK << 4) | LIGHTCYAN, (BLACK << 4) | LIGHTRED, (LIGHTGRAY << 4) | BLACK, help_descriptions_list, NULL, 25, 1, (BLACK << 4) | YELLOW, help_quick_pick_list, 0, 0, 0, bgi_interface_function);

   main_option = file_option = dial_option = transfer_option = configure_option = help_option = 0;
   result = EZERO;

   for (exit_flag = FALSE; !exit_flag;) {

      for (i = 3; i <= 25; i++) {
         gotoxy(1, i);
         clreol();
      }

      MENU_modify_default_option(&main_menu, main_option);

      if (result == EZERO) {
         MENU_horizontal(&main_menu, &main_option, NULL);
      }
      switch (main_option) {
         case 0  : for (file_option = MENU_retrieve_default_option(&file_menu); file_option != -1;) {

                      MENU_modify_default_option(&file_menu, file_option);
                      result = MENU_vertical(&file_menu, &file_option, NULL);

                      switch (file_option) {
                         case 0 :
                                  break;
                         case 1 :
                                  break;
                         case 2 :
                                  break;
                         case 3 :
                                  break;
                      }
                   }
                   break;

         case 1  : for (dial_option = MENU_retrieve_default_option(&dial_menu); dial_option != -1;) {

                      MENU_modify_default_option(&dial_menu, dial_option);
                      result = MENU_vertical(&dial_menu, &dial_option, NULL);

                      switch (dial_option) {
                         case 0 :
                                  break;
                         case 1 :
                                  break;
                         case 2 :
                                  break;
                      }
                   }
                   break;

         case 2  : for (transfer_option = MENU_retrieve_default_option(&transfer_menu); transfer_option != -1;) {

                      MENU_modify_default_option(&transfer_menu, transfer_option);
                      result = MENU_vertical(&transfer_menu, &transfer_option, NULL);

                      switch (transfer_option) {
                         case 0 :
                                  break;
                         case 1 :
                                  break;
                      }
                   }
                   break;

         case 3  : for (configure_option = MENU_retrieve_default_option(&configure_menu); configure_option != -1;) {

                      MENU_modify_default_option(&configure_menu, configure_option);
                      result = MENU_vertical(&configure_menu, &configure_option, NULL);

                      switch (configure_option) {
                         case 0 :
                                  break;
                         case 1 :
                                  break;
                         case 2 :
                                  break;
                         case 3 :
                                  break;
                      }
                   }
                   break;

         case 4  : for (help_option = MENU_retrieve_default_option(&help_menu); help_option != -1;) {

                      MENU_modify_default_option(&help_menu, help_option);
                      result = MENU_vertical(&help_menu, &help_option, NULL);

                      switch (help_option) {
                         case 0 :
                                  break;
                         case 1 :
                                  break;
                      }
                   }
                   break;

         case -1 : exit_flag = TRUE;
      }

      switch (result) {
         case KB_LEFT  : main_option = (main_option == 0) ? 4 : main_option - 1;
                         break;
         case KB_RIGHT : main_option = (main_option == 4) ? 0 : main_option + 1;
                         break;
      }
   }

   MENU_Destructor(&main_menu);
   MENU_Destructor(&file_menu);
   MENU_Destructor(&dial_menu);
   MENU_Destructor(&transfer_menu);
   MENU_Destructor(&configure_menu);
   MENU_Destructor(&help_menu);
}

/* Function    : main
   Description : This function is for testing purposes only and should be
                 removed when the module is finished.
   Expects     : Nothing.
   Returns     : Always returns a value of zero.
   Modified    : 03/30/91 DWP Initial coding.
   Notes       :
*/
int main(void) {

   COMM_main();

   return (0);
}