; File        : CRT1.ASM
; Module      : CRT
; System      : None
; Description : A method to write characters to the console.
; Modified    : 08/01/90 DWP Created from "CRT.ASM".

                   include crt.inc

                   extrn  crt_scroll:_MODEL_SIZE
                   extrn  cursor_update_pos:_MODEL_SIZE

crt_module_data    segment byte public 'DATA'
crt_module_data    ends

crt_module_code    segment byte public 'CODE'
                   assume cs:crt_module_code, ds:crt_module_data

; PRIVATE code.

; Procedure   : crt_display_char
; Description : Displays the specified character on the screen.
; Expects     : al = The character to display.
; Returns     : Nothing.
; Modified    : 05/22/90 DWP Updated.
; Notes       : 1) Video_attr, wn_min_row, wn_min_col, wn_max_row, wn_max_col,
;                  row, col must all be current
;               2) Ah is modified.

crt_display_char   proc   near

                   push   bx
                   push   ds

                   ; ds = data segment, ah = 0

                   mov    bx, crt_module_data
                   mov    ds, bx
                   sub    ah, ah

                   ; Special characters.

                   cmp    al, 0ah                ;Line feed.
                   jne    crt_display_char_002
                   inc    row
                   mov    al, wn_height
                   cmp    row, al                ;if row > window height then
                   jle    crt_display_char_001   ;scroll up a line
                   mov    al, SCROLL_UP
                   push   ax
                   call   far ptr crt_scroll
                   dec    row

crt_display_char_001:

                   jmp    crt_display_char_006

crt_display_char_002:

                   cmp    al, 0dh                ;Carriage return.
                   jne    crt_display_char_003
                   mov    col, 0
                   jmp    crt_display_char_006

crt_display_char_003:

                   cmp    al, 8                  ;Backspace.
                   jne    crt_display_char_005
                   dec    col
                   cmp    col, ah
                   jge    crt_display_char_004
                   mov    al, wn_length
                   mov    col, al
                   dec    row
                   cmp    row, ah                ;if row < 0 then scroll down
                   jge    crt_display_char_004   ;and set row equal to 0
                   mov    al, SCROLL_DOWN
                   push   ax
                   call   far ptr crt_scroll
                   mov    row, ah

crt_display_char_004:

                   jmp    short crt_display_char_006

crt_display_char_005:

                   ; bx = ((row * 80) + col) * 2

                   push   dx

                   sub    dx, dx
                   mov    dl, wn_min_row
                   add    dl, row
                   shl    dx, 1
                   shl    dx, 1
                   shl    dx, 1
                   shl    dx, 1
                   mov    bx, dx
                   shl    dx, 1
                   shl    dx, 1
                   add    bx, dx
                   sub    dx, dx
                   mov    dl, wn_min_col
                   add    dl, col
                   add    bx, dx
                   shl    bx, 1

                   pop    dx

		   ; ah = current video attribute, ds = current video segment

                   mov    ah, video_attr
                   push   ds
                   mov    ds, [video_segment]

                   ; Output the char to the screen using the current attribute.

                   mov    [bx], ax
                   pop    ds

                   ; Adjust the column and row, if necessary.

                   inc    col
                   mov    al, col
                   cmp    al, wn_length
                   jle    crt_display_char_006
                   mov    col, 0
                   inc    row
                   mov    al, wn_height
                   cmp    row, al
                   jle    crt_display_char_006
                   mov    ax, SCROLL_UP
                   push   ax
                   call   far ptr crt_scroll
                   dec    row

crt_display_char_006:

                   ; Determine if the cursor should be moved (updated).

                   test   byte ptr flag_1, 1
                   je     crt_display_char_007
                   sub    ax, ax
                   mov    al, col
                   push   ax
                   mov    al, row
                   push   ax
                   call   far ptr cursor_update_pos

crt_display_char_007:

                   pop    ds
                   pop    bx
                   ret
crt_display_char   endp

crt_module_code    ends
                   end
