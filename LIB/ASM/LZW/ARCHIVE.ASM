; File          : ARCHIVE.ASM
; Description   : File archival methods and supporting routines
; Last Modified : 01/30/90 DWP Clean-up

                   .model large
                   .code

		   include  ..\misc\bios.inc
		   include  ..\misc\dos.inc

MODEL_ADJUSTMENT   equ    2

                   public    lzw_compress
                   public    lzw_expand

MAX_CODE_LENGTH    equ    12
TABLE_SIZE         equ    5021         ;prime number > 2^MAX_CODE_LENGTH

ERROR_LZW_COMPRESS_MEMORY_ALLOCATION equ 100
ERROR_LZW_EXPAND_MEMORY_ALLOCATION   equ 100
ERROR_LZW_EXPAND_STACK_OVERFLOW      equ 101

; Function    : LZW_COMPRESS
; Description : Compresses a contiguous block of memory  using the
;               Lempel-Ziv-Welch data compression algorithm discussed in
;               Dr. Dobbs Journal, October, 1989, starting on page 29.  There
;               are 3 different code lengths used in the compression, 9, 10,
;               and 12.  This algorithm tries each of the code lengths,
;               the code length with the best compression results is the one
;               actually used.
; Expects     : SOURCE = Far address of buffer for input data.
;                        byte 0  = Size of SOURCE, low byte.
;                        byte 1  = Size of SOURCE, high byte.
;                        byte 2+ = Actual data buffer.
;               DEST   = Far address of buffer for output data.
;                        byte 0  = Size of DEST, low byte (undefined).
;                        byte 1  = Size of DEST, hight byte (undefined).
;                        byte 2  = Compression code used (undefined).
;                        byte 3+ = Actual data buffer (undefined).
; Returns     : DEST byte 0  = Size of DEST, low byte.
;                    byte 1  = Size of DEST, high byte.
;                    byte 2  = Compression code used, now defined [0 | 1 | 2 | 4].
;                    byte 3+ = Image of SOURCE compressed using code type DEST.byte 2
;                              with length (DEST.byte 1)*256 + DEST.byte 2.
;               AX           = Error Code (0 = no errors).
; Modified    : 12/21/89 DWP Initial coding.
;               01/25/90 DWP Completed recoding for use with buffers, no I/O required.
;               01/26/90 DWP Fixed several bugs found during testing.
; Notes       : 1) Uses PASCAL calling conventions.
;               2) Requires that 25106 bytes be available from DOS.
;               3) Dest should be the same size as source.

; Parameter Definitions:
;-----------------------
SOURCE_SEG         equ    <[bp+10+MODEL_ADJUSTMENT]>
SOURCE_OFS         equ    <[bp+8+MODEL_ADJUSTMENT]>
DEST_SEG           equ    <[bp+6+MODEL_ADJUSTMENT]>
DEST_OFS           equ    <[bp+4+MODEL_ADJUSTMENT]>

PARAMETER_ADJUSTMENT =    8

; Local Variable Definitions:
;----------------------------
HASH_VAR           equ    <[bp-2]>               ;hashing function variable
SOURCE_BUFR_END    equ    <[bp-4]>               ;end of buffer ofs for SOURCE
CODE_LENGTH        equ    <[bp-6]>               ;length of CURRENT_CODE
CODE_VAR           equ    <[bp-8]>               ;# of bits to shift output code
CODE_ARRAY_SEG     equ    <[bp-10]>              ;segment of CODE_ARRAY
BEST_SIZE          equ    <[bp-12]>              ;best compression size
BEST_SIZE_CODE     equ    <[bp-14]>              ;code associated w/ above
CURRENT_CODE       equ    <[bp-16]>              ;current code
MAX_CODE_VALUE     equ    <[bp-18]>              ;max value for CURRENT_CODE wrt CODE_LENGTH
TERMINATE_FLAG     equ    <[bp-20]>
FINAL_PASS_FLAG    equ    <[bp-22]>

CODE_ARRAY_SIZE    =      TABLE_SIZE*(2+2+1)+1   ;TABLE_SIZE*(sizeof(int+int+char))
STRING_OFFSET      =      2
CHARACTER_OFFSET   =      4
LOCALS_ADJUSTMENT  =      22

lzw_compress       proc

                   push   bp
                   mov    bp, sp
                   sub    sp, LOCALS_ADJUSTMENT
                   push   bx
                   push   cx
                   push   dx
                   push   si
                   push   di
                   push   ds
                   push   es

                   mov    ah, _ALLOCATE_MEM      ;allocate mem for CODE_ARRAY
                   mov    bx, (CODE_ARRAY_SIZE / 16) + 1
                   int    _DOS_SERVICES
                   jc     lzw_compress_001
                   mov    CODE_ARRAY_SEG, ax
                   jmp    short lzw_compress_002
