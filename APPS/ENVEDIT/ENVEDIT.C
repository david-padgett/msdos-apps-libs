/* File        : ENVEDIT.C
   Module      : ENVEDIT
   System      : ENVEDIT
   Description : This program allows variables in the master environment to be added, edited, or deleted.
   Modified    : 05/01/91 DWP Created.
   Notes       :
*/

#include <conio.h>
#include <ctype.h>
#include <dos.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

#include "msdos\msdos.h"
#include "kb\kb.h"

/* Function    : ENVEDIT_Modify_Environment
   Description : Performs the specified action on the specified environment variable.
   Inputs      : Action         = The action to perform, either add, edit, or delete (['A' | 'E' | 'D']).
                 Variable_Name  = The variable to modify.
                 Variable_Value = The new value of the variable that is to be modified.  This parameter is optional.  If this
                                  parameter is not specified, the user will be allowed to enter it from the keyboard in add and
                                  edit modes.  If this parameter is specified with the delete mode, the variable will only be
                                  deleted if it matches this value.  If no value is specified in delete mode, the variable will
                                  be deleted no matter what its value is.
   Updates     : Nothing.
   Outputs     : Nothing.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 05/01/91 DWP Initial coding.
   Notes       :
*/

int ENVEDIT_Modify_Environment(char Action, char * Variable_Name, char * Variable_Value) {

   DOS_PSP * root_psp;
   char *    master_environment;
   char *    environment_variable;
   char      value[81], str[256];
   int       result;

   /* Locate the root PSP and master environment. */

   root_psp = DOS_Get_Root_PSP();
   master_environment = MK_FP(root_psp->Environment_Segment, 0x0000);
   environment_variable = DOS_Get_Environment_Variable(root_psp, Variable_Name, str);

   /* Allow the user to input a new value, if necessary. */

   if (Action != 'D' && !(Action == 'A' && environment_variable != NULL) && !(Action == 'E' && environment_variable == NULL) && Variable_Value == NULL) {

      value[0] = sizeof(value) - 3;
      cgets(value);
      Variable_Value = &(value[2]);

   }


   /* Perform the specified action. */

   switch (Action) {

      case 'A' :

         result = (environment_variable != NULL) ? 1 : DOS_Add_Environment_Variable(master_environment, Variable_Name, Variable_Value);
         break;

      case 'E' :

         result = (environment_variable == NULL) ? 1 : DOS_Alter_Environment_Variable(master_environment, Variable_Name, Variable_Value);
         break;

      case 'D' :

         result = (environment_variable == NULL || (Variable_Value != NULL && stricmp(environment_variable, Variable_Value) != 0)) ? 1 : DOS_Delete_Environment_Variable(master_environment, Variable_Name);
         break;

      default :

         result = EINVDAT;

   }

   return (result);

}

/* Function    : main
   Description : The main entry point for the ENVEDIT program.
   Inputs      : argv[1] = The action to perform, either add, edit, or delete (['A' | 'E' | 'D']).
                 argv[2] = The name of the environment variable to modify.
                 argv[3] = The new value of the environment variable.  This is an optional parameter.  If this parameter is not
                           specified, the user will be allowed to enter it from the keyboard in add and edit modes.  If this
                           parameter is specified with the delete mode, the variable will only be deleted if it matches this value.
                           If no value is specified in delete mode, the variable will be deleted no matter what its value is.
   Updates     : Nothing.
   Outputs     : Nothing.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 05/01/91 DWP Initial coding.
   Notes       :
*/

int main(int argc, char * argv[]) {

   char *      variable_name;
   char *      variable_value;
   char        action;
   CARDINAL_16 i;
   BOOLEAN     exit_flag;
   int         result;

   printf("\nENVEDIT V1.0, " COMPILE_DATE ", Copyright (c) 1991 by CSFX\n");

   /* Initialize the control variables. */

   action = ' ';
   variable_name = variable_value = NULL;
   result = 0;

   /* Loop until all of the command line parameters have been evaluated. */

   for (i = 1, exit_flag = TRUE; i < argc; i++) {

      /* Determine if the next argument is a valid switch.  If so, extract the switch and continue processing the command-line
         parameters.  If the switch is not valid, then abort the program. */

      if (argv[i][0] == '-' || argv[i][0] == '/') {

         if (action == ' ' && strchr("AED", toupper(argv[i][1])) != NULL) {

            action = toupper(argv[i][1]);
            continue;

         }
         else {

            break;

         }

      }

      /* If no action has been specified, then abort the program. */

      if (action == ' ') {

         break;

      }

      /* If no variable name has been specified yet, use the current argument as the variable name. */

      if (variable_name == NULL) {

         variable_name = argv[i];
         exit_flag = FALSE;

      }
      else {

         /* If no variable value has been specified yet, use the current argument as the variable value. */

         if (variable_value == NULL) {

            variable_value = argv[i];

         }
         else {

            /* Exit the loop since no more parameters are needed to edit the environment variable. */

            break;

         }

      }

   }

   if (!exit_flag) {

      result = ENVEDIT_Modify_Environment(action, variable_name, variable_value);

   }

   else {

      printf("\n   Purpose : Adds, modifies, or deletes variables in the master environment.\n\n");
      printf("   Usage   : ENVEDIT {{[- | /][Command]} [VariableName] {[VariableValue]}}\n\n");
      printf("   Commands\n\n%6sA = Add Variables\n%6sE = Modify/Alter Variables\n%6sD = Delete Variables\n\n", "", "", "");
      printf("   Note\n\n%6sIf no value is specified with switches A or E, the interactive user is\n%6sprompted for the value.  If a value is specified with switch D, \n%6sthe variable will be deleted only if its value matches the specified\n%6svalue.  ERRORLEVEL is given a non-zero value when ENVEDIT cannot perform\n%6sthe requested action.\n\n", "", "", "", "", "");

   }

   return (result);

}