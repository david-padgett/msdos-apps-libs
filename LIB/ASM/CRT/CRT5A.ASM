; File        : CRT5A.ASM
; Module      : CRT
; System      : None
; Description : A method for determining the vertical cursor position.
; Modified    : 08/01/90 DWP Created from "CRT.ASM".

                   include crt.inc

                   public crt_wherey

crt_module_data    segment byte public 'DATA'
crt_module_data    ends

crt_module_code    segment byte public 'CODE'
                   assume cs:crt_module_code, ds:crt_module_data

; Function    : crt_wherey
; Description : Determines the current row the cursor is in.
; Expects     : Nothing.
; Returns     : ax = The current row the cursor is in.
; Modified    : 05/24/90 DWP Initial coding.
; Notes       :

crt_wherey         proc   _MODEL_SIZE

                   push   ds

                   ; Make sure ds contains the correct data segment.

                   mov    ax, crt_module_data
                   mov    ds, ax

                   ; ax = row

                   sub    ax, ax
                   mov    al, row

                   pop    ds
                   ret
crt_wherey         endp

crt_module_code    ends
                   end
