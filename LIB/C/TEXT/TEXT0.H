/* File        : TEXT0.H
   Module      : TEXT
   System      : None
   Description : The implementation header file for the TEXT module.
   Modified    : 01/11/91 DWP Created.
   Notes       :
*/

#include "text.h"

/* Type definitions. */

typedef struct __TEXT {

   void *      Window;
   CARDINAL_16 Row;
   CARDINAL_16 Column;
   CARDINAL_16 Color;
   void *      Font;

   int         (*Set_Cursor_Position)(void * Window, CARDINAL_16 Row, CARDINAL_16 Column);
   int         (*Set_Cursor_Row)(void * Window, CARDINAL_16 Row);
   int         (*Set_Cursor_Column)(void * Window, CARDINAL_16 Column);
   int         (*Get_Cursor_Row)(void * Window, CARDINAL_16 * Row);
   int         (*Get_Cursor_Column)(void * Window, CARDINAL_16 * Column);
   int         (*Set_Text_Color)(void * Window, CARDINAL_16 Color);
   int         (*Get_Text_Color)(void * Window, CARDINAL_16 * Color);
   int         (*Clear_Text_Window)(void * Window);
   int         (*Print_Character)(void * Window, char Character);
   int         (*Print_String)(void * Window, char * String);

} _TEXT;

