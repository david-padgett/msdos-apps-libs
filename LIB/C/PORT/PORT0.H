/* File        : PORT0.H
   Module      : PORT
   System      : None
   Description : The implementation header file for the PORT module.
   Modified    : 04/13/92 DWP Created.
   Notes       :
*/

#include "port.h"

/* Type Definitions. */

typedef struct __PORT_CHARACTER_DESCRIPTOR {

   char Character;
   char Attribute;

} _PORT_CHARACTER_DESCRIPTOR;

typedef struct __PORT {

   CARDINAL_16                  Starting_Row;
   CARDINAL_16                  Starting_Column;
   CARDINAL_16                  Height;
   CARDINAL_16                  Width;
   CARDINAL_16                  Port_Color;
   CARDINAL_16                  Border_Color;

   CARDINAL_16                  Cursor_Row;
   CARDINAL_16                  Cursor_Column;
   CARDINAL_16                  Text_Color;

   char                         Border[8];
   BOOLEAN                      Raised_Port;

   _PORT_CHARACTER_DESCRIPTOR * Save_Area;

} _PORT;
