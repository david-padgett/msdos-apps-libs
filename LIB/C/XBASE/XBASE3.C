/* File        : XBASE3.C
   Module      : XBASE
   System      : None
   Description : The methods for opening and closing XBASE files.
   Modified    : 02/06/91 DWP Created.
   Notes       :
*/

#include <alloc.h>
#include <errno.h>
#include <memory.h>
#include <string.h>

#include "dir\dir.h"

#include "xbase0.h"

/* Function    : XBASE_Use
   Description : Opens the specified XBASE file.
   Expects     : dbf_file = The name of the file to open.
                 ndx_file = The name of the index file to open along with the XBASE file.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 02/06/91 DWP Initial coding.
   Notes       :
*/
int XBASE_Use(char *dbf_file, char *ndx_file_list[], char *alias) {
   XBASE_work_area *work_area;
   char            str[MAXPATH];

   XBASE_error_code = EZERO;

   /* If no DBF file was specified, close the current work area. */

   if (dbf_file == NULL || dbf_file[0] == '\0') {
      _XBASE_Close_Work_Area(XBASE_current_work_area_number);
   }
   else {

      /* Open the specified DBF file. */

      LIST_Retrieve(XBASE_work_area_list, XBASE_current_work_area_number, (void **) &work_area);
      if (work_area != NULL) {

         /* If the current work area is in use, close the files that are in use in that work area. */

         if (work_area->in_use_flag) {
            _XBASE_Close_Work_Area(XBASE_current_work_area_number);
         }

         work_area->in_use_flag = TRUE;
         work_area->current_record = 1L;

         /* Initialize the dbf_file and alias fields of new work area record. */

         sprintf(work_area->dbf_file, "%.*s", sizeof(work_area->dbf_file) - 1, dbf_file);

	  if (DIR_Retrieve_File_Extension(dbf_file, sizeof(str), str) == NULL && strlen(work_area->dbf_file) + 4 < sizeof(work_area->dbf_file)) {
             strcat(work_area->dbf_file, ".dbf");
          }

	 sprintf(work_area->alias, "%.*s", sizeof(work_area->alias) - 1, (alias != NULL && alias[0] != '\0') ? alias : DIR_Retrieve_File_Name(dbf_file, sizeof(str), str));

         /* Open the DBF file. */

         if ((work_area->dbf_fp = fopen(work_area->dbf_file, "r+b")) == NULL) {
            XBASE_error_code = ENOFILE;
         }
         else {

            /* Load the header record. */

            if (fread(&(work_area->header_record), sizeof(work_area->header_record), 1, work_area->dbf_fp) != 1) {
               XBASE_error_code = EACCES;
            }
            else {

               /* Check to see if the file is actually a DBF file. */

               if ((work_area->header_record.file_id & 0x03) != 0x03) {
                  XBASE_error_code = EINVDAT;
               }
               else {

                  /* Load the field descriptors. */

                  work_area->number_of_fields = (work_area->header_record.total_bytes_in_header - sizeof(XBASE_header_record) - 1) / sizeof(XBASE_field_descriptor);

                  /* Allocate space for the field descriptor list.  Also allocate space for an unaltered record of the newly opened
                     database.  Include space for two extra bytes.  The first is the deleted record flag, the second serves as an
                     overflow buffer for string operations during conversion of C records to XBASE records in
                     XBASE_Convert_To_Xbase() in "XBASE2C.C". */

                  if ((work_area->field_list = calloc(work_area->number_of_fields, sizeof(XBASE_field_descriptor))) == NULL || (work_area->xbase_record = malloc(sizeof(BYTE) + work_area->header_record.total_bytes_in_record + sizeof(BYTE))) == NULL) {
                     XBASE_error_code = ENOMEM;
                  }
                  else {

                     if (fread(work_area->field_list, sizeof(XBASE_field_descriptor), work_area->number_of_fields, work_area->dbf_fp) != work_area->number_of_fields) {
                        XBASE_error_code = EACCES;
                     }
                     else {

                        if ((work_area->c_record = malloc(_XBASE_Calculate_C_Record_Size(work_area))) == NULL) {
                           XBASE_error_code = ENOMEM;
                        }
                        else {

                           /* Load the first record. */

                           if (_XBASE_Load_Record(work_area->current_record) == ERANGE) {
                              setmem(work_area->xbase_record, sizeof(BYTE) + work_area->header_record.total_bytes_in_record, 0);
                              work_area->end_of_file_flag = TRUE;
                              XBASE_error_code = EZERO;
                           }
                        }
                     }
                  }
               }
            }
         }

         /* Close files and return allocated memory to the heap if an error occurred while attempting to open the DBF file. */

         if (XBASE_error_code != EZERO) {
            _XBASE_Close_Work_Area(XBASE_current_work_area_number);
         }
      }
   }

   return (XBASE_error_code);
}