/* File        : BGI.C
   Module      : TEXT
   System      : None
   Description : The graphics interface module for the BGI procedures and functions.
   Modified    : 02/27/92 DWP Created.
   Notes       :
*/

#include <conio.h>

#include "text_int.h"

/* Function    : BGI_TextAttr
   Description : Modifies the current character attribute.
   Inputs      : Window    = The window being accessed or modified.
                 Attribute = The new character attribute.
   Updates     : Nothing.
   Outputs     : Nothing.
   Returns     : Always returns a value of zero.
   Modified    : 02/27/92 DWP Initial coding.
   Notes       :
*/

int BGI_TextAttr(void * Window, CARDINAL_16 Attribute) {

   textattr(Attribute);

   return (0);

}

/* Function    : BGI_GetTextInfo
   Description : Retrieves the current character attribute.
   Inputs      : Window    = The window being accessed or modified.
   Updates     : Nothing.
   Outputs     : Attribute = The current character attribute.
   Returns     : Always returns a value of zero.
   Modified    : 02/27/92 DWP Initial coding.
   Notes       :
*/

int BGI_GetTextInfo(void * Window, CARDINAL_16 * Attribute) {

   struct text_info ti;

   gettextinfo(&ti);
   *(Attribute) = (ti.attribute << 4) | ti.normattr;

   return (0);

}

/* Function    : BGI_WhereX
   Description : Determines the position of the cursor.
   Inputs      : Window = The window being accessed or modified.
   Updates     : Nothing.
   Outputs     : Column = The current cursor column.
   Returns     : Always returns a value of zero.
   Modified    : 02/27/92 DWP Initial coding.
   Notes       :
*/

int BGI_WhereX(void * Window, CARDINAL_16 * Column) {

   *(Column) = wherex();

   return (0);

}

/* Function    : BGI_WhereY
   Description : Determines the position of the cursor.
   Inputs      : Window = The window being accessed or modified.
   Updates     : Nothing.
   Outputs     : Row    = The current cursor row.
   Returns     : Always returns a value of zero.
   Modified    : 02/27/92 DWP Initial coding.
   Notes       :
*/

int BGI_WhereY(void * Window, CARDINAL_16 * Row) {

   *(Row) = wherey();

   return (0);

}

/* Function    : BGI_GotoY
   Description : Positions the cursor on the specified row.
   Inputs      : Window = The window being accessed or modified.
                 Row    = The new row.
   Updates     : Nothing.
   Outputs     : Nothing.
   Returns     : Always returns a value of zero.
   Modified    : 02/27/92 DWP Initial coding.
   Notes       :
*/

int BGI_GotoY(void * Window, CARDINAL_16 Row) {

   gotoxy(wherex(), Row);

   return (0);

}

/* Function    : BGI_GotoX
   Description : Positions the cursor on the specified column.
   Inputs      : Window = The window being accessed or modified.
                 Column = The new column.
   Updates     : Nothing.
   Outputs     : Nothing.
   Returns     : Always returns a value of zero.
   Modified    : 02/27/92 DWP Initial coding.
   Notes       :
*/

int BGI_GotoX(void * Window, CARDINAL_16 Column) {

   gotoxy(Column, wherey());

   return (0);

}

/* Function    : BGI_GotoYX
   Description : Positions the cursor at the specified coordinates.
   Inputs      : Window = The window being accessed or modified.
                 Row    = The new row.
                 Column = The new column.
   Updates     : Nothing.
   Outputs     : Nothing.
   Returns     : Always returns a value of zero.
   Modified    : 02/27/92 DWP Initial coding.
   Notes       :
*/

int BGI_GotoYX(void * Window, CARDINAL_16 Row, CARDINAL_16 Column) {

   gotoxy(Column, Row);

   return (0);

}

/* Function    : BGI_Print_Character
   Description : Prints the specified character on the screen at the current cursor coordinates and using the current character
                 attribute.
   Inputs      : Window    = The window being accessed or modified.
                 Character = The character to print.
   Updates     : Nothing.
   Outputs     : Nothing.
   Returns     : Always returns a value of zero.
   Modified    : 02/28/92 DWP Initial coding.
   Notes       :
*/

int BGI_Print_Character(void * Window, char Character) {

   putch(Character);

   return (0);

}

/* Function    : BGI_Print_String
   Description : Prints the specified character string on the screen at the current cursor coordinates and using the current
                 character attribute.
   Inputs      : Window = The window being accessed or modified.
                 String = The string to print.
   Updates     : Nothing.
   Outputs     : Nothing.
   Returns     : Always returns a value of zero.
   Modified    : 02/28/92 DWP Initial coding.
   Notes       :
*/

int BGI_Print_String(void * Window, char * String) {

   cprintf(String);

   return (0);

}

/* Function    : BGI_ClrScr
   Description : Clears the current window.
   Inputs      : Window = The window being accessed or modified.
   Updates     : Nothing.
   Outputs     : Nothing.
   Returns     : Always returns a value of zero.
   Modified    : 02/28/92 DWP Initial coding.
   Notes       :
*/

int BGI_ClrScr(void * Window) {

   clrscr();

   return (0);

}

/* Function    : BGI_ClrEol
   Description : Clears to the window to the end of the line.
   Inputs      : Window = The window being accessed or modified.
   Updates     : Nothing.
   Outputs     : Nothing.
   Returns     : Always returns a value of zero.
   Modified    : 02/28/92 DWP Initial coding.
   Notes       :
*/

int BGI_ClrEol(void * Window) {

   clreol();

   return (0);

}
