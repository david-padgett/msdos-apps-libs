/*

   File        : BMI3.C
   Module      : MISCELLANEOUS
   System      : BMI
   Description : Miscellaneous support procedures and functions for the BMI system.
   Modified    : 08/18/92 DWP Created.
   Notes       :

*/

#include <alloc.h>
#include <conio.h>
#include <ctype.h>
#include <dos.h>
#include <errno.h>
#include <memory.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <fcntl.h>
#include <io.h>
#include <sys\stat.h>

#include "KB\kb.h"
#include "String\string.h"

#include "bmi.h"

/*

   Procedure   : BMI_Activate_Process
   Description : Activates the specified process.
   Inputs      : Parameters_List = The parameters list to use while the BMI system is active.
                 Process         = The process to activate.
   Updates     : Nothing.
   Outputs     : Nothing.
   Returns     : Nothing.
   Modified    : 08/18/92 DWP Initial coding.
   Notes       :

*/

void BMI_Activate_Process(BMI_PARAMETERS_LIST * Parameters_List, BMI_PROCESS_TYPES Process) {

   Parameters_List->Process_Descriptor[Process].Process_Active_Flag = TRUE;

}

/*

   Procedure   : BMI_Halt_Process
   Description : De-activates the specified process.
   Inputs      : Parameters_List = The parameters list to use while the BMI system is active.
                 Process         = The process to activate.
   Updates     : Nothing.
   Outputs     : Nothing.
   Returns     : Nothing.
   Modified    : 08/18/92 DWP Initial coding.
   Notes       :

*/

void BMI_Halt_Process(BMI_PARAMETERS_LIST * Parameters_List, BMI_PROCESS_TYPES Process) {

   Parameters_List->Process_Descriptor[Process].Process_Active_Flag = FALSE;

}

/*

   Function    : BMI_Validate_Parameters
   Description : Determines if the two parameters reference valid memory locations.
   Inputs      : Process_Parameters = The parameters list used by the calling process.
                 Key                = The last key pressed.
   Updates     : Nothing.
   Outputs     : Nothing.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 08/18/92 DWP Initial coding.
   Notes       :

*/

int BMI_Validate_Parameters(void ** Process_Parameters, CARDINAL_16 * Key) {

   int result;

   /*

      Validate the parameters.  Exit if either one is invalid.

   */

   if (Process_Parameters == NULL || Key == NULL) {

      result = EINVAL;

   }
   else {

      result = EZERO;

   }

   return (result);


}

/*

   Function    : BMI_Allocate_Parameters_List
   Description : Allocates the parameters list for the calling process.
   Inputs      : Process_Parameters_Size = The size of the new parameters list.
   Updates     : Nothing.
   Outputs     : Process_Parameters      = The parameters list used by the calling process.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 08/18/92 DWP Initial coding.
   Notes       :

*/

int BMI_Allocate_Parameters_List(CARDINAL_16 Process_Parameters_Size, void ** Process_Parameters) {

   int result;

   /*

      Initialize the process parameters list for this process.

   */

   if ((*(Process_Parameters) = malloc(Process_Parameters_Size)) == NULL) {

      result = ENOMEM;

   }
   else {

      setmem(*(Process_Parameters), Process_Parameters_Size, 0);
      result = EZERO;

   }

   return (result);

}

/*

   Procedure   : BMI_Display_Time
   Description : Displays the current time and date on the screen.
   Inputs      : Nothing.
   Updates     : Process_Parameters = The parameters list used by this process.
                 Key                = The last key that was pressed.
   Outputs     : Nothing.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 08/18/92 DWP Initial Coding.
   Notes       :

*/

