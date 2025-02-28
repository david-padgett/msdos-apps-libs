/* File        : TEXT1.C
   Module      : TEXT
   System      : None
   Description : A method for initializing an instance of a TEXT record.
   Modified    : 03/04/92 DWP Created.
   Notes       :
*/

#include <alloc.h>
#include <stdio.h>

#include "text0.h"

/* Function    : TEXT_Constructor
   Description : A method for initializing the specified TEXT record.
   Inputs      : Set_Cursor_Position = A method for positioning the cursor.
                 Set_Cursor_Row      = A method for altering the y coordinate of the cursor.
                 Set_Cursor_Column   = A method for altering the x coordinate of the cursor.
                 Get_Cursor_Row      = A method for retrieving the y coordinate of the cursor.
                 Get_Cursor_Column   = A method for retrieving the x coordinate of the cursor.
                 Set_Text_Color      = A method for altering the text color.
                 Get_Text_Color      = A method for retrieving the text color.
                 Clear_Text_Window   = A method for clearing the text window.
                 Print_Character     = A method for printing a character.
                 Print_String        = A method for printing an ASCIIZ string.
   Updates     : Nothing.
   Outputs     : Text                = The TEXT record to initialize.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 03/04/92 DWP Initial coding.
   Notes       :
*/

int TEXT_Constructor(int (*Set_Cursor_Position)(void * Window, CARDINAL_16 Row, CARDINAL_16 Column), int (*Set_Cursor_Row)(void * Window, CARDINAL_16 Row), int (*Set_Cursor_Column)(void * Window, CARDINAL_16 Column), int (*Get_Cursor_Row)(void * Window, CARDINAL_16 * Row), int (*Get_Cursor_Column)(void * Window, CARDINAL_16 * Column), int (*Set_Text_Color)(void * Window, CARDINAL_16 Color), int (*Get_Text_Color)(void * Window, CARDINAL_16 * Color), int (*Clear_Text_Window)(void * Window), int (*Print_Character)(void * Window, char Character), int (*Print_String)(void * Window, char * String), TEXT * Text) {

   _TEXT * text_descriptor;
   int     result;

   if ((text_descriptor = malloc(sizeof(_TEXT))) == NULL) {

      result = TEXT_NOMEM;

   }
   else {

      text_descriptor->Window = NULL;
      text_descriptor->Row = 0;
      text_descriptor->Column = 0;
      text_descriptor->Color = 0;
      text_descriptor->Font = NULL;
      text_descriptor->Set_Cursor_Position = Set_Cursor_Position;
      text_descriptor->Set_Cursor_Row = Set_Cursor_Row;
      text_descriptor->Set_Cursor_Column = Set_Cursor_Column;
      text_descriptor->Get_Cursor_Row = Get_Cursor_Row;
      text_descriptor->Get_Cursor_Column = Get_Cursor_Column;
      text_descriptor->Set_Text_Color = Set_Text_Color;
      text_descriptor->Get_Text_Color = Get_Text_Color;
      text_descriptor->Clear_Text_Window = Clear_Text_Window;
      text_descriptor->Print_Character = Print_Character;
      text_descriptor->Print_String = Print_String;

      result = TEXT_NOERR;

   }

   *(Text) = text_descriptor;

   return (result);

}
