/* File        : DEBUG4.C
   Module      : DEBUG
   System      : None
   Description : An alternate version of open.
   Modified    : 08/10/90 DWP Created.
   Notes       :
*/

#include <errno.h>
#include <io.h>
#include <memory.h>
#include <string.h>

#include "debug0.h"

/* Function    : _DEBUG_Open
   Description : This version of fopen adds an element to the open file list and then records the action in the open file report
                 file.
   Inputs      : Pathname = The parameter pathname required by open.
                 Access   = The parameter access required by open.
                 Mode     = The optional mode parameter specified by open.
                 File     = The source file of the call to open.
                 Line     = The source line number in the above file.
   Updates     : Nothing.
   Outputs     : Nothing.
   Returns     : The result of open.
   Modified    : 08/13/90 DWP Initial coding.
   Notes       :
*/

int _DEBUG_Open(const char * Pathname, int Access, unsigned int Mode, char * File, unsigned int Line) {

   FILE *                  fp;
   _DEBUG_Open_File_Record rec;
   BOOLEAN                 close_flag;

   errno = EZERO;
   setmem(&rec, sizeof(rec), 0);

   /* Attempt to open the open file report file. */

   if ((fp = fopen(_DEBUG_Open_File_Report_File, "at")) != NULL) {

      close_flag = TRUE;

   }
   else {

      fp = stdprn;
      close_flag = FALSE;

   }

   /* Attempt to open the file.  Initialize the rest of the open file record. */

   if (Mode != 0) {

      rec.File_Handle = open(Pathname, Access, Mode);

   }
   else {

      rec.File_Handle = open(Pathname, Access);

   }

   strncpy(rec.Pathname, Pathname, MAXPATH - 1);
   rec.Pathname[MAXPATH] = '\0';
   rec.Access = Access;
   rec.Mode = Mode;
   strcpy(rec.Source_File, File);
   rec.Source_Line = Line;

   if (rec.File_Handle != -1) {

      LIST_Insert(&rec, LIST_LAST, _DEBUG_Open_File_List);

   }

   _DEBUG_Write_Output(DEBUG_OPEN_FILE, File, Line, errno, fp);
   fprintf(fp, "%10sOPEN  - Fh: %5d  Pn: %s  Ac: %5d  Md: %5d%s\n", "", rec.File_Handle, rec.Pathname, rec.Access, rec.Mode, (rec.File_Handle != -1) ? "" : "\n          ERROR  - Unable to open the specified file.");

   if (close_flag) {

      fclose(fp);

   }

   return (rec.File_Handle);

}
