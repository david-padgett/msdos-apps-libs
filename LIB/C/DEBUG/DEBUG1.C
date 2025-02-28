/* File        : DEBUG1.C
   Module      : DEBUG
   System      : None
   Description : Memory/File management debugging aids for C.
   Modified    : 08/09/90 DWP Created.
   Notes       :
*/

#include <dos.h>
#include <errno.h>
#include <io.h>
#include <stdlib.h>
#include <string.h>

#include "KB\kb.h"
#include "Standard\standard.h"
#include "String\string.h"

#include "debug0.h"

/* Procedure   : DEBUG_Constructor
   Description : Initializes the DEBUG module, creates the report files, and resisters the debug destructor function with the exit
		 code.
   Inputs      : File       = The source file of the call to the constructor.
		 Line       = The source line number of the above file.
		 Rpt_File_1 = A user-defined heap allocation report file name.  If this value is zero length string, then the
			      default file name is used.
		 Rpt_File_2 = A user-defined open stream report file name.  If this value is a zero-length string, then the default
			      file name is used.
		 Rpt_File_3 = A user-defined open file report file name.  If this value is zero-length string, then the default
			      file name is used.
   Updates     : Nothing.
   Outputs     : Nothing.
   Returns     : Nothing.
   Modified    : 08/09/90 DWP Initial coding.
		 08/13/90 DWP Added the code for the open file report.
   Notes       : 1) If the two report files are successfully opened, this function will register the result of the atexit call in
		    the two report files.
*/

