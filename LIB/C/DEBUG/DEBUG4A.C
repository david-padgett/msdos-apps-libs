/* File        : DEBUG4A.C
   Module      : DEBUG
   System      : None
   Description : An enhanced version of fclose.
   Modified    : 08/10/90 DWP Created.
   Notes       :
*/

#include <errno.h>

#include "debug0.h"

/* Function    : _DEBUG_Fclose
   Description : This version of fclose removes an element from the open stream list and then records the event in the open stream
                 report file.
   Inputs      : File_Pointer = The stream to close.
                 File         = The source file of the call to fclose.
                 Line         = The source line number of the above file.
   Updates     : Nothing.
   Outputs     : Nothing.
   Returns     : The return value of fclose.
   Modified    : 08/10/90 DWP Initial coding.
   Notes       :
*/

int _DEBUG_Fclose(FILE * File_Pointer, char * File, unsigned int Line) {

   FILE *                      fp;
   _DEBUG_Open_Stream_Record * rec;
   int                         position = -1, result = EOF;
   BOOLEAN                     close_flag;
   CARDINAL_32                 list_position;

   errno = EZERO;

   if ((fp = fopen(_DEBUG_Open_Stream_Report_File, "at")) != NULL) {

      close_flag = TRUE;

   }
   else {

      fp = stdprn;
      close_flag = FALSE;

   }

   LIST_Find(_DEBUG_Open_Stream_List, _DEBUG_Open_Stream_Key_Compare, File_Pointer, (void **) &rec, &list_position);
   if (rec != NULL) {

      result = fclose(File_Pointer);

   }

   _DEBUG_Write_Output(DEBUG_OPEN_STREAM, File, Line, errno, fp);
   fprintf(fp, "%10sFCLOSE - Fp: %Fp  Fn: %s  Md: %s%s\n", "", File_Pointer, (rec) ? ((_DEBUG_Open_Stream_Record *) rec)->File_Name : "", (rec) ? ((_DEBUG_Open_Stream_Record *) rec)->Mode : "", (result == EZERO) ? "" : "\n          ERROR  - Unable to close file.");

   if (position != -1) {

      LIST_Delete(position, _DEBUG_Open_Stream_List, NULL);

   }

   if (close_flag) {

      fclose(fp);

   }

   return (result);

}
