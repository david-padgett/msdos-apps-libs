/* File        : STACK.H
   Module      : STACK
   System      : None
   Description : The header file for the STACK module.
   Modified    : 11/06/89 DWP Created.
   Notes       :
*/

#ifndef _STACK_MODULE
#define _STACK_MODULE

#include "Standard\standard.h"

/* This is the definition of the actual stack, contains a data element pointer and a next element pointer. */

typedef struct __STACK_Element {

   BYTE *                   Data;
   struct __STACK_Element * Next;

} _STACK_Element;

/* This is the definition of the stack header record, it contains the size of each element, and a pointer to the top element. */

typedef struct _STACK {

   CARDINAL_16      Elements;
   CARDINAL_16      Size;
   _STACK_Element * Top;

} STACK;

/* Procedures and functions. */

void STACK_Constructor(STACK * Stack, CARDINAL_16 Size);
void STACK_Destructor(STACK * Stack);
int  STACK_Push(STACK * Stack, const void * Data);
void STACK_Pop(STACK * Stack, void * Data);

#endif
