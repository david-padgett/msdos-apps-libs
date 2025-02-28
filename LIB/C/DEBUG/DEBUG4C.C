/* File        : DEBUG4C.C
   Module      : DEBUG
   System      : None
   Description : An enhanced version of close.
   Modified    : 08/13/90 DWP Created.
   Notes       :
*/

#include <errno.h>
#include <io.h>

#include "debug0.h"

/* Function    : _DEBUG_Close
   Description : This version of close removes an element from the open file list and then records the event in the open file
                 report file.
   Inputs      : Handle = The file handle to close.
                 File   = The source file of the call to close.
                 Line   = The source line number of the above file.
   Updates     : Nothing.
   Outputs     : Nothing.
   Returns     : The return value of close.
   Modified    : 08/13/90 DWP Initial coding.
   Notes       :
*/

int _DEBUG_Close(int Handle, char * File, unsigned int Line) {

   FILE *                    fp;
   _DEBUG_Open_File_Record * rec;
   int                       position = -1, result = EOF;
   BOOLEAN                   close_flag;
   CARDINAL_32               list_position;

   errno = EZERO;

   if ((fp = fopen(_DEBUG_Open_File_Report_File, "at")) != NULL) {

      close_flag = TRUE;

   }
   else {

      fp = stdprn;
      close_flag = FALSE;

   }

   LIST_Find(_DEBUG_Open_File_List, _DEBUG_Open_File_Key_Compare, &Handle, (void **) &rec, &list_position);
   if (rec != NULL) {

      result = close(Handle);

   }

   _DEBUG_Write_Output(DEBUG_OPEN_FILE, File, Line, errno, fp);
   fprintf(fp, "%10sCLOSE - Fh: %5d  Pn: %s  Ac: %5d Md: %5u%s\n", "", Handle, (rec) ? ((_DEBUG_Open_File_Record *) rec)->Pathname : "", (rec) ? ((_DEBUG_Open_File_Record *) rec)->Access : 0, (rec) ? ((_DEBUG_Open_File_Record *) rec)->Mode : 0, (result != -1) ? "" : "\n          ERROR  - Unable to close file.");

   if (position != -1) {

      LIST_Delete(position, _DEBUG_Open_File_List, NULL);

   }

   if (close_flag) {

      fclose(fp);

   }

   return (result);

}
