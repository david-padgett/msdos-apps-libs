/* File        : REMINDR1.C
   Module      : REMINDER
   System      : REMINDER
   Description : The main module for the REMINDER program.
   Modified    : 09/16/92 DWP Created.
   Notes       :
*/

#include <ctype.h>
#include <dir.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Date\date.h"
#include "List\list.h"
#include "KB\kb.h"
#include "Port\port.h"
#include "String\string.h"
#include "Text\text.h"
#include "Text_Int\text_int.h"

/* Function    : REMINDER_Calculate_Port_Height
   Description : The main entry point to the REMINDER module.
   Inputs      : Message_List = The message being displayed.
                 Port_Width   = The length of each line in the port in which the text will be displayed.
   Updates     : Nothing.
   Outputs     : Nothing.
   Returns     : The total number of lines required to display the entire message.
   Modified    : 09/16/92 DWP Initial coding.
   Notes       :
*/

CARDINAL_16 REMINDER_Calculate_Port_Height(LIST Message_List, CARDINAL_16 Port_Width) {

   char *      message_text_line;
   CARDINAL_16 message_text_line_pos, message_text_line_length, current_column_pos, last_word_start_pos, total_lines_required, result;

   /* Get the first message line from the message line list.  If no message line exists, then exit. */

   if (LIST_Retrieve(Message_List, LIST_FIRST, (void *) &(message_text_line)) == LIST_NOERR) {

      total_lines_required = 0;

      /* Loop until all of the message lines have been processed. */

      do {

         message_text_line_length = strlen(message_text_line);
         current_column_pos = 0;
         last_word_start_pos = 0;

         /* Loop until the end of the current message line has been encountered. */

         for (message_text_line_pos = 0; message_text_line_pos < message_text_line_length; message_text_line_pos++) {

            /* Increment the total number of lines required if the current word cannot fit on the current line. */

            if (current_column_pos == Port_Width) {

               total_lines_required++;
               message_text_line_pos = last_word_start_pos;
               current_column_pos = 0;
               last_word_start_pos = 0;

            }
            else {

               /* Reset the start of the last word, if necessary. */

               if (isspace(message_text_line[message_text_line_pos])) {

                  last_word_start_pos = message_text_line_pos;

               }

               current_column_pos++;

            }

         }

      } while (LIST_Retrieve(Message_List, LIST_NEXT, (void *) &(message_text_line)) != LIST_NOERR);

   }

   result = total_lines_required;

   return (result);

}

/* Function    : REMINDER_Main
   Description : The main entry point to the REMINDER module.
   Inputs      : LIST Message_List          = The message being displayed.
                 Upper_Left_Row_Position    = The starting row of the port in which the text will be displayed.
                 Upper_Left_Column_Position = The starting column of the port in which the text will be displayed.
                 Port_Width                 = The length of each line in the port in which the text will be displayed.
                 Text_Foreground_Color      = The text foreground color.
                 Text_Background_Color      = The text background color.
                 Border_Type                = The border type, either 0 (no border), 1 (single line border), or 2 (double line
                                              border).
                 Border_Foreground_Color    = The border foreground color.
                 Border_Background_Color    = The border background color.
                 Wait_For_Keypress_Flag     = A flag indicating whether or not a key should be pressed before exiting the function.
                 Current_Date               = The current system date.
                 Countdown_Date             = The date on which the event described by the message takes place.
   Updates     : Nothing.
   Outputs     : Nothing.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 09/16/92 DWP Initial coding.
   Notes       :
*/

int REMINDER_Main(LIST Message_List, CARDINAL_16 Upper_Left_Row_Position, CARDINAL_16 Upper_Left_Column_Position, CARDINAL_16 Port_Width, CARDINAL_16 Text_Foreground_Color, CARDINAL_16 Text_Background_Color, int Border_Type, CARDINAL_16 Border_Foreground_Color, CARDINAL_16 Border_Background_Color, BOOLEAN Wait_For_Keypress_Flag, DATE_YYYYMMDD Current_Date, DATE_YYYYMMDD Countdown_Date) {

   PORT        port;
   TEXT        text;
   char *      port_border_descriptor;
   CARDINAL_16 height;
   int         result;

   TEXT_Constructor(BGI_GotoYX, BGI_GotoY, BGI_GotoX, BGI_WhereY, BGI_WhereX, BGI_TextAttr, BGI_GetTextInfo, BGI_ClrScr, BGI_Print_Character, BGI_Print_String, &(text));
   port_border_descriptor = (Border_Type == 2) ? PORT_DOUBLE_LINE_BORDER : ((Border_Type == 1) ? PORT_SINGLE_LINE_BORDER : PORT_NO_BORDER);
   height = REMINDER_Calculate_Port_Height(Message_List, Port_Width);

   if ((result = PORT_Constructor(Upper_Left_Row_Position, Upper_Left_Column_Position, height, Port_Width, port_border_descriptor, (Text_Background_Color << 4) | Text_Foreground_Color, (Border_Background_Color << 4) | Border_Foreground_Color, &(port))) == PORT_NOERR) {



      result = PORT_Destructor(&(port));

   }

   return (result);

}

