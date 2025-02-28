/* File        : XBASE4N.C
   Module      : XBASE
   System      : None
   Description : A method for determining what day of week a date falls on.
   Modified    : 02/15/91 DWP Created.
*/

#include <dos.h>

#include "date\date.h"

#include "xbase0.h"

/* Function    : XBASE_Dow
   Description : Determines what day of week the specified date falls on.
   Expects     : date = The date to query.
   Returns     : The number in the range [1..7], where Sunday is equivalent
                 to day one and Saturday is equivalent to day seven.
   Modified    : 02/19/91 DWP Initial coding.
   Notes       :
*/
unsigned int XBASE_Dow(void) {
   struct date date;

   getdate(&date);

   return (DATE_Day_Of_Week(date.da_year * 10000L + date.da_mon * 100L + date.da_day));
}
