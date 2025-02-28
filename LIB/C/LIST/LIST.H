/* File        : LIST.H
   Module      : LIST
   System      : None
   Description : The definition header file for the LIST module.
   Modified    : 03/05/92 DWP Created.
   Notes       :
*/

#ifndef _LIST_MODULE
#define _LIST_MODULE

#include "Standard\standard.h"

/* Type Definitions. */

typedef enum   _LIST_ERROR_CODES {LIST_NOERR, LIST_NOMEM, LIST_PARAM, LIST_EOLST} LIST_ERROR_CODES;
typedef enum   _LIST_POSITIONS {LIST_CURRENT = 0L, LIST_FIRST = 1L, LIST_NEXT = -2L, LIST_LAST = -1L} LIST_POSITIONS;

typedef void * LIST;

/* Procedures and Functions. */

int LIST_Constructor(CARDINAL_16 Element_Size, LIST * List);
int LIST_Destructor(LIST * List);
int LIST_Find(LIST List, int (* Comparison_Function)(void *List_Element, void *Data, CARDINAL_32 Position), void *Data, void **List_Element, CARDINAL_32 *Position);
int LIST_Insert(void * Element, CARDINAL_32 Position, LIST List);
int LIST_Iterate(LIST List, int (* Iterator_Function)(void *List_Element, void *Data, CARDINAL_32 Position), void *Data);
int LIST_Retrieve(LIST List, CARDINAL_32 Position, void ** Element);
int LIST_Delete(CARDINAL_32 Position, LIST List, void * Element);
int LIST_Size(LIST List, CARDINAL_32 * Size);
int LIST_Current(LIST List, CARDINAL_32 * Position);

#endif
