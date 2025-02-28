/* File        : PRREAL.C
   Module      : TEST
   System      : None
   Description : Tests output of reals using printf().
   Modified    : 01/08/91 DWP Created.
*/

#include <stdio.h>

/* Function    : main
   Description :
   Expects     : Nothing.
   Returns     : Always returns zero.
   Modified    : 01/08/91 DWP Initial coding.
   Notes       :
*/
int main(void) {

   printf("%.0lf\n", 123999999.123456);

   return (0);
}