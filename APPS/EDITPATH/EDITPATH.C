/* File        : EDITPATH.C
   Module      : EDITPATH
   System      : EDITPATH
   Description : A master environment path editor.
   Modified    : 05/06/91 DWP Created.
   Notes       :
*/

#include <alloc.h>
#include <ctype.h>
#include <dos.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

#include "msdos\msdos.h"
#include "list\list.h"

/* Function    : EDITPATH_Rebuild_Path_Value
   Description : Reconstructs the value of the PATH variable whose elements are contained in the specified list.
   Inputs      : Path_List         = The list which contains the components of a PATH.
                 Path_Value_Length = The size in bytes required for the Path_Value buffer.
   Updates     : Nothing.
   Outputs     : Path_Value        = The buffer in which to place the reconstituted PATH.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 06/28/91 DWP Initial coding.
   Notes       :
*/

int EDITPATH_Rebuild_Path_Value(LIST Path_List, int Path_Value_Length, char ** Path_Value) {

   int i, result;
   char * list_element;
   CARDINAL_32 list_size;

   /* Allocate memory for the PATH value, exit if an error occurs. */

   if ((* Path_Value = malloc(Path_Value_Length)) == NULL) {

      result = ENOMEM;

   }
   else {

      /* Build an exact copy of the current PATH value. */

      result = EZERO;
      * Path_Value[0] = '\0';

      LIST_Size(Path_List, &list_size);
      for (i = 0; i < list_size; i++) {

	 if (* Path_Value[0] != '\0') {

	    strcat(* Path_Value, ";");

	 }

	 LIST_Retrieve(Path_List, i, (void **) &list_element);
	 strcat(*(Path_Value), list_element);

      }

   }

   return (result);

}


/* Function    : EDITPATH_Add_To_Path
   Description : Adds the specified path spec to the PATH environment variable which is located in the specified environment.
   Inputs      : Environment        = The environment to alter.
		 Path_List          = A list of the components of the PATH environment variable which resides in the specified
				      environment.
		 Path_Spec          = The path spec that is to be added to the PATH environment variable.
		 Front_Of_List_Flag = A flag indicating where in the PATH list to add the new path spec.  If TRUE, then the path
				      spec is added at the beginning of the list, otherwise, it is added at the end of the list.
   Updates     : Nothing.
   Outputs     : Nothing.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 06/27/91 DWP Initial coding.
   Notes       :
*/

int EDITPATH_Add_To_Path(char * Environment, LIST Path_List, char * Path_Spec, BOOLEAN Front_Of_List_Flag) {

   char *      new_path_value;
   int         i, new_path_length, result = EZERO;
   CARDINAL_32 list_size;
   char *      list_element;

   /* Determine how much space is occupied by the current value of the PATH environment variable. */

   LIST_Size(Path_List, &list_size);
   for (i = 0, new_path_length = strlen(Path_Spec) + 1; i < list_size; i++) {

      /* If the path spec that is to be added is already in the current path, abort the process. */

      LIST_Retrieve(Path_List, i, (void **) &list_element);
      if (stricmp(Path_Spec, list_element) == 0) {

	 result = EEXIST;
	 break;

      }

      /* Calculate the total length of the new value for the PATH variable. */

      LIST_Retrieve(Path_List, i, (void **) &list_element);
      new_path_length += strlen(list_element) + 1;

   }

   /* Do not continue if an error occurred. */

   if (result == EZERO) {

      /* Build an exact copy of the current PATH value. */

      if ((result = EDITPATH_Rebuild_Path_Value(Path_List, new_path_length, &new_path_value)) == EZERO) {

	 if (Front_Of_List_Flag) {

	    /* Place the new path spec at the beginning of the PATH list. */

	    memmove(new_path_value + strlen(Path_Spec) + 1, new_path_value, strlen(new_path_value) + 1);
	    strcpy(new_path_value, Path_Spec);
	    new_path_value[strlen(Path_Spec)] = ';';

	 }
	 else {

	    /* Append the new path spec to the end of the PATH list. */

	    strcat(new_path_value, ";");
	    strcat(new_path_value, Path_Spec);

	 }

	 result = DOS_Alter_Environment_Variable(Environment, "PATH", new_path_value);
	 free(new_path_value);

      }

   }

   return (result);

}

