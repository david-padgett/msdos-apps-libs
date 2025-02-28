/* File        : HELLOPMW.C
   Module      : None
   System      : None
   Description : A demonstration program for Window 3.0 protected mode
                 programming.
   Modified    : 02/18/91 DWP Created from PC MAGAZINE, February 12, 1991,
                              page 370.
*/

/* HELLOPMW.C  ---  "Hello Protected Mode World!"
                    Illustrates use of the DPMI interface to switch into
                    protected mode, and use of Windows 3's built-in DOS
                    Extender to print a message in protected mode.

                    Compile in SMALL MODEL with:  CL HELLOWPMW.C

                    Execute under Windows 3.0 only!
*/

#include <conio.h>
#include <stdio.h>
#include <stdlib.h>

unsigned modeswitch(void);

main() {
   unsigned saveCS, saveDS;

   asm mov saveCS, cs
   asm mov saveDS, ds

   printf("\nHello, real mode world! \tCS=%04xh DS=%04xh", saveCS, saveDS);

   if (modeswitch()) {
      puts("\nDPMI not available or memory allocation failed.");
      exit(1);
   }

   asm mov saveCS, cs
   asm mov saveDS, ds

   printf("\nHello, protected mode world! \tCs=%04xh DS=%04xh\n", saveCS, saveDS);
   getch();

   asm mov ah, 4ch
   asm int 21h

   return (0);
}

/* Call DPMI to switch from real mode to protected mode.
   Returns false of mode switch successful, true if no DPMI
   present or if memory allocation for DPMI data area failed. */

unsigned modeswitch(void) {
   void far *switchpoint;

   asm mov  ax, 1687h
   asm int  2fh
   asm or   ax,ax
   asm jnz  exitlabel
   asm mov  word ptr switchpoint, di
   asm mov  word ptr switchpoint+2, es
   asm mov  bx, si
   asm mov  ah, 48h
   asm int  21h
   asm jc   exitlabel
   asm mov  es, ax
   asm mov  ax, 0
   asm call switchpoint
   asm mov  ax, 0

   exitlabel:;
}
