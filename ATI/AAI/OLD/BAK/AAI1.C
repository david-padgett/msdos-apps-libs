/*

   File        : AAI1.C
   Module      : MAIN
   System      : AAI
   Description : The main module for the AAI program.
   Modified    : 10/08/94 DWP Created.
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
#include "\Dev\DOS\Lib\C\text_Int\text_int.h"

#include "aai.h"

/*

   Procedure   : aaiInitializeParametersList
   Description : Initializes a parameters list.
   Inputs      : parametersList =
   Updates     : Nothing.
   Outputs     : Nothing.
   Returns     : Nothing.
   Modified    : 10/08/94 DWP Initial coding.
   Notes       :

*/

void aaiInitializeParametersList(AaiParametersList * parametersList) {

   strcpy(parametersList->defaultParameters.id, AAI_CONFIG_FILE_TITLE);

   if (parametersList->displayType != parametersList->defaultParameters.displayType) {

      if (parametersList->displayTypeSpecified) {

         parametersList->defaultParameters.displayType = parametersList->displayType;

      }
      else {

         parametersList->displayType = parametersList->defaultParameters.displayType;

      }

   }

   parametersList->defaultParameters.functionKeyMenuColors.primaryColor = (parametersList->displayType == AaiColor) ? (LIGHTGRAY << 4) | BLACK : (LIGHTGRAY << 4) | BLACK;
   parametersList->defaultParameters.functionKeyMenuColors.secondaryColor = (parametersList->displayType == AaiColor) ? (LIGHTGRAY << 4) | RED : (LIGHTGRAY << 4) | BLACK;
   parametersList->defaultParameters.functionKeyMenuColors.primaryHighlightColor = (parametersList->displayType == AaiColor) ? (BLUE << 4) | WHITE : (BLACK << 4) | LIGHTGRAY;
   parametersList->defaultParameters.functionKeyMenuColors.secondaryHighlightColor = (parametersList->displayType == AaiColor) ? (BLUE << 4) | WHITE : (BLACK << 4) | DARKGRAY;

   parametersList->defaultParameters.mainMenuColors.primaryColor = (parametersList->displayType == AaiColor) ? (LIGHTGRAY << 4) | BLACK : (LIGHTGRAY << 4) | BLACK;
   parametersList->defaultParameters.mainMenuColors.secondaryColor = (parametersList->displayType == AaiColor) ? (LIGHTGRAY << 4) | RED : (LIGHTGRAY << 4) | BLACK;
   parametersList->defaultParameters.mainMenuColors.primaryHighlightColor = (parametersList->displayType == AaiColor) ? (GREEN << 4) | BLACK : (BLACK << 4) | LIGHTGRAY;
   parametersList->defaultParameters.mainMenuColors.secondaryHighlightColor = (parametersList->displayType == AaiColor) ? (GREEN << 4) | RED : (BLACK << 4) | DARKGRAY;

   parametersList->defaultParameters.subMenuColors.primaryColor = (parametersList->displayType == AaiColor) ? (LIGHTGRAY << 4) | BLACK : (LIGHTGRAY << 4) | BLACK;
   parametersList->defaultParameters.subMenuColors.secondaryColor = (parametersList->displayType == AaiColor) ? (LIGHTGRAY << 4) | RED : (LIGHTGRAY << 4) | BLACK;
   parametersList->defaultParameters.subMenuColors.primaryHighlightColor = (parametersList->displayType == AaiColor) ? (GREEN << 4) | BLACK : (BLACK << 4) | LIGHTGRAY;
   parametersList->defaultParameters.subMenuColors.secondaryHighlightColor = (parametersList->displayType == AaiColor) ? (GREEN << 4) | RED : (BLACK << 4) | DARKGRAY;

   parametersList->defaultParameters.yesNoMenuColors.primaryColor = (parametersList->displayType == AaiColor) ? (LIGHTGRAY << 4) | BLACK : (LIGHTGRAY << 4) | BLACK;
   parametersList->defaultParameters.yesNoMenuColors.secondaryColor = (parametersList->displayType == AaiColor) ? (LIGHTGRAY << 4) | RED : (LIGHTGRAY << 4) | BLACK;
   parametersList->defaultParameters.yesNoMenuColors.primaryHighlightColor = (parametersList->displayType == AaiColor) ? (GREEN << 4) | BLACK : (BLACK << 4) | LIGHTGRAY;
   parametersList->defaultParameters.yesNoMenuColors.secondaryHighlightColor = (parametersList->displayType == AaiColor) ? (GREEN << 4) | RED : (BLACK << 4) | DARKGRAY;

   parametersList->defaultParameters.editColors.primaryColor = (parametersList->displayType == AaiColor) ? (LIGHTGRAY << 4) | BLACK : (LIGHTGRAY << 4) | BLACK;
   parametersList->defaultParameters.editColors.secondaryColor = (parametersList->displayType == AaiColor) ? (LIGHTGRAY << 4) | RED : (LIGHTGRAY << 4) | BLACK;
   parametersList->defaultParameters.editColors.primaryHighlightColor = (parametersList->displayType == AaiColor) ? (GREEN << 4) | BLACK : (BLACK << 4) | LIGHTGRAY;
   parametersList->defaultParameters.editColors.secondaryHighlightColor = (parametersList->displayType == AaiColor) ? (GREEN << 4) | RED : (BLACK << 4) | DARKGRAY;

}

/*

   Procedure   : aaiDisplayMainScreenText
   Description : Displays the main title screen text.
   Inputs      : parametersList = A record of configuration information.
                 mainScreenText = The text to display.
                 characterList  = A list of the unique characters in mainScreenText.
                 attributeList  = A one-to-one mapping of attributes to characters.  Each byte of this list corresponds to the
                                  character which occupies the same position in characterList.  The characters in
                                  characterList will be displayed using the attributes found in attributeList.
                 text           = The text object to use when printing characters to the screen.
   Updates     : Nothing.
   Outputs     : Nothing.
   Returns     : Nothing.
   Modified    : 08/18/92 DWP Initial coding.
   Notes       :

*/

void aaiDisplayMainScreenText(char * mainScreenText, char * characterList, BYTE * attributeList, TEXT text) {

   size_t characterPosition;
   int    i;
   char   character;

   /*

      Loop until the entire screen has been displayed.

   */

   for (i = 0; (character = mainScreenText[i]) != '\0'; i++) {

      characterPosition = STRING_CharPos(characterList, character);
      TEXT_Set_Text_Color((characterPosition == 0) ? BLACK : (int) attributeList[characterPosition - 1], text);
      TEXT_Print_Character(character, text);

   }

}

