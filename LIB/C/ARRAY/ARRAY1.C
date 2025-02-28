/* File        : ARRAY1.C
   Module      : ARRAY
   System      : None
   Description : A method for manipulating arrays.
   Modified    : 11/07/91 DWP Created.
   Notes       :
*/

#include "array.h"

/* Procedure   : ARRAY_Insert
   Description : Inserts elements into an array.  Since arrays have a fixed length, array elements at the end of the array are
                 displaced.
   Inputs      : Element_Size       = The size of an element in array.
                 Array_Length       = The total number of elements in array.
                 Insertion_Position = The starting position of the array element(s) to be inserted.
                 Count              = The number of elements to insert.
   Updates     : Array              = The array to modify.
   Outputs     : Nothing.
   Returns     : Nothing.
   Modified    : 07/25/90 DWP Initial coding.
   Notes       : 1) The specified array must be no larger than 64k.
                 2) A positive direction shifts the array forwards (right); a negative direction shifts the array backwards (left).
*/

void ARRAY_Insert(CARDINAL_16 Element_Size, CARDINAL_16 Array_Length, CARDINAL_16 Insertion_Position, CARDINAL_16 Count, void * Array) {

   /* If count equals 0, then take no action. */

   if (Count != 0) {

      memmove(((char *) Array) + Insertion_Position + Count, ((char *) Array) + Insertion_Position, (Array_Length - Insertion_Position - Count) * Element_Size);
      setmem(((char *) Array) + Insertion_Position, Element_Size * Count, 0);

   }

}
