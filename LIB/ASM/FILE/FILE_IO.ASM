; File          : FILE_IO.ASM
; Description   : File input/output procedures.
; Last Modified : 12/19/89


; Procedure     : _READFILE
; Description   : Reads data from an open file.
; Expects       : far ptr = address of _FILE_TYPE that describes the open file
;                           to be read
; Returns       : _FILE_TYPE.msg = 0 if operation was successful
;                 _FILE_TYPE.msg = error code otherwise
; Last Modified : 12/27/89
; Notes         : None

; Parameter Definitions:
;-----------------------
FILE_SEG           equ    <[bp+6+_MODEL_ADJUSTMENT]>
FILE_OFS           equ    <[bp+4+_MODEL_ADJUSTMENT]>

_readfile          proc   

                   push   bp
                   mov    bp, sp

                   push   ax
                   push   bx
                   push   cx
                   push   dx
                   push   ds

                   mov    ds, FILE_SEG
                   mov    bx, FILE_OFS
                   mov    cx, [bx+_FILE_TYPE_BUFRSIZE]
                   mov    ds, [bx+_FILE_TYPE_BUFRSEG]
                   mov    dx, [bx+_FILE_TYPE_BUFROFS]
                   mov    bx, [bx+_FILE_TYPE_HANDLE]

                   mov    ah, _READ_HANDLE
                   int    _DOS_SERVICES

                   mov    ds, FILE_SEG
                   mov    bx, FILE_OFS

                   mov    [bx+_FILE_TYPE_COUNT], ax   ;save # of bytes read
                   mov    word ptr [bx+_FILE_TYPE_OFS], 0

                   jc     readfile_001
                   cmp    ax, 0
                   jne    readfile_000
                   mov    ax, _END_OF_FILE
                   jmp    readfile_001

readfile_000:      sub    ax, ax

readfile_001:      mov    [bx+_FILE_TYPE_MSG], ax     ;save error code

                   pop    ds
                   pop    dx
                   pop    cx
                   pop    bx
                   pop    ax
                   pop    bp
                   ret    4
_readfile          endp


; Procedure     : _WRITEFILE
; Description   : Writes data to an open file.
; Expects       : far ptr = address of _FILE_TYPE that describes open file to
;                           be written to
;                 word    = # of bytes to write
;                 far ptr = address of write buffer
; Returns       : _FILE_TYPE.msg = 0 if operation was successful
;                 _FILE_TYPE.msg = error number if otherwise
; Last Modified : 12/27/89
; Notes         : None

; Parameter Definitions:
;-----------------------
FILE_SEG           equ    <[bp+6+_MODEL_ADJUSTMENT]>
FILE_OFS           equ    <[bp+4+_MODEL_ADJUSTMENT]>

_writefile         proc   

                   push   bp
                   mov    bp, sp

                   push   ax
                   push   bx
                   push   cx
                   push   dx
                   push   ds

                   mov    ds, FILE_SEG
                   mov    bx, FILE_OFS
                   mov    cx, [bx+_FILE_TYPE_OFS]
                   mov    ds, [bx+_FILE_TYPE_BUFRSEG]
                   mov    dx, [bx+_FILE_TYPE_BUFROFS]
                   mov    bx, [bx+_FILE_TYPE_HANDLE]

                   mov    ah, _WRITE_HANDLE
                   int    _DOS_SERVICES

                   mov    ds, FILE_SEG
                   mov    bx, FILE_OFS

                   mov    [bx+_FILE_TYPE_COUNT], ax   ;save # of bytes written
                   mov    word ptr [bx+_FILE_TYPE_OFS], 0

                   jc     writefile_001
                   cmp    ax, cx
                   je     writefile_000
                   mov    ax, _DISK_FULL
                   jmp    writefile_001

writefile_000:     sub    ax, ax

writefile_001:     mov    [bx+_FILE_TYPE_MSG], ax     ;save error code

                   pop    ds
                   pop    dx
                   pop    cx
                   pop    bx
                   pop    ax
                   pop    bp
                   ret    4
_writefile         endp


; Function      : _READCHAR
; Description   : Reads a character (one byte) from a file
; Expects       : far ptr = addr of _FILE_TYPE of file to read from,
;                           all data in _FILE_TYPE should be current
; Returns       : AL = character read (if not EOF)
; Last Modified : 12/27/89
; Notes         : None

; Parameter Definitions:
;-----------------------
FILE_SEG           equ    <[bp+6+_MODEL_ADJUSTMENT]>
FILE_OFS           equ    <[bp+4+_MODEL_ADJUSTMENT]>

_readchar          proc   

                   push   bp
                   mov    bp, sp
                   push   si
                   push   ds

                   mov    ds, FILE_SEG
                   mov    si, FILE_OFS

readchar_000:      mov    ax, [si+_FILE_TYPE_OFS]
                   cmp    ax, [si+_FILE_TYPE_COUNT]
                   jl     readchar_001

                   push   ds
                   push   si
                   call   _readfile
                   sub    ax, ax

readchar_001:      inc    word ptr [si+_FILE_TYPE_OFS]
                   push   [si+_FILE_TYPE_BUFRSEG]
                   add    ax, [si+_FILE_TYPE_BUFROFS]
                   pop    ds
                   mov    si, ax
                   lodsb
                   sub    ah, ah

                   pop    ds
                   pop    si
                   pop    bp
                   ret    4
_readchar          endp


; Procedure     : _WRITECHAR
; Description   : Writes a character (one byte) to the specified output file.
; Expects       : far ptr = addr of _FILE_TYPE of output file, all data in
;                           _FILE_TYPE should be current
;                 word    = character to output (low order byte)
; Returns       : Nothing
; Last Modified : 12/27/89
; Notes         : None

