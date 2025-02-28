; Procedure   : word_to_ascii
; Description : Converts a word from hexadecimal to ASCII hexadecimal.
; Expects     : DEST_SEG = destination segment, ptr to a 4 byte string
;               DEST_OFS = destination offset, ptr to a 4 byte string
;               SOURCE   = the word to be converted
; Returns     : DEST     = converted SOURCE word
; Modified    : 02/15/90 DWP Switched to simplified segments
; Notes       :

; Parameter Definitions:
;-----------------------
DEST_SEG           equ    <[bp+6+MODEL_ADJUSTMENT]>
DEST_OFS           equ    <[bp+4+MODEL_ADJUSTMENT]>
SOURCE             equ    <[bp+2+MODEL_ADJUSTMENT]>

PARAMETER_ADJUSTMENT =    6

word_to_ascii      proc

                   push   bp
                   mov    bp, sp

                   push   ax
                   push   di
                   push   es

                   cld

                   mov    es, DEST_SEG
                   mov    di, DEST_OFS

                   mov    ax, SOURCE             ;ah, high nibble
                   xchg   ah, al
                   call   word_to_ascii_000
                   stosb

                   mov    ax, SOURCE             ;ah, low nibble
                   xchg   ah, al
                   call   word_to_ascii_001
                   stosb

                   mov    ax, SOURCE             ;al, high nibble
                   call   word_to_ascii_000
                   stosb

                   mov    ax, SOURCE             ;al, low nibble
                   call   word_to_ascii_001
                   stosb

                   pop    es
                   pop    di
                   pop    ax
                   mov    sp, bp
                   pop    bp

                   ret    PARAMETER_ADJUSTMENT

word_to_ascii_000:
                   shr    al, 1                  ;convert high nibble
                   shr    al, 1
                   shr    al, 1
                   shr    al, 1

word_to_ascii_001:
                   and    ax, 0fh                ;convert low nibble
                   cmp    ax, 9
                   jg     word_to_ascii_002
                   add    al, '0' - 1
                   jmp    short word_to_ascii_003
word_to_ascii_002:
                   add    al, 'A' - 10
word_to_ascii_003:
                   db     0c3h                   ;RET

word_to_ascii      endp