int BMI_Display_Time(void ** Process_Parameters, CARDINAL_16 * Key) {

   BMI_DISPLAY_TIME_PARAMETERS * parameters;
   time_t                        timer;
   struct tm *                   current_time;
   char                          output_string[256], am_pm_value;
   int                           result;

   /*

      Validate the parameters.  Exit if either one is invalid.

   */

   if (Process_Parameters == NULL || Key == NULL) {

      result = EINVAL;

   }
   else {

      /*

	 Initialize the process parameters list for this process.

      */

      if (*(Process_Parameters) == NULL) {

         if ((*(Process_Parameters) = malloc(sizeof(*(parameters)))) == NULL) {

            result = ENOMEM;

         }
         else {

            setmem(*(Process_Parameters), sizeof(*(parameters)), 0);
            result = EZERO;

         }

      }
      else {

	 /*

	    Perform the main function of this process.

	 */

         parameters = *(Process_Parameters);
         timer = time(NULL);
         current_time = localtime(&timer);

	 /*

	    Toggle the blinking character between the hours and minutes fields of the displayed time.

	 */

         if (parameters->Seconds_Value != current_time->tm_sec || parameters->Separator_Character == '\0') {

            parameters->Seconds_Value = current_time->tm_sec;
            parameters->Separator_Character = (parameters->Separator_Character == ':') ? ' ' : ':';

	    /*

	       Determine if it is before or after 12:00 PM, so that the 12 hour format can be displayed on the screen.

	    */

            if (current_time->tm_hour >= 13) {

               current_time->tm_hour -= 12;
               am_pm_value = 'P';

            }
            else {

               if (current_time->tm_hour == 0) {

                  current_time->tm_hour = 12;

               }

               am_pm_value = 'A';

            }

	    /*

	       Display the time on the screen.

	    */

            TEXT_Set_Text_Color(parameters->Colors.Primary_Color, parameters->Text);
            window(1, 1, 80, 25);

            if (parameters->Minutes_Value == current_time->tm_min) {

               TEXT_Set_Cursor_Position(parameters->Row, parameters->Column + 2, parameters->Text);
               TEXT_Print_Character(parameters->Separator_Character, parameters->Text);

            }
            else {

               sprintf(output_string, "%2u%c%02u %cM  %02u/%02u/%02u", current_time->tm_hour, parameters->Separator_Character, current_time->tm_min, am_pm_value, current_time->tm_mon + 1, current_time->tm_mday, current_time->tm_year % 100);
               TEXT_Set_Cursor_Position(parameters->Row, parameters->Column, parameters->Text);
               TEXT_Print_String(output_string, parameters->Text);
               parameters->Minutes_Value = current_time->tm_min;

            }

         }

         result = EZERO;

      }

   }

   return (result);

}

/*

   Function    : BMI_Load_Configuration
   Description : Loads the specified configuration file.
   Inputs      : Config_File_Name   = The name of configuration file to load.
   Updates     : Nothing.
   Outputs     : Default_Parameters = The default parameters list.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 08/18/92 DWP Initial coding.
   Notes       :

*/

int BMI_Load_Configuration(char * Config_File_Name, BMI_DEFAULT_PARAMETERS * Default_Parameters) {

   FILE * config_fp;
   int    result;

   if (Config_File_Name == NULL || Default_Parameters == NULL) {

      result = EINVDAT;

   }
   else {

      /*

	 Open the configuration file.  Continue only if no errors occurred.

      */

      if ((config_fp = fopen(Config_File_Name, "rb")) == NULL) {

          result = EACCES;

      }
      else {

	 /*

	    Load the configuration file into memory.

	 */

         if (fread(Default_Parameters, sizeof(*(Default_Parameters)), 1, config_fp) != 1 || strcmp(Default_Parameters->ID, BMI_CONFIG_FILE_TITLE) != 0) {

            result = EINVDAT;

         }
         else {

            result = EZERO;

         }

         fclose(config_fp);

      }

   }

   return (result);

}

/*

   Function    : BMI_Save_Configuration
   Description : Saves a configuration to disk.
   Inputs      : Config_File_Name   = The file to write to.
                 Default_Parameters = The configuration to save.
   Updates     : Nothing.
   Outputs     : Nothing.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 08/18/92 DWP Initial coding.
   Notes       :

*/

