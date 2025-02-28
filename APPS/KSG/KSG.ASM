; File        : KSG.ASM
; Module      : KSG
; System      : KSG
; Description :
; Modified    : 06/21/91 DWP Created.
; Notes       :

MODEL_SIZE         equ    <FAR>

                   include asm.inc

PAGE0_segment      segment at 0
                   org    9h * 4
int_09h            dd     ?
                   org    16h * 4
int_16h            dd     ?
PAGE0_segment      ends

comment *
KSG_stack_segment  segment byte stack 'STACK'
                   dw     100 dup(0)
KSG_stack_segment  ends

KSG_data_segment   segment byte public 'DATA'
program_name       db     'Key-Stroke Generator V1.0a'
newline            db     0dh, 0ah, '$'
KSG_data_segment   ends
*

KSG_code_segment   segment byte public 'CODE'
                   assume cs:KSG_code_segment ;, ds:KSG_data_segment, ss:KSG_stack_segment
                   org    100h
KSG:
;                   mov    ax, KSG_data_segment
;                   mov    ds, ax
;                   mov    es, ax
                   jmp    far ptr KSG_main

; Procedure   : KSG_exit
; Description : Exits to DOS.
; Expects     : AL = The exit code which will be returned to DOS.
; Returns     : Nothing.
; Modified    : 06/21/91 DWP Initial coding.
; Notes       :
comment *
KSG_exit           proc   MODEL_SIZE

                   ; Exit to DOS.

                   mov    ah, 4ch
                   int    21h
                   ret

KSG_exit           endp
*
; Procedure   : KSG_interrupt
; Description :
; Expects     :
; Returns     :
; Modified    :
; Notes       :

KSG_interrupt      proc   MODEL_SIZE

                   push   ax
                   push   di
                   push   es

                   mov    ax, 0b800h
                   mov    es, ax
                   xor    ax, ax
                   mov    di, ax
                   mov    ax, es:[di]
                   inc    ah
                   inc    al
                   mov    es:[di], ax

                   pop    es
                   pop    di
                   pop    ax

                   jmp    cs:keyboard_vector

KSG_interrupt      endp

; Procedure   : KSG_main
; Description : The main entry point to the KSG program.
; Expects     : Nothing.
; Returns     : Nothing.
; Modified    : 06/21/91 DWP Initial coding.
; Notes       :

KSG_main           proc   MODEL_SIZE
                   assume ds:PAGE0_segment

                   mov    ax, PAGE0_segment
                   mov    ds, ax
                   les    ax, [int_16h]
                   mov    word ptr cs:keyboard_vector, ax
                   mov    word ptr cs:keyboard_vector + 2, es

                   cli
                   mov  word ptr int_16h, offset KSG_interrupt
                   mov  word ptr int_16h + 2, cs
                   sti

                   ; Exit to DOS.

                   mov    ax, 3100h
                   mov    dx, 20
                   int    21h

KSG_main           endp

keyboard_vector    dd     0

KSG_code_segment   ends
                   end KSG