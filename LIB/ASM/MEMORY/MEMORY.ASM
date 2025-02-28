; File        : MEMORY.ASM
; Module      : MEMORY
; System      : None
; Description :
; Modified    : 06/25/91 DWP Created.
; Notes       :

                   public MEMORY_setmem

MEMORY_code_segment segment byte public 'CODE'
                   assume cs:MEMORY_code_segment

; Procedure   : MEMORY_setmem
; Description : Sets all values in the specified memory block to the specified value.
; Expects     : AX = The value to place in the specified memory block.
;               CX = The total number of bytes to alter.
;               ES = The segment of the memory block to modify.
;               DI = The offset of the memory block to modify.
; Returns     : Nothing.
; Modified    : 06/25/91 DWP Initial coding.
; Notes       :

MEMORY_setmem      proc   MODEL_SIZE

                   ; Save the counter register and then divide it by two so that a 16-bit word can be placed in the destination
                   ; memory block instead of an 8-bit byte.  This halves the number of writes to memory needed to complete the
                   ; operation.

                   push   cx
                   shr    cx, 1

                   ; Fix the AX register so that it contains two copies of the byte that is being placed in the destination
                   ; memory block, then perform the operation.

                   mov    ah, al
                   cld
                   repne  stosw

                   ; Retrieve the original value of the counter register, if it was odd, then alter one additional byte of the
                   ; specified memory block.

                   pop    cx
                   and    cx, 1
                   rep    stosb
                   ret

MEMORY_setmem      endp

MEMORY_code_segment ends
                   end