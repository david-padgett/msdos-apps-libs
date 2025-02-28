/* File        : PORT2.C
   Module      : PORT
   System      : None.
   Description : A method for activating a port.
   Modified    : 05/05/92 DWP Created.
   Notes       :
*/

#include <conio.h>
#include <stdio.h>

#include "port0.h"

/* Function    : PORT_Activate
   Description : Sets the proper screen coordinates for a port.
   Inputs      : Port = The port to activate.
   Updates     : Nothing.
   Outputs     : Nothing.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 05/05/92 DWP Initial coding.
   Notes       :
*/

int PORT_Activate(PORT Port) {

   _PORT * port_descriptor;
   int     result;

   if ((port_descriptor = Port) == NULL) {

      result = PORT_PARAM;

   }
   else {

      if (port_descriptor->Border[0] == '\0') {

         window(port_descriptor->Starting_Column, port_descriptor->Starting_Row, port_descriptor->Starting_Column + port_descriptor->Width - 1, port_descriptor->Starting_Row + port_descriptor->Height - 1);

      }
      else {

         window(port_descriptor->Starting_Column + 1, port_descriptor->Starting_Row + 1, port_descriptor->Starting_Column + port_descriptor->Width - 2, port_descriptor->Starting_Row + port_descriptor->Height - 2);

      }

      result = PORT_NOERR;

   }

   return (result);

}

