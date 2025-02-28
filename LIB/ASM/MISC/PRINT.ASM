; File        : PRINT.ASM
; Description : Contains various procedures for printing text to the
;               screen.
; Modified    : 05/22/90 DWP Modified.

; Procedure   : print
; Description : This is a mini-interpreter that allows text to be printed
;               to the screen using a combination of text characters and
;               codes.
; Expects     : SOURCE_SEG = source segment of string to print
;               SOURCE_OFS = source offset of string to print
; Returns     : Nothing.
; Modified    : 05/22/90 Added parameters.
; Notes       : 1) All codes are bytes (characters) in the range [0..255]
;               2) The following is a list of the codes and their functions.
;                  Each of these codes is preceded by 0h.
;
;    #/Code     Description                 Parameters
;-----------------------------------------------------------------------------
;    (000xxxxx) miscellaneous control routines
;
;    0/00h      terminate print routine
;    1/01h      toggle screen formatting
;    2/02h      set active text page        mode, page
;    3/03h      set screen display mode     mode
;    4/04h      turn cursor on
;    5/05h      turn cursor off
;    6/06h      set cursor blink            blink_rate [0..2]
;    7/07h      set cursor attribute        cursor_attr
;    8/08h      set cursor update           flag [0..1]
;
;    (001xxxxx) formatted print routines
;
;    0/20h - set character attribute        foreground, background
;    1/21h - position cursor                x, y
;    2/22h - repeat character horizontal    count, char
;    3/23h - rep char. horiz. w/ gotoxy     x, y, count, char
;    4/24h - rep char. vert. w/ gotoxy      x, y,  count, char
;    5/25h - center text string             string
;    6/26h - left justify text              string
;    7/27h - right justify text             string
;
;    (010xxxxx) windowing routines
;
;    0/40h - set coordinates                tl_row, tl_col, br_row, br_col
;    1/41h - set max height,length,area - wnd_max_height,wnd_max_length
;    2/42h - clear current window - no parameters
;    3/43h - clear entire 80 col screen - no parameters

print              proc   far

                   mov    cs:print_si,si
                   mov    cs:print_ds,ds

                   pop    si
                   pop    ds

print_000:         push   ax
                   push   bx
                   push   cx

print_001:         cld
                   lodsb
                   cmp    al,0
                   je     print_002
                   call   far ptr display_char
                   jmp    short print_001

; print programming start

print_002:         lodsb                         ;load appropriate category
                   sub    bx,bx
                   mov    bl,al
                   and    ax,1fh
                   mov    cl,5
                   shr    bl,cl
                   cmp    bx,cs:print_group_tbl
                   jg     print_001
                   inc    bx
                   shl    bx,1
                   mov    bx,cs:print_group_tbl[bx]

                   cmp    ax,cs:[bx]
                   jg     print_001
                   inc    ax
                   shl    ax,1
                   add    bx,ax
                   mov    bx,cs:[bx]

                   test   sys_flag_1,2
                   je     print_003
                   cmp    bx,offset print_110
                   je     print_003

                   sub    bx,2
                   mov    ax,cs:[bx]
                   add    si,ax
                   jmp    print_001

print_003:         jmp    bx

print_group_tbl    dw     2,print_group_1,print_group_2,print_group_3
print_group_1      dw     8,print_100,print_110,print_120,print_130,print_140,print_150,print_160,print_170,print_180
print_group_2      dw     5,print_200,print_210,print_220,print_230,print_240,print_250
print_group_3      dw     4,print_300,print_310,print_320,print_330,print_340

; print/bios control routines

; exit print routine
print_100np        dw     0
print_100:         pop    cx
                   pop    bx
                   pop    ax
                   test   sys_flag_1,1
                   jne    print_101              ;on, then called from prnstr
                   push   ds
                   push   si
                   mov    ds,cs:print_ds
                   mov    si,cs:print_si
print_101:         and    sys_flag_1,0fffeh
                   ret

; toggle print formatting
print_110np        dw     0
print_110:         test   sys_flag_1,2           ;on, then ignore formatting
                   je     print_111
                   and    sys_flag_1,0fffdh
                   jmp    print_001
print_111:         or     sys_flag_1,2
                   jmp    print_001

; set active text page - new video mode, new text page
print_120np        dw     2
print_120:         lodsw
                   call   far ptr set_text
                   jmp    print_001

; set screen mode - mode
print_130np        dw     1
print_130:         lodsb
                   mov    ah,0
                   int    10h
                   jmp    print_001

; turn cursor on - no parameters
print_140np        dw     0
print_140:         call   far ptr cursor_on
                   jmp    print_001

