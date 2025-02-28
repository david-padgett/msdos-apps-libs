/* File        : XBASE2.C
   Module      : XBASE
   System      : None
   Description : A method for closing the current work area.
   Modified    : 02/07/91 DWP Created.
   Notes       :
*/

#include <alloc.h>
#include <errno.h>
#include <memory.h>

#include "xbase0.h"

/* Function    : _XBASE_Close_Work_Area
   Description : Closes the current work area.
   Expects     : work_area_number = The work area to close.
   Returns     : Nothing.
   Modified    : 02/07/91 DWP Initial coding.
   Notes       :
*/
void _XBASE_Close_Work_Area(int work_area_number) {
   FILE            *ndx_fp;
   XBASE_work_area *work_area;
   int             i;
   CARDINAL_32     ndx_fp_list_size;

   LIST_Retrieve(XBASE_work_area_list, work_area_number, (void **) &work_area);
   if (work_area == NULL) {
      XBASE_error_code = EINVDAT;
   }
   else {

      /* Close the DBF file. */

      if (work_area->dbf_fp != NULL && fclose(work_area->dbf_fp) != 0) {
	 XBASE_error_code = EACCES;
      }

      /* Destroy the NDX files list. */

      LIST_Destructor(&(work_area->ndx_file_list));

      /* Close the NDX file(s) and destroy the NDX files list. */

      LIST_Size(work_area->ndx_fp_list, &ndx_fp_list_size);
      for (i = ndx_fp_list_size - 1; i > 0; i--) {

	 LIST_Retrieve(work_area->ndx_fp_list, i, (void **) &ndx_fp);
	 if (ndx_fp == NULL || fclose(ndx_fp) != 0) {
	    XBASE_error_code = EACCES;
	 }
      }

      LIST_Destructor(&(work_area->ndx_fp_list));

      /* Deallocate the field list and record buffers. */

      if (work_area->field_list != NULL) {
	 free(work_area->field_list);
      }

      if (work_area->c_record != NULL) {
	 free(work_area->c_record);
      }

      if (work_area->xbase_record != NULL) {
	 free(work_area->xbase_record);
      }

      /* Destroy all remaining data in the work area. */

      setmem(work_area, sizeof(XBASE_work_area), 0);
   }
}