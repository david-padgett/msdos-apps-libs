/*

   File        : AAI1.C
   Module      : MAIN
   System      : AAI
   Description : The main module for the AAI program.
   Modified    : 08/18/92 DWP Created.
                 02/13/93 DWP Added Display_Length field to variables of type AAI_INPUT_DESCRIPTOR.  Created Winchester Version.
   Notes       :

*/

#include <alloc.h>
#include <conio.h>
#include <ctype.h>
#include <dir.h>
#include <dos.h>
#include <errno.h>
#include <mem.h>
#include <string.h>
#include <time.h>

#include "\Dev\DOS\Lib\Asm\Cursor\cursor.h"
#include "\Dev\DOS\Lib\Asm\KB\kb.h"
#include "\Dev\DOS\Lib\C\Dir\dir.h"
#include "\Dev\DOS\Lib\C\String\string.h"
#include "\Dev\DOS\Lib\C\Text_Int\text_int.h"

#include "aai.h"

/*

   Procedure   : AAI_Initialize_Parameters_List
   Description : Initializes a parameters list.
   Inputs      : Display_Type       = The type of display currently in use.
   Updates     : Nothing.
   Outputs     : Default_Parameters = The parameters list to initialize.
   Returns     : Nothing.
   Modified    : 08/18/92 DWP Initial coding.
   Notes       :

*/

void AAI_Initialize_Parameters_List(AAI_PARAMETERS_LIST * Parameters_List) {

   strcpy(Parameters_List->Default_Parameters.ID, AAI_CONFIG_FILE_TITLE);

   if (Parameters_List->Display_Type != Parameters_List->Default_Parameters.Display_Type) {

      if (Parameters_List->Display_Type_Specified) {

         Parameters_List->Default_Parameters.Display_Type = Parameters_List->Display_Type;

      }
      else {

         Parameters_List->Display_Type = Parameters_List->Default_Parameters.Display_Type;

      }

   }

   Parameters_List->Default_Parameters.Function_Key_Menu_Colors.Primary_Color = (Parameters_List->Display_Type == AAI_COLOR) ? (LIGHTGRAY << 4) | BLACK : (LIGHTGRAY << 4) | BLACK;
   Parameters_List->Default_Parameters.Function_Key_Menu_Colors.Secondary_Color = (Parameters_List->Display_Type == AAI_COLOR) ? (LIGHTGRAY << 4) | RED : (LIGHTGRAY << 4) | BLACK;
   Parameters_List->Default_Parameters.Function_Key_Menu_Colors.Primary_Highlight_Color = (Parameters_List->Display_Type == AAI_COLOR) ? (BLUE << 4) | WHITE : (BLACK << 4) | LIGHTGRAY;
   Parameters_List->Default_Parameters.Function_Key_Menu_Colors.Secondary_Highlight_Color = (Parameters_List->Display_Type == AAI_COLOR) ? (BLUE << 4) | WHITE : (BLACK << 4) | DARKGRAY;

   Parameters_List->Default_Parameters.Main_Menu_Colors.Primary_Color = (Parameters_List->Display_Type == AAI_COLOR) ? (LIGHTGRAY << 4) | BLACK : (LIGHTGRAY << 4) | BLACK;
   Parameters_List->Default_Parameters.Main_Menu_Colors.Secondary_Color = (Parameters_List->Display_Type == AAI_COLOR) ? (LIGHTGRAY << 4) | RED : (LIGHTGRAY << 4) | BLACK;
	Parameters_List->Default_Parameters.Main_Menu_Colors.Primary_Highlight_Color = (Parameters_List->Display_Type == AAI_COLOR) ? (GREEN << 4) | BLACK : (BLACK << 4) | LIGHTGRAY;
   Parameters_List->Default_Parameters.Main_Menu_Colors.Secondary_Highlight_Color = (Parameters_List->Display_Type == AAI_COLOR) ? (GREEN << 4) | RED : (BLACK << 4) | DARKGRAY;

   Parameters_List->Default_Parameters.Sub_Menu_Colors.Primary_Color = (Parameters_List->Display_Type == AAI_COLOR) ? (LIGHTGRAY << 4) | BLACK : (LIGHTGRAY << 4) | BLACK;
   Parameters_List->Default_Parameters.Sub_Menu_Colors.Secondary_Color = (Parameters_List->Display_Type == AAI_COLOR) ? (LIGHTGRAY << 4) | RED : (LIGHTGRAY << 4) | BLACK;
   Parameters_List->Default_Parameters.Sub_Menu_Colors.Primary_Highlight_Color = (Parameters_List->Display_Type == AAI_COLOR) ? (GREEN << 4) | BLACK : (BLACK << 4) | LIGHTGRAY;
   Parameters_List->Default_Parameters.Sub_Menu_Colors.Secondary_Highlight_Color = (Parameters_List->Display_Type == AAI_COLOR) ? (GREEN << 4) | RED : (BLACK << 4) | DARKGRAY;

   Parameters_List->Default_Parameters.Yes_No_Menu_Colors.Primary_Color = (Parameters_List->Display_Type == AAI_COLOR) ? (LIGHTGRAY << 4) | BLACK : (LIGHTGRAY << 4) | BLACK;
   Parameters_List->Default_Parameters.Yes_No_Menu_Colors.Secondary_Color = (Parameters_List->Display_Type == AAI_COLOR) ? (LIGHTGRAY << 4) | RED : (LIGHTGRAY << 4) | BLACK;
   Parameters_List->Default_Parameters.Yes_No_Menu_Colors.Primary_Highlight_Color = (Parameters_List->Display_Type == AAI_COLOR) ? (GREEN << 4) | BLACK : (BLACK << 4) | LIGHTGRAY;
   Parameters_List->Default_Parameters.Yes_No_Menu_Colors.Secondary_Highlight_Color = (Parameters_List->Display_Type == AAI_COLOR) ? (GREEN << 4) | RED : (BLACK << 4) | DARKGRAY;

   Parameters_List->Default_Parameters.Edit_Colors.Primary_Color = (Parameters_List->Display_Type == AAI_COLOR) ? (LIGHTGRAY << 4) | BLACK : (LIGHTGRAY << 4) | BLACK;
   Parameters_List->Default_Parameters.Edit_Colors.Secondary_Color = (Parameters_List->Display_Type == AAI_COLOR) ? (LIGHTGRAY << 4) | RED : (LIGHTGRAY << 4) | BLACK;
   Parameters_List->Default_Parameters.Edit_Colors.Primary_Highlight_Color = (Parameters_List->Display_Type == AAI_COLOR) ? (GREEN << 4) | BLACK : (BLACK << 4) | LIGHTGRAY;
   Parameters_List->Default_Parameters.Edit_Colors.Secondary_Highlight_Color = (Parameters_List->Display_Type == AAI_COLOR) ? (GREEN << 4) | RED : (BLACK << 4) | DARKGRAY;

   if (Parameters_List->Port_No != Parameters_List->Default_Parameters.Port_No) {

      if (Parameters_List->Port_No_Specified) {

         Parameters_List->Default_Parameters.Port_No = Parameters_List->Port_No;

      }
      else {

         Parameters_List->Port_No = Parameters_List->Default_Parameters.Port_No;

      }

   }

}

/*

   Procedure   : AAI_Display_Main_Screen_Text
   Description : Displays the main title screen text.
   Inputs      : Parameters_List  = A record of configuration information.
                 Main_Screen_Text = The text to display.
                 Character_List   = A list of the unique characters in Main_Screen_Text.
                 Attribute_List   = A one-to-one mapping of attributes to characters.  Each byte of this list corresponds to the
                                    character which occupies the same position in Character_List.  The characters in
                 Character_List will be displayed using the attributes found in Attribute_List.
                 Text             = The text object to use when printing characters to the screen.
	Updates     : Nothing.
   Outputs     : Nothing.
   Returns     : Nothing.
   Modified    : 08/18/92 DWP Initial coding.
   Notes       :

*/

void AAI_Display_Main_Screen_Text(char * Main_Screen_Text, char * Character_List, BYTE * Attribute_List, TEXT Text) {

   size_t character_position;
   int    i;
   char   character;

   /*

      Loop until the entire screen has been displayed.

   */

   for (i = 0; (character = Main_Screen_Text[i]) != '\0'; i++) {

      character_position = STRING_CharPos(Character_List, character);
		TEXT_Set_Text_Color((character_position == 0) ? BLACK : (int) Attribute_List[character_position - 1], Text);
      TEXT_Print_Character(character, Text);

   }

}

/*

   Procedure   : AAI_Display_Main_Screen
   Description : Displays the main title screen.
   Inputs      : Parameters_List = A record of configuration information.
   Updates     : Nothing.
   Outputs     : Nothing.
   Returns     : Nothing.
   Modified    : 08/18/92 DWP Initial coding.
   Notes       :

*/

