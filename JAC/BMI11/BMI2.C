/*

   File        : BMI2.C
   Module      : PROCESSES
   System      : BMI
   Description : This module contains all sub-menu processes for the BMI system.
   Modified    : 08/18/92 DWP Created.
   Notes       :

*/

#include <alloc.h>
#include <conio.h>
#include <ctype.h>
#include <errno.h>
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "CAsynch\Include\asynch_1.h"
#include "Cursor\cursor.h"
#include "MSDOS\msdos.h"
#include "KB\kb.h"
#include "Printer\printer.h"
#include "String\string.h"

#include "bmi.h"

/*

   Procedure   : BMI_Select_File_Print_One_File_Name
   Description : Prints one file name.
   Inputs      : File_List =
                 Position  =
                 Text      =
   Updates     : Nothing.
   Outputs     : Nothing.
   Returns     : Nothing.
   Modified    : 08/18/92 DWP Initial coding.
   Notes       :

*/

void BMI_Select_File_Print_One_File_Name(LIST File_List, CARDINAL_16 Row, CARDINAL_32 Position, TEXT Text) {

   char * current_file_name;
   char   str[MAXFILE];

   LIST_Retrieve(File_List, Position, (void **) &current_file_name);
   TEXT_Set_Cursor_Position(Row + 4, 2, Text);
   sprintf(str, "%-8.8s", (current_file_name != NULL) ? current_file_name : "");
   TEXT_Print_String(str, Text);

}

/*

   Function    : BMI_Select_File_Print_File_Names
   Description : Prints 8 files on the screen.
   Inputs      : Starting_File_Number =
                 File_List            =
                 Text                 =
   Updates     : Nothing.
   Outputs     : Nothing.
   Returns     : Nothing.
   Modified    : 08/18/92 DWP Initial coding.
   Notes       :

*/

void BMI_Select_File_Print_File_Names(CARDINAL_32 Starting_File_Number, LIST File_List, TEXT Text) {

   CARDINAL_16 i;
   CARDINAL_32 last_position;
   char *      current_file_name;

   for (i = 0; i < 8; i++) {

      BMI_Select_File_Print_One_File_Name(File_List, i, Starting_File_Number + i, Text);

   }

   TEXT_Set_Cursor_Position(4, 12, Text);
   TEXT_Print_Character((Starting_File_Number > 1) ? '\x18' : ' ', Text);
   LIST_Retrieve(File_List, LIST_LAST, (void **) &(current_file_name));
   LIST_Current(File_List, &(last_position));
   TEXT_Set_Cursor_Position(11, 12, Text);
   TEXT_Print_Character((last_position > Starting_File_Number + 7) ? '\x19' : ' ', Text);

}

/*

   Function    : BMI_Select_File
   Description : Allows the user to select a file from a list of files in a directory.
   Inputs      : Nothing.
   Updates     : Current_Row          =
                 Current_File_Number  =
                 Previous_File_Number =
                 Key                  =
   Outputs     : File_List            =
		 File_Name            =
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 08/18/92 DWP Initial coding.
   Notes       :

*/

int BMI_Select_File(CARDINAL_16 * Current_Row, CARDINAL_32 * Current_File_Number, CARDINAL_32 * Previous_File_Number, CARDINAL_32 * First_File_Number, BMI_COLORS * Colors, TEXT Text, CARDINAL_16 * Key, LIST * File_List, char * File_Name) {

   CARDINAL_32  total_files;
   BOOLEAN      valid_key_flag, display_light_bar_flag, refresh_screen_flag;
   struct ffblk ffblk;
   char *       current_file_name;
   char         str[MAXFILE];
   int          end_of_directory_indicator, result;

   refresh_screen_flag = FALSE;

   if (*(File_List) != NULL) {

      display_light_bar_flag = FALSE;
      result = EZERO;

   }
   else {

      display_light_bar_flag = TRUE;
      result = LIST_Constructor(MAXFILE, File_List);
      end_of_directory_indicator = findfirst("*.DAT", &(ffblk), 0);

      while (result == LIST_NOERR && end_of_directory_indicator == 0) {

         sprintf(str, "%-8.8s", ffblk.ff_name);

         if (STRING_CharPos(str, '.') != 0) {

            str[STRING_CharPos(str, '.') - 1] = '\0';

         }

         result = LIST_Insert(str, LIST_LAST, *(File_List));
         end_of_directory_indicator = findnext(&(ffblk));

      }

      if (result == LIST_NOERR) {

         refresh_screen_flag = TRUE;

      }

   }

   if (result == EZERO) {

      if (*(Previous_File_Number) != *(Current_File_Number) || display_light_bar_flag) {

         if (*(First_File_Number) + 7 < *(Current_File_Number)) {

            (*(First_File_Number))++;
            refresh_screen_flag = TRUE;

         }
         else {

            if (*(First_File_Number) > *(Current_File_Number)) {

               (*(First_File_Number))--;
               refresh_screen_flag = TRUE;

            }

         }

         if (refresh_screen_flag) {

            TEXT_Set_Text_Color(Colors->Primary_Color, Text);
            BMI_Select_File_Print_File_Names(*(First_File_Number), *(File_List), Text);

         }
         else {

            TEXT_Set_Text_Color(Colors->Primary_Color, Text);
            BMI_Select_File_Print_One_File_Name(*(File_List), *(Current_Row), *(Previous_File_Number), Text);

         }

         if (*(Current_File_Number) > *(Previous_File_Number)) {

            *(Current_Row) = (*(Current_Row) < 7) ? *(Current_Row) + 1 : 7;

         }
         else {

            if (*(Current_File_Number) < *(Previous_File_Number)) {

               *(Current_Row) = (*(Current_Row) > 0) ? *(Current_Row) - 1 : 0;

            }

         }

         TEXT_Set_Text_Color(Colors->Primary_Highlight_Color, Text);
         BMI_Select_File_Print_One_File_Name(*(File_List), *(Current_Row), *(Current_File_Number), Text);

         *(Previous_File_Number) = *(Current_File_Number);


      }

      valid_key_flag = TRUE;

      switch (*(Key)) {

         case KB_UP :
         case KB_GRAY_UP :
         case KB_SHIFT_TAB :

            *(Current_File_Number) = (*(Current_File_Number) > 1) ? *(Current_File_Number) - 1 : 1;
            break;

         case KB_DOWN :
         case KB_GRAY_DOWN :
         case KB_TAB :

            LIST_Retrieve(*(File_List), LIST_LAST, (void **) &(current_file_name));
            LIST_Current(*(File_List), &(total_files));
            *(Current_File_Number) = (*(Current_File_Number) < total_files) ? *(Current_File_Number) + 1 : total_files;
            break;

         case KB_ENTER :
         case KB_GRAY_ENTER :

            LIST_Retrieve(*(File_List), LIST_FIRST, (void **) &(current_file_name));
            LIST_Retrieve(*(File_List), *(Current_File_Number), (void **) &(current_file_name));
            sprintf(File_Name, "%.8s", current_file_name);
            break;

         default :

            valid_key_flag = FALSE;

      }

      if (valid_key_flag) {

         *(Key) = 0;

      }

   }

   return (result);

}

/*

   Function    : BMI_Load_File
   Description : Allows the user to load a data file into memory.
   Inputs      : Nothing.
   Updates     : Process_Parameters =
                 Key                =
   Outputs     : Nothing.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 08/18/92 DWP Initial coding.
   Notes       :

*/

int BMI_File_Load(void ** Process_Parameters, CARDINAL_16 * Key) {

   BMI_FILE_LOAD_PARAMETERS * parameters;
   BOOLEAN                    exit_flag = FALSE;
   int                        result;

   /*

      Validate the parameters.  Exit if either one is invalid.

   */

   if ((result = BMI_Validate_Parameters(Process_Parameters, Key)) == EZERO) {

      /*

	 Initialize the process parameters list for this process.

      */

      if (*(Process_Parameters) == NULL) {

         result = BMI_Allocate_Parameters_List(sizeof(*(parameters)), Process_Parameters);

      }
      else {

	 /*

	    Perform the main function of this process.

	 */

         parameters = *(Process_Parameters);
         BMI_Set_Help_Screen(parameters->Parameters_List, BMI_Help_Index_Key_List[BMI_HELP_LODFM]);

         if (parameters->Port != NULL) {

            result = PORT_Activate(parameters->Port);

         }
         else {

            if ((result = PORT_Constructor(parameters->Starting_Row, parameters->Starting_Column, parameters->Height, parameters->Width, PORT_SINGLE_LINE_BORDER, parameters->Colors.Primary_Color, parameters->Colors.Primary_Color, &(parameters->Port))) == PORT_NOERR) {

               TEXT_Set_Cursor_Position(2, 2, parameters->Text);
               TEXT_Print_String("Load A File", parameters->Text);
               parameters->File_Name[0] = '\0';

            }

         }

         if (result == EZERO) {

            result = BMI_Select_File(&(parameters->Current_Row), &(parameters->Current_File_Number), &(parameters->Previous_File_Number), &(parameters->First_File_Number), &(parameters->Colors), parameters->Text, Key, &(parameters->File_List), parameters->File_Name);

            if (*(Key) == KB_ESC) {

               exit_flag = TRUE;

            }

            if (parameters->File_Name[0] != '\0') {

               exit_flag = TRUE;
               result = BMI_Load_Edit_Parameters(parameters->File_Name, parameters->Edit_Parameters);

            }

            if (exit_flag) {

               LIST_Destructor(&(parameters->File_List));
               PORT_Destructor(&(parameters->Port));
               BMI_Halt_Process(parameters->Parameters_List, BMI_FILE_LOAD_PROCESS);
               BMI_Activate_Process(parameters->Parameters_List, BMI_MAIN_MENU_PROCESS);
               *(Key) = 0;

            }

         }

      }

   }

   return (result);

}

/*

   Function    : BMI_Load_New
   Description : Allows the user to clear memory.
   Inputs      : Nothing.
   Updates     : Process_Parameters =
                 Key                =
   Outputs     : Nothing.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 08/18/92 DWP Initial coding.
   Notes       :

*/

int BMI_File_New(void ** Process_Parameters, CARDINAL_16 * Key) {

   BMI_FILE_NEW_PARAMETERS * parameters;
   int                       result;

   /*

      Validate the parameters.  Exit if either one is invalid.

   */

   if ((result = BMI_Validate_Parameters(Process_Parameters, Key)) == EZERO) {

      /*

	 Initialize the process parameters list for this process.

      */

      if (*(Process_Parameters) == NULL) {

         result = BMI_Allocate_Parameters_List(sizeof(*(parameters)), Process_Parameters);

      }
      else {

	 /*

	    Perform the main function of this process.

	 */

         parameters = *(Process_Parameters);
         BMI_Set_Help_Screen(parameters->Parameters_List, BMI_Help_Index_Key_List[BMI_HELP_NEWFM]);

         if (parameters->Process_In_Progress_Flag) {

            if ((int) parameters->Clear_Memory_Flag != 255) {

               if (parameters->Clear_Memory_Flag) {

                  BMI_Clear_Edit_Parameters(parameters->Edit_Parameters);
                  parameters->Load_Parameters->File_Name[0] = '\0';

               }

               parameters->Process_In_Progress_Flag = FALSE;
               BMI_Halt_Process(parameters->Parameters_List, BMI_FILE_NEW_PROCESS);
               BMI_Activate_Process(parameters->Parameters_List, BMI_MAIN_MENU_PROCESS);
            }

         }
         else {

            BMI_Activate_Process(parameters->Parameters_List, BMI_YES_NO_MENU_PROCESS);

            ((BMI_YES_NO_MENU_PARAMETERS *) parameters->Parameters_List->Process_Descriptor[BMI_YES_NO_MENU_PROCESS].Process_Parameters)->Starting_Row = 9;
            ((BMI_YES_NO_MENU_PARAMETERS *) parameters->Parameters_List->Process_Descriptor[BMI_YES_NO_MENU_PROCESS].Process_Parameters)->Starting_Column = 21;
            ((BMI_YES_NO_MENU_PARAMETERS *) parameters->Parameters_List->Process_Descriptor[BMI_YES_NO_MENU_PROCESS].Process_Parameters)->Display_Message = "Clear Current Times, Are You Sure?";
            ((BMI_YES_NO_MENU_PARAMETERS *) parameters->Parameters_List->Process_Descriptor[BMI_YES_NO_MENU_PROCESS].Process_Parameters)->Option = 1;
            ((BMI_YES_NO_MENU_PARAMETERS *) parameters->Parameters_List->Process_Descriptor[BMI_YES_NO_MENU_PROCESS].Process_Parameters)->Invoking_Process = BMI_MAIN_MENU_PROCESS;
            ((BMI_YES_NO_MENU_PARAMETERS *) parameters->Parameters_List->Process_Descriptor[BMI_YES_NO_MENU_PROCESS].Process_Parameters)->Yes_Selected_Flag = &(((BMI_FILE_NEW_PARAMETERS *) parameters->Parameters_List->Process_Descriptor[BMI_FILE_NEW_PROCESS].Process_Parameters)->Clear_Memory_Flag);

            parameters->Clear_Memory_Flag = -1;
            parameters->Process_In_Progress_Flag = TRUE;

         }

         result = EZERO;

      }

   }

   return (result);

}

/*

   Function    : BMI_File_Save
   Description : The process used to save bender configurations to disk.
   Inputs      : Process_Parameters =
                 Key                =
   Updates     : Nothing.
   Outputs     : Nothing.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 08/18/92 DWP Initial coding.
   Notes       :

*/

int BMI_File_Save(void ** Process_Parameters, CARDINAL_16 * Key) {

   BMI_FILE_SAVE_PARAMETERS * parameters;
   BOOLEAN                    exit_flag = FALSE;
   char                       str[9];
   int                        result;

   /*

      Validate the parameters.  Exit if either one is invalid.

   */

   if ((result = BMI_Validate_Parameters(Process_Parameters, Key)) == EZERO) {

      /*

	 Initialize the process parameters list for this process.

      */

      if (*(Process_Parameters) == NULL) {

         result = BMI_Allocate_Parameters_List(sizeof(*(parameters)), Process_Parameters);

      }
      else {

	 /*

	    Perform the main function of this process.

	 */

         parameters = *(Process_Parameters);

         if (parameters->Load_Parameters->File_Name[7] != '\xff') {

            BMI_Set_Help_Screen(parameters->Parameters_List, BMI_Help_Index_Key_List[BMI_HELP_SAVFM]);

         }

         if (parameters->Load_Parameters->File_Name[0] != '\0') {

            result = BMI_Save_Edit_Parameters(parameters->Load_Parameters->File_Name, parameters->Edit_Parameters);
            exit_flag = TRUE;

         }
         else {

            if (parameters->Port != NULL) {

               result = PORT_Activate(parameters->Port);

            }
            else {

               if ((result = PORT_Constructor(parameters->Starting_Row, parameters->Starting_Column, parameters->Height, parameters->Width, PORT_SINGLE_LINE_BORDER, parameters->Colors.Primary_Color, parameters->Colors.Primary_Color, &(parameters->Port))) == PORT_NOERR) {

                  TEXT_Set_Cursor_Position(2, 2, parameters->Text);
                  TEXT_Print_String("Save As File", parameters->Text);
                  parameters->File_Name.Refresh_Flag = TRUE;
                  BMI_Input(&(parameters->File_Name), Key);

               }

            }

            if (result == EZERO) {

               switch (*(Key)) {

                  case KB_ENTER :
                  case KB_GRAY_ENTER :
                  case KB_TAB :

                     sprintf(str, "%-.8s", parameters->File_Name.Value);
                     STRING_Trim(STRING_TRIM_SPACE, STRING_ATrim(str));

                     if (STRING_CharPos(str, '.') > 0) {

                        str[STRING_CharPos(str, '.') - 1] = '\0';

                     }

                     if (str[0] != '\0') {

                        strcpy(parameters->Load_Parameters->File_Name, str);

                     }

                     *(Key) = 0;
                     break;

                  case KB_ESC :

                     parameters->Load_Parameters->File_Name[0] = '\0';
                     exit_flag = TRUE;
                     *(Key) = 0;
                     break;

               }

               BMI_Input(&(parameters->File_Name), Key);

            }

         }

         if (exit_flag) {

            if (parameters->Port != NULL) {

               PORT_Destructor(&(parameters->Port));

            }

            BMI_Halt_Process(parameters->Parameters_List, BMI_FILE_SAVE_PROCESS);
            BMI_Activate_Process(parameters->Parameters_List, BMI_MAIN_MENU_PROCESS);

         }

      }

   }

   return (result);

}

/*

   Function    : BMI_File_Save_As
   Description : The process used to save bender configurations to disk.
   Inputs      : Process_Parameters =
                 Key                =
   Updates     : Nothing.
   Outputs     : Nothing.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 08/18/92 DWP Initial coding.
   Notes       :

*/

