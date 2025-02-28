/* File        : PORT.H
   Module      : PORT
   System      : None
   Description : The definition header file for the PORT module.
   Modified    : 04/13/92 DWP Created.
   Notes       :
*/

#ifndef _PORT_MODULE

#include "Standard\standard.h"

/* Type Definitions. */

typedef enum _PORT_ERROR_CODES {PORT_NOERR, PORT_PARAM, PORT_NOMEM, PORT_INTRN, PORT_EXTRN} PORT_ERROR_CODES;

typedef void * PORT;

#define PORT_DOUBLE_LINE_BORDER "ÉÍ»ººÈÍ¼"
#define PORT_SINGLE_LINE_BORDER "ÚÄ¿³³ÀÄÙ"
#define PORT_NO_BORDER          ""

/* Procedures and Functions. */

int PORT_Constructor(CARDINAL_16 Starting_Row, CARDINAL_16 Starting_Column, CARDINAL_16 Height, CARDINAL_16 Width, char * Border, CARDINAL_16 Port_Color, CARDINAL_16 Border_Color, PORT * Port);
int PORT_Destructor(PORT * Port);
int PORT_Activate(PORT Port);

#endif
