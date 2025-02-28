/*

   File        : AAI3.C
   Module      : MISCELLANEOUS
   System      : AAI
   Description : Miscellaneous support procedures and functions for the AAI system.
   Modified    : 10/15/94 DWP Created.
   Notes       :

*/

#include <alloc.h>
#include <conio.h>
#include <ctype.h>
#include <dos.h>
#include <errno.h>
#include <mem.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <fcntl.h>
#include <io.h>
#include <sys\stat.h>

#include "\Dev\DOS\Lib\ASM\KB\kb.h"
#include "\Dev\DOS\Lib\C\String\string.h"

#include "aai.h"

/*

   Procedure   : aaiActivateProcess
   Description : Activates the specified process.
   Inputs      : parametersList = The parameters list to use while the AAI system is active.
                 process        = The process to activate.
   Updates     : Nothing.
   Outputs     : Nothing.
   Returns     : Nothing.
   Modified    : 08/18/92 DWP Initial coding.
   Notes       :

*/

void aaiActivateProcess(AaiParametersList * parametersList, AaiProcessTypes process) {

   parametersList->processDescriptor[process].processActiveFlag = TRUE;

}

/*

   Procedure   : aaiHaltProcess
   Description : De-activates the specified process.
   Inputs      : parametersList = The parameters list to use while the AAI system is active.
                 process        = The process to activate.
   Updates     : Nothing.
   Outputs     : Nothing.
   Returns     : Nothing.
   Modified    : 08/18/92 DWP Initial coding.
   Notes       :

*/

void aaiHaltProcess(AaiParametersList * parametersList, AaiProcessTypes process) {

   parametersList->processDescriptor[process].processActiveFlag = FALSE;

}

/*

   Function    : aaiValidateParameters
   Description : Determines if the two parameters reference valid memory locations.
   Inputs      : processParameters = The parameters list used by the calling process.
                 key               = The last key pressed.
   Updates     : Nothing.
   Outputs     : Nothing.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 08/18/92 DWP Initial coding.
   Notes       :

*/

int aaiValidateParameters(void ** processParameters, CARDINAL_16 * key) {

   int result;

   /*

      Validate the parameters.  Exit if either one is invalid.

   */

   if (processParameters == NULL || key == NULL) {

      result = EINVAL;

   }
   else {

      result = EZERO;

   }

   return (result);

}

/*

   Function    : aaiAllocateParametersList
   Description : Allocates the parameters list for the calling process.
   Inputs      : processParametersSize = The size of the new parameters list.
   Updates     : Nothing.
   Outputs     : processParameters     = The parameters list used by the calling process.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 08/18/92 DWP Initial coding.
   Notes       :

*/

int aaiAllocateParametersList(CARDINAL_16 processParametersSize, void ** processParameters) {

   int result;

   /*

      Initialize the process parameters list for this process.

   */

   if ((*(processParameters) = malloc(processParametersSize)) == NULL) {

      result = ENOMEM;

   }
   else {

      setmem(*(processParameters), processParametersSize, 0);
      result = EZERO;

   }

   return (result);

}

/*

   Procedure   : aaiDisplayTime
   Description : Displays the current time and date on the screen.
   Inputs      : Nothing.
   Updates     : processParameters = The parameters list used by this process.
                 key               = The last key that was pressed.
   Outputs     : Nothing.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 08/18/92 DWP Initial Coding.
   Notes       :

*/

int aaiDisplayTime(void ** processParameters, CARDINAL_16 * key) {

   AaiDisplayTimeParameters * parameters;
   time_t                     timer;
   struct tm *                currentTime;
   char                       outputString[256], amPmvalue;
   int                        result;

   /*

      Validate the parameters.  Exit if either one is invalid.

   */

   if (processParameters == NULL || key == NULL) {

      result = EINVAL;

   }
   else {

      /*

         Initialize the process parameters list for this process.

      */

      if (*(processParameters) == NULL) {

         if ((*(processParameters) = malloc(sizeof(*(parameters)))) == NULL) {

            result = ENOMEM;

         }
         else {

            setmem(*(processParameters), sizeof(*(parameters)), 0);
            result = EZERO;

         }

      }
      else {

         /*

           Perform the main function of this process.

         */

         parameters = *(processParameters);
         timer = time(NULL);
         currentTime = localtime(&timer);

	      /*

	         Toggle the blinking character between the hours and minutes fields of the displayed time.

	      */

         if (parameters->secondsValue != currentTime->tm_sec || parameters->separatorCharacter == '\0') {

            parameters->secondsValue = currentTime->tm_sec;
            parameters->separatorCharacter = (parameters->separatorCharacter == ':') ? ' ' : ':';

	         /*

	            Determine if it is before or after 12:00 PM, so that the 12 hour format can be displayed on the screen.

            */

            if (currentTime->tm_hour >= 13) {

               currentTime->tm_hour -= 12;
               amPmvalue = 'P';

            }
            else {

               if (currentTime->tm_hour == 0) {

                  currentTime->tm_hour = 12;

               }

               amPmvalue = 'A';

            }

            /*

	            Display the time on the screen.

	         */

            TEXT_Set_Text_Color(parameters->colors.primaryColor, parameters->text);
            window(1, 1, 80, 25);

            if (parameters->minutesValue == currentTime->tm_min) {

               TEXT_Set_Cursor_Position(parameters->row, parameters->column + 2, parameters->text);
               TEXT_Print_Character(parameters->separatorCharacter, parameters->text);

            }
            else {

               sprintf(outputString, "%2u%c%02u %cM  %02u/%02u/%02u", currentTime->tm_hour, parameters->separatorCharacter, currentTime->tm_min, amPmvalue, currentTime->tm_mon + 1, currentTime->tm_mday, currentTime->tm_year % 100);
               TEXT_Set_Cursor_Position(parameters->row, parameters->column, parameters->text);
               TEXT_Print_String(outputString, parameters->text);
               parameters->minutesValue = currentTime->tm_min;

            }

         }

         result = EZERO;

      }

   }

   return (result);

}

