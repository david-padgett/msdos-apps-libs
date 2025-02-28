/* File        : DEBUG3.C
   Module      : DEBUG
   System      : None
   Description : An enhanced version of malloc.
   Modified    : 08/10/90 DWP Created.
   Notes       :
*/

#include <alloc.h>
#include <errno.h>
#include <memory.h>
#include <string.h>

#include "debug0.h"
#include "Standard\standard.h"

/* Function    : _DEBUG_Malloc
   Description : This version of malloc adds to the heap allocation list if memory was successfully allocated from the heap.  The
                 information about the malloc is then added to the heap allocation report file.
   Inputs      : Size = The actual parameter for malloc.
                 File = The source file of the call to malloc.
                 Line = The source line number in the above file.
   Updates     : Nothing.
   Outputs     : Nothing.
   Returns     : The result of the call to malloc.
   Modified    : 08/10/90 DWP Initial coding.
   Notes       :
*/

void * _DEBUG_Malloc(size_t Size, char *File, unsigned int Line) {

   FILE *                        fp;
   _DEBUG_Heap_Allocation_Record rec;
   BOOLEAN                       close_flag;

   errno = EZERO;
   setmem(&rec, sizeof(rec), 0);

   /* Open the heap allocation report file.  */

   if ((fp = fopen(_DEBUG_Heap_Allocation_Report_File, "at")) != NULL) {

      close_flag = TRUE;

   }
   else {

      fp = stdprn;
      close_flag = FALSE;

   }

   /* Request the memory and initialize the heap allocation record. */

   rec.Memory_Address = malloc(Size);
   rec.Size = Size;
   strcpy(rec.Source_File, File);
   rec.Source_Line = Line;

   if (rec.Memory_Address != NULL) {

      LIST_Insert(&rec, LIST_LAST, _DEBUG_Heap_Allocation_List);
   }

   /* Save the heap allocation record information to disk and close the heap allocation report file. */

   _DEBUG_Write_Output(DEBUG_HEAP_ALLOCATION, rec.Source_File, rec.Source_Line, errno, fp);
   fprintf(fp, "%10sMALLOC  - Addr: %Fp  Sz: %u%s\n", "", rec.Memory_Address, rec.Size, (rec.Memory_Address != NULL) ? "" : "\n          ERROR - Unable to allocate memory.");

   /* Close the output file only if it isn't stdprn. */

   if (close_flag) {

      fclose(fp);

   }

   return (rec.Memory_Address);

}