void AAI_Display_Main_Screen(AAI_PARAMETERS_LIST * Parameters_List) {

   TEXT_Set_Text_Color(LIGHTGRAY, Parameters_List->Text);
   TEXT_Clear_Text_Window(Parameters_List->Text);
   TEXT_Set_Text_Color(Parameters_List->Default_Parameters.Main_Menu_Colors.Primary_Color, Parameters_List->Text);
   BGI_ClrEol(NULL);

   TEXT_Set_Cursor_Position(2, 1, Parameters_List->Text);
   AAI_Display_Main_Screen_Text(Parameters_List->Main_Screen_Text, Parameters_List->Main_Screen_Characters, Parameters_List->Main_Screen_Character_Colors, Parameters_List->Text);

   TEXT_Set_Cursor_Position(25, 1, Parameters_List->Text);
   TEXT_Set_Text_Color(Parameters_List->Default_Parameters.Function_Key_Menu_Colors.Primary_Color, Parameters_List->Text);
   BGI_ClrEol(NULL);
   TEXT_Set_Cursor_Position(25, 1, Parameters_List->Text);

}

/*

   Function    : AAI_Process_Sub_Menu
   Description : Processes events that occur while a sub-menu is active.
   Inputs      : Nothing.
   Updates     : Process_Parameters = The parameters list used by this process.
                 Key                = The last key pressed.
	Outputs     : Nothing.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
	Modified    : 08/18/92 DWP Initial coding.

   Notes       :

*/

int AAI_Sub_Menu(void ** Process_Parameters, CARDINAL_16 * Key) {

   AAI_SUB_MENU_PARAMETERS * parameters;
   AAI_MENU_TYPES            i;
   AAI_PROCESS_TYPES         absolute_process;
   CARDINAL_16               position;
   BOOLEAN                   valid_key_flag, process_aborted_flag, process_selected_flag;
   int                       result;

   /*

      Validate the parameters.  Exit if either one is invalid.

   */

	if ((result = AAI_Validate_Parameters(Process_Parameters, Key)) == EZERO) {

		/*

         Initialize the process parameters list for this process.

      */

      if (*(Process_Parameters) == NULL) {

         result = AAI_Allocate_Parameters_List(sizeof(*(parameters)), Process_Parameters);

      }
      else {

         /*

            Perform the main function of this process.

         */

         parameters = *(Process_Parameters);
         AAI_Set_Help_Screen(parameters->Parameters_List, AAI_Help_Index_Key_List[((AAI_MAIN_MENU_PARAMETERS *) parameters->Parameters_List->Process_Descriptor[AAI_MAIN_MENU_PROCESS].Process_Parameters)->Option - 1 + AAI_HELP_FILEM]);

         /*

            Initialize and display the sub-menu, if necessary.

         */

         if (!parameters->Refresh_Flag) {

   			result = PORT_Activate(parameters->Port);

      	}
		   else {

   			if (parameters->Menu == NULL) {

	  				result = EZERO;

	   		}
		   	else {

			   	if ((result = MENU_Destructor(&(parameters->Menu))) == MENU_NOERR) {

				   	result = PORT_Destructor(&(parameters->Port));

   				}

            }

            if (result == 0 && parameters->Total_Options > 0 && (result = PORT_Constructor(parameters->Starting_Row, parameters->Starting_Column, parameters->Height, parameters->Width, PORT_SINGLE_LINE_BORDER, parameters->Colors.Primary_Color, parameters->Colors.Primary_Color, &(parameters->Port))) == PORT_NOERR) {

               if ((result = MENU_Constructor(parameters->Menu_Text, 1, 2, parameters->Colors.Primary_Color, parameters->Colors.Secondary_Color, parameters->Colors.Primary_Highlight_Color, parameters->Colors.Secondary_Highlight_Color, NULL, 0, 0, 0, 0, parameters->Text, &(parameters->Menu))) == MENU_NOERR) {

                  result = MENU_Display(parameters->Menu, parameters->Option);

               }

            }

            parameters->Refresh_Flag = FALSE;

         }

         /*

            Continue only if no errors occurred during initialization and a key was pressed.

         */

         if (result == EZERO && *(Key) != 0) {

            valid_key_flag = TRUE;
            process_selected_flag = (parameters->Total_Options == 0) ? TRUE : FALSE;
            process_aborted_flag = FALSE;

            switch (*(Key)) {

               /*

                  Move the cursor up one line.

               */

               case KB_UP :
               case KB_GRAY_UP :

                  parameters->Option = (parameters->Option > 1) ? parameters->Option - 1 : parameters->Total_Options;
                  break;

					/*

						Move the cursor down one line.

               */

               case KB_DOWN :
               case KB_GRAY_DOWN :

                  parameters->Option = (parameters->Option < parameters->Total_Options) ? parameters->Option + 1 : 1;
                  break;

               /*

                  Move the cursor to the first option in the menu.

               */

               case KB_HOME :
               case KB_GRAY_HOME :

                  parameters->Option = 1;
                  break;

               /*

                  Move the cursor to the last option in the menu.

               */

               case KB_END :
               case KB_GRAY_END :

                  parameters->Option = parameters->Total_Options;
                  break;

               /*

                  Select and activate the currently highlighted option.

               */

               case KB_ENTER :
               case KB_GRAY_ENTER :

						process_selected_flag = TRUE;

                  break;

               /*

                  Close the sub-menu.

               */

               case KB_ESC :

                  process_aborted_flag = TRUE;
                  break;

               default :

                  /*

							Determine if an option was activated via its hot-key.  If so, activate that option.

                  */

                  if ((position = STRING_CharPos(parameters->Menu_Keys_List, toupper((char) (*(Key) % 256)))) > 0) {

                     parameters->Option = position;
							process_selected_flag = TRUE;

                  }
                  else {

                     valid_key_flag = FALSE;

                  }

            }

            /*

               Update the position of the cursor if a valid event occurred.

            */

            if (valid_key_flag) {

               *(Key) = 0;
               result = MENU_Display(parameters->Menu, parameters->Option);
					parameters->Parameters_List->Menu_Characteristics_List[((AAI_MAIN_MENU_PARAMETERS *) parameters->Parameters_List->Process_Descriptor[AAI_MAIN_MENU_PROCESS].Process_Parameters)->Option - 1 + AAI_FILE_MENU].Option = parameters->Option;

				}

            /*

               Hide the sub-menu, if necessary.

            */

            if (process_aborted_flag || process_selected_flag) {

               if ((result = MENU_Destructor(&(parameters->Menu))) == MENU_NOERR) {

                  AAI_Halt_Process(parameters->Parameters_List, AAI_SUB_MENU_PROCESS);
                  result = PORT_Destructor(&(parameters->Port));

               }

               if (process_selected_flag) {

                  AAI_Halt_Process(parameters->Parameters_List, AAI_MAIN_MENU_PROCESS);

						for (i = 1, absolute_process = parameters->Option; i < ((AAI_MAIN_MENU_PARAMETERS *) (parameters->Parameters_List->Process_Descriptor[AAI_MAIN_MENU_PROCESS].Process_Parameters))->Option; i++) {

							absolute_process += strlen(AAI_Menu_Keys_List[AAI_FILE_MENU + i - 1]);

                  }

                  AAI_Activate_Process(parameters->Parameters_List, absolute_process);

               }

               parameters->Parameters_List->Menu_Characteristics_List[((AAI_MAIN_MENU_PARAMETERS *) parameters->Parameters_List->Process_Descriptor[AAI_MAIN_MENU_PROCESS].Process_Parameters)->Option - 1 + AAI_FILE_MENU].Option = parameters->Option;

            }

         }

      }

   }

   return (result);

}

/*

   Function    : AAI_Main_Menu
   Description : Processes events that occur while the main menu is active.
   Inputs      : Nothing.
   Updates     : Process_Parameters = The parameters list used by this process.
                 Key                = The last key pressed.
   Outputs     : Nothing.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 08/18/92 DWP Initial coding.
   Notes       :

*/

