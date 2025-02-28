/* File        : KBFLAGS.C
   Module      : None
   System      : None
   Description : Displays the contents of the keyboard shift status and status words.
   Modified    : 04/26/91 DWP Created.
   Notes       :
*/

#include <conio.h>

#include "cursor\cursor.h"
#include "kb\kb.h"

/* Procedure   : KBFLAGS_Display_Description
   Description : Displays the descriptions of the shift status and status words, as well as a description of each of the bits in
                 these two words.
   Inputs      : Nothing.
   Updates     : Nothing.
   Outputs     : Nothing.
   Returns     : Nothing.
   Modified    : 04/26/91 DWP Initial coding.
   Notes       :
*/

void KBFLAGS_Display_Description(void) {

  /* Display descriptions of the shift status and status words. */

   textattr((BLACK << 4) | CYAN);
   gotoxy(1, 3);
   cprintf("%12sShift Status Word%21sKeyboard Status Word%10s", "", "", "");

   /* Display descriptions of each bit of the shift status and status words. */

   gotoxy(1, 7);
   cprintf("  (15) Insert key pressed.%16s(15) Transmit error flag.\n\r", "");
   cprintf("  (14) Caps Lock key pressed.%13s(14) LED update in progress flag.\n\r", "");
   cprintf("  (13) Num Lock key pressed.%14s(13) Resend received flag.\n\r", "");
   cprintf("  (12) Scroll Lock key pressed.%11s(12) ACK received flag.\n\r", "");
   cprintf("  (11) Pause state active.%16s(11) Reserved, must be 0.\n\r", "");
   cprintf("  (10) SysRq key pressed.%17s(10) Caps Lock LED flag.\n\r", "");
   cprintf("  ( 9) Left ALT key pressed.%14s( 9) Num Lock LED flag.\n\r", "");
   cprintf("  ( 8) Left CTRL key pressed.%13s( 8) Scroll Lock LED flag.\n\r", "");
   cprintf("  ( 7) Insert on.%25s( 7) Read-ID in progress.\n\r", "");
   cprintf("  ( 6) Caps Lock on.%22s( 6) Last code was 1st of 2 ID codes.\n\r", "");
   cprintf("  ( 5) Num Lock on.%23s( 5) Force Num Lock if Bit 7 & Bit 4.\n\r", "");
   cprintf("  ( 4) Scroll Lock on.%20s( 4) Enhanced keyboard installed.\n\r", "");
   cprintf("  ( 3) Either ALT key pressed.%12s( 3) Right ALT key pressed.\n\r", "");
   cprintf("  ( 2) Either CTRL key pressed.%11s( 2) Right CTRL key pressed.\n\r", "");
   cprintf("  ( 1) Left Shift pressed.%16s( 1) Last code read was E0h.\n\r", "");
   cprintf("  ( 0) Right Shift pressed.%15s( 0) Last code read was E1h.\n\r", "");
   textattr((BLACK << 4) | LIGHTCYAN);

}

/* Procedure   : KBFLAGS_Draw_Screen
   Description : Draws the screen for the KBFLAGS program.
   Inputs      : Nothing.
   Updates     : Nothing.
   Outputs     : Nothing.
   Returns     : Nothing.
   Modified    : 04/26/91 DWP Initial coding.
   Notes       :
*/

void KBFLAGS_Draw_Screen(void) {

   int i;

   /* Clear the screen, display the available function keys and the program title . */

   clrscr();
   textattr((BLACK << 4) | YELLOW);
   gotoxy(1, 25);
   clreol();
   gotoxy(1, 25);
   cprintf(" F1 - Help%59sESC - Exit ", "");
   gotoxy(1, 1);
   clreol();
   gotoxy(7, 1);
   cprintf("Keyboard Status Flags V1.0, " COMPILE_DATE ", Copyright (c) 1991 by CSFX");

   /* Draw the horizontal lines. */

   for (i = 1; i <= 80; i++) {

      gotoxy(i, 2);
      putch('Ä');
      gotoxy(i, 24);
      putch('Ä');

   }

   KBFLAGS_Display_Description();

 }

/* Procedure   : KBFLAGS_Help
   Description : Displays the help screen for the KBFLAGS program.
   Inputs      : Nothing.
   Updates     : Nothing.
   Outputs     : Nothing.
   Returns     : Nothing.
   Modified    : 04/26/91 DWP Initial coding.
   Notes       :
*/

void KBFLAGS_Help(void) {

   int i;

   window(17, 9, 63, 18);
   textattr((BLACK << 4) | LIGHTRED);
   clrscr();
   gotoxy(1, 1);
   cprintf("É%44s»", "");
   gotoxy(1, 10);
   cprintf("È%44s¼", "");

   for (i = 1; i <= 44; i++) {

      gotoxy(i + 1, 1);
      putch('Í');
      gotoxy(i + 1, 10);
      putch('Í');

      if (i < 9) {

         gotoxy(1, i + 1);
         putch('º');
         gotoxy(46, i + 1);
         putch('º');

      }

   }

   window(19, 10, 61, 17);
   gotoxy(1, 1);
   cprintf("This program repeatedly displays the key-\n\r");
   cprintf("board shift status word and the keyboard\n\r");
   cprintf("status word.  Press any of the ALT, CTRL,\n\r");
   cprintf("SHIFT, INS, or lock keys to see the values\n\r");
   cprintf("change.  Press ESC to exit the program.\n\r\n\r");
   cprintf("%8sPress any key to continue.", "");

   KB_Read();
   window(1, 1, 80, 25);
   KBFLAGS_Display_Description();

}

/* Procedure   : KBFLAGS_Main
   Description : The main procedure for the KBFLAGS program.
   Inputs      : Nothing.
   Updates     : Nothing.
   Outputs     : Nothing.
   Returns     : Nothing.
   Modified    : 04/26/91 DWP Initial coding.
   Notes       :
*/

void KBFLAGS_Main(void) {

   WORD_16     shift_status, status;
   CARDINAL_16 key;
   int         i;

   /* Loop until ESC is pressed. */

   while (TRUE) {

      if (KB_Preview() != 0) {

         key = KB_Read();

         /* If ESC was pressed, then exit. */

         if (key == KB_ESC) {

            gotoxy(1, 25);
            break;

         }

         /* If F1 was pressed, display the help screen. */

         if (key == KB_F1) {

            KBFLAGS_Help();

         }

      }

      /* Make copies of the current shift status and status words. */

      shift_status = KB_Retrieve_Shift_Status_Word();
      status = KB_Retrieve_Status_Word();

      /* Display each bit in the shift status and status words. */

      for (i = 0; i < 16; i++) {

         gotoxy(28 - i, 5);
         putch('0' + ((shift_status >> i) & 1));
         gotoxy(1, 22 - i);
         putch('0' + ((shift_status >> i) & 1));

         gotoxy(68 - i, 5);
         putch('0' + ((status >> i) & 1));
         gotoxy(41, 22 - i);
         putch('0' + ((status >> i) & 1));

      }

   }

}

/* Function    : main
   Description : The main entry point for the KBFLAGS program.
   Inputs      : Nothing.
   Updates     : Nothing.
   Outputs     : Nothing.
   Returns     : Always returns value of zero.
   Modified    : 04/26/91 DWP Initial coding.
   Notes       :
*/

int main(void) {

   CURSOR_Off();
   KBFLAGS_Draw_Screen();
   KBFLAGS_Main();
   textattr(LIGHTGRAY);
   gotoxy(1, 25);
   putch(' ');
   CURSOR_On();

   return (0);

}
