; File        : KB2.ASM
; Module      : KB
; System      : None
; Description : A method for previewing the keyboard.
; Modified    : 08/01/90 DWP Created.
; Notes       :

_KB_MODULE         =      0

		   include ..\Standard\standard.inc
		   include kb.inc

                   extrn  KB_Enhanced_Keyboard_Present : far
                   public KB_Preview

KB_Code            segment byte public 'CODE'
                   assume cs:KB_Code

; Function    : KB_Preview
; Description : Checks to see if a key has been pressed.
; Inputs      : Nothing.
; Updates     : Nothing.
; Outputs     : Nothing.
; Returns     : AX = 0 if no key has been pressed, otherwise, AX contains the scan code and ASCII character of the key which is
;                    waiting in the keyboard buffer (AL - ASCII character, AH - scan code).
; Modified    : 03/09/90 DWP Initial Coding.
; Notes       :

KB_Preview         proc   far

                   ; Determine if an enhanced keyboard is present.

                   call   KB_Enhanced_Keyboard_Present
                   cmp    ax, TRUE
                   jne    KB_Preview_000

                   ; An enhanced keyboard is present, so use the BIOS preview enhanced keystroke sub-function.  If no keystroke is
                   ; available, ZF will be set, otherwise, ZF will be clear and the AX register will contain the scan code and
                   ; ASCII character of the next key in the keyboard buffer.

                   mov    ah, 11h
                   int    16h
                   jnz    KB_Preview_002
                   jmp    short KB_Preview_001
KB_Preview_000:
                   ; An enhanced keyboard is not present, so use the BIOS preview keystroke sub-function.  If no keystroke is
                   ; available, ZF will be set, otherwise, ZF will be clear and the AX register will contain the scan code and
                   ; ASCII character of the next key in the keyboard buffer.

                   mov    ah, 1
                   int    16h
                   jnz    KB_Preview_002
KB_Preview_001:
                   sub    ax, ax
KB_Preview_002:
                   retf

KB_Preview         endp

KB_Code            ends
                   end
