; File        : CRT7.ASM
; Module      : CRT
; System      : None
; Description : A method for initializing the CRT module.
; Modified    : 08/01/90 DWP Created from "CRT.ASM".

                   include crt.inc

                   public crt_init

crt_module_data    segment byte public 'DATA'
crt_module_data    ends

crt_module_code    segment byte public 'CODE'
                   assume cs:crt_module_code, ds:crt_module_data

; Procedure   : crt_init
; Description : Initializes all of the global variables in this module.
; Expects     : Nothing.
; Returns     : Nothing.
; Modified    : 05/23/90 DWP Initial coding.
; Notes       : 1) If this isn't called before using any of the procedures
;                  in this module, unpredictable results may occur.

crt_init           proc   _MODEL_SIZE

                   push   ax
                   push   ds

                   mov    ax, crt_module_data
                   mov    ds, ax

		   ; Initialize wn_max_row, wn_min_row, wn_max_row, wn_min_col,
                   ; wn_max_height, wn_max_length, wn_height, wn_length
                   ; row, and col.

                   mov    ax, 24
                   mov    wn_max_row, al
                   mov    wn_height, al
                   inc    ax
                   mov    wn_max_height, ax
                   mov    al, 79
                   mov    wn_max_col, al
                   mov    wn_length, al
                   inc    ax
                   mov    wn_max_length, ax
                   mov    wn_min_row, ah
                   mov    wn_min_col, ah
                   mov    row, ah
                   mov    col, ah

		   ; Video attribute is lightgray on black, cursor update is
                   ; on.

                   mov    video_attr, LIGHTGRAY
                   or     flag_1, 1

                   pop    ds
                   pop    ax
                   ret
crt_init           endp

crt_module_code    ends
                   end
