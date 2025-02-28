; File        : CRT5.ASM
; Module      : CRT
; System      : None
; Description : A method for determining the horizontal cursor position.
; Modified    : 08/01/90 DWP Created from "CRT.ASM".

                   include crt.inc

                   public crt_wherex

crt_module_data    segment byte public 'DATA'
crt_module_data    ends

crt_module_code    segment byte public 'CODE'
                   assume cs:crt_module_code, ds:crt_module_data

; Function    : crt_wherex
; Description : Determines the current column the cursor is in.
; Expects     : Nothing.
; Returns     : ax = The current column of the cursor.
; Modified    : 05/24/90 DWP Initial coding.
; Notes       :

crt_wherex         proc   _MODEL_SIZE

                   push   ds

                   ; Make sure ds contains the correct data segment.

                   mov    ax, crt_module_data
                   mov    ds, ax

                   ; ax = col

                   sub    ax, ax
                   mov    al, col

                   pop    ds
                   ret
crt_wherex         endp

crt_module_code    ends
                   end