int BMI_Save_Configuration(char * Config_File_Name, BMI_DEFAULT_PARAMETERS * Default_Parameters) {

   FILE * config_fp;
   int    result;

   if (Config_File_Name == NULL || Default_Parameters == NULL) {

      result = EINVDAT;

   }
   else {


      /*

	 Open the configuration file.  Continue only if no errors occurred.

      */

      if ((config_fp = fopen(Config_File_Name, "wb")) == NULL) {

         result = EACCES;

      }
      else {

         strcpy(Default_Parameters->ID, BMI_CONFIG_FILE_TITLE);

	 /*

	    Save the configuration file to disk.

	 */

         if (fwrite(Default_Parameters, sizeof(*(Default_Parameters)), 1, config_fp) != 1) {

            result = EFAULT;

         }
         else {

            result = EZERO;

         }

         fclose(config_fp);

      }

   }

   return (result);

}

/*

   Function    : BMI_Yes_No_Menu
   Description : Processes the Yes/No message used in various other processes.
   Inputs      : Nothing.
   Updates     : Process_Parameters = The parameters list used by this process.
                 Key                = The last key that was pressed.
   Outputs     : Nothing.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 08/18/92 DWP Initial coding.
   Notes       :

*/

int BMI_Yes_No_Menu(void ** Process_Parameters, CARDINAL_16 * Key) {

   BMI_YES_NO_MENU_PARAMETERS * parameters;
   CARDINAL_16                  port_length, position;
   BOOLEAN                      valid_key_flag, option_selected_flag, process_aborted_flag;
   int                          result;

   /*

      Validate the parameters.  Exit if either one is invalid.

   */

   if (Process_Parameters == NULL || Key == NULL) {

      result = EINVAL;

   }
   else {

      /*

	 Initialize the process parameters list for this process.

      */

      if (*(Process_Parameters) == NULL) {

         if ((*(Process_Parameters) = malloc(sizeof(*(parameters)))) == NULL) {

            result = ENOMEM;

         }
         else {

            setmem(*(Process_Parameters), sizeof(*(parameters)), 0);
            result = EZERO;

         }

      }
      else {

         parameters = *(Process_Parameters);

	 /*

	    Initialize the port and menu, if necessary.

	 */

         if (parameters->Menu != NULL) {

            result = PORT_Activate(parameters->Port);

         }
         else {

            port_length = strlen(parameters->Display_Message);

            if ((result = PORT_Constructor(parameters->Starting_Row, parameters->Starting_Column, 7, port_length + 4, PORT_DOUBLE_LINE_BORDER, parameters->Colors.Primary_Color, parameters->Colors.Primary_Color, &(parameters->Port))) == PORT_NOERR) {

	       /*

		  Display the 'Yes/No'menu.

	       */

               if ((result = MENU_Constructor(parameters->Menu_Text, 4, (port_length - 3) / 2, parameters->Colors.Primary_Color, parameters->Colors.Secondary_Color, parameters->Colors.Primary_Highlight_Color, parameters->Colors.Secondary_Highlight_Color, NULL, 0, 0, BLACK, BLACK, parameters->Text, &(parameters->Menu))) == MENU_NOERR) {

                  TEXT_Set_Text_Color(parameters->Colors.Primary_Color, parameters->Text);
                  TEXT_Set_Cursor_Position(2, 2, parameters->Text);
                  TEXT_Print_String(parameters->Display_Message, parameters->Text);
                  result = MENU_Display(parameters->Menu, parameters->Option);

               }

            }

         }

	 /*

	    Continue only if no errors occurred above and a key was pressed.

	 */

         if (result == EZERO && *(Key) != 0) {

            valid_key_flag = TRUE;
            option_selected_flag = FALSE;
            process_aborted_flag = FALSE;

            switch (*(Key)) {

	       /*

		  Move the cursor to the left.

	       */

               case KB_LEFT :
               case KB_GRAY_LEFT :
               case KB_SHIFT_TAB :

	       /*

		  Move the cursor to the right.

	       */

               case KB_RIGHT :
               case KB_GRAY_RIGHT :
               case KB_TAB :

                  parameters->Option = (parameters->Option == 1) ? 2 : 1;
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

                  parameters->Option = 2;
                  break;

	       /*

		  Select the currently highlighted option.

	       */

               case KB_ENTER :
               case KB_GRAY_ENTER :

                  *(parameters->Yes_Selected_Flag) = (parameters->Option == 1) ? TRUE : FALSE;
                  option_selected_flag = TRUE;
                  break;

	       /*

		  Discontinue processing the menu.

	       */

               case KB_ESC :

                  process_aborted_flag = TRUE;
                  *(parameters->Yes_Selected_Flag) = FALSE;

                  break;

               default :

		  /*

		     Determine if one of the menu hot-keys was pressed.


		  */

                  if ((position = STRING_CharPos(parameters->Menu_Keys_List, (char) toupper((*(Key) % 256)))) == 0) {

                     valid_key_flag = FALSE;

                  }
                  else {

                     parameters->Option = position;

                     if (position == 1) {

                        *(parameters->Yes_Selected_Flag) = (parameters->Option == 1) ? TRUE : FALSE;

                     }

                     option_selected_flag = TRUE;

                  }

            }

	    /*

	       Update or remove the menu if a valid key was pressed.

	    */

            if (valid_key_flag) {

               *(Key) = 0;

               if (!process_aborted_flag && !option_selected_flag) {

                  result = MENU_Display(parameters->Menu, parameters->Option);

               }
               else {

		  /*

		     Remove the menu and port.

		  */

                  if ((result = MENU_Destructor(&(parameters->Menu))) == MENU_NOERR) {

                     BMI_Activate_Process(parameters->Parameters_List, parameters->Invoking_Process);
                     BMI_Halt_Process(parameters->Parameters_List, BMI_YES_NO_MENU_PROCESS);
                     result = PORT_Destructor(&(parameters->Port));

                  }

               }

            }

         }

      }

   }

   return (result);

}

