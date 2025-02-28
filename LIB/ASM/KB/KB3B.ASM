; File        : KB3B.ASM
; Module      : KB
; System      : None
; Description : A method for retrieving keyboard status information.
; Modified    : 04/25/91 DWP Created.
; Notes       :

_KB_MODULE         =      0

                   include kb.inc

                   public KB_Retrieve_Status_Word

KB_Code            segment byte public 'CODE'
                   assume cs:KB_Code

; Function    : KB_Retrieve_Status_Word
; Description : Retrieves the status word of the keyboard.
; Inputs      : Nothing.
; Updates     : Nothing.
; Outputs     : Nothing.
; Returns     : The keyboard status word is returned in the AX register.
;                    AL Bit 7 = Read-ID in progress.
;                           6 = Last code read was first of two ID codes.
;                           5 = Force Num Lock if read-ID and enhanced keyboard.
;                           4 = Enhanced keyboard installed.
;                           3 = Right ALT key pressed.
;                           2 = Right CTRL key pressed.
;                           1 = Last code read was E0h.
;                           0 = Last code read was E1h.
;                    AH Bit 7 = Keyboard transmit error flag.
;                           6 = LED update in progress flag.
;                           5 = Resend received from keyboard flag.
;                           4 = ACK received from keyboard flag.
;                           3 = Reserved, must be 0.
;                           2 = Caps Lock LED flag.
;                           1 = Num Lock LED flag.
;                           0 = Scroll Lock LED flag.
; Modified    : 04/25/91 DWP Initial Coding.
; Notes       :

KB_Retrieve_Status_Word proc far

                   ; Save the DS and BX registers.

                   push   bx
                   push   ds

                   ; Place absolute memory location 40h:17H into AX.

                   mov    ax, 40h
                   mov    ds, ax
                   mov    bx, 96h
                   mov    ax, [bx]

                   ; Restore DS and BX registers.

                   pop    ds
                   pop    bx

                   retf

KB_Retrieve_Status_Word endp

KB_Code            ends
                   end
