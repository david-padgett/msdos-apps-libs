; File        : CURSOR1A.ASM
; Module      : CURSOR
; System      : None
; Description : A method for turning the cursor on.
; Modified    : 04/30/91 DWP Created.
; Notes       :

_CURSOR_MODULE     equ    0

                   include cursor.inc

                   public CURSOR_On

CURSOR_Data        segment byte public 'DATA'
CURSOR_Data        ends

CURSOR_Code        segment byte public 'CODE'
                   assume cs:CURSOR_Code

; Procedure   : CURSOR_On
; Description : Turns the cursor on.
; Inputs      : Nothing.
; Updates     : Nothing.
; Outputs     : Nothing.
; Returns     : Nothing.
; Modified    : 04/30/91 DWP Initial coding.
; Notes       :

CURSOR_On          proc   far

                   ; Save the AX, BX, CX, and DX registers since calls to INT 10 will alter their values.

                   push   ax
                   push   bx
                   push   cx
                   push   dx

                   ; Place the current video mode into the AL register and the current page in the BH register.  This is done
		   ; because both the AMI 386 BIOS and AST Premier 386 BIOS supposedly contain a bug which causes a system crash
                   ; if the AL register isn't initialized in this way.

                   mov    ah, 0fh
                   int    10h

                   ; Retrieve the current cursor characteristic.  The cursor characteristic will be in the CX register.

                   mov    ah, 03h
                   int    10h

                   ; Set bits 5 and 6 of the CH register to 00.

                   and    ch, 9fh

                   ; Turn on the cursor by setting its characteristic to the value in the CX register.

                   mov    ah, 01h
                   int    10h

                   pop    dx
                   pop    cx
                   pop    bx
                   pop    ax
                   ret

CURSOR_On          endp

CURSOR_Code        ends
                   end