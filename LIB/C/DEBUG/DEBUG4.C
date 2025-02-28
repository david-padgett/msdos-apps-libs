/* File        : DEBUG4.C
   Module      : DEBUG
   System      : None
   Description : An alternate version of fopen.
   Modified    : 08/10/90 DWP Created.
   Notes       :
*/

#include <errno.h>
#include <memory.h>
#include <string.h>

#include "debug0.h"

/* Function    : _DEBUG_Fopen
   Description : This version of fopen adds an element to the open stream list and then records the action in the open stream report file.
   Inputs      : File_Name = The name of the file to open.
                 Mode      = The mode in which to open the file.
                 File      = The source file of the call to fopen.
                 Line      = The source line number of the above file.
   Updates     : Nothing.
   Outputs     : Nothing.
   Returns     : The result of fopen.
   Modified    : 08/10/90 DWP Initial coding.
   Notes       :
*/

FILE * _DEBUG_Fopen(char * File_Name, char * Mode, char * File, unsigned int Line) {

   FILE *                    fp;
   _DEBUG_Open_Stream_Record rec;
   BOOLEAN                   close_flag;

   errno = EZERO;
   setmem(&rec, sizeof(rec), 0);

   /* Attempt to open the open stream report file. */

   if ((fp = fopen(_DEBUG_Open_Stream_Report_File, "at")) != NULL) {

      close_flag = TRUE;

   }
   else {

      fp = stdprn;
      close_flag = FALSE;

   }

   /* Attempt to open the file.  Initialize the rest of the open stream record. */

   rec.File_Pointer = fopen(File_Name, Mode);
   strncpy(rec.File_Name, File_Name, MAXPATH - 1);
   rec.File_Name[MAXPATH] = '\0';
   strncpy(rec.Mode, Mode, 3);
   rec.Mode[4] = '\0';
   strcpy(rec.Source_File, File);
   rec.Source_Line = Line;

   if (rec.File_Pointer != NULL) {

      LIST_Insert(&rec, LIST_LAST, _DEBUG_Open_Stream_List);

   }

   _DEBUG_Write_Output(DEBUG_OPEN_STREAM, File, Line, errno, fp);
   fprintf(fp, "%10sFOPEN  - Fp: %Fp  Fn: %s  Md: %s%s\n", "", rec.File_Pointer, rec.File_Name, rec.Mode, (rec.File_Pointer != NULL) ? "" : "\n          ERROR  - Unable to open the specified file.");

   if (close_flag) {

      fclose(fp);

   }

   return (rec.File_Pointer);

}