/*

   Procedure   : aaiDisplayMainScreen
   Description : Displays the main title screen.
   Inputs      : parametersList = A record of configuration information.
   Updates     : Nothing.
   Outputs     : Nothing.
   Returns     : Nothing.
   Modified    : 08/18/92 DWP Initial coding.
   Notes       :

*/

void aaiDisplayMainScreen(AaiParametersList * parametersList) {

   TEXT_Set_Text_Color(LIGHTGRAY, parametersList->text);
   TEXT_Clear_Text_Window(parametersList->text);
   TEXT_Set_Text_Color(parametersList->defaultParameters.mainMenuColors.primaryColor, parametersList->text);
   BGI_ClrEol(NULL);

   TEXT_Set_Cursor_Position(2, 1, parametersList->text);
   aaiDisplayMainScreenText(parametersList->mainScreenText, parametersList->mainScreenCharacters, parametersList->mainScreenCharacterColors, parametersList->text);

   TEXT_Set_Cursor_Position(25, 1, parametersList->text);
   TEXT_Set_Text_Color(parametersList->defaultParameters.functionKeyMenuColors.primaryColor, parametersList->text);
   BGI_ClrEol(NULL);
   TEXT_Set_Cursor_Position(25, 1, parametersList->text);

}

/*

   Function    : aaiSubMenu
   Description : processes events that occur while a sub-menu is active.
   Inputs      : Nothing.
   Updates     : processParameters = The parameters list used by this process.
                 key               = The last key pressed.
   Outputs     : Nothing.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 08/18/92 DWP Initial coding.

   Notes       :

*/

int aaiSubMenu(void ** processParameters, CARDINAL_16 * key) {

   AaiSubMenuParameters * parameters;
   AaiMenuTypes           i;
   AaiProcessTypes        absoluteProcess;
   CARDINAL_16            position;
   BOOLEAN                validKeyFlag, processAbortedFlag, processSelectedFlag;
   int                    result;

   /*

      Validate the parameters.  Exit if either one is invalid.

   */

   if ((result = aaiValidateParameters(processParameters, key)) == EZERO) {

      /*

         Initialize the process parameters list for this process.

      */

      if (*(processParameters) == NULL) {

         result = aaiAllocateParametersList(sizeof(*(parameters)), processParameters);

      }
      else {

         /*

            Perform the main function of this process.

         */

         parameters = *(processParameters);
         aaiSetHelpScreen(parameters->parametersList, AaiHelpIndexKeyList[((AaiMainMenuParameters *) parameters->parametersList->processDescriptor[AaiMainMenuProcess].processParameters)->option - 1 + AaiHelpFileM]);

         /*

            Initialize and display the sub-menu, if necessary.

         */

         if (!parameters->refreshFlag) {

            result = PORT_Activate(parameters->port);

         }
         else {

            if (parameters->menu == NULL) {

               result = EZERO;

            }
            else {

               if ((result = MENU_Destructor(&(parameters->menu))) == MENU_NOERR) {

                  result = PORT_Destructor(&(parameters->port));

               }

            }

            if (result == 0 && (result = PORT_Constructor(parameters->startingRow, parameters->startingColumn, parameters->height, parameters->width, PORT_SINGLE_LINE_BORDER, parameters->colors.primaryColor, parameters->colors.primaryColor, &(parameters->port))) == PORT_NOERR) {

               if ((result = MENU_Constructor(parameters->menuText, 1, 2, parameters->colors.primaryColor, parameters->colors.secondaryColor, parameters->colors.primaryHighlightColor, parameters->colors.secondaryHighlightColor, NULL, 0, 0, 0, 0, parameters->text, &(parameters->menu))) == MENU_NOERR) {

                  result = MENU_Display(parameters->menu, parameters->option);

               }

            }

            parameters->refreshFlag = FALSE;

         }

         /*

            Continue only if no errors occurred during initialization and a key was pressed.

         */

         if (result == EZERO && *(key) != 0) {

            validKeyFlag = TRUE;
            processSelectedFlag = FALSE;
            processAbortedFlag = FALSE;

            switch (*(key)) {

               /*

                  Move the cursor up one line.

               */

               case KB_UP :
               case KB_GRAY_UP :

                  parameters->option = (parameters->option > 1) ? parameters->option - 1 : parameters->totalOptions;
                  break;

               /*

                  Move the cursor down one line.

               */

               case KB_DOWN :
               case KB_GRAY_DOWN :

                  parameters->option = (parameters->option < parameters->totalOptions) ? parameters->option + 1 : 1;
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

                  parameters->option = parameters->totalOptions;
                  break;

               /*

                  Select and activate the currently highlighted option.

               */

               case KB_ENTER :
               case KB_GRAY_ENTER :

                  processSelectedFlag = TRUE;
                  break;

               /*

                  Close the sub-menu.

               */

               case KB_ESC :

                  processAbortedFlag = TRUE;
                  break;

               default :

                  /*

                     Determine if an option was activated via its hot-key.  If so, activate that option.

                  */

                  if ((position = STRING_CharPos(parameters->menuKeysList, toupper((char) (*(key) % 256)))) > 0) {

                     parameters->option = position;
                     processSelectedFlag = TRUE;

                  }
                  else {

                     validKeyFlag = FALSE;

                  }

            }

            /*

               Update the position of the cursor if a valid event occurred.

            */

            if (validKeyFlag) {

               *(key) = 0;
               result = MENU_Display(parameters->menu, parameters->option);
               parameters->parametersList->menuCharacteristicsList[((AaiMainMenuParameters *) parameters->parametersList->processDescriptor[AaiMainMenuProcess].processParameters)->option - 1 + AaiFileMenu].option = parameters->option;

            }

            /*

               Hide the sub-menu, if necessary.

            */

            if (processAbortedFlag || processSelectedFlag) {

               if ((result = MENU_Destructor(&(parameters->menu))) == MENU_NOERR) {

                  aaiHaltProcess(parameters->parametersList, AaiSubMenuProcess);
                  result = PORT_Destructor(&(parameters->port));

               }

               if (processSelectedFlag) {

                  aaiHaltProcess(parameters->parametersList, AaiMainMenuProcess);

                  for (i = 1, absoluteProcess = parameters->option; i < ((AaiMainMenuParameters *) (parameters->parametersList->processDescriptor[AaiMainMenuProcess].processParameters))->option; i++) {

                     absoluteProcess += strlen(AaiMenuKeysList[AaiFileMenu + i - 1]);

                  }

                  aaiActivateProcess(parameters->parametersList, absoluteProcess);

               }

               parameters->parametersList->menuCharacteristicsList[((AaiMainMenuParameters *) parameters->parametersList->processDescriptor[AaiMainMenuProcess].processParameters)->option - 1 + AaiFileMenu].option = parameters->option;

            }

         }

      }

   }

   return (result);

}

