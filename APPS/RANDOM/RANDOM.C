/* File        : RANDOM.C
   Module      : RANDOM
   System      : RANDOM
   Description : This program creates a file of random data.  The size of the file is also random.
   Modified    : 01/25/91 DWP Created.
   Notes       :
*/

#include <io.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Function    : main
   Description : This program creates a file of random data.  The size of the file is also random.
   Expects     : argv[1] = The name of the random data file to created.
   Returns     : A value of 0 if no errors occurred, otherwise, a value of 1.
   Modified    : 01/25/91 DWP Initial coding.
   Notes       :
*/
int main(int argc, char *argv[]) {
   FILE          *fp;
   unsigned long length;
   int           result = 1;

   printf("\nRANDOM V1.0, " COMPILE_DATE ", Copyright (c) 1991 by CSFX\n");

   /* Display the help screen if the command-line parameters are invalid. */

   if (argc != 2) {
      printf("\n   Purpose : Creates a random size file containing random data.\n\n");
      printf("   Usage   : RANDOM {[RandomDataFileName]}\n\n");
      printf("   Where\n\n%6sRandomDataFileName = The name of the random data file to create.  No\n%27sprocessing occurs if the file already exists.\n", "", "");
   }
   else {

      /* Attempt to create and open the specified file. */

      if (access(argv[1], 0) == -1 && (fp = fopen(argv[1], "wb")) != NULL && setvbuf(fp, NULL, _IOFBF, 32767) == 0) {

         /* Initialize the random number generator, then generate a file length for the random data file. */

         randomize();
         length = ((unsigned long) rand() * (unsigned long) rand()) % 1000000L;

         /* Loop until enough random data has been placed into the random file. */

         while ((length-- > 0L) && (fputc(rand() % 256, fp) != EOF));

         /* If the length is zero, then no errors occurred. */

         if (length == 0L) {
            result = 0;
         }
      }

      /* Close the newly created random data file. */

      if (fp != NULL) {
         fclose(fp);
      }
   }

   return (result);
}
