/* File        : FCOMP.C
   Module      : FILE_COMPARE
   System      : FILE_COMPARE
   Description : This program compares two files, byte by byte, and reports
                 any differences encountered during the comparison.
   Modified    : 01/29/91 DWP Created.
*/

#include <alloc.h>
#include <dir.h>
#include <stdio.h>
#include <string.h>

#include "standard\standard.h"

#define BUFR_SIZE 32767

/* Procedures and Functions. */

/* Function    : main
   Description : This program compares two files, byte by byte, and reports any differences encountered during the comparison.  The
                 two files to be compared are specified on the command line.  In addition, output can be redirected by specifying
                 an output file.  Any output from FILECOMP will be appended to the specified output file.
   Expects     : See Notes.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 01/29/91 DWP Initial coding.
                 07/10/91 DWP Cleanup.
   Notes       :
*/
int main(int argc, char *argv[]) {
   FILE        *fp_1, *fp_2;
   BYTE        *bufr_1, *bufr_2;
   CARDINAL_32 absolute_file_position, number_of_differences, file_1_length, file_2_length;
   BOOLEAN     output_flag = TRUE;
   char        file_1[MAXPATH] = "\0", file_2[MAXPATH] = "\0";
   size_t      bufr_1_size, bufr_2_size, i;
   int         result = 1;

   printf("\nFCOMP V1.0, " COMPILE_DATE ", Copyright (c) 1991 by CSFX\n");

   if (argc == 1) {
      printf("\n   Purpose : Performs a binary image comparison of two files.\n\n");
      printf("   Usage   : {{[- | /][Switch]} [File_1] [File_2]}\n\n");
      printf("   Switches\n\n%6sS = Silent operation\n", "");
   }
   else {

      /* Process the command line arguments. */

      for (i = 1; i < argc; i++) {

         strupr(argv[i]);

         if (argv[i][0] == '-' || argv[i][0] == '/') {
            if (argv[i][1] == 'S') {
               output_flag = FALSE;
            }
         }
         else {
            if (strlen(file_1) == 0) {
               strcpy(file_1, argv[i]);
            }
            else {
               if (strlen(file_2) == 0) {
                  strcpy(file_2, argv[i]);
               }
            }
         }
      }

      if ((bufr_1 = malloc(BUFR_SIZE)) != NULL && (bufr_2 = malloc(BUFR_SIZE)) != NULL) {
         if ((fp_1 = fopen(file_1, "rb")) != NULL && (fp_2 = fopen(file_2, "rb")) != NULL) {
            if (setvbuf(fp_1, (char *) bufr_1, _IOFBF, BUFR_SIZE) == 0 && setvbuf(fp_2, (char *) bufr_2, _IOFBF, BUFR_SIZE) == 0) {

               printf("\nComparing files %s, %s.\n", file_1, file_2);
               absolute_file_position = 0L;
               number_of_differences = 0L;
               file_1_length = 0L;
               file_2_length = 0L;

               while (TRUE) {

                  file_1_length += (bufr_1_size = fread(bufr_1, 1, BUFR_SIZE, fp_1));
                  file_2_length += (bufr_2_size = fread(bufr_2, 1, BUFR_SIZE, fp_2));

                  for (i = 0; i < bufr_1_size && i < bufr_2_size; i++, absolute_file_position++) {

                     if (bufr_1[i] != bufr_2[i]) {

                        number_of_differences++;

                        if (output_flag) {
                           printf("\n%10lX: %02X %02X", absolute_file_position, bufr_1[i], bufr_2[i]);
                        }
                     }
                  }

                  if (bufr_1_size < BUFR_SIZE || bufr_2_size < BUFR_SIZE) {
                     break;
                  }
               }

               putchar('\n');

               if (bufr_1_size != bufr_2_size) {
                  printf("\n%s and %s are not the same size.\n", file_1, file_2);

                  /* Determine the size difference of the two files. */

                  if (bufr_1_size > bufr_2_size) {
                     number_of_differences += file_1_length - file_2_length;
                  }
                  else {
                     number_of_differences += file_2_length - file_1_length;
                  }
               }

               if (number_of_differences == 0L) {
                  printf("No Differences Encountered.\n");
               }
               else {
                  printf("\nThe files contain %ld differences.\n", number_of_differences);
               }
            }
         }
         else {
            printf("\nUnable to open files.\n");
         }

         if (fp_1 != NULL) {
            fclose(fp_1);
         }

         if (fp_2 != NULL) {
            fclose(fp_2);
         }
      }

      if (bufr_1 != NULL) {
         free(bufr_1);
      }

      if (bufr_2 != NULL) {
         free(bufr_2);
      }
   }

   return (result);
}