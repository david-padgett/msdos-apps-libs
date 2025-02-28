/* File        : XBASE4D.C
   Module      : XBASE
   System      : None
   Description : A method for calculating the day of week from a date.
   Modified    : 02/14/91 DWP Created.
   Notes       :
*/

#include "xbase0.h"

/* Function    : XBASE_Cdow
   Description : Retrieves the name of the day of week using the specified date.
   Expects     : date = The date to query.
   Returns     : The name of the day of week.  If the date was invalid, no name is returned.
   Modified    : 02/19/91 DWP Initial coding.
   Notes       :
*/
const char *XBASE_Cdow(DATE_YYYYMMDD date) {

   return (DATE_Days_List[DATE_Day_Of_Week(date)]);
}
