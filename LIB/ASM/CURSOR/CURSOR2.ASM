; File        : CURSOR2.ASM
; Module      : CURSOR
; System      : None
; Description : A method for altering the cursor characteristic.
; Modified    : 04/30/91 DWP Created.
; Notes       :

_CURSOR_MODULE     equ    0

                   include cursor.inc

                   public CURSOR_Set_Characteristic

CURSOR_Data        segment byte public 'DATA'
CURSOR_Data        ends

CURSOR_Code        segment byte public 'CODE'
                   assume cs:CURSOR_Code

; Procedure   : CURSOR_Set_Characteristic
; Description : Alters the current character characteristic or attribute.
; Inputs      : Characteristic = The new characteristic of the cursor.
; Updates     : Nothing.
; Outputs     : Nothing.
; Returns     : Nothing.
; Modified    : 04/30/91 DWP Initial coding.
; Notes       :

; Parameters

Characteristic     equ    <[bp + 6]>
PARAMETER_ADJUSTMENT =     2

CURSOR_Set_Characteristic proc far

                   ; Set up the standard stack frame and save the AX, BX, and CX registers since calls to INT 10 will alter their
                   ; values.

                   push   bp
                   mov    bp, sp
                   push   ax
                   push   bx
                   push   cx

                   ; Place the current video mode into the AL register and the current page in the BH register.  This is done
		   ; because both the AMI 386 BIOS and AST Premier 386 BIOS supposedly contain a bug which causes a system crash
                   ; if the AL register isn't initialized in this way.

                   mov    ah, 0fh
                   int    10h

                   ; Place the new cursor characteristic into the CX register.

                   mov    cx, Characteristic

                   ; Alter the shape of the cursor of the cursor by setting its characteristic to the value in the CX register.

                   mov    ah, 01h
                   int    10h

                   ; Restore the AX, BX, and CX registers to their original values, and then restore the stack to its
                   ; previous state, and then remove all parameters from the stack.

                   pop    cx
                   pop    bx
                   pop    ax
                   mov    sp, bp
                   pop    bp
                   ret    PARAMETER_ADJUSTMENT

CURSOR_Set_Characteristic endp

CURSOR_Code        ends
                   end