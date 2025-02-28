/*

   File        : AAI2.C
   Module      : PROCESSES
   System      : AAI
   Description : This module contains all sub-menu processes for the AAI system.
   Modified    : 08/18/92 DWP Created.
   Notes       :

*/

#include <alloc.h>
#include <conio.h>
#include <ctype.h>
#include <errno.h>
#include <mem.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "\Dev\DOS\Lib\C\CAsynch\Include\asynch_1.h"
#include "\Dev\DOS\Lib\ASM\Cursor\cursor.h"
#include "\Dev\DOS\Lib\C\MSDOS\dos.h"
#include "\Dev\DOS\Lib\ASM\KB\kb.h"
#include "\Dev\DOS\Lib\ASM\Printer\printer.h"
#include "\Dev\DOS\Lib\C\String\string.h"

#include "aai.h"

/*

   Procedure   : aaiSelectFilePrintOneFileName
   Description : Prints one file name.
   Inputs      : fileList =
                 row      =
                 position =
                 text     =
   Updates     : Nothing.
   Outputs     : Nothing.
   Returns     : Nothing.
   Modified    : 08/18/92 DWP Initial coding.
   Notes       :

*/

void aaiSelectFilePrintOneFileName(LIST fileList, CARDINAL_16 row, CARDINAL_32 position, TEXT text) {

   char * currentFileName;
   char   str[MAXFILE];

   LIST_Retrieve(fileList, position, (void **) &currentFileName);
   TEXT_Set_Cursor_Position(row + 4, 2, text);
   sprintf(str, "%-8.8s", (currentFileName != NULL) ? currentFileName : "");
   TEXT_Print_String(str, text);

}

/*

   Function    : aaiSelectFilePrintFileNames
   Description : Prints 8 files on the screen.
   Inputs      : startingFileNumber =
                 fileList           =
                 text               =
   Updates     : Nothing.
   Outputs     : Nothing.
   Returns     : Nothing.
   Modified    : 08/18/92 DWP Initial coding.
   Notes       :

*/

void aaiSelectFilePrintFileNames(CARDINAL_32 startingFileNumber, LIST fileList, TEXT text) {

   CARDINAL_16 i;
   CARDINAL_32 lastPosition;
   char *      currentFileName;

   for (i = 0; i < 8; i++) {

      aaiSelectFilePrintOneFileName(fileList, i, startingFileNumber + i, text);

   }

   TEXT_Set_Cursor_Position(4, 12, text);
   TEXT_Print_Character((startingFileNumber > 1) ? '\x18' : ' ', text);
   LIST_Retrieve(fileList, LIST_LAST, (void **) &(currentFileName));
   LIST_Current(fileList, &(lastPosition));
   TEXT_Set_Cursor_Position(11, 12, text);
   TEXT_Print_Character((lastPosition > startingFileNumber + 7) ? '\x19' : ' ', text);

}

/*

   Function    : aaiSelectFile
   Description : Allows the user to select a file from a list of files in a directory.
   Inputs      : Nothing.
   Updates     : currentRow         =
                 currentFileNumber  =
                 previousFileNumber =
                 firstFileNumber    =
                 colors             =
                 text               =
                 key                =
   Outputs     : fileList           =
                 fileName           =
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 08/18/92 DWP Initial coding.
   Notes       :

*/

int aaiSelectFile(CARDINAL_16 * currentRow, CARDINAL_32 * currentFileNumber, CARDINAL_32 * previousFileNumber, CARDINAL_32 * firstFileNumber, AaiColors * colors, TEXT text, CARDINAL_16 * key, LIST * fileList, char * fileName) {

   CARDINAL_32  totalFiles;
   BOOLEAN      validKeyFlag, displayLightBarFlag, refreshScreenFlag;
   struct ffblk ffblk;
   char *       currentFileName;
   char         str[MAXFILE];
   int          endOfDirectoryIndicator, result;

   refreshScreenFlag = FALSE;

   if (*(fileList) != NULL) {

      displayLightBarFlag = FALSE;
      result = EZERO;

   }
   else {

      displayLightBarFlag = TRUE;
      result = LIST_Constructor(MAXFILE, fileList);
      endOfDirectoryIndicator = findfirst("*.DAT", &(ffblk), 0);

      while (result == LIST_NOERR && endOfDirectoryIndicator == 0) {

         sprintf(str, "%-8.8s", ffblk.ff_name);

         if (STRING_CharPos(str, '.') != 0) {

            str[STRING_CharPos(str, '.') - 1] = '\0';

         }

         result = LIST_Insert(str, LIST_LAST, *(fileList));
         endOfDirectoryIndicator = findnext(&(ffblk));

      }

      if (result == LIST_NOERR) {

         refreshScreenFlag = TRUE;

      }

   }

   if (result == EZERO) {

      if (*(previousFileNumber) != *(currentFileNumber) || displayLightBarFlag) {

         if (*(firstFileNumber) + 7 < *(currentFileNumber)) {

            (*(firstFileNumber))++;
            refreshScreenFlag = TRUE;

         }
         else {

            if (*(firstFileNumber) > *(currentFileNumber)) {

               (*(firstFileNumber))--;
               refreshScreenFlag = TRUE;

            }

         }

         if (refreshScreenFlag) {

            TEXT_Set_Text_Color(colors->primaryColor, text);
            aaiSelectFilePrintFileNames(*(firstFileNumber), *(fileList), text);

         }
         else {

            TEXT_Set_Text_Color(colors->primaryColor, text);
            aaiSelectFilePrintOneFileName(*(fileList), *(currentRow), *(previousFileNumber), text);

         }

         if (*(currentFileNumber) > *(previousFileNumber)) {

            *(currentRow) = (*(currentRow) < 7) ? *(currentRow) + 1 : 7;

         }
         else {

            if (*(currentFileNumber) < *(previousFileNumber)) {

               *(currentRow) = (*(currentRow) > 0) ? *(currentRow) - 1 : 0;

            }

         }

         TEXT_Set_Text_Color(colors->primaryHighlightColor, text);
         aaiSelectFilePrintOneFileName(*(fileList), *(currentRow), *(currentFileNumber), text);

         *(previousFileNumber) = *(currentFileNumber);

      }

      validKeyFlag = TRUE;

      switch (*(key)) {

         case KB_UP :
         case KB_GRAY_UP :
         case KB_SHIFT_TAB :

            *(currentFileNumber) = (*(currentFileNumber) > 1) ? *(currentFileNumber) - 1 : 1;
            break;

         case KB_DOWN :
         case KB_GRAY_DOWN :
         case KB_TAB :

            LIST_Retrieve(*(fileList), LIST_LAST, (void **) &(currentFileName));
            LIST_Current(*(fileList), &(totalFiles));
            *(currentFileNumber) = (*(currentFileNumber) < totalFiles) ? *(currentFileNumber) + 1 : totalFiles;
            break;

         case KB_ENTER :
         case KB_GRAY_ENTER :

            LIST_Retrieve(*(fileList), LIST_FIRST, (void **) &(currentFileName));
            LIST_Retrieve(*(fileList), *(currentFileNumber), (void **) &(currentFileName));
            sprintf(fileName, "%.8s", currentFileName);
            break;

         default :

            validKeyFlag = FALSE;

      }

      if (validKeyFlag) {

         *(key) = 0;

      }

   }

   return (result);

}

/*

   Function    : aaiFileLoad
   Description : Allows the user to load a data file into memory.
   Inputs      : Nothing.
   Updates     : processParameters =
                 key               =
   Outputs     : Nothing.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 08/18/92 DWP Initial coding.
   Notes       :

*/

