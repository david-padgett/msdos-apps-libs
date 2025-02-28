/* File        : MSDOS4D.C
   Module      : MSDOS
   System      : None
   Description : A method for deleting an environment variable from an environment.
   Modified    : 03/20/91 DWP Created.
   Notes       :
*/

#include <string.h>

#include "msdos0.h"

/* Function    : DOS_Delete_Environment_Variable
   Description : Deletes the specified variable from the specified environment.
   Inputs      : Environment = The environment whose contents are to be altered.
                 Variable    = The environment variable that is to be removed from the specified environment.
   Updates     : Nothing.
   Outputs     : Nothing.
   Returns     : A value of zero if no errors occurred, otherwise, a value of -1.
   Modified    : 03/20/91 DWP Initial coding.
   Notes       :
*/

int DOS_Delete_Environment_Variable(char * Environment, char * Variable) {

   char * variable_address;
   char * source_address;
   int    result = -1;

   /* Determine if the specified variable actually exists in the environment. */

   if ((variable_address = _DOS_Get_Environment_Variable_Address(Environment, Variable)) != NULL) {

      /* Locate the end of the variable + value string that is to be removed from the environment.  Then move the remaining portion
         of the envrionment that exists beyond the deleted variable to the space occupied by the deleted variable. */

      source_address = variable_address + strlen(variable_address) + 1;
      memmove(variable_address, source_address, DOS_Get_Current_Size_Of_Environment(source_address));
      result = 0;

   }

   return (result);

}