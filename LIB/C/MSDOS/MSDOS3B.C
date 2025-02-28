/* File        : MSDOS3B.C
   Module      : MSDOS
   System      : None
   Description : Determines the number of unused bytes in an environment.
   Modified    : 03/20/91 DPW Created.
   Notes       :
*/

#include "msdos0.h"

/* Function    : DOS_Get_Remaining_Space_In_Environment
   Description : Calculates the number of unused bytes in the envrionment associated with the specified PSP.
   Inputs      : Environment = The envrionment to inspect.
   Updates     : Nothing.
   Outputs     : Nothing.
   Returns     : The number of unused bytes in the specified environment.
   Modified    : 03/02/91 DWP Initial coding.
   Notes       :
*/

int DOS_Get_Remaining_Space_In_Environment(char * Environment) {

   int result;

   result = DOS_Get_Environment_Size(Environment) - DOS_Get_Current_Size_Of_Environment(Environment);

   return (result);

}