/* File        : DEBUG3B.C
   Module      : DEBUG
   System      : None
   Description : An enhanced version of free.
   Modified    : 08/10/90 DWP Created.
   Notes       :
*/

#include <alloc.h>
#include <errno.h>

#include "debug0.h"

/* Procedure   : _DEBUG_Free
   Description : This version of free removes an element from the heap allocation record and then records the event in the heap
                 allocation report file.
   Inputs      : Block = The block that is to be returned to the heap.
                 File  = The source file of the call to free.
                 Line  = The source line number in the above file.
   Updates     : Nothing.
   Outputs     : Nothing.
   Returns     : Nothing.
   Modified    : 08/10/90 DWP Initial coding.
   Notes       :
*/

void _DEBUG_Free(void * Block, char * File, unsigned int Line) {

   FILE *                          fp;
   _DEBUG_Heap_Allocation_Record * rec;
   int                             position = -1;
   BOOLEAN                         close_flag;
   CARDINAL_32                     list_position;

   errno = EZERO;

   /* Attempt to open the heap allocation report file. */

   if ((fp = fopen(_DEBUG_Heap_Allocation_Report_File, "ab")) != NULL) {

      close_flag = TRUE;

   }
   else {

      fp = stdprn;
      close_flag = FALSE;

   }

   /* Determine if the specified block pointer is valid. */

   LIST_Find(_DEBUG_Heap_Allocation_List, _DEBUG_Heap_Allocation_Key_Compare, Block, (void **) &rec, &list_position);
   if (rec != NULL) {

      free(Block);

   }

   _DEBUG_Write_Output(DEBUG_HEAP_ALLOCATION, File, Line, errno, fp);
   fprintf(fp, "%10sFREE    - Addr: %Fp  Size: %u%s\n", "", ((_DEBUG_Heap_Allocation_Record *) rec)->Memory_Address, ((_DEBUG_Heap_Allocation_Record *) rec)->Size, (position != -1) ? "" : "\n          ERROR   - Attempted to free a block not previously allocated.");

   if (position != -1) {

      LIST_Delete(position, _DEBUG_Heap_Allocation_List, NULL);

   }

   /* Close the output file only if it isn't stdprn. */

   if (close_flag) {

      fclose(fp);

   }

}