; File        : CRT1A.ASM
; Module      : CRT
; System      : None
; Description : A method to calculate the memory address of screen one set of
;               screen coordinates.
; Modified    : 08/01/90 DWP Created from "CRT.ASM".

                   include crt.inc

crt_module_data    segment byte public 'DATA'
crt_module_data    ends

crt_module_code    segment byte public 'CODE'
                   assume cs:crt_module_code, ds:crt_module_data

; PRIVATE code.

; Function    : crt_calculate_offset
; Description : Calculates the address for the screen position specified.
; Expects     : al = The row in question.
;               ah = The column in question.
; Returns     : di = Offset from start of current video page of the specified
;                    screen coordinates.
; Modified    : 02/15/90 DWP Modified.
; Notes       :

crt_calculate_offset proc near

                   push   bx
                   push   ax

                   ; ax = ((row * 80) + col) * 2

                   sub    ah, ah
                   shl    ax, 1
                   shl    ax, 1
                   shl    ax, 1
                   shl    ax, 1
                   mov    bx, ax
                   shl    bx, 1
                   shl    bx, 1
                   add    ax, bx
                   pop    bx
                   mov    bl, bh
                   sub    bh, bh
                   add    ax, bx
                   shl    ax, 1

                   pop    bx
                   ret
crt_calculate_offset endp

crt_module_code    ends
                   end
