/* File        : XBASE4I.C
   Module      : XBASE
   System      : None
   Description : A method for retrieving the system date in text string
                 format.
   Modified    : 02/14/91 DWP Created.
                 02/15/91 DWP Removed code which was duplicated in
                              XBASE_Dtoc().
*/

#include <dos.h>
#include <errno.h>

#include "xbase0.h"

/* Function    : XBASE_Date
   Description : Retrieves the system date.
   Expects     : Nothing.
   Returns     : A pointer to a string containing the current date.
   Modified    : 02/14/91 DWP Initial coding.
                 02/15/91 DWP Removed all code which is duplicated in
                              XBASE_Tdoc().
   Notes       :
*/
char *XBASE_Date(void) {
   struct date date;

   getdate(&date);

   return (XBASE_Dtoc((((date.da_year * 100L) + date.da_mon) * 100L) + date.da_day));
}
