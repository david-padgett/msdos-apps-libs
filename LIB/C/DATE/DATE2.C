/* File        : DATE2.C
   Module      : DATE
   System      : None
   Description : A method for determining the validity of a date.
   Modified    : 08/01/90 DWP Created.
   Notes       :
*/

#include "date.h"

/* Function    : DATE_IsValid
   Description : Determines if the specified date is a valid date.
   Inputs      : Format = The format the date is in, see DATE_TYPES.
                 Type   = The type of date, either CARDINAL_32 or STRING, see DATA_TYPES.
   Updates     : Nothing.
   Outputs     : Date   = The date to verify.
   Returns     : A value of TRUE if the specified date is valid, FALSE otherwise.
   Modified    : 04/26/90 DWP Initial Coding.
                 02/19/91 DWP Added support for verification of text dates.
   Notes       : 1) Integer date values must be passed as an unsigned long.
                 2) Punctuation is not analyzed, for example, the / and - characters are not considered in the examples below.
                 3) The following are examples of the allowed formats:

                       Symbol    - Examples
                       ----------------------
                       INTEGER/STRING formats.

                       DATE_MMYY_TYPE      - "04/90", "0490", 490
                       DATE_MMDDYY_TYPE    - "04/26/90", "042690", 42690
                       DATE_MMYYYY_TYPE    - "04/1990", "041990", 41990
                       DATE_MMDDYYYY_TYPE  - "04-26-1990", "04261990", 4261990
                       DATE_YYMM_TYPE      - "90/04", "9004", 9004
                       DATE_YYMMDD_TYPE    - "90/04/26", "900426", 900426
                       DATE_YYYYMM_TYPE    - "1990-04", "199004", 199004
                       DATE_YYYYMMDD_TYPE  - "1990-04-26", "19900426", 19900426
                       DATE_DDMMYY_TYPE    - "04-26-90", "042690", 042690
                       DATE_DDMMYYYY_TYPE  - "04-26-1990", "04261990", 04261990

                       STRING only formats.

                       DATE_DDMMMYY_TYPE   - "26 APR 90", "26APR90"
                       DATE_DDMMMYYYY_TYPE - "26-APR-1990", "26APR1990"
                       DATE_MMMDDYYYY_TYPE - "April 26, 1990", "APRIL 26 1990"
*/

BOOLEAN DATE_IsValid(DATE_TYPES Format, DATA_TYPES Type, void * Date) {

   BOOLEAN     result = FALSE, use_day_flag;
   CARDINAL_16 day_maximum_value, year, month, day;

   /* Extract the year, month, and day fields from the specified date, and then validate the month. */

   if (DATE_Decompose_Date(Format, Type, Date, &year, &month, &day) && ((month >= 1) && (month <= 12))) {

      switch (Format) {

         case DATE_MMYY_TYPE :
         case DATE_MMYYYY_TYPE :
         case DATE_YYMM_TYPE :
         case DATE_YYYYMM_TYPE :

            use_day_flag = FALSE;
            break;

         default :

            use_day_flag = TRUE;

      }

      /* Validate the day if one was specified. */

      if (!use_day_flag) {

         result = TRUE;

      }
      else {

         switch (month) {

            /* April, June, September, November all have 30 days. */

            case 4 :
            case 6 :
            case 9 :
            case 11 :

               day_maximum_value = 30;
               break;

	    /* February has either 28 or 29 days, depending on the year.  Several things are checked here.  If the year ends with
               00, then an extra check for a leap year must take place.  Only the centuries that can be evenly divided by 4 (ie:
               16, 20, and 24) are leap years, the others (ie: 17, 18, 19, ...) are not leap years, even though they can be evenly
               divided by 4.  Also, any year, except the 00 year, which is divisible by 4 is a leap year.  If the century isn't
               specified for a year ending in 00, then it is assumed that the 00 year is not a leap year, since the odds are 1 in 4
               against it. */

            case 2 :

               day_maximum_value = (((year / 100 > 0) && ((year / 100) % 4 == 0)) || ((year % 100) != 0 && year % 4 == 0)) ? 29 : 28;
               break;

            /* January, March, May, July, August, October, and December all have 31 days. */

            default :

               day_maximum_value = 31;

         }

         if (day > 0 && day <= day_maximum_value) {

            result = TRUE;

         }

      }

   }

   return (result);

}