int DEBUG_Constructor(char * File, int Line, char * Rpt_File_1, char * Rpt_File_2, char * Rpt_File_3) {

   FILE * fp_1;
   FILE * fp_2;
   FILE * fp_3;
   char   title[81];
   int    i, result = EZERO;

   /* If the user specified an alternate DEBUG heap allocation report file name, use it. */

   if (Rpt_File_1[0] != '\0') {

      sprintf(_DEBUG_Heap_Allocation_Report_File, "%.*s", MAXPATH, Rpt_File_1);

   }

   /* If the user specified an alternate DEBUG open stream report file name, use it. */

   if (Rpt_File_2[0] != '\0') {

      if (strncmp(Rpt_File_1, Rpt_File_2, MAXPATH) == 0) {

         result = EINVAL;

      }
      else {

	 sprintf(_DEBUG_Open_Stream_Report_File, "%.*s", MAXPATH, Rpt_File_2);

      }

   }

   /* If the user specified an alternate DEBUG open file report file name, use it. */

   if (Rpt_File_3[0] != '\0') {

      if (strncmp(Rpt_File_1, Rpt_File_3, MAXPATH) == 0 && strncmp(Rpt_File_2, Rpt_File_3, MAXPATH) == 0) {

         result = EINVAL;

      }
      else {

	 sprintf(_DEBUG_Open_File_Report_File, "%.*s", MAXPATH, Rpt_File_3);

      }

   }

   /* Initialize errno and the two DEBUG lists that are maintained throughout the life-span of the DEBUG module. */

   errno = EZERO;
   LIST_Constructor(sizeof(_DEBUG_Heap_Allocation_Record), &_DEBUG_Heap_Allocation_List);
   LIST_Constructor(sizeof(_DEBUG_Open_Stream_Record), &_DEBUG_Open_Stream_List);
   LIST_Constructor(sizeof(_DEBUG_Open_File_Record), &_DEBUG_Open_File_List);

   /* Attempt to open and write to the standard DEBUG module report file. */

   fp_1 = fopen(_DEBUG_Heap_Allocation_Report_File, "wt");
   fp_2 = fopen(_DEBUG_Open_Stream_Report_File, "wt");
   fp_3 = fopen(_DEBUG_Open_File_Report_File, "wt");

   if (fp_1 != NULL && fp_2 != NULL && fp_3 != NULL) {

      /* Register the destructor for the DEBUG module. */

      result = atexit(DEBUG_Destructor);

      /* Create the title for the first report, then record the result of the call to atexit. */

      sprintf(title, "%s %s Report", _DEBUG_Debug_Text, _DEBUG_Heap_Allocation_Text);
      fprintf(fp_1, "\n%s\n", STRING_Center(80, title));

      for (i = 0; i < 80; i++) {

	 fputc('-', fp_1);

      }

      fputc('\n', fp_1);
      _DEBUG_Write_Output(DEBUG_HEAP_ALLOCATION, File, Line, result, fp_1);
      fprintf(fp_1, "%10s%s %s (%s) File successfully created.\n", "", _DEBUG_Debug_Text, _DEBUG_Heap_Allocation_Text, _DEBUG_Heap_Allocation_Report_File);

      /* Create the title for the second report, then register the result of the call to atexit. */

      sprintf(title, "%s %s Report", _DEBUG_Debug_Text, _DEBUG_Open_Stream_Text);
      fprintf(fp_2, "\n%s\n", STRING_Center(80, title));

      for (i = 0; i < 80; i++) {

	 fputc('-', fp_2);

      }

      fputc('\n', fp_2);
      _DEBUG_Write_Output(DEBUG_OPEN_STREAM, File, Line, result, fp_2);
      fprintf(fp_2, "%10s%s %s (%s) File successfully created.\n", "", _DEBUG_Debug_Text, _DEBUG_Open_Stream_Text, _DEBUG_Open_Stream_Report_File);

      /* Create the title for the third report, then register the result of the call to atexit. */

      sprintf(title, "%s %s Report", _DEBUG_Debug_Text, _DEBUG_Open_File_Text);
      fprintf(fp_3, "\n%s\n", STRING_Center(80, title));

      for (i = 0; i < 80; i++) {

         fputc('-', fp_3);

      }

      fputc('\n', fp_3);
      _DEBUG_Write_Output(DEBUG_OPEN_FILE, File, Line, result, fp_3);
      fprintf(fp_3, "%10s%s %s (%s) File successfully created.\n", "", _DEBUG_Debug_Text, _DEBUG_Open_File_Text, _DEBUG_Open_File_Report_File);

   }
   else {

      /* Unable to open all of the report files. */

      result = errno;
      printf(_DEBUG_Open_Error_Text, _DEBUG_Debug_Text, result, (fp_1 != NULL) ? _DEBUG_Heap_Allocation_Report_File : ((fp_2 != NULL) ? _DEBUG_Open_Stream_Report_File : _DEBUG_Open_File_Report_File));
      KB_Read();

   }

   /* Close the report files. */

   if (fp_3 != NULL) {

      fclose(fp_3);

   }

   if (fp_2 != NULL) {

      fclose(fp_2);

   }

   if (fp_1 != NULL) {

      fclose(fp_1);

   }

   return (result);

}

/* Function    : _DEBUG_Heap_Allocation_Summary
   Description : Reports the status of the heap allocation list after a normal program termination (a call to exit).
   Inputs      : Data  = An element in the heap allocation list.
                 Parms = A record of parameters of type _DEBUG_Parms_Record.
   Updates     : Nothing.
   Outputs     : Nothing.
   Returns     : EZERO is always returned.
   Modified    : 08/10/90 DWP Initial coding.
   Notes       : 1) This is only called if there are still elements in the heap allocation list.
*/

