/* File        : PORT1.C
   Module      : PORT
   System      : None
   Description : The constructor and destructor functions for the PORT module.
   Modified    : 04/13/92 DWP Created.
   Notes       :
*/

#include <alloc.h>
#include <conio.h>
#include <dos.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "port0.h"

/* Procedure   : _PORT_Get_Video_Screen_Address
   Description : Determines where in memory the currently active video memory resides.
   Inputs      : Nothing.
   Updates     : Nothing.
   Outputs     : Video_Screen = The address of the currently active video memory.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 04/13/92 DWP Initial coding.
   Notes       :
*/

int _PORT_Get_Video_Screen_Address(_PORT_CHARACTER_DESCRIPTOR ** Video_Screen) {

   union REGS  input_registers, output_registers;
   int         result = PORT_NOERR;

   /* Get current video mode. */

   input_registers.h.ah = 0x0f;
   int86(0x10, &input_registers, &output_registers);

   switch (output_registers.h.al) {

      case 2 :
      case 3 :

         *(Video_Screen) = MK_FP(0xb800, 0x0000);
         break;

      case 7 :

         *(Video_Screen) = MK_FP(0xb000, 0x0000);
         break;

      default :

         result = PORT_INTRN;

   }

   if (result == PORT_NOERR) {

      *(Video_Screen) += output_registers.h.bh * 2000;

   }

   return (result);

}

/* Function    : PORT_Constructor
   Description : Initializes and opens a port.
   Inputs      : Starting_Row    = The top-most row of the new port.
                 Starting_Column = The left-most column of the new port.
                 Height          = The number of rows in the new port.
                 Width           = The number of columns in the new port.
                 Border          = The border characters of the new port.
                 Port_Color      = The default color attribute of the new port.
                 Border_Color    = The default color attribute of the border, if one is displayed.
   Updates     : Nothing.
   Outputs     : Port            = The port to initialize.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 04/13/92 DWP Initial coding.
   Notes       :
*/

int PORT_Constructor(CARDINAL_16 Starting_Row, CARDINAL_16 Starting_Column, CARDINAL_16 Height, CARDINAL_16 Width, char * Border, CARDINAL_16 Port_Color, CARDINAL_16 Border_Color, PORT * Port) {

   struct text_info             text_info;
   _PORT *                      port_descriptor;
   CARDINAL_16                  port_size, i, j;
   _PORT_CHARACTER_DESCRIPTOR * video_screen;
   int                          result;

   /* Validate the 'Height' and 'Width' parameters.  Continue only if they are valid. */

   if (Height == 0 || Width == 0 || (strncmp(Border, PORT_NO_BORDER, 8) != 0 && (Height < 3 || Width < 3))) {

      result = PORT_PARAM;

   }
   else {

      /* Allocate space for the new port descriptor.  Continue only if enough free memory is available. */

      if ((port_descriptor = malloc(sizeof(_PORT))) == NULL) {

         result = PORT_NOMEM;

      }
      else {

         /* Allocate space for a temporary storage buffer.  Continue only if enough free memory is available. */

         port_size = Height * Width * sizeof(_PORT_CHARACTER_DESCRIPTOR);

         if ((port_descriptor->Save_Area = malloc(port_size)) == NULL) {

            result = (PORT_Destructor((PORT *) &port_descriptor) == PORT_NOERR) ? PORT_NOMEM : PORT_INTRN;

         }
         else {

            /* Initialize the new port descriptor. */

            port_descriptor->Starting_Row = Starting_Row;
            port_descriptor->Starting_Column = Starting_Column;
            port_descriptor->Height = Height;
            port_descriptor->Width = Width;
            strncpy(port_descriptor->Border, Border, 8);
            port_descriptor->Port_Color = Port_Color;
            port_descriptor->Border_Color = Border_Color;

            port_descriptor->Cursor_Row = wherey();
            port_descriptor->Cursor_Column = wherex();

            gettextinfo(&text_info);
            port_descriptor->Text_Color = (text_info.attribute << 4) | text_info.normattr;

            port_descriptor->Raised_Port = FALSE;

            /* Get current video mode. */

            result = _PORT_Get_Video_Screen_Address(&video_screen);

            if (result == PORT_NOERR) {

               /* Save the portion of the screen that will be overwritten by the new port. */

               for (i = 0; i < Height; i++) {

                  memcpy(port_descriptor->Save_Area + (i * Width), video_screen + ((Starting_Row - 1 + i) * 80) + (Starting_Column - 1), Width * sizeof(_PORT_CHARACTER_DESCRIPTOR));

               }

               /* Set the new window coordinates. */

               window(Starting_Column, Starting_Row, Starting_Column + Width - 1, Starting_Row + Height - (Border[0] == '\0' ? 1 : 0));

               if (strncmp(Border, PORT_NO_BORDER, 8) == 0) {

                  /* No border was specified, so clear the screen. */

                  textattr(Port_Color);
                  clrscr();

               }
               else {

                  /* Draw the border. */

                  for (i = 0; i < Height; i++) {

                     if (i > 0 && i < Height - 1) {

                        putch(Border[3]);
                        textattr(Port_Color);
                        cprintf("%*s", Width - 2, "");
                        textattr(Border_Color);
                        putch(Border[4]);

                     }
                     else {

                        textattr(Border_Color);
                        putch(Border[(i == 0) ? 0 : 5]);

                        for (j = 0; j < Width - 2; j++) {

                           putch(Border[(i == 0) ? 1 : 6]);

                        }

                        putch(Border[(i == 0) ? 2 : 7]);

                     }

                  }

                  result = PORT_Activate((PORT) port_descriptor);

               }

            }

         }

         *(Port) = port_descriptor;

      }

   }

   return (result);

}

