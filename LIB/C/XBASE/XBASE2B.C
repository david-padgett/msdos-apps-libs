/* File        : XBASE2B.C
   Module      : XBASE
   System      : None
   Description : A method for converting from a XBASE record to a Standard C record.
   Modified    : 02/08/91 DWP Created.
   Notes       :
*/

#include <stdlib.h>
#include <string.h>

#include "string\string.h"

#include "xbase0.h"

/* Procedure   : _XBASE_Convert_To_C
   Description : Converts the current DBF record to a Standard C record.
   Expects     : Nothing.
   Returns     : Nothing.
   Modified    : 02/08/91 DWP Initial coding.
   Notes       :
*/
void _XBASE_Convert_To_C(XBASE_work_area *work_area) {
   size_t field_length;
   BYTE   *c_record, *xbase_record;
   char   str[25];
   int    i;

   c_record = work_area->c_record;
   xbase_record = work_area->xbase_record + 1;

   for (i = 0; i < work_area->number_of_fields; i++) {

      field_length = (size_t) work_area->field_list[i].field_length;

      switch (work_area->field_list[i].field_type) {

         case XBASE_CHARACTER_FIELD : strncpy((char *) c_record, (char *) xbase_record, field_length);
                                      c_record[field_length] = '\0';
				      STRING_RTrim((char *) c_record);
				      c_record += field_length + 1;
				      break;

	 case XBASE_NUMERIC_FIELD   : strncpy(str, (char *) xbase_record, field_length);
				      str[field_length] = '\0';
				      *((double *) c_record) = atof(str);
				      c_record += sizeof(double);
				      break;

	 case XBASE_LOGICAL_FIELD   : switch (*xbase_record) {

					 case 'Y' :
					 case 'y' :
					 case 'T' :
					 case 't' : *((BOOLEAN *) c_record) = TRUE;
						    break;

					 default  : *((BOOLEAN *) c_record) = FALSE;
				      }

				      c_record += sizeof(BOOLEAN);
                                      break;

         case XBASE_DATE_FIELD      : strncpy(str, (char *) xbase_record, field_length);
                                      str[field_length] = 0;
                                      *((unsigned long *) c_record) = atol(str);
                                      c_record += sizeof(unsigned long);
                                      break;

	 case XBASE_MEMO_FIELD      : memcpy(c_record, xbase_record, field_length);
                                      c_record += 10;
                                      break;
      }

      xbase_record += field_length;
   }
}