/*

   Function    : aaiLoadConfiguration
   Description : Loads the specified configuration file.
   Inputs      : configFileName    = The name of configuration file to load.
   Updates     : Nothing.
   Outputs     : defaultParameters = The default parameters list.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 08/18/92 DWP Initial coding.
   Notes       :

*/

int aaiLoadConfiguration(char * configFileName, AaiDefaultParameters * defaultParameters) {

   FILE * configFp;
   int    result;

   if (configFileName == NULL || defaultParameters == NULL) {

      result = EINVDAT;

   }
   else {

      /*

         Open the configuration file.  Continue only if no errors occurred.

      */

      if ((configFp = fopen(configFileName, "rb")) == NULL) {

          result = EACCES;

      }
      else {

	      /*

	         Load the configuration file into memory.

	      */

         if (fread(defaultParameters, sizeof(*(defaultParameters)), 1, configFp) != 1 || strcmp(defaultParameters->id, AAI_CONFIG_FILE_TITLE) != 0) {

            result = EINVDAT;

         }
         else {

            result = EZERO;

         }

         fclose(configFp);

      }

   }

   return (result);

}

/*

   Function    : aaiSaveConfiguration
   Description : Saves a configuration to disk.
   Inputs      : configFileName    = The file to write to.
                 defaultParameters = The configuration to save.
   Updates     : Nothing.
   Outputs     : Nothing.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 08/18/92 DWP Initial coding.
   Notes       :

*/

int aaiSaveConfiguration(char * configFileName, AaiDefaultParameters * defaultParameters) {

   FILE * configFp;
   int    result;

   if (configFileName == NULL || defaultParameters == NULL) {

      result = EINVDAT;

   }
   else {

      /*

        Open the configuration file.  Continue only if no errors occurred.

      */

      if ((configFp = fopen(configFileName, "wb")) == NULL) {

         result = EACCES;

      }
      else {

         strcpy(defaultParameters->id, AAI_CONFIG_FILE_TITLE);

         /*

	         Save the configuration file to disk.

	      */

         if (fwrite(defaultParameters, sizeof(*(defaultParameters)), 1, configFp) != 1) {

            result = EFAULT;

         }
         else {

            result = EZERO;

         }

         fclose(configFp);

      }

   }

   return (result);

}

/*

   Function    : aaiYesNoMenu
   Description : processes the Yes/No message used in various other processes.
   Inputs      : Nothing.
   Updates     : processParameters = The parameters list used by this process.
                 key               = The last key that was pressed.
   Outputs     : Nothing.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 08/18/92 DWP Initial coding.
   Notes       :

*/