/*

   Function    : aaiMainMenu
   Description : processes events that occur while the main menu is active.
   Inputs      : Nothing.
   Updates     : processParameters = The parameters list used by this process.
                 key               = The last key pressed.
   Outputs     : Nothing.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 08/18/92 DWP Initial coding.
   Notes       :

*/

int aaiMainMenu(void ** processParameters, CARDINAL_16 * key) {

   AaiMainMenuParameters * parameters;
   CARDINAL_16             position;
   BOOLEAN                 validKeyFlag, optionSelectedFlag;
   int                     result;

   /*

      Validate the parameters.  Exit if either one is invalid.

   */

   if ((result = aaiValidateParameters(processParameters, key)) == EZERO) {

      /*

         Initialize the process parameters list for this process.

      */

      if (*(processParameters) == NULL) {

         result = aaiAllocateParametersList(sizeof(*(parameters)), processParameters);

      }
      else {

         /*

            Perform the main function of this process.

         */

         parameters = *(processParameters);

         if (!parameters->parametersList->processDescriptor[AaiSubMenuProcess].processActiveFlag && !parameters->parametersList->processDescriptor[AaiYesNoMenuProcess].processActiveFlag) {

            aaiSetHelpScreen(parameters->parametersList, AaiHelpIndexKeyList[AaiHelpMainM]);

         }

         if (parameters->menu != NULL) {

            result = (parameters->exitFlag) ? -1 : EZERO;

         }
         else {

            window(1, 1, 80, 25);

            if ((result = MENU_Constructor(parameters->menuText, parameters->startingRow, parameters->startingColumn, parameters->colors.primaryColor, parameters->colors.secondaryColor, parameters->colors.primaryHighlightColor, parameters->colors.secondaryHighlightColor, NULL, 0, 0, BLACK, BLACK, parameters->text, &(parameters->menu))) == MENU_NOERR) {

               result = MENU_Display(parameters->menu, parameters->option);

            }

         }

         /*

            Continue processing only if no errors occurred during initialization and a key was pressed.

         */

         if (result == EZERO && *(key) != 0) {

            window(1, 1, 80, 25);
            validKeyFlag = TRUE;
            optionSelectedFlag = FALSE;

            switch (*(key)) {

               /*

                  Move the cursor to the left.

               */

               case KB_LEFT :
               case KB_GRAY_LEFT :
               case KB_SHIFT_TAB :

                  parameters->option = (parameters->option > 1) ? parameters->option - 1 : parameters->totalOptions;

                  if (parameters->parametersList->processDescriptor[AaiSubMenuProcess].processActiveFlag) {

                     optionSelectedFlag = TRUE;

                  }

                  break;

               /*

                  Move the cursor to the right.

               */

               case KB_RIGHT :
               case KB_GRAY_RIGHT :
               case KB_TAB :

                  parameters->option = (parameters->option < parameters->totalOptions) ? parameters->option + 1 : 1;

                  if (parameters->parametersList->processDescriptor[AaiSubMenuProcess].processActiveFlag) {

                     optionSelectedFlag = TRUE;

                  }

                  break;

               /* 

                  Move the cursor to the first menu option.

               */

               case KB_HOME :
               case KB_GRAY_HOME :

                  parameters->option = 1;
                  break;

               /*

                  Move the cursor to the last menu option.

               */

               case KB_END :
               case KB_GRAY_END :

                  parameters->option = parameters->totalOptions;
                  break;

               /*

                  Select the currently highlighted option.

               */

               case KB_ENTER :
               case KB_GRAY_ENTER :
               case KB_DOWN :
               case KB_GRAY_DOWN :

                  optionSelectedFlag = TRUE;
                  break;

               default :

                  /*

                     Determine if an option was activated via its hot-key.  If so, activate that option.

                  */

                  if ((position = STRING_CharPos(parameters->menuKeysList, toupper((char) (*(key) % 256)))) > 0) {

                     parameters->option = position;

                  }
                  else {

                     validKeyFlag = FALSE;

                  }

            }

            /*

               Update the position of the cursor if a valid event occurred.

            */

            if (validKeyFlag) {

               result = MENU_Display(parameters->menu, parameters->option);
               *(key) = 0;

               if (optionSelectedFlag) {

                  aaiActivateProcess(parameters->parametersList, AaiSubMenuProcess);
                  ((AaiSubMenuParameters *) parameters->parametersList->processDescriptor[AaiSubMenuProcess].processParameters)->menuText = parameters->parametersList->menuTextList[parameters->option - 1 + AaiFileMenu];
                  ((AaiSubMenuParameters *) parameters->parametersList->processDescriptor[AaiSubMenuProcess].processParameters)->menuKeysList = parameters->parametersList->menuKeysList[parameters->option - 1 + AaiFileMenu];
                  ((AaiSubMenuParameters *) parameters->parametersList->processDescriptor[AaiSubMenuProcess].processParameters)->startingRow = parameters->parametersList->menuCharacteristicsList[parameters->option - 1 + AaiFileMenu].startingRow;
                  ((AaiSubMenuParameters *) parameters->parametersList->processDescriptor[AaiSubMenuProcess].processParameters)->startingColumn = parameters->parametersList->menuCharacteristicsList[parameters->option - 1 + AaiFileMenu].startingColumn;
                  ((AaiSubMenuParameters *) parameters->parametersList->processDescriptor[AaiSubMenuProcess].processParameters)->height = parameters->parametersList->menuCharacteristicsList[parameters->option - 1 + AaiFileMenu].height;
                  ((AaiSubMenuParameters *) parameters->parametersList->processDescriptor[AaiSubMenuProcess].processParameters)->width = parameters->parametersList->menuCharacteristicsList[parameters->option - 1 + AaiFileMenu].width;
                  ((AaiSubMenuParameters *) parameters->parametersList->processDescriptor[AaiSubMenuProcess].processParameters)->option = parameters->parametersList->menuCharacteristicsList[parameters->option - 1 + AaiFileMenu].option;
                  ((AaiSubMenuParameters *) parameters->parametersList->processDescriptor[AaiSubMenuProcess].processParameters)->totalOptions = parameters->parametersList->menuCharacteristicsList[parameters->option - 1 + AaiFileMenu].totalOptions;
                  ((AaiSubMenuParameters *) parameters->parametersList->processDescriptor[AaiSubMenuProcess].processParameters)->refreshFlag = TRUE;

               }

            }

         }

      }

   }

   return (result);

}