int _DEBUG_Heap_Allocation_Summary(void * Data, void * Parms, CARDINAL_32 Position) {

   static unsigned long size = 0;
   static unsigned int  count = 0;

   (void) Position;

   /* Put some room between the last line of the main report and the summary. */

   if (count == 0) {

      fprintf(((_DEBUG_Parms_Record *) Parms)->Fp, "\n\nSummary of Heap Allocation.\n\n");

   }

   /* Print the current element that wasn't returned to the heap before exiting. */

   fprintf(((_DEBUG_Parms_Record *) Parms)->Fp, "Addr: %Fp  Sz: %u  ", ((_DEBUG_Heap_Allocation_Record *) Data)->Memory_Address, ((_DEBUG_Heap_Allocation_Record *) Data)->Size);
   fprintf(((_DEBUG_Parms_Record *) Parms)->Fp, "Src Fn: %-12.12s  Src Ln: %u\n", ((_DEBUG_Heap_Allocation_Record *) Data)->Source_File, ((_DEBUG_Heap_Allocation_Record *) Data)->Source_Line);

   /* Attempt Free the memory. */

   free(((_DEBUG_Heap_Allocation_Record *) Data)->Memory_Address);

   /* Keep track of the total memory that wasn't returned to the heap. */

   size += (long) ((_DEBUG_Heap_Allocation_Record *) Data)->Size;

   /* Print the summary if there are no more list elements. */

   if (++count == ((_DEBUG_Parms_Record *) Parms)->Elements) {

      fprintf(((_DEBUG_Parms_Record *) Parms)->Fp, "\nTotal blocks not freed: %u\nTotal memory not freed: %lu\n", count, size);

   }

   return (EZERO);

}

/* Function    : _DEBUG_Open_Stream_Summary
   Description : Reports the status of the open stream list after a normal program termination (a call to exit).
   Inputs      : Data  = An element in the open stream list.
                 Parms = A record of parameters of type _DEBUG_Parms_Record.
   Updates     : Nothing.
   Outputs     : Nothing.
   Returns     : EZERO is always returned.
   Modified    : 08/10/90 DWP Initial coding.
   Notes       : 1) This is only called if there are still elements in the open stream list.
*/

int _DEBUG_Open_Stream_Summary(void * Data, void * Parms, CARDINAL_32 Position) {

   static unsigned int count = 0;

   (void) Position;

   /* Put some room between the last line of the main report and the summary. */

   if (count == 0) {

      fprintf(((_DEBUG_Parms_Record *) Parms)->Fp, "\n\nSummary of Open Streams.\n\n");

   }

   /* Display the current stream that wasn't closed before exiting. */

   fprintf(((_DEBUG_Parms_Record *) Parms)->Fp, "Fp: %Fp  Fn: %-12.12s  Md: %-s  ", ((_DEBUG_Open_Stream_Record *) Data)->File_Pointer, ((_DEBUG_Open_Stream_Record *) Data)->File_Name, ((_DEBUG_Open_Stream_Record *) Data)->Mode);
   fprintf(((_DEBUG_Parms_Record *) Parms)->Fp, "Src Fn: %-12.12s  Src Ln: %u\n", ((_DEBUG_Open_Stream_Record *) Data)->Source_File, ((_DEBUG_Open_Stream_Record *) Data)->Source_Line);

   /* Attempt to close the stream. */

   fclose(((_DEBUG_Open_Stream_Record *) Data)->File_Pointer);

   /* Print the summary if there are no more list elements. */

   if (++count == ((_DEBUG_Parms_Record *) Parms)->Elements) {

      fprintf(((_DEBUG_Parms_Record *) Parms)->Fp, "\nTotal streams not closed: %u\n", count);

   }

   return (EZERO);

}

/* Function    : _DEBUG_Open_File_Summary
   Description : Reports the status of the open file list after a normal program termination (a call to exit).
   Inputs      : Data  = An element in the open file list.
                 Parms = A record of parameters of type _DEBUG_Parms_Record.
   Updates     : Nothing.
   Outputs     : Nothing.
   Returns     : EZERO is always returned.
   Modified    : 08/13/90 DWP Initial coding.
   Notes       : 1) This is only called if there are still elements in the open file list.
*/

