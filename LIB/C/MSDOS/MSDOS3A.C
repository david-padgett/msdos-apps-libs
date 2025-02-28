/* File        : MSDOS3A.C
   Module      : MSDOS
   System      : None
   Description : A method for determining the number of bytes used in an environment.
   Modified    : 03/19/91 DWP Created.
   Notes       :
*/

#include <stdio.h>

#include "msdos0.h"

/* Function    : DOS_Get_Current_Size_Of_Environment
   Description : Determines the number of bytes used in the environment associated with the specified PSP.
   Inputs      : Environment = The environment to inspect.
   Updates     : Nothing.
   Outputs     : Nothing.
   Returns     : The size in bytes of the specified environment.
   Modified    : 03/19/91 DWP Initial coding.
   Notes       :
*/

int DOS_Get_Current_Size_Of_Environment(char * Environment) {

   int result;

   for (result = 1; *Environment != '\0'; result++) {

      while (*(Environment++) != '\0') {

         result++;

      }
   }

   return (result);

}