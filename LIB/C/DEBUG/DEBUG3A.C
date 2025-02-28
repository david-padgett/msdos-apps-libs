/* File        : DEBUG3A.C
   Module      : DEBUG
   System      : None
   Description : An enhanced version of realloc.
   Modified    : 08/10/90 DWP Created.
   Notes       :
*/

#include <alloc.h>
#include <errno.h>

#include "debug0.h"

/* Function    : _DEBUG_Realloc
   Description : This version of realloc modifies an existing entry in the heap allocation list and then writes the updated
                 information to the heap allocation report file.
   Inputs      : Block = The block to resize.
                 Size  = The new size of the block.
                 File  = The source file of the call to realloc.
                 Line  = The source line number in the above file.
   Updates     : Nothing.
   Outputs     : Nothing.
   Returns     : The result of the call to realloc.
   Modified    : 08/10/90 DWP Initial coding.
   Notes       :
*/
void * _DEBUG_Realloc(void * Block, size_t Size, char * File, unsigned int Line) {

   FILE *  fp;
   void *  rec;
   BOOLEAN close_flag;
   CARDINAL_32 list_position;

   errno = EZERO;

   /* Attempt to open the heap allocation report file. */

   if ((fp = fopen(_DEBUG_Heap_Allocation_Report_File, "ab")) != NULL) {

      close_flag = TRUE;

   }
   else {

      fp = stdprn;
      close_flag = FALSE;

   }

   LIST_Find(_DEBUG_Heap_Allocation_List, _DEBUG_Heap_Allocation_Key_Compare, Block, &rec, &list_position);
   if (rec != NULL) {

      ((_DEBUG_Heap_Allocation_Record *) rec)->Memory_Address = realloc(Block, Size);

   }

   _DEBUG_Write_Output(DEBUG_HEAP_ALLOCATION, File, Line, (rec != NULL) ? errno : EINVMEM, fp);
   fprintf(fp, "%10sREALLOC - Old Addr: %Fp  Old Size: %u ", "", *((char *) Block), Size);

   /* If rec is non-NULL, then output the new values, otherwise output an error message indicating the problem. */

   if (rec != NULL) {

      fprintf(fp, "New Addr: %Fp  New Size: %u%s\n", ((_DEBUG_Heap_Allocation_Record *) rec)->Memory_Address, ((_DEBUG_Heap_Allocation_Record *) rec)->Size, (((_DEBUG_Heap_Allocation_Record *) rec)->Memory_Address != NULL) ? "" : "ERROR - Unable to reallocate memory.");

   }
   else {

      fprintf(fp, "\n%10sERROR - Attempted to reallocate a pointer not previously allocated.\n", "");

   }

   /* Close the output file only if isn't stdprn. */

   if (close_flag) {

      fclose(fp);

   }

   return ((rec != NULL) ? ((_DEBUG_Heap_Allocation_Record *) rec)->Memory_Address : NULL);

}
