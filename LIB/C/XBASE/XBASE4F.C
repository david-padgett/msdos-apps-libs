/* File        : XBASE4F.C
   Module      : XBASE
   System      : None
   Description : A method for extracting the month from a date.
   Modified    : 02/14/91 DWP Created.
   Notes       :
*/

#include <errno.h>

#include "xbase0.h"

/* Function    : XBASE_Cmonth
   Description : A method for extracting the month from the specified date.
   Expects     : date = The date to query.
   Returns     : The month contained in the specified date.
   Modified    : 02/14/91 DWP Initial coding.
   Notes       :
*/
int XBASE_Cmonth(DATE_YYYYMMDD date) {

   return ((int) ((date % 10000L) / 100L));
}