int BMI_File_Save_As(void ** Process_Parameters, CARDINAL_16 * Key) {

   BMI_FILE_SAVE_AS_PARAMETERS * parameters;
   int                           result;

   /*

      Validate the parameters.  Exit if either one is invalid.

   */

   if ((result = BMI_Validate_Parameters(Process_Parameters, Key)) == EZERO) {

      /*

	 Initialize the process parameters list for this process.

      */

      if (*(Process_Parameters) == NULL) {

         result = BMI_Allocate_Parameters_List(sizeof(*(parameters)), Process_Parameters);

      }
      else {

	 /*

	    Perform the main function of this process.

	 */

         parameters = *(Process_Parameters);
         BMI_Set_Help_Screen(parameters->Parameters_List, BMI_Help_Index_Key_List[BMI_HELP_SVAFM]);
         parameters->Load_Parameters->File_Name[0] = '\0';
         parameters->Load_Parameters->File_Name[7] = '\xff';
         BMI_Halt_Process(parameters->Parameters_List, BMI_FILE_SAVE_AS_PROCESS);
         BMI_Activate_Process(parameters->Parameters_List, BMI_FILE_SAVE_PROCESS);

      }

   }

   return (result);

}

/*

   Function    : BMI_Load_Delete
   Description : Allows the user to delete a data file.
   Inputs      : Nothing.
   Updates     : Process_Parameters =
                 Key                =
   Outputs     : Nothing.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 08/18/92 DWP Initial coding.
   Notes       :

*/

int BMI_File_Delete(void ** Process_Parameters, CARDINAL_16 * Key) {

   BMI_FILE_DELETE_PARAMETERS * parameters;
   BOOLEAN                      exit_flag = FALSE;
   char                         whole_file_name[MAXPATH];
   int                          result;

   /*

      Validate the parameters.  Exit if either one is invalid.

   */

   if ((result = BMI_Validate_Parameters(Process_Parameters, Key)) == EZERO) {

      /*

	 Initialize the process parameters list for this process.

      */

      if (*(Process_Parameters) == NULL) {

         result = BMI_Allocate_Parameters_List(sizeof(*(parameters)), Process_Parameters);

      }
      else {

	 /*

	    Perform the main function of this process.

	 */

         parameters = *(Process_Parameters);
         BMI_Set_Help_Screen(parameters->Parameters_List, BMI_Help_Index_Key_List[BMI_HELP_DELFM]);

         if (parameters->Port != NULL) {

            result = PORT_Activate(parameters->Port);

         }
         else {

            if ((result = PORT_Constructor(parameters->Starting_Row, parameters->Starting_Column, parameters->Height, parameters->Width, PORT_SINGLE_LINE_BORDER, parameters->Colors.Primary_Color, parameters->Colors.Primary_Color, &(parameters->Port))) == PORT_NOERR) {

               TEXT_Set_Cursor_Position(2, 2, parameters->Text);
               TEXT_Print_String("Delete A File", parameters->Text);
               parameters->File_Name[0] = '\0';
               parameters->Delete_File_Flag = -1;

            }

         }

         if (result == EZERO) {

            if (parameters->File_Name[0] == '\0') {

               result = BMI_Select_File(&(parameters->Current_Row), &(parameters->Current_File_Number), &(parameters->Previous_File_Number), &(parameters->First_File_Number), &(parameters->Colors), parameters->Text, Key, &(parameters->File_List), parameters->File_Name);

               if (*(Key) == KB_ESC) {

                  exit_flag = TRUE;

               }

            }
            else {

               if (parameters->Process_In_Progress_Flag) {

                  sprintf(whole_file_name, "%-.8s.DAT", parameters->File_Name);

                  if ((int) parameters->Delete_File_Flag != -1) {

                     if (parameters->Delete_File_Flag) {

                        unlink(whole_file_name);

                     }

                     parameters->Process_In_Progress_Flag = FALSE;
                     BMI_Halt_Process(parameters->Parameters_List, BMI_FILE_DELETE_PROCESS);
                     BMI_Activate_Process(parameters->Parameters_List, BMI_MAIN_MENU_PROCESS);
                     exit_flag = TRUE;

                  }

               }
               else {

                  BMI_Activate_Process(parameters->Parameters_List, BMI_YES_NO_MENU_PROCESS);

                  ((BMI_YES_NO_MENU_PARAMETERS *) parameters->Parameters_List->Process_Descriptor[BMI_YES_NO_MENU_PROCESS].Process_Parameters)->Starting_Row = 9;
                  ((BMI_YES_NO_MENU_PARAMETERS *) parameters->Parameters_List->Process_Descriptor[BMI_YES_NO_MENU_PROCESS].Process_Parameters)->Starting_Column = 21;
                  ((BMI_YES_NO_MENU_PARAMETERS *) parameters->Parameters_List->Process_Descriptor[BMI_YES_NO_MENU_PROCESS].Process_Parameters)->Display_Message = "Delete File, Are You Sure?";
                  ((BMI_YES_NO_MENU_PARAMETERS *) parameters->Parameters_List->Process_Descriptor[BMI_YES_NO_MENU_PROCESS].Process_Parameters)->Option = 1;
                  ((BMI_YES_NO_MENU_PARAMETERS *) parameters->Parameters_List->Process_Descriptor[BMI_YES_NO_MENU_PROCESS].Process_Parameters)->Invoking_Process = BMI_FILE_DELETE_PROCESS;
                  ((BMI_YES_NO_MENU_PARAMETERS *) parameters->Parameters_List->Process_Descriptor[BMI_YES_NO_MENU_PROCESS].Process_Parameters)->Yes_Selected_Flag = &(((BMI_FILE_DELETE_PARAMETERS *) parameters->Parameters_List->Process_Descriptor[BMI_FILE_DELETE_PROCESS].Process_Parameters)->Delete_File_Flag);

                  parameters->Delete_File_Flag = -1;
                  parameters->Process_In_Progress_Flag = TRUE;

               }

            }

            if (exit_flag) {

               LIST_Destructor(&(parameters->File_List));
               PORT_Destructor(&(parameters->Port));
               BMI_Halt_Process(parameters->Parameters_List, BMI_FILE_DELETE_PROCESS);
               BMI_Activate_Process(parameters->Parameters_List, BMI_MAIN_MENU_PROCESS);
               *(Key) = 0;

            }

         }

      }

   }

   return (result);

}

/*

   Function    : BMI_File_Rename
   Description : Allows the user to rename a data file.
   Inputs      : Nothing.
   Updates     : Process_Parameters =
                 Key                =
   Outputs     : Nothing.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 08/18/92 DWP Initial coding.
   Notes       :

*/

int BMI_File_Rename(void ** Process_Parameters, CARDINAL_16 * Key) {

   BMI_FILE_RENAME_PARAMETERS * parameters;
   BOOLEAN                      exit_flag = FALSE;
   char                         str[9], old_file_name[MAXPATH], new_file_name[MAXPATH];
   int                          result;

   /*

      Validate the parameters.  Exit if either one is invalid.

   */

   if ((result = BMI_Validate_Parameters(Process_Parameters, Key)) == EZERO) {

      /*

	 Initialize the process parameters list for this process.

      */

      if (*(Process_Parameters) == NULL) {

         result = BMI_Allocate_Parameters_List(sizeof(*(parameters)), Process_Parameters);

      }
      else {

	 /*

	    Perform the main function of this process.

	 */

         parameters = *(Process_Parameters);
         BMI_Set_Help_Screen(parameters->Parameters_List, BMI_Help_Index_Key_List[BMI_HELP_RENFM]);

         if (parameters->Port != NULL) {

            result = PORT_Activate(parameters->Port);

         }
         else {

            if ((result = PORT_Constructor(parameters->Starting_Row, parameters->Starting_Column, parameters->Height, parameters->Width, PORT_SINGLE_LINE_BORDER, parameters->Colors.Primary_Color, parameters->Colors.Primary_Color, &(parameters->Port))) == PORT_NOERR) {

               TEXT_Set_Cursor_Position(2, 2, parameters->Text);
               TEXT_Print_String("Rename File", parameters->Text);
               parameters->New_File_Name.Refresh_Flag = TRUE;
               parameters->Current_File_Name[0] = '\0';

            }

         }

         if (result == EZERO) {

            if (parameters->Current_File_Name[0] == '\0') {

               result = BMI_Select_File(&(parameters->Current_Row), &(parameters->Current_File_Number), &(parameters->Previous_File_Number), &(parameters->First_File_Number), &(parameters->Colors), parameters->Text, Key, &(parameters->File_List), parameters->Current_File_Name);

               if (*(Key) == KB_ESC) {

                  exit_flag = TRUE;

               }

            }
            else {

               if (parameters->New_File_Port != NULL) {

                  result = PORT_Activate(parameters->New_File_Port);

               }
               else {

                  if ((result = PORT_Constructor(parameters->New_File_Starting_Row, parameters->New_File_Starting_Column, parameters->New_File_Height, parameters->New_File_Width, PORT_SINGLE_LINE_BORDER, parameters->Colors.Primary_Color, parameters->Colors.Primary_Color, &(parameters->New_File_Port))) == PORT_NOERR) {

                     TEXT_Set_Cursor_Position(2, 2, parameters->Text);
                     TEXT_Print_String("As File", parameters->Text);
                     parameters->New_File_Name.Refresh_Flag = TRUE;

                  }

               }

               switch (*(Key)) {

                  case KB_ENTER :
                  case KB_GRAY_ENTER :
                  case KB_TAB :

                     sprintf(str, "%-.8s", parameters->New_File_Name.Value);
                     STRING_Trim(STRING_TRIM_SPACE, STRING_ATrim(str));

                     if (STRING_CharPos(str, '.') > 0) {

                        str[STRING_CharPos(str, '.') - 1] = '\0';

                     }

                     if (str[0] != '\0') {

                        strcpy(parameters->New_File_Name.Value, str);
                        sprintf(old_file_name, "%-.8s.DAT", parameters->Current_File_Name);
                        sprintf(new_file_name, "%-.8s.DAT", parameters->New_File_Name.Value);
                        rename(old_file_name, new_file_name);

                     }

                     exit_flag = TRUE;
                     break;

                  case KB_ESC :

                     exit_flag = TRUE;
                     break;

               }

               BMI_Input(&(parameters->New_File_Name), Key);

            }

            if (exit_flag) {

               LIST_Destructor(&(parameters->File_List));
               PORT_Destructor(&(parameters->New_File_Port));
               PORT_Destructor(&(parameters->Port));
               BMI_Halt_Process(parameters->Parameters_List, BMI_FILE_RENAME_PROCESS);
               BMI_Activate_Process(parameters->Parameters_List, BMI_MAIN_MENU_PROCESS);
               *(Key) = 0;

            }

         }

      }

   }

   return (result);

}

/*

   Function    : BMI_File_Quit
   Description : The process used to exit from the BMI system.
   Inputs      : Process_Parameters =
                 Key                =
   Updates     : Nothing.
   Outputs     : Nothing.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 08/18/92 DWP Initial coding.
   Notes       :

*/

int BMI_File_Quit(void ** Process_Parameters, CARDINAL_16 * Key) {

   BMI_FILE_QUIT_PARAMETERS * parameters;
   int                        result;

   /*

      Validate the parameters.  Exit if either one is invalid.

   */

   if ((result = BMI_Validate_Parameters(Process_Parameters, Key)) == EZERO) {

      /*

	 Initialize the process parameters list for this process.

      */

      if (*(Process_Parameters) == NULL) {

         result = BMI_Allocate_Parameters_List(sizeof(*(parameters)), Process_Parameters);

      }
      else {

	 /*

	    Perform the main function of this process.

	 */

         parameters = *(Process_Parameters);
         BMI_Set_Help_Screen(parameters->Parameters_List, BMI_Help_Index_Key_List[BMI_HELP_QUIFM]);

         BMI_Halt_Process(parameters->Parameters_List, BMI_MAIN_MENU_PROCESS);
         BMI_Activate_Process(parameters->Parameters_List, BMI_YES_NO_MENU_PROCESS);

         ((BMI_YES_NO_MENU_PARAMETERS *) parameters->Parameters_List->Process_Descriptor[BMI_YES_NO_MENU_PROCESS].Process_Parameters)->Starting_Row = 9;
         ((BMI_YES_NO_MENU_PARAMETERS *) parameters->Parameters_List->Process_Descriptor[BMI_YES_NO_MENU_PROCESS].Process_Parameters)->Starting_Column = 25;
         ((BMI_YES_NO_MENU_PARAMETERS *) parameters->Parameters_List->Process_Descriptor[BMI_YES_NO_MENU_PROCESS].Process_Parameters)->Display_Message = "Exit Program, Are You Sure?";
         ((BMI_YES_NO_MENU_PARAMETERS *) parameters->Parameters_List->Process_Descriptor[BMI_YES_NO_MENU_PROCESS].Process_Parameters)->Option = 1;
         ((BMI_YES_NO_MENU_PARAMETERS *) parameters->Parameters_List->Process_Descriptor[BMI_YES_NO_MENU_PROCESS].Process_Parameters)->Invoking_Process = BMI_MAIN_MENU_PROCESS;
         ((BMI_YES_NO_MENU_PARAMETERS *) parameters->Parameters_List->Process_Descriptor[BMI_YES_NO_MENU_PROCESS].Process_Parameters)->Yes_Selected_Flag = &(((BMI_MAIN_MENU_PARAMETERS *) parameters->Parameters_List->Process_Descriptor[BMI_MAIN_MENU_PROCESS].Process_Parameters)->Exit_Flag);

         BMI_Halt_Process(parameters->Parameters_List, BMI_FILE_QUIT_PROCESS);

         result = EZERO;

      }

   }

   return (result);

}

/*

   Procedure   : BMI_Edit_Print_Labels
   Description :
   Inputs      : Starting_Label = The value of the first label to print.
                 Text           = The text descriptor to write in.
   Updates     : Nothing.
   Outputs     : Nothing.
   Returns     : Nothing.
   Modified    : 08/18/92 DWP Initial coding.
   Notes       :

*/

void BMI_Edit_Print_Labels(BMI_EDIT_EDIT_PARAMETERS * Process_Parameters, CARDINAL_16 * Key) {

   CARDINAL_16 i, j, k;
   char        str[6];

   for (i = 0; i < 8; i++) {

      TEXT_Set_Cursor_Position(4 + (i * 2), 2, Process_Parameters->Text);
      TEXT_Set_Text_Color(Process_Parameters->Colors.Primary_Color, Process_Parameters->Text);
      sprintf(str, "%02u-%02u", Process_Parameters->Top_Row_Starting_Number + (i * 5), Process_Parameters->Top_Row_Starting_Number + (i * 5) + 4);
      TEXT_Print_String(str, Process_Parameters->Text);

      for (j = 0; j < 5; j++) {

         k = Process_Parameters->Top_Row_Starting_Number + (i * 5) + j - 1;

         Process_Parameters->Advance_Time[k].Current_Row = 4 + (i * 2);
         Process_Parameters->Advance_Time[k].Current_Column = 9 + (j * 14);
         Process_Parameters->Advance_Time[k].Refresh_Flag = TRUE;
         BMI_Input(&(Process_Parameters->Advance_Time[k]), Key);

         Process_Parameters->Retract_Time[k].Current_Row = 4 + (i * 2);
         Process_Parameters->Retract_Time[k].Current_Column = 15 + (j * 14);
         Process_Parameters->Retract_Time[k].Refresh_Flag = TRUE;
         BMI_Input(&(Process_Parameters->Retract_Time[k]), Key);

      }

   }

}

/*

   Procedure   : BMI_Edit_Update_Process_Parameters
   Description : Updates the edit processing parameters.
   Inputs      : Update_Top_Row_Starting_Number_Flag
                 Top_Row_Starting_Number_Increment_Value
   Updates     : Process_Parameters
   Outputs     : Nothing.
   Returns     : Nothing.
   Modified    : 08/18/92 DWP Initial coding.
   Notes       :

*/

void BMI_Edit_Update_Process_Parameters(BOOLEAN Update_Top_Row_Starting_Number_Flag, int Top_Row_Starting_Number_Increment_Value, BMI_EDIT_EDIT_PARAMETERS * Process_Parameters) {

   char str[256];

   if (Process_Parameters->Current_Field_Descriptor->Type == INTEGER_16_TYPE) {

      if (Process_Parameters->Current_Field_Descriptor->Maximum_Editable_Value < atoi(Process_Parameters->Current_Field_Descriptor->Value) || Process_Parameters->Current_Field_Descriptor->Minimum_Value > atoi(Process_Parameters->Current_Field_Descriptor->Value)) {

         sprintf(str, "%*d", Process_Parameters->Current_Field_Descriptor->Display_Length, Process_Parameters->Current_Field_Descriptor->Integer_Value);
         strncpy(Process_Parameters->Current_Field_Descriptor->Value, str, /* 4 */ Process_Parameters->Current_Field_Descriptor->Display_Length);

      }

      Process_Parameters->Current_Field_Descriptor->Integer_Value = atoi(Process_Parameters->Current_Field_Descriptor->Value);

      if (Process_Parameters->Current_Field_Descriptor->Integer_Value < 0) {

         Process_Parameters->Current_Field_Descriptor->Integer_Value *= -1;

      }

      sprintf(str, "%*d", Process_Parameters->Current_Field_Descriptor->Display_Length, Process_Parameters->Current_Field_Descriptor->Integer_Value);
      strncpy(Process_Parameters->Current_Field_Descriptor->Value, str, /* 4 */ Process_Parameters->Current_Field_Descriptor->Display_Length);
      Process_Parameters->Current_Field_Descriptor->Refresh_Flag = TRUE;
      BMI_Input(Process_Parameters->Current_Field_Descriptor, NULL);

   }

   if (Top_Row_Starting_Number_Increment_Value >= 0) {

      Process_Parameters->Field = (Process_Parameters->Field >= BMI_TOTAL_EDIT_FIELDS) ? BMI_TOTAL_EDIT_FIELDS : Process_Parameters->Field + 1;

   }
   else {

      Process_Parameters->Field = (Process_Parameters->Field > 1) ? Process_Parameters->Field - 1 : 1;

   }

   if (Update_Top_Row_Starting_Number_Flag) {

      Process_Parameters->Top_Row_Starting_Number += Top_Row_Starting_Number_Increment_Value;
      Process_Parameters->Redraw_Timing_Values_Flag = TRUE;

   }

}

