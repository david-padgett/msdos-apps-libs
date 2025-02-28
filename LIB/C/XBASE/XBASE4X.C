/* File        : XBASE4X.C
   Module      : XBASE
   System      : None
   Description : A method for retrieving environment variable information.
   Modified    : 02/19/91 DWP Created.
*/

#include <stdlib.h>

#include "xbase0.h"

/* Function    : XBASE_Getenv
   Description : Retrieves the value of the specified environment variable.
   Expects     : variable = The environment variable to query.
   Returns     : The value of the specified environment variable if the
                 environment variable exists.
   Modified    : 02/19/91 DWP Initial coding.
   Notes       :
*/
const char *XBASE_Getenv(const char *variable) {
   char *result;

   if ((result = getenv(variable)) == NULL) {
      result = XBASE_empty_string;
   }

   return (result);
}