/*

   Function    : aaiFunctionKeyMenu
   Description : processes events that occur while the function key menu is active.
   Inputs      : Nothing.
   Updates     : processParameters = The parameters list used by this process.
                 key               = The last key pressed.
   Outputs     : Nothing.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 08/18/92 DWP Initial coding.
   Notes       :

*/

int aaiFunctionKeyMenu(void ** processParameters, CARDINAL_16 * key) {

   AaiFunctionKeyMenuParameters * parameters;
   BOOLEAN                        validKeyFlag, invokeprocessFlag;
   int                            i, result;

   /*

      Validate the parameters.  Exit if either one is invalid.

   */

   if ((result = aaiValidateParameters(processParameters, key)) == EZERO) {

      /*

         Initialize the process parameters list for this process.

      */

      if (*(processParameters) == NULL) {

         result = aaiAllocateParametersList(sizeof(*(parameters)), processParameters);

      }
      else {

         /*

            Perform the main function of this process.

         */

         parameters = *(processParameters);

         if (parameters->menu != NULL) {

            result = EZERO;

         }
         else {

            if ((result = MENU_Constructor(parameters->menuText, parameters->startingRow, parameters->startingColumn, parameters->colors.primaryColor, parameters->colors.secondaryColor, parameters->colors.primaryHighlightColor, parameters->colors.secondaryHighlightColor, NULL, 0, 0, BLACK, BLACK, parameters->text, &(parameters->menu))) == MENU_NOERR) {

               /*

                  Display the function keys menu.  Continue only if no errors occurred.

               */

               result = MENU_Display(parameters->menu, 0);

            }

         }

         /*

            Continue only if no errors occurred above and a key was pressed.

         */

         if (result == EZERO && *(key) != 0) {

            window(1, 1, 80, 25);
            validKeyFlag = TRUE;

            /*

               Determine if any of the active function keys options were activated.

            */

            switch (*(key)) {

               case KB_F1 :

                  aaiActivateProcess(parameters->parametersList, AaiHelpTopicProcess);
                  break;

               case KB_F2 :

                  for (invokeprocessFlag = TRUE, i = AaiFileLoadProcess; i <= AaiSubMenuProcess; i++) {

                     if (parameters->parametersList->processDescriptor[i].processActiveFlag) {

                        invokeprocessFlag = FALSE;

                     }

                  }

                  if (invokeprocessFlag) {

                     aaiActivateProcess(parameters->parametersList, AaiFileLoadProcess);
                     aaiHaltProcess(parameters->parametersList, AaiMainMenuProcess);

                  }

                  break;

               case KB_F3 :

                  for (invokeprocessFlag = TRUE, i = AaiFileLoadProcess; i <= AaiSubMenuProcess; i++) {

                     if (parameters->parametersList->processDescriptor[i].processActiveFlag) {

                        invokeprocessFlag = FALSE;

                     }

                  }

                  if (invokeprocessFlag) {

                     aaiActivateProcess(parameters->parametersList, AaiFileSaveProcess);
                     aaiHaltProcess(parameters->parametersList, AaiMainMenuProcess);

                  }

                  break;

               case KB_F8 :

                  for (invokeprocessFlag = TRUE, i = AaiFileLoadProcess; i <= AaiSubMenuProcess; i++) {

                     if (parameters->parametersList->processDescriptor[i].processActiveFlag) {

                        invokeprocessFlag = FALSE;

                     }

                  }

                  if (invokeprocessFlag) {

                     aaiHaltProcess(parameters->parametersList, AaiMainMenuProcess);

                  }

                  break;

               case KB_F9 :

                  for (invokeprocessFlag = TRUE, i = AaiFileLoadProcess; i <= AaiSubMenuProcess; i++) {

                     if (parameters->parametersList->processDescriptor[i].processActiveFlag) {

                        invokeprocessFlag = FALSE;

                     }

                  }

                  if (invokeprocessFlag) {

                     aaiHaltProcess(parameters->parametersList, AaiMainMenuProcess);

                  }

                  break;

               case KB_F10 :

                  for (invokeprocessFlag = TRUE, i = AaiFileLoadProcess; i <= AaiSubMenuProcess; i++) {

                     if (parameters->parametersList->processDescriptor[i].processActiveFlag) {

                        invokeprocessFlag = FALSE;

                     }

                  }

                  if (invokeprocessFlag) {

                     aaiHaltProcess(parameters->parametersList, AaiMainMenuProcess);

                  }

                  break;

               case KB_ESC :

                  aaiActivateProcess(parameters->parametersList, AaiFileQuitProcess);
                  break;

               default :

                  validKeyFlag = FALSE;

            }

            if (validKeyFlag) {

               *(key) = 0;

            }

         }

      }

   }

   return (result);

}

/*

   Function    : aaiInitialize
   Description : Initializes the AAI system.
   Inputs      : Nothing.
   Updates     : Nothing.
   Outputs     : parametersList = The parameters list to use while the AAI system is active.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    :
   Notes       :

*/

