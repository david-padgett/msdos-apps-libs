/* File        : DEBUG2A.C
   Module      : DEBUG
   System      : None
   Description : A method for DEBUG specific code to compare two elements in the heap allocation list.
   Modified    : 08/10/90 DWP Created.
   Notes       :
*/

#include "debug0.h"

/* Function    : _DEBUG_Heap_Allocation_Key_Compare
   Description : Compares two heap allocation list keys to determine whether or not they are identical.
   Inputs      : Key1 = The first key.
                 Key2 = The second key.
   Updates     : Nothing.
   Outputs     : Nothing.
   Returns     : The result of the comparison, [ 0 | 1], 0 - Key1 = Key2, 1 - Key1 <> Key2.
   Modified    : 08/10/90 DWP Initial coding.
   Notes       :
*/
int _DEBUG_Heap_Allocation_Key_Compare(void * Key1, void * Key2, CARDINAL_32 Position) {

   (void) Position;
   return ((((_DEBUG_Heap_Allocation_Record *) Key1)->Memory_Address == Key2) ? 0 : 1);

}
