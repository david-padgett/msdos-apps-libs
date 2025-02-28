/* File        : XBASE4H.C
   Module      : XBASE
   System      : None
   Description : A method for converting a date stored as a string to a date
                 stored as a number.
   Modified    : 02/14/91 DWP Created.
*/

#include <stdlib.h>
#include <string.h>

#include "xbase0.h"

/* Function    : XBASE_Ctod
   Description : Converts the specified date, which is represented as a
                 string, to a date stored as a number.
   Expects     : date = The date to convert.
   Returns     : The numeric value of the specified date.
   Modified    : 02/14/91 DWP Initial coding.
   Notes       :
*/
unsigned long XBASE_Ctod(char *date) {
   unsigned long year, month, day;
   char          year_text[5], month_text[3], day_text[3];
   int           year_text_length;

   year_text_length = sizeof(year_text) - ((XBASE_century_flag) ? 0 : (sizeof(year_text) - 1) / 2) - 1;

   switch (XBASE_date_type) {

      case AMERICAN : strncpy(year_text, date + sizeof(month_text) + sizeof(day_text), year_text_length);
                      strncpy(month_text, date, sizeof(month_text) - 1);
                      strncpy(day_text, date + sizeof(month_text), sizeof(day_text) - 1);
                      break;

      case ANSI     : strncpy(year_text, date, year_text_length);
                      strncpy(month_text, date + year_text_length + 1, sizeof(month_text) - 1);
                      strncpy(day_text, date + year_text_length + sizeof(month_text) + 1, sizeof(day_text) - 1);
                      break;

      case BRITISH  :
      case FRENCH   :
      case GERMAN   :
      case ITALIAN  : strncpy(year_text, date + sizeof(day_text) + sizeof(month_text), year_text_length);
                      strncpy(month_text, date + sizeof(day_text), sizeof(month_text) - 1);
                      strncpy(day_text, date, sizeof(day_text) - 1);
                      break;
   }

   year_text[year_text_length] = month_text[sizeof(month_text)] = day_text[sizeof(day_text)] = '\0';

   year = atol(year_text);
   month = atol(month_text);
   day = atol(day_text);

   return ((((year * 100L) + month) * 100L) + day);
}
