/* File        : ARRAY1A.C
   Module      : ARRAY
   System      : None
   Description : A method for manipulating arrays.
   Modified    : 11/07/91 DWP Created.
   Notes       :
*/

#include "array.h"

/* Procedure   : ARRAY_Delete
   Description : Deletes array elements from an array.
   Inputs      : Element_Size      = The size of an element in array.
                 Array_Length      = The total number of elements in array.
                 Deletion_Position = The starting position of the array element(s) to be deleted.
                 Count             = The number of elements to insert.
   Updates     : Array             = The array to modify.
   Outputs     : Nothing.
   Returns     : Nothing.
   Modified    : 07/25/90 DWP Initial coding.
   Notes       : 1) The specified array must be no larger than 64k.
                 2) A positive direction shifts the array forwards (right); a negative direction shifts the array backwards (left).
*/

void ARRAY_Delete(CARDINAL_16 Element_Size, CARDINAL_16 Array_Length, CARDINAL_16 Deletion_Position, CARDINAL_16 Count, void * Array) {

   /* If count equals 0, then take no action. */

   if (Count != 0) {

      memmove(((char *) Array) + Deletion_Position, ((char *) Array) + Deletion_Position + Count, (Array_Length - Deletion_Position - Count) * Element_Size);
      setmem(((char *) Array) + Array_Length - Count, Element_Size * Count, 0);

   }

}
