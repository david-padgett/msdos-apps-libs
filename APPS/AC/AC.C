/* File        : AC.C
   Module      : AC
   System      : AC
   Description : This program displays the IBM-PC ASCII chart.
   Modified    : 12/10/90 DWP Created.
   Notes       :
*/

#include <conio.h>
#include <dos.h>
#include <memory.h>
#include <stdio.h>

#include "cursor\cursor.h"
#include "kb\kb.h"

/* Procedure   : AC_Draw_Screen
   Description : Draws the screen for the AC program.
   Inputs      : Nothing.
   Updates     : Nothing.
   Outputs     : Nothing.
   Returns     : Nothing.
   Modified    : 06/28/91 DWP Initial coding.
   Notes       :
*/

void AC_Draw_Screen(void) {

   char str[256];
   int  i;

   /* Clear the screen and display the program title. */

   textattr(LIGHTGRAY);
   clrscr();
   textattr(GREEN);
   cprintf(" DECIMAL/HEXIDECIMAL/ASCII Chart, V1.0, " COMPILE_DATE ", Copyright (c) 1991 by CSFX\n\r", "");

   /* Draw the first line of the grid. */

   textattr(LIGHTRED);
   putch('Õ');

   for (i = 1; i < 79; i++) {

      putch((i % 20 != 0) ? 'Í' : 'Ñ');

   }

   putch('¸');

   /* Display the labels at the top of the grid. */

   for (i = 0; i < 4; i++) {

      cprintf("³%4sDEC HEX ASC", "");
      cprintf("%*s", (i != 3) ? 4 : 3, "");

   }

   putch('³');
   putch('Æ');

   /* Draw line 3 of the grid. */

   for (i = 1; i < 79; i++) {

      putch((i % 20 != 0) ? 'Í' : 'Ø');

   }

   putch('µ');

   /* Draw lines 4 through 23 of the grid. */

   setmem(str, 19, 'Ä');
   str[19] = '\0';

   for (i = 0; i < 19; i++) {

      gotoxy(1, i + 5);

      if (i % 2 == 0) {

         cprintf("³%19s³%19s³%19s³%18s³\n\r", "", "", "", "");

      }
      else {

         cprintf("Ã%19sÅ%19sÅ%19sÅ%18s´", str, str, str,&(str[1]));

      }

   }

   /* Draw the last line of the grid. */

   gotoxy(1, 24);
   putch('Ô');

   for (i = 1; i < 79; i++) {

      putch((i % 20 != 0) ? 'Í' : 'Ï');

   }

   putch('¾');

   /* Display the active function keys. */

   gotoxy(1, 25);
   textattr(GREEN);
   cprintf(" Home/End - Top/Bottom  PgUp/PgDn - Prev/Next  / - Up/Down  ESC - Exit to DOS");

}

/* Procedure   : AC_Process_Keystrokes
   Description : Processes keystrokes and updates the screen as required.
   Inputs      : Nothing.
   Updates     : Nothing.
   Outputs     : Nothing.
   Returns     : Nothing.
   Modified    : 06/28/91 DWP Initial coding.
   Notes       :
*/

void AC_Process_Keystrokes(void) {

   union REGS input_registers, output_registers;
   BOOLEAN    exit_flag, invalid_key_flag;
   int        i, j, display_page, current_character;

   /* Retrieve the current display page. */

   input_registers.h.ah = 0x0f;
   int86(0x10, &input_registers, &output_registers);
   display_page = (int) output_registers.h.bh;

   /* Loop until ESC is pressed. */

   for (i = 0, exit_flag = FALSE; !exit_flag;) {

      /* Loop until 40 characters have been displayed. */

      for (j = 0; j < 40; j++) {

         /* Determine what character should be displayed next. */

         current_character = i + j;

         if (current_character > 255) {

            current_character -= 256;

         }

         gotoxy(5 + ((j  % 4) * 20), 5 + (j / 4 * 2));

         /* Print the decimal representation of the current character. */

         textattr(LIGHTCYAN);
         cprintf("%03d ", current_character);

	 /* Print the hexidecimal representation of the current character. */

         textattr(LIGHTGREEN);
         cprintf(" %02X   ", current_character);

         /* Print the ASCII representation of the current character using INT 10H/09H. */

         input_registers.h.ah = 0x09;
         input_registers.h.al = current_character;
         input_registers.h.bh = display_page;
         input_registers.h.bl = YELLOW;
         input_registers.x.cx = 1;
         int86(0x10, &input_registers, &output_registers);

      }

      /* Loop until a valid key is pressed. */

      for (invalid_key_flag = TRUE; invalid_key_flag;) {

         invalid_key_flag = FALSE;

         switch (KB_Read()) {

            case KB_ESC :

               exit_flag = TRUE;
               break;

            case KB_GRAY_PGDN :
            case KB_PGDN :

               if ((i += 40) > 255) {

                  i -= 256;

               }

               break;

            case KB_GRAY_PGUP :
            case KB_PGUP :

               if ((i -= 40) < 0) {

                  i += 256;

               }

               break;

            case KB_UP :
            case KB_GRAY_UP :

               i = (i > 0) ? i - 4 : 252;
               break;

            case KB_DOWN :
            case KB_GRAY_DOWN :

              i = ( i < 252) ? i + 4 : 0;
              break;

            case KB_HOME :
            case KB_GRAY_HOME :

               i = 0;
               break;

            case KB_END :
            case KB_GRAY_END :

               i = 216;
               break;

            default :

               invalid_key_flag = TRUE;

         }

      }

   }

}

/* Function    : main
   Description : The entry point to the AC program.
   Inputs      : Nothing.
   Updates     : Nothing.
   Outputs     : Nothing.
   Returns     : Always returns 0.
   Modified    : 12/10/90 DWP Initial coding.
                 05/01/91 DWP Added code to disable cursor.
   Notes       :
*/

int main(void) {

   CURSOR_Off();
   AC_Draw_Screen();
   AC_Process_Keystrokes();
   textattr(LIGHTGRAY);
   gotoxy(1, 25);
   putch(' ');
   CURSOR_On();

   return (0);

}