int aaiYesNoMenu(void ** processParameters, CARDINAL_16 * key) {

   AaiYesNoMenuParameters * parameters;
   CARDINAL_16              portLength, position;
   BOOLEAN                  validKeyFlag, optionSelectedFlag, processAbortedFlag;
   int                      result;

   /*

      Validate the parameters.  Exit if either one is invalid.

   */

   if (processParameters == NULL || key == NULL) {

      result = EINVAL;

   }
   else {

      /*

         Initialize the process parameters list for this process.

      */

      if (*(processParameters) == NULL) {

         if ((*(processParameters) = malloc(sizeof(*(parameters)))) == NULL) {

            result = ENOMEM;

         }
         else {

            setmem(*(processParameters), sizeof(*(parameters)), 0);
            result = EZERO;

         }

      }
      else {

         parameters = *(processParameters);

         /*

	         Initialize the port and menu, if necessary.

	      */

         if (parameters->menu != NULL) {

            result = PORT_Activate(parameters->port);

         }
         else {

            portLength = strlen(parameters->displayMessage);

            if ((result = PORT_Constructor(parameters->startingRow, parameters->startingColumn, 7, portLength + 4, PORT_DOUBLE_LINE_BORDER, parameters->colors.primaryColor, parameters->colors.primaryColor, &(parameters->port))) == PORT_NOERR) {

	            /*

                  Display the 'Yes/No'menu.

	            */

               if ((result = MENU_Constructor(parameters->menuText, 4, (portLength - 3) / 2, parameters->colors.primaryColor, parameters->colors.secondaryColor, parameters->colors.primaryHighlightColor, parameters->colors.secondaryHighlightColor, NULL, 0, 0, BLACK, BLACK, parameters->text, &(parameters->menu))) == MENU_NOERR) {

                  TEXT_Set_Text_Color(parameters->colors.primaryColor, parameters->text);
                  TEXT_Set_Cursor_Position(2, 2, parameters->text);
                  TEXT_Print_String(parameters->displayMessage, parameters->text);
                  result = MENU_Display(parameters->menu, parameters->option);

               }

            }

         }

         /*

	         Continue only if no errors occurred above and a key was pressed.

	      */

         if (result == EZERO && *(key) != 0) {

            validKeyFlag = TRUE;
            optionSelectedFlag = FALSE;
            processAbortedFlag = FALSE;

            switch (*(key)) {

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

                  parameters->option = (parameters->option == 1) ? 2 : 1;
                  break;

	            /*

		            Move the cursor to the first option in the menu.

	            */

               case KB_HOME :
               case KB_GRAY_HOME :

                  parameters->option = 1;
                  break;

	            /*

		            Move the cursor to the last option in the menu.

	            */

               case KB_END :
               case KB_GRAY_END :

                  parameters->option = 2;
                  break;

	            /*

		            Select the currently highlighted option.

	            */

               case KB_ENTER :
               case KB_GRAY_ENTER :

                  *(parameters->yesSelectedFlag) = (parameters->option == 1) ? TRUE : FALSE;
                  optionSelectedFlag = TRUE;
                  break;

	            /*

		            Discontinue processing the menu.

	            */

               case KB_ESC :

                  processAbortedFlag = TRUE;
                  *(parameters->yesSelectedFlag) = FALSE;

                  break;

               default :

		            /*

		               Determine if one of the menu hot-keys was pressed.

		            */

                  if ((position = STRING_CharPos(parameters->menuKeysList, (char) toupper((*(key) % 256)))) == 0) {

                     validKeyFlag = FALSE;

                  }
                  else {

                     parameters->option = position;

                     if (position == 1) {

                        *(parameters->yesSelectedFlag) = (parameters->option == 1) ? TRUE : FALSE;

                     }

                     optionSelectedFlag = TRUE;

                  }

            }

	         /*

	            Update or remove the menu if a valid key was pressed.

	         */

            if (validKeyFlag) {

               *(key) = 0;

               if (!processAbortedFlag && !optionSelectedFlag) {

                  result = MENU_Display(parameters->menu, parameters->option);

               }
               else {

		            /*

		               Remove the menu and port.

		            */

                  if ((result = MENU_Destructor(&(parameters->menu))) == MENU_NOERR) {

                     aaiActivateProcess(parameters->parametersList, parameters->invokingProcess);
                     aaiHaltProcess(parameters->parametersList, AaiYesNoMenuProcess);
                     result = PORT_Destructor(&(parameters->port));

                  }

               }

            }

         }

      }

   }

   return (result);

}

/*

   Function    : aaiInput
   Description : Allows information to be entered via the keyboard.
   Inputs      :
   Updates     :
   Outputs     :
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 08/18/92 DWP Initial coding.
   Notes       :

*/

