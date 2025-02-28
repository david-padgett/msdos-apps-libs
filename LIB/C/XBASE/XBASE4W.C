/* File        : XBASE4W.C
   Module      : XBASE
   System      : None
   Description : A method for determining if the most recent XBASE_Find(),
                 XBASE_Seek(), XBASE_Locate(), or XBASE_Continue() was
                 successful.
   Modified    : 02/19/91 DWP Created.
*/

#include "xbase0.h"

/* Function    : XBASE_Found
   Description : Determines if the most recent XBASE_Find(), XBASE_Seek(),
                 XBASE_Locate(), or XBASE_Continue() issued in the current
                 work area was successful.
   Expects     : Nothing.
   Returns     : TRUE if the last search operation was successful, FALSE
                 otherwise.
   Modified    : 02/19/91 DWP Initial coding.
   Notes       :
*/
unsigned int XBASE_Found(void) {

   return (XBASE_current_work_area->found_flag);
}