int AAI_Main_Menu(void ** Process_Parameters, CARDINAL_16 * Key) {

   AAI_MAIN_MENU_PARAMETERS * parameters;
   CARDINAL_16                position;
   BOOLEAN                    valid_key_flag, option_selected_flag;
   int                        result;

   /*

      Validate the parameters.  Exit if either one is invalid.

   */

   if ((result = AAI_Validate_Parameters(Process_Parameters, Key)) == EZERO) {

      /*

         Initialize the process parameters list for this process.

      */

      if (*(Process_Parameters) == NULL) {

         result = AAI_Allocate_Parameters_List(sizeof(*(parameters)), Process_Parameters);

      }
      else {

         /*

            Perform the main function of this process.

         */

         parameters = *(Process_Parameters);

         if (!parameters->Parameters_List->Process_Descriptor[AAI_SUB_MENU_PROCESS].Process_Active_Flag && !parameters->Parameters_List->Process_Descriptor[AAI_YES_NO_MENU_PROCESS].Process_Active_Flag) {

            AAI_Set_Help_Screen(parameters->Parameters_List, AAI_Help_Index_Key_List[AAI_HELP_MAINM]);

         }

         if (parameters->Menu != NULL) {

            result = (parameters->Exit_Flag) ? -1 : EZERO;

         }
         else {

            window(1, 1, 80, 25);

            if ((result = MENU_Constructor(parameters->Menu_Text, parameters->Starting_Row, parameters->Starting_Column, parameters->Colors.Primary_Color, parameters->Colors.Secondary_Color, parameters->Colors.Primary_Highlight_Color, parameters->Colors.Secondary_Highlight_Color, NULL, 0, 0, BLACK, BLACK, parameters->Text, &(parameters->Menu))) == MENU_NOERR) {

               result = MENU_Display(parameters->Menu, parameters->Option);

            }

         }

			/*

            Continue processing only if no errors occurred during initialization and a key was pressed.

         */

         if (result == EZERO && *(Key) != 0) {

            window(1, 1, 80, 25);
            valid_key_flag = TRUE;
            option_selected_flag = FALSE;

            switch (*(Key)) {

               /*

                  Move the cursor to the left.

					*/

					case KB_LEFT :
               case KB_GRAY_LEFT :
               case KB_SHIFT_TAB :

                  parameters->Option = (parameters->Option > 1) ? parameters->Option - 1 : parameters->Total_Options;

                  if (parameters->Parameters_List->Process_Descriptor[AAI_SUB_MENU_PROCESS].Process_Active_Flag) {

                     option_selected_flag = TRUE;

                  }

                  break;

               /*

                  Move the cursor to the right.

               */

               case KB_RIGHT :
					case KB_GRAY_RIGHT :
               case KB_TAB :

						parameters->Option = (parameters->Option < parameters->Total_Options) ? parameters->Option + 1 : 1;

						if (parameters->Parameters_List->Process_Descriptor[AAI_SUB_MENU_PROCESS].Process_Active_Flag) {

							option_selected_flag = TRUE;

                  }

                  break;

               /*

                  Move the cursor to the first menu option.

               */

               case KB_HOME :
               case KB_GRAY_HOME :

                  parameters->Option = 1;
						break;

					/*

                  Move the cursor to the last menu option.

               */

					case KB_END :
               case KB_GRAY_END :

                  parameters->Option = parameters->Total_Options;
                  break;

               /*

                  Select the currently highlighted option.

               */

               case KB_ENTER :
               case KB_GRAY_ENTER :
               case KB_DOWN :
					case KB_GRAY_DOWN :

						option_selected_flag = TRUE;
                  break;

					default :

                  /*

                     Determine if an option was activated via its hot-key.  If so, activate that option.

                  */

                  if ((position = STRING_CharPos(parameters->Menu_Keys_List, toupper((char) (*(Key) % 256)))) > 0) {

                     parameters->Option = position;

                  }
                  else {

                     valid_key_flag = FALSE;

                  }

            }

            /*

               Update the position of the cursor if a valid event occurred.

            */

            if (valid_key_flag) {

               result = MENU_Display(parameters->Menu, parameters->Option);
               *(Key) = 0;

					if (option_selected_flag) {
/*
						if (parameters->Parameters_List->Menu_Characteristics_List[parameters->Option - 1 + AAI_FILE_MENU].Total_Options == 0) {

						}
						else {
*/
							AAI_Activate_Process(parameters->Parameters_List, AAI_SUB_MENU_PROCESS);
							((AAI_SUB_MENU_PARAMETERS *) parameters->Parameters_List->Process_Descriptor[AAI_SUB_MENU_PROCESS].Process_Parameters)->Menu_Text = parameters->Parameters_List->Menu_Text_List[parameters->Option - 1 + AAI_FILE_MENU];
							((AAI_SUB_MENU_PARAMETERS *) parameters->Parameters_List->Process_Descriptor[AAI_SUB_MENU_PROCESS].Process_Parameters)->Menu_Keys_List = parameters->Parameters_List->Menu_Keys_List[parameters->Option - 1 + AAI_FILE_MENU];
							((AAI_SUB_MENU_PARAMETERS *) parameters->Parameters_List->Process_Descriptor[AAI_SUB_MENU_PROCESS].Process_Parameters)->Starting_Row = parameters->Parameters_List->Menu_Characteristics_List[parameters->Option - 1 + AAI_FILE_MENU].Starting_Row;
							((AAI_SUB_MENU_PARAMETERS *) parameters->Parameters_List->Process_Descriptor[AAI_SUB_MENU_PROCESS].Process_Parameters)->Starting_Column = parameters->Parameters_List->Menu_Characteristics_List[parameters->Option - 1 + AAI_FILE_MENU].Starting_Column;
							((AAI_SUB_MENU_PARAMETERS *) parameters->Parameters_List->Process_Descriptor[AAI_SUB_MENU_PROCESS].Process_Parameters)->Height = parameters->Parameters_List->Menu_Characteristics_List[parameters->Option - 1 + AAI_FILE_MENU].Height;
							((AAI_SUB_MENU_PARAMETERS *) parameters->Parameters_List->Process_Descriptor[AAI_SUB_MENU_PROCESS].Process_Parameters)->Width = parameters->Parameters_List->Menu_Characteristics_List[parameters->Option - 1 + AAI_FILE_MENU].Width;
							((AAI_SUB_MENU_PARAMETERS *) parameters->Parameters_List->Process_Descriptor[AAI_SUB_MENU_PROCESS].Process_Parameters)->Option = parameters->Parameters_List->Menu_Characteristics_List[parameters->Option - 1 + AAI_FILE_MENU].Option;
							((AAI_SUB_MENU_PARAMETERS *) parameters->Parameters_List->Process_Descriptor[AAI_SUB_MENU_PROCESS].Process_Parameters)->Total_Options = parameters->Parameters_List->Menu_Characteristics_List[parameters->Option - 1 + AAI_FILE_MENU].Total_Options;
							((AAI_SUB_MENU_PARAMETERS *) parameters->Parameters_List->Process_Descriptor[AAI_SUB_MENU_PROCESS].Process_Parameters)->Refresh_Flag = TRUE;
/*
						}
*/
					}

            }

			}

      }

   }


   return (result);

}

/*

   Function    : AAI_Function_Key_Menu
   Description : Processes events that occur while the function key menu is active.
	Inputs      : Nothing.
   Updates     : Process_Parameters = The parameters list used by this process.
                 Key                = The last key pressed.
   Outputs     : Nothing.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 08/18/92 DWP Initial coding.
   Notes       :

*/

