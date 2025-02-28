/* File        : DATE6.C
   Module      : DATE
   System      : None
   Description : A method for converting dates stored as YYYYMMDD to dates stored as the number of days elapsed since the
                 beginning of the century.
   Modified    : 05/30/91 DWP Created.
   Notes       :
*/

#include "date.h"

/* Function    : DATE_Convert_YYYYMMDD_To_Days
   Description : Converts the specified date to a form that represents how many days have elapsed between it and the beginning of
                 the century.
   Inputs      : Date = The date to convert.  This date must be in YYYYMMDD format.
   Updates     : Nothing.
   Outputs     : Nothing.
   Returns     : The number of days that have elapsed between the specified date and the beginning of the century.  If an error
                 occurs, a value of zero is returned.
   Modified    : 05/30/91 DWP Initial coding.
   Notes       : 1) This function computes the value of "date - 01/01/00".  The return value is this difference in days.
                 2) The return value is computed by converting years and months to days, and then adding these two values to the
                    number of leftover days.  One extra day is added for February during leap years.
*/

INTEGER_32 DATE_Convert_YYYYMMDD_To_Days(DATE_YYYYMMDD Date) {

   CARDINAL_16 century, year, month, day;
   INTEGER_32  result;

   /* Decompose the date, if an error occurs, exit. */

   if (!DATE_IsValid(DATE_YYYYMMDD_TYPE, CARDINAL_32_TYPE, &Date) || !DATE_Decompose_Date(DATE_YYYYMMDD_TYPE, CARDINAL_32_TYPE, &Date, &year, &month, &day)) {

      result = 0;

   }
   else {

      /* Extract and then remove the century information from the specified year. */

      century = year / 100;
      year %= 100;

      /* Determine how many days separate the specified date and the beginning of the century. */

      result = year * 365 + (((year > 0) ? year - 1 : year) / 4) + (((century % 4 == 0) && ((year > 0) || (Date % 10000 >= 229))) ? 1 : 0) + day;

      while (--month > 0) {

         result += DATE_Days_In_Month_List[month];

         /* Adjust the number of days in February if the specified year is a leap year.  Leap years occur on all year evenly
            divisible by four, except for the year 00.  The year 00 is a leap year only if the century is evenly divisible by
            four. */

         if (month == 2 && (year > 0 && year % 4 == 0)) {

            result++;

         }

      }

   }

   return (result);

}