int _DEBUG_Open_File_Summary(void * Data, void * Parms, CARDINAL_32 Position) {

   static unsigned int count = 0;

   (void) Position;
   /* Put some room between the last line of the main report and the summary. */

   if (count == 0) {

      fprintf(((_DEBUG_Parms_Record *) Parms)->Fp, "\n\nSummary of Open Files.\n\n");

   }

   /* Display the current stream that wasn't closed before exiting. */

   fprintf(((_DEBUG_Parms_Record *) Parms)->Fp, "Fh: %5d  Pn: %-.*s  Ac: %5d  Md: %5d ", ((_DEBUG_Open_File_Record *) Data)->File_Handle, MAXPATH, ((_DEBUG_Open_File_Record *) Data)->Pathname, ((_DEBUG_Open_File_Record *) Data)->Access, ((_DEBUG_Open_File_Record *) Data)->Mode);
   fprintf(((_DEBUG_Parms_Record *) Parms)->Fp, "Src Fn: %-12.12s  Src Ln: %u\n", ((_DEBUG_Open_File_Record *) Data)->Source_File, ((_DEBUG_Open_File_Record *) Data)->Source_Line);

   /* Attempt to close the file. */

   close(((_DEBUG_Open_File_Record *) Data)->File_Handle);

   /* Print the summary if there are no more list elements. */

   if (++count == ((_DEBUG_Parms_Record *) Parms)->Elements) {

      fprintf(((_DEBUG_Parms_Record *) Parms)->Fp, "\nTotal files not closed: %u\n", count);

   }

   return (EZERO);

}

/* Procedure   : DEBUG_Destructor
   Description : The termination procedure for the DEBUG module.  This procedure is registered with atexit in the DEBUG_Constructor
                 function.
   Inputs      : Nothing.
   Updates     : Nothing.
   Outputs     : Nothing.
   Returns     : Nothing.
   Modified    : 08/09/90 DWP Initial coding.
   Notes       :
*/

void DEBUG_Destructor(void) {

   _DEBUG_Parms_Record parms;
   BOOLEAN             close_flag;

   /* Report on the status of the heap allocation list and then destroy the list. */

   errno = EZERO;
   parms.Fp = fopen(_DEBUG_Heap_Allocation_Report_File, "at");
   close_flag = TRUE;

   if (parms.Fp == NULL) {

      parms.Fp = stdprn;
      close_flag = FALSE;

   }

   LIST_Size(_DEBUG_Heap_Allocation_List, &parms.Elements);
   LIST_Iterate(_DEBUG_Heap_Allocation_List, _DEBUG_Heap_Allocation_Summary, &parms);
   fprintf(parms.Fp, "\n\n<End Of Report>\n");

   if (close_flag) {

      fclose(parms.Fp);

   }

   LIST_Destructor(&_DEBUG_Heap_Allocation_List);

   /* Report on the status of the open stream list and then destroy the list. */

   errno = EZERO;
   parms.Fp = fopen(_DEBUG_Open_Stream_Report_File, "at");
   close_flag = TRUE;

   if (parms.Fp == NULL) {

      parms.Fp = stdprn;
      close_flag = FALSE;

   }

   LIST_Size(_DEBUG_Open_Stream_List, &parms.Elements);
   LIST_Iterate(_DEBUG_Open_Stream_List, _DEBUG_Open_Stream_Summary, &parms);
   fprintf(parms.Fp, "\n\n<End Of Report>\n");

   if (close_flag) {

      fclose(parms.Fp);

   }

   LIST_Destructor(&_DEBUG_Open_Stream_List);

   /* Report on the status of the open file list and then destroy the list. */

   errno = EZERO;
   parms.Fp = fopen(_DEBUG_Open_File_Report_File, "at");
   close_flag = TRUE;

   if (parms.Fp == NULL) {

      parms.Fp = stdprn;
      close_flag = FALSE;

   }

   LIST_Size(_DEBUG_Open_File_List, &parms.Elements);
   LIST_Iterate(_DEBUG_Open_File_List, _DEBUG_Open_File_Summary, &parms);
   fprintf(parms.Fp, "\n\n<End Of Report>\n");

   if (close_flag) {

      fclose(parms.Fp);

   }

   LIST_Destructor(&_DEBUG_Open_File_List);

}
