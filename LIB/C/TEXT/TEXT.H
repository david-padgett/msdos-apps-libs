/* File        : TEXT.H
   Module      : TEXT
   System      : NONE
   Description : The definition header file for the TEXT module.
   Modified    : 01/10/91 DWP Created.
   Notes       :
*/

#ifndef _TEXT_MODULE
#define _TEXT_MODULE

#include "Standard\standard.h"

/* Type Definitions. */

typedef enum _TEXT_ERROR_CODES {TEXT_NOERR, TEXT_NOMEM, TEXT_PARAM} TEXT_ERROR_CODES;

typedef void * TEXT;

/* Procedures and functions. */

int TEXT_Constructor(int (* Set_Cursor_Position)(void * Window, CARDINAL_16 Row, CARDINAL_16 Column), int (* Set_Cursor_Row)(void * Window, CARDINAL_16 Row), int (* Set_Cursor_Column)(void * Window, CARDINAL_16 Column), int (* Get_Cursor_Row)(void * Window, CARDINAL_16 * Row), int (* Get_Cursor_Column)(void * Window, CARDINAL_16 * Column), int (* Set_Text_Color)(void * Window, CARDINAL_16 Color), int (* Get_Text_Color)(void * Window, CARDINAL_16 * Color), int (* Clear_Text_Window)(void * Window), int (* Print_Character)(void * Window, char Character), int (* Print_String)(void * Window, char * String), TEXT * Text);
int TEXT_Destructor(TEXT * Text);

int TEXT_Set_Text_Window(void * Window, TEXT Text);
int TEXT_Set_Cursor_Position(CARDINAL_16 Row, CARDINAL_16 Column, TEXT Text);
int TEXT_Set_Cursor_Row(CARDINAL_16 Row, TEXT Text);
int TEXT_Set_Cursor_Column(CARDINAL_16 Column, TEXT Text);
int TEXT_Set_Text_Color(CARDINAL_16 Color, TEXT Text);
int TEXT_Set_Text_Font(void * Font, TEXT Text);

int TEXT_Retrieve_Cursor_Row(TEXT Text, CARDINAL_16 * Row);
int TEXT_Retrieve_Cursor_Column(TEXT Text, CARDINAL_16 * Column);
int TEXT_Retrieve_Text_Color(TEXT Text, CARDINAL_16 * Color);

int TEXT_Clear_Text_Window(TEXT Text);
int TEXT_Print_Character(char Character, TEXT Text);
int TEXT_Print_String(char * String, TEXT Text);

#endif
