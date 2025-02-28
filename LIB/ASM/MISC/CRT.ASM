; File        : CRT.ASM
; Description : Various video manipulation routines.
; Modified    : 05/22/90 DWP Created.

CRT                equ    0

_MODEL_SIZE        equ    <far>
_MODEL_ADJUSTMENT  equ    4

		   include crt.def
		   include cursor.def
		   include bios.def
		   include dos.def

crt_module_data    segment byte public 'data'

                   ; All data defaults to the standard DOS screen.

video_attr         db     7                      ;hi=foreground, lo=background
video_segment      dw     0b800h                 ;seg of current screen bufr

row                db     0                      ;relative to window
col                db     0                      ;relative to window

wn_max_row         db     24                     ;max row in window (absolute)
wn_min_row         db     0                      ;min row in window (absolute)
wn_max_col         db     79                     ;max col in window (absolute)
wn_min_col         db     0                      ;min col in window (absolute)

wn_height          db     24                     ;wn_max_row - wn_min_row
wn_length          db     79                     ;wn_max_col - wn_min_col
wn_max_height      dw     25                     ;max allowable wn height
wn_max_length      dw     80                     ;max allowable wn length

flag_1             db     1                      ;bit 0 - update cursor
                                                 ;bit 1 - use ROM BIOS /future
crt_module_data    ends

crt_module_code    segment byte public 'code'
                   assume cs:crt_module_code, ds:crt_module_data

; PRIVATE code

; Procedure   : crt_display_char
; Description : Displays the character on the screen.
; Expects     : al = character to display
; Returns     : Nothing.
; Modified    : 05/22/90 DWP Updated.
; Notes       : 1) video_attr, wn_min_row, wn_min_col, wn_max_row, wn_max_col, row,
;                  col must all be current
;               2) ah is modified

crt_display_char   proc   near

                   push   bx
                   push   ds

                   ; ds = data segment, ah = 0

                   mov    bx, crt_module_data
                   mov    ds, bx
                   sub    ah, ah

                   ; special characters

                   cmp    al, 0ah                ;line feed
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

                   cmp    al, 0dh                ;carriage return
                   jne    crt_display_char_003
                   mov    col, 0
                   jmp    crt_display_char_006

crt_display_char_003:

                   cmp    al, 8                  ;backspace
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

                   ; output the char to the screen using the current attribute

                   mov    [bx], ax
                   pop    ds

                   ; adjust the column and row, if necessary

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

                   ; determine if the cursor should be moved (updated)

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

; Function    : crt_calculate_offset
; Description : Calculates the address for the screen position specified.
; Expects     : al = row
;               ah = column
; Returns     : di = offset from start of page
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

; PUBLIC code

; Procedure   : crt_print_char
; Description : Prints the specified character at the current cursor position
;               in the current window.
; Expects     : CHARACTER = the character to print
; Returns     : Noting.
; Modified    : 05/24/90 DWP Initial coding.
; Notes       :

; Parameter Definitions;
; ----------------------
CHARACTER          equ    <[bp+2+_MODEL_ADJUSTMENT]>

PARAMETER_ADJUSTMENT =    2

crt_print_char     proc   _MODEL_SIZE

                   push   bp
                   mov    bp, sp
                   push   ax

                   mov    ax, CHARACTER
                   call   crt_display_char

                   pop    ax
                   mov    sp, bp
                   pop    bp
                   ret    PARAMETER_ADJUSTMENT
crt_print_char     endp

; Procedure   : crt_print_str
; Description : Prints the specified string at the current cursor position in
;               the current window.
; Expects     : STR_SEG = segment of string
;               STR_OFS = offset of string
; Returns     : Nothing.
; Modified    : 05/24/90 DWP Initial coding.
; Notes       : 1) The string must be an ASCIIZ string (0 terminated)