int AAI_Function_Key_Menu(void ** Process_Parameters, CARDINAL_16 * Key) {

   AAI_FUNCTION_KEY_MENU_PARAMETERS * parameters;
   BOOLEAN                            valid_key_flag, invoke_process_flag;
   char                               str[81];
   int                                i, result;

   /*

      Validate the parameters.  Exit if either one is invalid.

   */

	if ((result = AAI_Validate_Parameters(Process_Parameters, Key)) == EZERO) {

      /*

         Initialize the process parameters list for this process.

      */

      if (*(Process_Parameters) == NULL) {

         result = AAI_Allocate_Parameters_List(sizeof(*(parameters)), Process_Parameters);

      }
      else {

         /*

            Perform the main function of this process.

         */

         parameters = *(Process_Parameters);

			if (parameters->Menu != NULL) {

            result = EZERO;

         }
         else {

            if ((result = MENU_Constructor(parameters->Menu_Text, parameters->Starting_Row, parameters->Starting_Column, parameters->Colors.Primary_Color, parameters->Colors.Secondary_Color, parameters->Colors.Primary_Highlight_Color, parameters->Colors.Secondary_Highlight_Color, NULL, 0, 0, BLACK, BLACK, parameters->Text, &(parameters->Menu))) == MENU_NOERR) {

               /*

                  Display the function keys menu.  Continue only if no errors occurred.

               */

               result = MENU_Display(parameters->Menu, 0);

            }

         }

         /*

				Hide all function keys except F1 and ESC if the edit process is currently active.

         */

         if (parameters->Parameters_List->Process_Descriptor[AAI_EDIT_EDIT_PROCESS].Process_Active_Flag || parameters->Parameters_List->Process_Descriptor[AAI_HELP_TOPIC_PROCESS].Process_Active_Flag && !parameters->Hide_Function_Keys_Flag) {

            window(1, 1, 80, 25);
            TEXT_Set_Text_Color(parameters->Colors.Primary_Color, parameters->Text);

            if (parameters->Parameters_List->Process_Descriptor[AAI_EDIT_EDIT_PROCESS].Process_Active_Flag) {

               sprintf(str, "%10s", "");
               TEXT_Set_Cursor_Position(25, 10, parameters->Text);
               TEXT_Print_String(str, parameters->Text);
               sprintf(str, "%40s", "");
					TEXT_Set_Cursor_Position(25, 30, parameters->Text);
               TEXT_Print_String(str, parameters->Text);

            }

            if (parameters->Parameters_List->Process_Descriptor[AAI_HELP_TOPIC_PROCESS].Process_Active_Flag) {

               sprintf(str, "%70s", "");
               TEXT_Set_Cursor_Position(25, 1, parameters->Text);
					TEXT_Print_String(str, parameters->Text);
            }

            parameters->Hide_Function_Keys_Flag = TRUE;

         }
         else {

            if (!parameters->Parameters_List->Process_Descriptor[AAI_EDIT_EDIT_PROCESS].Process_Active_Flag && !parameters->Parameters_List->Process_Descriptor[AAI_COMMUNICAAIONS_TERMINAL_PROCESS].Process_Active_Flag && !parameters->Parameters_List->Process_Descriptor[AAI_HELP_TOPIC_PROCESS].Process_Active_Flag && parameters->Hide_Function_Keys_Flag) {

               window(1, 1, 80, 25);
               MENU_Destructor(&(parameters->Menu));
               MENU_Constructor(parameters->Menu_Text, parameters->Starting_Row, parameters->Starting_Column, parameters->Colors.Primary_Color, parameters->Colors.Secondary_Color, parameters->Colors.Primary_Highlight_Color, parameters->Colors.Secondary_Highlight_Color, NULL, 0, 0, BLACK, BLACK, parameters->Text, &(parameters->Menu));
               MENU_Display(parameters->Menu, 0);
					parameters->Hide_Function_Keys_Flag = FALSE;

            }

         }

         /*

            Continue only if no errors occurred above and a key was pressed.

         */

         if (result == EZERO && *(Key) != 0) {

            window(1, 1, 80, 25);
            valid_key_flag = TRUE;

            /*

               Determine if any of the active function keys options were activated.

            */

				switch (*(Key)) {

               case KB_F1 :

                  AAI_Activate_Process(parameters->Parameters_List, AAI_HELP_TOPIC_PROCESS);
                  break;

               case KB_F2 :

						for (invoke_process_flag = TRUE, i = AAI_FILE_LOAD_PROCESS; i <= AAI_SUB_MENU_PROCESS; i++) {

							if (parameters->Parameters_List->Process_Descriptor[i].Process_Active_Flag) {

                        invoke_process_flag = FALSE;

                     }

                  }

                  if (invoke_process_flag) {

                     AAI_Activate_Process(parameters->Parameters_List, AAI_FILE_LOAD_PROCESS);
                     AAI_Halt_Process(parameters->Parameters_List, AAI_MAIN_MENU_PROCESS);

                  }

                  break;

               case KB_F3 :

                  for (invoke_process_flag = TRUE, i = AAI_FILE_LOAD_PROCESS; i <= AAI_SUB_MENU_PROCESS; i++) {

                     if (i != AAI_EDIT_EDIT_PROCESS && parameters->Parameters_List->Process_Descriptor[i].Process_Active_Flag) {

                        invoke_process_flag = FALSE;

                     }

                  }

                  if (invoke_process_flag) {

                     AAI_Activate_Process(parameters->Parameters_List, AAI_FILE_SAVE_PROCESS);
                     AAI_Halt_Process(parameters->Parameters_List, AAI_MAIN_MENU_PROCESS);

                  }

                  break;

               case KB_F8 :

                  for (invoke_process_flag = TRUE, i = AAI_FILE_LOAD_PROCESS; i <= AAI_SUB_MENU_PROCESS; i++) {

                     if (parameters->Parameters_List->Process_Descriptor[i].Process_Active_Flag) {

                        invoke_process_flag = FALSE;

                     }

                  }

                  if (invoke_process_flag) {

                     AAI_Activate_Process(parameters->Parameters_List, AAI_COMMUNICAAIONS_TERMINAL_PROCESS);
                     AAI_Halt_Process(parameters->Parameters_List, AAI_MAIN_MENU_PROCESS);

                  }

                  break;

               case KB_F9 :

                  for (invoke_process_flag = TRUE, i = AAI_FILE_LOAD_PROCESS; i <= AAI_SUB_MENU_PROCESS; i++) {

                     if (parameters->Parameters_List->Process_Descriptor[i].Process_Active_Flag) {

                        invoke_process_flag = FALSE;

                     }

                  }

                  if (invoke_process_flag) {

                     AAI_Activate_Process(parameters->Parameters_List, AAI_COMMUNICAAIONS_SEND_PROCESS);
                     AAI_Halt_Process(parameters->Parameters_List, AAI_MAIN_MENU_PROCESS);

                  }

                  break;

               case KB_F10 :

                  for (invoke_process_flag = TRUE, i = AAI_FILE_LOAD_PROCESS; i <= AAI_SUB_MENU_PROCESS; i++) {

                     if (parameters->Parameters_List->Process_Descriptor[i].Process_Active_Flag) {

                        invoke_process_flag = FALSE;

                     }

                  }

                  if (invoke_process_flag) {

                     AAI_Activate_Process(parameters->Parameters_List, AAI_COMMUNICAAIONS_RECEIVE_PROCESS);
                     AAI_Halt_Process(parameters->Parameters_List, AAI_MAIN_MENU_PROCESS);

                  }

                  break;

               case KB_ESC :

                  AAI_Activate_Process(parameters->Parameters_List, AAI_FILE_QUIT_PROCESS);
						break;

               default :

                  valid_key_flag = FALSE;

            }

            if (valid_key_flag) {

               *(Key) = 0;

            }

         }

      }

   }

   return (result);

}

/*

   Function    : AAI_Initialize
   Description : Initializes the AAI system.
   Inputs      : Nothing.
   Updates     : Nothing.
   Outputs     : Parameters_List = The parameters list to use while the AAI system is active.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 08/18/92 DWP Initial coding.
                 02/13/93 DWP Added Display_Length field to variables of type AAI_INPUT_DESCRIPTOR.
   Notes       :

*/