/*

   Function    : BMI_Input
   Description : Allows information to be entered via the keyboard.
   Inputs      :
   Updates     :
   Outputs     :
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 08/18/92 DWP Initial coding.
   Notes       :

*/

int BMI_Input(BMI_INPUT_DESCRIPTOR * Input, CARDINAL_16 * Key) {

   CARDINAL_16 current_color, cursor_color;
   struct time curr_time;
   char        str[100];
   int         result;

   if (Input == NULL) {

      result = EINVAL;

   }
   else {

      result = EZERO;

      if (Input->Refresh_Flag) {

         TEXT_Retrieve_Text_Color(Input->Text, &current_color);
         TEXT_Set_Text_Color((Input->Marked_Flag) ? Input->Colors.Secondary_Highlight_Color : Input->Colors.Primary_Highlight_Color, Input->Text);
         TEXT_Set_Cursor_Position(Input->Current_Row, Input->Current_Column, Input->Text);
         sprintf(str, "%-*.*s", Input->Display_Length, Input->Display_Length, ((Input->Type == STRING_TYPE) || (Input->Type == INTEGER_16_TYPE && atoi(Input->Value) != 0)) ? Input->Value : "");
         TEXT_Print_String(str, Input->Text);
	 TEXT_Set_Text_Color(current_color, Input->Text);
         TEXT_Set_Cursor_Position(Input->Current_Row, Input->Current_Column + Input->Current_Offset, Input->Text);
         Input->Display_Cursor_Flag = TRUE;
         Input->Color_Indicator_Flag = FALSE;
         Input->Refresh_Flag = FALSE;

      }
      else {

         if ((Input->Previous_Offset != Input->Current_Offset) || Input->Display_Cursor_Flag) {

            TEXT_Retrieve_Text_Color(Input->Text, &current_color);

            TEXT_Set_Text_Color(Input->Colors.Primary_Highlight_Color, Input->Text);
            TEXT_Set_Cursor_Position(Input->Current_Row, Input->Current_Column + Input->Previous_Offset, Input->Text);
            TEXT_Print_Character(Input->Value[Input->Previous_Offset], Input->Text);

            cursor_color = ((Input->Colors.Primary_Highlight_Color << 4) | (Input->Colors.Primary_Highlight_Color >> 4)) & 0x0ff;
            TEXT_Set_Text_Color(cursor_color, Input->Text);
            TEXT_Set_Cursor_Position(Input->Current_Row, Input->Current_Column + Input->Current_Offset, Input->Text);
            TEXT_Print_Character(Input->Value[Input->Current_Offset], Input->Text);

            TEXT_Set_Text_Color(current_color, Input->Text);
            Input->Previous_Offset = Input->Current_Offset;
            Input->Display_Cursor_Flag = FALSE;

         }

         gettime(&(curr_time));

         if (curr_time.ti_hund > 50) {

            TEXT_Retrieve_Text_Color(Input->Text, &current_color);

            cursor_color = (Input->Color_Indicator_Flag) ? ((Input->Colors.Primary_Highlight_Color << 4) | (Input->Colors.Primary_Highlight_Color >> 4)) & 0x0ff : Input->Colors.Primary_Highlight_Color;
            Input->Color_Indicator_Flag = !Input->Color_Indicator_Flag;
            TEXT_Set_Text_Color(cursor_color, Input->Text);
            TEXT_Set_Cursor_Position(Input->Current_Row, Input->Current_Column + Input->Previous_Offset, Input->Text);
            TEXT_Print_Character(Input->Value[Input->Current_Offset], Input->Text);

         }

         switch (*(Key)) {

            case 0 :

               break;

            case KB_BACKSPACE :

               if (Input->Current_Offset > 0) {

                  Input->Current_Offset--;
                  memmove(&(Input->Value[Input->Current_Offset]), &(Input->Value[Input->Current_Offset + 1]), Input->Edit_Length - Input->Current_Offset);
                  Input->Refresh_Flag = TRUE;

               }

               *(Key) = 0;
               break;

	    case KB_DEL :
	    case KB_GRAY_DEL :

	       memmove(&(Input->Value[Input->Current_Offset]), &(Input->Value[Input->Current_Offset + 1]), Input->Edit_Length - Input->Current_Offset);
	       Input->Refresh_Flag = TRUE;
	       *(Key) = 0;
	       break;

            default :

               if (Input->Type == STRING_TYPE) {

                  if ((char) *(Key) >= ' ' && (char) *(Key) <= '~' && Input->Current_Offset < Input->Edit_Length) {

                     Input->Value[Input->Current_Offset] = (char) *(Key);
                     TEXT_Set_Cursor_Position(Input->Current_Row, Input->Current_Column + Input->Current_Offset, Input->Text);
                     Input->Current_Offset += (Input->Current_Offset < Input->Edit_Length - 1) ? 1 : 0;
                     TEXT_Print_Character((char) *(Key), Input->Text);
                     *(Key) = 0;

                  }

               }
               else {

                  if ((((char) *(Key) >= '0' && (char) *(Key) <= '9') || (char) *(Key) == '+' || (char) *(Key) == '-') && Input->Current_Offset < Input->Edit_Length) {

                     Input->Value[Input->Current_Offset] = (char) *(Key);
                     TEXT_Set_Cursor_Position(Input->Current_Row, Input->Current_Column + Input->Current_Offset, Input->Text);
                     Input->Current_Offset += (Input->Current_Offset < Input->Edit_Length - 1) ? 1 : 0;
                     TEXT_Print_Character((char) *(Key), Input->Text);
                     *(Key) = 0;

                     if (Input->First_Pass_Flag) {

                        setmem(&(Input->Value[1]), sizeof(Input->Value) - 1, '\0');
                        Input->First_Pass_Flag = FALSE;
                        Input->Refresh_Flag = TRUE;

                     }

                  }

               }

               if (Input->Current_Offset + 1 == Input->Edit_Length) {

                  Input->Display_Cursor_Flag = TRUE;

               }

         }

      }

   }

   return (result);

}

