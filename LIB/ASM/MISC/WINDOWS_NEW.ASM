; Windowing Routines:
;     open_window
;     close_window
;
; Windowing support subroutines:
;
;     window_init
;     window_end
;     window_calc
;     window_calc_bufr
;     window_calc_lengths

;procedure open_window
;   opens the window specified by the following 4 bytes, these are
;   top left row, top left column, bottom right row, bottom right column,
;   ie: call   open_window
;       db     10,11,20,21
;   the new window is cleared and the cursor is placed in the home position
;
;   note: when defining a window, leave 1 space on each side for the
;         border, this routine adjusts the parameters (top left row and top
;         left column are incremented, bottom right row and bottom right
;         column are decremented)
;
;         maximum number of windows allowed open at one time should be defined
;         in wnd_nmbr_max before assembly

wnd_nmbr_max       equ    10
wnd_sav_parm_nmbr  equ    5
                                                 ;single     double
                                                 ;-----------------
wnd_top_lft_crnr   equ    0c9h                   ;0dah       0c9h
wnd_top_rght_crnr  equ    0bbh                   ;0bfh       0bbh
wnd_bot_lft_crnr   equ    0c8h                   ;0c0h       0c8h
wnd_bot_rght_crnr  equ    0bch                   ;0d9h       0bch
wnd_hrz_ln         equ    0cdh                   ;0c4h       0cdh
wnd_vrt_ln         equ    0bah                   ;0b3h       0bah

wnd_x1             equ    [bp]
wnd_y1             equ    [bp+1]
wnd_x2             equ    [bp+2]
wnd_y2             equ    [bp+3]
wnd_foreground     equ    [bp+4]
wnd_background     equ    [bp+5]
wnd_ulc            equ    [bp+6]
wnd_urc            equ    [bp+7]
wnd_blc            equ    [bp+8]
wnd_brc            equ    [bp+9]
wnd_horizontal     equ    [bp+10]
wnd_vertical       equ    [bp+11]
wnd_title          equ    [bp+12]

open_window        proc   far

                   push   bp
                   mov    bp,sp
                   add    bp,6
                   sub    sp,0

                   sub    ax,ax                  ;determine size of window
                   mov    al,wnd_x2
                   sub    al,wnd_x1
                   shl    al,1
                   sub    dx,dx
                   mov    dl,wnd_y2
                   sub    dl,wnd_y1

                   mul    dl

                   add    ax,24

;                   call   far ptr getmem

getmem             proc   far


                   mov    cx,4                   ;calc. # paragraphs needed
                   div    cx
                   cmp    dx,0
                   je     open_window_001
                   inc    ax
open_window_001:   add    ax,2

                   mov    bx,ax                  ;ask dos for memory
                   mov    ah,48h
                   int    21h
                   jnc    open_window_002

                   call   print
                   db     'Open_window: memory allocation error',0,0
                   jmp    open_window_009

open_window_002:   inc    wnd_nmbr_cur           ;open a window

                   mov    bx,wnd_nmbr_cur        ;save allocated paragraph #
                   dec    bx
                   shl    bx,1
                   mov    di,offset wnd_sav_seg_bufr
                   add    di,bx
                   mov    [di],ax
                   mov    wnd_sav_seg_nmbr,ax

                   mov    di,0                   ;save current window coords
                   mov    si,offset min_row      ;cursor pos, and attribute
                   mov    es,ax
                   mov    ax,cs
                   mov    ds,ax
                   mov    cx,wnd_sav_parm_nmbr
                   cld
                   rep    movsw

                   mov    si,cs:wnd_parms_si     ;install new window coords
                   mov    ds,cs:wnd_parms_ds
                   mov    di,offset min_row
                   mov    ax,cs
                   mov    es,ax
                   mov    cx,4
                   cld
                   rep    movsb

                   call   window_calc_lengths
                   call   window_calc            ;set up regs to move a row
                   mov    si,di                  ;si=window start offset
                   mov    ax,es                  ;di=buffer start offset
                   mov    ds,ax                  ;ds=paragraph (seg) of window
                   mov    es,wnd_sav_seg_nmbr    ;es=paragraph (seg) of buffer
                   mov    di,wnd_sav_parm_nmbr*2 ;bx=# bytes in row (cx*2)
                   mov    cx,wnd_length          ;cx=# characters in row
                   mov    bx,cx
                   shl    bx,1

                   cld
open_window_003:   rep    movsw                  ;move a row
                   mov    cx,wnd_max_length
                   shl    cx,1
                   add    si,cx
                   sub    si,bx
                   mov    cx,wnd_length
                   cmp    si,dx
                   jl     open_window_003

                   mov    ax,wnd_length          ;set print border parameters
                   dec    ax
                   mov    cs:open_window_008+3,al
                   dec    ax
                   mov    cs:open_window_004+2,al
                   mov    cs:open_window_006+2,al
                   mov    ax,wnd_height
                   mov    cs:open_window_005+2,al
                   dec    ax
                   mov    cs:open_window_007+4,al
                   mov    cs:open_window_008+4,al
                   inc    max_col

                   call   print
                   db     0,22                   ;clear window
                   db     0,4,0,0                ;goto top left
                   db     wnd_top_lft_crnr