int AAI_Initialize(AAI_PARAMETERS_LIST * Parameters_List) {

   AAI_PROCESS_DESCRIPTOR *                 process_descriptor;
   AAI_PROCESS_TYPES                        process_number;
   AAI_DISPLAY_TIME_PARAMETERS *            display_time_parameters;
   AAI_FILE_LOAD_PARAMETERS *               file_load_parameters;
   AAI_FILE_NEW_PARAMETERS *                file_new_parameters;
   AAI_FILE_SAVE_PARAMETERS *               file_save_parameters;
	AAI_FILE_SAVE_AS_PARAMETERS *            file_save_as_parameters;
   AAI_FILE_DELETE_PARAMETERS *             file_delete_parameters;
   AAI_FILE_RENAME_PARAMETERS *             file_rename_parameters;
   AAI_FILE_QUIT_PARAMETERS *               file_quit_parameters;
   AAI_EDIT_EDIT_PARAMETERS *               edit_edit_parameters;
   AAI_EDIT_MARK_PARAMETERS *               edit_mark_parameters;
   AAI_EDIT_CLEAR_PARAMETERS *              edit_clear_parameters;
   AAI_REPORTS_DATA_DUMP_PARAMETERS *       reports_data_dump_parameters;
   AAI_REPORTS_AVAIL_CFG_PARAMETERS *       reports_available_configurations_parameters;
   AAI_COMMUNICAAIONS_SEND_PARAMETERS *     comm_send_parameters;
   AAI_COMMUNICAAIONS_RECEIVE_PARAMETERS *  comm_receive_parameters;
   AAI_COMMUNICAAIONS_TERMINAL_PARAMETERS * comm_terminal_parameters;
   AAI_HELP_INDEX_PARAMETERS *              help_index_parameters;
   AAI_HELP_ABOUT_PARAMETERS *              help_about_parameters;
   AAI_HELP_PRINT_PARAMETERS *              help_print_parameters;
   AAI_HELP_TOPIC_PARAMETERS *              help_topic_parameters;
   AAI_YES_NO_MENU_PARAMETERS *             yes_no_menu_parameters;
   AAI_SUB_MENU_PARAMETERS *                sub_menu_parameters;
   AAI_MAIN_MENU_PARAMETERS *               main_menu_parameters;
   AAI_FUNCTION_KEY_MENU_PARAMETERS *       function_key_menu_parameters;
   CARDINAL_16                              i, key = 0;
   int                                      result = EZERO;

	if (AAI_Load_Configuration(AAI_CONFIG_FILE_NAME, &(Parameters_List->Default_Parameters)) != EZERO || (Parameters_List->Display_Type != Parameters_List->Default_Parameters.Display_Type) || (Parameters_List->Port_No != Parameters_List->Default_Parameters.Port_No)) {

      AAI_Initialize_Parameters_List(Parameters_List);
      result = AAI_Save_Configuration(AAI_CONFIG_FILE_NAME, &(Parameters_List->Default_Parameters));

   }

   textmode((Parameters_List->Display_Type == AAI_COLOR) ? C80 : BW80);
   TEXT_Constructor(BGI_GotoYX, BGI_GotoY, BGI_GotoX, BGI_WhereY, BGI_WhereX, BGI_TextAttr, BGI_GetTextInfo, BGI_ClrScr, BGI_Print_Character, BGI_Print_String, &(Parameters_List->Text));

   memcpy(&(Parameters_List->Menu_Characteristics_List), AAI_Menu_Characteristics_List, sizeof(Parameters_List->Menu_Characteristics_List));
   memcpy(Parameters_List->Menu_Text_List, AAI_Menu_Text_List, sizeof(Parameters_List->Menu_Text_List));
   memcpy(Parameters_List->Menu_Keys_List, AAI_Menu_Keys_List, sizeof(Parameters_List->Menu_Keys_List));
   Parameters_List->Main_Screen_Text = AAI_Main_Screen_Text;
   Parameters_List->Main_Screen_Characters = AAI_Main_Screen_Unique_Characters;
   Parameters_List->Main_Screen_Character_Colors = AAI_Main_Screen_Unique_Colors;

   Parameters_List->Total_Processes = AAI_TOTAL_PROCESSES;

   for (process_number = 0; process_number < Parameters_List->Total_Processes; process_number++) {

      process_descriptor = &(Parameters_List->Process_Descriptor[process_number]);

      process_descriptor->Process_Number = process_number;
      AAI_Halt_Process(Parameters_List, process_number);
      process_descriptor->Process_Parameters = NULL;
		process_descriptor->Process = AAI_Process_List[process_number].Process;

      if (process_descriptor->Process == NULL) {

         result = EZERO;

      }
      else {

         result = process_descriptor->Process(&(process_descriptor->Process_Parameters), &key);

         if (result == EZERO) {

            switch (process_number) {

               case AAI_DISPLAY_TIME_PROCESS :

                  display_time_parameters = process_descriptor->Process_Parameters;

                  display_time_parameters->Text = Parameters_List->Text;
                  memcpy(&(display_time_parameters->Colors), &(Parameters_List->Default_Parameters.Main_Menu_Colors), sizeof(display_time_parameters->Colors));
                  display_time_parameters->Row = 1;
                  display_time_parameters->Column = 61;
						display_time_parameters->Minutes_Value = -1;
                  AAI_Activate_Process(Parameters_List, AAI_DISPLAY_TIME_PROCESS);
                  break;

               case AAI_FILE_LOAD_PROCESS :

                  file_load_parameters = process_descriptor->Process_Parameters;
                  file_load_parameters->Parameters_List = Parameters_List;
                  file_load_parameters->Port = NULL;
                  file_load_parameters->Text = Parameters_List->Text;
                  memcpy(&(file_load_parameters->Colors), &(Parameters_List->Default_Parameters.Main_Menu_Colors), sizeof(file_load_parameters->Colors));
                  file_load_parameters->Starting_Row = 3;
                  file_load_parameters->Starting_Column = 2;
                  file_load_parameters->Height = 14;
                  file_load_parameters->Width = 15;
                  strcpy(file_load_parameters->File_Name, "");
                  file_load_parameters->Current_File_Number = 1;
                  file_load_parameters->Previous_File_Number = 1;
                  file_load_parameters->First_File_Number = 1;
                  file_load_parameters->Current_Row = 0;

                  break;

					case AAI_FILE_NEW_PROCESS :

                  file_new_parameters = process_descriptor->Process_Parameters;
                  file_new_parameters->Parameters_List = Parameters_List;
                  file_new_parameters->Load_Parameters = file_load_parameters;
                  file_new_parameters->Clear_Memory_Flag = -1;
                  file_new_parameters->Process_In_Progress_Flag = FALSE;
                  break;

               case AAI_FILE_SAVE_PROCESS :

                  file_save_parameters = process_descriptor->Process_Parameters;
                  file_save_parameters->Parameters_List = Parameters_List;
                  file_save_parameters->Load_Parameters = file_load_parameters;
                  file_save_parameters->Port = NULL;
                  file_save_parameters->Text = Parameters_List->Text;
                  memcpy(&(file_save_parameters->Colors), &(Parameters_List->Default_Parameters.Main_Menu_Colors), sizeof(file_save_parameters->Colors));
                  file_save_parameters->Starting_Row = 9;
                  file_save_parameters->Starting_Column = 27;
                  file_save_parameters->Height = 5;
                  file_save_parameters->Width = 25;

                  file_save_parameters->File_Name.Text = Parameters_List->Text;
						file_save_parameters->File_Name.Edit_Length = 8;
                  file_save_parameters->File_Name.Display_Length = 8;
                  file_save_parameters->File_Name.Type = STRING_TYPE;
                  memcpy(&(file_save_parameters->File_Name.Colors), &(Parameters_List->Default_Parameters.Main_Menu_Colors), sizeof(file_save_parameters->File_Name.Colors));
                  file_save_parameters->File_Name.Current_Row = 2;
                  file_save_parameters->File_Name.Current_Column = 15;
                  file_save_parameters->File_Name.Marked_Flag = FALSE;
                  file_save_parameters->File_Name.Refresh_Flag = TRUE;
                  strcpy(file_save_parameters->File_Name.Value, "");

                  break;

               case AAI_FILE_SAVE_AS_PROCESS :

                  file_save_as_parameters = process_descriptor->Process_Parameters;
                  file_save_as_parameters->Parameters_List = Parameters_List;
                  file_save_as_parameters->Load_Parameters = file_load_parameters;
                  break;

               case AAI_FILE_DELETE_PROCESS :

                  file_delete_parameters = process_descriptor->Process_Parameters;
                  file_delete_parameters->Parameters_List = Parameters_List;
						file_delete_parameters->Port = NULL;
                  file_delete_parameters->Text = Parameters_List->Text;
                  memcpy(&(file_delete_parameters->Colors), &(Parameters_List->Default_Parameters.Main_Menu_Colors), sizeof(file_delete_parameters->Colors));
                  file_delete_parameters->Starting_Row = 3;
                  file_delete_parameters->Starting_Column = 2;
                  file_delete_parameters->Height = 14;
                  file_delete_parameters->Width = 17;
                  strcpy(file_delete_parameters->File_Name, "");
                  file_delete_parameters->Current_File_Number = 1;
                  file_delete_parameters->Previous_File_Number = 1;
                  file_delete_parameters->First_File_Number = 1;
                  file_delete_parameters->Current_Row = 0;
                  file_delete_parameters->Delete_File_Flag = -1;
                  file_delete_parameters->Process_In_Progress_Flag = FALSE;
                  break;

               case AAI_FILE_RENAME_PROCESS :

                  file_rename_parameters = process_descriptor->Process_Parameters;
                  file_rename_parameters->Parameters_List = Parameters_List;
                  file_rename_parameters->Port = NULL;
                  file_rename_parameters->Text = Parameters_List->Text;
                  memcpy(&(file_rename_parameters->Colors), &(Parameters_List->Default_Parameters.Main_Menu_Colors), sizeof(file_rename_parameters->Colors));
						file_rename_parameters->Starting_Row = 3;
                  file_rename_parameters->Starting_Column = 2;
                  file_rename_parameters->Height = 14;
                  file_rename_parameters->Width = 15;

                  file_rename_parameters->New_File_Port = NULL;
                  file_rename_parameters->New_File_Starting_Row = 9;
                  file_rename_parameters->New_File_Starting_Column = 30;
                  file_rename_parameters->New_File_Height = 5;
                  file_rename_parameters->New_File_Width = 20;

                  file_rename_parameters->New_File_Name.Text = Parameters_List->Text;
                  file_rename_parameters->New_File_Name.Edit_Length = 8;
                  file_rename_parameters->New_File_Name.Display_Length = 8;
                  file_rename_parameters->New_File_Name.Type = STRING_TYPE;
                  memcpy(&(file_rename_parameters->New_File_Name.Colors), &(Parameters_List->Default_Parameters.Main_Menu_Colors), sizeof(file_rename_parameters->New_File_Name.Colors));
                  file_rename_parameters->New_File_Name.Current_Row = 2;
                  file_rename_parameters->New_File_Name.Current_Column = 10;
                  file_rename_parameters->New_File_Name.Marked_Flag = FALSE;
                  file_rename_parameters->New_File_Name.Refresh_Flag = TRUE;
                  strcpy(file_rename_parameters->New_File_Name.Value, "");

                  strcpy(file_rename_parameters->Current_File_Name, "");
						file_rename_parameters->Current_File_Number = 1;
                  file_rename_parameters->Previous_File_Number = 1;
                  file_rename_parameters->First_File_Number = 1;
                  file_rename_parameters->Current_Row = 0;

                  break;

               case AAI_FILE_QUIT_PROCESS :

                  file_quit_parameters = process_descriptor->Process_Parameters;
                  file_quit_parameters->Parameters_List = Parameters_List;
                  break;

               case AAI_EDIT_EDIT_PROCESS :

                  edit_edit_parameters = process_descriptor->Process_Parameters;
                  file_load_parameters->Edit_Parameters = edit_edit_parameters;
                  file_new_parameters->Edit_Parameters = edit_edit_parameters;
                  file_save_parameters->Edit_Parameters = edit_edit_parameters;
                  edit_edit_parameters->Parameters_List = Parameters_List;
                  edit_edit_parameters->Port = NULL;
                  edit_edit_parameters->Text = Parameters_List->Text;
                  memcpy(&(edit_edit_parameters->Colors), &(Parameters_List->Default_Parameters.Main_Menu_Colors), sizeof(edit_edit_parameters->Colors));
						edit_edit_parameters->Starting_Row = 3;
                  edit_edit_parameters->Starting_Column = 2;
                  edit_edit_parameters->Height = 21;
                  edit_edit_parameters->Width = 78;
                  edit_edit_parameters->Field = 1;
                  edit_edit_parameters->Total_Fields = 84;

                  edit_edit_parameters->Part_Number.Text = Parameters_List->Text;
                  edit_edit_parameters->Part_Number.Edit_Length = 16;
                  edit_edit_parameters->Part_Number.Display_Length = 16;
                  edit_edit_parameters->Part_Number.Type = STRING_TYPE;
                  memcpy(&(edit_edit_parameters->Part_Number.Colors), &(Parameters_List->Default_Parameters.Main_Menu_Colors), sizeof(edit_edit_parameters->Part_Number.Colors));
                  edit_edit_parameters->Part_Number.Current_Row = 2;
                  edit_edit_parameters->Part_Number.Current_Column = 5;
                  edit_edit_parameters->Part_Number.Marked_Flag = FALSE;
                  edit_edit_parameters->Part_Number.Refresh_Flag = TRUE;

                  edit_edit_parameters->Valve_Pack_Number.Text = Parameters_List->Text;
                  edit_edit_parameters->Valve_Pack_Number.Edit_Length = (Parameters_List->Version == AAI_PLANT_VERSION) ? 4 : 5;
                  edit_edit_parameters->Valve_Pack_Number.Display_Length = 5;
                  edit_edit_parameters->Valve_Pack_Number.Type = INTEGER_16_TYPE;
                  memcpy(&(edit_edit_parameters->Valve_Pack_Number.Colors), &(Parameters_List->Default_Parameters.Main_Menu_Colors), sizeof(edit_edit_parameters->Valve_Pack_Number.Colors));
                  edit_edit_parameters->Valve_Pack_Number.Current_Row = 2;
						edit_edit_parameters->Valve_Pack_Number.Current_Column = 27;
                  edit_edit_parameters->Valve_Pack_Number.Marked_Flag = FALSE;
                  edit_edit_parameters->Valve_Pack_Number.Refresh_Flag = TRUE;
                  edit_edit_parameters->Valve_Pack_Number.Minimum_Value = 0;
                  edit_edit_parameters->Valve_Pack_Number.Maximum_Editable_Value = (Parameters_List->Version == AAI_PLANT_VERSION) ? 9999 : 16383;
                  edit_edit_parameters->Valve_Pack_Number.Maximum_Loadable_Value = 16383;

                  edit_edit_parameters->Multiple_Part_Number.Text = Parameters_List->Text;
                  edit_edit_parameters->Multiple_Part_Number.Edit_Length = 1;
                  edit_edit_parameters->Multiple_Part_Number.Display_Length = 1;
                  edit_edit_parameters->Multiple_Part_Number.Type = INTEGER_16_TYPE;
                  memcpy(&(edit_edit_parameters->Multiple_Part_Number.Colors), &(Parameters_List->Default_Parameters.Main_Menu_Colors), sizeof(edit_edit_parameters->Multiple_Part_Number.Colors));
                  edit_edit_parameters->Multiple_Part_Number.Current_Row = 2;
                  edit_edit_parameters->Multiple_Part_Number.Current_Column = 38;
                  edit_edit_parameters->Multiple_Part_Number.Marked_Flag = FALSE;
                  edit_edit_parameters->Multiple_Part_Number.Refresh_Flag = TRUE;
                  edit_edit_parameters->Multiple_Part_Number.Minimum_Value = 1;
                  edit_edit_parameters->Multiple_Part_Number.Maximum_Editable_Value = 4;
                  edit_edit_parameters->Multiple_Part_Number.Maximum_Loadable_Value = 4;

                  edit_edit_parameters->Last_Bin_Sensor.Text = Parameters_List->Text;
                  edit_edit_parameters->Last_Bin_Sensor.Edit_Length = 4;
                  edit_edit_parameters->Last_Bin_Sensor.Display_Length = 4;
						edit_edit_parameters->Last_Bin_Sensor.Type = INTEGER_16_TYPE;
                  memcpy(&(edit_edit_parameters->Last_Bin_Sensor.Colors), &(Parameters_List->Default_Parameters.Main_Menu_Colors), sizeof(edit_edit_parameters->Last_Bin_Sensor.Colors));
                  edit_edit_parameters->Last_Bin_Sensor.Current_Row = 2;
                  edit_edit_parameters->Last_Bin_Sensor.Current_Column = 45;
                  edit_edit_parameters->Last_Bin_Sensor.Marked_Flag = FALSE;
                  edit_edit_parameters->Last_Bin_Sensor.Refresh_Flag = TRUE;
                  edit_edit_parameters->Last_Bin_Sensor.Minimum_Value = 0;
                  edit_edit_parameters->Last_Bin_Sensor.Maximum_Editable_Value = 3275;
                  edit_edit_parameters->Last_Bin_Sensor.Maximum_Loadable_Value = 3275;

                  edit_edit_parameters->Total_Cycle_Time.Text = Parameters_List->Text;
                  edit_edit_parameters->Total_Cycle_Time.Edit_Length = 4;
                  edit_edit_parameters->Total_Cycle_Time.Display_Length = 4;
                  edit_edit_parameters->Total_Cycle_Time.Type = INTEGER_16_TYPE;
                  memcpy(&(edit_edit_parameters->Total_Cycle_Time.Colors), &(Parameters_List->Default_Parameters.Main_Menu_Colors), sizeof(edit_edit_parameters->Total_Cycle_Time.Colors));
                  edit_edit_parameters->Total_Cycle_Time.Current_Row = 2;
                  edit_edit_parameters->Total_Cycle_Time.Current_Column = 71;
                  edit_edit_parameters->Total_Cycle_Time.Marked_Flag = FALSE;
                  edit_edit_parameters->Total_Cycle_Time.Refresh_Flag = TRUE;
                  edit_edit_parameters->Total_Cycle_Time.Minimum_Value = 1;
                  edit_edit_parameters->Total_Cycle_Time.Maximum_Editable_Value = 3276;
                  edit_edit_parameters->Total_Cycle_Time.Maximum_Loadable_Value = 3276;

						for (i = 0; i < 80; i++) {

                     edit_edit_parameters->Advance_Time[i].Text = Parameters_List->Text;
                     edit_edit_parameters->Advance_Time[i].Edit_Length = 4;
                     edit_edit_parameters->Advance_Time[i].Display_Length = 4;
                     edit_edit_parameters->Advance_Time[i].Type = INTEGER_16_TYPE;
                     memcpy(&(edit_edit_parameters->Advance_Time[i].Colors), &(Parameters_List->Default_Parameters.Main_Menu_Colors), sizeof(edit_edit_parameters->Advance_Time[i].Colors));
                     edit_edit_parameters->Advance_Time[i].Marked_Flag = FALSE;
                     edit_edit_parameters->Advance_Time[i].Refresh_Flag = TRUE;
                     edit_edit_parameters->Advance_Time[i].Minimum_Value = 0;
                     edit_edit_parameters->Advance_Time[i].Maximum_Editable_Value = 3275;
                     edit_edit_parameters->Advance_Time[i].Maximum_Loadable_Value = 3275;

                     edit_edit_parameters->Retract_Time[i].Text = Parameters_List->Text;
                     edit_edit_parameters->Retract_Time[i].Edit_Length = 4;
                     edit_edit_parameters->Retract_Time[i].Display_Length = 4;
                     edit_edit_parameters->Retract_Time[i].Type = INTEGER_16_TYPE;
                     memcpy(&(edit_edit_parameters->Retract_Time[i].Colors), &(Parameters_List->Default_Parameters.Main_Menu_Colors), sizeof(edit_edit_parameters->Retract_Time[i].Colors));
                     edit_edit_parameters->Retract_Time[i].Marked_Flag = FALSE;
                     edit_edit_parameters->Retract_Time[i].Refresh_Flag = TRUE;
                     edit_edit_parameters->Retract_Time[i].Minimum_Value = 0;
                     edit_edit_parameters->Retract_Time[i].Maximum_Editable_Value = 3276;
                     edit_edit_parameters->Retract_Time[i].Maximum_Loadable_Value = 3276;

                  }

                  AAI_Clear_Edit_Parameters(edit_edit_parameters);
                  edit_edit_parameters->Top_Row_Starting_Number = 1;
                  break;

               case AAI_EDIT_MARK_PROCESS :

                  edit_mark_parameters = process_descriptor->Process_Parameters;
                  edit_mark_parameters->Parameters_List = Parameters_List;
                  edit_mark_parameters->Edit_Parameters = edit_edit_parameters;
                  break;

               case AAI_EDIT_CLEAR_PROCESS :

                  edit_clear_parameters = process_descriptor->Process_Parameters;
                  edit_clear_parameters->Parameters_List = Parameters_List;
                  edit_clear_parameters->Edit_Parameters = edit_edit_parameters;
                  break;

               case AAI_REPORTS_DATA_DUMP_PROCESS :

						reports_data_dump_parameters = process_descriptor->Process_Parameters;
                  reports_data_dump_parameters->Parameters_List = Parameters_List;
                  reports_data_dump_parameters->Load_Parameters = file_load_parameters;
                  reports_data_dump_parameters->Edit_Parameters = edit_edit_parameters;
                  reports_data_dump_parameters->Print_Report_Flag = -1;
                  reports_data_dump_parameters->Process_In_Progress_Flag = FALSE;
                  reports_data_dump_parameters->Stop_Process_Flag = FALSE;
                  break;

               case AAI_REPORTS_AVAIL_CFG_PROCESS :

                  reports_available_configurations_parameters = process_descriptor->Process_Parameters;
                  reports_available_configurations_parameters->Parameters_List = Parameters_List;
                  reports_available_configurations_parameters->Load_Parameters = file_load_parameters;
                  reports_available_configurations_parameters->Edit_Parameters = edit_edit_parameters;
                  reports_available_configurations_parameters->Print_Report_Flag = -1;
                  reports_available_configurations_parameters->Process_In_Progress_Flag = FALSE;
                  reports_available_configurations_parameters->Stop_Process_Flag = FALSE;
                  break;

               case AAI_COMMUNICAAIONS_SEND_PROCESS :

                  comm_send_parameters = process_descriptor->Process_Parameters;
						comm_send_parameters->Parameters_List = Parameters_List;
                  comm_send_parameters->Edit_Parameters = edit_edit_parameters;
                  comm_send_parameters->Port = NULL;
                  comm_send_parameters->Text = Parameters_List->Text;
                  memcpy(&(comm_send_parameters->Colors), &(Parameters_List->Default_Parameters.Main_Menu_Colors), sizeof(comm_send_parameters->Colors));
                  comm_send_parameters->Starting_Row = 7;
                  comm_send_parameters->Starting_Column = 5;
                  comm_send_parameters->Height = 11;
                  comm_send_parameters->Width = 70;

                  comm_send_parameters->Unit_Number.Text = Parameters_List->Text;
                  comm_send_parameters->Unit_Number.Edit_Length = 1;
                  comm_send_parameters->Unit_Number.Display_Length = 1;
                  comm_send_parameters->Unit_Number.Type = STRING_TYPE;
                  memcpy(&(comm_send_parameters->Unit_Number.Colors), &(Parameters_List->Default_Parameters.Main_Menu_Colors), sizeof(comm_send_parameters->Unit_Number.Colors));
                  comm_send_parameters->Unit_Number.Current_Row = 3;
                  comm_send_parameters->Unit_Number.Current_Column = 48;
                  comm_send_parameters->Unit_Number.Marked_Flag = FALSE;
                  comm_send_parameters->Unit_Number.Refresh_Flag = TRUE;

                  comm_send_parameters->Save_Timing_Values.Text = Parameters_List->Text;
                  comm_send_parameters->Save_Timing_Values.Edit_Length = 1;
                  comm_send_parameters->Save_Timing_Values.Display_Length = 1;
						comm_send_parameters->Save_Timing_Values.Type = STRING_TYPE;
                  memcpy(&(comm_send_parameters->Save_Timing_Values.Colors), &(Parameters_List->Default_Parameters.Main_Menu_Colors), sizeof(comm_send_parameters->Save_Timing_Values.Colors));
                  comm_send_parameters->Save_Timing_Values.Current_Row = 5;
                  comm_send_parameters->Save_Timing_Values.Current_Column = 48;
                  comm_send_parameters->Save_Timing_Values.Marked_Flag = FALSE;
                  comm_send_parameters->Save_Timing_Values.Refresh_Flag = TRUE;

                  comm_send_parameters->Get_Parameters_Flag = TRUE;
                  comm_send_parameters->Field = 1;
                  comm_send_parameters->Valve_Packs = 0;

                  comm_send_parameters->Port_No = Parameters_List->Default_Parameters.Port_No;
                  comm_send_parameters->IQ_Size = 4096;
                  comm_send_parameters->OQ_Size = 4096;
                  comm_send_parameters->Int_Level = 0;
                  comm_send_parameters->Port_Ads = 0;
                  setmem(comm_send_parameters->Pbuffer, sizeof(comm_send_parameters->Pbuffer), 0);

                  comm_send_parameters->First_Pass_Flag = TRUE;
                  comm_send_parameters->Exit_Flag = FALSE;
                  comm_send_parameters->Abort_Flag = FALSE;
                  comm_send_parameters->Parameter_Number = 0;
                  strcpy(comm_send_parameters->Send_String, "");

                  break;

               case AAI_COMMUNICAAIONS_RECEIVE_PROCESS :

                  comm_receive_parameters = process_descriptor->Process_Parameters;
                  comm_receive_parameters->Parameters_List = Parameters_List;
                  comm_receive_parameters->Edit_Parameters = edit_edit_parameters;
                  comm_receive_parameters->Port = NULL;
                  comm_receive_parameters->Text = Parameters_List->Text;
                  memcpy(&(comm_receive_parameters->Colors), &(Parameters_List->Default_Parameters.Main_Menu_Colors), sizeof(comm_receive_parameters->Colors));
                  comm_receive_parameters->Starting_Row = 8;
                  comm_receive_parameters->Starting_Column = 5;
                  comm_receive_parameters->Height = 9;
                  comm_receive_parameters->Width = 70;

                  comm_receive_parameters->Port_No = Parameters_List->Default_Parameters.Port_No;
                  comm_receive_parameters->IQ_Size = 4096;
                  comm_receive_parameters->OQ_Size = 4096;
                  comm_receive_parameters->Int_Level = 0;
                  comm_receive_parameters->Port_Ads = 0;
                  setmem(comm_receive_parameters->Pbuffer, sizeof(comm_receive_parameters->Pbuffer), 0);

						comm_receive_parameters->First_Pass_Flag = TRUE;
                  comm_receive_parameters->Exit_Flag = FALSE;
                  comm_receive_parameters->Parameter_Number = 0;
                  strcpy(comm_receive_parameters->Receive_String, "");
                  comm_receive_parameters->Receive_String_Offset = 0;
                  comm_receive_parameters->Lines_Received = 0;
                  break;

               case AAI_COMMUNICAAIONS_TERMINAL_PROCESS :

                  comm_terminal_parameters = process_descriptor->Process_Parameters;
                  comm_terminal_parameters->Parameters_List = Parameters_List;
                  comm_terminal_parameters->Port = NULL;
                  comm_terminal_parameters->Text = Parameters_List->Text;
                  memcpy(&(comm_terminal_parameters->Colors), &(Parameters_List->Default_Parameters.Main_Menu_Colors), sizeof(comm_terminal_parameters->Colors));
                  comm_terminal_parameters->Starting_Row = 1;
                  comm_terminal_parameters->Starting_Column = 1;
                  comm_terminal_parameters->Height = 25;
                  comm_terminal_parameters->Width = 80;

                  comm_terminal_parameters->Port_No = Parameters_List->Default_Parameters.Port_No;
                  comm_terminal_parameters->IQ_Size = 4096;
                  comm_terminal_parameters->OQ_Size = 4096;
						comm_terminal_parameters->Int_Level = 0;
                  comm_terminal_parameters->Port_Ads = 0;

                  comm_terminal_parameters->First_Pass_Flag = TRUE;
                  comm_terminal_parameters->Exit_Flag = FALSE;
                  break;

               case AAI_HELP_INDEX_PROCESS :

                  help_index_parameters = process_descriptor->Process_Parameters;
                  help_index_parameters->Parameters_List = Parameters_List;
                  help_index_parameters->Port = NULL;
                  help_index_parameters->Text = Parameters_List->Text;
                  memcpy(&(help_index_parameters->Colors), &(Parameters_List->Default_Parameters.Main_Menu_Colors), sizeof(help_index_parameters->Colors));
                  help_index_parameters->Starting_Row = 7;
                  help_index_parameters->Starting_Column = 8;
                  help_index_parameters->Height = 11;
                  help_index_parameters->Width = 64;
                  help_index_parameters->Help_File = NULL;
                  help_index_parameters->End_Of_File = FALSE;
                  help_index_parameters->Help_Available_Flag = FALSE;
                  help_index_parameters->Help_Loaded_Flag = FALSE;
                  help_index_parameters->First_Row_Line = 1;
						help_index_parameters->Current_Row = 0;
                  help_index_parameters->Previous_Row = 0;
                  help_index_parameters->Redraw_Screen_Flag = TRUE;
                  AAI_Activate_Process(Parameters_List, AAI_HELP_INDEX_PROCESS);
                  break;

               case AAI_HELP_ABOUT_PROCESS :

                  help_about_parameters = process_descriptor->Process_Parameters;
                  help_about_parameters->Parameters_List = Parameters_List;
                  help_about_parameters->Port = NULL;
                  help_about_parameters->Text = Parameters_List->Text;
                  memcpy(&(help_about_parameters->Colors), &(Parameters_List->Default_Parameters.Main_Menu_Colors), sizeof(help_about_parameters->Colors));
						help_about_parameters->Starting_Row = 7;
                  help_about_parameters->Starting_Column = 13;
                  help_about_parameters->Height = 11;
                  help_about_parameters->Width = 55;
                  AAI_Activate_Process(Parameters_List, AAI_HELP_ABOUT_PROCESS);
                  break;

               case AAI_HELP_PRINT_PROCESS :

                  help_print_parameters = process_descriptor->Process_Parameters;
						help_print_parameters->Parameters_List = Parameters_List;
                  help_print_parameters->Index_Parameters = help_index_parameters;
                  help_print_parameters->Help_Index = NULL;
                  help_print_parameters->Help_Text = NULL;
                  help_print_parameters->Exit_Flag = FALSE;
                  help_print_parameters->Report_File = NULL;
                  help_print_parameters->Print_Report_Flag = -1;
                  help_print_parameters->Page_Number = 0;
                  help_print_parameters->Line_Number = 0;
                  help_print_parameters->New_Page_Flag = TRUE;
                  help_print_parameters->Process_In_Progress_Flag = FALSE;
                  help_print_parameters->First_Index_Node_Flag = TRUE;
                  break;

               case AAI_HELP_TOPIC_PROCESS :

                  help_topic_parameters = process_descriptor->Process_Parameters;
                  help_topic_parameters->Parameters_List = Parameters_List;
                  help_topic_parameters->Index_Parameters = help_index_parameters;
                  help_topic_parameters->Port = NULL;
                  help_topic_parameters->Text = Parameters_List->Text;
                  memcpy(&(help_topic_parameters->Colors), &(Parameters_List->Default_Parameters.Main_Menu_Colors), sizeof(help_topic_parameters->Colors));
                  help_topic_parameters->Starting_Row = 7;
						help_topic_parameters->Starting_Column = 5;
                  help_topic_parameters->Height = 11;
                  help_topic_parameters->Width = 70;
                  help_topic_parameters->Key = NULL;
                  help_topic_parameters->First_Row_Line = 1;
                  help_topic_parameters->Redraw_Screen_Flag = TRUE;
                  help_topic_parameters->Exit_Flag = FALSE;
                  break;

               case AAI_YES_NO_MENU_PROCESS :

                  yes_no_menu_parameters = process_descriptor->Process_Parameters;
                  yes_no_menu_parameters->Parameters_List = Parameters_List;
						yes_no_menu_parameters->Text = Parameters_List->Text;
                  memcpy(&(yes_no_menu_parameters->Colors), &(Parameters_List->Default_Parameters.Yes_No_Menu_Colors), sizeof(yes_no_menu_parameters->Colors));
                  yes_no_menu_parameters->Menu_Text = Parameters_List->Menu_Text_List[AAI_YES_NO_MENU];
                  yes_no_menu_parameters->Menu_Keys_List = Parameters_List->Menu_Keys_List[AAI_YES_NO_MENU];
                  yes_no_menu_parameters->Option = 1;

                  break;

               case AAI_SUB_MENU_PROCESS :

						sub_menu_parameters = process_descriptor->Process_Parameters;
						sub_menu_parameters->Parameters_List = Parameters_List;
						sub_menu_parameters->Text = Parameters_List->Text;
						memcpy(&(sub_menu_parameters->Colors), &(Parameters_List->Default_Parameters.Sub_Menu_Colors), sizeof(sub_menu_parameters->Colors));
						sub_menu_parameters->Option = 1;
						break;

					case AAI_MAIN_MENU_PROCESS :

						main_menu_parameters = process_descriptor->Process_Parameters;
						main_menu_parameters->Parameters_List = Parameters_List;
						main_menu_parameters->Text = Parameters_List->Text;
                  memcpy(&(main_menu_parameters->Colors), &(Parameters_List->Default_Parameters.Main_Menu_Colors), sizeof(main_menu_parameters->Colors));
						main_menu_parameters->Menu_Text = Parameters_List->Menu_Text_List[AAI_MAIN_MENU];
                  main_menu_parameters->Menu_Keys_List = Parameters_List->Menu_Keys_List[AAI_MAIN_MENU];
                  main_menu_parameters->Starting_Row = Parameters_List->Menu_Characteristics_List[AAI_MAIN_MENU].Starting_Row;
                  main_menu_parameters->Starting_Column = Parameters_List->Menu_Characteristics_List[AAI_MAIN_MENU].Starting_Column;
                  main_menu_parameters->Option = Parameters_List->Menu_Characteristics_List[AAI_MAIN_MENU].Option;
                  main_menu_parameters->Total_Options = Parameters_List->Menu_Characteristics_List[AAI_MAIN_MENU].Total_Options;
                  main_menu_parameters->Exit_Flag = FALSE;
                  AAI_Activate_Process(Parameters_List, AAI_MAIN_MENU_PROCESS);
                  break;

               case AAI_FUNCTION_KEY_MENU_PROCESS :

                  function_key_menu_parameters = process_descriptor->Process_Parameters;
                  function_key_menu_parameters->Parameters_List = Parameters_List;
                  function_key_menu_parameters->Text = Parameters_List->Text;
                  function_key_menu_parameters->Menu_Text = Parameters_List->Menu_Text_List[AAI_FUNCTION_KEY_MENU];
                  memcpy(&(function_key_menu_parameters->Colors), &(Parameters_List->Default_Parameters.Function_Key_Menu_Colors), sizeof(function_key_menu_parameters->Colors));
                  function_key_menu_parameters->Starting_Row = Parameters_List->Menu_Characteristics_List[AAI_FUNCTION_KEY_MENU].Starting_Row;
                  function_key_menu_parameters->Starting_Column = Parameters_List->Menu_Characteristics_List[AAI_FUNCTION_KEY_MENU].Starting_Column;
                  function_key_menu_parameters->Hide_Function_Keys_Flag = FALSE;
                  AAI_Activate_Process(Parameters_List, AAI_FUNCTION_KEY_MENU_PROCESS);
                  break;

				}

         }

      }

   }

   return (result);

}

