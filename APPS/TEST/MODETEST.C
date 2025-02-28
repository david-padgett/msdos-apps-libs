/* File        : MODETEST.C
   Module      : TEST
   System      : None
   Description : A method for test crt_modify_attr() in the CRT module.
   Modified    : 12/13/90 DWP Created.
*/

#include <conio.h>
#include "crt\crt.h"

int main(void) {

   crt_modify_attr(10, 10, 10, 10, (LIGHTGRAY << 4) + WHITE);

   return (0);
}