/*

   Procedure   : BMI_Edit_Set_Refresh_Flag
   Description :
   Inputs      : Process_Parameters
   Updates     : Nothing.
   Outputs     : Nothing.
   Returns     : Nothing.
   Modified    : 08/15/82 DWP Initial coding.
   Notes       :

*/

void BMI_Edit_Set_Refresh_Flag(BMI_EDIT_EDIT_PARAMETERS * Process_Parameters) {

   int i;

   Process_Parameters->Part_Number.Refresh_Flag = TRUE;
   Process_Parameters->Valve_Pack_Number.Refresh_Flag = TRUE;
   Process_Parameters->Multiple_Part_Number.Refresh_Flag = TRUE;
   Process_Parameters->Last_Bin_Sensor.Refresh_Flag = TRUE;
   Process_Parameters->Total_Cycle_Time.Refresh_Flag = TRUE;

   for (i = 0; i < 80; i++) {

      Process_Parameters->Advance_Time[i].Refresh_Flag = TRUE;
      Process_Parameters->Retract_Time[i].Refresh_Flag = TRUE;

   }

}

/*

   Procedure   : BMI_Edit_Set_First_Pass_Flag
   Description :
   Inputs      : Process_Parameters
   Updates     : Nothing.
   Outputs     : Nothing.
   Returns     : Nothing.
   Modified    : 08/15/82 DWP Initial coding.
   Notes       :

*/

void BMI_Edit_Set_First_Pass_Flag(BMI_EDIT_EDIT_PARAMETERS * Process_Parameters) {

   int i;

   Process_Parameters->Part_Number.First_Pass_Flag = TRUE;
   Process_Parameters->Valve_Pack_Number.First_Pass_Flag = TRUE;
   Process_Parameters->Multiple_Part_Number.First_Pass_Flag = TRUE;
   Process_Parameters->Last_Bin_Sensor.First_Pass_Flag = TRUE;
   Process_Parameters->Total_Cycle_Time.First_Pass_Flag = TRUE;

   for (i = 0; i < 80; i++) {

      Process_Parameters->Advance_Time[i].First_Pass_Flag = TRUE;
      Process_Parameters->Retract_Time[i].First_Pass_Flag = TRUE;

   }

}

/*

   Procedure   : BMI_Edit_Initialize_Current_Offset
   Description :
   Inputs      : Process_Parameters
   Updates     : Nothing.
   Outputs     : Nothing.
   Returns     : Nothing.
   Modified    : 08/15/82 DWP Initial coding.
   Notes       :

*/

void BMI_Edit_Initialize_Current_Offset(BMI_EDIT_EDIT_PARAMETERS * Process_Parameters) {

   int i;

   Process_Parameters->Part_Number.Current_Offset = 0;
   Process_Parameters->Valve_Pack_Number.Current_Offset = 0;
   Process_Parameters->Multiple_Part_Number.Current_Offset = 0;
   Process_Parameters->Last_Bin_Sensor.Current_Offset = 0;
   Process_Parameters->Total_Cycle_Time.Current_Offset = 0;

   for (i = 0; i < 80; i++) {

      Process_Parameters->Advance_Time[i].Current_Offset = 0;
      Process_Parameters->Retract_Time[i].Current_Offset = 0;

   }

}

/*

   Procedure   : BMI_Edit_Special_Processing
   Description :
   Inputs      : Process_Parameters                  =
   Updates     : Nothing.
   Outputs     : Update_Top_Row_Starting_Number_Flag =
                 Timing_Values_Altered_Flag          =
   Returns     : Nothing.
   Modified    : 08/18/92 DWP Initial coding.
   Notes       :

*/

void BMI_Edit_Special_Processing(BMI_EDIT_EDIT_PARAMETERS * Process_Parameters, BOOLEAN * Update_Top_Row_Starting_Number_Flag, BOOLEAN * Timing_Values_Altered_Flag) {

   INTEGER_16 displacement_value, previous_value;
   int        i;

   if (Process_Parameters->Field >= BMI_TOTAL_UNIQUE_EDIT_FIELDS) {

      STRING_ATrim(Process_Parameters->Current_Field_Descriptor->Value);
      displacement_value = atoi(Process_Parameters->Current_Field_Descriptor->Value);
      previous_value = (STRING_CharPos("+-", Process_Parameters->Current_Field_Descriptor->Value[0]) == 0) ? 0 : Process_Parameters->Current_Field_Descriptor->Integer_Value;

      if (previous_value + displacement_value >= Process_Parameters->Current_Field_Descriptor->Minimum_Value && previous_value + displacement_value <= Process_Parameters->Current_Field_Descriptor->Maximum_Editable_Value) {

         if (Process_Parameters->Current_Field_Descriptor->Value[0] == '+' || Process_Parameters->Current_Field_Descriptor->Value[0] == '-') {

            if (previous_value == 0) {

               Process_Parameters->Current_Field_Descriptor->Integer_Value = atoi(Process_Parameters->Current_Field_Descriptor->Value);
               sprintf(Process_Parameters->Current_Field_Descriptor->Value, "%*d", Process_Parameters->Current_Field_Descriptor->Display_Length, Process_Parameters->Current_Field_Descriptor->Integer_Value);

            }
            else {

               *(Timing_Values_Altered_Flag) = TRUE;

               for (i = (Process_Parameters->Field - BMI_TOTAL_UNIQUE_EDIT_FIELDS) / 2; i < (BMI_TOTAL_EDIT_FIELDS - BMI_TOTAL_UNIQUE_EDIT_FIELDS + 1) / 2; i++) {

                  if (Process_Parameters->Advance_Time[i].Integer_Value != 0 && Process_Parameters->Advance_Time[i].Integer_Value >= previous_value) {

                     Process_Parameters->Advance_Time[i].Integer_Value += displacement_value;
                     sprintf(Process_Parameters->Advance_Time[i].Value, "%*d", Process_Parameters->Advance_Time[i].Display_Length, Process_Parameters->Advance_Time[i].Integer_Value);

                  }

                  if (Process_Parameters->Retract_Time[i].Integer_Value != 0 && Process_Parameters->Retract_Time[i].Integer_Value >= previous_value) {

                     Process_Parameters->Retract_Time[i].Integer_Value += displacement_value;
                     sprintf(Process_Parameters->Retract_Time[i].Value, "%*d", Process_Parameters->Retract_Time[i].Display_Length, Process_Parameters->Retract_Time[i].Integer_Value);

                  }

		  /*

		     Make sure the retract time is at least as large as the advance time.

		  */

                  if (Process_Parameters->Retract_Time[i].Integer_Value != 0 && Process_Parameters->Retract_Time[i].Integer_Value <= Process_Parameters->Advance_Time[i].Integer_Value) {

                     Process_Parameters->Retract_Time[i].Integer_Value = atoi(Process_Parameters->Advance_Time[i].Value) + 1;
                     sprintf(Process_Parameters->Retract_Time[i].Value, "%*d", Process_Parameters->Retract_Time[i].Display_Length, Process_Parameters->Retract_Time[i].Integer_Value);

                  }

               }

            }

            Process_Parameters->Redraw_Timing_Values_Flag = TRUE;

         }

         *(Update_Top_Row_Starting_Number_Flag) = TRUE;

	 /*

	    Make sure the retract time is at least as large as the advance time.

	 */

         if (atoi(Process_Parameters->Advance_Time[(Process_Parameters->Field - BMI_TOTAL_UNIQUE_EDIT_FIELDS) / 2].Value) != 0 && atoi(Process_Parameters->Advance_Time[(Process_Parameters->Field - BMI_TOTAL_UNIQUE_EDIT_FIELDS) / 2].Value) >= atoi(Process_Parameters->Retract_Time[(Process_Parameters->Field - BMI_TOTAL_UNIQUE_EDIT_FIELDS) / 2].Value)) {

            Process_Parameters->Retract_Time[(Process_Parameters->Field - BMI_TOTAL_UNIQUE_EDIT_FIELDS) / 2].Integer_Value = atoi(Process_Parameters->Advance_Time[(Process_Parameters->Field - BMI_TOTAL_UNIQUE_EDIT_FIELDS) / 2].Value) + 1;
            sprintf(Process_Parameters->Retract_Time[(Process_Parameters->Field - BMI_TOTAL_UNIQUE_EDIT_FIELDS) / 2].Value, "%*d", Process_Parameters->Retract_Time[(Process_Parameters->Field - BMI_TOTAL_UNIQUE_EDIT_FIELDS) / 2].Display_Length, Process_Parameters->Retract_Time[(Process_Parameters->Field - BMI_TOTAL_UNIQUE_EDIT_FIELDS) / 2].Integer_Value);
            Process_Parameters->Retract_Time[(Process_Parameters->Field - BMI_TOTAL_UNIQUE_EDIT_FIELDS) / 2].Refresh_Flag = TRUE;
            BMI_Input(&(Process_Parameters->Retract_Time[(Process_Parameters->Field - BMI_TOTAL_UNIQUE_EDIT_FIELDS) / 2]), NULL);

	    /*

	       Adjust the total cycle time, if necessary.

	    */

            if (Process_Parameters->Retract_Time[(Process_Parameters->Field - BMI_TOTAL_UNIQUE_EDIT_FIELDS) / 2].Integer_Value > Process_Parameters->Total_Cycle_Time.Integer_Value) {

               sprintf(Process_Parameters->Total_Cycle_Time.Value, "%*d", Process_Parameters->Total_Cycle_Time.Display_Length, Process_Parameters->Retract_Time[(Process_Parameters->Field - BMI_TOTAL_UNIQUE_EDIT_FIELDS) / 2].Integer_Value);
               Process_Parameters->Total_Cycle_Time.Integer_Value = atoi(Process_Parameters->Total_Cycle_Time.Value);
               Process_Parameters->Total_Cycle_Time.Refresh_Flag = TRUE;
               BMI_Input(&(Process_Parameters->Total_Cycle_Time), NULL);

            }

         }

         if (Process_Parameters->Field % 2 == 1 && atoi(Process_Parameters->Current_Field_Descriptor->Value) > atoi(Process_Parameters->Total_Cycle_Time.Value) && atoi(Process_Parameters->Current_Field_Descriptor->Value) <= Process_Parameters->Total_Cycle_Time.Maximum_Editable_Value && atoi(Process_Parameters->Current_Field_Descriptor->Value) >= Process_Parameters->Total_Cycle_Time.Minimum_Value) {

            sprintf(Process_Parameters->Total_Cycle_Time.Value, "%*.*s", Process_Parameters->Total_Cycle_Time.Display_Length, Process_Parameters->Total_Cycle_Time.Display_Length, Process_Parameters->Current_Field_Descriptor->Value);
            Process_Parameters->Total_Cycle_Time.Integer_Value = atoi(Process_Parameters->Current_Field_Descriptor->Value);
            Process_Parameters->Total_Cycle_Time.Refresh_Flag = TRUE;
            BMI_Input(&(Process_Parameters->Total_Cycle_Time), NULL);

         }

         if (Process_Parameters->Field % 2 == 0 && atoi(Process_Parameters->Current_Field_Descriptor->Value) > atoi(Process_Parameters->Last_Bin_Sensor.Value) && atoi(Process_Parameters->Current_Field_Descriptor->Value) <= Process_Parameters->Last_Bin_Sensor.Maximum_Editable_Value && atoi(Process_Parameters->Current_Field_Descriptor->Value) >= Process_Parameters->Last_Bin_Sensor.Minimum_Value) {

            sprintf(Process_Parameters->Last_Bin_Sensor.Value, "%*.*s", Process_Parameters->Last_Bin_Sensor.Display_Length, Process_Parameters->Last_Bin_Sensor.Display_Length, Process_Parameters->Current_Field_Descriptor->Value);
            Process_Parameters->Last_Bin_Sensor.Integer_Value = atoi(Process_Parameters->Current_Field_Descriptor->Value);
            Process_Parameters->Last_Bin_Sensor.Refresh_Flag = TRUE;
            BMI_Input(&(Process_Parameters->Last_Bin_Sensor), NULL);

         }

      }

   }

}

/*

   Function    : BMI_Edit
   Description : Allows the user to edit a set of parameters for a bender.
   Inputs      : Nothing.
   Updates     : Process_Parameters =
                 Key                =
   Outputs     : Nothing.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 08/18/92 DWP Initial coding.
   Notes       :

*/