/* Function    : main
   Description : The main entry point to the REMINDER program.
   Inputs      : The command line.
   Updates     : Nothing.
   Outputs     : Nothing.
   Returns     : Always returns a value of zero.
   Modified    : 09/16/92 DWP Initial coding.
   Notes       :
*/

int main(int argc, char * argv[]) {

   FILE *        cfg_file;
   struct ffblk  ffblk;
   BOOLEAN       delete_cfg_files_flag, wait_for_keypress_flag, display_message_once_per_day_flag, switch_value, loading_text_flag;
   LIST          message_list;
   DATE_YYYYMMDD current_date, countdown_date;
   CARDINAL_16   equals_sign_position, upper_left_row_position, upper_left_column_position, port_width, text_foreground_color, text_background_color, border_foreground_color, border_background_color, border_type;
   char          cfg_files_dir[MAXDIR], cfg_files[MAXPATH], cfg_file_name[MAXPATH], cfg_file_line[81], variable_name[81], variable_value[81];
   char *        colors_list = "Black        Blue         Green        Cyan         Red          Magenta      Brown        LightGray    DarkGray     LightBlue    LightGreen   LightRed     LightMagenta Yellow       White";
   char *        numbers_list = "0123456789";
   int           i, colors_list_pos, more_files_indicator, result = 0;

   /* If no command line arguments were entered, display the help screen. */

   if (argc == 1) {

      result = 1;

   }
   else {

      current_date = *((DATE_YYYYMMDD *) DATE_Retrieve_System_Date(DATE_YYYYMMDD_TYPE, CARDINAL_32_TYPE, 0, &(current_date)));
      delete_cfg_files_flag = FALSE;
      wait_for_keypress_flag = FALSE;
      display_message_once_per_day_flag = FALSE;
      switch_value = FALSE;

      /* Traverse the command line. */

      for (i = 1; i < argc - 1; i++) {

         if (argv[i][0] != '/' && argv[i][0] != '-') {

            /* Search for and process all of the REMINDER information files in the specified directory. */

            sprintf(cfg_files_dir, "%.*s", sizeof(cfg_files_dir) - 1, argv[i]);

            sprintf(cfg_files, "%s\\*.RIF", cfg_files_dir);
            more_files_indicator = findfirst(STRING_Trim(STRING_TRIM_SPACE, cfg_files), &ffblk, 0);

            while (more_files_indicator == 0) {

               /* Open and load the next information file. */

               sprintf(cfg_file_name, "%s\\%s", cfg_files_dir, ffblk.ff_name);

               if ((cfg_file = fopen(STRING_Trim(STRING_TRIM_SPACE, cfg_file_name), "rt")) != NULL) {

                  LIST_Constructor(sizeof(cfg_file_line), (void **) &(message_list));
                  loading_text_flag = FALSE;
                  upper_left_row_position = 0;
                  upper_left_column_position = 0;
                  port_width = 0;
                  text_foreground_color = 0;
                  text_background_color = 0;
                  border_foreground_color = 0;
                  border_background_color = 0;
                  border_type = 0;
                  countdown_date = 0;

                  /* Get all of the lines in the current information file. */

                  while (fgets(cfg_file_line, sizeof(cfg_file_line), cfg_file) != NULL) {

                     STRING_ATrim(cfg_file_line);

                     /* Ignore all comment lines. */

                     if (cfg_file_line[0] != ';') {

                        /* Determine if the line is a parameter assignment line or a line containing information about the text
                           being displayed. */

                        equals_sign_position = STRING_CharPos(cfg_file_line, '=');

                        if (equals_sign_position == 0) {

                           if (stricmp(cfg_file_line, "Text_Begin") == 0) {

                              loading_text_flag = TRUE;

                           }
                           else {

                              if (stricmp(cfg_file_line, "Text_End") == 0) {

                                 loading_text_flag = FALSE;

                              }
                              else {

                                 /* Add a message line to the message line list if the 'Text_Begin' indicator has been
                                    encountered. */

                                 if (loading_text_flag) {

                                    LIST_Insert(cfg_file_line, LIST_LAST, message_list);

                                 }

                              }

                           }

                        }
                        else {

                           sprintf(variable_name, "%.*s", equals_sign_position - 1, cfg_file_line);
                           sprintf(variable_value, "%s", cfg_file_line + equals_sign_position + 1);

                           /* Set the upper left-hand corner screen coordinates and window length. */

                           if (stricmp(variable_name, "Screen_Coordinates") == 0) {

                              STRING_Trim(STRING_TRIM_SPACE, variable_value);
                              STRING_Trim(STRING_TRIM_ALPHA, variable_name);
                              sscanf(variable_name, "%u%u%u", &(upper_left_row_position), &(upper_left_column_position), &(port_width));

                           }

                           /* Set the text foreground color. */

                           if (stricmp(variable_name, "Text_Color") == 0) {

                              if (strcspn(variable_value, numbers_list) == 0) {

                                 text_foreground_color = atoi(variable_value);

                              }
                              else {

                                 if ((colors_list_pos = STRING_StrPos(colors_list, variable_value)) % 12 == 0) {

                                    text_foreground_color = colors_list_pos % 12;

                                 }

                              }

                           }

                           /* Set the text background color. */

                           if (stricmp(variable_name, "Text_Background") == 0) {

                              if (strcspn(variable_value, numbers_list) == 0) {

                                 text_background_color = atoi(variable_value);

                              }
                              else {

                                 if ((colors_list_pos = STRING_StrPos(colors_list, variable_value)) % 12 == 0) {

                                    text_background_color = colors_list_pos % 12;

                                 }

                              }

                           }

                           /* Set the border foreground color. */

                           if (stricmp(variable_name, "Border_Color") == 0) {

                              if (strcspn(variable_value, numbers_list) == 0) {

                                 border_foreground_color = atoi(variable_value);

                              }
                              else {

                                 if ((colors_list_pos = STRING_StrPos(colors_list, variable_value)) % 12 == 0) {

                                    border_foreground_color = colors_list_pos % 12;

                                 }

                              }

                           }

                           /* Set the border background color. */

                           if (stricmp(variable_name, "Border_Background") == 0) {

                              if (strcspn(variable_value, numbers_list) == 0) {

                                 border_background_color = atoi(variable_value);

                              }
                              else {

                                 if ((colors_list_pos = STRING_StrPos(colors_list, variable_value)) % 12 == 0) {

                                    border_background_color = colors_list_pos % 12;

                                 }

                              }

                           }

                           /* Set the border type. */

                           if (stricmp(variable_name, "Border_Type") == 0) {

                              if (stricmp(variable_value, "Double") == 0 || atoi(variable_value) == 2) {

                                 border_type = 2;

                              }

                              if (stricmp(variable_value, "Single") == 0 || atoi(variable_value) == 1) {

                                 border_type = 1;

                              }

                              if (stricmp(variable_value, "None") == 0 || atoi(variable_value) == 0) {

                                 border_type = 0;

                              }

                           }

                           /* Set the countdown date. */

                           if (stricmp(variable_name, "CountDown_Date") == 0) {

                              if (!DATE_Convert_To_YYYYMMDD(DATE_MMDDYYYY_TYPE, STRING_TYPE, variable_value, &(countdown_date))) {

                                 countdown_date = 0;

                              }

                           }

                        }

                     }

                  }

                  fclose(cfg_file);
                  result = REMINDER_Main(message_list, upper_left_row_position, upper_left_column_position, port_width, text_foreground_color, text_background_color, border_type, border_foreground_color, border_background_color, wait_for_keypress_flag, current_date, countdown_date);

                  if (delete_cfg_files_flag) {

                     unlink(cfg_file_name);

                  }

               }

               more_files_indicator = findnext(&ffblk);

            }

         }
         else {

            switch (argv[i][2]) {

               case '-' :

                  switch_value = FALSE;
                  break;

               case '+' :

                  switch_value = TRUE;

               default :

                  switch_value = FALSE;

            }

            switch (toupper(argv[i][1])) {

               case 'D' :

                  delete_cfg_files_flag = switch_value;
                  break;

               case 'S' :

                  wait_for_keypress_flag = switch_value;
                  break;

               case 'O' :

                  display_message_once_per_day_flag = switch_value;
                  break;

            }

         }

      }

   }

   if (result != 0) {

      printf("\nREMINDER V1.0, " COMPILE_DATE ", Copyright (C) " COMPILE_YEAR " by CSFX Computing Services\n\n");
      printf("%3sPurpose : Displays daily reminders on the screen.\n\n", "");
      printf("%3sUsage   : REMINDER {{[- | /][Switch][+ | -} [CfgFileDir]}\n\n", "");
      printf("%6sSwitches\n\n", "");
      printf("%9sD = Delete out of date configuration files (Default = Off)\n", "");
      printf("%9sS = Display a single message at a time (Default = Off)\n", "");
      printf("%9sO = Display messages only once per day (Default = Off)\n", "");
      printf("%9s+ = Turn switch on\n", "");
      printf("%9s- = Turn switch off\n\n", "");
      printf("%6sParameters\n\n", "");
      printf("%9sCfgFileDir = The location of the REMINDER information files (*.RIF).\n\n", "");
      printf("%3sProgram By :\n\n", "");
      printf("%3sCSFX Computing Services\n", "");
      printf("%3sxxxx Eastport Dr. #x\n", "");
      printf("%3sBloomington, IL  61704\n", "");
      printf("%3s(309) 663-xxxx\n", "");

   }

   return (0);

}
