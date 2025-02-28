/* File        : CURSOR.H
   Module      : CURSOR
   System      : None
   Description : The definition header file for the CURSOR module.
   Modified    : 04/30/91 DWP Created.
   Notes       :
*/

#ifndef _CURSOR_MODULE
#define _CURSOR_MODULE

#include "Standard\standard.h"

void    pascal CURSOR_Off(void);
void    pascal CURSOR_On(void);
void    pascal CURSOR_Set_Characteristic(WORD_16 Characteristic);
WORD_16 pascal CURSOR_Get_Characteristic(void);

#endif
