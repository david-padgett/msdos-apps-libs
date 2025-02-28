/* File        : SCAN.C
   Module      : SCAN
   System      : SCAN
   Description : Searches for text strings in any type of file.
   Modified    : 07/09/91 DWP Initial coding.
   Notes       : 1) Usage : SCAN {{[- | /][Switch]} <[FileName]>...}

                    Switches

                       D  = Display offset of string in decimal
                       H  = Display offset of string in hexidecimal
                       W# = Set word length to # (default word length is 5)
*/

#include <alloc.h>
#include <ctype.h>
#include <dir.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#include "msdos\msdos.h"

/* Type definitions. */

typedef enum _SCAN_OFFSET_TYPES {SCAN_NO_OFFSET, SCAN_DECIMAL_OFFSET, SCAN_HEXIDECIMAL_OFFSET} SCAN_OFFSET_TYPES;

/* Procedures and Functions. */

/* Function    : SCAN_Process_File
   Description : The file processing portion of the SCAN module.  The specified file is scanned for text strings of the specified
                 length.  All text strings found are displayed to the standard output device.
   Inputs      : Offset_Type = The type of offset to display for each text string that is discovered.
                 Word_Length = The minimum length the text string must be for it to be displayed.
                 File        = The file to search.
   Updates     : Nothing.
   Outputs     : Nothing.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 07/09/91 DWP Initial coding.
   Notes       :
*/

int SCAN_Process_File(SCAN_OFFSET_TYPES Offset_Type, int Word_Length, FILE * File) {

   BOOLEAN     beginning_of_string_flag;
   char *      buffer;
   char        ch;
   CARDINAL_32 file_offset;
   int         buffer_length, result;

   /* Allocate space for the word buffer, exit if an error occurs. */

   if ((buffer = malloc(Word_Length)) == NULL) {

      result = ENOMEM;

   }
   else {

      buffer_length = 0;

      /* Loop until the entire file has been processed. */

      for (file_offset = 0L; fread(&ch, sizeof(ch), 1, File) == 1; file_offset++) {

         /* Determine if the character is printable, if not, then re-initialize the word buffer. */

         if (ch < ' ' || ch > '~') {

            buffer_length = 0;
            beginning_of_string_flag = TRUE;

         }
         else {

            /* If the word buffer is not full, add the character to it. */

            if (buffer_length < Word_Length) {

               buffer[buffer_length++] = ch;
               beginning_of_string_flag = TRUE;

            }

            /* If the word buffer is full, then either display the word buffer or the character currently being processed. */

            if (buffer_length == Word_Length) {

               /* Print the character if a new line has already been started, otherwise, start a new line and display the optional
                  offset. */

               if (!beginning_of_string_flag) {

                  putchar(ch);

               }
               else {

                  /* Start a new line.  Display the offset information, if necessary. */

                  printf("\n");

                  switch (Offset_Type) {

                     case SCAN_DECIMAL_OFFSET :

                        printf("%10lu : ", file_offset - (buffer_length - 1));
                        break;

                     case SCAN_HEXIDECIMAL_OFFSET :

                        printf("%10lx : ", file_offset - (buffer_length - 1));
                        break;
                  }

                  /* Display the word buffer. */

                  printf("%.*s", buffer_length, buffer);
                  beginning_of_string_flag = FALSE;

               }

            }

         }

      }

      /* Return the word buffer to the heap and initialize the return value. */

      putchar('\n');
      free(buffer);
      result = (feof(File)) ? EZERO : EINVDAT;

   }

   return (result);

}

/* Function    : SCAN_Main
   Description : The entry point to the SCAN module.
   Inputs      : Offset_Type = The type of offset to display for each text string that is discovered.
                 Word_Length = The minimum length the text string must be for it to be displayed.
                 File_Name   = The name of the file to search.
   Updates     : Nothing.
   Outputs     : Nothing.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 07/09/91 DWP Initial coding.
   Notes       :
*/

int SCAN_Main(SCAN_OFFSET_TYPES Offset_Type, int Word_Length, char * File_Name) {

   FILE * file;
   char * buffer;
   int    result;

   if ((file = fopen(File_Name, "rb")) == NULL) {

      result = ENOFILE;

   }
   else {

      if ((buffer = malloc(32767)) != NULL) {

         result = setvbuf(file, buffer, _IOFBF, 32767);

      }

      if (result == EZERO) {

         result = SCAN_Process_File(Offset_Type, Word_Length, file);

      }

      if (buffer != NULL) {

         free(buffer);

      }

      fclose(file);

   }

   return (result);

}

/* Function    : main
   Description : The entry point for the SCAN program.
   Inputs      : See Notes for a complete description of the command-line parameters.
   Updates     : Nothing.
   Outputs     : Nothing.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 07/09/91 DWP Initial coding.
   Notes       :
*/

int main(int argc, char * argv[]) {

   SCAN_OFFSET_TYPES offset_type;
   DOS_FILE_TYPES    file_type;
   char              file_name[256];
   int               i, word_length, result;

   printf("\nSCAN V1.0, " COMPILE_DATE ", Copyright (c) " COMPILE_YEAR " by CSFX\n");

   /* Do not continue if there were no command-line parameters specified. */

   if (argc == 1) {

      printf("\n   Purpose : Searches for text strings in any type of file.\n\n");
      printf("   Usage   : SCAN {{[- | /][Switch]} [FileName]}\n\n");
      printf("   Switches\n\n%6sD  = Display offset of string in decimal\n%6sH  = Display offset of string in hexidecimal\n%6sW# = Set word length to # (default word length is 5)\n", "", "", "");
      result = EINVAL;

   }
   else {

      /* Initialize the control parameters. */

      offset_type = SCAN_NO_OFFSET;
      word_length = 5;
      file_name[0] = '\0';
      result = EZERO;

      /* Loop until all of the command-line parameters have been processed. */

      for (i = 1; i < argc; i++) {

         /* Determine if the next parameter is a switch, if it isn't a switch, assume it is the name of the file to process. */

         if (argv[i][0] != '-' && argv[i][0] != '/') {

            file_type = DOS_Retrieve_Real_Name(argv[i], file_name);

            if (file_type == DOS_INVALID_FILE_SPECIFICATION || file_type == DOS_DEVICE) {

               result = EINVAL;

            }

         }
         else {

            switch (toupper(argv[i][1])) {

               case 'D' :

                  offset_type = SCAN_DECIMAL_OFFSET;
                  break;

               case 'H' :

                  offset_type = SCAN_HEXIDECIMAL_OFFSET;
                  break;

               case 'W' :

                  word_length = atoi(&(argv[i][2]));

                  if (word_length == 0) {

                     result = EINVDAT;

                  }

                  break;

               default  :

                  result = EINVAL;

            }

         }

         /* Proceed with the scan if no errors have occurred during parameter processing and a file name has been located. */

         if (result == EZERO && file_name[0] != '\0') {

            printf("\nScanning %s\n", file_name);
            result = SCAN_Main(offset_type, word_length, file_name);
            file_name[0] = '\0';

         }

         if (result != EZERO) {

            printf("\nSCAN : An unrecoverable error occurred, aborting.\n");
            break;

         }

      }

   }

   return (result);

}