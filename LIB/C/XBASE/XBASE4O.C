/* File        : XBASE4O.C
   Module      : XBASE
   System      : None
   Description : A method for converting a date from its numeric
                 representation to its textual representation.
   Modified    : 02/15/91 DWP Created.
*/

#include "xbase0.h"

/* Function    : XBASE_Dtoc
   Description : Converts the specified date to a text string.
   Expects     : date = The date to convert.
   Returns     : A pointer to a text string which contains the converted
                 date.
   Modified    : 02/15/91 DWP Initial coding.
   Notes       :
*/
char *XBASE_Dtoc(unsigned long date) {
   unsigned int year, month, day;
   unsigned int field_1, field_2, field_3;
   int          field_1_length, field_2_length, field_3_length;
   char         field_separator;

   year = (unsigned int) (date / 10000L);
   month = (unsigned int) ((date % 10000L) / 100L);
   day = (unsigned int) (date % 100L);

   field_1_length = field_2_length = 2;

   if (XBASE_century_flag) {
      field_3_length = 4;
   }
   else {
      year /= 100;
      field_3_length = 2;
   }

   switch (XBASE_date_type) {

      case AMERICAN : field_1 = month;
                      field_2 = day;
                      field_3 = year;
                      field_separator = '/';
                      break;

      case ANSI     : field_1 = year;
                      field_2 = month;
                      field_3 = day;
                      field_1_length = field_3_length;
                      field_3_length = 2;
                      field_separator = '.';
                      break;

      default       : field_1 = day;
                      field_2 = month;
                      field_3 = year;

                      switch (XBASE_date_type) {
                         case BRITISH  :
                         case FRENCH   : field_separator = '/';
                                         break;
                         case GERMAN   : field_separator = '.';
                                         break;
                         case ITALIAN  : field_separator = '-';
                                         break;
                      }
   }

   sprintf(XBASE_date_string, "%0*u%c%0*u%c%0*u", field_1_length, field_1, field_separator, field_2_length, field_2, field_separator, field_3_length, field_3);

   return (XBASE_date_string);
}
