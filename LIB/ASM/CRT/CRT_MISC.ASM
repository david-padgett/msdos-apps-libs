; File        : CRT_MISC.ASM
; Module      : CRT
; System      : None
; Description : Miscellaneous crt routines.
; Modified    : 06/13/90 DWP Created.

_MODEL_ADJUSTMENT  equ    4
_MODEL_SIZE        equ    <far>

                   include \lib\asm\bios.inc
                   include \lib\asm\dos.inc

                   public crt_modify_attr

crt_misc_segment   segment byte public 'CODE'
                   assume cs:crt_misc_segment

; Function    : crt_calculate_offset
; Description : Calculates the address for the screen position specified.
; Expects     : al = The row in question.
;               ah = The column in question.
; Returns     : ax = The offset from start of current video page of the
;                    specified coordinates.
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

; Procedure   : crt_modify_attr
; Description : Alters the attribute of the specified window.
; Expects     : row   = The starting row of the window.
;               col   = The starting column of the window.
;               x_len = The length of the window.
;               y_len = The height of window.
;               attr  = The new attribute.
; Returns     : Nothing.
; Modified    : 06/13/90 DWP Initial coding.
; Notes       :

;Parameter Definitions;
;----------------------
ROW                equ    <[bp+10+_MODEL_ADJUSTMENT]>
COL                equ    <[bp+8+_MODEL_ADJUSTMENT]>
X_LEN              equ    <[bp+6+_MODEL_ADJUSTMENT]>
Y_LEN              equ    <[bp+4+_MODEL_ADJUSTMENT]>
ATTR               equ    <[bp+2+_MODEL_ADJUSTMENT]>

PARAMETER_ADJUSTMENT =    10

crt_modify_attr    proc   far

                   push   bp
                   mov    bp, sp
                   push   ax
                   push   bx
                   push   cx
                   push   dx
                   push   di
                   push   es

                   ; Get current mode and page.

                   mov    ah, 0fh
                   int    _VIDEO_IO

                   ; If al (mode) = 2, then video segment = B000.

                   cmp    al, 2
                   je     crt_modify_attr_000
                   cmp    al, 7
                   jne    crt_modify_attr_001

crt_modify_attr_000:

                   mov    ax, 0b000h
                   mov    es, ax
                   jmp    short crt_modify_attr_003

crt_modify_attr_001:

                   ; video segment = B800 + (100 * page number)

                   mov    ax, 0b800h
                   mov    es, ax

crt_modify_attr_002:

                   cmp    bh, 0
                   je     crt_modify_attr_003

                   mov    ax, es
                   add    ax, 100h
                   mov    es, ax
                   dec    bh
                   jmp    short crt_modify_attr_002

crt_modify_attr_003:

                   ; al = row, ah = col

                   mov    ax, ROW
                   mov    bx, COL
                   mov    ah, bl

                   ; di = start addr of specified window

                   call   crt_calculate_offset
                   mov    di, ax
                   inc    di

                   ; bx = (wn_max_len - x_len) * 2

                   mov    bx, 80
                   sub    bx, X_LEN
                   shl    bx, 1

                   ; dx = y_len

                   mov    dx, Y_LEN

                   ; al = attr

                   mov    ax, ATTR

crt_modify_attr_004:

                   ; Loop until all of the rows have been modified.

                   cmp    dx, 0
                   je     crt_modify_attr_006

                   ; modify one row

                   mov    cx, X_LEN

crt_modify_attr_005:

                   mov    es:[di], al
                   inc    di
                   inc    di
                   loopnz crt_modify_attr_005

                   add    di, bx
                   dec    dx
                   jmp    short crt_modify_attr_004

crt_modify_attr_006:

                   pop    es
                   pop    di
                   pop    dx
                   pop    cx
                   pop    bx
                   pop    ax
                   mov    sp, bp
                   pop    bp
                   ret    PARAMETER_ADJUSTMENT
crt_modify_attr    endp

crt_misc_segment   ends
                   end