; Parameter Definitions;
; ----------------------
STR_OFS            equ    <[bp+2+_MODEL_ADJUSTMENT]>
STR_SEG            equ    <[bp+4+_MODEL_ADJUSTMENT]>

PARAMETER_ADJUSTMENT =    4

crt_print_str      proc   _MODEL_SIZE

                   push   bp
                   mov    bp, sp
                   push   ax
                   push   si
                   push   ds

                   ; ds:si = STR, ax will pass loop test first time thru

                   mov    ds, STR_SEG
                   mov    si, STR_OFS
                   sub    ax, ax
crt_print_str_000:
                   ; loop until the 0 terminator is found

                   lodsb
                   cmp    ax, 0
                   je     crt_print_str_001
                   call   crt_display_char
                   jmp    short crt_print_str_000

crt_print_str_001:
                   pop    ds
                   pop    si
                   pop    ax
                   mov    sp, bp
                   pop    bp
                   ret    PARAMETER_ADJUSTMENT
crt_print_str      endp

; Procedure   : crt_scroll
; Description : Scrolls the contents of the current window one row or column
;               in the specified direction.  A blank line is inserted on the
;               opposite side of the direction specified.
; Expects     : DIR = [SCROLL_UP | SCROLL_DOWN | SCROLL_LEFT | SCROLL_RIGHT]
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

                   ; make sure ds is pointing to the correct segment

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

                   ; determine the axis of the scroll

                   cmp    word ptr DIR, SCROLL_DOWN
                   jg     crt_scroll_004

                   ; bx = # chars * 2 in 1 row of cur. window (wn_length + 1)

                   inc    bx
                   inc    bx

                   ; determine y-axis direction (up or down)

                   cmp    word ptr DIR, SCROLL_UP
                   jne    crt_scroll_001

                   ; code for scrolling up, blank line added on last line
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
                   ; loop until entire window has been scrolled up one line

                   cmp    al, 0
                   je     crt_scroll_003

                   ; move line one row up

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
                   ; code for scrolling down, blank line added on first line
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
                   ; loop until entire window has been scrolled down one line

                   cmp    al, 0
                   je     crt_scroll_003

                   ; move line one row down

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
                   ; blank out the line that has been inserted

                   pop    ds

                   mov    ah, video_attr
                   mov    al, ' '
                   mov    cx, bx
                   shr    cx, 1
                   rep    stosw
                   jmp    short crt_scroll_008
crt_scroll_004:
                   ; if not a valid parameter then exit procedure

                   cmp    word ptr DIR, SCROLL_RIGHT
                   jg     short crt_scroll_008

                   ; determine x-axis direction (left or right)

                   cmp    word ptr DIR, SCROLL_LEFT
                   jne    crt_scroll_006

                   ; code for scrolling left, blanking out rightmost column
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
                   ; loop until entire window has been scrolled one col left

                   cmp    al, -1
                   je     crt_scroll_008

                   ; move line one column to the left

                   mov    di, si
                   dec    di
                   dec    di
                   mov    cx, bx
                   shr    cx, 1
                   rep    movsw

                   ; blank out the last char in the line

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
                   ; loop until entire window has been scrolled one col right

                   cmp    al, -1
                   je     crt_scroll_008

                   ; move row one column to the right

                   mov    di, si
                   inc    di
                   inc    di
                   mov    cx, bx
                   shr    cx, 1
                   rep    movsw

                   ; blank out the first char in the line

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

                   ; make sure ds contains the correct data segment

                   mov    ax, crt_module_data
                   mov    ds, ax

                   ; determine offset of top left corner of window

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
                   ; loop until entire window is cleared

                   cmp    bl, -1
                   je     crt_clrscr_001

                   mov    cl, bh
                   rep    stosw

                   add    di, dx
                   dec    bl
                   jmp    short crt_clrscr_000
crt_clrscr_001:
                   ; go to the home position and update the cursor position.

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