/*

  Function    : AAI_Main
   Description : The main entry point for the MAIN module of the AAI program.
   Inputs      : Nothing.
   Updates     : Nothing.
   Outputs     : Parameters_List = The parameters list to use while the AAI system is active.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 08/18/92 DWP Initial coding.
   Notes       :

*/

int AAI_Main(AAI_PARAMETERS_LIST * Parameters_List) {

   PORT              main_screen;
   CARDINAL_16       key;
   BOOLEAN           exit_flag;
   AAI_PROCESS_TYPES process_number;
   int               result;

   /*

      Initialize the parameters list.  Exit if an error occurs.


   */

   if ((result = AAI_Initialize(Parameters_List)) == EZERO) {

      /*

         Initialize the main port.  Continue only if it was successfully initialized.

		*/

      if ((result = PORT_Constructor(1, 1, 25, 80, PORT_NO_BORDER, LIGHTGRAY, LIGHTGRAY, &main_screen)) == PORT_NOERR) {

         CURSOR_Off();
         AAI_Display_Main_Screen(Parameters_List);

         /*

            Main event loop.

         */

         for (exit_flag = FALSE; !exit_flag && result == 0;) {

            key = (KB_Preview() != 0) ? KB_Read() : 0;

            for (process_number = 0; result == EZERO && process_number < Parameters_List->Total_Processes; process_number++) {

               if (Parameters_List->Process_Descriptor[process_number].Process_Active_Flag) {

                  if (!Parameters_List->Process_Descriptor[AAI_HELP_TOPIC_PROCESS].Process_Active_Flag || process_number == AAI_DISPLAY_TIME_PROCESS || process_number == AAI_HELP_TOPIC_PROCESS || process_number == AAI_FUNCTION_KEY_MENU_PROCESS) {

							if (Parameters_List->Process_Descriptor[process_number].Process != NULL) {

                        result = Parameters_List->Process_Descriptor[process_number].Process(&(Parameters_List->Process_Descriptor[process_number].Process_Parameters), &key);

                     }

                  }

               }

            }

         }

         CURSOR_On();
         result = PORT_Destructor(&main_screen);

      }

   }

   return (result);

}


