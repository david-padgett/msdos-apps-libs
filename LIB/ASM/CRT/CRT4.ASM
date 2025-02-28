; File        : CRT4.ASM
; Module      : CRT
; System      : None
; Description : A method for clearing the screen.
; Modified    : 08/01/90 DWP Created from "CRT.ASM".

                   include crt.inc

                   public crt_clrscr

                   extrn  crt_calculate_offset:near
                   extrn  cursor_update_pos:_MODEL_SIZE

crt_module_data    segment byte public 'DATA'
crt_module_data    ends

crt_module_code    segment byte public 'CODE'
                   assume cs:crt_module_code, ds:crt_module_data

; Procedure   : crt_clrscr
; Description ; Clears the current window to the specified character/attribute.
; Expects     : Nothing.
; Returns     : Nothing.
; Modified    : 05/23/90 DWP Recoded.
; Notes       : 1) The cursor is placed in the home position.

crt_clrscr         proc   _MODEL_SIZE

                   push   ax
                   push   bx
                   push   cx
                   push   dx
                   push   di
                   push   ds
                   push   es

                   ; Make sure ds contains the correct data segment.

                   mov    ax, crt_module_data
                   mov    ds, ax

                   ; Determine offset of top left corner of window.

                   mov    ah, wn_min_col
                   mov    al, wn_min_row
                   call   crt_calculate_offset

                   ; es:di points to the top left corner of the current window

                   mov    di, ax
                   mov    es, [video_segment]

                   ; ax = SPACE + current video attr, bl = height, bh = length
                   ; dx = (wn_max_length - wn_length - 1) * 2, cx = 0

                   mov    al, ' '
                   mov    ah, video_attr
                   mov    bl, wn_height
                   mov    bh, wn_length
                   inc    bh
                   mov    dx, wn_max_length
                   sub    dl, bh
                   shl    dx, 1
                   sub    cx, cx
crt_clrscr_000:
                   ; Loop until entire window is cleared.

                   cmp    bl, -1
                   je     crt_clrscr_001

                   mov    cl, bh
                   rep    stosw

                   add    di, dx
                   dec    bl
                   jmp    short crt_clrscr_000
crt_clrscr_001:
                   ; Go to the home position and update the cursor position.

                   sub    ax, ax
                   mov    row, al
                   mov    col, al
                   push   ax
                   push   ax
                   call   far ptr cursor_update_pos

                   pop    es
                   pop    ds
                   pop    di
                   pop    dx
                   pop    cx
                   pop    bx
                   pop    ax
                   ret
crt_clrscr         endp

crt_module_code    ends
                   end
