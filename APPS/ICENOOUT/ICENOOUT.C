/* File        : ICENOOUT.C
   Module      : ICENOOUT
   System      : ICENOOUT
   Description : This program disables output on a COM or EXE file created
                 with the ICE -s option.
   Modified    : 06/25/90 DWP Created.
*/

#include <ctype.h>
#include <stdio.h>
#include <string.h>

/* Function    : main
   Description : The main entry point for the ICENOOUT program.
   Expects     : argc = The total number of command-line arguments.
                 argv = A list of the command-line arguments.
   Returns     : A value of 1 if an error occurred, a value of 0 otherwise.
   Modified    : 06/25/90 DWP Initial coding.
   Notes       :
*/
int main(int argc, char *argv[]) {
   FILE *fp;
   char bufr[1150];
   int  i;
   int  type_flag;
   int  result = 0;

   if (argc < 2) {
      printf("\n\nICENOOUT v1.0 - Disables output on COM or EXE files created with\n");
      printf("                the ICE -s option.\n");
      printf("   Usage :\n\n");
      printf("      ICENOOUT filename.ext\n\n");
   }
   else {

      /* Determine if specified file is a COM or EXE type file. */

      for (i = 0; i < strlen(argv[1]); i++) {
         if (argv[1][i] == '.') {
            type_flag = (toupper(argv[1][i + 1]) == 'E') ? 1 : 0;
            break;
         }
      }

      if ((fp = fopen(argv[1], "r+b")) != NULL) {
         if (!fread(&bufr, sizeof(bufr), 1, fp)) {
            printf("Unable to read %s.\n\n", argv[1]);
         }
         else {

            /* Modify the file. */

            bufr[0x139 + (type_flag * 0x20)] = 0x90; /* NOP */
            bufr[0x13a + (type_flag * 0x20)] = 0x90; /* NOP */
            bufr[0x1fc + (type_flag * 0x20)] = 0x90; /* NOP */
            bufr[0x1fd + (type_flag * 0x20)] = 0x90; /* NOP */
            bufr[0x1fe + (type_flag * 0x20)] = 0xb0; /* MOV AL, 59 */
            bufr[0x1ff + (type_flag * 0x20)] = 0x59;
            bufr[0x268 + (type_flag * 0x20)] = 0x90; /* NOP */
            bufr[0x269 + (type_flag * 0x20)] = 0x90; /* NOP */
            bufr[0x2c3 + (type_flag * 0x20)] = 0xc3; /* RET */

            if (!fseek(fp, 0L, SEEK_SET)) {
               if (!fwrite(&bufr, sizeof(bufr), 1, fp)) {
                  result = 1;
               }
            }
            else {
               result = 1;
            }
         }
         fclose(fp);
      }
      else {
         result = 1;
      }
   }
   if (result) {
      printf("Error: Unable to perform I/O on %s.\n\n", argv[1]);
   }

   return (result);
}