int aaiFileLoad(void ** processParameters, CARDINAL_16 * key) {

   AaiFileLoadParameters * parameters;
   BOOLEAN                 firstRowLine = FALSE;
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
         aaiSetHelpScreen(parameters->parametersList, AaiHelpIndexKeyList[AaiHelpFlLoa]);

         if (parameters->port != NULL) {

            result = PORT_Activate(parameters->port);

         }
         else {

            if ((result = PORT_Constructor(parameters->startingRow, parameters->startingColumn, parameters->height, parameters->width, PORT_SINGLE_LINE_BORDER, parameters->colors.primaryColor, parameters->colors.primaryColor, &(parameters->port))) == PORT_NOERR) {

               TEXT_Set_Cursor_Position(2, 2, parameters->text);
               TEXT_Print_String("Load A File", parameters->text);
               parameters->fileName[0] = '\0';

            }

         }

         if (result == EZERO) {

            result = aaiSelectFile(&(parameters->currentRow), &(parameters->currentFileNumber), &(parameters->previousFileNumber), &(parameters->firstFileNumber), &(parameters->colors), parameters->text, key, &(parameters->fileList), parameters->fileName);

            if (*(key) == KB_ESC) {

               firstRowLine = TRUE;

            }

            if (parameters->fileName[0] != '\0') {

               firstRowLine = TRUE;

            }

            if (firstRowLine) {

               LIST_Destructor(&(parameters->fileList));
               PORT_Destructor(&(parameters->port));
               aaiHaltProcess(parameters->parametersList, AaiFileLoadProcess);
               aaiActivateProcess(parameters->parametersList, AaiMainMenuProcess);
               *(key) = 0;

            }

         }

      }

   }

   return (result);

}

/*

   Function    : aaiFileNew
   Description : Allows the user to clear memory.
   Inputs      : Nothing.
   Updates     : processParameters =
                 key               =
   Outputs     : Nothing.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 08/18/92 DWP Initial coding.
   Notes       :

*/

int aaiFileNew(void ** processParameters, CARDINAL_16 * key) {

   AaiFileNewParameters * parameters;
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
         aaiSetHelpScreen(parameters->parametersList, AaiHelpIndexKeyList[AaiHelpFlNew]);

         if (parameters->processInProgressFlag) {

            if ((int) parameters->clearMemoryFlag != 255) {

               if (parameters->clearMemoryFlag) {

                  parameters->loadParameters->fileName[0] = '\0';

               }

               parameters->processInProgressFlag = FALSE;
               aaiHaltProcess(parameters->parametersList, AaiFileNewProcess);
               aaiActivateProcess(parameters->parametersList, AaiMainMenuProcess);

            }

         }
         else {

            aaiActivateProcess(parameters->parametersList, AaiYesNoMenuProcess);

            ((AaiYesNoMenuParameters *) parameters->parametersList->processDescriptor[AaiYesNoMenuProcess].processParameters)->startingRow = 9;
            ((AaiYesNoMenuParameters *) parameters->parametersList->processDescriptor[AaiYesNoMenuProcess].processParameters)->startingColumn = 21;
            ((AaiYesNoMenuParameters *) parameters->parametersList->processDescriptor[AaiYesNoMenuProcess].processParameters)->displayMessage = "Clear Current Times, Are You Sure?";
            ((AaiYesNoMenuParameters *) parameters->parametersList->processDescriptor[AaiYesNoMenuProcess].processParameters)->option = 1;
            ((AaiYesNoMenuParameters *) parameters->parametersList->processDescriptor[AaiYesNoMenuProcess].processParameters)->invokingProcess = AaiMainMenuProcess;
            ((AaiYesNoMenuParameters *) parameters->parametersList->processDescriptor[AaiYesNoMenuProcess].processParameters)->yesSelectedFlag = &(((AaiFileNewParameters *) parameters->parametersList->processDescriptor[AaiFileNewProcess].processParameters)->clearMemoryFlag);

            parameters->clearMemoryFlag = -1;
            parameters->processInProgressFlag = TRUE;

         }

         result = EZERO;

      }

   }

   return (result);

}

/*

   Function    : aaiFileSave
   Description : The process used to save bender configurations to disk.
   Inputs      : processParameters =
                 key               =
   Updates     : Nothing.
   Outputs     : Nothing.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 08/18/92 DWP Initial coding.
   Notes       :

*/

int aaiFileSave(void ** processParameters, CARDINAL_16 * key) {

   AaiFileSaveParameters * parameters;
   BOOLEAN                 firstRowLine = FALSE;
   char                    str[9];
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

         if (parameters->loadParameters->fileName[7] != '\xff') {

            aaiSetHelpScreen(parameters->parametersList, AaiHelpIndexKeyList[AaiHelpFlSav]);

         }

         if (parameters->loadParameters->fileName[0] != '\0') {

            firstRowLine = TRUE;

         }
         else {

            if (parameters->port != NULL) {

               result = PORT_Activate(parameters->port);

            }
            else {

               if ((result = PORT_Constructor(parameters->startingRow, parameters->startingColumn, parameters->height, parameters->width, PORT_SINGLE_LINE_BORDER, parameters->colors.primaryColor, parameters->colors.primaryColor, &(parameters->port))) == PORT_NOERR) {

                  TEXT_Set_Cursor_Position(2, 2, parameters->text);
                  TEXT_Print_String("Save As File", parameters->text);
                  parameters->fileName.refreshFlag = TRUE;
                  aaiInput(&(parameters->fileName), key);

               }

            }

            if (result == EZERO) {

               switch (*(key)) {

                  case KB_ENTER :
                  case KB_GRAY_ENTER :
                  case KB_TAB :

                     sprintf(str, "%-.8s", parameters->fileName.value);
                     STRING_Trim(STRING_TRIM_SPACE, STRING_ATrim(str));

                     if (STRING_CharPos(str, '.') > 0) {

                        str[STRING_CharPos(str, '.') - 1] = '\0';

                     }

                     if (str[0] != '\0') {

                        strcpy(parameters->loadParameters->fileName, str);

                     }

                     *(key) = 0;
                     break;

                  case KB_ESC :

                     parameters->loadParameters->fileName[0] = '\0';
                     firstRowLine = TRUE;
                     *(key) = 0;
                     break;

               }

               aaiInput(&(parameters->fileName), key);

            }

         }

         if (firstRowLine) {

            if (parameters->port != NULL) {

               PORT_Destructor(&(parameters->port));

            }

            aaiHaltProcess(parameters->parametersList, AaiFileSaveProcess);
            aaiActivateProcess(parameters->parametersList, AaiMainMenuProcess);

         }

      }

   }

   return (result);

}

/*

   Function    : aaiFileSaveAs
   Description : The process used to save bender configurations to disk.
   Inputs      : processParameters =
                 key               =
   Updates     : Nothing.
   Outputs     : Nothing.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 08/18/92 DWP Initial coding.
   Notes       :

*/

int aaiFileSaveAs(void ** processParameters, CARDINAL_16 * key) {

   AaiFileSaveAsParameters * parameters;
   int                       result;

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
         aaiSetHelpScreen(parameters->parametersList, AaiHelpIndexKeyList[AaiHelpFlSvA]);
         parameters->loadParameters->fileName[0] = '\0';
         parameters->loadParameters->fileName[7] = '\xff';
         aaiHaltProcess(parameters->parametersList, AaiFileSaveAsProcess);
         aaiActivateProcess(parameters->parametersList, AaiFileSaveProcess);

      }

   }

   return (result);

}

/*

   Function    : aaiFileDelete
   Description : Allows the user to delete a data file.
   Inputs      : Nothing.
   Updates     : processParameters =
                 key               =
   Outputs     : Nothing.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 08/18/92 DWP Initial coding.
   Notes       :

*/

