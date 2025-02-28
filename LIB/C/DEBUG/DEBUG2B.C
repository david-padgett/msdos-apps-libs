/* File        : DEBUG2B.C
   Module      : DEBUG
   System      : None
   Description : A method for DEBUG specific code to compare two elements in the open stream list.
   Modified    : 08/10/90 DWP Created.
   Notes       :
*/

#include "debug0.h"

/* Function    : _DEBUG_Open_Stream_Key_Compare
   Description : Compares two open stream list keys to determine whether or not they are identical.
   Inputs      : key1 = The first key.
                 key2 = The second key.
   Updates     : Nothing.
   Outputs     : Nothing.
   Returns     : The result of the comparison, [0 | 1], 0 - key1 = key2, 1 - key 1 <> key2.
   Modified    : 08/10/90 DWP Initial coding.
   Notes       :
*/
int _DEBUG_Open_Stream_Key_Compare(void * Key1, void * Key2, CARDINAL_32 Position) {

   (void) Position;
   return ((((_DEBUG_Open_Stream_Record *) Key1)->File_Pointer == Key2) ? 0 : 1);

}