int aaiInitialize(AaiParametersList * parametersList) {

   AaiProcessDescriptor *                   processDescriptor;
   AaiProcessTypes                          processNumber;
   AaiDisplayTimeParameters *               displayTimeParameters;
   AaiFileLoadParameters *                  fileLoadParameters;
   AaiFileNewParameters *                   fileNewParameters;
   AaiFileSaveParameters *                  fileSaveParameters;
   AaiFileSaveAsParameters *                fileSaveAsParameters;
   AaiFileDeleteParameters *                fileDeleteParameters;
   AaiFileRenameParameters *                fileRenameParameters;
   AaiFileQuitParameters *                  fileQuitParameters;
   AaiMeasureMeasureParameters *            measureMeasureParameters;
   AaiMeasurePurgeParameters *              measurePurgeParameters;
   AaiMeasureZeroSetParameters *            measureZeroSetParameters;
   AaiMeasureSampleNrParameters *           measureSampleNrParameters;
   AaiMeasureBatchParameters *              measureBatchParameters;
   AaiMeasureLabelParameters *              measureLabelParameters;
   AaiProductParameters *                   productParameters;
   AaiCalibrateEditMeasureParameters *      calibrateEditMeasureParameters;
   AaiCalibrateZeroSetParameters *          calibrateZeroSetParameters;
   AaiCalibrateCrossCalibrationParameters * calibrateCrossCalibrationParameters;
   AaiCalibratePilotSamplesParameters *     calibratePilotSamplesParameters;
   AaiCalibrateBiasAndSlopeParameters *     calibrateBiasAndScopeParameters;
   AaiCalibrateViewCalibrationParameters *  calibrateViewCalibrationParameters;
   AaiCalibrateMineralBiasParameters *      calibrateMineralBiasParameters;
   AaiCalibrateStatisticsParameters *       calibrateStatisticsParameters;
   AaiCalibrateGraphicsParameters *         calibrateGraphicsParameters;
   AaiCalibrateCarryOverParameters *        calibrateCarryOverParameters;
   AaiCalibratePolynomialParameters *       calibratePolynomialParameters;
   AaiSetupPrinterParameters *              setupPrinterParameters;
   AaiSetupOutputParameters *               setupOutputParameters;
   AaiSetupTemperatureParameters *          setupTemperatureParameters;
   AaiSetupHeaderParameters *               setupHeaderParameters;
   AaiSetupFooterParameters *               setupFooterParameters;
   AaiSetup1stSerialPortParameters *        setup1stSerialPortParameters;
   AaiSetup2ndSerialPortParameters *        setup2ndSerialPortParameters;
   AaiSetupBarcodeReaderParameters *        setupBarcodeReaderParameters;
   AaiSetupCyclesParameters *               setupCyclesParameters;
   AaiSetupPressureLimitParameters *        setupPressureLimitParameters;
   AaiSetupChopperSpeedParameters *         setupChopperSpeedParameters;
   AaiHelpIndexParameters *                 helpIndexParameters;
   AaiHelpAboutParameters *                 helpAboutParameters;
   AaiHelpPrintParameters *                 helpPrintParameters;
   AaiHelpTopicParameters *                 helpTopicParameters;
   AaiYesNoMenuParameters *                 yesNoMenuParameters;
   AaiSubMenuParameters *                   subMenuParameters;
   AaiMainMenuParameters *                  mainMenuParameters;
   AaiFunctionKeyMenuParameters *           functionKeyMenuParameters;
   CARDINAL_16                              key = 0;
   int                                      result = EZERO;

   if (aaiLoadConfiguration(AAI_CONFIG_FILE_NAME, &(parametersList->defaultParameters)) != EZERO || (parametersList->displayType != parametersList->defaultParameters.displayType)) {

      aaiInitializeParametersList(parametersList);
      result = aaiSaveConfiguration(AAI_CONFIG_FILE_NAME, &(parametersList->defaultParameters));

   }

   textmode((parametersList->displayType == AaiColor) ? C80 : BW80);
   TEXT_Constructor(BGI_GotoYX, BGI_GotoY, BGI_GotoX, BGI_WhereY, BGI_WhereX, BGI_TextAttr, BGI_GetTextInfo, BGI_ClrScr, BGI_Print_Character, BGI_Print_String, &(parametersList->text));

   memcpy(&(parametersList->menuCharacteristicsList), AaiMenuCharacteristicsList, sizeof(parametersList->menuCharacteristicsList));
   memcpy(parametersList->menuTextList, AaiMenuTextList, sizeof(parametersList->menuTextList));
   memcpy(parametersList->menuKeysList, AaiMenuKeysList, sizeof(parametersList->menuKeysList));
   parametersList->mainScreenText = AaiMainScreenText;
   parametersList->mainScreenCharacters = AaiMainScreenUniqueCharacters;
   parametersList->mainScreenCharacterColors = AaiMainScreenUniqueColors;

   parametersList->totalProcesses = AAI_TOTAL_PROCESSES;

   for (processNumber = 0; processNumber < parametersList->totalProcesses; processNumber++) {

      processDescriptor = &(parametersList->processDescriptor[processNumber]);

      processDescriptor->processNumber = processNumber;
      aaiHaltProcess(parametersList, processNumber);
      processDescriptor->processParameters = NULL;
      processDescriptor->process.process = AaiProcessList[processNumber].process;

      if (processDescriptor->process.process == NULL) {

         result = EZERO;

      }
      else {

         result = processDescriptor->process.process(&(processDescriptor->processParameters), &key);

         if (result == EZERO) {

            switch (processNumber) {

               case AaiDisplayTimeProcess :

                  displayTimeParameters = processDescriptor->processParameters;

                  displayTimeParameters->text = parametersList->text;
                  memcpy(&(displayTimeParameters->colors), &(parametersList->defaultParameters.mainMenuColors), sizeof(displayTimeParameters->colors));
                  displayTimeParameters->row = 1;
                  displayTimeParameters->column = 61;
                  displayTimeParameters->minutesValue = -1;
                  aaiActivateProcess(parametersList, AaiDisplayTimeProcess);
                  break;

               case AaiFileLoadProcess :

                  fileLoadParameters = processDescriptor->processParameters;
                  fileLoadParameters->parametersList = parametersList;
                  fileLoadParameters->port = NULL;
                  fileLoadParameters->text = parametersList->text;
                  memcpy(&(fileLoadParameters->colors), &(parametersList->defaultParameters.mainMenuColors), sizeof(fileLoadParameters->colors));
                  fileLoadParameters->startingRow = 3;
                  fileLoadParameters->startingColumn = 2;
                  fileLoadParameters->height = 14;
                  fileLoadParameters->width = 15;
                  strcpy(fileLoadParameters->fileName, "");
                  fileLoadParameters->currentFileNumber = 1;
                  fileLoadParameters->previousFileNumber = 1;
                  fileLoadParameters->firstFileNumber = 1;
                  fileLoadParameters->currentRow = 0;

                  break;

               case AaiFileNewProcess :

                  fileNewParameters = processDescriptor->processParameters;
                  fileNewParameters->parametersList = parametersList;
                  fileNewParameters->loadParameters = fileLoadParameters;
                  fileNewParameters->clearMemoryFlag = -1;
                  fileNewParameters->processInProgressFlag = FALSE;
                  break;

               case AaiFileSaveProcess :

                  fileSaveParameters = processDescriptor->processParameters;
                  fileSaveParameters->parametersList = parametersList;
                  fileSaveParameters->loadParameters = fileLoadParameters;
                  fileSaveParameters->port = NULL;
                  fileSaveParameters->text = parametersList->text;
                  memcpy(&(fileSaveParameters->colors), &(parametersList->defaultParameters.mainMenuColors), sizeof(fileSaveParameters->colors));
                  fileSaveParameters->startingRow = 9;
                  fileSaveParameters->startingColumn = 27;
                  fileSaveParameters->height = 5;
                  fileSaveParameters->width = 25;

                  fileSaveParameters->fileName.text = parametersList->text;
                  fileSaveParameters->fileName.editLength = 8;
                  fileSaveParameters->fileName.displayLength = 8;
                  fileSaveParameters->fileName.type = STRING_TYPE;
                  memcpy(&(fileSaveParameters->fileName.colors), &(parametersList->defaultParameters.mainMenuColors), sizeof(fileSaveParameters->fileName.colors));
                  fileSaveParameters->fileName.currentRow = 2;
                  fileSaveParameters->fileName.currentColumn = 15;
                  fileSaveParameters->fileName.markedFlag = FALSE;
                  fileSaveParameters->fileName.refreshFlag = TRUE;
                  strcpy(fileSaveParameters->fileName.value, "");

                  break;

               case AaiFileSaveAsProcess :

                  fileSaveAsParameters = processDescriptor->processParameters;
                  fileSaveAsParameters->parametersList = parametersList;
                  fileSaveAsParameters->loadParameters = fileLoadParameters;
                  break;

               case AaiFileDeleteProcess :

                  fileDeleteParameters = processDescriptor->processParameters;
                  fileDeleteParameters->parametersList = parametersList;
                  fileDeleteParameters->port = NULL;
                  fileDeleteParameters->text = parametersList->text;
                  memcpy(&(fileDeleteParameters->colors), &(parametersList->defaultParameters.mainMenuColors), sizeof(fileDeleteParameters->colors));
                  fileDeleteParameters->startingRow = 3;
                  fileDeleteParameters->startingColumn = 2;
                  fileDeleteParameters->height = 14;
                  fileDeleteParameters->width = 17;
                  strcpy(fileDeleteParameters->fileName, "");
                  fileDeleteParameters->currentFileNumber = 1;
                  fileDeleteParameters->previousFileNumber = 1;
                  fileDeleteParameters->firstFileNumber = 1;
                  fileDeleteParameters->currentRow = 0;
                  fileDeleteParameters->deleteFileFlag = -1;
                  fileDeleteParameters->processInProgressFlag = FALSE;
                  break;

               case AaiFileRenameProcess :

                  fileRenameParameters = processDescriptor->processParameters;
                  fileRenameParameters->parametersList = parametersList;
                  fileRenameParameters->port = NULL;
                  fileRenameParameters->text = parametersList->text;
                  memcpy(&(fileRenameParameters->colors), &(parametersList->defaultParameters.mainMenuColors), sizeof(fileRenameParameters->colors));
                  fileRenameParameters->startingRow = 3;
                  fileRenameParameters->startingColumn = 2;
                  fileRenameParameters->height = 14;
                  fileRenameParameters->width = 15;

                  fileRenameParameters->newFilePort = NULL;
                  fileRenameParameters->newFileStartingRow = 9;
                  fileRenameParameters->newFileStartingColumn = 30;
                  fileRenameParameters->newFileHeight = 5;
                  fileRenameParameters->newFileWidth = 20;

                  fileRenameParameters->newFileName.text = parametersList->text;
                  fileRenameParameters->newFileName.editLength = 8;
                  fileRenameParameters->newFileName.displayLength = 8;
                  fileRenameParameters->newFileName.type = STRING_TYPE;
                  memcpy(&(fileRenameParameters->newFileName.colors), &(parametersList->defaultParameters.mainMenuColors), sizeof(fileRenameParameters->newFileName.colors));
                  fileRenameParameters->newFileName.currentRow = 2;
                  fileRenameParameters->newFileName.currentColumn = 10;
                  fileRenameParameters->newFileName.markedFlag = FALSE;
                  fileRenameParameters->newFileName.refreshFlag = TRUE;
                  strcpy(fileRenameParameters->newFileName.value, "");

                  strcpy(fileRenameParameters->currentFileName, "");
                  fileRenameParameters->currentFileNumber = 1;
                  fileRenameParameters->previousFileNumber = 1;
                  fileRenameParameters->firstFileNumber = 1;
                  fileRenameParameters->currentRow = 0;

                  break;

               case AaiFileQuitProcess :

                  fileQuitParameters = processDescriptor->processParameters;
                  fileQuitParameters->parametersList = parametersList;
                  break;

               case AaiMeasureMeasureProcess :

                  measureMeasureParameters = processDescriptor->processParameters;
                  measureMeasureParameters->parametersList = parametersList;
                  break;

               case AaiMeasurePurgeProcess :

                  measurePurgeParameters = processDescriptor->processParameters;
                  measurePurgeParameters->parametersList = parametersList;
                  break;

               case AaiMeasureZeroSetProcess :

                  measureZeroSetParameters = processDescriptor->processParameters;
                  measureZeroSetParameters->parametersList = parametersList;
                  break;

               case AaiMeasureSampleNrProcess :

                  measureSampleNrParameters = processDescriptor->processParameters;
                  measureSampleNrParameters->parametersList = parametersList;
                  break;

               case AaiMeasureBatchProcess :

                  measureBatchParameters = processDescriptor->processParameters;
                  measureBatchParameters->parametersList = parametersList;
                  break;

               case AaiMeasureLabelProcess :

                  measureLabelParameters = processDescriptor->processParameters;
                  measureLabelParameters->parametersList = parametersList;
                  break;

               case AaiProductProcess :

                  productParameters = processDescriptor->processParameters;
                  productParameters->parametersList = parametersList;
                  break;

               case AaiCalibrateEditMeasureProcess :

                  calibrateEditMeasureParameters = processDescriptor->processParameters;
                  calibrateEditMeasureParameters->parametersList = parametersList;
                  break;

               case AaiCalibrateZeroSetProcess :

                  calibrateZeroSetParameters = processDescriptor->processParameters;
                  calibrateZeroSetParameters->parametersList = parametersList;
                  break;

               case AaiCalibrateCrossCalibrationProcess :

                  calibrateCrossCalibrationParameters = processDescriptor->processParameters;
                  calibrateCrossCalibrationParameters->parametersList = parametersList;
                  break;

               case AaiCalibratePilotSamplesProcess :

                  calibratePilotSamplesParameters = processDescriptor->processParameters;
                  calibratePilotSamplesParameters->parametersList = parametersList;
                  break;

               case AaiCalibrateBiasAndSlopeProcess :

                  calibrateBiasAndScopeParameters = processDescriptor->processParameters;
                  calibrateBiasAndScopeParameters->parametersList = parametersList;
                  break;

               case AaiCalibrateViewCalibrationProcess :

                  calibrateViewCalibrationParameters = processDescriptor->processParameters;
                  calibrateViewCalibrationParameters->parametersList = parametersList;
                  break;

               case AaiCalibrateMineralBiasProcess :

                  calibrateMineralBiasParameters = processDescriptor->processParameters;
                  calibrateMineralBiasParameters->parametersList = parametersList;
                  break;

               case AaiCalibrateStatisticsProcess :

                  calibrateStatisticsParameters = processDescriptor->processParameters;
                  calibrateStatisticsParameters->parametersList = parametersList;
                  break;

               case AaiCalibrateGraphicsProcess :

                  calibrateGraphicsParameters = processDescriptor->processParameters;
                  calibrateGraphicsParameters->parametersList = parametersList;
                  break;

               case AaiCalibrateCarryOverProcess :

                  calibrateCarryOverParameters = processDescriptor->processParameters;
                  calibrateCarryOverParameters->parametersList = parametersList;
                  break;

               case AaiCalibratePolynomialProcess :

                  calibratePolynomialParameters = processDescriptor->processParameters;
                  calibratePolynomialParameters->parametersList = parametersList;
                  break;

               case AaiSetupPrinterProcess :

                  setupPrinterParameters = processDescriptor->processParameters;
                  setupPrinterParameters->parametersList = parametersList;
                  break;

               case AaiSetupOutputProcess :

                  setupOutputParameters = processDescriptor->processParameters;
                  setupOutputParameters->parametersList = parametersList;
                  break;

               case AaiSetupTemperatureProcess :

                  setupTemperatureParameters = processDescriptor->processParameters;
                  setupTemperatureParameters->parametersList = parametersList;
                  break;

               case AaiSetupHeaderProcess :

                  setupHeaderParameters = processDescriptor->processParameters;
                  setupHeaderParameters->parametersList = parametersList;
                  break;

               case AaiSetupFooterProcess :

                  setupFooterParameters = processDescriptor->processParameters;
                  setupFooterParameters->parametersList = parametersList;
                  break;

               case AaiSetup1stSerialPortProcess :

                  setup1stSerialPortParameters = processDescriptor->processParameters;
                  setup1stSerialPortParameters->parametersList = parametersList;
                  break;

               case AaiSetup2ndSerialPortProcess :

                  setup2ndSerialPortParameters = processDescriptor->processParameters;
                  setup2ndSerialPortParameters->parametersList = parametersList;
                  break;

               case AaiSetupBarcodeReaderProcess :

                  setupBarcodeReaderParameters = processDescriptor->processParameters;
                  setupBarcodeReaderParameters->parametersList = parametersList;
                  break;

               case AaiSetupCyclesProcess :

                  setupCyclesParameters = processDescriptor->processParameters;
                  setupCyclesParameters->parametersList = parametersList;
                  break;

               case AaiSetupPressureLimitProcess :

                  setupPressureLimitParameters = processDescriptor->processParameters;
                  setupPressureLimitParameters->parametersList = parametersList;
                  break;

               case AaiSetupChopperSpeedProcess :

                  setupChopperSpeedParameters = processDescriptor->processParameters;
                  setupChopperSpeedParameters->parametersList = parametersList;
                  break;

               case AaiHelpIndexProcess :

                  helpIndexParameters = processDescriptor->processParameters;
                  helpIndexParameters->parametersList = parametersList;
                  helpIndexParameters->port = NULL;
                  helpIndexParameters->text = parametersList->text;
                  memcpy(&(helpIndexParameters->colors), &(parametersList->defaultParameters.mainMenuColors), sizeof(helpIndexParameters->colors));
                  helpIndexParameters->startingRow = 7;
                  helpIndexParameters->startingColumn = 8;
                  helpIndexParameters->height = 11;
                  helpIndexParameters->width = 64;
                  helpIndexParameters->helpFile = NULL;
                  helpIndexParameters->endOfFile = FALSE;
                  helpIndexParameters->helpAvailableFlag = FALSE;
                  helpIndexParameters->helpLoadedFlag = FALSE;
                  helpIndexParameters->firstRowLine = 1;
                  helpIndexParameters->currentRow = 0;
                  helpIndexParameters->previousRow = 0;
                  helpIndexParameters->redrawScreenFlag = TRUE;
                  aaiActivateProcess(parametersList, AaiHelpIndexProcess);
                  break;

               case AaiHelpAboutProcess :

                  helpAboutParameters = processDescriptor->processParameters;
                  helpAboutParameters->parametersList = parametersList;
                  helpAboutParameters->port = NULL;
                  helpAboutParameters->text = parametersList->text;
                  memcpy(&(helpAboutParameters->colors), &(parametersList->defaultParameters.mainMenuColors), sizeof(helpAboutParameters->colors));
                  helpAboutParameters->startingRow = 7;
                  helpAboutParameters->startingColumn = 13;
                  helpAboutParameters->height = 11;
                  helpAboutParameters->width = 54;
                  aaiActivateProcess(parametersList, AaiHelpAboutProcess);
                  break;

               case AaiHelpPrintProcess :

                  helpPrintParameters = processDescriptor->processParameters;
                  helpPrintParameters->parametersList = parametersList;
                  helpPrintParameters->indexParameters = helpIndexParameters;
                  helpPrintParameters->helpIndex = NULL;
                  helpPrintParameters->helpText = NULL;
                  helpPrintParameters->exitFlag = FALSE;
                  helpPrintParameters->reportFile = NULL;
                  helpPrintParameters->printReportFlag = -1;
                  helpPrintParameters->pageNumber = 0;
                  helpPrintParameters->lineNumber = 0;
                  helpPrintParameters->newPageFlag = TRUE;
                  helpPrintParameters->processInProgressFlag = FALSE;
                  helpPrintParameters->firstIndexNodeFlag = TRUE;
                  break;

               case AaiHelpTopicProcess :

                  helpTopicParameters = processDescriptor->processParameters;
                  helpTopicParameters->parametersList = parametersList;
                  helpTopicParameters->indexParameters = helpIndexParameters;
                  helpTopicParameters->port = NULL;
                  helpTopicParameters->text = parametersList->text;
                  memcpy(&(helpTopicParameters->colors), &(parametersList->defaultParameters.mainMenuColors), sizeof(helpTopicParameters->colors));
                  helpTopicParameters->startingRow = 7;
                  helpTopicParameters->startingColumn = 5;
                  helpTopicParameters->height = 11;
                  helpTopicParameters->width = 70;
                  helpTopicParameters->key = NULL;
                  helpTopicParameters->firstRowLine = 1;
                  helpTopicParameters->redrawScreenFlag = TRUE;
                  helpTopicParameters->exitFlag = FALSE;
                  break;

               case AaiYesNoMenuProcess :

                  yesNoMenuParameters = processDescriptor->processParameters;
                  yesNoMenuParameters->parametersList = parametersList;
                  yesNoMenuParameters->text = parametersList->text;
                  memcpy(&(yesNoMenuParameters->colors), &(parametersList->defaultParameters.yesNoMenuColors), sizeof(yesNoMenuParameters->colors));
                  yesNoMenuParameters->menuText = parametersList->menuTextList[AaiYesNoMenu];
                  yesNoMenuParameters->menuKeysList = parametersList->menuKeysList[AaiYesNoMenu];
                  yesNoMenuParameters->option = 1;

                  break;

               case AaiSubMenuProcess :

                  subMenuParameters = processDescriptor->processParameters;
                  subMenuParameters->parametersList = parametersList;
                  subMenuParameters->text = parametersList->text;
                  memcpy(&(subMenuParameters->colors), &(parametersList->defaultParameters.subMenuColors), sizeof(subMenuParameters->colors));
                  subMenuParameters->option = 1;
                  break;

               case AaiMainMenuProcess :

                  mainMenuParameters = processDescriptor->processParameters;
                  mainMenuParameters->parametersList = parametersList;
                  mainMenuParameters->text = parametersList->text;
                  memcpy(&(mainMenuParameters->colors), &(parametersList->defaultParameters.mainMenuColors), sizeof(mainMenuParameters->colors));
                  mainMenuParameters->menuText = parametersList->menuTextList[AaiMainMenu];
                  mainMenuParameters->menuKeysList = parametersList->menuKeysList[AaiMainMenu];
                  mainMenuParameters->startingRow = parametersList->menuCharacteristicsList[AaiMainMenu].startingRow;
                  mainMenuParameters->startingColumn = parametersList->menuCharacteristicsList[AaiMainMenu].startingColumn;
                  mainMenuParameters->option = parametersList->menuCharacteristicsList[AaiMainMenu].option;
                  mainMenuParameters->totalOptions = parametersList->menuCharacteristicsList[AaiMainMenu].totalOptions;
                  mainMenuParameters->exitFlag = FALSE;
                  aaiActivateProcess(parametersList, AaiMainMenuProcess);
                  break;

               case AaiFunctionKeyMenuProcess :

                  functionKeyMenuParameters = processDescriptor->processParameters;
                  functionKeyMenuParameters->parametersList = parametersList;
                  functionKeyMenuParameters->text = parametersList->text;
                  functionKeyMenuParameters->menuText = parametersList->menuTextList[AaiFunctionKeyMenu];
                  memcpy(&(functionKeyMenuParameters->colors), &(parametersList->defaultParameters.functionKeyMenuColors), sizeof(functionKeyMenuParameters->colors));
                  functionKeyMenuParameters->startingRow = parametersList->menuCharacteristicsList[AaiFunctionKeyMenu].startingRow;
                  functionKeyMenuParameters->startingColumn = parametersList->menuCharacteristicsList[AaiFunctionKeyMenu].startingColumn;
                  functionKeyMenuParameters->hideFunctionKeysFlag = FALSE;
                  aaiActivateProcess(parametersList, AaiFunctionKeyMenuProcess);
                  break;

            }

         }

      }

   }

   return (result);

}