/* Function    : EDITPATH_Remove_From_Path
   Description : Removes the specified path spec from the PATH environment variable of the specified environment.
   Inputs      : Environment = The environment to alter.
		 Path_List   = A list of the components of the PATH environment variable which resides in the specified environment.
		 Path_Spec   = The path spec that is to be removed from the PATH environment variable.
   Updates     : Nothing.
   Outputs     : Nothing.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 06/27/91 DWP Initial coding.
   Notes       :
*/

int EDITPATH_Remove_From_Path(char * Environment, LIST Path_List, char * Path_Spec) {

   char *      new_path_value;
   int         i, new_path_length, result = ENOENT;
   CARDINAL_32 list_size;
   char *      list_element;

   /* Determine the new size of the PATH value, also determine if the specified path spec is actually in the PATH. */

   LIST_Size(Path_List, &list_size);
   for (i = new_path_length = 0; i < list_size;) {

      /* Count the current list element if it is not the element being deleted. */

      LIST_Retrieve(Path_List, i, (void **) &list_element);
      if (stricmp(Path_Spec, list_element) != 0) {

	 LIST_Retrieve(Path_List, i++, (void **) &list_element);
	 new_path_length += strlen(list_element) + 1;

      }
      else {

         /* Remove the element from the list, and reset the error code so that the PATH will actually be modified. */

         LIST_Delete(i, Path_List, NULL);
         result = EZERO;

      }

   }

   /* Do not continue if the specified path spec was not in the PATH value. */

   if (result == EZERO) {

      /* Rebuild the PATH value.  If no errors occurred, alter the value of the PATH variable. */

      if ((result = EDITPATH_Rebuild_Path_Value(Path_List, new_path_length, &new_path_value)) == EZERO) {

         result = DOS_Alter_Environment_Variable(Environment, "PATH", new_path_value);
         free(new_path_value);

      }

   }

   return (result);

}

/* Function    : EDITPATH_Construct_Path_List
   Description : Builds a list of the path specs in the current master environment path variable.
   Inputs      : Environment = The environment of the PATH variable whose components are to be placed in a list.
                 Path_List   = The list in which to store the components of the PATH variable.
   Updates     : Nothing.
   Outputs     : Nothing.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 06/27/91 DWP Initial coding.
   Notes       :
*/

int EDITPATH_Construct_Path_List(DOS_PSP * PSP, char * Environment, LIST Path_List) {

   char * variable_value, path_spec[256];
   int    environment_size, current_path_spec_length, i, result;

   /* Determine the size of the master environment, exit if it has no size. */

   if ((environment_size = DOS_Get_Environment_Size(Environment)) == EZERO) {

      result = EINVENV;

   }
   else {

      /* Allocate memory for a copy of the PATH environment variable value. */

      if ((variable_value = malloc(environment_size)) == NULL) {

         result = ENOMEM;

      }
      else {

	 /* Determine if the PATH environment variable exists, if it doesn't exist, then exit. */

         if (strlen(DOS_Get_Environment_Variable(PSP, "PATH", variable_value)) == 0) {

	    result = ENOPATH;

         }
         else {

            /* Loop until all of the path specs have been placed into the path list. */

            for (i = current_path_spec_length = 0, result = EZERO; result == EZERO; i++) {

	       /* If the end of a path spec has been found, place the path spec into the path list, exit if an error
                  occurs or if the end of the path value has been reached. */

               if (variable_value[i] != ';' && variable_value[i] != '\0') {

                  current_path_spec_length++;

               }
               else {

                  /* Copy the path spec currently being processed into a temporary buffer. */

                  sprintf(path_spec, "%.*s", current_path_spec_length, variable_value + i - current_path_spec_length);
		  current_path_spec_length = 0;

                  /* If the temporary path spec buffer contains a path spec, then add it to the path spec list. */

		  if (path_spec[0] != '\0') {

		     result = LIST_Insert(path_spec, LIST_LAST, Path_List);

                  }

                  /* Exit if the end of the PATH value has been reached. */

                  if (variable_value[i] == '\0') {

                     break;

                  }

               }

            }

         }

         free(variable_value);

      }

   }

   return (result);

}

