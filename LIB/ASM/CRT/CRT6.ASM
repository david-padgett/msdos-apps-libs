; File        : CRT6.ASM
; Module      : CRT
; System      : None
; Description :
; Modified    : 08/01/90 DWP Created from "CRT.ASM".

                   include crt.inc

                   public crt_open_window

crt_module_data    segment byte public 'DATA'
crt_module_data    ends

crt_module_code    segment byte public 'CODE'
                   assume cs:crt_module_code, ds:crt_module_data

; Function    : crt_open_window
; Description : Opens the specified window.
; Expects     : WN_SEG = segment of window_rec to open
;               WN_OFS = offset of window_rec to open
; Returns     : ax = DOS services error code.
; Modified    : 05/23/90 Recoded.
; Notes       :

; Parameter Definitions:
; ----------------------
WN_SEG             equ    <[bp+4+_MODEL_ADJUSTMENT]>
WN_OFS             equ    <[bp+6+_MODEL_ADJUSTMENT]>

PARAMETER_ADJUSTMENT =    4

crt_open_window    proc   _MODEL_SIZE

                   push   bp
                   mov    bp, sp

                   push   ax
                   push   bx
                   push   cx
                   push   dx
                   push   si
                   push   ds
                   push   es

                   ; Make sure ds is pointing to the correct segment.

                   mov    ax, crt_module_data
                   mov    ds, ax

                   ; point es:di to the window_rec being manipulated

                   mov    es, WN_SEG
                   mov    di, WN_OFS

                   ; If not a popup window, skip memory allocation.

                   cmp    word ptr es:[di + WN_REC_TYPE], WN_POPUP
                   jne    crt_open_window_001

                   ; calculate size of window
                   ; bx = ((WN_REC_LENGTH * 2) * WN_REC_HEIGHT) / 16

                   sub    ax, ax
                   mov    al, es:[di + WN_REC_LENGTH]
                   shl    ax, 1
                   mul    byte ptr es:[di + WN_REC_HEIGHT]

                   ; If there was a remainder, allocate an extra 16 byte block.

                   mov    cx, 4
                   div    cl
                   cmp    ah, 0
                   je     crt_open_window_002
                   inc    ax

crt_open_window_001:

                   mov    bx, ax
                   mov    ah, _ALLOCATE_MEM
                   int    _DOS_SERVICES
                   jnc    crt_open_window_002

                   ; Insufficient memory, so exit.

                   jmp    crt_open_window_end

                   ; Memory was allocated, so continue.

crt_open_window_002:

                   mov    al, es:[di + WN_REC_ROW]
                   mov    wn_min_row, al
                   mov    ah, es:[di + WN_REC_HEIGHT]
                   mov    wn_length, ah
                   add    al, ah
                   mov    wn_max_row, al

                   mov    al, es:[di + WN_REC_COL]
                   mov    wn_min_col, al
                   mov    ah, es:[di + WN_REC_HEIGHT]
                   mov    wn_height, ah
                   add    al, ah
                   mov    wn_max_col, al

crt_open_window_end:
                   pop    es
                   pop    ds
                   pop    si
                   pop    dx
                   pop    cx
                   pop    bx
                   pop    ax
                   mov    sp, bp
                   pop    bp
                   ret    PARAMETER_ADJUSTMENT
crt_open_window    endp

crt_close_window   proc   _MODEL_SIZE
crt_close_window   endp

crt_select_window  proc   _MODEL_SIZE
crt_select_window  endp

crt_modify_window  proc   _MODEL_SIZE
crt_modify_window  endp