int BMI_Edit(void ** Process_Parameters, CARDINAL_16 * Key) {

   BMI_EDIT_EDIT_PARAMETERS * parameters;
   BMI_PROCESS_TYPES          new_process;
   CARDINAL_16                previous_field, input_field;
   BOOLEAN                    exit_flag, refresh_flag, new_field_flag, update_top_row_starting_number_flag, timing_values_altered_flag;
   int                        direction, result;

   /*

      Validate the parameters.  Exit if either one is invalid.

   */

   if ((result = BMI_Validate_Parameters(Process_Parameters, Key)) == EZERO) {

      /*

	 Initialize the process parameters list for this process.

      */

      if (*(Process_Parameters) == NULL) {

         result = BMI_Allocate_Parameters_List(sizeof(*(parameters)), Process_Parameters);

      }
      else {

	 /*

	    Perform the main function of this process.

	 */

         parameters = *(Process_Parameters);
         BMI_Set_Help_Screen(parameters->Parameters_List, BMI_Help_Index_Key_List[BMI_HELP_EDTEM]);

         if (parameters->Port != NULL) {

            result = PORT_Activate(parameters->Port);

         }
         else {

            if ((result = PORT_Constructor(parameters->Starting_Row, parameters->Starting_Column, parameters->Height, parameters->Width, PORT_SINGLE_LINE_BORDER, parameters->Colors.Primary_Color, parameters->Colors.Primary_Color, &(parameters->Port))) == PORT_NOERR) {

               TEXT_Set_Cursor_Position(2, 2, parameters->Text);
               TEXT_Print_String("PN", parameters->Text);
               parameters->Part_Number.Refresh_Flag = TRUE;

               TEXT_Set_Cursor_Position(2, 23, parameters->Text);
               TEXT_Print_String("VPN", parameters->Text);
               parameters->Valve_Pack_Number.Refresh_Flag = TRUE;

               TEXT_Set_Cursor_Position(2, 34, parameters->Text);
               TEXT_Print_String("MSN", parameters->Text);
               parameters->Multiple_Part_Number.Refresh_Flag = TRUE;

               TEXT_Set_Cursor_Position(2, 41, parameters->Text);
               TEXT_Print_String("LBS", parameters->Text);
               parameters->Last_Bin_Sensor.Refresh_Flag = TRUE;

               TEXT_Set_Cursor_Position(2, 52, parameters->Text);
               TEXT_Print_String("Total Cycle Time :", parameters->Text);
               parameters->Total_Cycle_Time.Refresh_Flag = TRUE;

               parameters->Field = 1;
               parameters->Top_Row_Starting_Number = 1;
               parameters->Current_Field_Descriptor = &(parameters->Part_Number);
               BMI_Edit_Print_Labels(parameters, Key);

               BMI_Input(&(parameters->Part_Number), Key);
               BMI_Input(&(parameters->Valve_Pack_Number), Key);
               BMI_Input(&(parameters->Multiple_Part_Number), Key);
               BMI_Input(&(parameters->Last_Bin_Sensor), Key);
               BMI_Input(&(parameters->Total_Cycle_Time), Key);

            }

         }

         if (result == EZERO) {

            previous_field = parameters->Field;
            exit_flag = FALSE;

            if (parameters->Redraw_Timing_Values_Flag) {

               BMI_Edit_Print_Labels(parameters, Key);
               parameters->Redraw_Timing_Values_Flag = FALSE;

            }

            direction = 1;

            switch (*(Key)) {

               case KB_ENTER :
               case KB_GRAY_ENTER :
               case KB_TAB :
               case KB_RIGHT :
               case KB_GRAY_RIGHT :

                  timing_values_altered_flag = FALSE;
                  update_top_row_starting_number_flag = FALSE;
                  BMI_Edit_Special_Processing(parameters, &(update_top_row_starting_number_flag), &(timing_values_altered_flag));

                  if ((parameters->Field - ((parameters->Top_Row_Starting_Number - 1) * 2)) >= (80 + BMI_TOTAL_UNIQUE_EDIT_FIELDS - 1) && parameters->Top_Row_Starting_Number < 41) {

                     update_top_row_starting_number_flag = TRUE;

                  }
                  else {

                     update_top_row_starting_number_flag = FALSE;

                  }

                  BMI_Edit_Update_Process_Parameters(update_top_row_starting_number_flag | timing_values_altered_flag, (timing_values_altered_flag) ? 0 : 5, parameters);
                  break;

               case KB_SHIFT_TAB :
               case KB_LEFT :
               case KB_GRAY_LEFT :

                  BMI_Edit_Special_Processing(parameters, &(update_top_row_starting_number_flag), &(timing_values_altered_flag));
                  update_top_row_starting_number_flag = (parameters->Top_Row_Starting_Number > 1 && parameters->Field - ((parameters->Top_Row_Starting_Number - 1) * 2) <= BMI_TOTAL_UNIQUE_EDIT_FIELDS - 1);
                  BMI_Edit_Update_Process_Parameters(update_top_row_starting_number_flag, -5, parameters);
                  direction = -1;
                  break;

               case KB_DOWN :
               case KB_GRAY_DOWN :

                  BMI_Edit_Special_Processing(parameters, &(update_top_row_starting_number_flag), &(timing_values_altered_flag));
                  BMI_Edit_Update_Process_Parameters(FALSE, 0, parameters);
                  parameters->Field--;

                  if (parameters->Field < BMI_TOTAL_UNIQUE_EDIT_FIELDS) {

                     parameters->Field = BMI_TOTAL_UNIQUE_EDIT_FIELDS;

                  }
                  else {

                     if (parameters->Field <= BMI_TOTAL_EDIT_FIELDS - 10) {

                        parameters->Field += 10;

                        if ((parameters->Field - 5 >= parameters->Top_Row_Starting_Number + 80) && parameters->Top_Row_Starting_Number < 41) {

                           parameters->Top_Row_Starting_Number += 5;
                           parameters->Redraw_Timing_Values_Flag = TRUE;

                        }

                     }

                  }

                  break;

               case KB_UP :
               case KB_GRAY_UP :

                  BMI_Edit_Special_Processing(parameters, &(update_top_row_starting_number_flag), &(timing_values_altered_flag));
                  BMI_Edit_Update_Process_Parameters(FALSE, 0, parameters);

                  if (parameters->Field != BMI_TOTAL_EDIT_FIELDS) {

                     parameters->Field--;

                  }

                  if (parameters->Field >= BMI_TOTAL_UNIQUE_EDIT_FIELDS && parameters->Field < BMI_TOTAL_UNIQUE_EDIT_FIELDS + 10) {

                     parameters->Field = 1;

                  }
                  else {

                     if (parameters->Field >= BMI_TOTAL_UNIQUE_EDIT_FIELDS + 10) {

                        parameters->Field -= 10;

                        if (parameters->Field <= ((parameters->Top_Row_Starting_Number - 1) * 2) + BMI_TOTAL_UNIQUE_EDIT_FIELDS - 1) {

                           parameters->Top_Row_Starting_Number -= 5;
                           parameters->Redraw_Timing_Values_Flag = TRUE;

                        }

                     }

                  }

                  direction = -1;
                  break;

               case KB_CTRL_HOME :
               case KB_CTRL_GRAY_HOME :

                  BMI_Edit_Special_Processing(parameters, &(update_top_row_starting_number_flag), &(timing_values_altered_flag));
                  BMI_Edit_Update_Process_Parameters(FALSE, 0, parameters);
                  parameters->Field = 1;
                  parameters->Top_Row_Starting_Number = 1;
                  parameters->Redraw_Timing_Values_Flag = TRUE;
                  break;

               case KB_CTRL_END :
               case KB_CTRL_GRAY_END :

                  BMI_Edit_Special_Processing(parameters, &(update_top_row_starting_number_flag), &(timing_values_altered_flag));
                  BMI_Edit_Update_Process_Parameters(FALSE, 0, parameters);
                  parameters->Field = BMI_TOTAL_EDIT_FIELDS;
                  parameters->Top_Row_Starting_Number = 41;
                  parameters->Redraw_Timing_Values_Flag = TRUE;
                  break;

               case KB_ESC :

                  new_process = BMI_MAIN_MENU_PROCESS;
                  exit_flag = TRUE;
                  break;

               case KB_F5 :

                  new_process = BMI_EDIT_MARK_PROCESS;
                  BMI_Activate_Process(parameters->Parameters_List, new_process);
                  break;

               case KB_F6 :

                  new_process = BMI_EDIT_CLEAR_PROCESS;
                  BMI_Activate_Process(parameters->Parameters_List, new_process);
                  break;

            }

            if (parameters->Parameters_List->Version == BMI_PLANT_VERSION && parameters->Field == 2 && parameters->Valve_Pack_Number.Integer_Value != 0) {

               parameters->Field += direction;

            }

            new_field_flag = (previous_field != parameters->Field);
            refresh_flag = (new_field_flag || *(Key) == KB_ESC || *(Key) == KB_F5 || *(Key) == KB_F6);
            input_field = (refresh_flag) ? previous_field : parameters->Field;
            *(Key) = (refresh_flag) ? 0 : *(Key);

            switch (input_field) {

               case 1 :

                  parameters->Current_Field_Descriptor = &(parameters->Part_Number);
                  break;

               case 2 :

                  parameters->Current_Field_Descriptor = &(parameters->Valve_Pack_Number);
                  break;

               case 3 :

                  parameters->Current_Field_Descriptor = &(parameters->Multiple_Part_Number);
                  break;

               case 4 :

                  parameters->Current_Field_Descriptor = &(parameters->Last_Bin_Sensor);
                  break;

               case 5 :

                  parameters->Current_Field_Descriptor = &(parameters->Total_Cycle_Time);
                  break;

               default :

                  parameters->Current_Field_Descriptor = ((input_field - BMI_TOTAL_UNIQUE_EDIT_FIELDS) % 2 == 0) ? &(parameters->Advance_Time[(input_field - BMI_TOTAL_UNIQUE_EDIT_FIELDS) / 2]) : &(parameters->Retract_Time[(input_field - BMI_TOTAL_UNIQUE_EDIT_FIELDS) / 2]);

            }

            if (refresh_flag) {

               BMI_Edit_Set_Refresh_Flag(parameters);
               BMI_Edit_Initialize_Current_Offset(parameters);
               parameters->Current_Field_Descriptor->Refresh_Flag = TRUE;
               parameters->Current_Field_Descriptor->Current_Offset = 0;

            }

            if (new_field_flag) {

               BMI_Edit_Set_First_Pass_Flag(parameters);
               parameters->Current_Field_Descriptor->First_Pass_Flag = TRUE;

            }

            BMI_Input(parameters->Current_Field_Descriptor, Key);

            if (exit_flag) {

               PORT_Destructor(&(parameters->Port));
               BMI_Halt_Process(parameters->Parameters_List, BMI_EDIT_EDIT_PROCESS);
               BMI_Activate_Process(parameters->Parameters_List, new_process);

            }

         }

      }

   }

   return (result);

}

/*

   Function    : BMI_Mark
   Description : Allows the user to mark an edit value.
   Inputs      : Nothing.
   Updates     : Process_Parameters =
                 Key                =
   Outputs     : Nothing.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 08/18/92 DWP Initial coding.
   Notes       :

*/

int BMI_Mark(void ** Process_Parameters, CARDINAL_16 * Key) {

   BMI_EDIT_MARK_PARAMETERS * parameters;
   int                        result;

   /*

      Validate the parameters.  Exit if either one is invalid.

   */

   if ((result = BMI_Validate_Parameters(Process_Parameters, Key)) == EZERO) {

      /*

	 Initialize the process parameters list for this process.

      */

      if (*(Process_Parameters) == NULL) {

         result = BMI_Allocate_Parameters_List(sizeof(*(parameters)), Process_Parameters);

      }
      else {

	 /*

	    Perform the main function of this process.

	 */

         parameters = *(Process_Parameters);
         BMI_Set_Help_Screen(parameters->Parameters_List, BMI_Help_Index_Key_List[BMI_HELP_MAREM]);
         parameters->Edit_Parameters->Current_Field_Descriptor->Marked_Flag = TRUE;
         parameters->Edit_Parameters->Current_Field_Descriptor->Refresh_Flag = TRUE;
         BMI_Halt_Process(parameters->Parameters_List, BMI_EDIT_MARK_PROCESS);
         BMI_Activate_Process(parameters->Parameters_List, BMI_EDIT_EDIT_PROCESS);

      }

   }

   return (result);

}

/*

   Function    : BMI_Clear
   Description : Allows the user to clear an edit value.
   Inputs      : Nothing.
   Updates     : Process_Parameters =
                 Key                =
   Outputs     : Nothing.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 08/18/92 DWP Initial coding.
   Notes       :

*/
int BMI_Clear(void ** Process_Parameters, CARDINAL_16 * Key) {

   BMI_EDIT_MARK_PARAMETERS * parameters;
   int                        result;

   /*

      Validate the parameters.  Exit if either one is invalid.

   */

   if ((result = BMI_Validate_Parameters(Process_Parameters, Key)) == EZERO) {

      /*

	 Initialize the process parameters list for this process.

      */

      if (*(Process_Parameters) == NULL) {

         result = BMI_Allocate_Parameters_List(sizeof(*(parameters)), Process_Parameters);

      }
      else {

	 /*

	    Perform the main function of this process.

	 */

         parameters = *(Process_Parameters);
         BMI_Set_Help_Screen(parameters->Parameters_List, BMI_Help_Index_Key_List[BMI_HELP_CLEEM]);
         parameters->Edit_Parameters->Current_Field_Descriptor->Marked_Flag = FALSE;
         parameters->Edit_Parameters->Current_Field_Descriptor->Refresh_Flag = TRUE;
         BMI_Halt_Process(parameters->Parameters_List, BMI_EDIT_CLEAR_PROCESS);
         BMI_Activate_Process(parameters->Parameters_List, BMI_EDIT_EDIT_PROCESS);

      }

   }

   return (result);

}

/*

   Function    : BMI_Reports_Data_Dump
   Description : Allows the user to print a data dump to the printer.
   Inputs      : Nothing.
   Updates     : Process_Parameters =
                 Key                =
   Outputs     : Nothing.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 08/18/92 DWP Initial coding.
   Notes       :

*/

int BMI_Reports_Data_Dump(void ** Process_Parameters, CARDINAL_16 * Key) {

   BMI_REPORTS_DATA_DUMP_PARAMETERS * parameters;
   FILE *                             report_file;
   time_t                             timer;
   struct tm *                        current_time;
   char                               str[81];
   int                                i, result;

   /*

      Validate the parameters.  Exit if either one is invalid.

   */

   if ((result = BMI_Validate_Parameters(Process_Parameters, Key)) == EZERO) {

      /*

	 Initialize the process parameters list for this process.

      */

      if (*(Process_Parameters) == NULL) {

         result = BMI_Allocate_Parameters_List(sizeof(*(parameters)), Process_Parameters);

      }
      else {

	 /*

	    Perform the main function of this process.

	 */

         parameters = *(Process_Parameters);
         BMI_Set_Help_Screen(parameters->Parameters_List, BMI_Help_Index_Key_List[BMI_HELP_DDPRM]);

         if (parameters->Process_In_Progress_Flag) {

            if ((int) parameters->Print_Report_Flag != -1) {

               if (!parameters->Print_Report_Flag) {

                  parameters->Stop_Process_Flag = TRUE;

               }
               else {

                  if (*(Key) == KB_ESC) {

                     parameters->Stop_Process_Flag = TRUE;
                     *(Key) = 0;

                  }
                  else {

                     if (PRINTER_Status(0) != (PRINTER_NOT_BUSY | PRINTER_SELECTED)) {

                        parameters->Stop_Process_Flag = TRUE;

                     }
                     else {

                        if ((report_file = fopen("PRN", "wt")) != NULL) {

                           fprintf(report_file, "\n%s\n\n", STRING_Center(sizeof(str) - 1, strcpy(str, "BASIC Module Interface - Edit Parameters Data Dump Report")));
                           timer = time(NULL);
                           current_time = localtime(&timer);
                           sprintf(str, "Report For Configuration File - %-8.8s", (parameters->Load_Parameters->File_Name[0] != '\0') ? parameters->Load_Parameters->File_Name : "********");
                           fprintf(report_file, "%s\n", STRING_Center(sizeof(str) - 1, str));
                           sprintf(str, "Report Date - %02u/%02u/%02u", current_time->tm_mon + 1, current_time->tm_mday, current_time->tm_year % 100);
                           fprintf(report_file, "%s\n\n\n\n", STRING_Center(sizeof(str) - 1, str));
                           fprintf(report_file, "Part Number              : %s\n", parameters->Edit_Parameters->Part_Number.Value);
                           fprintf(report_file, "Valve Pack Number        : %*u\n", parameters->Edit_Parameters->Valve_Pack_Number.Display_Length, parameters->Edit_Parameters->Valve_Pack_Number.Integer_Value);
                           fprintf(report_file, "Multiple Sequence Number : %*u\n", parameters->Edit_Parameters->Multiple_Part_Number.Display_Length, parameters->Edit_Parameters->Multiple_Part_Number.Integer_Value);
                           fprintf(report_file, "Last Bin Sensor          : %*u\n", parameters->Edit_Parameters->Last_Bin_Sensor.Display_Length, parameters->Edit_Parameters->Last_Bin_Sensor.Integer_Value);
                           fprintf(report_file, "Total Cycle Time         : %*u\n", parameters->Edit_Parameters->Total_Cycle_Time.Display_Length, parameters->Edit_Parameters->Total_Cycle_Time.Integer_Value);

                           sprintf(str, "Advance Time = Adv");
                           fprintf(report_file, "\n\n\n%s\n", STRING_Center(sizeof(str) - 1, str));
                           sprintf(str, "Retract Time = Ret");
                           fprintf(report_file, "%s", STRING_Center(sizeof(str) - 1, str));

                           for (i = 0; i < 80; i++) {

                              if (i % 20 == 0) {

                                 sprintf(str, "Group %d", (i / 20) + 1);
                                 fprintf(report_file, "\n\n%s\n\n", STRING_Center(sizeof(str) - 1, str));
                                 fprintf(report_file, "   Adv    Ret      Adv    Ret      Adv    Ret      Adv    Ret      Adv    Ret\n");
                                 fprintf(report_file, "  -----  -----    -----  -----    -----  -----    -----  -----    -----  -----\n");

                              }

			      fprintf(report_file, "   %*u   %*u  ", parameters->Edit_Parameters->Advance_Time[i].Display_Length, parameters->Edit_Parameters->Advance_Time[i].Integer_Value, parameters->Edit_Parameters->Retract_Time[i].Display_Length, parameters->Edit_Parameters->Retract_Time[i].Integer_Value);

                              if ((i + 1) % 5 == 0) {

                                 fputc('\n', report_file);

                              }

                           }

                           fputc(12, report_file);
                           parameters->Stop_Process_Flag = TRUE;

                        }

                     }

                  }

               }

               if (parameters->Stop_Process_Flag) {

                  fclose(report_file);
                  parameters->Print_Report_Flag = -1;
                  parameters->Stop_Process_Flag = FALSE;
                  parameters->Process_In_Progress_Flag = FALSE;
                  BMI_Halt_Process(parameters->Parameters_List, BMI_REPORTS_DATA_DUMP_PROCESS);
                  BMI_Activate_Process(parameters->Parameters_List, BMI_MAIN_MENU_PROCESS);

               }

            }

         }
         else {

            BMI_Activate_Process(parameters->Parameters_List, BMI_YES_NO_MENU_PROCESS);

            ((BMI_YES_NO_MENU_PARAMETERS *) parameters->Parameters_List->Process_Descriptor[BMI_YES_NO_MENU_PROCESS].Process_Parameters)->Starting_Row = 9;
            ((BMI_YES_NO_MENU_PARAMETERS *) parameters->Parameters_List->Process_Descriptor[BMI_YES_NO_MENU_PROCESS].Process_Parameters)->Starting_Column = 23;
            ((BMI_YES_NO_MENU_PARAMETERS *) parameters->Parameters_List->Process_Descriptor[BMI_YES_NO_MENU_PROCESS].Process_Parameters)->Display_Message = "Is The Printer On-Line And Ready?";
            ((BMI_YES_NO_MENU_PARAMETERS *) parameters->Parameters_List->Process_Descriptor[BMI_YES_NO_MENU_PROCESS].Process_Parameters)->Option = 1;
            ((BMI_YES_NO_MENU_PARAMETERS *) parameters->Parameters_List->Process_Descriptor[BMI_YES_NO_MENU_PROCESS].Process_Parameters)->Invoking_Process = BMI_REPORTS_DATA_DUMP_PROCESS;
            ((BMI_YES_NO_MENU_PARAMETERS *) parameters->Parameters_List->Process_Descriptor[BMI_YES_NO_MENU_PROCESS].Process_Parameters)->Yes_Selected_Flag = &(((BMI_REPORTS_DATA_DUMP_PARAMETERS *) parameters->Parameters_List->Process_Descriptor[BMI_REPORTS_DATA_DUMP_PROCESS].Process_Parameters)->Print_Report_Flag);

            parameters->Process_In_Progress_Flag = TRUE;
            result = EZERO;

         }

      }

   }

   return (result);

}