/*

   Function    : main
   Description : The main entry point for the AAI program.
   Inputs      : The command line.
   Updates     : Nothing.
   Outputs     : Nothing.
   Returns     : Always returns a value of zero.
   Modified    : 08/18/92 DWP Initial coding.
   Notes       :

*/

int main(int argc, char * argv[]) {

   AAI_PARAMETERS_LIST parameters_list;
   struct text_info    text_info;
   struct ffblk        ffblk;
   char                program_file_name[MAXPATH];
   int                 i;

   if (_osmajor < 3 || (_osmajor == 3 && _osminor < 3)) {

      printf("\nAAI Requires MS-DOS Version 3.3 Or Higher\n");

   }
   else {

      setmem(&parameters_list, sizeof(parameters_list), 0);
      parameters_list.Display_Type_Specified = FALSE;
      parameters_list.Port_No_Specified = FALSE;

      /*

         Determine if the default configuration file exists in the current directory.  If it does exist, use the video mode defined in
         it, otherwise, determine what display mode is currently active and use it as the default video mode.

      */

      if (findfirst("AAI.CFG", &ffblk, FA_ARCH) != 0) {

         setmem(&(parameters_list.Default_Parameters), sizeof(parameters_list.Default_Parameters), 0);
         gettextinfo(&text_info);
			parameters_list.Display_Type = (text_info.currmode == 3) ? AAI_COLOR : AAI_MONOCHROME;
         parameters_list.Port_No = 1;

      }

      parameters_list.Version = (stricmp(DIR_Retrieve_File_Name(argv[0], sizeof(program_file_name), program_file_name), "AAIWIN") == 0) ? AAI_WINCHESTER_VERSION : AAI_PLANT_VERSION;

      /*

         Process the command-line parameters.

      */

      for (i = 1; i < argc; i++) {

         if (strchr("-/", argv[i][0]) != NULL) {

            if (stricmp("COLOR", &(argv[i][1])) == 0) {

               parameters_list.Display_Type = AAI_COLOR;
               parameters_list.Display_Type_Specified = TRUE;

            }

            if (stricmp("MONO", &(argv[i][1])) == 0) {

               parameters_list.Display_Type = AAI_MONOCHROME;
               parameters_list.Display_Type_Specified = TRUE;

            }

            if (stricmp("LCD", &(argv[i][1])) == 0) {

               parameters_list.Display_Type = AAI_LCD;
               parameters_list.Display_Type_Specified = TRUE;

            }

            if (stricmp("COM1", &(argv[i][1])) == 0) {

               parameters_list.Port_No = 1;
               parameters_list.Port_No_Specified = TRUE;

            }

            if (stricmp("COM2", &(argv[i][1])) == 0) {

               parameters_list.Port_No = 2;
               parameters_list.Port_No_Specified = TRUE;

            }

         }

      }

      /*

         Invoke the main module.

      */

		AAI_Main(&parameters_list);

   }

   return (0);

}

