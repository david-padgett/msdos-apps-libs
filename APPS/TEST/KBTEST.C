/* File        : KBTEST.C
   Module      : None
   System      : None
   Description : Displays the contents of bytes 40:96 and 40:97.
   Modified    : 04/24/91 DWP Created.
*/

#include <conio.h>
#include <dos.h>
#include <stdio.h>

#include "kb\kb.h"

/* Function    : main
   Description : The main entry point for the KBTEST program.
   Expects     : Nothing.
   Returns     : Always returns value of zero.
   Modified    : 04/24/91 DWP Initial coding.
   Notes       :
*/
int main(void) {
   BYTE *status_byte_2, *status_byte_3;
   int  i;

   status_byte_2 = MK_FP(0x0040, 0x0097);
   status_byte_3 = MK_FP(0x0040, 0x0096);

   clrscr();
   gotoxy(1, 5);
   printf("Status Byte 2 = 00000000");
   gotoxy(1, 7);
   printf("Status Byte 3 = 00000000");
   gotoxy(1, 9);
   printf("Keyboard is %s enhanced.", (KB_Enhanced_Keyboard_Present()) ? "" : "not");

   while (TRUE) {

      if (KB_Preview() && KB_Read() == KB_ESC) {
         break;
      }

      for (i = 0; i < 8; i++) {

         gotoxy(24 - i, 5);
         putchar('0' + ((*status_byte_2 >> i) & 1));
         gotoxy(24 - i, 7);
         putchar('0' + ((*status_byte_3 >> i) & 1));
      }
   }

   return (0);
}