/* Function    : EDITPATH_Main
   Description : Adds or removes the specified path from the master environment path variable.
   Inputs      : Add_Flag           = Determines what action to take.  If TRUE, then the path specification is added to the path,
                                      otherwise, the path specification is removed from the path.
                 Front_Of_List_Flag = Determines where in the list the additions are to take place.  If TRUE, then additions are
				      made at the beginning of the PATH variable, otherwise, additions are made at the end of
				      the PATH variable.
		 Path_Spec          = The path specification that is either going to be added or removed from the path.
   Updates     : Nothing.
   Outputs     : Nothing.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 05/06/91 DWP Initial coding.
   Notes       :
*/

int EDITPATH_Main(BOOLEAN Add_Flag, BOOLEAN Front_Of_List_Flag, char *Path_Spec) {

   LIST      path_list;
   DOS_PSP * root_PSP;
   char *    master_environment;
   int       result;

   /* Locate the root PSP, exit if it cannot be found. */

   if ((root_PSP = DOS_Get_Root_PSP()) == NULL) {

      result = EINVMEM;

   }
   else {

      /* Locate the master environment, exit if it cannot be found. */

      if ((master_environment = MK_FP(root_PSP->Environment_Segment, 0)) == NULL) {
	 result = EINVENV;

      }
      else {

	 /* Construct the path list, exit if an error occurs. */

	 LIST_Constructor(256, &path_list);

	 if ((result = EDITPATH_Construct_Path_List(root_PSP, master_environment, path_list)) == EZERO) {

	    /* Perform the requested operation. */

	    result = (Add_Flag) ? EDITPATH_Add_To_Path(master_environment, path_list, Path_Spec, Front_Of_List_Flag) : EDITPATH_Remove_From_Path(master_environment, path_list, Path_Spec);

	 }

	 /* Destroy the path list. */

	 LIST_Destructor(&path_list);

      }

   }

   return (result);

}

/* Function    : main
   Description : The main entry point for the EDITPATH program.
   Inputs      : Nothing.
   Updates     : Nothing.
   Outputs     : Nothing.
   Returns     : The value of the last error that occurred.  A value of zero
		 indicates that no errors occurred.
   Modified    : 05/06/91 DWP Initial coding.
   Notes       :
*/

int main(int argc, char * argv[]) {

   BOOLEAN add_flag, front_of_list_flag;
   char    str[256];
   int     i, result = EZERO;

   printf("\nEDITPATH V1.0, " COMPILE_DATE ", Copyright (c) 1991 by CSFX\n");

   /* Display the help screen if no command-line parameters were given. */

   if (argc == 1) {

      printf("\n   Purpose : Alters the PATH variable in the master environment.\n\n");
      printf("   Usage   : EDITPATH {[(- | /)<Command>] <PathSpec>}\n\n");
      printf("   Commands\n\n%6sA  = Add to end of path (default)\n%6sAB = Add to beginning of path\n%6sR  = Remove from path\n", "", "", "");

   }
   else {

      /* Process the command-line parameters. */

      for (i = 1; result == EZERO && i < argc; i++) {

	 add_flag = TRUE;
	 front_of_list_flag = FALSE;

	 if (argv[i][0] == '-' || argv[i][0] == '/') {

	    switch (toupper(argv[i][1])) {

	       case 'A' :

		  if (toupper(argv[i][2]) == 'B') {
		     front_of_list_flag = TRUE;
		  }

		  break;

	       case 'R' :

		  add_flag = FALSE;
		  break;

	       default :

		  result = EINVAL;

	    }

	    i++;

	 }

	 if (result == EZERO) {

	    result = EDITPATH_Main(add_flag, front_of_list_flag, argv[i]);

         }

      }

   }

   if (result != 0) {

      switch (result) {

         case ENOENT :

            strcpy(str, "Path Spec Not Found");
            break;

         case EINVMEM :

            strcpy(str, "Invalid PSP");
            break;

         case ENOPATH :

            strcpy(str, "No Path Variable");
            break;

         case EINVENV :

            strcpy(str, "Invalid Environment");
            break;

         case ENOMEM :

            strcpy(str, "Out of Memory");
            break;

         case EEXIST :

            strcpy(str, "Duplicate PathSpec");
            break;

         case EINVAL :

            strcpy(str, "Invalid Argument");
            break;

         case -1 :

            strcpy(str, "Unable to Alter Environment");
            break;

         default :

            strcpy(str, "Unknown Error");

      }

      printf("\nEDITPATH Error : %s.\n", str);

   }

   return (result);

}