lzw_compress_001:
                   mov    ax, ERROR_LZW_COMPRESS_MEMORY_ALLOCATION
                   jmp    lzw_compress_021
lzw_compress_002:
                   ;start of main loop, use code 4, 2, and 1
                   mov    ds, SOURCE_SEG
                   mov    si, SOURCE_OFS
                   mov    ax, [si]
                   mov    BEST_SIZE, ax
                   mov    word ptr BEST_SIZE_CODE, 0
                   mov    word ptr FINAL_PASS_FLAG, 0

                   mov    word ptr HASH_VAR, 4   ;determine starting HASH_VAR (4, 2, or 1)
                   cmp    ax, 1023
                   jge    lzw_compress_004
                   shr    word ptr HASH_VAR, 1
                   cmp    ax, 511
                   jge    lzw_compress_004
lzw_compress_003:
                   shr    word ptr HASH_VAR, 1
lzw_compress_004:
                   jmp    short lzw_compress_009
lzw_compress_005:
                   mov    es, DEST_SEG
                   mov    di, DEST_OFS
                   mov    ax, es:[di]
                   cmp    ax, BEST_SIZE
                   jg     lzw_compress_006
                   mov    BEST_SIZE, ax
                   mov    ax, HASH_VAR
                   mov    BEST_SIZE_CODE, ax
lzw_compress_006:
                   cmp    word ptr FINAL_PASS_FLAG, 1
                   je     lzw_compress_007
                   cmp    word ptr HASH_VAR, 1
                   jg     lzw_compress_003

                   cmp    word ptr BEST_SIZE_CODE, 0
                   jg     lzw_compress_008
                   mov    ds, SOURCE_SEG
                   mov    si, SOURCE_OFS
                   mov    es, DEST_SEG
                   mov    di, DEST_OFS
                   mov    cx, [si]
                   mov    es:[di], cx
                   mov    word ptr es:[di+2], 0
                   add    si, 2
                   add    di, 3
                   cld
                   rep    movsb
lzw_compress_007:
                   jmp    lzw_compress_020
lzw_compress_008:
                   mov    ax, BEST_SIZE_CODE
                   cmp    ax, HASH_VAR
                   je     lzw_compress_007
                   mov    HASH_VAR, ax
                   mov    word ptr FINAL_PASS_FLAG, 1
lzw_compress_009:
                   ;initialize CURRENT_CODE+STRING+CHARACTER array space
                   mov    es, CODE_ARRAY_SEG
                   sub    di, di
                   sub    ax, ax
                   mov    cx, CODE_ARRAY_SIZE / 2
                   cld
                   rep    stosw

                   ;initialize SOURCE, DEST, SOURCE_BUFR_END, zero out DEST
                   mov    ds, SOURCE_SEG
                   mov    si, SOURCE_OFS
                   mov    es, DEST_SEG
                   mov    di, DEST_OFS
                   add    di, 3
                   lodsw
                   mov    cx, ax
                   mov    SOURCE_BUFR_END, ax
                   add    SOURCE_BUFR_END, si

                   sub    ax, ax                 ;zero out DEST, size=size of SOURCE
                   rep    stosb
                   mov    di, DEST_OFS
                   add    di, 3

                   ;initialize CURRENT_CODE, MAX_CODE_VALUE = (1 << CODE_LENGTH) - 2
                   mov    word ptr CURRENT_CODE, 256
                   mov    cx, HASH_VAR
                   mov    word ptr CODE_VAR, 8
                   sub    CODE_VAR, cx
                   add    cx, 8
                   mov    ax, 1
                   shl    ax, cl
                   sub    ax, 2
                   mov    MAX_CODE_VALUE, ax
                   mov    word ptr TERMINATE_FLAG, 0

                   ;STRING = get input character
                   lodsb
                   sub    dx, dx
                   mov    dl, al
lzw_compress_010:
                   ;WHILE there are still input characters DO
                   cmp    si, SOURCE_BUFR_END
                   jne    lzw_compress_011
                   jmp    lzw_compress_018