int aaiFileDelete(void ** processParameters, CARDINAL_16 * key) {

   AaiFileDeleteParameters * parameters;
   BOOLEAN                   firstRowLine = FALSE;
   char                      wholeFileName[MAXPATH];
   int                       result;

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
         aaiSetHelpScreen(parameters->parametersList, AaiHelpIndexKeyList[AaiHelpFlDel]);

         if (parameters->port != NULL) {

            result = PORT_Activate(parameters->port);

         }
         else {

            if ((result = PORT_Constructor(parameters->startingRow, parameters->startingColumn, parameters->height, parameters->width, PORT_SINGLE_LINE_BORDER, parameters->colors.primaryColor, parameters->colors.primaryColor, &(parameters->port))) == PORT_NOERR) {

               TEXT_Set_Cursor_Position(2, 2, parameters->text);
               TEXT_Print_String("Delete A File", parameters->text);
               parameters->fileName[0] = '\0';
               parameters->deleteFileFlag = -1;

            }

         }

         if (result == EZERO) {

            if (parameters->fileName[0] == '\0') {

               result = aaiSelectFile(&(parameters->currentRow), &(parameters->currentFileNumber), &(parameters->previousFileNumber), &(parameters->firstFileNumber), &(parameters->colors), parameters->text, key, &(parameters->fileList), parameters->fileName);

               if (*(key) == KB_ESC) {

                  firstRowLine = TRUE;

               }

            }
            else {

               if (parameters->processInProgressFlag) {

                  sprintf(wholeFileName, "%-.8s.DAT", parameters->fileName);

                  if ((int) parameters->deleteFileFlag != -1) {

                     if (parameters->deleteFileFlag) {

                        unlink(wholeFileName);

                     }

                     parameters->processInProgressFlag = FALSE;
                     aaiHaltProcess(parameters->parametersList, AaiFileDeleteProcess);
                     aaiActivateProcess(parameters->parametersList, AaiMainMenuProcess);
                     firstRowLine = TRUE;

                  }

               }
               else {

                  aaiActivateProcess(parameters->parametersList, AaiYesNoMenuProcess);

                  ((AaiYesNoMenuParameters *) parameters->parametersList->processDescriptor[AaiYesNoMenuProcess].processParameters)->startingRow = 9;
                  ((AaiYesNoMenuParameters *) parameters->parametersList->processDescriptor[AaiYesNoMenuProcess].processParameters)->startingColumn = 21;
                  ((AaiYesNoMenuParameters *) parameters->parametersList->processDescriptor[AaiYesNoMenuProcess].processParameters)->displayMessage = "Delete File, Are You Sure?";
                  ((AaiYesNoMenuParameters *) parameters->parametersList->processDescriptor[AaiYesNoMenuProcess].processParameters)->option = 1;
                  ((AaiYesNoMenuParameters *) parameters->parametersList->processDescriptor[AaiYesNoMenuProcess].processParameters)->invokingProcess = AaiFileDeleteProcess;
                  ((AaiYesNoMenuParameters *) parameters->parametersList->processDescriptor[AaiYesNoMenuProcess].processParameters)->yesSelectedFlag = &(((AaiFileDeleteParameters *) parameters->parametersList->processDescriptor[AaiFileDeleteProcess].processParameters)->deleteFileFlag);

                  parameters->deleteFileFlag = -1;
                  parameters->processInProgressFlag = TRUE;

               }

            }

            if (firstRowLine) {

               LIST_Destructor(&(parameters->fileList));
               PORT_Destructor(&(parameters->port));
               aaiHaltProcess(parameters->parametersList, AaiFileDeleteProcess);
               aaiActivateProcess(parameters->parametersList, AaiMainMenuProcess);
               *(key) = 0;

            }

         }

      }

   }

   return (result);

}

/*

   Function    : aaiFileRename
   Description : Allows the user to rename a data file.
   Inputs      : Nothing.
   Updates     : processParameters =
                 key               =
   Outputs     : Nothing.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 08/18/92 DWP Initial coding.
   Notes       :

*/

int aaiFileRename(void ** processParameters, CARDINAL_16 * key) {

   AaiFileRenameParameters * parameters;
   BOOLEAN                   firstRowLine = FALSE;
   char                      str[9], oldFileName[MAXPATH], newFileName[MAXPATH];
   int                       result;

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
         aaiSetHelpScreen(parameters->parametersList, AaiHelpIndexKeyList[AaiHelpFlRen]);

         if (parameters->port != NULL) {

            result = PORT_Activate(parameters->port);

         }
         else {

            if ((result = PORT_Constructor(parameters->startingRow, parameters->startingColumn, parameters->height, parameters->width, PORT_SINGLE_LINE_BORDER, parameters->colors.primaryColor, parameters->colors.primaryColor, &(parameters->port))) == PORT_NOERR) {

               TEXT_Set_Cursor_Position(2, 2, parameters->text);
               TEXT_Print_String("Rename File", parameters->text);
               parameters->newFileName.refreshFlag = TRUE;
               parameters->currentFileName[0] = '\0';

            }

         }

         if (result == EZERO) {

            if (parameters->currentFileName[0] == '\0') {

               result = aaiSelectFile(&(parameters->currentRow), &(parameters->currentFileNumber), &(parameters->previousFileNumber), &(parameters->firstFileNumber), &(parameters->colors), parameters->text, key, &(parameters->fileList), parameters->currentFileName);

               if (*(key) == KB_ESC) {

                  firstRowLine = TRUE;

               }

            }
            else {

               if (parameters->newFilePort != NULL) {

                  result = PORT_Activate(parameters->newFilePort);

               }
               else {

                  if ((result = PORT_Constructor(parameters->newFileStartingRow, parameters->newFileStartingColumn, parameters->newFileHeight, parameters->newFileWidth, PORT_SINGLE_LINE_BORDER, parameters->colors.primaryColor, parameters->colors.primaryColor, &(parameters->newFilePort))) == PORT_NOERR) {

                     TEXT_Set_Cursor_Position(2, 2, parameters->text);
                     TEXT_Print_String("As File", parameters->text);
                     parameters->newFileName.refreshFlag = TRUE;

                  }

               }

               switch (*(key)) {

                  case KB_ENTER :
                  case KB_GRAY_ENTER :
                  case KB_TAB :

                     sprintf(str, "%-.8s", parameters->newFileName.value);
                     STRING_Trim(STRING_TRIM_SPACE, STRING_ATrim(str));

                     if (STRING_CharPos(str, '.') > 0) {

                        str[STRING_CharPos(str, '.') - 1] = '\0';

                     }

                     if (str[0] != '\0') {

                        strcpy(parameters->newFileName.value, str);
                        sprintf(oldFileName, "%-.8s.DAT", parameters->currentFileName);
                        sprintf(newFileName, "%-.8s.DAT", parameters->newFileName.value);
                        rename(oldFileName, newFileName);

                     }

                     firstRowLine = TRUE;
                     break;

                  case KB_ESC :

                     firstRowLine = TRUE;
                     break;

               }

               aaiInput(&(parameters->newFileName), key);

            }

            if (firstRowLine) {

               LIST_Destructor(&(parameters->fileList));
               PORT_Destructor(&(parameters->newFilePort));
               PORT_Destructor(&(parameters->port));
               aaiHaltProcess(parameters->parametersList, AaiFileRenameProcess);
               aaiActivateProcess(parameters->parametersList, AaiMainMenuProcess);
               *(key) = 0;

            }

         }

      }

   }

   return (result);

}

/*

   Function    : aaiFileQuit
   Description : The process used to exit from the AAI system.
   Inputs      : processParameters =
                 key               =
   Updates     : Nothing.
   Outputs     : Nothing.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 08/18/92 DWP Initial coding.
   Notes       :

*/

int aaiFileQuit(void ** processParameters, CARDINAL_16 * key) {

   AaiFileQuitParameters * parameters;
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
         aaiSetHelpScreen(parameters->parametersList, AaiHelpIndexKeyList[AaiHelpFlQui]);

         aaiHaltProcess(parameters->parametersList, AaiMainMenuProcess);
         aaiActivateProcess(parameters->parametersList, AaiYesNoMenuProcess);

         ((AaiYesNoMenuParameters *) parameters->parametersList->processDescriptor[AaiYesNoMenuProcess].processParameters)->startingRow = 9;
         ((AaiYesNoMenuParameters *) parameters->parametersList->processDescriptor[AaiYesNoMenuProcess].processParameters)->startingColumn = 25;
         ((AaiYesNoMenuParameters *) parameters->parametersList->processDescriptor[AaiYesNoMenuProcess].processParameters)->displayMessage = "Exit Program, Are You Sure?";
         ((AaiYesNoMenuParameters *) parameters->parametersList->processDescriptor[AaiYesNoMenuProcess].processParameters)->option = 1;
         ((AaiYesNoMenuParameters *) parameters->parametersList->processDescriptor[AaiYesNoMenuProcess].processParameters)->invokingProcess = AaiMainMenuProcess;
         ((AaiYesNoMenuParameters *) parameters->parametersList->processDescriptor[AaiYesNoMenuProcess].processParameters)->yesSelectedFlag = &(((AaiMainMenuParameters *) parameters->parametersList->processDescriptor[AaiMainMenuProcess].processParameters)->exitFlag);

         aaiHaltProcess(parameters->parametersList, AaiFileQuitProcess);

         result = EZERO;

      }

   }

   return (result);

}

