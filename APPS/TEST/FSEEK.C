/* File        : FSEEK.C
   Module      : TEST
   System      : None
   Description : Tests the performance of fseek().
   Modified    : 04/03/91 DWP Created.
*/

#include <io.h>
#include <stdio.h>

#include "standard\standard.h"

/* Function    : main
   Description : Tests the fseek() function.
   Expects     : Nothing.
   Returns     : Always returns a value of zero.
   Modified    : 04/03/91 DWP Initial coding.
   Notes       :
*/
int main(int argc, char *argv[]) {
   FILE *fp;
   BYTE data;
   long current_record, length;
   int  result = 0;

   fp = fopen(argv[argc - 1], "rb");
   length = filelength(fileno(fp));
   current_record = 0L;
   data = 0;

   while (TRUE) {

      if ((result = fseek(fp, current_record++ * (long) sizeof(data), SEEK_SET)) != 0) {
         break;
      }

      if ((result = fread(&data, sizeof(data), 1, fp)) != 1) {
         break;
      }
   }

   printf("\nlength = %ld, current_record = %ld, error = %d\n", length, current_record, result);
   fclose(fp);

   return (0);
}