; Parameter Definitions:
;-----------------------
FILE_SEG           equ    <[bp+8+_MODEL_ADJUSTMENT]>
FILE_OFS           equ    <[bp+6+_MODEL_ADJUSTMENT]>
CHARACTER          equ    <[bp+4+_MODEL_ADJUSTMENT]>

_writechar         proc   

                   push   bp
                   mov    bp, sp
                   push   ax
                   push   di
                   push   es

                   mov    es, FILE_SEG
                   mov    di, FILE_OFS
writechar_000:
                   mov    ax, es:[di+_FILE_TYPE_OFS]
                   cmp    ax, es:[di+_FILE_TYPE_BUFRSIZE]
                   jl     writechar_001

                   push   es
                   push   di
                   call   _writefile
                   sub    ax, ax
writechar_001:
                   inc    word ptr es:[di+_FILE_TYPE_OFS]
                   push   es:[di+_FILE_TYPE_BUFRSEG]
                   add    ax, es:[di+_FILE_TYPE_BUFROFS]
                   pop    es
                   mov    di, ax
                   mov    ax, CHARACTER
                   stosb

                   pop    es
                   pop    di
                   pop    ax
                   pop    bp
                   ret    6
_writechar         endp


; Procedure     : _CREATEFILE
; Description   : Creates a new file.
; Expects       : far ptr = address of _FILE_TYPE for new file
; Returns       : _FILE_TYPE.msg = 0 if operation was successful
;                 _FILE_TYPE.msg = error code otherwise
; Last Modified : 12/27/89
; Notes         : None

; Parameter Definitions:
;-----------------------
FILE_SEG           equ    <[bp+6+_MODEL_ADJUSTMENT]>
FILE_OFS           equ    <[bp+4+_MODEL_ADJUSTMENT]>

_createfile        proc   

                   push   bp
                   mov    bp, sp
                   push   ax
                   push   bx
                   push   cx
                   push   dx
                   push   ds

                   mov    ds, FILE_SEG          ;get segment of _FILE_TYPE
                   mov    dx, FILE_OFS          ;get offset of _FILE_TYPE
                   mov    bx, dx
                   mov    cl, [bx+_FILE_TYPE_ATTR]    ;get file attribute
                   sub    ch, ch

                   mov    ah, _CREATE
                   int    _DOS_SERVICES

                   jc     createfile_000
                   mov    [bx+_FILE_TYPE_HANDLE], ax
                   sub    ax, ax

createfile_000:    mov    [bx+_FILE_TYPE_MSG], ax

                   pop    ds
                   pop    dx
                   pop    cx
                   pop    bx
                   pop    ax
                   pop    bp
                   ret    4
_createfile        endp



; Procedure     : _OPENFILE
; Description   : Opens the specified file.
; Expects       : far ptr = address of file struc that describes the file
;                           to be opened.
; Returns       : _FILE_TYPE.handle = file handle of opened file if successful
;                 _FILE_TYPE.msg    = error code if otherwise
; Last Modified : 12/27/89
; Notes         : None

; Parameter Definitions:
;-----------------------
FILE_SEG           equ    <[bp+6+_MODEL_ADJUSTMENT]>
FILE_OFS           equ    <[bp+4+_MODEL_ADJUSTMENT]>

_openfile          proc   

                   push   bp
                   mov    bp,sp
                   push   ax
                   push   bx
                   push   dx
                   push   ds

                   mov    ds, FILE_SEG           ;get segment of _FILE_TYPE
                   mov    dx, FILE_OFS           ;get offset of _FILE_TYPE
                   mov    bx, dx
                   mov    ah, _OPEN
                   mov    al, [bx+_FILE_TYPE_ACCESS]  ;get access type
                   int    _DOS_SERVICES

                   jc     openfile_000
                   mov    [bx+_FILE_TYPE_HANDLE], ax  ;save file handle
                   sub    ax, ax

openfile_000:      mov    [bx+_FILE_TYPE_MSG], ax     ;save error code

                   pop    ds
                   pop    dx
                   pop    bx
                   pop    ax
                   pop    bp
                   ret    4
_openfile          endp


; Procedure     : _CLOSEFILE
; Description   : Closes an open file.
; Expects       : far ptr = address of _FILE_TYPE that describes the open file
; Returns       : _FILE_TYPE.msg = 0 if operation successful
;                 _FILE_TYPE.msg = error code otherwise
; Last Modified : 12/27/89
; Notes         : None

; Parameter Definitions:
;-----------------------
FILE_SEG        equ       <[bp+6+_MODEL_ADJUSTMENT]>
FILE_OFS        equ       <[bp+4+_MODEL_ADJUSTMENT]>

_closefile      proc

                push      bp
                mov       bp, sp

                push      ax
                push      bx
                push      ds

                mov       ds, FILE_SEG           ;get segment of _FILE_TYPE
                mov       bx, FILE_OFS           ;get offset of _FILE_TYPE

                cmp       word ptr [bx+_FILE_TYPE_OFS], 0
                je        closefile_000

                push      ds
                push      bx
                call      _writefile
closefile_000:
                mov       bx, [bx+_FILE_TYPE_HANDLE]  ;get file handle

                mov       ah, _CLOSE_HANDLE
                int       _DOS_SERVICES

                jc        closefile_001
                sub       ax, ax

closefile_001:  mov       [bx+_FILE_TYPE_MSG], ax     ;save error code

                pop       ds
                pop       bx
                pop       ax
                pop       bp
                ret       4
_closefile      endp
