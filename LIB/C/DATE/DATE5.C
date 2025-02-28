/* File        : DATE5.C
   Module      : DATE
   System      : None
   Description : A method for decomposing, or extracting the year, month, and day fields from a date.
   Modified    : 03/13/91 DWP Created.
   Notes       :
*/

#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include "Standard\standard.h"
#include "String\string.h"

#include "date.h"

/* Function    : _DATE_Convert_STRING_To_CARDINAL_32
   Description : Converts the specified character string to its unsigned integer equivalent.
   Inputs      : Date   = The STRING type date to be converted.
   Updates     : Format = The format of the date to convert, see DATE_TYPES.
   Outputs     : Nothing.
   Returns     : The converted date.
   Modified    : 10/25/91 DWP Created, extracted from DATE_Decompose_Date().
   Notes       :
*/

CARDINAL_32 _DATE_Convert_STRING_To_CARDINAL_32(char * Date, DATE_TYPES * Format) {

   char        str[256];
   char *      month_text;
   CARDINAL_32 result;
   CARDINAL_16 month_length, month_value;

   if (strlen(Date) < sizeof(str)) {

      /* Remove all punctuation, including white space, from the formatted text string. */

      strcpy(str, Date);
      STRING_Trim(STRING_TRIM_SPACE, STRING_Trim(STRING_TRIM_PUNCT, str));
      month_length = 0;

      /* Convert the formatted text date to its numeric equivalent and process it further as an integer. */

      switch (* Format) {

         case DATE_DDMMMYY_TYPE :
         case DATE_DDMMMYYYY_TYPE :

            month_length = 3;
            month_text = str + 2;
            result = (atol(str) * 10000) + atol(str + 5);
            break;

         case DATE_MMMDDYYYY_TYPE :

            for (month_length = 0; isalpha(str[month_length]); month_length++) {
            }

            month_text = str;
            result = atol(str + month_length);
            break;

         /* The text string can be directly converted to an integer. */

         default :

            result = atol(str);

      }

      /* Determine what month was specified.  If the month is less than three characters in length, the month is invalid. */

      if (month_length >= 3) {

         for (month_value = 1; month_value < 13 && strnicmp(month_text, DATE_Months_List[month_value], month_length) != 0; month_value++) {
         }

         if (month_value < 13) {

            result += month_value * 1000000L;
            * Format = DATE_MMDDYYYY_TYPE;

         }
         else {

            result = 0;

         }

      }

   }

   return (result);

}

/* Function    : DATE_Decompose_Date
   Description : Extracts the year, month, and day fields from the specified date.
   Inputs      : Format = The format of the date that is to be decomposed, see DATE_TYPES.
                 Type   = The data type of the date, either CARDINAL_32 or STRING, see DATA_TYPES.
                 Date   = The date to decompose.
   Updates     : Nothing.
   Outputs     : Year   = The year field of the specified date.
                 Month  = The month field of the specified date.
                 Day    = The day field of the specified date.
   Returns     : A value of TRUE if the date was successfully decomposed, FALSE otherwise.
   Modified    : 03/13/91 DWP Initial coding.
   Notes       :
*/

BOOLEAN DATE_Decompose_Date(DATE_TYPES Format, DATA_TYPES Type, void *Date, CARDINAL_16 *Year, CARDINAL_16 *Month, CARDINAL_16 *Day) {

   CARDINAL_32  numeric_date, adjustment;
   CARDINAL_16  year_value, month_value, day_value, exchange_value;
   BOOLEAN      result = TRUE;

   switch (Type) {

      case CARDINAL_32_TYPE :

         numeric_date = (Format != DATE_DDMMMYY_TYPE && Format != DATE_DDMMMYYYY_TYPE && Format != DATE_MMMDDYYYY_TYPE) ? *((CARDINAL_32 *) Date) : 0;
         break;

      case STRING_TYPE :

         numeric_date = _DATE_Convert_STRING_To_CARDINAL_32(Date, &Format);
         break;

      default :

         numeric_date = 0;

   }

   if (numeric_date != 0) {

      switch (Format) {

         case DATE_MMYY_TYPE :
         case DATE_MMDDYY_TYPE :
         case DATE_DDMMYY_TYPE :

            adjustment = 100;
            break;

         default :

            adjustment = 10000;

      }

      switch (Format) {

         case DATE_MMYY_TYPE :
         case DATE_MMDDYY_TYPE :
         case DATE_MMYYYY_TYPE :
         case DATE_MMDDYYYY_TYPE :
         case DATE_DDMMYY_TYPE :
         case DATE_DDMMYYYY_TYPE :

            year_value = (CARDINAL_16) (numeric_date % adjustment);
            month_value = (CARDINAL_16) ((numeric_date / adjustment) % 100);
            day_value = (CARDINAL_16) (numeric_date / (100 * adjustment));

            /* Exchange the month and day values if the format is MMDDYY or MMDDYYYY. */

            if (Format == DATE_MMDDYY_TYPE || Format == DATE_MMDDYYYY_TYPE) {

               exchange_value = month_value;
               month_value = day_value;
               day_value = exchange_value;

            }

            break;

         case DATE_YYMM_TYPE :
         case DATE_YYYYMM_TYPE :

            numeric_date *= 100;

         case DATE_YYMMDD_TYPE :
         case DATE_YYYYMMDD_TYPE :

            year_value = (CARDINAL_16) (numeric_date / 10000);
            month_value = (CARDINAL_16) ((numeric_date % 10000) / 100);
            day_value = (CARDINAL_16) (numeric_date % 100);
            break;

         case DATE_DDMMMYY_TYPE :
         case DATE_DDMMMYYYY_TYPE :
         case DATE_MMMDDYYYY_TYPE :
         default :

            result = FALSE;

      }

      /* Assign values to the year, month, and day parameters if no errors occurred. */

      if (result) {

         * Year = year_value;
         * Month = month_value;
         * Day = day_value;

      }

   }

   return (result);

}
