/* File        : STACK2.C
   Module      : STACK
   System      : None
   Description : A method for adding data to a stack.
   Modified    : 08/01/90 DWP Created from "STACK.C".
   Notes       :
*/

#include <alloc.h>
#include <errno.h>
#include <memory.h>

#include "stack.h"

/* Function    : STACK_Push
   Description : Places a new element on the specified stack.
   Inputs      : Data  = The data to place on the stack.
   Updates     : Stack = The stack to place data on.
   Outputs     : Nothing.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 11/06/89 DWP Initial Coding.
                 06/25/90 DWP Enhanced.
   Notes       :
*/

int STACK_Push(STACK * Stack, const void *Data) {

   _STACK_Element * new;
   int              result = EZERO;

   if (((new = malloc(sizeof(_STACK_Element))) != NULL) && ((new->Data = malloc(Stack->Size)) != NULL)) {

      memcpy(new->Data, Data, Stack->Size);
      new->Next = Stack->Top;
      Stack->Top = new;
      Stack->Elements++;

   }
   else {

      result = ENOMEM;

      if (new != NULL) {

         free(new);

      }

   }

   return (result);

}