/* Function    : PORT_Destructor
   Description : Closes a port.
   Inputs      : Nothing.
   Updates     : Port = The port to close.
   Outputs     : Nothing.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 04/13/92 DWP Initial coding.
   Notes       :
*/

int PORT_Destructor(PORT * Port) {

   _PORT *                      port_descriptor;
   CARDINAL_16                  i;
   _PORT_CHARACTER_DESCRIPTOR * video_screen;
   int                          result;

   if (Port == NULL || (port_descriptor = *(Port)) == NULL) {

      result = PORT_PARAM;

   }
   else {

      window(1, 1, 80, 25);
      result = _PORT_Get_Video_Screen_Address(&video_screen);

      if (result == PORT_NOERR) {

         /* Restore the screen to the state it was in before the port was opened. */

         for (i = 0; i < port_descriptor->Height; i++) {

            memcpy(video_screen + ((port_descriptor->Starting_Row - 1 + i) * 80) + ((port_descriptor->Starting_Column - 1)), port_descriptor->Save_Area + (i * port_descriptor->Width), port_descriptor->Width * sizeof(_PORT_CHARACTER_DESCRIPTOR));

         }

         textattr(port_descriptor->Text_Color);
         gotoxy(port_descriptor->Cursor_Column, port_descriptor->Cursor_Row);

         free(port_descriptor->Save_Area);
         free(port_descriptor);
         *(Port) = NULL;

      }

   }

   return (result);

}

/*
void main(void) {

   PORT Port;
   int  result;

   textattr(LIGHTGRAY);
   clrscr();
   system("dir");
   gotoxy(1, 9);
   printf("-------------------------------------------------------------\n");

   result = PORT_Constructor(1, 1, 25, 80, PORT_NO_BORDER, (LIGHTGRAY << 4) | LIGHTCYAN, (LIGHTGRAY << 4) | CYAN, &Port);

   if (result == PORT_NOERR) {

      result = PORT_Destructor(&Port);

   }

}
*/
