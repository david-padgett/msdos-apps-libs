/* File        : REALNAME.C
   Module      : REALNAME
   System      : REALNAME
   Description : Determines the full name of a file.
   Modified    : 05/06/91 DWP Created.
   Notes       :
*/

#include <ctype.h>
#include <dos.h>
#include <errno.h>
#include <stdio.h>

#include "MSDOS\msdos.h"

/* Global Variables and data. */

char realname_text[] = "REALNAME";

/* Function    : main
   Description : The main entry point for the REALNAME program.  Displays the full path and name of the specified file.  An
                 environment variable named 'REALNAME' is set in the master environment if the command-line switch '-E' is
                 specified.
   Expects     : The parameters specified on the command-line.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 05/06/91 DWP Initial coding.
   Notes       :
*/
int main(int argc, char *argv[]) {
   char    *file_name, real_name[256], adjusted_real_name[256];
   BOOLEAN continue_flag = FALSE, set_environment_variable_flag;
   int     result = EZERO;

   printf("\n%s V1.0, " COMPILE_DATE ", Copyright (c) 1991 by CSFX\n", realname_text);

   /* Proceed only if REALNAME is running under DOS 3.0 or greater. */

   if (_osmajor < 3) {
      printf("\n%s : Requires DOS 3.xx or later.\n", realname_text);
   }
   else {

      /* Initialize the control variables if their values were specified on the command-line. */

      if (argc >= 1 && argc <= 3) {

         set_environment_variable_flag = ((argv[1][0] == '-' || argv[1][0] == '/') && (toupper(argv[1][1]) == 'E' || toupper(argv[1][1]) == 'A')) ? TRUE : FALSE;
         file_name = (set_environment_variable_flag) ? argv[2] : argv[1];

         if (argc == 2 || (argc == 3 && set_environment_variable_flag)) {
            continue_flag = TRUE;
         }
      }

      /* Display the help screen if the control parameters were not correctly specified. */

      if (!continue_flag) {
         printf("\n   Purpose : Reveals the complete name of a file, directory, or device.\n\n");
         printf("   Usage   : %s {{[- | /][Switch]} [FileName]}\n\n", realname_text);
         printf("   Switches\n\n%6sE = Set environment variable %s to the real name of the file\n%6sA = Same as E, but use adjusted real name\n", "", realname_text, "");
      }
      else {

         /* Determine the true name of the specified file.  If an error occurs, exit. */

	 if ((result = DOS_Qualify_File_Specification(real_name, file_name)) != EZERO || DOS_Retrieve_Real_Name(file_name, adjusted_real_name) == DOS_INVALID_FILE_SPECIFICATION) {
            printf("\n%s : Unable to resolve %s.\n", realname_text, file_name);
         }
         else {

            /* Set the environment variable 'REALNAME' to the value of the true name of the specified file, if that action was
               requested. */

            if (set_environment_variable_flag) {
               result = DOS_Set_Environment_Variable(DOS_Get_Root_PSP(), realname_text, (toupper(argv[1][1]) == 'E') ? real_name : adjusted_real_name);
            }
            else {

               /* Display the real name of the specified file. */

               printf("\nThe %s of '%s' is '%s'.\nThe adjusted %s of '%s' is '%s'.\n", realname_text, file_name, real_name, realname_text, file_name, adjusted_real_name);
            }
         }
      }
   }

   return (result);
}