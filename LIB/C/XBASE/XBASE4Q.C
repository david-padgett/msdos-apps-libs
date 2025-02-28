/* File        : XBASE4Q.C
   Module      : XBASE
   System      : None
   Description : A method for querying the error number.
   Modified    : 02/15/91 DWP Created.
*/

#include "xbase0.h"

/* Function    : XBASE_Error
   Description : A method for querying the error number.
   Expects     : Nothing.
   Returns     : The value of the last error that occurred.
   Modified    : 02/15/91 DWP Initial coding.
   Notes       :
*/
unsigned int XBASE_Error(void) {

   return (XBASE_error_code);
}