/*

   Function    : BMI_Reports_Available_Configurations
   Description : Allows the user to print a list of the available edit parameter files to the printer.
   Inputs      : Nothing.
   Updates     : Process_Parameters =
                 Key                =
   Outputs     : Nothing.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 08/18/92 DWP Initial coding.
   Notes       :

*/

int BMI_Reports_Available_Configurations(void ** Process_Parameters, CARDINAL_16 * Key) {

   BMI_REPORTS_AVAIL_CFG_PARAMETERS * parameters;
   FILE *                             report_file;
   BOOLEAN                            end_of_directory_indicator;
   time_t                             timer;
   struct tm *                        current_time;
   struct ffblk                       ffblk;
   struct ffblk *                     current_ffblk;
   char                               str[81], real_name[MAXPATH];
   int                                result;

   /*

      Validate the parameters.  Exit if either one is invalid.

   */

   if ((result = BMI_Validate_Parameters(Process_Parameters, Key)) == EZERO) {

      /*

	 Initialize the process parameters list for this process.

      */

      if (*(Process_Parameters) == NULL) {

         result = BMI_Allocate_Parameters_List(sizeof(*(parameters)), Process_Parameters);

      }
      else {

	 /*

	    Perform the main function of this process.

	 */

         parameters = *(Process_Parameters);
         BMI_Set_Help_Screen(parameters->Parameters_List, BMI_Help_Index_Key_List[BMI_HELP_ACGRM]);

         if (parameters->Process_In_Progress_Flag) {

            if ((int) parameters->Print_Report_Flag != -1) {

               if (!parameters->Print_Report_Flag) {

                  parameters->Stop_Process_Flag = TRUE;

               }
               else {

                  result = LIST_Constructor(sizeof(ffblk), &(parameters->File_List));
                  end_of_directory_indicator = findfirst("*.DAT", &(ffblk), 0);

                  while (result == LIST_NOERR && end_of_directory_indicator == 0) {

                     result = LIST_Insert(&ffblk, LIST_LAST, parameters->File_List);
                     end_of_directory_indicator = findnext(&(ffblk));

                  }

                  if (*(Key) == KB_ESC) {

                     parameters->Stop_Process_Flag = TRUE;
                     *(Key) = 0;

                  }
                  else {

                     if (PRINTER_Status(0) != (PRINTER_NOT_BUSY | PRINTER_SELECTED)) {

                        parameters->Stop_Process_Flag = TRUE;

                     }
                     else {

                        if ((report_file = fopen("PRN", "wt")) != NULL) {

                           fprintf(report_file, "\n%s\n\n", STRING_Center(sizeof(str) - 1, strcpy(str, "BASIC Module Interface - Available Configurations Report")));
                           sprintf(str, "Report For Configuration Files in %s", (DOS_Qualify_File_Specification(real_name, ".") != EZERO) ? "" : real_name);
                           fprintf(report_file, "%s\n", STRING_Center(sizeof(str) - 1, str));
                           timer = time(NULL);
                           current_time = localtime(&timer);
                           sprintf(str, "Report Date - %02u/%02u/%02u", current_time->tm_mon + 1, current_time->tm_mday, current_time->tm_year % 100);
                           fprintf(report_file, "%s\n\n\n\n", STRING_Center(sizeof(str) - 1, str));
                           sprintf(str, "File Name%10sCreation Date", "");
                           fprintf(report_file, "%s\n\n\n", STRING_Center(sizeof(str) - 1, str));

                           result = LIST_Retrieve(parameters->File_List, LIST_FIRST, (void **) &(current_ffblk));

                           while (result == LIST_NOERR) {

                              if (STRING_CharPos(current_ffblk->ff_name, '.') > 0) {

                                 current_ffblk->ff_name[STRING_CharPos(current_ffblk->ff_name, '.') - 1] = '\0';

                              }

                              sprintf(str, "%-9.9s%12s%02u/%02u/%02u", current_ffblk->ff_name, "", current_time->tm_mon + 1, current_time->tm_mday, current_time->tm_year % 100);
                              fprintf(report_file, "%s\n", STRING_Center(sizeof(str) - 1, str));
                              result = LIST_Retrieve(parameters->File_List, LIST_NEXT, (void **) &(current_ffblk));

                           }

                           fputc(12, report_file);
                           parameters->Stop_Process_Flag = TRUE;
                           result = EZERO;

                        }

                     }

                  }

               }

               if (parameters->Stop_Process_Flag) {

                  fclose(report_file);
                  parameters->Print_Report_Flag = -1;
                  parameters->Stop_Process_Flag = FALSE;
                  parameters->Process_In_Progress_Flag = FALSE;
                  BMI_Halt_Process(parameters->Parameters_List, BMI_REPORTS_AVAIL_CFG_PROCESS);
                  BMI_Activate_Process(parameters->Parameters_List, BMI_MAIN_MENU_PROCESS);

               }

            }

         }
         else {

            BMI_Activate_Process(parameters->Parameters_List, BMI_YES_NO_MENU_PROCESS);

            ((BMI_YES_NO_MENU_PARAMETERS *) parameters->Parameters_List->Process_Descriptor[BMI_YES_NO_MENU_PROCESS].Process_Parameters)->Starting_Row = 9;
            ((BMI_YES_NO_MENU_PARAMETERS *) parameters->Parameters_List->Process_Descriptor[BMI_YES_NO_MENU_PROCESS].Process_Parameters)->Starting_Column = 23;
            ((BMI_YES_NO_MENU_PARAMETERS *) parameters->Parameters_List->Process_Descriptor[BMI_YES_NO_MENU_PROCESS].Process_Parameters)->Display_Message = "Is The Printer On-Line And Ready?";
            ((BMI_YES_NO_MENU_PARAMETERS *) parameters->Parameters_List->Process_Descriptor[BMI_YES_NO_MENU_PROCESS].Process_Parameters)->Option = 1;
            ((BMI_YES_NO_MENU_PARAMETERS *) parameters->Parameters_List->Process_Descriptor[BMI_YES_NO_MENU_PROCESS].Process_Parameters)->Invoking_Process = BMI_REPORTS_AVAIL_CFG_PROCESS;
            ((BMI_YES_NO_MENU_PARAMETERS *) parameters->Parameters_List->Process_Descriptor[BMI_YES_NO_MENU_PROCESS].Process_Parameters)->Yes_Selected_Flag = &(((BMI_REPORTS_AVAIL_CFG_PARAMETERS *) parameters->Parameters_List->Process_Descriptor[BMI_REPORTS_AVAIL_CFG_PROCESS].Process_Parameters)->Print_Report_Flag);

            parameters->Process_In_Progress_Flag = TRUE;
            result = EZERO;

         }

      }

   }

   return (result);

}

/*

   Function    : BMI_Initialize_Comm_Port
   Description : Initializes the communications port for use.
   Inputs      : Port_No = The communications port to be initialized.
   Updates     : Nothing.
   Outputs     : Nothing.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 08/18/92 DWP Initial coding.
   Notes       :

*/

int BMI_Initialize_Comm_Port(int Port_No, int IQ_Size, int OQ_Size, int Int_Level, int Port_Ads, char * Pbuffer) {

   int result;

      result = open_a1(Port_No, IQ_Size, OQ_Size, Int_Level, Port_Ads, Pbuffer);

      result |= setop_a1(Port_No, 1, 7);
      result |= setop_a1(Port_No, 2, 0);
      result |= setop_a1(Port_No, 3, 3);
      result |= setop_a1(Port_No, 4, 0);
      result |= setop_a1(Port_No, 5, 1);
      result |= setop_a1(Port_No, 6, 1);
      result |= setop_a1(Port_No, 7, 0);
      result |= setop_a1(Port_No, 8, 0);
      result |= setop_a1(Port_No, 9, 0);
      result |= setop_a1(Port_No, 10, 250);

   return (result);

}

/*

   Procedure   : BMI_Send_Calculate_Valve_Packs
   Description :
   Inputs      :
   Updates     :
   Outputs     :
   Returns     : Nothing.
   Modified    : 08/18/92 DWP Initial coding.
   Notes       :

*/

void BMI_Send_Calculate_Valve_Packs(BMI_COMMUNICATIONS_SEND_PARAMETERS * Process_Parameters) {

   int i;

   Process_Parameters->Valve_Packs = 1;

   for (i = 0; i < 80; i++) {

      if (i >= 20 && (Process_Parameters->Edit_Parameters->Advance_Time[i].Integer_Value != 0 || Process_Parameters->Edit_Parameters->Retract_Time[i].Integer_Value != 0)) {

         Process_Parameters->Valve_Packs = 2;

      }

      if (i >= 40 && (Process_Parameters->Edit_Parameters->Advance_Time[i].Integer_Value != 0 || Process_Parameters->Edit_Parameters->Retract_Time[i].Integer_Value != 0)) {

         Process_Parameters->Valve_Packs = 3;

      }

      if (i >= 60 && (Process_Parameters->Edit_Parameters->Advance_Time[i].Integer_Value != 0 || Process_Parameters->Edit_Parameters->Retract_Time[i].Integer_Value != 0)) {

         Process_Parameters->Valve_Packs = 4;

      }

   }

}

/*

   Procedure   : BMI_Send_Construct_Send_String
   Description :
   Inputs      :
   Updates     :
   Outputs     :
   Returns     : Nothing.
   Modified    : 08/18/92 DWP Initial coding.
   Notes       :

*/

void BMI_Send_Construct_Send_String(BMI_COMMUNICATIONS_SEND_PARAMETERS * Process_Parameters) {

   int i;

   Process_Parameters->Send_String[0] = '\0';

   switch (Process_Parameters->Parameter_Number) {

      case 0 :

         strcpy(Process_Parameters->Send_String, "ST");
         break;

      case 1 :

         sprintf(Process_Parameters->Send_String, "UN%c%d", Process_Parameters->Unit_Number.Value[0], Process_Parameters->Valve_Packs);
         break;

      case 2 :

         if (Process_Parameters->Edit_Parameters->Valve_Pack_Number.Integer_Value < Process_Parameters->Edit_Parameters->Valve_Pack_Number.Minimum_Value || Process_Parameters->Edit_Parameters->Valve_Pack_Number.Integer_Value > Process_Parameters->Edit_Parameters->Valve_Pack_Number.Maximum_Editable_Value) {

            Process_Parameters->Edit_Parameters->Valve_Pack_Number.Integer_Value = Process_Parameters->Edit_Parameters->Valve_Pack_Number.Minimum_Value;
            sprintf(Process_Parameters->Edit_Parameters->Valve_Pack_Number.Value, "%*d", Process_Parameters->Edit_Parameters->Valve_Pack_Number.Display_Length, Process_Parameters->Edit_Parameters->Valve_Pack_Number.Integer_Value);

         }

         sprintf(Process_Parameters->Send_String, "CD%0*u", Process_Parameters->Edit_Parameters->Valve_Pack_Number.Display_Length, Process_Parameters->Edit_Parameters->Valve_Pack_Number.Integer_Value);
         break;

      case 3 :

         sprintf(Process_Parameters->Send_String, "PN%-*.*s", Process_Parameters->Edit_Parameters->Part_Number.Display_Length, Process_Parameters->Edit_Parameters->Part_Number.Display_Length, Process_Parameters->Edit_Parameters->Part_Number.Value);
         break;

      case 4 :

         if (Process_Parameters->Edit_Parameters->Multiple_Part_Number.Integer_Value < Process_Parameters->Edit_Parameters->Multiple_Part_Number.Minimum_Value || Process_Parameters->Edit_Parameters->Multiple_Part_Number.Integer_Value > Process_Parameters->Edit_Parameters->Multiple_Part_Number.Maximum_Editable_Value) {

            Process_Parameters->Edit_Parameters->Multiple_Part_Number.Integer_Value = Process_Parameters->Edit_Parameters->Multiple_Part_Number.Minimum_Value;
            sprintf(Process_Parameters->Edit_Parameters->Multiple_Part_Number.Value, "%*d", Process_Parameters->Edit_Parameters->Multiple_Part_Number.Display_Length, Process_Parameters->Edit_Parameters->Multiple_Part_Number.Integer_Value);

         }

         sprintf(Process_Parameters->Send_String, "MP%0*u", Process_Parameters->Edit_Parameters->Multiple_Part_Number.Display_Length, Process_Parameters->Edit_Parameters->Multiple_Part_Number.Integer_Value - 1);
         break;

      case 5 :

         if (Process_Parameters->Edit_Parameters->Last_Bin_Sensor.Integer_Value < Process_Parameters->Edit_Parameters->Last_Bin_Sensor.Minimum_Value || Process_Parameters->Edit_Parameters->Last_Bin_Sensor.Integer_Value > Process_Parameters->Edit_Parameters->Last_Bin_Sensor.Maximum_Editable_Value) {

            Process_Parameters->Edit_Parameters->Last_Bin_Sensor.Integer_Value = Process_Parameters->Edit_Parameters->Last_Bin_Sensor.Minimum_Value;
            sprintf(Process_Parameters->Edit_Parameters->Last_Bin_Sensor.Value, "%*d", Process_Parameters->Edit_Parameters->Last_Bin_Sensor.Display_Length, Process_Parameters->Edit_Parameters->Last_Bin_Sensor.Integer_Value);

         }

         sprintf(Process_Parameters->Send_String, "LB%0*u", Process_Parameters->Edit_Parameters->Last_Bin_Sensor.Display_Length, Process_Parameters->Edit_Parameters->Last_Bin_Sensor.Integer_Value);
         break;

      case 6 :

         if (Process_Parameters->Edit_Parameters->Total_Cycle_Time.Integer_Value < Process_Parameters->Edit_Parameters->Total_Cycle_Time.Minimum_Value || Process_Parameters->Edit_Parameters->Total_Cycle_Time.Integer_Value > Process_Parameters->Edit_Parameters->Total_Cycle_Time.Maximum_Editable_Value) {

            Process_Parameters->Edit_Parameters->Total_Cycle_Time.Integer_Value = Process_Parameters->Edit_Parameters->Total_Cycle_Time.Minimum_Value;
            sprintf(Process_Parameters->Edit_Parameters->Total_Cycle_Time.Value, "%*d", Process_Parameters->Edit_Parameters->Total_Cycle_Time.Display_Length, Process_Parameters->Edit_Parameters->Total_Cycle_Time.Integer_Value);

         }

         sprintf(Process_Parameters->Send_String, "TC%0*u", Process_Parameters->Edit_Parameters->Total_Cycle_Time.Display_Length, Process_Parameters->Edit_Parameters->Total_Cycle_Time.Integer_Value);
         break;

      default :

         switch (Process_Parameters->Parameter_Number) {

            case 167 :

               strcpy(Process_Parameters->Send_String, (toupper(Process_Parameters->Save_Timing_Values.Value[0]) == 'Y') ? "SA" : "");
               break;

            case 168 :

               strcpy(Process_Parameters->Send_String, "DN");
               break;

            case 169 :

               Process_Parameters->Exit_Flag = TRUE;
               break;

            default :

               i = (Process_Parameters->Parameter_Number - BMI_TOTAL_UNIQUE_EDIT_FIELDS - 1) / 2;

               if (i < Process_Parameters->Valve_Packs * 20) {

                  if (Process_Parameters->Parameter_Number % 2 != 0) {

                     if (!Process_Parameters->Edit_Parameters->Advance_Time[i].Marked_Flag) {

                        if (Process_Parameters->Edit_Parameters->Advance_Time[i].Integer_Value < Process_Parameters->Edit_Parameters->Advance_Time[i].Minimum_Value || Process_Parameters->Edit_Parameters->Advance_Time[i].Integer_Value > Process_Parameters->Edit_Parameters->Advance_Time[i].Maximum_Editable_Value) {

                           Process_Parameters->Edit_Parameters->Advance_Time[i].Integer_Value = Process_Parameters->Edit_Parameters->Advance_Time[i].Minimum_Value;
                           sprintf(Process_Parameters->Edit_Parameters->Advance_Time[i].Value, "%*d", Process_Parameters->Edit_Parameters->Advance_Time[i].Display_Length, Process_Parameters->Edit_Parameters->Advance_Time[i].Integer_Value);

                        }

                        sprintf(Process_Parameters->Send_String, "VA%02u%0*u", i + 1, Process_Parameters->Edit_Parameters->Advance_Time[i].Display_Length, Process_Parameters->Edit_Parameters->Advance_Time[i].Integer_Value);

                     }

                  }
                  else {

                     if (!Process_Parameters->Edit_Parameters->Retract_Time[i].Marked_Flag) {

                        if (Process_Parameters->Edit_Parameters->Retract_Time[i].Integer_Value < Process_Parameters->Edit_Parameters->Retract_Time[i].Minimum_Value || Process_Parameters->Edit_Parameters->Retract_Time[i].Integer_Value > Process_Parameters->Edit_Parameters->Retract_Time[i].Maximum_Editable_Value) {

                           Process_Parameters->Edit_Parameters->Retract_Time[i].Integer_Value = Process_Parameters->Edit_Parameters->Retract_Time[i].Minimum_Value;
                           sprintf(Process_Parameters->Edit_Parameters->Retract_Time[i].Value, "%*d", Process_Parameters->Edit_Parameters->Retract_Time[i].Display_Length, Process_Parameters->Edit_Parameters->Retract_Time[i].Integer_Value);

                        }

                        sprintf(Process_Parameters->Send_String, "VR%02u%0*u", i + 1, Process_Parameters->Edit_Parameters->Retract_Time[i].Display_Length, Process_Parameters->Edit_Parameters->Retract_Time[i].Integer_Value);

                     }

                  }

               }

         }

   }

   if (strlen(Process_Parameters->Send_String) > 0 ) {

      strcat(Process_Parameters->Send_String, "\r\n\0");

   }

}

