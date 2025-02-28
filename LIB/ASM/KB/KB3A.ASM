; File        : KB3A.ASM
; Module      : KB
; System      : None
; Description : A method for retrieving keyboard status information.
; Modified    : 04/25/91 DWP Created.
; Notes       :

_KB_MODULE         =      0

                   include kb.inc

                   public KB_Retrieve_Shift_Status_Word

KB_Code            segment byte public 'CODE'
                   assume cs:KB_Code

; Function    : KB_Retrieve_Shift_Status_Word
; Description : Retrieves the status of the keyboard.
; Inputs      : Nothing.
; Updates     : Nothing.
; Outputs     : Nothing.
; Returns     : The shift status word is returned in the AX register.
;                    AL Bit 7 = Insert on.
;                           6 = Caps Lock on.
;                           5 = Num Lock on.
;                           4 = Scroll Lock on.
;                           3 = Either ALT key pressed.
;                           2 = Either CTRL key pressed.
;                           1 = Left Shift pressed.
;                           0 = Right Shift pressed.
;                    AH Bit 7 = Insert key pressed.
;                           6 = Caps Lock key pressed.
;                           5 = Num Lock key pressed.
;                           4 = Scroll Lock key pressed.
;                           3 = Pause state active.
;                           2 = SysRq key pressed.
;                           1 = Left ALT key pressed.
;                           0 = Left CTRL key pressed.
; Modified    : 04/25/91 DWP Initial Coding.
; Notes       :

KB_Retrieve_Shift_Status_Word proc far

                   ; Save the DS and BX registers.

                   push   bx
                   push   ds

                   ; Place absolute memory location 40h:17H into AX.

                   mov    ax, 40h
                   mov    ds, ax
                   mov    bx, 17h
                   mov    ax, [bx]

                   ; Restore DS and BX registers.

                   pop    ds
                   pop    bx

                   retf

KB_Retrieve_Shift_Status_Word endp

KB_Code            ends
                   end