lzw_compress_011:
                   ;   CHARACTER = get input character
                   lodsb
                   mov    ds, CODE_ARRAY_SEG

                   ;   IF STRING+CHARACTER is in the string table THEN
                   sub    bx, bx                 ;hash STRING+CHARACTER
                   mov    bl, al                 ;f(h)=(CHARACTER << 4) ^ STRING_CODE
                   mov    cx, HASH_VAR           ;bx = hash code
                   shl    bx, cl
                   xor    bx, dx

                   mov    cx, 1                  ;cx = adjustment nmbr for re-hash
                   cmp    bx, 0
                   je     lzw_compress_012
                   add    cx, TABLE_SIZE-1
                   sub    cx, bx
lzw_compress_012:
                   ;bx = index into CODE+STRING+CHARACTER array (bx=bx*5)
                   push   cx                     ;save adjustment nmbr
                   mov    cx, bx
                   shl    bx, 1
                   shl    bx, 1
                   add    bx, cx

                   cmp    word ptr [bx], 0       ;CODE = 0 (new STRING+CHARACTER)
                   jne    lzw_compress_013

                   mov    cx, CURRENT_CODE
                   cmp    cx, MAX_CODE_VALUE
                   ja     lzw_compress_015 ;jge
                   inc    word ptr CURRENT_CODE
                   mov    [bx], cx
                   mov    [bx + STRING_OFFSET], dx
                   mov    [bx + CHARACTER_OFFSET], al

                   jmp    short lzw_compress_015
lzw_compress_013:
                   cmp    [bx + STRING_OFFSET], dx    ;check STRING
                   jne    lzw_compress_014
                   cmp    [bx + CHARACTER_OFFSET], al ;check CHARACTER
                   jne    lzw_compress_014

                   mov    dx, [bx]               ;STRING+CHARACTER found
                   mov    ds, SOURCE_SEG
                   add    sp, 2
                   jmp    short lzw_compress_010
lzw_compress_014:
                   mov    bx, cx                 ;re-hash function
                   pop    cx
                   sub    bx, cx
                   cmp    bx, 0
                   jge    lzw_compress_012
                   add    bx, TABLE_SIZE
                   jmp    short lzw_compress_012

lzw_compress_015:
                   mov    ds, SOURCE_SEG
                   add    sp, 2
lzw_compress_016:
                   mov    cx, CODE_VAR
                   shl    dx, cl
                   or     es:[di], dh
                   inc    di
                   or     es:[di], dl
                   cmp    cx, 0
                   jne    lzw_compress_017
                   inc    di
                   mov    word ptr CODE_VAR, 8
lzw_compress_017:
                   mov    cx, HASH_VAR
                   sub    CODE_VAR, cx
                   sub    dx, dx
                   mov    dl, al
                   jmp    lzw_compress_010

lzw_compress_018:
                   cmp    word ptr TERMINATE_FLAG, 2
                   je     lzw_compress_019
                   inc    word ptr TERMINATE_FLAG
                   cmp    word ptr TERMINATE_FLAG, 1
                   je     lzw_compress_016
                   mov    dx, MAX_CODE_VALUE
                   inc    dx
                   jmp    short lzw_compress_016
lzw_compress_019:
                   mov    cx, di
                   mov    di, DEST_OFS
                   sub    cx, di
                   sub    cx, 2
                   mov    es:[di], cx
                   mov    cx, HASH_VAR
                   mov    es:[di+2], cl
                   jmp    lzw_compress_005
lzw_compress_020:
                   mov    ah, 49h
                   mov    es, CODE_ARRAY_SEG
                   int    _DOS_SERVICES
                   sub    ax, ax
                   jnc    lzw_compress_021
                   mov    ax, ERROR_LZW_COMPRESS_MEMORY_ALLOCATION
lzw_compress_021:
                   pop    es
                   pop    ds
                   pop    di
                   pop    si
                   pop    dx
                   pop    cx
                   pop    bx
                   mov    sp, bp
                   pop    bp
                   ret    PARAMETER_ADJUSTMENT
lzw_compress       endp

; Procedure   : LZW_EXPAND
; Description : Expands a contiguous block of memory previously compressed
;               with LZW_COMPRESS.
; Expects     : SOURCE = far address of buffer for input data.
;                        byte 0  = Size of SOURCE, low byte.
;                        byte 1  = Size of SOURCE, high byte.
;                        byte 2  = Compression code length (assigned
;                                  in LZW_COMPRESS [0 | 1 | 2 | 4].
;                        byte 3+ = Actual data buffer.
;               DEST   = Far address of buffer for output data.
;                        byte 0  = Size of DEST, low byte (undefined).
;                        byte 1  = Size of DEST, high byte (undefined).
;                        byte 2+ = Actual data buffer (undefined).
; Returns     : DEST byte 0  = Size of DEST, low byte.
;                    byte 1  = Size of DEST, high byte.
;                    byte 2+ = Uncompressed image of SOURCE with length
;                              (DEST.byte 1)*256 + DEST.byte 0.
;               AX = Error Code (0=successful, no errors).
; Modified    : 12/21/89 DWP Initial coding completed.
;               01/25/90 DWP Completed update for use with memory buffers.
;               01/26/90 DWP Fixed several bugs found during testing.
; Notes       : 1) Uses PASCAL calling conventions.
;               2) Requires that 29,202 bytes be available from DOS.
;               3) DEST should be the same size as SOURCE.