/*

   Function    : aaiMeasureMeasure
   Description :
   Inputs      : Nothing.
   Updates     : processParameters =
                 key               =
   Outputs     : Nothing.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 10/15/94 DWP Initial coding.
   Notes       :

*/

int aaiMeasureMeasure(void ** processParameters, CARDINAL_16 * key) {

   AaiMeasureMeasureParameters * parameters;
   int                           result;

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
         aaiSetHelpScreen(parameters->parametersList, AaiHelpIndexKeyList[AaiHelpMeMea]);

      }

   }

   return (result);

}

/*

   Function    : aaiMeasurePurge
   Description :
   Inputs      : Nothing.
   Updates     : processParameters =
                 key               =
   Outputs     : Nothing.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 10/15/94 DWP Initial coding.
   Notes       :

*/

int aaiMeasurePurge(void ** processParameters, CARDINAL_16 * key) {

   AaiMeasurePurgeParameters * parameters;
   int                         result;

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
         aaiSetHelpScreen(parameters->parametersList, AaiHelpIndexKeyList[AaiHelpMePur]);

      }

   }

   return (result);

}

/*

   Function    : aaiMeasureZeroSet
   Description :
   Inputs      : Nothing.
   Updates     : processParameters =
                 key               =
   Outputs     : Nothing.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 10/15/94 DWP Initial coding.
   Notes       :

*/

int aaiMeasureZeroSet(void ** processParameters, CARDINAL_16 * key) {

   AaiMeasureZeroSetParameters * parameters;
   int                           result;

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
         aaiSetHelpScreen(parameters->parametersList, AaiHelpIndexKeyList[AaiHelpMeZer]);

      }

   }

   return (result);

}

/*

   Function    : aaiMeasureSampleNr
   Description :
   Inputs      : Nothing.
   Updates     : processParameters =
                 key               =
   Outputs     : Nothing.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 10/15/94 DWP Initial coding.
   Notes       :

*/

int aaiMeasureSampleNr(void ** processParameters, CARDINAL_16 * key) {

   AaiMeasureSampleNrParameters * parameters;
   int                            result;

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
         aaiSetHelpScreen(parameters->parametersList, AaiHelpIndexKeyList[AaiHelpMeSam]);

      }

   }

   return (result);

}

/*

   Function    : aaiMeasureBatch
   Description :
   Inputs      : Nothing.
   Updates     : processParameters =
                 key               =
   Outputs     : Nothing.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 10/15/94 DWP Initial coding.
   Notes       :

*/

int aaiMeasureBatch(void ** processParameters, CARDINAL_16 * key) {

   AaiMeasureBatchParameters * parameters;
   int                         result;

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
         aaiSetHelpScreen(parameters->parametersList, AaiHelpIndexKeyList[AaiHelpMeBat]);

      }

   }

   return (result);

}

/*

   Function    : aaiMeasureLabel
   Description :
   Inputs      : Nothing.
   Updates     : processParameters =
                 key               =
   Outputs     : Nothing.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 10/15/94 DWP Initial coding.
   Notes       :

*/

int aaiMeasureLabel(void ** processParameters, CARDINAL_16 * key) {

   AaiMeasureLabelParameters * parameters;
   int                         result;

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
         aaiSetHelpScreen(parameters->parametersList, AaiHelpIndexKeyList[AaiHelpMeLab]);

      }

   }

   return (result);

}

/*

   Function    : aaiProduct
   Description :
   Inputs      : Nothing.
   Updates     : processParameters =
                 key               =
   Outputs     : Nothing.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 10/15/94 DWP Initial coding.
   Notes       :

*/

int aaiProduct(void ** processParameters, CARDINAL_16 * key) {

   AaiProductParameters * parameters;
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
         aaiSetHelpScreen(parameters->parametersList, AaiHelpIndexKeyList[AaiHelpProdM]);

      }

   }

   return (result);

}

/*

   Function    : aaiCalibrateEditMeasure
   Description :
   Inputs      : Nothing.
   Updates     : processParameters =
                 key               =
   Outputs     : Nothing.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 10/15/94 DWP Initial coding.
   Notes       :

*/

int aaiCalibrateEditMeasure(void ** processParameters, CARDINAL_16 * key) {

   AaiCalibrateEditMeasureParameters * parameters;
   int                                 result;

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
         aaiSetHelpScreen(parameters->parametersList, AaiHelpIndexKeyList[AaiHelpCaEdi]);

      }

   }

   return (result);

}

/*

   Function    : aaiCalibrateZeroSet
   Description :
   Inputs      : Nothing.
   Updates     : processParameters =
                 key               =
   Outputs     : Nothing.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 10/15/94 DWP Initial coding.
   Notes       :

*/

int aaiCalibrateZeroSet(void ** processParameters, CARDINAL_16 * key) {

   AaiCalibrateZeroSetParameters * parameters;
   int                             result;

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
         aaiSetHelpScreen(parameters->parametersList, AaiHelpIndexKeyList[AaiHelpCaZer]);

      }

   }

   return (result);

}

/*

   Function    : aaiCalibrateCrossCalibration
   Description :
   Inputs      : Nothing.
   Updates     : processParameters =
                 key               =
   Outputs     : Nothing.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 10/15/94 DWP Initial coding.
   Notes       :

*/

int aaiCalibrateCrossCalibration(void ** processParameters, CARDINAL_16 * key) {

   AaiCalibrateCrossCalibrationParameters * parameters;
   int                                      result;

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
         aaiSetHelpScreen(parameters->parametersList, AaiHelpIndexKeyList[AaiHelpCaCro]);

      }

   }

   return (result);

}

/*

   Function    : aaiCalibratePilotSamples
   Description :
   Inputs      : Nothing.
   Updates     : processParameters =
                 key               =
   Outputs     : Nothing.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 10/15/94 DWP Initial coding.
   Notes       :

*/

int aaiCalibratePilotSamples(void ** processParameters, CARDINAL_16 * key) {

   AaiCalibratePilotSamplesParameters * parameters;
   int                                  result;

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
         aaiSetHelpScreen(parameters->parametersList, AaiHelpIndexKeyList[AaiHelpCaPil]);

      }

   }

   return (result);

}

/*

   Function    : aaiCalibrateBiasAndSlope
   Description :
   Inputs      : Nothing.
   Updates     : processParameters =
                 key               =
   Outputs     : Nothing.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 10/15/94 DWP Initial coding.
   Notes       :

*/

int aaiCalibrateBiasAndSlope(void ** processParameters, CARDINAL_16 * key) {

   AaiCalibrateBiasAndSlopeParameters * parameters;
   int                                  result;

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
         aaiSetHelpScreen(parameters->parametersList, AaiHelpIndexKeyList[AaiHelpCaBia]);

      }

   }

   return (result);

}

/*

   Function    : aaiCalibrateViewCalibration
   Description :
   Inputs      : Nothing.
   Updates     : processParameters =
                 key               =
   Outputs     : Nothing.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 10/15/94 DWP Initial coding.
   Notes       :

*/

int aaiCalibrateViewCalibration(void ** processParameters, CARDINAL_16 * key) {

   AaiCalibrateViewCalibrationParameters * parameters;
   int                                     result;

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
         aaiSetHelpScreen(parameters->parametersList, AaiHelpIndexKeyList[AaiHelpCaVie]);

      }

   }

   return (result);

}