/*

   Procedure   : BMI_Send_Print_Error_Code
   Description :
   Inputs      : Text
                 Parameter_Number
                 Error_Code
                 Error_Message
   Updates     : Nothing.
   Outputs     : Nothing.
   Returns     : Nothing.
   Modified    : 08/18/92 DWP Initial Coding.
   Notes       :

*/

void BMI_Send_Print_Error_Code(TEXT Text, int Parameter_Number, int Error_Code, char * Error_Message) {

   char str[81];

   TEXT_Set_Cursor_Position(6, 16, Text);
   sprintf(str, "%02d-%02d", Parameter_Number, Error_Code);
   TEXT_Print_String(str, Text);

   if (Error_Message[0] != '\0') {

      sprintf(str, "-%.44s", Error_Message);
      TEXT_Print_String(str, Text);

   }

}

/*

   Function    : BMI_Send
   Description : Allows the user to send the edit parameters to the basic module.
   Inputs      : Nothing.
   Updates     : Process_Parameters =
                 Key                =
   Outputs     : Nothing.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 08/18/92 DWP Initial coding.
   Notes       :

*/

int BMI_Send(void ** Process_Parameters, CARDINAL_16 * Key) {

   BMI_COMMUNICATIONS_SEND_PARAMETERS * parameters;
   BOOLEAN                              valid_value_flag;
   char                                 str[256], output_string[256];
   int                                  poq_size, pwritten, result;

   /*

      Validate the parameters.  Exit if either one is invalid.

   */

   if ((result = BMI_Validate_Parameters(Process_Parameters, Key)) == EZERO) {

      /*

	 Initialize the process parameters list for this process.

      */

      if (*(Process_Parameters) == NULL) {

         result = BMI_Allocate_Parameters_List(sizeof(*(parameters)), Process_Parameters);

      }
      else {

	 /*

	    Perform the main function of this process.

	 */

         parameters = *(Process_Parameters);
         BMI_Set_Help_Screen(parameters->Parameters_List, BMI_Help_Index_Key_List[BMI_HELP_SNDCM]);

         if (parameters->Port == NULL) {

            if ((result = PORT_Constructor(parameters->Starting_Row, parameters->Starting_Column, parameters->Height, parameters->Width, PORT_SINGLE_LINE_BORDER, parameters->Colors.Primary_Color, parameters->Colors.Primary_Color, &(parameters->Port))) == PORT_NOERR) {

               TEXT_Set_Text_Color(parameters->Colors.Primary_Color, parameters->Text);
               TEXT_Set_Cursor_Position(3, 21, parameters->Text);
               TEXT_Print_String("Unit Number (1-4)        : ", parameters->Text);
               TEXT_Set_Cursor_Position(5, 21, parameters->Text);
               TEXT_Print_String("Save Timing Values (Y/N) : ", parameters->Text);
               parameters->Unit_Number.Refresh_Flag = TRUE;
               BMI_Input(&(parameters->Unit_Number), Key);
               parameters->Save_Timing_Values.Refresh_Flag = TRUE;
               BMI_Input(&(parameters->Save_Timing_Values), Key);
               parameters->Send_Raw_Data_File = fopen("BMI.SND", "wt");
               BMI_Send_Calculate_Valve_Packs(parameters);

            }

         }
         else {

            PORT_Activate(parameters->Port);

            if (parameters->Get_Parameters_Flag) {

               switch (parameters->Field) {

                  case 1 :

                     parameters->Save_Timing_Values.Refresh_Flag = TRUE;
                     parameters->Save_Timing_Values.Current_Offset = 0;
                     BMI_Input(&(parameters->Save_Timing_Values), Key);

                     break;

                  case 2 :

                     parameters->Unit_Number.Refresh_Flag = TRUE;
                     parameters->Unit_Number.Current_Offset = 0;
                     BMI_Input(&(parameters->Unit_Number), Key);

                     break;

               }

               switch (*(Key)) {

                  case KB_ENTER :
                  case KB_GRAY_ENTER :
                  case KB_TAB :

                     parameters->Field++;

                     if (parameters->Field > 2) {

                        STRING_ATrim(parameters->Unit_Number.Value);
                        STRING_ATrim(parameters->Save_Timing_Values.Value);

                        if (parameters->Unit_Number.Value[0] == '\0' || parameters->Save_Timing_Values.Value[0] == '\0') {

                           parameters->Field = 1;

                        }
                        else {

                           TEXT_Set_Text_Color(parameters->Colors.Primary_Color, parameters->Text);
                           clrscr();
                           TEXT_Set_Cursor_Position(2, 29, parameters->Text);
                           TEXT_Print_String("Send Status", parameters->Text);
                           TEXT_Set_Cursor_Position(4, 2, parameters->Text);
                           TEXT_Print_String("Send Buffer : ", parameters->Text);
                           TEXT_Set_Cursor_Position(6, 2, parameters->Text);
                           TEXT_Print_String("Status      : ", parameters->Text);
                           parameters->Get_Parameters_Flag = FALSE;

                        }

                     }

                     break;

                  case KB_SHIFT_TAB :

                     parameters->Field = (parameters->Field == 1) ? 2 : 1;
                     break;

                  case KB_ESC :

                     parameters->Exit_Flag = TRUE;
                     *(Key) = 0;
                     break;

               }

               switch (parameters->Field) {

                  case 1 :

                     BMI_Input(&(parameters->Unit_Number), Key);
                     valid_value_flag = TRUE;

                     switch (parameters->Unit_Number.Value[0]) {

                        case '1' :

                           break;

                        case '2' :
                        case '4' :

                           if (parameters->Valve_Packs != 1) {

                              valid_value_flag = FALSE;

                           }

                           break;

                        case '3' :

                           if (parameters->Valve_Packs > 2) {

                              valid_value_flag = FALSE;

                           }

                           break;

                        default :

                           valid_value_flag = FALSE;

                     }

                     if (!valid_value_flag) {

                        parameters->Unit_Number.Value[0] = '\0';

                     }

                     break;

                  case 2 :

                     BMI_Input(&(parameters->Save_Timing_Values), Key);

                     if (strchr("YyNn", parameters->Save_Timing_Values.Value[0]) == NULL) {

                        parameters->Save_Timing_Values.Value[0] = '\0';

                     }

                     break;

               }

            }
            else {

               if (parameters->First_Pass_Flag) {

                  result = BMI_Initialize_Comm_Port(parameters->Port_No, parameters->IQ_Size, parameters->OQ_Size, parameters->Int_Level, parameters->Port_Ads, parameters->Pbuffer);
                  parameters->First_Pass_Flag = FALSE;
                  BMI_Send_Construct_Send_String(parameters);
                  wrtch_a1(0x13, parameters->Port_No);
                  wait_a1(18);

               }

               if (*(Key) == KB_ESC) {

                  *(Key) = 0;

                  if (parameters->Exit_Flag) {

                     parameters->Abort_Flag = TRUE;

                  }
                  else {

                     parameters->Exit_Flag = TRUE;

                  }

               }
               else {

                  PORT_Activate(parameters->Port);
                  TEXT_Set_Text_Color(parameters->Colors.Primary_Color, parameters->Text);
                  result = 0;

                  oqsiz_a1(parameters->Port_No, &(poq_size));

                  if (poq_size == 0) {

                     if (wrtbk_a1(parameters->Port_No, sizeof(parameters->Send_String), '\0', parameters->Send_String, &(pwritten)) == 0) {

                        parameters->Parameter_Number++;
                        fprintf(parameters->Send_Raw_Data_File, parameters->Send_String);

                     }

                  }

                  TEXT_Set_Text_Color(parameters->Colors.Primary_Color, parameters->Text);
                  TEXT_Set_Cursor_Position(4, 16, parameters->Text);
                  strcpy(str, parameters->Send_String);
                  sprintf(output_string, "[%-50.50s]", STRING_Trim(STRING_TRIM_SPACE, str));
                  TEXT_Print_String(output_string, parameters->Text);
                  BMI_Send_Print_Error_Code(parameters->Text, parameters->Parameter_Number, result, "");
                  BMI_Send_Construct_Send_String(parameters);


               }

            }

         }

         if (parameters->Exit_Flag) {

            oqsiz_a1(parameters->Port_No, &(poq_size));

            if (poq_size == 0 || parameters->Abort_Flag) {

               parameters->Exit_Flag = FALSE;
               parameters->Abort_Flag = FALSE;
               parameters->First_Pass_Flag = TRUE;
               parameters->Parameter_Number = 0;
               parameters->Get_Parameters_Flag = TRUE;
               parameters->Field = 1;
               result = close_a1(parameters->Port_No);
               BMI_Halt_Process(parameters->Parameters_List, BMI_COMMUNICATIONS_SEND_PROCESS);
               BMI_Activate_Process(parameters->Parameters_List, BMI_MAIN_MENU_PROCESS);
               result = PORT_Destructor(&(parameters->Port));
               fclose(parameters->Send_Raw_Data_File);

            }

         }

      }

   }

   if (result != 0) {

      result = 0;

   }

   return (result);

}

/*

   Function    : BMI_Receive_Decode_String
   Description :
   Inputs      : Process_Parameters
   Updates     : Nothing.
   Outputs     : Nothing.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 08/18/92 DWP Initial coding.
   Notes       :

*/

int BMI_Receive_Decode_String(BMI_COMMUNICATIONS_RECEIVE_PARAMETERS * Process_Parameters) {

   char str[256];
   int  i, result;

   switch (Process_Parameters->Receive_String[0] * 2 + Process_Parameters->Receive_String[1]) {

      /*

	 Part Number, PN.

      */

      case 238 :

         strncpy(Process_Parameters->Edit_Parameters->Part_Number.Value, Process_Parameters->Receive_String + 2, Process_Parameters->Edit_Parameters->Part_Number.Display_Length);
         break;

      /*

	 Valve Pack Number, CD.

      */

      case 202 :

         strcpy(str, Process_Parameters->Receive_String + 2);
         Process_Parameters->Edit_Parameters->Valve_Pack_Number.Integer_Value = atoi(str);
         sprintf(Process_Parameters->Edit_Parameters->Valve_Pack_Number.Value, "%*u", Process_Parameters->Edit_Parameters->Valve_Pack_Number.Display_Length, Process_Parameters->Edit_Parameters->Valve_Pack_Number.Integer_Value);
         break;

      /*

	 Multiple Sequence Number, MP.

      */

      case 234 :

         strcpy(str, Process_Parameters->Receive_String + 2);
         Process_Parameters->Edit_Parameters->Multiple_Part_Number.Integer_Value = atoi(str) + 1;
         sprintf(Process_Parameters->Edit_Parameters->Multiple_Part_Number.Value, "%*u", Process_Parameters->Edit_Parameters->Multiple_Part_Number.Display_Length, Process_Parameters->Edit_Parameters->Multiple_Part_Number.Integer_Value);
         break;

      /*

	 Last Bin Sensor, LB.

      */

      case 218 :

         strcpy(str, Process_Parameters->Receive_String + 2);
         Process_Parameters->Edit_Parameters->Last_Bin_Sensor.Integer_Value = atoi(str);
         sprintf(Process_Parameters->Edit_Parameters->Last_Bin_Sensor.Value, "%*u", Process_Parameters->Edit_Parameters->Last_Bin_Sensor.Display_Length, Process_Parameters->Edit_Parameters->Last_Bin_Sensor.Integer_Value);
         break;

      /*

	 Total Cycle Time, TC.

      */

      case 235 :

         strcpy(str, Process_Parameters->Receive_String + 2);
         Process_Parameters->Edit_Parameters->Total_Cycle_Time.Integer_Value = atoi(str);
         sprintf(Process_Parameters->Edit_Parameters->Total_Cycle_Time.Value, "%*u", Process_Parameters->Edit_Parameters->Total_Cycle_Time.Display_Length, Process_Parameters->Edit_Parameters->Total_Cycle_Time.Integer_Value);
         break;

      /*

	 Valve Advance, VA.

      */

      case 237 :

         sprintf(str, "%.2s", Process_Parameters->Receive_String + 2);
         i = atoi(str) - 1;

         if (i >= 0 && i < 80) {

            strcpy(str, Process_Parameters->Receive_String + 4);
            Process_Parameters->Edit_Parameters->Advance_Time[i].Integer_Value = atoi(str);
            sprintf(Process_Parameters->Edit_Parameters->Advance_Time[i].Value, "%*u", Process_Parameters->Edit_Parameters->Advance_Time[i].Display_Length, Process_Parameters->Edit_Parameters->Advance_Time[i].Integer_Value);

         }

         break;

      /*

	 Valve Retract, VR.

      */

      case 254 :

         sprintf(str, "%.2s", Process_Parameters->Receive_String + 2);
         i = atoi(str) - 1;

         if (i >= 0 && i < 80) {

            strcpy(str, Process_Parameters->Receive_String + 4);
            Process_Parameters->Edit_Parameters->Retract_Time[i].Integer_Value = atoi(str);
            sprintf(Process_Parameters->Edit_Parameters->Retract_Time[i].Value, "%*u", Process_Parameters->Edit_Parameters->Retract_Time[i].Display_Length, Process_Parameters->Edit_Parameters->Retract_Time[i].Integer_Value);

         }

         break;

      /*

	 Error Message, ER.

      */

      case 220 :

         sprintf(Process_Parameters->Error_Message, "%.*s", sizeof(Process_Parameters->Error_Message) - 1, Process_Parameters->Receive_String + 2);
         break;

      /*

	 Done Transmitting, DN.

      */

      case 214 :

         Process_Parameters->Exit_Flag = TRUE;
         break;

      default :

         result = 1;

   }

   return (result);

}

/*

   Function    : BMI_Receive
   Description : Allows the user to receive edit parameters from the basic module.
   Inputs      : Nothing.
   Updates     : Process_Parameters =
                 Key                =
   Outputs     : Nothing.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 08/18/92 DWP Initial coding.
   Notes       :

*/

