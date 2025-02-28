/* File        : MSDOS4A.C
   Module      : MSDOS
   System      : None
   Description : A method for altering the value of an environment variable associated with the root PSP.
   Modified    : 03/19/91 DWP Created.
   Notes       :
*/

#include <alloc.h>
#include <dos.h>
#include <stdio.h>
#include <string.h>

#include "msdos0.h"

/* Function    : DOS_Set_Environment_Variable
   Description : Alters the value of the specified environment variable.
   Inputs      : PSP      = The PSP whose environment will be altered.
                 Variable = The environment variable whose value will be altered.
                 Value    = The new value of the specified environment variable.
   Updates     : Nothing.
   Outputs     : Nothing.
   Returns     : A value of zero if no errors occurred, otherwise, a value of -1.
   Modified    : 03/19/91 DWP Initial coding.
   Notes       :
*/
int DOS_Set_Environment_Variable(DOS_PSP far * PSP, char * Variable, char * Value) {

   char * environment;
   int    result;

   environment = MK_FP(PSP->Environment_Segment, 0);

   /* Determine if the variable is to be altered or removed. */

   if (*(Value) != '\0') {

      result = (_DOS_Get_Environment_Variable_Address(environment, Variable) != NULL) ? DOS_Alter_Environment_Variable(environment, Variable, Value) : DOS_Add_Environment_Variable(environment, Variable, Value);

   }
   else {

      DOS_Delete_Environment_Variable(environment, Variable);
      result = 0;

   }

   return (result);

}
