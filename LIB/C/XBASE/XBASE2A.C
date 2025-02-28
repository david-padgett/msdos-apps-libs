/* File        : XBASE2A.C
   Module      : XBASE
   System      : None
   Description : A method for loading a record from disk.
   Modified    : 02/07/91 DWP Created.
   Notes       :
*/

#include <errno.h>
#include <memory.h>

#include "xbase0.h"

/* Function    : _XBASE_Load_Record
   Description : Loads in the specified record from the DBF file.
   Expects     : new_record = The record to read.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 02/07/91 DWP Initial coding.
   Notes       :
*/
int _XBASE_Load_Record(INTEGER_32 new_record) {
   XBASE_work_area *work_area;

   /* Retrieve the current work area. */

   LIST_Retrieve(XBASE_work_area_list, XBASE_current_work_area_number, (void **) &work_area);
   if (work_area == NULL) {
      XBASE_error_code = EINVDAT;
   }
   else {

      if (new_record > work_area->header_record.total_records) {

         /* the specified record is too large. */

         work_area->current_record = work_area->header_record.total_records + 1L;
         work_area->end_of_file_flag = TRUE;
         setmem(work_area->xbase_record, work_area->header_record.total_bytes_in_record, 0);
         setmem(work_area->c_record, _XBASE_Calculate_C_Record_Size(work_area), 0);
      }
      else {

         if (new_record < 1L) {

            /* The specified record is too small, so indicate the error using the beginning of file flag and load record number
               one instead. */

            work_area->current_record = 1L;
            work_area->beginning_of_file_flag = TRUE;
         }
         else {

            /* Specified record is valid, clear beginning/end of file flags. */

            work_area->current_record = new_record;
            work_area->end_of_file_flag = work_area->beginning_of_file_flag = FALSE;
         }

         /* Seek the specified record, then read in the deleted record flag and the actual record. */

         if (fseek(work_area->dbf_fp, work_area->header_record.total_bytes_in_header + (work_area->header_record.total_bytes_in_record * (work_area->current_record - 1)), SEEK_SET) != 0 || fread(work_area->xbase_record, work_area->header_record.total_bytes_in_record, 1, work_area->dbf_fp) == 0) {
            XBASE_error_code = EACCES;
         }
         else {
            _XBASE_Convert_To_C(work_area);
         }
      }
   }

   return (XBASE_error_code);
}
