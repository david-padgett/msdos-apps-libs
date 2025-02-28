/* File        : MSDOS4C.C
   Module      : MSDOS
   System      : None
   Description : A method for adding an environment variable to an environment.
   Modified    : 03/20/91 DWP Created.
   Notes       :
*/

#include <stdio.h>
#include <string.h>

#include "msdos0.h"

/* Function    : DOS_Add_Environment_Variable
   Description : Adds the specified environment variable and its value to the specified environment.
   Inputs      : Environment = The environment whose contents are to be altered.
                 Variable    = The variable that is to be added.
                 Value       = The value of the variable that is to be added.
   Updates     : Nothing.
   Outputs     : Nothing.
   Returns     : A value of zero if no errors occurred, otherwise, a value of -1.
   Modified    : 03/20/91 DWP Initial coding.
   Notes       :
*/

int DOS_Add_Environment_Variable(char * Environment, char * Variable, char * Value) {

   int variable_length, value_length, result = -1;

   /* Determine if enough space exists in the environment to add the variable name, its value, and space for the '=' and '\0'
      characters needed to complete the string.  Note:  The remaining space in the environment is adjusted so the terminating
      '\0' character is not counted. */

   variable_length = strlen(Variable);
   value_length = strlen(Value);

   if (_DOS_Get_Environment_Variable_Address(Environment, Variable) == NULL && DOS_Get_Remaining_Space_In_Environment(Environment) >= variable_length + value_length + 3) {

      /* Locate the end of the environment.  The end of the environment always points to an '\0' character. */

      Environment += DOS_Get_Current_Size_Of_Environment(Environment) - 1;

      /* Place the new environment variable name in the environment and update the end of environment pointer. */

      strupr(strcpy(Environment, Variable));
      Environment += variable_length;

      /* Place the '=' character at the end of the environment and update the end of environment pointer. */

      *(Environment++) = '=';

      /* Place the environment variable's value in the environment, update the end of environment pointer, and then properly
         terminate the environment buffer and then exit. */

      strupr(strcpy(Environment, Value));
      Environment += value_length;
      result = *((int *) Environment) = 0;

   }

   return (result);

}