; Parameter Definitions:
;-----------------------
SOURCE_SEG     equ    <[bp+10+MODEL_ADJUSTMENT]>
SOURCE_OFS     equ    <[bp+8+MODEL_ADJUSTMENT]>
DEST_SEG       equ    <[bp+6+MODEL_ADJUSTMENT]>
DEST_OFS       equ    <[bp+4+MODEL_ADJUSTMENT]>

PARAMETERS_ADJUSTMENT =   8

;Local Variable Definitions:
;----------------------------
HASH_VAR           equ    <[bp-2]>
CODE_VAR           equ    <[bp-4]>
STRING_SEG         equ    <[bp-6]>
CODE_ARRAY_SEG     equ    <[bp-8]>
DEST_SIZE          equ    <[bp-10]>
CURRENT_CODE       equ    <[bp-12]>
MAX_CODE_VALUE     equ    <[bp-14]>
CHARACTER          equ    <[bp-16]>
TEMP               equ    <[bp-18]>
TEMP1              equ    <[bp-20]>
TEMP2              equ    <[bp-22]>

STRING_SIZE        =      4096
CODE_ARRAY_SIZE    =      TABLE_SIZE*(2+2+1)+1
STRING_OFFSET      =      2
CHARACTER_OFFSET   =      4

LOCALS_ADJUSTMENT  =      22

lzw_expand         proc

                   push   bp
                   mov    bp, sp
                   sub    sp, LOCALS_ADJUSTMENT
                   push   bx
                   push   cx
                   push   dx
                   push   si
                   push   di
                   push   ds
                   push   es

                   mov    ah, _ALLOCATE_MEM      ;allocate mem for CODE_ARRAY
                   mov    bx, (CODE_ARRAY_SIZE / 16) + 1
                   int    _DOS_SERVICES
                   jc     lzw_expand_001
                   mov    CODE_ARRAY_SEG, ax

                   mov    ah, _ALLOCATE_MEM      ;allocate mem for STRING_ARRAY
                   mov    bx, (STRING_SIZE / 16)
                   int    _DOS_SERVICES
                   jc     lzw_expand_001
                   mov    STRING_SEG, ax

                   jmp    short lzw_expand_002
lzw_expand_001:
                   mov    ax, ERROR_LZW_EXPAND_MEMORY_ALLOCATION
                   jmp    short lzw_expand_003
lzw_expand_002:
                   ;initialize CURRENT_CODE+STRING+CHARACTER array space
                   mov    es, CODE_ARRAY_SEG
                   sub    di, di
                   sub    ax, ax
                   mov    cx, CODE_ARRAY_SIZE / 2
                   cld
                   rep    stosw

                   ;init SOURCE, DEST, DEST_SIZE,  zero out DEST
                   mov    ds, SOURCE_SEG
                   mov    si, SOURCE_OFS
                   mov    es, DEST_SEG
                   mov    di, DEST_OFS
                   lodsw
                   mov    cx, ax
                   add    di, 2
                   mov    word ptr DEST_SIZE, 0

                   sub    ax, ax                ;zero out DEST, size=size of SOURCE
                   rep    stosb
                   mov    di, DEST_OFS
                   add    di, 2

                   ;initialize CURRENT_CODE, HASH_VAR, CODE_VAR, MAX_CODE_VALUE
                   mov    word ptr CURRENT_CODE, 256
                   lodsb
                   sub    ah, ah
                   mov    HASH_VAR, ax
                   mov    cx, ax
                   mov    word ptr CODE_VAR, 8
                   sub    CODE_VAR, cx
                   add    cx, 8
                   mov    ax, 1
                   shl    ax, cl
                   dec    ax
                   mov    MAX_CODE_VALUE, ax

                   cmp    word ptr HASH_VAR, 0   ;move SOURCE to DEST if HASH_VAR=0
                   jne    lzw_expand_004
                   mov    si, SOURCE_OFS
                   lodsw
                   mov    cx, ax
                   mov    DEST_SIZE, ax
                   inc    si
                   rep    movsb
