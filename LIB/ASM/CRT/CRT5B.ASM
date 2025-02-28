; File        : CRT1A.ASM
; Module      : CRT
; System      : None
; Description : The global variables for the CRT module.
; Modified    : 08/01/90 DWP Created from "CRT.ASM".

                   include crt.inc

                   public crt_gotoxy

crt_module_data    segment byte public 'DATA'
crt_module_data    ends

crt_module_code    segment byte public 'CODE'
                   assume cs:crt_module_code, ds:crt_module_data

; Procedure   : crt_gotoxy
; Description : Positions the cursor at the specified coordinates.  The
;               coordinates are relative to the current window only.
; Expects     : XPOS = The new column.
;               YPOS = The new row.
; Returns     : Nothing.
; Modified    : 05/24/90 DWP Initial coding.
; Notes       :

; Parameter Definitions:
; ----------------------
YPOS               equ    <[bp+2+_MODEL_ADJUSTMENT]>
XPOS               equ    <[bp+4+_MODEL_ADJUSTMENT]>

PARAMETER_ADJUSTMENT =    4

crt_gotoxy         proc   _MODEL_SIZE

                   push   bp
                   mov    bp, sp
                   push   ax
                   push   ds

                   ; Make sure ds contains the correct data segment.

                   mov    ax, crt_module_data
                   mov    ds, ax

                   ; col = XPOS, row = YPOS

                   mov    ax, XPOS
                   mov    col, al
                   mov    ax, YPOS
                   mov    row, al

                   pop    ds
                   pop    ax
                   mov    sp, bp
                   pop    bp
                   ret    PARAMETER_ADJUSTMENT
crt_gotoxy         endp
