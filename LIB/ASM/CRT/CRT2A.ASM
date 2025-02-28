; File        : CRT2A.ASM
; Module      : CRT
; System      : None
; Description : A method for displaying strings on the screen.
; Modified    : 08/01/90 DWP Created from "CRT.ASM".

                   include crt.inc

                   public crt_print_str

                   extrn  crt_display_char:_MODEL_SIZE

crt_module_data    segment byte public 'DATA'
crt_module_data    ends

crt_module_code    segment byte public 'CODE'
                   assume cs:crt_module_code, ds:crt_module_data

; Procedure   : crt_print_str
; Description : Prints the specified string at the current cursor position in
;               the current window.
; Expects     : STR_SEG = Segment of string.
;               STR_OFS = Offset of string.
; Returns     : Nothing.
; Modified    : 05/24/90 DWP Initial coding.
; Notes       : 1) The string must be a NULL terminated string.

; Parameter Definitions;
; ----------------------
STR_OFS            equ    <[bp+2+_MODEL_ADJUSTMENT]>
STR_SEG            equ    <[bp+4+_MODEL_ADJUSTMENT]>

PARAMETER_ADJUSTMENT =    4

crt_print_str      proc   _MODEL_SIZE

                   push   bp
                   mov    bp, sp
                   push   ax
                   push   si
                   push   ds

                   ; ds:si = STR, ax will pass loop test first time thru

                   mov    ds, STR_SEG
                   mov    si, STR_OFS
                   sub    ax, ax
crt_print_str_000:
                   ;Loop until the 0 terminator is found.

                   lodsb
                   cmp    ax, 0
                   je     crt_print_str_001
                   call   crt_display_char
                   jmp    short crt_print_str_000

crt_print_str_001:
                   pop    ds
                   pop    si
                   pop    ax
                   mov    sp, bp
                   pop    bp
                   ret    PARAMETER_ADJUSTMENT
crt_print_str      endp

crt_module_code    ends
                   end
