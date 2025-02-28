/* File        : MSDOS4B.C
   Module      : MSDOS
   System      : None
   Description : A method for altering the contents of an environment variable.
   Modified    : 03/20/91 DWP Created.
   Notes       :
*/

#include <string.h>

#include "msdos0.h"

/* Function    : DOS_Alter_Environment_Variable
   Description : Alters the contents of the specified environment variable which is located in the specified environment.
   Inputs      : Environment = The environment whose contents are to be altered.
                 Variable    = The variable whose value is to be altered.
                 Value       = The new value of the specified environment variable.
   Updates     : Nothing.
   Outputs     : Nothing.
   Returns     : A value of zero if no errors occurred, otherwise, a value of -1.
   Modified    : 03/20/91 DWP Initial coding.
   Notes       :
*/

int DOS_Alter_Environment_Variable(char * Environment, char * Variable, char * Value) {

   char * variable_address;
   char * current_value;
   size_t value_length, current_value_length;
   int    result = -1;

   /* Make sure the environment variable actually exists.  */

   if ((variable_address = _DOS_Get_Environment_Variable_Address(Environment, Variable)) != NULL) {

      /* Locate the starting address of the value of the environment variable that is being changed. */

      current_value = variable_address + strlen(Variable) + 1;
      value_length = strlen(Value);
      current_value_length = strlen(current_value);

      /* Make sure altering the current value won't cause the environment to grow larger than its maximum allowable size. */

      if (DOS_Get_Remaining_Space_In_Environment(Environment) + current_value_length > value_length) {

         /* Alter the environment variable's value and exit. */

         memmove(current_value + value_length + 1, current_value + current_value_length + 1, DOS_Get_Current_Size_Of_Environment(current_value + current_value_length + 1));
         strupr(strcpy(current_value, Value));
         result = 0;

      }

   }

   return (result);

}