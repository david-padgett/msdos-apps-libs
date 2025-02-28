; File        : STANDARD.INC
; Module      : ASM
; System      : None
; Description : A general-purpose, standard header include file.
; Modified    : 03/30/91 DWP Created.
; Notes       :

                   ifndef _STANDARD_INC

_STANDARD_INC      equ   1

; Boolean/Logical symbols.

FALSE              equ   0
TRUE               equ   1

NO                 equ   0
YES                equ   1

OFF                equ   0
ON                 equ   1

; Standard data type symbols.  The numbers following the underscore in several of these symbols indicates the bit length of the
; actual data type associated with that symbol.

_BYTE_TYPE         equ    0
_WORD_8_TYPE       equ    1
_WORD_16_TYPE      equ    2
_WORD_32_TYPE      equ    3
_BOOLEAN_TYPE      equ    4
_CHARACTER_TYPE    equ    5
_STRING_TYPE       equ    6
_INTEGER_8_TYPE    equ    7
_INTEGER_16_TYPE   equ    8
_INTEGER_32_TYPE   equ    9
_CARDINAL_8_TYPE   equ   10
_CARDINAL_16_TYPE  equ   11
_CARDINAL_32_TYPE  equ   12
_REAL_32_TYPE      equ   13
_REAL_64_TYPE      equ   14
_REAL_80_TYPE      equ   15

; The number following the underscore in several of these types indicates the bit length of that type.

_BYTE              equ   <db>
_WORD_8            equ   <db>
_WORD_16           equ   <dw>
_WORD_32           equ   <dd>
_BOOLEAN           equ   <dw>
_CHARACTER         equ   <db>
_STRING            equ   <dd>
_INTEGER_8         equ   <db>
_INTEGER_16        equ   <dw>
_INTEGER_32        equ   <dd>
_CARDINAL_8        equ   <db>
_CARDINAL_16       equ   <dw>
_CARDINAL_32       equ   <dd>
_REAL_32           equ   <dd>
_REAL_64           equ   <dq>
_REAL_80           equ   <dt>

                   endif