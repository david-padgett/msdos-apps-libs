/* File        : DATE3.C
   Module      : DATE
   System      : None
   Description : A method for calculating the day of week of a date.
   Modified    : 02/19/91 DWP Created.
   Notes       :
*/

#include "date.h"

/* Function    : DATE_Day_Of_Week
   Description : Calculates the day of week the specified date falls on.
   Inputs      : Date = The date to query.
   Updates     : Nothing.
   Outputs     : Nothing.
   Returns     : The day of week the specified date falls on.  The result will be a value in the range [1..7], where Sunday is
                 equivalent to one and Saturday is equivalent to seven.
   Modified    : 02/19/91 DWP Initial coding.  Algorithm from Dr. Dobbs Nov 1990 and Feb 1991 issues.
   Notes       : 1) The date must be in the format YYYYMMDD.
*/

CARDINAL_16 DATE_Day_Of_Week(DATE_YYYYMMDD Date) {

   CARDINAL_16 century, year, month, day, result;

   /* Validate the date, and then extract the year, month, and day information from it. */

   if (!DATE_IsValid(DATE_YYYYMMDD_TYPE, CARDINAL_32_TYPE, &Date) || !DATE_Decompose_Date(DATE_YYYYMMDD_TYPE, CARDINAL_32_TYPE, &Date, &year, &month, &day)) {

      result = 0;

   }
   else {

      /* Extract and the remove the century from the year. */

      century = year / 100;
      year %= 100;

      /* Convert January and February from months 1 and 2 to months 13 and 14.  This is a condition of Zeller's Congruence
         Algorithm. */

      if (month < 3) {

         month += 12;

         if (year > 0) {

            year--;

         }
         else {

            year = 99;
            century--;

         }

      }

      /* Zeller's Congruence Algorithm. */

      result = (day + (((month + 1) * 26) / 10) + year + (year / 4) + (century / 4) + (century * 5)) % 7;

      /* Modify result when result indicates the day is Saturday.  Make Saturday the last day and not the first day. */

      if (result == 0) {

         result  = 7;

      }

   }

   return (result);

}
