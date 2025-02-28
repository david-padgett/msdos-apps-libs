/* File        : XBASE2D.C
   Module      : XBASE
   System      : None
   Description : A method for calculating the size of a Standard C record based upon information contained in a DBF file.
   Modified    : 02/08/91 DWP Created.
   Notes       :
*/

#include "date\date.h"

#include "xbase0.h"

/* Function    : _XBASE_Calculate_C_Record_Size
   Description : Determines how many bytes of space are required to store a DBF file record that is to be converted to a Standard C
                 record.
   Expects     : work_area = The work area to query.
   Returns     : The size, in bytes, of the Standard C record that will be created by converting the DBF file record to the
                 Standard C format.
   Modified    : 02/08/91 DWP Initial coding.
   Notes       :
*/
CARDINAL_16 _XBASE_Calculate_C_Record_Size(XBASE_work_area *work_area) {
   CARDINAL_16 result;
   int i;

   result = 0;

   if (work_area->in_use_flag) {

      for (i = 0; i < work_area->number_of_fields; i++) {

         switch (work_area->field_list[i].field_type) {

            case XBASE_CHARACTER_FIELD : result += work_area->field_list[i].field_length + 1;
                                         break;

            case XBASE_NUMERIC_FIELD   : result += sizeof(double);
                                         break;

            case XBASE_LOGICAL_FIELD   : result += sizeof(BOOLEAN);
                                         break;

            case XBASE_DATE_FIELD      : result += sizeof(DATE_YYYYMMDD);
                                         break;

	    case XBASE_MEMO_FIELD      : result += 10;
                                         break;
         }
      }
   }

   return (result);
}
