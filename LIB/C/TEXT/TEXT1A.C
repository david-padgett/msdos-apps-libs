/* File        : TEXT1A.C
   Module      : TEXT
   System      : None
   Description : A method for destroying an instance of a TEXT record.
   Modified    : 03/04/92 DWP Created.
   Notes       :
*/

#include <alloc.h>
#include <stdio.h>

#include "text0.h"

/* Function    : TEXT_Destructor
   Description : A method for destroying the specified TEXT record.
   Inputs      : Nothing.
   Updates     : Text = The TEXT record to destroy.
   Outputs     : Nothing.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 03/04/92 DWP Initial coding.
   Notes       :
*/

int TEXT_Destructor(TEXT * Text) {

   int result;

   if (*(Text) == NULL) {

      result = TEXT_PARAM;

   }
   else {

      free(*(Text));
      *(Text) = NULL;
      result = TEXT_NOERR;

   }

   return (result);
}
