/* File        : RANDTEST.C
   Module      : TEST
   System      : None
   Description : Tests the random number generator.
   Modified    : 12/13/90 DWP Created.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
   int i, value;
   int true_count, false_count;

   randomize();
   true_count = 0;
   false_count = 0;

   for (i = 0; i < 100; i++) {
      value = random(2);
      if (value == 1) {
         true_count++;
      }
      else {
         false_count++;
      }
      printf("%3d ", value);
   }

   printf("True Count  : %5d     False Count : %5d\n", true_count, false_count);

   return (0);
}
