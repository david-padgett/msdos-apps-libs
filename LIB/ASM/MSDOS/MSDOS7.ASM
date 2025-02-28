; File        : MSDOS7.ASM
; Module      : MSDOS
; System      : None
; Description : Displays a text string using INT 21/09h.
; Modified    : 06/24/91 DWP Created.
; Notes       :

                   public DOS_Display_String

		   include ..\Standard\standard.inc
DOS_Data           segment byte public 'DATA'
DOS_Data           ends

DOS_Code           segment byte public 'CODE'
                   assume cs:DOS_Code, ds:DOS_Data

; Procedure   : DOS_Display_String
; Description : Displays the dollar sign ('$') terminated string pointed to by ES:DI.
; Inputs      : String_Segment = The segment of the string to display.
;               String_Offset  = The offset of the string to display.
; Updates     : Nothing.
; Outputs     : Nothing.
; Returns     : Nothing.
; Modified    : 06/21/91 DWP Initial coding.
; Notes       :

; Parameters

String_Segment     equ    <[bp + 8]>
String_Offset      equ    <[bp + 6]>

DOS_Display_String proc   far

                   ; Save the contents of the AX, DX, and DS registers.

                   push   bp
                   mov    bp, sp

                   push   ax
                   push   dx
                   push   ds

                   ; Set up the parameters to INT 21/09h.

                   mov    ax, String_Segment
                   mov    ds, ax
                   mov    dx, String_Offset

                   ; Display the specified '$' terminated string.

                   mov    ah, 9
                   int    21h

                   ; Restore the AX, DX, and DS registers to their previous state and exit.

                   pop    ds
                   pop    dx
                   pop    ax

                   mov    sp, bp
                   pop    bp

                   ret

DOS_Display_String endp

DOS_Code           ends
                   end