/*

  Function    : aaiMain
   Description : The main entry point for the MAIN module of the AAI program.
   Inputs      : Nothing.
   Updates     : Nothing.
   Outputs     : parametersList = The parameters list to use while the AAI system is active.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 08/18/92 DWP Initial coding.
   Notes       :

*/

int aaiMain(AaiParametersList * parametersList) {

   PORT              main_screen;
   CARDINAL_16       key;
   BOOLEAN           exitFlag;
   AaiProcessTypes   processNumber;
   int               result;

   /*

      Initialize the parameters list.  Exit if an error occurs.

   */

   if ((result = aaiInitialize(parametersList)) == EZERO) {

      /*

         Initialize the main port.  Continue only if it was successfully initialized.

      */

      if ((result = PORT_Constructor(1, 1, 25, 80, PORT_NO_BORDER, LIGHTGRAY, LIGHTGRAY, &main_screen)) == PORT_NOERR) {

         CURSOR_Off();
         aaiDisplayMainScreen(parametersList);

         /*

            Main event loop.

         */

         for (exitFlag = FALSE; !exitFlag && result == 0;) {

            key = (KB_Preview() != 0) ? KB_Read() : 0;

            for (processNumber = 0; result == EZERO && processNumber < parametersList->totalProcesses; processNumber++) {

               if (parametersList->processDescriptor[processNumber].processActiveFlag) {

                  if (!parametersList->processDescriptor[AaiHelpTopicProcess].processActiveFlag || processNumber == AaiDisplayTimeProcess || processNumber == AaiHelpTopicProcess || processNumber == AaiFunctionKeyMenuProcess) {

                     if (parametersList->processDescriptor[processNumber].process.process != NULL) {

                        result = parametersList->processDescriptor[processNumber].process.process(&(parametersList->processDescriptor[processNumber].processParameters), &key);

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

   AaiParametersList parametersList;
   struct text_info  textInfo;
   struct ffblk      ffblk;
   int               i;

   if (_osmajor < 3 || (_osmajor == 3 && _osminor < 3)) {

      printf("\nAAI Requires MS/PC-DOS version 3.3 Or Higher\n");

   }
   else {

      setmem(&parametersList, sizeof(parametersList), 0);
      parametersList.displayTypeSpecified = FALSE;

      /*

         Determine if the default configuration file exists in the current directory.  If it does exist, use the video mode defined in
         it, otherwise, determine what display mode is currently active and use it as the default video mode.

      */

      if (findfirst("AAI.CFG", &ffblk, FA_ARCH) != 0) {

         setmem(&(parametersList.defaultParameters), sizeof(parametersList.defaultParameters), 0);
         gettextinfo(&textInfo);
         parametersList.displayType = (textInfo.currmode == 3) ? AaiColor : AaiMonochrome;

      }

      /*

         Process the command-line parameters.

      */

      for (i = 1; i < argc; i++) {

         if (strchr("-/", argv[i][0]) != NULL) {

            if (stricmp("COLOR", &(argv[i][1])) == 0) {

               parametersList.displayType = AaiColor;
               parametersList.displayTypeSpecified = TRUE;

            }

            if (stricmp("MONO", &(argv[i][1])) == 0) {

               parametersList.displayType = AaiMonochrome;
               parametersList.displayTypeSpecified = TRUE;

            }

            if (stricmp("LCD", &(argv[i][1])) == 0) {

               parametersList.displayType = AaiLcd;
               parametersList.displayTypeSpecified = TRUE;

            }

         }

      }

      /*

         Invoke the main module.

      */

      aaiMain(&parametersList);

   }

   return (0);

}