/*

   Function    : aaiCalibrateMineralBias
   Description :
   Inputs      : Nothing.
   Updates     : processParameters =
                 key               =
   Outputs     : Nothing.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 10/15/94 DWP Initial coding.
   Notes       :

*/

int aaiCalibrateMineralBias(void ** processParameters, CARDINAL_16 * key) {

   AaiCalibrateMineralBiasParameters * parameters;
   int                                 result;

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
         aaiSetHelpScreen(parameters->parametersList, AaiHelpIndexKeyList[AaiHelpCaMin]);

      }

   }

   return (result);

}

/*

   Function    : aaiCalibrateStatistics
   Description :
   Inputs      : Nothing.
   Updates     : processParameters =
                 key               =
   Outputs     : Nothing.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 10/15/94 DWP Initial coding.
   Notes       :

*/

int aaiCalibrateStatistics(void ** processParameters, CARDINAL_16 * key) {

   AaiCalibrateStatisticsParameters * parameters;
   int                                result;

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
         aaiSetHelpScreen(parameters->parametersList, AaiHelpIndexKeyList[AaiHelpCaSta]);

      }

   }

   return (result);

}

/*

   Function    : aaiCalibrateGraphics
   Description :
   Inputs      : Nothing.
   Updates     : processParameters =
                 key               =
   Outputs     : Nothing.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 10/15/94 DWP Initial coding.
   Notes       :

*/

int aaiCalibrateGraphics(void ** processParameters, CARDINAL_16 * key) {

   AaiCalibrateGraphicsParameters * parameters;
   int                            result;

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
         aaiSetHelpScreen(parameters->parametersList, AaiHelpIndexKeyList[AaiHelpCaGra]);

      }

   }

   return (result);

}

/*

   Function    : aaiCalibrateCarryOver
   Description :
   Inputs      : Nothing.
   Updates     : processParameters =
                 key               =
   Outputs     : Nothing.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 10/15/94 DWP Initial coding.
   Notes       :

*/

int aaiCalibrateCarryOver(void ** processParameters, CARDINAL_16 * key) {

   AaiCalibrateCarryOverParameters * parameters;
   int                               result;

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
         aaiSetHelpScreen(parameters->parametersList, AaiHelpIndexKeyList[AaiHelpCaCar]);

      }

   }

   return (result);

}

/*

   Function    : aaiCalibratePolynomial
   Description :
   Inputs      : Nothing.
   Updates     : processParameters =
                 key               =
   Outputs     : Nothing.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 10/15/94 DWP Initial coding.
   Notes       :

*/

int aaiCalibratePolynomial(void ** processParameters, CARDINAL_16 * key) {

   AaiCalibratePolynomialParameters * parameters;
   int                                result;

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
         aaiSetHelpScreen(parameters->parametersList, AaiHelpIndexKeyList[AaiHelpCaPol]);

      }

   }

   return (result);

}

/*

   Function    : aaiSetupPrinter
   Description :
   Inputs      : Nothing.
   Updates     : processParameters =
                 key               =
   Outputs     : Nothing.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 10/15/94 DWP Initial coding.
   Notes       :

*/

int aaiSetupPrinter(void ** processParameters, CARDINAL_16 * key) {

   AaiSetupPrinterParameters * parameters;
   int                         result;

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
         aaiSetHelpScreen(parameters->parametersList, AaiHelpIndexKeyList[AaiHelpSePri]);

      }

   }

   return (result);

}

/*

   Function    : aaiSetupOutput
   Description :
   Inputs      : Nothing.
   Updates     : processParameters =
                 key               =
   Outputs     : Nothing.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 10/15/94 DWP Initial coding.
   Notes       :

*/

int aaiSetupOutput(void ** processParameters, CARDINAL_16 * key) {

   AaiSetupOutputParameters * parameters;
   int                        result;

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
         aaiSetHelpScreen(parameters->parametersList, AaiHelpIndexKeyList[AaiHelpSeOut]);

      }

   }

   return (result);

}

/*

   Function    : aaiSetupTemperature
   Description :
   Inputs      : Nothing.
   Updates     : processParameters =
                 key               =
   Outputs     : Nothing.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 10/15/94 DWP Initial coding.
   Notes       :

*/

int aaiSetupTemperature(void ** processParameters, CARDINAL_16 * key) {

   AaiSetupTemperatureParameters * parameters;
   int                             result;

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
         aaiSetHelpScreen(parameters->parametersList, AaiHelpIndexKeyList[AaiHelpSeTem]);

      }

   }

   return (result);

}

/*

   Function    : aaiSetupHeader
   Description :
   Inputs      : Nothing.
   Updates     : processParameters =
                 key               =
   Outputs     : Nothing.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 10/15/94 DWP Initial coding.
   Notes       :

*/

int aaiSetupHeader(void ** processParameters, CARDINAL_16 * key) {

   AaiSetupHeaderParameters * parameters;
   int                        result;

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
         aaiSetHelpScreen(parameters->parametersList, AaiHelpIndexKeyList[AaiHelpSeHea]);

      }

   }

   return (result);

}

/*

   Function    : aaiSetupFooter
   Description :
   Inputs      : Nothing.
   Updates     : processParameters =
                 key               =
   Outputs     : Nothing.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 10/15/94 DWP Initial coding.
   Notes       :

*/

int aaiSetupFooter(void ** processParameters, CARDINAL_16 * key) {

   AaiSetupFooterParameters * parameters;
   int                        result;

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
         aaiSetHelpScreen(parameters->parametersList, AaiHelpIndexKeyList[AaiHelpSeFoo]);

      }

   }

   return (result);

}

/*

   Function    : aaiSetup1stSerialPort
   Description :
   Inputs      : Nothing.
   Updates     : processParameters =
                 key               =
   Outputs     : Nothing.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 10/15/94 DWP Initial coding.
   Notes       :

*/

int aaiSetup1stSerialPort(void ** processParameters, CARDINAL_16 * key) {

   AaiSetup1stSerialPortParameters * parameters;
   int                               result;

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
         aaiSetHelpScreen(parameters->parametersList, AaiHelpIndexKeyList[AaiHelpSe1SP]);

      }

   }

   return (result);

}

/*

   Function    : aaiSetup2ndSerialPort
   Description :
   Inputs      : Nothing.
   Updates     : processParameters =
                 key               =
   Outputs     : Nothing.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 10/15/94 DWP Initial coding.
   Notes       :

*/

int aaiSetup2ndSerialPort(void ** processParameters, CARDINAL_16 * key) {

   AaiSetup2ndSerialPortParameters * parameters;
   int                               result;

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
         aaiSetHelpScreen(parameters->parametersList, AaiHelpIndexKeyList[AaiHelpSe2SP]);

      }

   }

   return (result);

}

/*

   Function    : aaiSetupBarcodeReader
   Description :
   Inputs      : Nothing.
   Updates     : processParameters =
                 key               =
   Outputs     : Nothing.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 10/15/94 DWP Initial coding.
   Notes       :

*/

int aaiSetupBarcodeReader(void ** processParameters, CARDINAL_16 * key) {

   AaiSetupBarcodeReaderParameters * parameters;
   int                               result;

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
         aaiSetHelpScreen(parameters->parametersList, AaiHelpIndexKeyList[AaiHelpSeBar]);

      }

   }

   return (result);

}

/*

   Function    : aaiSetupCycles
   Description :
   Inputs      : Nothing.
   Updates     : processParameters =
                 key               =
   Outputs     : Nothing.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 10/15/94 DWP Initial coding.
   Notes       :

*/

int aaiSetupCycles(void ** processParameters, CARDINAL_16 * key) {

   AaiSetupCyclesParameters * parameters;
   int                        result;

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
         aaiSetHelpScreen(parameters->parametersList, AaiHelpIndexKeyList[AaiHelpSeCyc]);

      }

   }

   return (result);

}

