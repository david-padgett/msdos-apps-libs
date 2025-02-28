/* File        : COUNT.C
   Module      : None
   System      : None
   Description :
   Modified    :
*/

#include <stdlib.h>
#include "standard\standard.h"
#include "kb\kb.h"
#include "string\string.h"

/* Function
   Description
   Expects
   Returns
   Modified
   Notes
*/
int main(void) {
   double x;
   char   str[256];

   printf("\n\n\n");

   for (x = 0.0; KB_Preview() != KB_ESC || KB_Read() != KB_ESC; x++) {

      sprintf(str, "%.0lf", x);
      printf("\r%s", STRING_Delimit(3, STRING_DELIMIT_RIGHT, ",", str));
   /*

      printf("\r%.0lf", x);
   */
   }

   return (0);
}