/*

   Procedure  : BMI_Clear_Edit_Parameters
   Description : Allows information to be entered via the keyboard.
   Inputs      : Nothing.
   Updates     : Process_Parameters
   Outputs     : Nothing.
   Returns     : Nothing.
   Modified    : 08/18/92 DWP Initial coding.
   Notes       :

*/

void BMI_Clear_Edit_Parameters(BMI_EDIT_EDIT_PARAMETERS * Process_Parameters) {

   int i;

   setmem(&(Process_Parameters->Part_Number.Value), sizeof(Process_Parameters->Part_Number.Value), 0);
   Process_Parameters->Part_Number.Integer_Value = 0;
   setmem(&(Process_Parameters->Valve_Pack_Number.Value), sizeof(Process_Parameters->Valve_Pack_Number.Value), 0);
   Process_Parameters->Valve_Pack_Number.Integer_Value = 0;
   setmem(&(Process_Parameters->Multiple_Part_Number.Value), sizeof(Process_Parameters->Multiple_Part_Number.Value), 0);
   Process_Parameters->Multiple_Part_Number.Integer_Value = 0;
   setmem(&(Process_Parameters->Last_Bin_Sensor.Value), sizeof(Process_Parameters->Last_Bin_Sensor.Value), 0);
   Process_Parameters->Last_Bin_Sensor.Integer_Value = 0;
   setmem(&(Process_Parameters->Total_Cycle_Time.Value), sizeof(Process_Parameters->Total_Cycle_Time.Value), 0);
   Process_Parameters->Total_Cycle_Time.Integer_Value = 0;

   for (i = 0; i < 80; i++) {

      setmem(&(Process_Parameters->Advance_Time[i].Value), sizeof(Process_Parameters->Advance_Time[i].Value), 0);
      Process_Parameters->Advance_Time[i].Integer_Value = 0;

      setmem(&(Process_Parameters->Retract_Time[i].Value), sizeof(Process_Parameters->Retract_Time[i].Value), 0);
      Process_Parameters->Retract_Time[i].Integer_Value = 0;

   }

}