/*

   Function    : aaiSetupPressureLimit
   Description :
   Inputs      : Nothing.
   Updates     : processParameters =
                 key               =
   Outputs     : Nothing.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 10/15/94 DWP Initial coding.
   Notes       :

*/

int aaiSetupPressureLimit(void ** processParameters, CARDINAL_16 * key) {

   AaiSetupPressureLimitParameters * parameters;
   int                               result;

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
         aaiSetHelpScreen(parameters->parametersList, AaiHelpIndexKeyList[AaiHelpSePre]);

      }

   }

   return (result);

}

/*

   Function    : aaiSetupChopperSpeed
   Description :
   Inputs      : Nothing.
   Updates     : processParameters =
                 key               =
   Outputs     : Nothing.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 10/15/94 DWP Initial coding.
   Notes       :

*/

int aaiSetupChopperSpeed(void ** processParameters, CARDINAL_16 * key) {

   AaiSetupChopperSpeedParameters * parameters;
   int                              result;

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
         aaiSetHelpScreen(parameters->parametersList, AaiHelpIndexKeyList[AaiHelpSeCho]);

      }

   }

   return (result);

}

/*

   Function    : aaiHelpIndex
   Description :
   Inputs      : Nothing.
   Updates     : processParameters =
                 key               =
   Outputs     : Nothing.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 08/18/92 DWP Initial coding.
   Notes       :

*/

int aaiHelpIndex(void ** processParameters, CARDINAL_16 * key) {

   AaiHelpIndexParameters * parameters;
   AaiHelpIndexList *       helpIndex;
   AaiHelpIndexList         helpIndexNode;
   AaiHelpTextList *        helpText;
   AaiHelpTextList          helpTextNode;
   CARDINAL_32              totalLines;
   char                     str[1024], word[1024];
   int                      i, strOffset, wordOffset, result;

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

         if (parameters->helpFile == NULL && !parameters->helpLoadedFlag) {

            parameters->helpAvailableFlag = ((parameters->helpFile = fopen("AAI.HLP", "rt")) != NULL);
            LIST_Constructor(sizeof(helpIndexNode), &(parameters->helpList));

         }
         else {

            if (!parameters->helpLoadedFlag) {

               if (fgets(str, sizeof(str) - 1, parameters->helpFile) == NULL) {

                  fclose(parameters->helpFile);
                  parameters->helpLoadedFlag = TRUE;
                  aaiHaltProcess(parameters->parametersList, AaiHelpIndexProcess);

               }
               else {

                  if (str[0] == ':' && str[6] == ':') {

                     STRING_RTrim(str);
                     strcat(str, " ");
                     strncpy(helpIndexNode.indexKey, &(str[1]), sizeof(helpIndexNode.indexKey));
                     strncpy(helpIndexNode.indexDescription, &(str[7]), sizeof(helpIndexNode.indexDescription));
                     LIST_Constructor(sizeof(helpTextNode), &(helpIndexNode.helpTextList));
                     setmem(&(helpTextNode), sizeof(helpTextNode), 0);
                     LIST_Insert(&(helpTextNode), LIST_LAST, helpIndexNode.helpTextList);
                     LIST_Insert(&(helpIndexNode), LIST_LAST, parameters->helpList);

                  }
                  else {

                     LIST_Retrieve(parameters->helpList, LIST_LAST, (void **) &(helpIndex));
                     LIST_Retrieve(helpIndex->helpTextList, LIST_LAST, (void **) &(helpText));
                     wordOffset = 0;

                     for (strOffset = 0; str[strOffset] != '\0'; strOffset++) {

                        if (str[strOffset] == '\n') {

                           str[strOffset] = ' ';

                           if (wordOffset == 0) {

                              helpTextNode.length = 0;
                              LIST_Insert(&(helpTextNode), LIST_LAST, helpIndex->helpTextList);
                              LIST_Insert(&(helpTextNode), LIST_LAST, helpIndex->helpTextList);
                              LIST_Retrieve(helpIndex->helpTextList, LIST_LAST, (void **) &(helpText));

                           }

                        }

                        if (str[strOffset] == '~') {

                           str[strOffset] = '\0';
                           str[strOffset + 1] = '\0';
                           strncat(&(helpText->helpText[helpText->length]), word, sizeof(helpText->helpText) - helpText->length - 1);
                           helpText->length += wordOffset;
                           wordOffset = 0;
                           helpTextNode.length = 0;
                           LIST_Insert(&(helpTextNode), LIST_LAST, helpIndex->helpTextList);
                           LIST_Retrieve(helpIndex->helpTextList, LIST_LAST, (void **) &(helpText));

                        }
                        else {

                           word[wordOffset++] = str[strOffset];
                           word[wordOffset] = '\0';

                           if (isspace(str[strOffset])) {

                              if (helpText->length + wordOffset >= sizeof(helpText->helpText)) {

                                 helpTextNode.length = 0;
                                 LIST_Insert(&(helpTextNode), LIST_LAST, helpIndex->helpTextList);
                                 LIST_Retrieve(helpIndex->helpTextList, LIST_LAST, (void **) &(helpText));

                              }

                              strncat(&(helpText->helpText[helpText->length]), word, sizeof(helpText->helpText) - helpText->length - 1);
                              helpText->length += wordOffset;
                              wordOffset = 0;

                           }

                        }

                     }

                  }

               }

            }
            else {

               aaiSetHelpScreen(parameters->parametersList, AaiHelpIndexKeyList[AaiHelpHeInd]);

               if (parameters->port != NULL) {

                  result = PORT_Activate(parameters->port);

               }
               else {

                  if ((result = PORT_Constructor(parameters->startingRow, parameters->startingColumn, parameters->height, parameters->width, PORT_SINGLE_LINE_BORDER, parameters->colors.primaryColor, parameters->colors.primaryColor, &(parameters->port))) == PORT_NOERR) {

                     TEXT_Set_Cursor_Position(1, 22, parameters->text);
                     TEXT_Print_String("Table of Contents", parameters->text);

                  }

               }

               if (result == EZERO) {

                  LIST_Size(parameters->helpList, &(totalLines));

                  if (parameters->redrawScreenFlag) {

                     sprintf(str, "%-*.*s%10s", parameters->width - 12, parameters->width - 12, "", (parameters->firstRowLine > 1) ? "[More] \x18  " : "");
                     TEXT_Set_Cursor_Position(2, 1, parameters->text);
                     TEXT_Print_String(str, parameters->text);
                     LIST_Retrieve(parameters->helpList, parameters->firstRowLine, (void **) &(helpIndex));

                     for (i = 0; i < 5; i++) {

                        if (helpIndex == NULL) {

                           sprintf(str, "%60s", "");

                        }
                        else {

                           sprintf(str, "%-*.*s", sizeof(helpIndex->indexDescription), sizeof(helpIndex->indexDescription), helpIndex->indexDescription);

                        }

                        TEXT_Set_Cursor_Position(i + 3, 2, parameters->text);
                        TEXT_Print_String(str, parameters->text);
                        LIST_Retrieve(parameters->helpList, LIST_NEXT, (void **) &(helpIndex));

                     }

                     sprintf(str, "%-*.*s%10s", parameters->width - 12, parameters->width - 12, "", (parameters->firstRowLine + 5 <= totalLines) ? "[More] \x19  " : "");
                     TEXT_Set_Cursor_Position(8, 1, parameters->text);
                     TEXT_Print_String(str, parameters->text);
                     parameters->redrawScreenFlag = FALSE;

                  }

                  if (parameters->previousRow != parameters->currentRow) {

                     TEXT_Set_Cursor_Position(parameters->previousRow + 3, 2, parameters->text);
                     TEXT_Set_Text_Color(parameters->colors.primaryColor, parameters->text);
                     LIST_Retrieve(parameters->helpList, parameters->firstRowLine + parameters->previousRow, (void **) &(helpIndex));
                     sprintf(str, "%-*.*s", sizeof(helpIndex->indexDescription), sizeof(helpIndex->indexDescription), helpIndex->indexDescription);
                     TEXT_Print_String(str, parameters->text);
                     parameters->previousRow = parameters->currentRow;

                  }

                  TEXT_Set_Cursor_Position(parameters->currentRow + 3, 2, parameters->text);
                  TEXT_Set_Text_Color(parameters->colors.primaryHighlightColor, parameters->text);
                  LIST_Retrieve(parameters->helpList, parameters->firstRowLine + parameters->currentRow, (void **) &(helpIndex));
                  sprintf(str, "%-*.*s", sizeof(helpIndex->indexDescription), sizeof(helpIndex->indexDescription), helpIndex->indexDescription);
                  TEXT_Print_String(str, parameters->text);
                  TEXT_Set_Text_Color(parameters->colors.primaryColor, parameters->text);

                  switch (*(key)) {

                     case KB_UP :
                     case KB_GRAY_UP :

                        if (parameters->currentRow > 0) {

                           parameters->currentRow--;

                        }
                        else {

                           if (parameters->firstRowLine > 1) {

                              parameters->firstRowLine--;
                              parameters->redrawScreenFlag = TRUE;

                           }

                        }

                        break;

                     case KB_DOWN :
                     case KB_GRAY_DOWN :

                        if (parameters->currentRow < 4 && (parameters->currentRow + parameters->firstRowLine < totalLines)) {

                           parameters->currentRow++;

                        }
                        else {

                           if (parameters->firstRowLine + 5 <= totalLines) {

                              parameters->firstRowLine++;
                              parameters->redrawScreenFlag = TRUE;

                           }

                        }

                        break;

                     case KB_PGUP :
                     case KB_GRAY_PGUP :

                        if (parameters->currentRow > 0) {

                           parameters->currentRow = 0;

                        }

                        parameters->redrawScreenFlag = TRUE;

                        if (parameters->firstRowLine > 5) {

                           parameters->firstRowLine -= 5;

                        }
                        else {

                           parameters->firstRowLine = 1;

                        }

                        break;

                     case KB_PGDN :
                     case KB_GRAY_PGDN :

                        if (parameters->currentRow > 0) {

                           parameters->currentRow = 0;

                        }

                        parameters->redrawScreenFlag = TRUE;

                        if (parameters->firstRowLine + 5 < totalLines) {

                           parameters->firstRowLine += 5;

                        }

                        break;

                     case KB_HOME :
                     case KB_GRAY_HOME :

                        parameters->firstRowLine = 1;
                        parameters->currentRow = 0;
                        parameters->redrawScreenFlag = TRUE;
                        break;

                     case KB_END :
                     case KB_GRAY_END :

                        parameters->firstRowLine = (totalLines > 5) ? totalLines - 4 : 1;
                        parameters->currentRow = (CARDINAL_16) totalLines % 5;
                        parameters->redrawScreenFlag = TRUE;
                        break;

                     case KB_GRAY_ENTER :
                     case KB_ENTER :

                        aaiSetHelpScreen(parameters->parametersList, helpIndex->indexKey);
                        aaiActivateProcess(parameters->parametersList, AaiHelpTopicProcess);
                        break;

                     case KB_ESC :

                        parameters->exitFlag = TRUE;
                        *(key) = 0;
                        break;

                  }

                  if (parameters->exitFlag) {

                     parameters->firstRowLine = 1;
                     parameters->currentRow = 0;
                     parameters->previousRow = 0;
                     parameters->redrawScreenFlag = TRUE;
                     parameters->exitFlag = FALSE;
                     PORT_Destructor(&(parameters->port));
                     aaiHaltProcess(parameters->parametersList, AaiHelpIndexProcess);
                     aaiActivateProcess(parameters->parametersList, AaiMainMenuProcess);

                  }

               }

            }

         }

      }

   }

   return (result);

}