int BMI_Receive(void ** Process_Parameters, CARDINAL_16 * Key) {

   BMI_COMMUNICATIONS_RECEIVE_PARAMETERS * parameters;
   char                                    ch, str[256], output_string[256];
   unsigned int                            pstatus;
   int                                     piq_size, pwritten, result;

   /*

      Validate the parameters.  Exit if either one is invalid.

   */

   if ((result = BMI_Validate_Parameters(Process_Parameters, Key)) == EZERO) {

      /*

	 Initialize the process parameters list for this process.

      */

      if (*(Process_Parameters) == NULL) {

         result = BMI_Allocate_Parameters_List(sizeof(*(parameters)), Process_Parameters);

      }
      else {

	 /*

	    Perform the main function of this process.

	 */

         parameters = *(Process_Parameters);
         BMI_Set_Help_Screen(parameters->Parameters_List, BMI_Help_Index_Key_List[BMI_HELP_RECCM]);

         if (parameters->Port == NULL) {

            if ((result = PORT_Constructor(parameters->Starting_Row, parameters->Starting_Column, parameters->Height, parameters->Width, PORT_SINGLE_LINE_BORDER, parameters->Colors.Primary_Color, parameters->Colors.Primary_Color, &(parameters->Port))) == PORT_NOERR) {

               TEXT_Set_Text_Color(parameters->Colors.Primary_Color, parameters->Text);
               TEXT_Set_Cursor_Position(2, 23, parameters->Text);
               TEXT_Print_String("Receive Status", parameters->Text);
               TEXT_Set_Cursor_Position(4, 2, parameters->Text);
               TEXT_Print_String("Recv Buffer : ", parameters->Text);
               TEXT_Set_Cursor_Position(6, 2, parameters->Text);
               TEXT_Print_String("Status      : ", parameters->Text);

            }

         }
         else {

            if (parameters->First_Pass_Flag) {

               result = BMI_Initialize_Comm_Port(parameters->Port_No, parameters->IQ_Size, parameters->OQ_Size, parameters->Int_Level, parameters->Port_Ads, parameters->Pbuffer);
               parameters->First_Pass_Flag = FALSE;
               setmem(parameters->Receive_String, sizeof(parameters->Receive_String), 0);
               setmem(parameters->Error_Message, sizeof(parameters->Error_Message), 0);
               parameters->Receive_String_Offset = 0;
               parameters->Parameter_Number = 0;
               wait_a1(18);
               strcpy(str, "\r\nST\r\n");
               wrtbk_a1(parameters->Port_No, sizeof(str), '\0', str, &(pwritten));
               sprintf(str, "RQ%0*u%*u\r\n", parameters->Edit_Parameters->Valve_Pack_Number.Display_Length, parameters->Edit_Parameters->Valve_Pack_Number.Integer_Value, parameters->Edit_Parameters->Multiple_Part_Number.Display_Length, parameters->Edit_Parameters->Multiple_Part_Number.Integer_Value);
               wrtbk_a1(parameters->Port_No, sizeof(str), '\0', str, &(pwritten));
               strcpy(str, "DN\r\n");
               wrtbk_a1(parameters->Port_No, sizeof(str), '\0', str, &(pwritten));
               parameters->Lines_Received = 0;
               parameters->Receive_Raw_Data_File = fopen("BMI.REC", "wt");

            }
            else {

               if (*(Key) == KB_ESC) {

                  *(Key) = 0;
                  parameters->Exit_Flag = TRUE;

               }
               else {

                  PORT_Activate(parameters->Port);
                  TEXT_Set_Text_Color(parameters->Colors.Primary_Color, parameters->Text);
                  result = qsize_a1(parameters->Port_No, &(piq_size), &(pstatus));

                  if (piq_size > 0) {

                     if ((result = rdch_a1(parameters->Port_No, &(ch), &(piq_size), &(pstatus))) == 0) {

                        fputc(ch, parameters->Receive_Raw_Data_File);

                        if (ch != '\r' && ch != '\n' && parameters->Receive_String_Offset < sizeof(parameters->Receive_String)) {

                           parameters->Receive_String[parameters->Receive_String_Offset++] = ch;

                        }
                        else {

                           if (ch == '\n') {

                              TEXT_Set_Text_Color(parameters->Colors.Primary_Color, parameters->Text);
                              TEXT_Set_Cursor_Position(4, 16, parameters->Text);
                              parameters->Receive_String[parameters->Receive_String_Offset] = '\0';
                              parameters->Receive_String_Offset = 0;
                              strcpy(str, parameters->Receive_String);
                              sprintf(output_string, "[%-50.50s]", STRING_Trim(STRING_TRIM_SPACE, str));
                              TEXT_Print_String(output_string, parameters->Text);

                              if (++parameters->Lines_Received > 6) {

                                 result = BMI_Receive_Decode_String(parameters);

                              }

                           }

                        }

                     }

                  }

                  BMI_Send_Print_Error_Code(parameters->Text, parameters->Parameter_Number, result, parameters->Error_Message);

                  if (result != 0) {

                     result = 0;

                  }

               }

               if (parameters->Exit_Flag) {

                  fclose(parameters->Receive_Raw_Data_File);
                  parameters->Exit_Flag = FALSE;
                  parameters->First_Pass_Flag = TRUE;
                  parameters->Parameter_Number = 0;
                  result = close_a1(parameters->Port_No);
                  BMI_Halt_Process(parameters->Parameters_List, BMI_COMMUNICATIONS_RECEIVE_PROCESS);
                  BMI_Activate_Process(parameters->Parameters_List, BMI_MAIN_MENU_PROCESS);
                  PORT_Destructor(&(parameters->Port));

               }

            }

         }

      }

   }

   if (result != 0) {

      result = 0;

   }

   return (result);

}

/*

   Function    : BMI_Terminal
   Description : Allows the user to interact with the basic module.
   Inputs      : Nothing.
   Updates     : Process_Parameters =
                 Key                =
   Outputs     : Nothing.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 08/18/92 DWP Initial coding.
   Notes       :

*/

int BMI_Terminal(void ** Process_Parameters, CARDINAL_16 * Key) {

   BMI_COMMUNICATIONS_TERMINAL_PARAMETERS * parameters;
   CARDINAL_16                              x, y;
   BOOLEAN                                  exit_flag = FALSE;
   static char                              str[81];
   char                                     ch, error_message[81];
   unsigned int                             pstatus;
   int                                      piq_size;
   int                                      result;

   /*

      Validate the parameters.  Exit if either one is invalid.

   */

   if ((result = BMI_Validate_Parameters(Process_Parameters, Key)) == EZERO) {

      /*

	 Initialize the process parameters list for this process.

      */

      if (*(Process_Parameters) == NULL) {

         result = BMI_Allocate_Parameters_List(sizeof(*(parameters)), Process_Parameters);

      }
      else {

	 /*

	    Perform the main function of this process.

	 */

         parameters = *(Process_Parameters);
         BMI_Set_Help_Screen(parameters->Parameters_List, BMI_Help_Index_Key_List[BMI_HELP_TERCM]);

         if (parameters->Port == NULL) {

            if ((result = PORT_Constructor(parameters->Starting_Row, parameters->Starting_Column, parameters->Height, parameters->Width, PORT_NO_BORDER, parameters->Colors.Primary_Color, parameters->Colors.Primary_Color, &(parameters->Port))) == PORT_NOERR) {

               BMI_Halt_Process(parameters->Parameters_List, BMI_DISPLAY_TIME_PROCESS);
               window(1, 1, 80, 25);

            }

         }
         else {

            if (parameters->First_Pass_Flag) {

               result = BMI_Initialize_Comm_Port(parameters->Port_No, parameters->IQ_Size, parameters->OQ_Size, parameters->Int_Level, parameters->Port_Ads, parameters->Pbuffer);
               sprintf(str, "Press ESC to exit terminal mode.");
               STRING_Center(80, str);
               TEXT_Set_Text_Color(parameters->Colors.Primary_Highlight_Color, parameters->Text);
               TEXT_Set_Cursor_Position(1, 1, parameters->Text);
               TEXT_Print_String(str, parameters->Text);
               CURSOR_On();
               parameters->First_Pass_Flag = FALSE;

            }
            else {

               if (rdch_a1(parameters->Port_No, &(ch), &(piq_size), &(pstatus)) == 0) {

                  printf("%c", ch);

                  if (ch == '\n') {

                     TEXT_Retrieve_Cursor_Row(parameters->Text, &(y));
                     TEXT_Retrieve_Cursor_Column(parameters->Text, &(x));
                     TEXT_Set_Cursor_Position(1, 1, parameters->Text);
                     TEXT_Set_Text_Color(parameters->Colors.Primary_Highlight_Color, parameters->Text);
                     TEXT_Print_String(str, parameters->Text);
                     TEXT_Set_Cursor_Position(y, x, parameters->Text);

                  }

               }

               switch (*(Key)) {

                  case 0 :

                     break;

                  case KB_ESC :

                     parameters->Exit_Flag = TRUE;
                     *(Key) = 0;
                     break;

               }

               if (parameters->Exit_Flag) {

                  exit_flag = TRUE;
                  CURSOR_Off();
                  PORT_Destructor(&(parameters->Port));
                  BMI_Halt_Process(parameters->Parameters_List, BMI_COMMUNICATIONS_TERMINAL_PROCESS);
                  BMI_Activate_Process(parameters->Parameters_List, BMI_DISPLAY_TIME_PROCESS);
                  BMI_Activate_Process(parameters->Parameters_List, BMI_MAIN_MENU_PROCESS);
                  parameters->First_Pass_Flag = TRUE;
                  parameters->Exit_Flag = FALSE;
                  result = close_a1(parameters->Port_No);
                  *(Key) = 0;

               }

            }

            if (result != 0 && !exit_flag) {

               TEXT_Retrieve_Cursor_Row(parameters->Text, &(y));
               TEXT_Retrieve_Cursor_Column(parameters->Text, &(x));
               TEXT_Set_Cursor_Position(1, 78, parameters->Text);
               TEXT_Set_Text_Color(parameters->Colors.Primary_Highlight_Color, parameters->Text);
               sprintf(error_message, "%2d", result);
               TEXT_Print_String(error_message, parameters->Text);
               TEXT_Set_Cursor_Position(y, x, parameters->Text);

            }

         }

      }

   }

   if (result != 0) {

      result = 0;

   }

   return (result);

}

/*

   Function    : BMI_Help_Index
   Description :
   Inputs      : Nothing.
   Updates     : Process_Parameters
                 Key
   Outputs     : Nothing.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 08/18/92 DWP Initial coding.
   Notes       :

*/

int BMI_Help_Index(void ** Process_Parameters, CARDINAL_16 * Key) {

   BMI_HELP_INDEX_PARAMETERS * parameters;
   BMI_HELP_INDEX_LIST *       help_index;
   BMI_HELP_INDEX_LIST         help_index_node;
   BMI_HELP_TEXT_LIST *        help_text;
   BMI_HELP_TEXT_LIST          help_text_node;
   CARDINAL_32                 total_lines;
   char                        str[1024], word[1024];
   int                         i, str_offset, word_offset, result;

   /*

      Validate the parameters.  Exit if either one is invalid.

   */

   if ((result = BMI_Validate_Parameters(Process_Parameters, Key)) == EZERO) {

      /*

	 Initialize the process parameters list for this process.

      */

      if (*(Process_Parameters) == NULL) {

         result = BMI_Allocate_Parameters_List(sizeof(*(parameters)), Process_Parameters);

      }
      else {

	 /*

	    Perform the main function of this process.

	 */

         parameters = *(Process_Parameters);

         if (parameters->Help_File == NULL && !parameters->Help_Loaded_Flag) {

            parameters->Help_Available_Flag = ((parameters->Help_File = fopen("BMI.HLP", "rt")) != NULL);
            LIST_Constructor(sizeof(help_index_node), &(parameters->Help_List));

         }
         else {

            if (!parameters->Help_Loaded_Flag) {

               if (fgets(str, sizeof(str) - 1, parameters->Help_File) == NULL) {

                  fclose(parameters->Help_File);
                  parameters->Help_Loaded_Flag = TRUE;
                  BMI_Halt_Process(parameters->Parameters_List, BMI_HELP_INDEX_PROCESS);

               }
               else {

                  if (str[0] == ':' && str[6] == ':') {

                     STRING_RTrim(str);
                     strcat(str, " ");
                     strncpy(help_index_node.Index_Key, &(str[1]), sizeof(help_index_node.Index_Key));
                     strncpy(help_index_node.Index_Description, &(str[7]), sizeof(help_index_node.Index_Description));
                     LIST_Constructor(sizeof(help_text_node), &(help_index_node.Help_Text_List));
                     setmem(&(help_text_node), sizeof(help_text_node), 0);
                     LIST_Insert(&(help_text_node), LIST_LAST, help_index_node.Help_Text_List);
                     LIST_Insert(&(help_index_node), LIST_LAST, parameters->Help_List);

                  }
                  else {

                     LIST_Retrieve(parameters->Help_List, LIST_LAST, (void **) &(help_index));
                     LIST_Retrieve(help_index->Help_Text_List, LIST_LAST, (void **) &(help_text));
                     word_offset = 0;

                     for (str_offset = 0; str[str_offset] != '\0'; str_offset++) {

                        if (str[str_offset] == '\n') {

                           str[str_offset] = ' ';

                           if (word_offset == 0) {

                              help_text_node.Length = 0;
                              LIST_Insert(&(help_text_node), LIST_LAST, help_index->Help_Text_List);
                              LIST_Insert(&(help_text_node), LIST_LAST, help_index->Help_Text_List);
                              LIST_Retrieve(help_index->Help_Text_List, LIST_LAST, (void **) &(help_text));

                           }

                        }

                        if (str[str_offset] == '~') {

                           str[str_offset] = '\0';
                           str[str_offset + 1] = '\0';
                           strncat(&(help_text->Help_Text[help_text->Length]), word, sizeof(help_text->Help_Text) - help_text->Length - 1);
                           help_text->Length += word_offset;
                           word_offset = 0;
                           help_text_node.Length = 0;
                           LIST_Insert(&(help_text_node), LIST_LAST, help_index->Help_Text_List);
                           LIST_Retrieve(help_index->Help_Text_List, LIST_LAST, (void **) &(help_text));

                        }
                        else {

                           word[word_offset++] = str[str_offset];
                           word[word_offset] = '\0';

                           if (isspace(str[str_offset])) {

                              if (help_text->Length + word_offset >= sizeof(help_text->Help_Text)) {

                                 help_text_node.Length = 0;
                                 LIST_Insert(&(help_text_node), LIST_LAST, help_index->Help_Text_List);
                                 LIST_Retrieve(help_index->Help_Text_List, LIST_LAST, (void **) &(help_text));

                              }

                              strncat(&(help_text->Help_Text[help_text->Length]), word, sizeof(help_text->Help_Text) - help_text->Length - 1);
                              help_text->Length += word_offset;
                              word_offset = 0;

                           }

                        }

                     }

                  }

               }

            }
            else {

               BMI_Set_Help_Screen(parameters->Parameters_List, BMI_Help_Index_Key_List[BMI_HELP_INDHM]);

               if (parameters->Port != NULL) {

                  result = PORT_Activate(parameters->Port);

               }
               else {

                  if ((result = PORT_Constructor(parameters->Starting_Row, parameters->Starting_Column, parameters->Height, parameters->Width, PORT_SINGLE_LINE_BORDER, parameters->Colors.Primary_Color, parameters->Colors.Primary_Color, &(parameters->Port))) == PORT_NOERR) {

                     TEXT_Set_Cursor_Position(1, 22, parameters->Text);
                     TEXT_Print_String("Table of Contents", parameters->Text);

                  }

               }

               if (result == EZERO) {

                  LIST_Size(parameters->Help_List, &(total_lines));

                  if (parameters->Redraw_Screen_Flag) {

                     sprintf(str, "%-*.*s%10s", parameters->Width - 12, parameters->Width - 12, "", (parameters->First_Row_Line > 1) ? "[More] \x18  " : "");
                     TEXT_Set_Cursor_Position(2, 1, parameters->Text);
                     TEXT_Print_String(str, parameters->Text);
                     LIST_Retrieve(parameters->Help_List, parameters->First_Row_Line, (void **) &(help_index));

                     for (i = 0; i < 5; i++) {

                        if (help_index == NULL) {

                           sprintf(str, "%60s", "");

                        }
                        else {

                           sprintf(str, "%-*.*s", sizeof(help_index->Index_Description), sizeof(help_index->Index_Description), help_index->Index_Description);

                        }

                        TEXT_Set_Cursor_Position(i + 3, 2, parameters->Text);
                        TEXT_Print_String(str, parameters->Text);
                        LIST_Retrieve(parameters->Help_List, LIST_NEXT, (void **) &(help_index));

                     }

                     sprintf(str, "%-*.*s%10s", parameters->Width - 12, parameters->Width - 12, "", (parameters->First_Row_Line + 5 <= total_lines) ? "[More] \x19  " : "");
                     TEXT_Set_Cursor_Position(8, 1, parameters->Text);
                     TEXT_Print_String(str, parameters->Text);
                     parameters->Redraw_Screen_Flag = FALSE;

                  }

                  if (parameters->Previous_Row != parameters->Current_Row) {

                     TEXT_Set_Cursor_Position(parameters->Previous_Row + 3, 2, parameters->Text);
                     TEXT_Set_Text_Color(parameters->Colors.Primary_Color, parameters->Text);
                     LIST_Retrieve(parameters->Help_List, parameters->First_Row_Line + parameters->Previous_Row, (void **) &(help_index));
                     sprintf(str, "%-*.*s", sizeof(help_index->Index_Description), sizeof(help_index->Index_Description), help_index->Index_Description);
                     TEXT_Print_String(str, parameters->Text);
                     parameters->Previous_Row = parameters->Current_Row;

                  }

                  TEXT_Set_Cursor_Position(parameters->Current_Row + 3, 2, parameters->Text);
                  TEXT_Set_Text_Color(parameters->Colors.Primary_Highlight_Color, parameters->Text);
                  LIST_Retrieve(parameters->Help_List, parameters->First_Row_Line + parameters->Current_Row, (void **) &(help_index));
                  sprintf(str, "%-*.*s", sizeof(help_index->Index_Description), sizeof(help_index->Index_Description), help_index->Index_Description);
                  TEXT_Print_String(str, parameters->Text);
                  TEXT_Set_Text_Color(parameters->Colors.Primary_Color, parameters->Text);

                  switch (*(Key)) {

                     case KB_UP :
                     case KB_GRAY_UP :

                        if (parameters->Current_Row > 0) {

                           parameters->Current_Row--;

                        }
                        else {

                           if (parameters->First_Row_Line > 1) {

                              parameters->First_Row_Line--;
                              parameters->Redraw_Screen_Flag = TRUE;

                           }

                        }

                        break;

                     case KB_DOWN :
                     case KB_GRAY_DOWN :

                        if (parameters->Current_Row < 4 && (parameters->Current_Row + parameters->First_Row_Line < total_lines)) {

                           parameters->Current_Row++;

                        }
                        else {

                           if (parameters->First_Row_Line + 5 <= total_lines) {

                              parameters->First_Row_Line++;
                              parameters->Redraw_Screen_Flag = TRUE;

                           }

                        }

                        break;

                     case KB_PGUP :
                     case KB_GRAY_PGUP :

                        if (parameters->Current_Row > 0) {

                           parameters->Current_Row = 0;

                        }

                        parameters->Redraw_Screen_Flag = TRUE;

                        if (parameters->First_Row_Line > 5) {

                           parameters->First_Row_Line -= 5;

                        }
                        else {

                           parameters->First_Row_Line = 1;

                        }

                        break;

                     case KB_PGDN :
                     case KB_GRAY_PGDN :

                        if (parameters->Current_Row > 0) {

                           parameters->Current_Row = 0;

                        }

                        parameters->Redraw_Screen_Flag = TRUE;

                        if (parameters->First_Row_Line + 5 < total_lines) {

                           parameters->First_Row_Line += 5;

                        }

                        break;

                     case KB_HOME :
                     case KB_GRAY_HOME :

                        parameters->First_Row_Line = 1;
                        parameters->Current_Row = 0;
                        parameters->Redraw_Screen_Flag = TRUE;
                        break;

                     case KB_END :
                     case KB_GRAY_END :

                        parameters->First_Row_Line = (total_lines > 5) ? total_lines - 4 : 1;
                        parameters->Current_Row = (CARDINAL_16) total_lines % 5;
                        parameters->Redraw_Screen_Flag = TRUE;
                        break;

                     case KB_GRAY_ENTER :
                     case KB_ENTER :

                        BMI_Set_Help_Screen(parameters->Parameters_List, help_index->Index_Key);
                        BMI_Activate_Process(parameters->Parameters_List, BMI_HELP_TOPIC_PROCESS);
                        break;

                     case KB_ESC :

                        parameters->Exit_Flag = TRUE;
                        *(Key) = 0;
                        break;

                  }

                  if (parameters->Exit_Flag) {

                     parameters->First_Row_Line = 1;
                     parameters->Current_Row = 0;
                     parameters->Previous_Row = 0;
                     parameters->Redraw_Screen_Flag = TRUE;
                     parameters->Exit_Flag = FALSE;
                     PORT_Destructor(&(parameters->Port));
                     BMI_Halt_Process(parameters->Parameters_List, BMI_HELP_INDEX_PROCESS);
                     BMI_Activate_Process(parameters->Parameters_List, BMI_MAIN_MENU_PROCESS);

                  }

               }

            }

         }

      }

   }

   return (result);

}

