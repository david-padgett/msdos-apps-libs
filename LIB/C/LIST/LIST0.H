/* File        : LIST0.H
   Module      : LIST
   System      : None
   Description : The implementation header file for the LIST module.
   Modified    : 03/05/92 DWP Created.
   Notes       :
*/

#include "list.h"

/* Type Definitions. */

typedef struct __LIST_NODE {

   void *               Data;
   struct __LIST_NODE * Previous_Element;
   struct __LIST_NODE * Next_Element;

} _LIST_NODE;

typedef struct __LIST {

   CARDINAL_16  Element_Size;

   _LIST_NODE * First_Element;
   _LIST_NODE * Last_Element;
   _LIST_NODE * Current_Element;

   CARDINAL_32  Current_Element_Number;
   CARDINAL_32  Total_Elements;

} _LIST;

/* Procedures and Functions. */
