; File        : CONVERT.ASM
; Module      : CONVERT
; System      : None
; Description :
; Modified    : 06/24/91 DWP Created.
; Notes       :

                   public CONVERT_BinToHex

CONVERT_code_segment segment byte public 'CODE'
                   assume cs:CONVERT_code_segment

; Procedure   : CONVERT_BinToHex
; Description : Converts the specified hexadecimal word to its textual equivalent.
; Expects     : AX = The binary number that is to be converted to its ASCII hexadecimal equivalent.
;               ES = The segment portion of a pointer to a 4 byte buffer where the converted binary number will be placed.
;               DI = The offset portion of a pointer to a 4 byte buffer where the converted binary number will be placed.
; Returns     : Nothing.
; Modified    : 06/21/91 DWP Initial coding.
; Notes       :

CONVERT_BinToHex   proc   MODEL_SIZE

                   ; Save the contents of the BX and CX registers.

                   push   bx
                   push   cx

                   ; Initialize CX.  CH is used as a loop variable while CL is used as an operand to SHR.  The hex word will be
                   ; shifted right three times, each shift will provide the main loop with a new 4 bit value to convert to ASCII.

                   mov    cx, 404h
                   add    di, 3
                   std

CONVERT_BinToHex_000:

                   ; Save the current value of AX, and then convert the digit in the AL register to its textual equivalent.

                   mov    bx, ax
                   and    al, 0fh
                   cmp    al, 9
                   jna    CONVERT_BinToHex_001

                   ; The value in AL is greater than 9, adjust it so that it will be properly converted to a letter between A and F.

                   add    al, 'A' - '0' - 10

CONVERT_BinToHex_001:

                   add    al, '0'

                   ; Place the converted character into the specified buffer.

                   stosb
                   dec    ch

                   ; Restore and then adjust the AX register so that the next 4 bits can be converted.

                   mov    ax, bx
                   shr    ax, cl

                   ; Exit the loop if the entire contents of the AX register have been converted.

                   cmp    ch, 0
                   ja     CONVERT_BinToHex_000

                   ; Restore the BX and CX registers to their previous state and exit.

                   pop    cx
                   pop    bx
                   ret

CONVERT_BinToHex   endp

CONVERT_code_segment ends
                   end
