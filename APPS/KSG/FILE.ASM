; File        : FILE.ASM
; Module      : FILE
; System      : None
; Description :
; Modified    : 06/24/91 DWP Created.
; Notes       :

                   public FILE_Open, FILE_Close, FILE_Read, FILE_Write, FILE_Seek

FILE_code_segment  segment byte public 'CODE'
                   assume cs:FILE_code_segment

; Function    : FILE_Open
; Description : Opens the specified file.
; Expects     : AX = Access code, either
;                    0 - Read mode
;                    1 - Write mode
;                    2 - Read/Write mode.
;               ES = The segment of the buffer that contains the name of the file to open.
;               DI = The offset of the buffer that contains the name of the file to open.
; Returns     : The value of the DOS error that occurred if the carry flag is set, otherwise, the file handle of the file
;               that has been opened.
; Modified    : 06/21/91 DWP Initial coding.
; Notes       :

FILE_Open          proc   MODEL_SIZE

                   ; Save the contents of the DX and DS registers.

                   push   dx
                   push   ds

                   ; Set up the parameters to INT 21/3d.

                   mov    dx, es
                   mov    ds, dx
                   mov    dx, di

                   ; Attempt to open the specified file.

                   mov    ah, 3dh
                   int    21h

                   ; Restore the DX and DS registers to their previous state and exit.

                   pop    ds
                   pop    dx
                   ret

FILE_Open          endp

; Function    : FILE_Close
; Description : Closes the specified file.
; Expects     : AX = The file handle of the file that is to be closed.
; Returns     : The value of the DOS error that occurred if the carry flag is set.
; Modified    : 06/21/91 DWP Initial coding.
; Notes       :

FILE_Close         proc   MODEL_SIZE

                   ; Save the contents of the BX register.

                   push   bx

		   ; Set up the parameters to INT 21/3e.

                   mov    bx, ax

                   ; Attempt to close the specified file.

                   mov    ah, 3eh
                   int    21h

                   ; Restore the BX register to its previous state and exit.

                   pop    bx
                   ret

FILE_Close         endp

; Function    : FILE_Read
; Description : Reads data from the specified file.
; Expects     : AX = The file handle of the file that is to be read.
;               CX = The number of bytes to read.
;               ES = The segment of the input buffer.
;               DI = The offset of the input buffer.
; Returns     : The value of the DOS error that occurred if the carry flag is set, otherwise, the number of bytes actually read.
; Modified    : 06/21/91 DWP Initial coding.
; Notes       :

FILE_Read          proc   MODEL_SIZE

                   ; Save the contents of the BX, DX, and DS registers.

                   push   bx
                   push   dx
                   push   ds

		   ; Set up the parameters to INT 21/3f.

                   mov    bx, ax
                   mov    dx, di
                   mov    ax, es
                   mov    ds, ax

                   ; Attempt to read data from the specified file.

                   mov    ah, 3fh
                   int    21h

                   ; Restore the DS, DX, and BX registers to their previous state and exit.

                   pop    ds
                   pop    dx
                   pop    bx
                   ret

FILE_Read          endp

; Function    : FILE_Write
; Description : Writes data to the specified file.
; Expects     : AX = The file handle of the file to write to.
;               CX = The number of bytes to write to the file.
;               ES = The segment of the output buffer.
;               DI = The offset of the output buffer.
; Returns     : The value of the DOS error that occurred if the carry flag is set, otherwise, the total number of bytes written
;               to the file.
; Modified    : 06/21/91 DWP Initial coding.
; Notes       :

FILE_Write         proc   MODEL_SIZE

                   ; Save the contents of the BX, DX, and DS registers.

                   push   bx
                   push   dx
                   push   ds

                   ; Set up the parameters for INT 21/40.

                   mov    bx, ax
                   mov    ax, es
                   mov    ds, ax
                   mov    dx, di

                   ; Attempt to write data to the specified file.

                   mov    ah, 40h
                   int    21h

                   ; Restore the BX, DX, and DS registers to their previous state and exit.

                   pop    ds
                   pop    dx
                   pop    bx
                   ret

FILE_Write         endp

; Function    : FILE_Seek
; Description : Modifies the position of the file pointer of the specified file.
; Expects     : AX = The file handle of the file whose file pointer is to be altered.
;               BX = Starting point of seek, either
;                    0 - Seek from the beginning of the file
;                    1 - Seek from the current position in the file
;                    2 - Seek from the end of the file.
;               CX = The high 16 bits of the new file position.
;               DX = The low 16 bits of the new file position.
; Returns     : The value of the DOS error that occurred if the carry flag is set, otherwise, DX:AX contains the new value of the
;               file pointer.
; Modified    : 06/21/91 DWP Initial coding.
; Notes       :

FILE_Seek          proc   MODEL_SIZE

                   ; Setup the parameters to INT 21/42.

                   xchg   ax, bx

                   ; Attempt to re-position the file pointer of the specified file.

                   mov    ah, 42h
                   int    21h

                   ret

FILE_Seek          endp

FILE_code_segment  ends
                   end
