/* File        : ARRAY.H
   Module      : ARRAY
   System      : None
   Description : The header file for the ARRAY module.
   Modified    : 08/01/90 DWP Created.
   Notes       :
*/

#ifndef _ARRAY_MODULE
#define _ARRAY_MODULE

#include <memory.h>

#include "Standard\standard.h"

/* Type Definitions. */

/* Procedure and Function Prototypes. */

void ARRAY_Insert(CARDINAL_16 Element_Size, CARDINAL_16 Array_Length, CARDINAL_16 Insertion_Position, CARDINAL_16 Count, void * Array);
void ARRAY_Delete(CARDINAL_16 Element_Size, CARDINAL_16 Array_Length, CARDINAL_16 Deletion_Position, CARDINAL_16 Count, void * Array);

#endif
