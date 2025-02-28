; File        : CRT.DEF
; Description : The definition file for CRT.ASM.
; Modified    : 05/23/90 DWP Created.

_MODEL_SIZE        equ    <far>
_MODEL_ADJUSTMENT  equ    4

; text colors (CGA, EGA, VGA)

BLACK              equ    0
BLUE               equ    1
GREEN              equ    2
CYAN               equ    3
RED                equ    4
MAGENTA            equ    5
BROWN              equ    6
LIGHTGRAY          equ    7
DARKGRAY           equ    8
LIGHTBLUE          equ    9
LIGHTGREEN         equ    10
LIGHTCYAN          equ    11
LIGHTRED           equ    12
LIGHTMAGENTA       equ    13
YELLOW             equ    14
WHITE              equ    15

                   ; definitions for crt_scroll

SCROLL_UP          equ    0
SCROLL_DOWN        equ    1
SCROLL_LEFT        equ    2
SCROLL_RIGHT       equ    3

                   ; definitions for the windowing procedures

WN_NOPOPUP         equ    0
WN_POPUP           equ    1

WN_NOSHADOW        equ    0
WN_SHADOW          equ    1

; Border definitions - Border definitions consist of 6 characters and are
;                       defined as follows:  top left corner, top line, top
;                       right corner, left line, right line, bottom left
;                       corner, bottom line, bottom right corner.  The border
;                       definition string does not need to be \0 terminated

WN_BDR_SINGLE      equ    <"ÚÄ¿³ ³ÀÄÙ"> ; Single line border
WN_BDR_DOUBLE      equ    <"ÉÍ»º ºÈÍ¼"> ; Double line border
WN_BDR_DRSC        equ    <"ÕÍ¸³ ³ÔÍ¾"> ; Double row, single column
WN_BDR_SRDC        equ    <"ÖÄ·º ºÓÄ½"> ; Single row, double column
WN_BDR_DTOP        equ    <"ÕÍ¸³ ³ÀÄÙ"> ; Double top row, rest is single
WN_BDR_DBOT        equ    <"ÚÄ¿³ ³ÔÍ¾"> ; Double bottom row, rest is single
WN_BDR_DLEFT       equ    <"ÖÄ¿º ³ÓÄÙ"> ; Double left column, rest is single
WN_BDR_DRIGHT      equ    <"ÚÄ·³ ºÀÄ½"> ; Double right column, rest is single
WN_BDR_STOP        equ    <"ÖÄ·º ºÈÍ¼"> ; Single top row, rest is double
WN_BDR_SBOT        equ    <"ÉÍ»º ºÓÄ½"> ; Single bottom row, rest is double
WN_BDR_SLEFT       equ    <"ÕÍ»³ ºÔÍ¼"> ; Single left column, rest is double
WN_BDR_SRIGHT      equ    <"ÉÍ¸º ³ÈÍ¾"> ; Single right column, rest is double

                   ; definition for WINDOW

WINDOW             struc
wn_rec_row         db     0            ; top left row coord. of window
wn_rec_col         db     0            ; top left col coord. of window
wn_rec_length      db     0            ; length of window
wn_rec_height      db     0            ; width of window
wn_rec_attr        dw     0            ; foreground/background color of window
wn_rec_border      dd     0            ; border characters, NULL = no border
wn_rec_border_attr dw     0            ; border attribute, not used if border = NULL
wn_rec_type        db     0            ; type of window
wn_rec_background  db     0            ; type of background
wn_rec_bufr        dd     0            ; save buffer
WINDOW             ends

                   ifndef CRT_MODULE

extrn  crt_print_char:_MODEL_SIZE
extrn  crt_print_str:_MODEL_SIZE
extrn  crt_scroll:_MODEL_SIZE
extrn  crt_clrscr:_MODEL_SIZE
extrn  crt_wherex:_MODEL_SIZE
extrn  crt_wherey:_MODEL_SIZE
extrn  crt_gotoxy:_MODEL_SIZE
extrn  crt_init:_MODEL_SIZE

                   endif