; turn cursor off - no parameters
print_150np        dw     0
print_150:         call   far ptr cursor_off
                   jmp    print_001

; set cursor blink rate - 0 = normal, 1 = invisible, 2 = slow, 3 = fast
print_160np        dw     1
print_160:         lodsb
                   sub    ah,ah
                   call   far ptr set_cursor_blink
                   jmp    print_001

; set cursor attribute - end line, start line
print_170np        dw     2
print_170:         lodsw
                   call   far ptr set_cursor_att
                   jmp    print_001

; set cursor update - 0 = no update, 1 = update
print_180np        dw     1
print_180:         lodsb
                   sub    ah,ah
                   call   far ptr set_cursor_update
                   jmp    print_001

; formatted print routines

; set video attribute
print_200np        dw     2
print_200:         lodsw
                   and    ax,070fh
                   mov    video_foreground,al
                   mov    video_background,ah
                   mov    cl,4
                   shl    ah,cl
                   or     al,ah
                   mov    video_att,al
                   jmp    print_001

; gotoxy - row,col
print_210np        dw     2
print_210:         lodsw
                   mov    cur_row,al
                   mov    cur_col,ah
                   jmp    print_001

; repeat character horizontal - # reps, char.
print_220np:       dw     2
print_220:         lodsw
                   sub    cx,cx
                   xchg   ah,al
                   mov    cl,ah
print_221:         call   display_char
                   loop   print_221
                   jmp    print_001

; repeat char horz. w/col,row - row,col,# reps,char
print_230np        dw     4
print_230:         lodsw
                   mov    cur_row,al
                   mov    cur_col,ah
                   jmp    short print_220

; repeat char vertical - row,col,# reps, char
print_240np        dw     4
print_240:         lodsw
                   mov    cur_row,al
                   mov    cur_col,ah
                   sub    cx,cx
                   lodsw
                   xchg   ah,al
                   mov    cl,ah
print_241:         call   display_char
                   inc    cur_row
                   dec    cur_col
                   loop   print_241
                   jmp    print_001

; center ASCIIZ string that follows
print_250np        dw     0
print_250:         call   far ptr strlen
                   cmp    ax,wnd_length
                   jg     print_251
                   sub    ax,wnd_length
                   neg    ax
                   shr    ax,1
                   add    al,min_col
                   mov    cur_col,al
print_251:         jmp    print_001

; windowing routines

; define window coordinates
print_300np        dw     4
print_300:         sub    bx,bx
                   mov    cur_row,bl
                   mov    cur_col,bl
                   lodsw
                   mov    min_row,al
                   mov    min_col,ah
                   lodsw
                   mov    max_row,al
                   mov    max_col,ah
                   call   window_calc_lengths
                   jmp    print_001

; define max window coordinates
print_310np        dw     2
print_310:         sub    ax,ax
                   lodsb
                   mov    wnd_max_height,ax
                   mov    bx,ax
                   lodsb
                   mov    wnd_max_length,ax
                   mul    bl
                   mov    wnd_max_area,ax
                   jmp    print_001

; clear current window
print_320np        dw     0
print_320:         call   far ptr clear_window
                   jmp    print_001

; clear screen/clear entire window - no parameters
print_330np        dw     0
print_330:         call   far ptr home
                   jmp    print_001

print_340np        dw     0
print_340:
                   jmp    print_001

print_si           dw     0
print_ds           dw     0

print              endp

; procedure write_str
;    similar to write but has ds:si pointing to the ASCIIZ string upon
;    entry

write_str          proc   far

                   or     sys_flag_1,1
                   jmp    short write_000

write_str          endp

; procedure write
;    prints an ASCIIZ text string, similar to print without control bytes
;    expects:  segment/offset on stack when entering,
;              ie:  call    write
;                   db      'this is a test',0
;    returns:  stack return location updated to skip the text string

write              proc   far

                   mov    cs:print_si,si
                   mov    cs:print_ds,ds
                   pop    si
                   pop    ds

write_000:         push   ax

write_001:         cld
                   lodsb
                   cmp    al,0
                   je     write_002
                   call   far ptr display_char
                   jmp    short write_001

write_002:         test   sys_flag_1,1
                   je     write_003
                   and    sys_flag_1,0fffeh
                   pop    ax
                   jmp    short write_004

write_003:         pop    ax
                   push   ds
                   push   si
                   mov    ds,cs:write_ds
                   mov    si,cs:write_si

write_004:         ret

write_ds           dw     0
write_si           dw     0

write              endp
