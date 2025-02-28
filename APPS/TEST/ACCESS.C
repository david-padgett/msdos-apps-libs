/* File        : ACCESS.C
   Module      : TEST
   System      : TEST
   Description : Tests the access() function in the Standard C library.
   Modified    : 05/02/91 DWP Created.
*/

#include <io.h>
#include <stdio.h>

/* Function    : main
   Description : The main entry point for the ACCESS test program.
   Expects     : Nothing.
   Returns     : Always returns a value of zero.
   Modified    : 05/02/91 DWP Initial coding.
   Notes       :
*/
int main(void) {

   printf("\naccess(\"c:\\dos\", 0) = %d\n", access("c:\\dos", 0));

   return (0);
}