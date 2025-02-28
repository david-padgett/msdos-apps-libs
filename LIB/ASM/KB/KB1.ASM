; File        : KB1.ASM
; Module      : KB
; System      : None
; Description : A method for retrieving a character from the keyboard.
; Modified    : 08/01/90 DWP Created.
; Notes       :

_KB_MODULE         equ    0

		   include ..\Standard\standard.inc
		   include kb.inc

                   extrn  KB_Enhanced_Keyboard_Present : far
                   public KB_Read

KB_Code            segment byte public 'CODE'
                   assume cs:KB_Code

; Function    : KB_Read
; Description : Retrieves (waits for) a character from the keyboard.
; Inputs      : Nothing.
; Updates     : Nothing.
; Outputs     : Nothing.
; Returns     : The last key that was pressed is returned in the AX register.  AH contains the scan code, and AL contains ascii
;               code.
; Modified    : 03/01/90 DWP Initial Coding.
; Notes       :

KB_Read            proc   far

                   ; Determine if an enhanced keyboard is present.

                   call   KB_Enhanced_Keyboard_Present
                   cmp    ax, TRUE
                   jne    KB_Read_000

                   ; An enhanced keyboard is present, so use the BIOS get enhanced keystroke interrupt.

                   mov    ah, 10h
                   int    16h
                   jmp    short KB_Read_001

                   ; An enhanced keyboard is not present, so use the BIOS get keystroke interrupt.

KB_Read_000:       sub    ah, ah
                   int    16h
KB_Read_001:
                   retf

KB_Read            endp

KB_Code            ends
                   end
