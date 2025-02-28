/* File        : ALLOCDSK.C
   Module      : ALLOCDSK
   System      : ALLOCDSK
   Description : Allocates disk space to temporary files.
   Modified    : 07/22/91 DWP Initial coding.
   Notes       : 1) Usage

                       ALLOCDSK {[FileSize] [FileSpec]}

                    FileSize : The number of bytes to allocate.
                    FileSpec : The name of the file to create.
*/

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Global data. */

char ALLOCDSK_Text[] = "\nThis is a temporary disk file created by CSFX's ALLOCDSK.\n\x1a";

/* Procedures and Functions. */

/* Function    : ALLOCDSK_Main
   Description : The entry point to the ALLOCDSK module.
   Inputs      : file_name = The name of the file to create.
                 file_size = The size of the file to create.
   Updates     : Nothing.
   Outputs     : Nothing.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 07/22/91 DWP Initial coding.
   Notes       :
*/

int ALLOCDSK_Main(char * File_Name, unsigned long File_Size) {

   FILE * file;
   char   str[sizeof(ALLOCDSK_Text)];
   int    result = EZERO;

   /* The minimum minimum amount of space that may be allocated is 512 bytes. */

   if (File_Size < 512) {

      result = EINVAL;

   }
   else {

      /* If the file already exists, check to see if it is a file created by ALLOCDSK, if not, then exit. */

      if ((file = fopen(File_Name, "rb")) != NULL) {

         fread(str, sizeof(str), 1, file);

         if (memcmp(str, ALLOCDSK_Text, sizeof(ALLOCDSK_Text)) != 0) {

            result = EEXIST;

         }

         fclose(file);

      }

      /* Continue only if no errors occurred above. */

      if (result == EZERO) {

         /* Truncate the file to zero bytes. */

         if ((file = fopen(File_Name, "wb")) == NULL) {

            result = ENOPATH;

         }
         else {

            fclose(file);

            /* Attempt to open the file, exit if an error occurs. */

            if ((file = fopen(File_Name, "r+b")) == NULL) {

               result = ENOPATH;

            }
            else {

               /* Write the header to the file, exit if an error occurs. */

               if (fwrite(ALLOCDSK_Text, sizeof(ALLOCDSK_Text), 1, file) != 1) {

                  result = EACCES;

               }
               else {

                  /* Extend the size of the file to the size that was specified. */

                  result = (fseek(file, File_Size - (unsigned long) sizeof(ALLOCDSK_Text), SEEK_SET) == 0 && fwrite(ALLOCDSK_Text, sizeof(ALLOCDSK_Text), 1, file) == 1) ? EZERO : EACCES;

               }

               fclose(file);

            }

         }

      }

   }

   return (result);

}

/* Function    : main
   Description : The entry point to the ALLOCDSK program.
   Inputs      : argv[1] = The size of the file to create.
                 argv[2] = The name of the file to create.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 07/22/91 DWP Initial coding.
   Notes       :
*/

int main(int argc, char * argv[]) {

   char * str;
   int    i, result;

   printf("\nALLOCDSK V1.0, " COMPILE_DATE ", Copyright (c) 1991 by CSFX\n");

   if (argc < 2) {

      printf("\nPurpose : Temporarily allocates disk space to a file.\n");
      printf("\nUsage   : ALLOCDSK {<FileSize> <FileName>}\n");
      printf("\nWhere\n\n%6sFileSize = The number of bytes of disk space to allocate.\n%6sFileName = The file to create.\n", "", "");
      result = EZERO;

   }
   else {

      for (i = 1, result = EZERO; result == EZERO && i < argc;) {

	 char * file_name = argv[i++];
	 char * file_size = argv[i++];
	 result = ALLOCDSK_Main(file_name, strtoul(file_size, &str, 10));

      }

   }

   if (result != EZERO) {

      switch (result) {

         case EACCES  : str = "Invalid Access";
                        break;

         case EEXIST  : str = "File Already Exists";
                        break;

         case EINVAL  : str = "Invalid Parameter";
                        break;

         case ENOPATH : str = "Invalid File Name";
                        break;

         default      : str = "Unknown";

      }

      printf("\nALLOCDSK Error : %s.\n", str);

   }

   return (result);

}
