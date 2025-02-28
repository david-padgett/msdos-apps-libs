/* File        : STACK1.C
   Module      : STACK
   System      : None
   Description : The methods for the creation and destruction of a stack.
   Modified    : 08/01/90 DWP Created from "STACK.C".
   Notes       :
*/

#include <stdio.h>

#include "stack.h"

/* Procedure   : STACK_Constructor
   Description : Initializes the specified stack.
   Inputs      : Size  = The size of a single stack element.
   Updates     : Nothing.
   Outputs     : Stack = The stack to initialize.
   Returns     : Nothing.
   Modified    : 11/06/89 DWP Initial Coding.
   Notes       : 1) This should be the first operation performed on the stack.  Unpredictable results may occur otherwise.
*/

void STACK_Constructor(STACK * Stack, CARDINAL_16 Size) {

   Stack->Elements = 0;
   Stack->Size = Size;
   Stack->Top = NULL;

}

/* Procedure   : STACK_Destructor
   Description : Removes all elements from the specified stack.  All of the data in the stack is permanently lost.
   Inputs      : Nothing.
   Updates     : Stack = The stack to destroy.
   Outputs     : Nothing.
   Returns     : Nothing.
   Modified    : 11/06/89 DWP Initial Coding.
                 06/25/90 DWP Enhanced.
   Notes       :
*/
void STACK_Destructor(STACK * Stack) {

   while (Stack->Elements != 0) {

      STACK_Pop(Stack, NULL);

   }

   STACK_Constructor(Stack, Stack->Size);

}
