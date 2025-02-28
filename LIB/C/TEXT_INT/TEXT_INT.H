/* File        : TEXT_INT.H
   Module      : TEXT
   System      : None
   Description : The implementation header file for the TEXT_INT module.
   Modified    : 03/20/92 DWP Created.
   Notes       :
*/

#ifndef _TEXT_INT_MODULE
#define _TEXT_INT_MODULE

#include "Standard\standard.h"

/* Procedures and Functions. */

int BGI_TextAttr(void * Window, CARDINAL_16 Attribute);
int BGI_GetTextInfo(void * Window, CARDINAL_16 * Attribute);
int BGI_WhereX(void * Window, CARDINAL_16 * Column);
int BGI_WhereY(void * Window, CARDINAL_16 * Row);
int BGI_GotoY(void * Window, CARDINAL_16 Row);
int BGI_GotoX(void * Window, CARDINAL_16 Column);
int BGI_GotoYX(void * Window, CARDINAL_16 Row, CARDINAL_16 Column);
int BGI_Print_Character(void * Window, char Character);
int BGI_Print_String(void * Window, char * String);
int BGI_ClrScr(void * Window);
int BGI_ClrEol(void * Window);

#endif