open_window_004    db     0,1,0,wnd_hrz_ln       ;draw top line
                   db     wnd_top_rght_crnr
open_window_005    db     0,4,0,0                ;goto bottom left
                   db     wnd_bot_lft_crnr
open_window_006    db     0,1,0,wnd_hrz_ln       ;draw bottom line
                   db     wnd_bot_rght_crnr
open_window_007    db     0,3,1,0,0,wnd_vrt_ln   ;draw left line
open_window_008    db     0,3,1,0,0,wnd_vrt_ln   ;draw right line
                   db     0,0

                   inc    min_row
                   inc    min_col
                   dec    max_row
                   sub    max_col,3
                   call   window_calc_lengths
                   mov    ax,0
                   mov    cur_row,al
                   mov    cur_col,al

open_window_009:   call   window_end
                   ret

open_window        endp

;procedure close_window
;   closes the most recently opened window, restores the screen
;   no parameters required

close_window       proc   far

                   cmp    wnd_nmbr_cur,1
                   jge    close_window_000
                   jmp    close_window_003

close_window_000:
                   call   window_init

                   dec    min_row
                   dec    min_col
                   inc    max_row
                   add    max_col,2
                   dec    wnd_nmbr_cur

                   call   window_calc_lengths    ;deter. length and height
                   call   window_calc_bufr       ;deter. storage area segment
                   call   window_calc            ;init. several variables
                   mov    bx,wnd_max_length
                   shl    bx,1
                   mov    cx,wnd_length
                   shl    cx,1
                   sub    bx,cx
                   shr    cx,1
                   mov    si,wnd_sav_parm_nmbr*2

                   cld                           ;restore a row
close_window_001:  rep    movsw
                   add    di,bx
                   mov    cx,wnd_length
                   cmp    di,dx
                   jl     close_window_001

                   mov    ax,cs                  ;restore prev. wnd coords
                   mov    es,ax
                   mov    si,0
                   mov    di,offset min_row
                   mov    cx,wnd_sav_parm_nmbr
                   cld
                   rep    movsw

                   call   window_calc_lengths
                   call   window_calc_bufr
                   mov    ax,ds
                   mov    es,ax
                   mov    ah,49h
                   int    21h
                   jnc    close_window_002

                   call   print
                   db     'Close_window: Error in memory deallocation.',0,0

close_window_002:  call   window_end
close_window_003:  ret

close_window       endp

;procedure window_init
;   saves all used registers, initializes wnd_length

window_ax          dw     0
window_bx          dw     0
window_cx          dw     0
window_dx          dw     0
window_si          dw     0
window_di          dw     0
window_ds          dw     0
window_es          dw     0

window_init        proc   near

                   mov    cs:window_ax,ax        ;save all used regs.
                   mov    cs:window_bx,bx
                   mov    cs:window_cx,cx
                   mov    cs:window_dx,dx
                   mov    cs:window_si,si
                   mov    cs:window_di,di
                   mov    cs:window_ds,ds
                   mov    cs:window_es,es

                   ret

window_init        endp

;procedure window_end
;   restores all used registers

window_end         proc   near

                   mov    ax,cs:window_ax        ;restore all used regs.
                   mov    bx,cs:window_bx
                   mov    cx,cs:window_cx
                   mov    dx,cs:window_dx
                   mov    si,cs:window_si
                   mov    di,cs:window_di
                   mov    ds,cs:window_ds
                   mov    es,cs:window_es

                   ret

window_end         endp

; procedure window_calc
;    calculates the top left and bottom right offsets for the window
;    specified by min_row,max_row,min_col,max_col
;    returns:
;       di=offset for top left of window,start
;       dx=offset for bottom right of window,end
;       es=paragraph number for text page, as defined by video_segment

window_calc_ax     dw     0

window_calc        proc   near

                   mov    es,[video_segment]
                   mov    cs:window_calc_ax,ax
                   mov    ah,min_col
                   mov    al,min_row
                   call   calc_addr
                   mov    dx,di
                   mov    ah,max_col
                   mov    al,max_row
                   call   calc_addr
                   xchg   dx,di
                   mov    ax,cs:window_calc_ax
                   ret

window_calc        endp

;procedure window_calc_bufr
;   determines where current storage word is in wnd_sav_seg_bufr
;   returns:  si=offset in wnd_sav_seg_bufr

window_calc_bufr   proc   near

                   mov    bx,wnd_nmbr_cur
                   shl    bx,1
                   mov    si,offset wnd_sav_seg_bufr
                   add    si,bx
                   mov    ds,[si]

                   ret

window_calc_bufr   endp

;procedure window_calc_lengths
;   calculates the length and height of the current window
;   returns:  wnd_length and wnd_height are correct

window_calc_lengths proc  near

                   mov    ax,0

                   mov    al,max_col             ;calc. window length
                   sub    al,min_col
                   mov    wnd_length,ax

                   mov    al,max_row             ;calc. window height
                   sub    al,min_row
                   mov    wnd_height,ax

                   ret

window_calc_lengths endp
