/* File        : DATE6A.C
   Module      : DATE
   System      : None
   Description : A method for converting a date, stored as days elapsed from the beginning of the century, to a date store in the
                 form YYYYMMDD.
   Modified    : 05/31/91 DWP Created.
   Notes       :
*/

#include "date.h"

/* Function    : DATE_Convert_Days_To_YYYYMMDD
   Description : Converts the specified date, stored as days since the beginning of the century, to a date in the form YYYYMMDD.
   Inputs      : Date    = The date to convert.
                 Century = The century in which the specified date occurred.
   Updates     : Nothing.
   Outputs     : Nothing.
   Returns     : The YYYYMMDD form of the specified date.
   Modified    : 05/30/91 DWP Initial coding.
   Notes       :
*/

DATE_YYYYMMDD DATE_Convert_Days_To_YYYYMMDD(CARDINAL_32 Date, CARDINAL_16 Century) {

   CARDINAL_32 year, month, days_in_month, days_in_year;
   CARDINAL_32 result;

   /* Determine the year by reducing the date until there are no longer enough days available to fill one year.  If the century is
      divisible by four, then the first year in that century (year 00) is a leap year. */

   for (year = 0, days_in_year = ((Century % 4 == 0) ? 366 : 365); Date > days_in_year;) {

      Date -= days_in_year;
      days_in_year = (++year % 4 == 0) ? 366 : 365;

   }

   /* Determine the month and day by reducing the date until there are no longer enough days to fill the next month. */

   for (month = 1; TRUE; month++, Date -= days_in_month) {

      days_in_month = DATE_Days_In_Month_List[(int) month];

      /* Adjust the total number of days in the current month if the current month is February and the current year is a leap
         year.  Leap years occur on years evenly divisible by four, except for the year 00.  The year 00 is a leap year only
         if the century is evenly divisible by four. */

      if (month == 2 && ((year == 0 && Century % 4 == 0) || (year > 0 && year % 4 == 0))) {

         days_in_month++;

      }

      /* Determine if there are enough days to fill the current month.  If the total number of unused days is less than or equal
         to the number of days in the current month, then exit. */

      if (Date <= days_in_month) {

         break;

      }

   }

   /* Construct the final result. */

   result = ((Century * 100 + year) * 100 + month) * 100 + Date;

   return (result);

}
