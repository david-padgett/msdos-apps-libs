; File        : KB3.ASM
; Module      : KB
; System      : None
; Description : A method for retrieving the shift flag status word.
; Modified    : 04/25/91 DWP Created.
; Notes       :

_KB_MODULE         =      0

		   include ..\Standard\standard.inc
                   include kb.inc

                   extrn  KB_Enhanced_Keyboard_Present : far
                   extrn  KB_Retrieve_Shift_Status_Word : far
                   extrn  KB_Retrieve_Status_Word : far
                   public KB_Shift_Status

KB_Code            segment byte public 'CODE'
                   assume cs:KB_Code

; Function    : KB_Shift_Status
; Description : Checks the shift status of the keyboard.
; Inputs      : Nothing.
; Updates     : Nothing.
; Outputs     : Nothing.
; Returns     : The keyboard shift status word is returned in the AX register.
;                    AL Bit 7 = Insert on.
;                           6 = Caps Lock on.
;                           5 = Num Lock on.
;                           4 = Scroll Lock on.
;                           3 = Either ALT key pressed.
;                           2 = Either CTRL key pressed.
;                           1 = Left Shift pressed.
;                           0 = Right Shift pressed.
;                    AH Bit 7 = SysRQ key pressed.
;                           6 = Caps Lock key pressed.
;                           5 = Num Lock key pressed.
;                           4 = Scroll Lock key pressed.
;                           3 = Right ALT key pressed.
;                           2 = Right CTRL key pressed.
;                           1 = Left ALT key pressed.
;                           0 = Left CTRL key pressed.
; Modified    : 04/25/91 DWP Initial Coding.
; Notes       :

KB_Shift_Status    proc   far

                   call   KB_Enhanced_Keyboard_Present
                   cmp    ax, TRUE
                   jne    KB_Shift_Status_000

                   ; An enhanced keyboard is present, so retrieve the enhanced shift flags.

                   mov    ah, 12h
                   int    16h
                   jmp    short KB_Shift_Status_003

KB_Shift_Status_000:

                    ; An enhanced keyboard is not present, so retrieve the shift status word and the keyboard status word.

                    call  KB_Retrieve_Shift_Status_Word

                    ; Initialize the SysRq key pressed flag.

                    test  ax, 400h
                    jz    KB_Shift_Status_001
                    or    ax, 8000h
                    jmp   short KB_Shift_Status_002

KB_Shift_Status_001:

                    and   ax, 7fffh

KB_Shift_Status_002:

                    ; Save the BX register, save AX, and then retrieve the keyboard status word.

                    push  bx
                    mov   bx, ax
                    call  KB_Retrieve_Status_Word

                    ; Initialize the Right ALT key pressed and Right CTRL key pressed flags, and then restore the BX register.

                    and   ax, 0ch
                    or    ax, bx
                    pop   bx

KB_Shift_Status_003:

                   retf

KB_Shift_Status    endp

KB_Code            ends
                   end