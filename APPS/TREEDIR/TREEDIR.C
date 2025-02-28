/* File        : TREEDIR.C
   Module      : TREEDIR
   System      : TREEDIR
   Description : This program displays the directory tree structure of the specified disk drive.
   Modified    : 01/31/91 DWP Created.
   Notes       :
*/

#include <dir.h>
#include <dos.h>
#include <stdio.h>
#include <string.h>

#include "standard\standard.h"
#include "dir\dir.h"

#define DIRECTORY_SLASH '\\'

/* Global Variables. */

BOOLEAN TREEDIR_Last_Directory_Flag_Stack[256];
char    TREEDIR_Lines[7] = "ÄÀÂÃ³ ";

/* Functions and Procedures. */

/* Procedure   : TREEDIR_Main
   Description : Recursively displays the tree structure of the specified path.  All directories whose path includes the specified
                 path are displayed.
   Inputs      : Path  = The path whose directory tree is to be displayed.
                 Level = The level of the specified path.
   Updates     : Nothing.
   Outputs     : Nothing.
   Returns     : Nothing.
   Modified    : 01/31/91 DWP Initial coding.
   Notes       :
*/

void TREEDIR_Main(char * Path, int Level) {

   struct ffblk current_file, next_file;
   char         current_path[MAXPATH], new_path[MAXPATH];
   int          i, count;

   /* Initialize the local variables. */

   count = 0;
   sprintf(current_path, "%s\\*.*", Path);
   Level++;

   /* Start the process of looking for directory entries. */

   if (DIR_FindFirst(current_path, FA_DIREC, &current_file)) {

      /* Loop until there are no more directory entries to process. */

      do {

         /* Make sure the current file is a valid directory. */

         if (strncmp(current_file.ff_name, "..", strlen(current_file.ff_name)) != 0) {

            /* Save the current DTA record. */

            memcpy(&next_file, &current_file, sizeof(next_file));

            /* Loop until the indentation depth corresponds to the current level. */

            for (i = 0; i < Level * 10; i++) {

               /* Print a vertical line that joins directories at the same level, if necessary. */

               if (i % 10 == 0) {

                  putchar(TREEDIR_Lines[(TREEDIR_Last_Directory_Flag_Stack[i / 10]) ? 5 : 4]);

               }
               else {

                  if (count == 0 && i == ((Level - 1) * 10) + 1) {

                     /* Print the graphics for the first sub-directory of the current directory, if necessary. */

                     printf(" %c", TREEDIR_Lines[1]);
                     i++;

                  }
                  else {

                     /* Print the graphics for the horizontal connecting lines, if necessary. */

                     putchar((count > 0 || i < (Level - 1) * 10) ? TREEDIR_Lines[5] : TREEDIR_Lines[0]);

                  }

               }

            }

            /* Print the name of the current directory. */

            printf("%c %s\n", TREEDIR_Lines[((count > 0) ? 1 : 0) + ((DIR_FindNext(current_path, FA_DIREC, &current_file)) ? 2 : 0)], next_file.ff_name);
            memcpy(&current_file, &next_file, sizeof(current_file));

            /* Increment the number of directories found at the current level, build the name for the next directory to process,
               and then process it. */

            count++;
            sprintf(new_path, "%s%c%s", Path, DIRECTORY_SLASH, current_file.ff_name);
            TREEDIR_Last_Directory_Flag_Stack[Level] = !DIR_FindNext(current_path, FA_DIREC, &current_file);
            memcpy(&current_file, &next_file, sizeof(current_file));
            TREEDIR_Main(new_path, Level);

         }

      } while (DIR_FindNext(current_path, FA_DIREC, &current_file));

   }

}

/* Function    : main
   Description : The main entry point for the TREEDIR program.
   Inputs      : Nothing.
   Updates     : Nothing.
   Outputs     : Nothing.
   Returns     : Always returns a value of 0.
   Modified    : 01/31/91 DWP Initial coding.
   Notes       : 1) Any parameters given on the command line are assumed to be directories, and will be processed as such.
*/

int main(int argc, char * argv[]) {

   size_t path_length;
   char   path[MAXPATH];
   int    i;

   /* Loop until all of the command line parameters have been processed. */

   for (i = 1; i <= argc; i++) {

      /* If no parameters were given, then process the current directory only, otherwise, process the next command line
         parameter. */

      if (argc == 1) {

         getcwd(path, MAXPATH);

      }
      else {

         /* Exit the loop if the last parameter has been processed. */

         if (i == argc) {

            break;

         }

         strcpy(path, argv[i]);

      }

      printf("\nTREEDIR V1.0, " COMPILE_DATE ", Copyright (c) 1991 by CSFX\n\nDirectory of %s\n\n", path);

      /* Make sure that a trailing slash is not present. */

      path_length = strlen(path) - 1;

      if (path[path_length] == DIRECTORY_SLASH) {

         path[path_length] = '\0';

      }

      /* Process the next directory. */

      TREEDIR_Main(path, -1);

   }

   return (0);

}