/*

   Function    : BMI_Load_Edit_Parameters
   Description : Saves the edit parameters to disk.
   Inputs      : File_Name          =
                 Process_Parameters =
   Updates     : Nothing.
   Outputs     : Nothing.
   Returns     : Nothing.
   Modified    : 08/18/92 DWP Initial coding.
   Notes       :

*/

int BMI_Load_Edit_Parameters(char * File_Name, BMI_EDIT_EDIT_PARAMETERS * Process_Parameters) {

   FILE *  load_file;
   BOOLEAN exit_flag;
   char    whole_file_name[MAXPATH], str[256], value[256];
   int     i, result;

   if (File_Name != NULL && File_Name[0] != '\0') {

      sprintf(whole_file_name, "%-.8s.DAT", File_Name);

      if ((load_file = fopen(whole_file_name, "rt")) == NULL) {

         result = EACCES;

      }
      else {

         result = EZERO;

         for(exit_flag = FALSE; !exit_flag && fgets(str, sizeof(str) - 1, load_file) != NULL;) {

            if (strncmp(str, "PN", 2) == 0) {

               strncpy(Process_Parameters->Part_Number.Value, str + 3, Process_Parameters->Part_Number.Display_Length);

            }
            else {

               if (strncmp(str, "CD", 2) == 0) {

                  strcpy(value, str + 3);

                  if (atoi(value) < Process_Parameters->Valve_Pack_Number.Minimum_Value || atoi(value) > Process_Parameters->Valve_Pack_Number.Maximum_Loadable_Value) {

                     sprintf(value, "%*u", Process_Parameters->Valve_Pack_Number.Display_Length, Process_Parameters->Valve_Pack_Number.Minimum_Value);

                  }

                  sprintf(Process_Parameters->Valve_Pack_Number.Value, "%*u", Process_Parameters->Valve_Pack_Number.Display_Length, atoi(value));
                  Process_Parameters->Valve_Pack_Number.Integer_Value = atoi(value);

               }
               else {

                  if (strncmp(str, "MP", 2) == 0) {

                     strcpy(value, str + 3);

                     if (atoi(value) < Process_Parameters->Multiple_Part_Number.Minimum_Value || atoi(value) > Process_Parameters->Multiple_Part_Number.Maximum_Loadable_Value) {

                        sprintf(value, "%*u", Process_Parameters->Multiple_Part_Number.Display_Length,  Process_Parameters->Multiple_Part_Number.Minimum_Value);

		     }

                     sprintf(Process_Parameters->Multiple_Part_Number.Value, "%*u", Process_Parameters->Multiple_Part_Number.Display_Length, atoi(value));
                     Process_Parameters->Multiple_Part_Number.Integer_Value = atoi(value);

                  }
                  else {

                     if (strncmp(str, "LB", 2) == 0) {

                        strcpy(value, str + 3);

                        if (atoi(value) < Process_Parameters->Last_Bin_Sensor.Minimum_Value || atoi(value) > Process_Parameters->Last_Bin_Sensor.Maximum_Loadable_Value) {

                           sprintf(value, "%*u", Process_Parameters->Last_Bin_Sensor.Display_Length, Process_Parameters->Last_Bin_Sensor.Minimum_Value);

                        }

                        sprintf(Process_Parameters->Last_Bin_Sensor.Value, "%*u", Process_Parameters->Last_Bin_Sensor.Display_Length, atoi(value));
                        Process_Parameters->Last_Bin_Sensor.Integer_Value = atoi(value);

                     }
                     else {

                        if (strncmp(str, "TC", 2) == 0) {

                           strcpy(value, str + 3);

                           if (atoi(value) < Process_Parameters->Total_Cycle_Time.Minimum_Value || atoi(value) > Process_Parameters->Total_Cycle_Time.Maximum_Loadable_Value) {

                              sprintf(value, "%*u", Process_Parameters->Total_Cycle_Time.Display_Length, Process_Parameters->Total_Cycle_Time.Minimum_Value);

                           }

                           sprintf(Process_Parameters->Total_Cycle_Time.Value, "%*u", Process_Parameters->Total_Cycle_Time.Display_Length, atoi(value));
                           Process_Parameters->Total_Cycle_Time.Integer_Value = atoi(value);

                        }
                        else {

			   if (strncmp(str, "VA", 2) == 0) {

                              sprintf(value, "%-2.2s", str + 3);
                              i = atoi(value) - 1;
                              strcpy(value, str + 6);

                              if (atoi(value) < Process_Parameters->Advance_Time[i].Minimum_Value || atoi(value) > Process_Parameters->Advance_Time[i].Maximum_Loadable_Value) {

                                 sprintf(value, "%*u", Process_Parameters->Advance_Time[i].Display_Length, Process_Parameters->Advance_Time[i].Minimum_Value);

                              }

                              sprintf(Process_Parameters->Advance_Time[i].Value, "%*u", Process_Parameters->Advance_Time[i].Display_Length, atoi(value));
                              Process_Parameters->Advance_Time[i].Integer_Value = atoi(value);

                              if (Process_Parameters->Retract_Time[i].Integer_Value <= atoi(value)) {

                                 sprintf(Process_Parameters->Retract_Time[i].Value, "%*u", Process_Parameters->Retract_Time[i].Display_Length, atoi(value) + 1);
                                 Process_Parameters->Retract_Time[i].Integer_Value = atoi(value) + 1;

			      }

                              if (Process_Parameters->Last_Bin_Sensor.Integer_Value < atoi(value)) {

                                 sprintf(Process_Parameters->Last_Bin_Sensor.Value, "%*u", Process_Parameters->Last_Bin_Sensor.Display_Length, atoi(value));
                                 Process_Parameters->Last_Bin_Sensor.Integer_Value = atoi(value);

                              }

                           }
                           else {

                              if (strncmp(str, "VR", 2) == 0) {

                                 sprintf(value, "%-2.2s", str + 3);
                                 i = atoi(value) - 1;
                                 strcpy(value, str + 6);

                                 if (atoi(value) < Process_Parameters->Retract_Time[i].Minimum_Value || atoi(value) > Process_Parameters->Retract_Time[i].Maximum_Loadable_Value) {

				    sprintf(value, "%*u", Process_Parameters->Retract_Time[i].Display_Length, Process_Parameters->Advance_Time[i].Integer_Value);

                                 }

                                 sprintf(Process_Parameters->Retract_Time[i].Value, "%*u", Process_Parameters->Retract_Time[i].Display_Length, atoi(value));
                                 Process_Parameters->Retract_Time[i].Integer_Value = atoi(value);

                                 if (Process_Parameters->Total_Cycle_Time.Integer_Value < atoi(value)) {

                                    sprintf(Process_Parameters->Total_Cycle_Time.Value, "%*u", Process_Parameters->Total_Cycle_Time.Display_Length, atoi(value));
                                    Process_Parameters->Total_Cycle_Time.Integer_Value = atoi(value);

                                 }

                              }
                              else {

                                 exit_flag = TRUE;

                              }

                           }

                        }

                     }

                  }

               }

            }

         }

      }

   }

   return (result);

}

