/* File        : XDEL.C
   Module      : XDEL
   System      : XDEL
   Description : This program allows entire directories to be deleted, regardless of their contents.
   Modified    : 05/02/91 DWP Created.
   Notes       :
*/

#include <conio.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

#include "dir\dir.h"
#include "msdos\msdos.h"
#include "list\list.h"

char XDEL_text[] = "XDEL";

/* Function    : XDEL_main
   Description : Deletes all of the directories in the specified list.
   Expects     : directory_list      = A list containing the fully qualified names of the directories which are to be deleted.
		 display_prompt_flag = Indicates whether or not to prompt the user before the directory and its contents are
				       deleted.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 05/02/91 DWP Initial coding.
   Notes       :
*/
int XDEL_main(LIST directory_list, BOOLEAN display_prompt_flag) {
   char        answer[6], *directory;
   CARDINAL_32 list_size;
   int         i, result;

   answer[0] = 0;

   /* Loop until all of the command-line parameters have been processed. */

   LIST_Size(directory_list, &list_size);
   for (i = 1, result = EZERO; result == EZERO && i <= list_size; i++) {

      /* Delete the directory currently being processed if the display prompt flag is FALSE, or if the user confirms by entering
	 'YES' at the prompt. */

      if (display_prompt_flag) {

	 LIST_Retrieve(directory_list, i, (void**) &directory);
	 printf("\n%s : Delete %s ['YES' or 'NO'] : ", XDEL_text, directory);
	 gets(answer);
	 putchar('\n');

	 if (stricmp(answer, "YES") != 0) {
            continue;
         }
      }

      LIST_Retrieve(directory_list, i, (void **) &directory);
      result = DIR_Delete_Directory(directory);
   }

   return (result);
}

/* Function    : main
   Description : The main entry point for the XDEL program.
   Expects     : argv[1] = The directory to delete.  This is an optional parameter.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 05/02/91 DWP Initial coding.
   Notes       :
*/
int main(int argc, char *argv[]) {
   LIST           directory_list;
   DOS_FILE_TYPES current_file_type;
   char           current_directory[256], current_argument[MAXPATH];
   BOOLEAN        display_prompt_flag = TRUE;
   int            i, result = 0;

   printf("\n%s V1.0, " COMPILE_DATE ", Copyright (c) 1991 by CSFX\n", XDEL_text);

   /* Display the help screen if no command-line parameters were given. */

   if (argc == 1) {
      printf("\n   Purpose : Deletes entire directories.\n\n");
      printf("   Usage   : %s {{[- | /][Command]} [Directory]}\n\n", XDEL_text);
      printf("   Commands\n\n%6sNC = Override confirmation prompt\n\n", "");
      printf("   Warning\n\n%6s%s removes entire directories.  Use with extreme caution.\n", "", XDEL_text);
   }
   else {

      /* Initialize the directory list, and then collect and qualify all of the command-line directory arguments. */

      LIST_Constructor(MAXPATH, &directory_list);

      for (i = 1; i < argc; i++) {

	 /* If the "NC" switch was specified, re-initialize the over-ride prompt flag. */

	 if ((argv[i][0] == '-' || argv[i][0] == '/') && stricmp(&(argv[i][1]), "NC") == 0) {
	    display_prompt_flag = FALSE;
	    continue;
	 }

	 /* Add the next command-line argument to the list only if it is a valid directory. */

	 if ((current_file_type = DOS_Retrieve_Real_Name(argv[i], current_argument)) != DOS_INVALID_FILE_SPECIFICATION && current_file_type != DOS_DEVICE) {

	    /* If a trailing backslash is present, remove it. */

	    if (current_argument[strlen(current_argument) - 1] == '\\') {
	       current_argument[strlen(current_argument) - 1] = '\0';
	    }

	    LIST_Insert(current_argument, LIST_LAST, directory_list);
	 }
      }

      /* Determine the current directory, then switch to the root directory.  If an error occurs, exit. */

      if (getcwd(current_directory, sizeof(current_directory) - 1) == NULL || chdir("\\") != 0) {
	 result = errno;
      }
      else {

	 /* Delete the specified directories. */

	 result = XDEL_main(directory_list, display_prompt_flag);

	 /* Return to the original directory, if possible. */

	 chdir(current_directory);
      }

      LIST_Destructor(&directory_list);
   }

   if (result != EZERO) {
      printf("\n%s : One or more errors occurred, aborting.\n", XDEL_text);
   }

   return (result);
}