int aaiInput(AaiInputDescriptor * input, CARDINAL_16 * key) {

   CARDINAL_16 currentColor, cursorColor;
   struct time currTime;
   char        str[100];
   int         result;

   if (input == NULL) {

      result = EINVAL;

   }
   else {

      result = EZERO;

      if (input->refreshFlag) {

         TEXT_Retrieve_Text_Color(input->text, &currentColor);
         TEXT_Set_Text_Color((input->markedFlag) ? input->colors.secondaryHighlightColor : input->colors.primaryHighlightColor, input->text);
         TEXT_Set_Cursor_Position(input->currentRow, input->currentColumn, input->text);
         sprintf(str, "%-*.*s", input->displayLength, input->displayLength, ((input->type == STRING_TYPE) || (input->type == INTEGER_16_TYPE && atoi(input->value) != 0)) ? input->value : "");
         TEXT_Print_String(str, input->text);
	      TEXT_Set_Text_Color(currentColor, input->text);
         TEXT_Set_Cursor_Position(input->currentRow, input->currentColumn + input->currentOffset, input->text);
         input->displayCursorFlag = TRUE;
         input->colorIndicatorFlag = FALSE;
         input->refreshFlag = FALSE;

      }
      else {

         if ((input->previousOffset != input->currentOffset) || input->displayCursorFlag) {

            TEXT_Retrieve_Text_Color(input->text, &currentColor);

            TEXT_Set_Text_Color(input->colors.primaryHighlightColor, input->text);
            TEXT_Set_Cursor_Position(input->currentRow, input->currentColumn + input->previousOffset, input->text);
            TEXT_Print_Character(input->value[input->previousOffset], input->text);

            cursorColor = ((input->colors.primaryHighlightColor << 4) | (input->colors.primaryHighlightColor >> 4)) & 0x0ff;
            TEXT_Set_Text_Color(cursorColor, input->text);
            TEXT_Set_Cursor_Position(input->currentRow, input->currentColumn + input->currentOffset, input->text);
            TEXT_Print_Character(input->value[input->currentOffset], input->text);

            TEXT_Set_Text_Color(currentColor, input->text);
            input->previousOffset = input->currentOffset;
            input->displayCursorFlag = FALSE;

         }

         gettime(&(currTime));

         if (currTime.ti_hund > 50) {

            TEXT_Retrieve_Text_Color(input->text, &currentColor);

            cursorColor = (input->colorIndicatorFlag) ? ((input->colors.primaryHighlightColor << 4) | (input->colors.primaryHighlightColor >> 4)) & 0x0ff : input->colors.primaryHighlightColor;
            input->colorIndicatorFlag = !input->colorIndicatorFlag;
            TEXT_Set_Text_Color(cursorColor, input->text);
            TEXT_Set_Cursor_Position(input->currentRow, input->currentColumn + input->previousOffset, input->text);
            TEXT_Print_Character(input->value[input->currentOffset], input->text);

         }

         switch (*(key)) {

            case 0 :

               break;

            case KB_BACKSPACE :

               if (input->currentOffset > 0) {

                  input->currentOffset--;
                  memmove(&(input->value[input->currentOffset]), &(input->value[input->currentOffset + 1]), input->editLength - input->currentOffset);
                  input->refreshFlag = TRUE;

               }

               *(key) = 0;
               break;

            case KB_DEL :
	         case KB_GRAY_DEL :

	            memmove(&(input->value[input->currentOffset]), &(input->value[input->currentOffset + 1]), input->editLength - input->currentOffset);
	            input->refreshFlag = TRUE;
	            *(key) = 0;
	            break;

            default :

               if (input->type == STRING_TYPE) {

                  if ((char) *(key) >= ' ' && (char) *(key) <= '~' && input->currentOffset < input->editLength) {

                     input->value[input->currentOffset] = (char) *(key);
                     TEXT_Set_Cursor_Position(input->currentRow, input->currentColumn + input->currentOffset, input->text);
                     input->currentOffset += (input->currentOffset < input->editLength - 1) ? 1 : 0;
                     TEXT_Print_Character((char) *(key), input->text);
                     *(key) = 0;

                  }

               }
               else {

                  if ((((char) *(key) >= '0' && (char) *(key) <= '9') || (char) *(key) == '+' || (char) *(key) == '-') && input->currentOffset < input->editLength) {

                     input->value[input->currentOffset] = (char) *(key);
                     TEXT_Set_Cursor_Position(input->currentRow, input->currentColumn + input->currentOffset, input->text);
                     input->currentOffset += (input->currentOffset < input->editLength - 1) ? 1 : 0;
                     TEXT_Print_Character((char) *(key), input->text);
                     *(key) = 0;

                     if (input->firstPassFlag) {

                        setmem(&(input->value[1]), sizeof(input->value) - 1, '\0');
                        input->firstPassFlag = FALSE;
                        input->refreshFlag = TRUE;

                     }

                  }

               }

               if (input->currentOffset + 1 == input->editLength) {

                  input->displayCursorFlag = TRUE;

               }

         }

      }

   }

   return (result);

}

/*

   Procedure   : aaiSetHelpScreen
   Description :
   Inputs      : processParameters =
                 key               =
   Updates     : Nothing.
   Outputs     : Nothing.
   Returns     : Nothing.
   Modified    : 08/18/92 DWP Initial coding.
   Notes       :

*/

void aaiSetHelpScreen(AaiParametersList * processParameters, char * key) {

   AaiHelpTopicParameters * helpTopicParameters;

   helpTopicParameters = processParameters->processDescriptor[AaiHelpTopicProcess].processParameters;
   helpTopicParameters->key = key;

}
