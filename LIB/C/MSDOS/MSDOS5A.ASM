; File        : DOS5A.ASM
; Module      : DOS
; System      : None
; Description : A method for altering the current DOS command-line switch character.
; Modified    : 03/30/91 DWP Created.
; Notes       :

		   include ..\..\ASM\Standard\standard.inc
		   include msdos.inc

                   public _DOS_Set_SwitchChar

DOS_Data           segment byte public 'DATA'
DOS_Data           ends

DOS_Code           segment byte public 'CODE'
                   assume cs:DOS_Code

; Function    : _DOS_Set_SwitchChar
; Description : Alters the current DOS command-line switch character.
; Inputs      : SwitchChar = The new DOS command-line switch character.
; Updates     : Nothing.
; Outputs     : Nothing.
; Returns     : TRUE if the value was successfully altered, FALSE otherwise.
; Modified    : 03/30/91 DWP Initial coding.
; Notes       :

; Parameter Definitions:
;-----------------------
SwitchChar         equ    <[bp + 6]>

PARAMETER_ADJUSTMENT =    2

_DOS_Set_SwitchChar proc  far

                   push   bp                     ; Set up standard stack
                   mov    bp, sp                 ; frame.
                   push   dx                     ; Save DX register.

                   mov    ax, 3701h              ; Attempt to alter the DOS
                   mov    dx, SwitchChar         ; switch character.
                   int    21h

                   mov    dx, TRUE               ; If AL = 0ffh, then the
                   cmp    al, 0ffh               ; DOS call was unsuccessful.
                   jne    _DOS_Set_SwitchChar_000
                   dec    dx

_DOS_Set_SwitchChar_000:

                   mov    ax, dx                 ; Move the return value into
                                                 ; the AX register.

                   pop    dx                     ; Restore DX register.
                   mov    sp, bp                 ; Restore stack to its
                   pop    bp                     ; previous state.

                   ret    PARAMETER_ADJUSTMENT

_DOS_Set_SwitchChar endp

DOS_Code           ends
                   end