lzw_expand_003:
                   jmp    lzw_expand_010
lzw_expand_004:
                   mov    word ptr TEMP2, 1
                   jmp    short lzw_expand_007
lzw_expand_005:
                   mov    word ptr TEMP2, 0
                   stosb
                   inc    word ptr DEST_SIZE
                   mov    dx, ax
                   mov    CHARACTER, ax
lzw_expand_006:
                   ;WHILE there are still input characters DO
lzw_expand_007:
                   ;   Read NEW_CODE
                   mov    cx, CODE_VAR

                   lodsw
                   dec    si
                   xchg   ah, al
                   shr    ax, cl
                   and    ax, MAX_CODE_VALUE
                   cmp    ax, MAX_CODE_VALUE
                   je     lzw_expand_010
                   cmp    cx, 0
                   jg     lzw_expand_008
                   inc    si
                   mov    word ptr CODE_VAR, 8
lzw_expand_008:
                   mov    cx, HASH_VAR
                   sub    CODE_VAR, cx

                   cmp    word ptr TEMP2, 1
                   je     lzw_expand_005

                   ;   IF NEW_CODE is not in the translation table THEN
                   push   ds                     ;save SOURCE_SEG
                   mov    ds, CODE_ARRAY_SEG

                   push   es                     ;save DEST_SEG
                   push   di                     ;save DEST_OFS

                   mov    ds, CODE_ARRAY_SEG
                   mov    es, STRING_SEG         ;es:[di] => end of STRING
                   mov    di, STRING_SIZE-1
                   mov    cx, di

                   mov    bx, ax
                   cmp    ax, CURRENT_CODE
                   jl     lzw_expand_009
                   mov    bx, dx
                   mov    cx, CHARACTER
                   mov    es:[di], cl
                   dec    di
lzw_expand_009:
                   cmp    bx, 255                ;expand CODE into STRING
                   jle    lzw_expand_011
                   mov    cx, bx
                   shl    bx, 1
                   shl    bx, 1
                   add    bx, cx
                   mov    cl, [bx + CHARACTER_OFFSET]
                   mov    es:[di], cl
                   dec    di
                   mov    bx, [bx + STRING_OFFSET]
                   cmp    di, 0
                   jge    lzw_expand_009
                   add    sp, 6
                   mov    ax, ERROR_LZW_EXPAND_STACK_OVERFLOW
lzw_expand_010:
                   jmp    short lzw_expand_013
lzw_expand_011:
                   mov    es:[di], bl
                   mov    CHARACTER, bx

                   mov    cx, STRING_SIZE
                   sub    cx, di                 ;move STRING to DEST
                   add    DEST_SIZE, cx
                   mov    TEMP, di
                   mov    TEMP1, es
                   pop    di
                   pop    es
                   push   si
                   mov    si, TEMP
                   push   ds
                   mov    ds, TEMP1

                   rep    movsb
                   pop    ds
                   pop    si

                   mov    bx, CURRENT_CODE
                   cmp    bx, MAX_CODE_VALUE
                   jae    lzw_expand_012 ;jge
                   inc    word ptr CURRENT_CODE
                   mov    cx, bx
                   shl    bx, 1
                   shl    bx, 1
                   add    bx, cx
                   mov    [bx + STRING_OFFSET], dx
                   mov    cx, CHARACTER
                   mov    [bx + CHARACTER_OFFSET], cl
lzw_expand_012:
                   pop    ds
                   mov    dx, ax
                   jmp    lzw_expand_006
lzw_expand_013:
                   mov    di, DEST_OFS
                   mov    cx, DEST_SIZE
                   mov    es:[di], cx

                   sub    cx, cx

                   mov    ah, _FREE_MEM
                   mov    es, STRING_SEG
                   int    _DOS_SERVICES
                   jnc    lzw_expand_014
                   inc    cx
lzw_expand_014:
                   mov    ah, _FREE_MEM
                   mov    es, CODE_ARRAY_SEG
                   int    _DOS_SERVICES
                   jnc    lzw_expand_015
                   inc    cx
lzw_expand_015:
                   sub    ax, ax
                   cmp    cx, 0
                   je     lzw_expand_016
                   mov    ax, ERROR_LZW_EXPAND_MEMORY_ALLOCATION
lzw_expand_016:
                   pop    es
                   pop    ds
                   pop    di
                   pop    si
                   pop    dx
                   pop    cx
                   pop    bx
                   mov    sp, bp
                   pop    bp
                   ret    PARAMETER_ADJUSTMENT
lzw_expand         endp

                   end
