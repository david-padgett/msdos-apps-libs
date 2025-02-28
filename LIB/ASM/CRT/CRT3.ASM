; File        : CRT3.ASM
; Module      : CRT
; System      : None
; Description : A method for scrolling the screen.
; Modified    : 08/01/90 DWP Created from "CRT.ASM".

                   include crt.inc

                   public crt_scroll

                   extrn  crt_calculate_offset:near

crt_module_data    segment byte public 'DATA'
crt_module_data    ends

crt_module_code    segment byte public 'CODE'
                   assume cs:crt_module_code, ds:crt_module_data

; Procedure   : crt_scroll
; Description : Scrolls the contents of the current window one row or column
;               in the specified direction.  A blank line is inserted on the
;               opposite side of the direction specified.
; Expects     : DIR = The direction to scroll the current window,
;                     [SCROLL_UP | SCROLL_DOWN | SCROLL_LEFT | SCROLL_RIGHT].
; Returns     : Nothing.
; Modified    : 05/22/90 DWP Recoded.
; Notes       :

; Parameter Definitions:
; ----------------------
DIR                equ    <[bp+2+_MODEL_ADJUSTMENT]>

PARAMETER_ADJUSTMENT =    2

crt_scroll         proc   _MODEL_SIZE

                   push   bp
                   mov    bp, sp
                   push   ax
                   push   bx
                   push   cx
                   push   dx
                   push   si
                   push   di
                   push   ds
                   push   es

                   ; Make sure ds is pointing to the correct segment.

                   mov    ax, crt_module_data
                   mov    ds, ax

                   ; bx = wn_length, dx = wn_max_length * 2
                   ; es = current window segment

                   sub    bx, bx
                   mov    bl, wn_length
                   shl    bx, 1
                   mov    dx, wn_max_length
                   shl    dx, 1
                   mov    es, [video_segment]

                   ; Determine the axis of the scroll.

                   cmp    word ptr DIR, SCROLL_DOWN
                   jg     crt_scroll_004

                   ; bx = # chars * 2 in 1 row of cur. window (wn_length + 1)

                   inc    bx
                   inc    bx

                   ; Determine y-axis direction (up or down).

                   cmp    word ptr DIR, SCROLL_UP
                   jne    crt_scroll_001

                   ; Code for scrolling up, blank line added on last line.
                   ; si = starting address of top of current window

                   mov    al, wn_min_row
                   inc    al
                   mov    ah, wn_min_col
                   call   crt_calculate_offset
                   mov    si, ax

                   ; al = loop counter, ds = current video segment
                   ; movsw direction = forward

                   mov    al, wn_height
                   push   ds
                   mov    ds, [video_segment]
                   cld
crt_scroll_000:
                   ; Loop until entire window has been scrolled up one line.

                   cmp    al, 0
                   je     crt_scroll_003

                   ; Move line one row up.

                   mov    di, si
                   sub    di, dx
                   mov    cx, bx
                   shr    cx, 1
                   rep    movsw

                   ; si = start of next line

                   add    si, dx
                   sub    si, bx
                   dec    al
                   jmp    short crt_scroll_000

crt_scroll_001:
                   ; Code for scrolling down, blank line added on first line.
                   ; si = starting address of bottom of current window

                   mov    al, wn_max_row
                   dec    al
                   mov    ah, wn_max_col
                   call   crt_calculate_offset
                   mov    si, ax

                   ; al = loop counter, ds = current video segment
                   ; movsw direction = backward

                   mov    al, wn_height
                   push   ds
                   mov    ds, [video_segment]
                   std

crt_scroll_002:
                   ; Loop until entire window has been scrolled down one line.

                   cmp    al, 0
                   je     crt_scroll_003

                   ; Move line one row down.

                   mov    di, si
                   add    di, dx
                   mov    cx, bx
                   shr    cx, 1
                   rep    movsw

                   ; si = end of previous line

                   sub    si, dx
                   add    si, bx
                   dec    al
                   jmp    short crt_scroll_002

crt_scroll_003:
                   ; Blank out the line that has been inserted.

                   pop    ds

                   mov    ah, video_attr
                   mov    al, ' '
                   mov    cx, bx
                   shr    cx, 1
                   rep    stosw
                   jmp    short crt_scroll_008

crt_scroll_004:
                   ; If not a valid parameter then exit procedure.

                   cmp    word ptr DIR, SCROLL_RIGHT
                   jg     short crt_scroll_008

                   ; Determine x-axis direction (left or right).

                   cmp    word ptr DIR, SCROLL_LEFT
                   jne    crt_scroll_006

                   ; Code for scrolling left, blanking out rightmost column.
                   ; si = starting address of top left of current window

                   mov    al, wn_min_row
                   mov    ah, wn_min_col
                   inc    ah
                   call   crt_calculate_offset
                   mov    si, ax

                   ; al = loop counter, ds = current video segment
                   ; movsw dir = forwards

                   mov    al, wn_height
                   mov    ah, video_attr
                   push   ds
                   mov    ds, [video_segment]
                   cld

crt_scroll_005:
                   ; Loop until entire window has been scrolled one col left.

                   cmp    al, -1
                   je     crt_scroll_008

                   ; Move line one column to the left.

                   mov    di, si
                   dec    di
                   dec    di
                   mov    cx, bx
                   shr    cx, 1
                   rep    movsw

                   ; Blank out the last char in the line.

                   mov    cx, ax
                   mov    al, ' '
                   stosb
                   mov    ax, cx

                   ; si = start of next line

                   add    si, dx
                   sub    si, bx
                   dec    al
                   jmp    short crt_scroll_005

crt_scroll_006:
                   ; code for scrolling right, blanking out leftmost column
                   ; si = starting address of top right of current window

                   mov    al, wn_min_row
                   mov    ah, wn_max_col
                   dec    ah
                   call   crt_calculate_offset
                   mov    si, ax

                   ; al = loop counter, ds = current video segment
                   ; movsw dir = backwards

                   mov    al, wn_height
                   mov    ah, video_attr
                   push   ds
                   mov    ds, [video_segment]
                   std

crt_scroll_007:
                   ; Loop until entire window has been scrolled one col right.

                   cmp    al, -1
                   je     crt_scroll_008

                   ; Move row one column to the right.

                   mov    di, si
                   inc    di
                   inc    di
                   mov    cx, bx
                   shr    cx, 1
                   rep    movsw

                   ; Blank out the first char in the line.

                   mov    cx, ax
                   mov    al, ' '
                   stosb
                   mov    ax, cx

                   ; si = start of next line

                   add    si, dx
                   add    si, bx
                   dec    al
                   jmp    short crt_scroll_007

crt_scroll_008:
                   pop    es
                   pop    ds
                   pop    di
                   pop    si
                   pop    dx
                   pop    cx
                   pop    bx
                   pop    ax
                   mov    sp, bp
                   pop    bp
                   ret    PARAMETER_ADJUSTMENT
crt_scroll         endp

crt_module_code    ends
                   end
