/* File        : STACK3.C
   Module      : STACK
   System      : None
   Description : A method for removing data from a stack.
   Modified    : 08/01/90 DWP Created from "STACK.C".
   Notes       :
*/

#include <alloc.h>
#include <errno.h>
#include <memory.h>

#include "stack.h"

/* Function    : STACK_Pop
   Description : Removes the top element from the specified stack and places the data in the specified buffer.
   Inputs      : Stack = The stack to remove data from.
   Updates     : Data  = The buffer that the data is placed in.  If Data is equal to NULL then removed data is not saved.
   Outputs     : Nothing.
   Returns     : Nothing.
   Modified    : 11/06/89 DWP Initial Coding.
                 06/25/90 DWP Enhanced.
   Notes       :
*/
void STACK_Pop(STACK * Stack, void * Data) {

   _STACK_Element * temp;

   if (Stack->Elements > 0) {

      temp = Stack->Top;

      if (Data != NULL) {

         memcpy(Data, temp->Data, Stack->Size);

      }

      Stack->Top = temp->Next;
      free(temp->Data);
      free(temp);
      Stack->Elements--;

   }

}