/*

   Function    : BMI_Save_Edit_Parameters
   Description : Saves the edit parameters to disk.
   Inputs      : File_Name          =
                 Process_Parameters =
   Updates     : Nothing.
   Outputs     : Nothing.
   Returns     : Nothing.
   Modified    : 08/18/92 DWP Initial coding.
   Notes       :

*/

int BMI_Save_Edit_Parameters(char * File_Name, BMI_EDIT_EDIT_PARAMETERS * Process_Parameters) {

   FILE * save_file;
   char   whole_file_name[MAXPATH];
   int    i, result;

   if (File_Name != NULL && File_Name[0] != '\0') {

      sprintf(whole_file_name, "%-.8s.DAT", File_Name);

      if ((save_file = fopen(whole_file_name, "wt")) == NULL) {

	 result = EACCES;

      }
      else {

         fprintf(save_file, "PN,%-*.*s\n", Process_Parameters->Part_Number.Display_Length, Process_Parameters->Part_Number.Display_Length, Process_Parameters->Part_Number.Value);
         fprintf(save_file, "CD,%0*u\n", Process_Parameters->Valve_Pack_Number.Display_Length, Process_Parameters->Valve_Pack_Number.Integer_Value);
         fprintf(save_file, "MP,%0*u\n", Process_Parameters->Multiple_Part_Number.Display_Length, Process_Parameters->Multiple_Part_Number.Integer_Value);
         fprintf(save_file, "LB,%0*u\n", Process_Parameters->Last_Bin_Sensor.Display_Length, Process_Parameters->Last_Bin_Sensor.Integer_Value);
         fprintf(save_file, "TC,%0*u\n", Process_Parameters->Total_Cycle_Time.Display_Length, Process_Parameters->Total_Cycle_Time.Integer_Value);

	 for (i = 0; i < 80; i++) {

            fprintf(save_file, "VA,%2u,%0*u\n", i + 1, Process_Parameters->Advance_Time[i].Display_Length, Process_Parameters->Advance_Time[i].Integer_Value);
            fprintf(save_file, "VR,%2u,%0*u\n", i + 1, Process_Parameters->Retract_Time[i].Display_Length, Process_Parameters->Retract_Time[i].Integer_Value);

         }

         fclose(save_file);
         result = EZERO;

      }

   }

   return (result);

}

/*

   Procedure   : BMI_Set_Help_Screen
   Description :
   Inputs      : Process_Parameters
                 Key
   Updates     : Nothing.
   Outputs     : Nothing.
   Returns     : Nothing.
   Modified    : 08/18/92 DWP Initial coding.
   Notes       :

*/

void BMI_Set_Help_Screen(BMI_PARAMETERS_LIST * Process_Parameters, char * Key) {

   BMI_HELP_TOPIC_PARAMETERS * help_topic_parameters;

   help_topic_parameters = Process_Parameters->Process_Descriptor[BMI_HELP_TOPIC_PROCESS].Process_Parameters;
   help_topic_parameters->Key = Key;

}