/*

   Function    : aaiHelpAbout
   Description :
   Inputs      : Nothing.
   Updates     : processParameters =
                 key               =
   Outputs     : Nothing.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 08/18/92 DWP Initial coding.
   Notes       :

*/

int aaiHelpAbout(void ** processParameters, CARDINAL_16 * key) {

   AaiHelpAboutParameters * parameters;
   int                      result;

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
         aaiSetHelpScreen(parameters->parametersList, AaiHelpIndexKeyList[AaiHelpHeAbo]);

         if (parameters->port != NULL) {

            result = PORT_Activate(parameters->port);

         }
         else {

            if ((result = PORT_Constructor(parameters->startingRow, parameters->startingColumn, parameters->height, parameters->width, PORT_SINGLE_LINE_BORDER, parameters->colors.primaryColor, parameters->colors.primaryColor, &(parameters->port))) == PORT_NOERR) {

               TEXT_Set_Cursor_Position(2, (parameters->width - strlen(AAI_TITLE_1)) / 2, parameters->text);
               TEXT_Print_String(AAI_TITLE_1, parameters->text);
               TEXT_Set_Cursor_Position(3, (parameters->width - strlen(AAI_TITLE_2)) / 2, parameters->text);
               TEXT_Print_String(AAI_TITLE_2, parameters->text);
               TEXT_Set_Cursor_Position(4, (parameters->width - strlen(AAI_TITLE_3)) / 2, parameters->text);
               TEXT_Print_String(AAI_TITLE_3, parameters->text);
               TEXT_Set_Cursor_Position(5, (parameters->width - strlen(AAI_TITLE_4)) / 2, parameters->text);
               TEXT_Print_String(AAI_TITLE_4, parameters->text);
               TEXT_Set_Cursor_Position(6, (parameters->width - strlen(AAI_TITLE_5)) / 2, parameters->text);
               TEXT_Print_String(AAI_TITLE_5, parameters->text);
               TEXT_Set_Cursor_Position(8, (parameters->width - strlen(AAI_TITLE_6)) / 2, parameters->text);
               TEXT_Print_String(AAI_TITLE_6, parameters->text);

            }

         }

         if (result == EZERO) {

            if (*(key) != 0 && *(key) != KB_F1) {

               if (parameters->port != NULL) {

                  PORT_Destructor(&(parameters->port));

               }

               *(key) = 0;
               aaiHaltProcess(parameters->parametersList, AaiHelpAboutProcess);
               aaiActivateProcess(parameters->parametersList, AaiMainMenuProcess);

            }

         }

      }

   }

   return (result);

}

/*

   Function    : aaiHelpPrint
   Description :
   Inputs      : Nothing.
   Updates     : processParameters =
                 key               =
   Outputs     : Nothing.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 08/18/92 DWP Initial coding.
   Notes       :

*/

