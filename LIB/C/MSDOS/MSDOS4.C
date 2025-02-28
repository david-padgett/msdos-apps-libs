/* File        : MSDOS4.C
   Module      : MSDOS
   System      : None
   Description : A method for retrieving an environment variable associated with the root PSP.
   Modified    : 03/19/91 DWP Created.
   Notes       :
*/

#include <dos.h>
#include <string.h>

#include "msdos0.h"

/* Function    : DOS_Get_Environment_Variable
   Description : Retrieves the value of the specified environment variable.  The value is extracted from the root PSP environment.
   Inputs      : PSP      = The PSP whose environment will be queried.
                 Variable = The environment variable whose value is desired.
   Updates     : Nothing.
   Outputs     : Value    = The value of the specified environment variable (undefined upon entry).
   Returns     : The value of the specified environment variable, or NULL if the environment variable does not exist.
   Modified    : 03/19/91 DWP Initial coding.
   Notes       :
*/

char * DOS_Get_Environment_Variable(DOS_PSP far * PSP, char * Variable, char * Value) {

   char * environment;
   char * result;

   environment = MK_FP(PSP->Environment_Segment, 0);

   /* Attempt to locate the specified environment variable. */

   if ((result = _DOS_Get_Environment_Variable_Address(environment, Variable)) != NULL) {

      /* Copy the value of the environment buffer to the value parameter. */

      result = strcpy(Value, result + strlen(Variable) + 1);

   }

   return (result);

}
