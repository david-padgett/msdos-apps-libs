; File        : PRINTER1.ASM
; Module      : PRINTER
; System      : None
; Description : A method for retrieving the status of a printer.
; Modified    : 08/01/90 DWP Created from "PRINTER.ASM".
; Notes       :

_PRINTER_MODULE    equ   0

                   include printer.inc

                   public PRINTER_Status

PRINTER_Code       segment byte public 'CODE'
                   assume cs:PRINTER_Code

; Function    : PRINTER_Status
; Description : Determines the status of the specified printer.
; Inputs      : Printer = The printer to get the status of [0 | 1 | 2].
; Updates     : Nothing.
; Outputs     : Nothing.
; Returns     : The status of specified printer.
; Modified    : 05/15/90 DWP Initial Coding.
; Notes       : 1) Uses PASCAL calling conventions.

; Parameters

Printer            equ    <[bp + 6]>
PARAMETER_ADJUSTMENT =    2

PRINTER_Status     proc   far

                   push   bp
                   mov    bp, sp
                   push   dx

                   mov    dx, Printer

                   mov    ah, 2
                   int    17h

                   mov    al, ah
                   sub    ah, ah

                   pop    dx
                   mov    sp, bp
                   pop    bp
                   ret    PARAMETER_ADJUSTMENT

PRINTER_Status     endp

PRINTER_Code       ends
                   end