int aaiHelpPrint(void ** processParameters, CARDINAL_16 * key) {

   AaiHelpPrintParameters * parameters;
   AaiHelpTextList *        helpText;
   char                     str[256];
   int                      result;

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

         if (!parameters->processInProgressFlag) {

            aaiActivateProcess(parameters->parametersList, AaiYesNoMenuProcess);
            ((AaiYesNoMenuParameters *) parameters->parametersList->processDescriptor[AaiYesNoMenuProcess].processParameters)->startingRow = 9;
            ((AaiYesNoMenuParameters *) parameters->parametersList->processDescriptor[AaiYesNoMenuProcess].processParameters)->startingColumn = 23;
            ((AaiYesNoMenuParameters *) parameters->parametersList->processDescriptor[AaiYesNoMenuProcess].processParameters)->displayMessage = "Is The Printer On-Line And Ready?";
            ((AaiYesNoMenuParameters *) parameters->parametersList->processDescriptor[AaiYesNoMenuProcess].processParameters)->option = 1;
            ((AaiYesNoMenuParameters *) parameters->parametersList->processDescriptor[AaiYesNoMenuProcess].processParameters)->invokingProcess = AaiHelpPrintProcess;
            ((AaiYesNoMenuParameters *) parameters->parametersList->processDescriptor[AaiYesNoMenuProcess].processParameters)->yesSelectedFlag = &(((AaiHelpPrintParameters *) parameters->parametersList->processDescriptor[AaiHelpPrintProcess].processParameters)->printReportFlag);
            parameters->processInProgressFlag = TRUE;
            result = EZERO;

         }
         else {

            if ((int) parameters->printReportFlag != -1) {

               if (!parameters->printReportFlag) {

                  parameters->exitFlag = TRUE;

               }
               else {

                  if (*(key) == KB_ESC) {

                     parameters->exitFlag = TRUE;
                     *(key) = 0;

                  }
                  else {

                     if (parameters->reportFile == NULL) {

                        if (PRINTER_Status(0) != (PRINTER_NOT_BUSY | PRINTER_SELECTED) || (parameters->reportFile = fopen("PRN", "wt")) == NULL) {

                           parameters->exitFlag = TRUE;

                        }
                        else {

                           parameters->pageNumber = 0;
                           parameters->newPageFlag = TRUE;
                           parameters->helpIndex = NULL;

                        }

                     }
                     else {

                        if (parameters->newPageFlag) {

                           if (parameters->pageNumber++ > 0) {

                              fputc(12, parameters->reportFile);

                           }

                           fprintf(parameters->reportFile, "\n%*s%s\n\n", (80 - sizeof(AAI_TITLE_1)) / 2, "", AAI_TITLE_1);
                           parameters->lineNumber = 4;
                           parameters->newPageFlag = FALSE;

                        }

                        if (parameters->lineNumber > 55) {

                           while (parameters->lineNumber++ < 59) {

                              fputc('\n', parameters->reportFile);

                           }

                           parameters->newPageFlag = TRUE;
                           sprintf(str, "- Page %d -", parameters->pageNumber);
                           fprintf(parameters->reportFile, "%*s%s", (80 - strlen(str)) / 2, "", str);

                        }
                        else {

                           if (parameters->helpIndex != NULL) {

                              if (LIST_Retrieve(parameters->helpIndex->helpTextList, ((parameters->firstTextNodeFlag) ? LIST_FIRST : LIST_NEXT), (void **) &(helpText)) != LIST_NOERR) {

                                 parameters->helpIndex = NULL;

                              }
                              else {

                                 fprintf(parameters->reportFile, "%10s%s\n", "", helpText->helpText);
                                 parameters->lineNumber++;

                              }

                              parameters->firstTextNodeFlag = FALSE;

                           }
                           else {

                              if (LIST_Retrieve(parameters->indexParameters->helpList, ((parameters->firstIndexNodeFlag) ? LIST_FIRST : LIST_NEXT), (void **) &(parameters->helpIndex)) == LIST_NOERR) {

                                 sprintf(str, "%.60s", parameters->helpIndex->indexDescription);
                                 fprintf(parameters->reportFile, "\n%s\n\n", str);
                                 parameters->lineNumber += 3;
                                 parameters->firstIndexNodeFlag = FALSE;
                                 parameters->firstTextNodeFlag = TRUE;

                              }
                              else {

                                 while (parameters->lineNumber++ < 59) {

                                    fputc('\n', parameters->reportFile);

                                 }

                                 sprintf(str, "- Page %d -", parameters->pageNumber);
                                 fprintf(parameters->reportFile, "%*s%s", (80 - strlen(str)) / 2, "", str);
                                 fputc(12, parameters->reportFile);
                                 parameters->exitFlag = TRUE;

                              }

                           }

                        }

                     }

                  }

               }

            }

         }

         if (parameters->exitFlag) {

            fclose(parameters->reportFile);
            parameters->processInProgressFlag = FALSE;
            parameters->printReportFlag = -1;
            parameters->firstIndexNodeFlag = TRUE;
            parameters->exitFlag = FALSE;
            aaiHaltProcess(parameters->parametersList, AaiHelpPrintProcess);
            aaiActivateProcess(parameters->parametersList, AaiMainMenuProcess);

         }

      }

   }

   return (result);

}

/*

   Function    : aaiHelpTopic
   Description :
   Inputs      : Nothing.
   Updates     : processParameters =
                 key               =
   Outputs     : Nothing.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 08/18/92 DWP Initial coding.
   Notes       :

*/

int aaiHelpTopic(void ** processParameters, CARDINAL_16 * key) {

   AaiHelpTopicParameters * parameters;
   AaiHelpTextList *        helpText;
   CARDINAL_32              totalLines;
   char                     str[256];
   int                      i, result;

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

         if (parameters->port != NULL) {

            result = PORT_Activate(parameters->port);

         }
         else {

            result = PORT_Constructor(parameters->startingRow, parameters->startingColumn, parameters->height, parameters->width, PORT_SINGLE_LINE_BORDER, parameters->colors.primaryColor, parameters->colors.primaryColor, &(parameters->port));
            result = LIST_Retrieve(parameters->indexParameters->helpList, LIST_FIRST, (void **) &(parameters->helpIndex));

            while (strncmp(parameters->helpIndex->indexKey, parameters->key, sizeof(parameters->helpIndex->indexKey)) != 0) {

               if (LIST_Retrieve(parameters->indexParameters->helpList, LIST_NEXT, (void **) &(parameters->helpIndex)) != LIST_NOERR) {

                  parameters->exitFlag = TRUE;
                  break;

               }

            }

         }

         if (result == EZERO) {

            if (parameters->redrawScreenFlag) {

               TEXT_Set_Cursor_Position(1, (parameters->width - strlen(parameters->helpIndex->indexDescription)) / 2, parameters->text);
               sprintf(str, "%-*.*s", sizeof(parameters->helpIndex->indexDescription), strlen(parameters->helpIndex->indexDescription), parameters->helpIndex->indexDescription);
               TEXT_Print_String(str, parameters->text);
               TEXT_Set_Cursor_Position(2, 1, parameters->text);
               sprintf(str, "%-*.*s%10s", parameters->width - 12, parameters->width - 12, "", (parameters->firstRowLine > 1) ? "[More] \x18  " : "");
               TEXT_Print_String(str, parameters->text);
               TEXT_Set_Cursor_Position(8, 1, parameters->text);
               LIST_Size(parameters->helpIndex->helpTextList, &(totalLines));
               sprintf(str, "%-*.*s%10s", parameters->width - 12, parameters->width - 12, "", (parameters->firstRowLine + 5 <= totalLines) ? "[More] \x19  " : "");
	            TEXT_Print_String(str, parameters->text);

               LIST_Retrieve(parameters->helpIndex->helpTextList, parameters->firstRowLine, (void **) &(helpText));

               for (i = 0; i < 5; i++) {

                  TEXT_Set_Cursor_Position(i + 3, 4, parameters->text);
                  sprintf(str, "%-*.*s", sizeof(helpText->helpText), helpText->length, helpText->helpText);
                  TEXT_Print_String(str, parameters->text);

                  if (LIST_Retrieve(parameters->helpIndex->helpTextList, LIST_NEXT, (void **) &(helpText)) != LIST_NOERR) {

                     break;

                  }

               }

               parameters->redrawScreenFlag = FALSE;

	         }

            switch (*(key)) {

               case KB_UP :
               case KB_GRAY_UP :

                  if (parameters->firstRowLine > 1) {

                     parameters->firstRowLine--;
                     parameters->redrawScreenFlag = TRUE;

                  }

                  break;

               case KB_DOWN :
               case KB_GRAY_DOWN :

                  LIST_Size(parameters->helpIndex->helpTextList, &(totalLines));

                  if (parameters->firstRowLine + 5 <= totalLines) {

                     parameters->firstRowLine++;
                     parameters->redrawScreenFlag = TRUE;

                  }

                  break;

               case KB_HOME :
               case KB_GRAY_HOME :

                  parameters->firstRowLine = 1;
                  parameters->redrawScreenFlag = TRUE;
                  break;

               case KB_ESC :

                  parameters->exitFlag = TRUE;
		            break;

            }

            *(key) = 0;

         }

         if (parameters->exitFlag) {

            parameters->firstRowLine = 1;
            parameters->redrawScreenFlag = TRUE;
            parameters->exitFlag = FALSE;
            PORT_Destructor(&(parameters->port));
            aaiHaltProcess(parameters->parametersList, AaiHelpTopicProcess);

         }

      }

   }

   return (result);

}
