/* File        : XBASE2C.C
   Module      : XBASE
   System      : None
   Description : A method for updating in-memory XBASE records.
   Modified    : 02/13/91 DWP Created.
   Notes       :
*/

#include <memory.h>

#include "xbase0.h"

/* Procedure   : _XBASE_Convert_To_Xbase
   Description : Replaces the information in the internal XBASE record with the information contained in the internal C record.
   Expects     : work_area = The current work area.
   Returns     : Nothing.
   Modified    : 02/13/91 DWP Initial coding.
   Notes       :
*/
void _XBASE_Convert_To_Xbase(XBASE_work_area *work_area) {
   size_t field_length;
   BYTE   *c_record, *xbase_record;
   int    i;

   c_record = work_area->c_record;
   xbase_record = work_area->xbase_record + 1;

   for (i = 0; i < work_area->number_of_fields; i++) {

      field_length = (size_t) work_area->field_list[i].field_length;

      switch (work_area->field_list[i].field_type) {

         case XBASE_CHARACTER_FIELD : sprintf((char *) xbase_record, "%-*.*s", field_length, field_length, c_record);
                                      c_record += field_length + 1;
                                      break;

         case XBASE_NUMERIC_FIELD   : sprintf((char *) xbase_record, "%*.*lf", field_length, (int) work_area->field_list[i].field_decimal_count, *((double *) c_record));
                                      c_record += sizeof(double);
                                      break;

         case XBASE_LOGICAL_FIELD   : *xbase_record = (*(((BOOLEAN *) c_record)++)) ? 'T' : 'F';
                                      break;

         case XBASE_DATE_FIELD      : sprintf((char *) xbase_record, "%0*lu", field_length, *((unsigned long *) c_record));
                                      c_record += sizeof(unsigned long);
                                      break;

	 case XBASE_MEMO_FIELD      : memcpy(xbase_record, c_record, field_length);
                                      c_record += field_length;
                                      break;
      }

      xbase_record += field_length;
   }
}