/*

   Function    : BMI_Help_About
   Description :
   Inputs      : Nothing.
   Updates     : Process_Parameters
                 Key
   Outputs     : Nothing.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 08/18/92 DWP Initial coding.
   Notes       :

*/

int BMI_Help_About(void ** Process_Parameters, CARDINAL_16 * Key) {

   BMI_HELP_ABOUT_PARAMETERS * parameters;
   int                         result;

   /*

      Validate the parameters.  Exit if either one is invalid.

   */

   if ((result = BMI_Validate_Parameters(Process_Parameters, Key)) == EZERO) {

      /*

	 Initialize the process parameters list for this process.

      */

      if (*(Process_Parameters) == NULL) {

         result = BMI_Allocate_Parameters_List(sizeof(*(parameters)), Process_Parameters);

      }
      else {

	 /*

	    Perform the main function of this process.

	 */

         parameters = *(Process_Parameters);
         BMI_Set_Help_Screen(parameters->Parameters_List, BMI_Help_Index_Key_List[BMI_HELP_ABOHM]);

         if (parameters->Port != NULL) {

            result = PORT_Activate(parameters->Port);

         }
         else {

            if ((result = PORT_Constructor(parameters->Starting_Row, parameters->Starting_Column, parameters->Height, parameters->Width, PORT_SINGLE_LINE_BORDER, parameters->Colors.Primary_Color, parameters->Colors.Primary_Color, &(parameters->Port))) == PORT_NOERR) {

               TEXT_Set_Cursor_Position(2, (parameters->Width - strlen((parameters->Parameters_List->Version == BMI_WINCHESTER_VERSION) ? BMI_TITLE_1A : BMI_TITLE_1B)) / 2, parameters->Text);
               TEXT_Print_String((parameters->Parameters_List->Version == BMI_WINCHESTER_VERSION) ? BMI_TITLE_1A : BMI_TITLE_1B, parameters->Text);
               TEXT_Set_Cursor_Position(3, (parameters->Width - strlen(BMI_TITLE_2)) / 2, parameters->Text);
               TEXT_Print_String(BMI_TITLE_2, parameters->Text);
               TEXT_Set_Cursor_Position(4, (parameters->Width - strlen(BMI_TITLE_3)) / 2, parameters->Text);
               TEXT_Print_String(BMI_TITLE_3, parameters->Text);
               TEXT_Set_Cursor_Position(5, (parameters->Width - strlen(BMI_TITLE_4)) / 2, parameters->Text);
               TEXT_Print_String(BMI_TITLE_4, parameters->Text);
               TEXT_Set_Cursor_Position(6, (parameters->Width - strlen(BMI_TITLE_5)) / 2, parameters->Text);
               TEXT_Print_String(BMI_TITLE_5, parameters->Text);
               TEXT_Set_Cursor_Position(8, (parameters->Width - strlen(BMI_TITLE_6)) / 2, parameters->Text);
               TEXT_Print_String(BMI_TITLE_6, parameters->Text);

            }

         }

         if (result == EZERO) {

            if (*(Key) != 0 && *(Key) != KB_F1) {

               if (parameters->Port != NULL) {

                  PORT_Destructor(&(parameters->Port));

               }

               *(Key) = 0;
               BMI_Halt_Process(parameters->Parameters_List, BMI_HELP_ABOUT_PROCESS);
               BMI_Activate_Process(parameters->Parameters_List, BMI_MAIN_MENU_PROCESS);

            }

         }

      }

   }

   return (result);

}

/*

   Function    : BMI_Help_Print
   Description :
   Inputs      : Nothing.
   Updates     : Process_Parameters
                 Key
   Outputs     : Nothing.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 08/18/92 DWP Initial coding.
   Notes       :

*/

int BMI_Help_Print(void ** Process_Parameters, CARDINAL_16 * Key) {

   BMI_HELP_PRINT_PARAMETERS * parameters;
   BMI_HELP_TEXT_LIST *        help_text;
   char                        str[256];
   int                         result;

   /*

      Validate the parameters.  Exit if either one is invalid.

   */

   if ((result = BMI_Validate_Parameters(Process_Parameters, Key)) == EZERO) {

      /*

	 Initialize the process parameters list for this process.

      */

      if (*(Process_Parameters) == NULL) {

         result = BMI_Allocate_Parameters_List(sizeof(*(parameters)), Process_Parameters);

      }
      else {

	 /*

	    Perform the main function of this process.

	 */

         parameters = *(Process_Parameters);

         if (!parameters->Process_In_Progress_Flag) {

            BMI_Activate_Process(parameters->Parameters_List, BMI_YES_NO_MENU_PROCESS);
            ((BMI_YES_NO_MENU_PARAMETERS *) parameters->Parameters_List->Process_Descriptor[BMI_YES_NO_MENU_PROCESS].Process_Parameters)->Starting_Row = 9;
            ((BMI_YES_NO_MENU_PARAMETERS *) parameters->Parameters_List->Process_Descriptor[BMI_YES_NO_MENU_PROCESS].Process_Parameters)->Starting_Column = 23;
            ((BMI_YES_NO_MENU_PARAMETERS *) parameters->Parameters_List->Process_Descriptor[BMI_YES_NO_MENU_PROCESS].Process_Parameters)->Display_Message = "Is The Printer On-Line And Ready?";
            ((BMI_YES_NO_MENU_PARAMETERS *) parameters->Parameters_List->Process_Descriptor[BMI_YES_NO_MENU_PROCESS].Process_Parameters)->Option = 1;
            ((BMI_YES_NO_MENU_PARAMETERS *) parameters->Parameters_List->Process_Descriptor[BMI_YES_NO_MENU_PROCESS].Process_Parameters)->Invoking_Process = BMI_HELP_PRINT_PROCESS;
            ((BMI_YES_NO_MENU_PARAMETERS *) parameters->Parameters_List->Process_Descriptor[BMI_YES_NO_MENU_PROCESS].Process_Parameters)->Yes_Selected_Flag = &(((BMI_HELP_PRINT_PARAMETERS *) parameters->Parameters_List->Process_Descriptor[BMI_HELP_PRINT_PROCESS].Process_Parameters)->Print_Report_Flag);
            parameters->Process_In_Progress_Flag = TRUE;
            result = EZERO;

         }
         else {

            if ((int) parameters->Print_Report_Flag != -1) {

               if (!parameters->Print_Report_Flag) {

                  parameters->Exit_Flag = TRUE;

               }
               else {

                  if (*(Key) == KB_ESC) {

                     parameters->Exit_Flag = TRUE;
                     *(Key) = 0;

                  }
                  else {

                     if (parameters->Report_File == NULL) {

                        if (PRINTER_Status(0) != (PRINTER_NOT_BUSY | PRINTER_SELECTED) || (parameters->Report_File = fopen("PRN", "wt")) == NULL) {

                           parameters->Exit_Flag = TRUE;

                        }
                        else {

                           parameters->Page_Number = 0;
                           parameters->New_Page_Flag = TRUE;
                           parameters->Help_Index = NULL;

                        }

                     }
                     else {

                        if (parameters->New_Page_Flag) {

                           if (parameters->Page_Number++ > 0) {

                              fputc(12, parameters->Report_File);

                           }

                           fprintf(parameters->Report_File, "\n%*s%s\n\n", (80 - sizeof((parameters->Parameters_List->Version == BMI_WINCHESTER_VERSION) ? BMI_TITLE_1A : BMI_TITLE_1B)) / 2, "", (parameters->Parameters_List->Version == BMI_WINCHESTER_VERSION) ? BMI_TITLE_1A : BMI_TITLE_1B);
                           parameters->Line_Number = 4;
                           parameters->New_Page_Flag = FALSE;

                        }

                        if (parameters->Line_Number > 55) {

                           while (parameters->Line_Number++ < 59) {

                              fputc('\n', parameters->Report_File);

                           }

                           parameters->New_Page_Flag = TRUE;
                           sprintf(str, "- Page %d -", parameters->Page_Number);
                           fprintf(parameters->Report_File, "%*s%s", (80 - strlen(str)) / 2, "", str);

                        }
                        else {

                           if (parameters->Help_Index != NULL) {

                              if (LIST_Retrieve(parameters->Help_Index->Help_Text_List, ((parameters->First_Text_Node_Flag) ? LIST_FIRST : LIST_NEXT), (void **) &(help_text)) != LIST_NOERR) {

                                 parameters->Help_Index = NULL;

                              }
                              else {

                                 fprintf(parameters->Report_File, "%10s%s\n", "", help_text->Help_Text);
                                 parameters->Line_Number++;

                              }

                              parameters->First_Text_Node_Flag = FALSE;

                           }
                           else {

                              if (LIST_Retrieve(parameters->Index_Parameters->Help_List, ((parameters->First_Index_Node_Flag) ? LIST_FIRST : LIST_NEXT), (void **) &(parameters->Help_Index)) == LIST_NOERR) {

                                 sprintf(str, "%.60s", parameters->Help_Index->Index_Description);
                                 fprintf(parameters->Report_File, "\n%s\n\n", str);
                                 parameters->Line_Number += 3;
                                 parameters->First_Index_Node_Flag = FALSE;
                                 parameters->First_Text_Node_Flag = TRUE;

                              }
                              else {

                                 while (parameters->Line_Number++ < 59) {

                                    fputc('\n', parameters->Report_File);

                                 }

                                 sprintf(str, "- Page %d -", parameters->Page_Number);
                                 fprintf(parameters->Report_File, "%*s%s", (80 - strlen(str)) / 2, "", str);
                                 fputc(12, parameters->Report_File);
                                 parameters->Exit_Flag = TRUE;

                              }

                           }

                        }

                     }

                  }

               }

            }

         }

         if (parameters->Exit_Flag) {

            fclose(parameters->Report_File);
            parameters->Process_In_Progress_Flag = FALSE;
            parameters->Print_Report_Flag = -1;
            parameters->First_Index_Node_Flag = TRUE;
            parameters->Exit_Flag = FALSE;
            BMI_Halt_Process(parameters->Parameters_List, BMI_HELP_PRINT_PROCESS);
            BMI_Activate_Process(parameters->Parameters_List, BMI_MAIN_MENU_PROCESS);

         }

      }

   }

   return (result);

}

/*

   Function    : BMI_Help_Topic
   Description :
   Inputs      : Nothing.
   Updates     : Process_Parameters
                 Key
   Outputs     : Nothing.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 08/18/92 DWP Initial coding.
   Notes       :

*/

int BMI_Help_Topic(void ** Process_Parameters, CARDINAL_16 * Key) {

   BMI_HELP_TOPIC_PARAMETERS * parameters;
   BMI_HELP_TEXT_LIST *        help_text;
   CARDINAL_32                 total_lines;
   char                        str[256];
   int                         i, result;

   /*

      Validate the parameters.  Exit if either one is invalid.

   */

   if ((result = BMI_Validate_Parameters(Process_Parameters, Key)) == EZERO) {

      /*

	 Initialize the process parameters list for this process.

      */

      if (*(Process_Parameters) == NULL) {

         result = BMI_Allocate_Parameters_List(sizeof(*(parameters)), Process_Parameters);

      }
      else {

	 /*

	    Perform the main function of this process.

	 */

         parameters = *(Process_Parameters);

         if (parameters->Port != NULL) {

            result = PORT_Activate(parameters->Port);

         }
         else {

            result = PORT_Constructor(parameters->Starting_Row, parameters->Starting_Column, parameters->Height, parameters->Width, PORT_SINGLE_LINE_BORDER, parameters->Colors.Primary_Color, parameters->Colors.Primary_Color, &(parameters->Port));
            result = LIST_Retrieve(parameters->Index_Parameters->Help_List, LIST_FIRST, (void **) &(parameters->Help_Index));

            while (strncmp(parameters->Help_Index->Index_Key, parameters->Key, sizeof(parameters->Help_Index->Index_Key)) != 0) {

               if (LIST_Retrieve(parameters->Index_Parameters->Help_List, LIST_NEXT, (void **) &(parameters->Help_Index)) != LIST_NOERR) {

                  parameters->Exit_Flag = TRUE;
                  break;

               }

            }

         }

         if (result == EZERO) {

            if (parameters->Redraw_Screen_Flag) {

               TEXT_Set_Cursor_Position(1, (parameters->Width - strlen(parameters->Help_Index->Index_Description)) / 2, parameters->Text);
               sprintf(str, "%-*.*s", sizeof(parameters->Help_Index->Index_Description), strlen(parameters->Help_Index->Index_Description), parameters->Help_Index->Index_Description);
               TEXT_Print_String(str, parameters->Text);
               TEXT_Set_Cursor_Position(2, 1, parameters->Text);
               sprintf(str, "%-*.*s%10s", parameters->Width - 12, parameters->Width - 12, "", (parameters->First_Row_Line > 1) ? "[More] \x18  " : "");
               TEXT_Print_String(str, parameters->Text);
               TEXT_Set_Cursor_Position(8, 1, parameters->Text);
               LIST_Size(parameters->Help_Index->Help_Text_List, &(total_lines));
               sprintf(str, "%-*.*s%10s", parameters->Width - 12, parameters->Width - 12, "", (parameters->First_Row_Line + 5 <= total_lines) ? "[More] \x19  " : "");
	       TEXT_Print_String(str, parameters->Text);

               LIST_Retrieve(parameters->Help_Index->Help_Text_List, parameters->First_Row_Line, (void **) &(help_text));

               for (i = 0; i < 5; i++) {

                  TEXT_Set_Cursor_Position(i + 3, 4, parameters->Text);
                  sprintf(str, "%-*.*s", sizeof(help_text->Help_Text), help_text->Length, help_text->Help_Text);
                  TEXT_Print_String(str, parameters->Text);

                  if (LIST_Retrieve(parameters->Help_Index->Help_Text_List, LIST_NEXT, (void **) &(help_text)) != LIST_NOERR) {

                     break;

                  }

               }

               parameters->Redraw_Screen_Flag = FALSE;

	    }

            switch (*(Key)) {

               case KB_UP :
               case KB_GRAY_UP :

                  if (parameters->First_Row_Line > 1) {

                     parameters->First_Row_Line--;
                     parameters->Redraw_Screen_Flag = TRUE;

                  }

                  break;

               case KB_DOWN :
               case KB_GRAY_DOWN :

                  LIST_Size(parameters->Help_Index->Help_Text_List, &(total_lines));

                  if (parameters->First_Row_Line + 5 <= total_lines) {

                     parameters->First_Row_Line++;
                     parameters->Redraw_Screen_Flag = TRUE;

                  }

                  break;

               case KB_HOME :
               case KB_GRAY_HOME :

                  parameters->First_Row_Line = 1;
                  parameters->Redraw_Screen_Flag = TRUE;
                  break;

               case KB_ESC :

                  parameters->Exit_Flag = TRUE;
		  break;

            }

            *(Key) = 0;

         }

         if (parameters->Exit_Flag) {

            parameters->First_Row_Line = 1;
            parameters->Redraw_Screen_Flag = TRUE;
            parameters->Exit_Flag = FALSE;
            PORT_Destructor(&(parameters->Port));
            BMI_Halt_Process(parameters->Parameters_List, BMI_HELP_TOPIC_PROCESS);

         }

      }

   }

   return (result);

}

