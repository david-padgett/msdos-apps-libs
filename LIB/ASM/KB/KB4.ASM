; File        : KB4.ASM
; Module      : KB
; System      : None
; Description : A method for determining if an enhanced keyboard is present.
; Modified    : 04/16/91 DWP Created.
; Notes       :

_KB_MODULE         =      0

                   include kb.inc

                   extrn  KB_Retrieve_Status_Word : far
                   public KB_Enhanced_Keyboard_Present

KB_Code            segment byte public 'CODE'
                   assume cs:KB_Code

; Function    : KB_Enhanced_Keyboard_Present
; Description : Determines if an enhanced keyboard is present.
; Inputs      : Nothing.
; Updates     : Nothing.
; Outputs     : Nothing.
; Returns     : A value of TRUE is returned in the AX register if an enhanced keyboard is present, FALSE otherwise.
; Modified    : 04/25/91 DWP Initial Coding.
; Notes       :

KB_Enhanced_Keyboard_Present proc far

                   ; Retrieve the keyboard status.

                   call   KB_Retrieve_Status_Word

                   ; Determine if an enhanced keyboard is present.  An enhanced keyboard is present if bit 4 of the AX register
                   ; is set.

                   and    ax, 10h
                   push   cx
                   mov    cl, 4
                   shr    ax, cl
                   pop    cx

                   retf

KB_Enhanced_Keyboard_Present endp

KB_Code            ends
                   end