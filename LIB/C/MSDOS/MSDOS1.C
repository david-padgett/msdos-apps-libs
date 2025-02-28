/* File        : MSDOS1.C
   Module      : MSDOS
   System      : None
   Description : A method for determining the address of an environment variable.
   Modified    : 03/19/91 DWP Created.
   Notes       :
*/

#include <dos.h>
#include <string.h>

#include "msdos0.h"

/* Function    : _DOS_Get_Environment_Variable_Address
   Description : Retrieves the address of the specified environment variable which is associated with the specified environment.
   Inputs      : Environment = The environment to query.
		 Variable    = The environment variable whose address is desired.
   Updates     : Nothing.
   Outputs     : Nothing.
   Returns     : The address of the specified environment variable, or NULL if the variable is undefined.
   Modified    : 03/19/91 DWP Initial coding.
   Notes       :
*/

char * _DOS_Get_Environment_Variable_Address(char * Environment, char * Variable) {

   char * result;
   int    i, search_variable_length;

   result = NULL;
   search_variable_length = strlen(Variable);

   /* Repeat until all of the environment variables have been processed. */

   for (i = 0; Environment[i] != '\0' && i < 32767; i += strlen(Environment + i) + 1) {

      /* Determine if the correct variable has been located, if so, save its address and exit. */

      if (strnicmp(Variable, Environment + i, search_variable_length) == 0 && Environment[i + search_variable_length] == '=') {

         result = Environment + i;
         break;

      }

   }

   return (result);

}
