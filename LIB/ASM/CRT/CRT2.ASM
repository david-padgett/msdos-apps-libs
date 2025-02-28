; File        : CRT2.ASM
; Module      : CRT
; System      : None
; Description : A method for displaying characters on the screen.
; Modified    : 08/01/90 DWP Created from "CRT.ASM".

                   include crt.inc

                   public crt_print_car

                   extrn  crt_display_char:_MODEL_SIZE

crt_module_data    segment byte public 'DATA'
crt_module_data    ends

crt_module_code    segment byte public 'CODE'
                   assume cs:crt_module_code, ds:crt_module_data

; Procedure   : crt_print_char
; Description : Prints the specified character at the current cursor position
;               in the current window.
; Expects     : CHARACTER = The character to print.
; Returns     : Nothing.
; Modified    : 05/24/90 DWP Initial coding.
; Notes       :

; Parameter Definitions;
; ----------------------
CHARACTER          equ    <[bp+2+_MODEL_ADJUSTMENT]>

PARAMETER_ADJUSTMENT =    2

crt_print_char     proc   _MODEL_SIZE

                   push   bp
                   mov    bp, sp
                   push   ax

                   mov    ax, CHARACTER
                   call   crt_display_char

                   pop    ax
                   mov    sp, bp
                   pop    bp
                   ret    PARAMETER_ADJUSTMENT
crt_print_char     endp

crt_module_code    ends
                   end
