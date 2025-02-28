; File        : CURSOR2A.ASM
; Module      : CURSOR
; System      : None
; Description : A method for retrieving the current cursor characteristic.
; Modified    : 04/30/91 DWP Created.
; Notes       :

_CURSOR_MODULE     equ    0

                   include cursor.inc

                   public CURSOR_Get_Characteristic

CURSOR_Data        segment byte public 'DATA'
CURSOR_Data        ends

CURSOR_Code        segment byte public 'CODE'
                   assume cs:CURSOR_Code

; Function    : CURSOR_Get_Characteristic
; Description : Retrieves the current cursor characteristic.
; Inputs      : Nothing.
; Updates     : Nothing.
; Outputs     : Nothing.
; Returns     : The current cursor characteristic is returned in the AX register.
; Modified    : 04/30/91 DWP Initial coding.
; Notes       :

CURSOR_Get_Characteristic proc far

                   ; Save the CX and DX registers since INT 10/03 alters their values.

                   push   cx
                   push   dx

                   ; Retrieve the current cursor attribute.  Cursor attribute will be in the CX register.

                   mov    ah, 03h
                   int    10h
                   mov    ax, cx

                   ; Restore the CX and DX registers to their previous values.

                   pop    dx
                   pop    cx
                   ret

CURSOR_Get_Characteristic endp

CURSOR_Code        ends
                   end