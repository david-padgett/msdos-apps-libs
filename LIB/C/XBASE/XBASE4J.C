/* File        : XBASE4J.C
   Module      : XBASE
   System      : None
   Description : A method for extracting the day portion of a date.
                 format.
   Modified    : 02/15/91 DWP Created.
*/

#include "xbase0.h"

/* Function    : XBASE_Day
   Description : Extracts the day portion of the specified date.
   Expects     : date = The date to query.
   Returns     : The numeric value of the day portion of the specified date.
   Modified    : 02/15/91 DWP Initial coding.
   Notes       :
*/
unsigned int XBASE_Day(unsigned long date) {

   return ((int) (date % 100L));
}