; Function    : crt_wherex
; Description : Determines the current column the cursor is in.
; Expects     : Nothing.
; Returns     : ax = col
; Modified    : 05/24/90 DWP Initial coding.
; Notes       :

crt_wherex         proc   _MODEL_SIZE

                   push   ds

                   ; make sure ds contains the correct data segment

                   mov    ax, crt_module_data
                   mov    ds, ax

                   ; ax = col

                   sub    ax, ax
                   mov    al, col

                   pop    ds
                   ret
crt_wherex         endp

; Function    : crt_wherey
; Description : Determines the current row the cursor is in.
; Expects     : Nothing.
; Returns     : ax = row
; Modified    : 05/24/90 DWP Initial coding.
; Notes       :

crt_wherey         proc   _MODEL_SIZE

                   push   ds

                   ; make sure ds contains the correct data segment

                   mov    ax, crt_module_data
                   mov    ds, ax

                   ; ax = row

                   sub    ax, ax
                   mov    al, row

                   pop    ds
                   ret
crt_wherey         endp

; Procedure   : crt_gotoxy
; Description : Positions the cursor at the specified coordinates.  The
;               coordinates are relative to the current window only.
; Expects     : XPOS = the new column
;               YPOS = the new row
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

                   ; make sure ds contains the correct data segment

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

; Function    : crt_open_window
; Description : Opens the specified window.
; Expects     : WN_SEG = segment of window_rec to open
;               WN_OFS = offset of window_rec to open
; Returns     : ax = DOS services error code
; Modified    : 05/23/90 Recoded.
; Notes       :

; Parameter Definitions:
; ----------------------
WN_OFS             equ    <[bp+2+_MODEL_ADJUSTMENT]>
WN_SEG             equ    <[bp+4+_MODEL_ADJUSTMENT]>

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

                   ; make sure ds is pointing to the correct segment

                   mov    ax, crt_module_data
                   mov    ds, ax

                   ; point es:di to the window_rec being manipulated

                   mov    es, WN_SEG
                   mov    di, WN_OFS

                   ; if not a popup window, skip memory allocation

                   cmp    word ptr es:[di].wn_rec_type, WN_POPUP
                   jne    crt_open_window_002

                   ; calculate size of window
                   ; ax = (((WN_REC_LENGTH * 2) * WN_REC_HEIGHT) / 16) +
                   ;       sizeof(crt_module_data)

                   sub    ax, ax
                   mov    al, es:[di].wn_rec_length
                   shl    ax, 1
                   mul    byte ptr es:[di].wn_rec_height
                   add    ax, CRT_MODULE_DATA_SIZE

                   ; if there was a remainder, allocate an extra 16 byte block

                   mov    cx, 4
                   div    cl
                   cmp    ah, 0
                   je     crt_open_window_002
                   inc    ax

crt_open_window_001:

                   ; allocate the memory needed to save the area underneath
                   ; the window

                   mov    bx, ax
                   mov    ah, _ALLOCATE_MEM
                   int    _DOS_SERVICES
                   jnc    crt_open_window_002

                   ; insufficient memory, so exit

                   jmp    crt_open_window_end

                   ; memory was allocated, so continue

crt_open_window_002:

                   mov    al, es:[di].wn_rec_row
                   mov    wn_min_row, al
                   mov    ah, es:[di].wn_rec_height
                   mov    wn_length, ah
                   add    al, ah
                   mov    wn_max_row, al

                   mov    al, es:[di].wn_rec_col
                   mov    wn_min_col, al
                   mov    ah, es:[di].wn_rec_height
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

		   ; initialize wn_max_row, wn_min_row, wn_max_row, wn_min_col
                   ; wn_max_height, wn_max_length, wn_height, wn_length
                   ; row, col

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

                   ; video attribute is lightgray on black, update cursor

                   mov    video_attr, LIGHTGRAY
                   or     flag_1, 1

                   pop    ds
                   pop    ax
                   ret
crt_init           endp

crt_module_code    ends
                   end


