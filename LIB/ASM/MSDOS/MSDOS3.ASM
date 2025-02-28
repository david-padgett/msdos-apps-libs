; File        : MSDOS3.ASM
; Module      : MSDOS
; System      : None
; Description : A method for determining the size, in bytes, of an environment.
; Modified    : 03/20/91 DWP Created.
; Notes       :

		   include msdos.inc

                   public _DOS_Get_Environment_Size

DOS_Data           segment byte public 'DATA'
DOS_Data           ends

DOS_Code           segment byte public 'CODE'
                   assume cs:DOS_Code

; Function    : _DOS_Get_Environment_Size
; Description : Determines the buffer size of the specified environment.
; Inputs      : Environment = The environment whose size is desired.
; Updates     : Nothing.
; Outputs     : Nothing.
; Returns     : The size, in bytes, of the specified environment.
; Modified    : 03/20/91 DWP Initial coding.
; Notes       : 1) Methodology obtained from Andrew Schulman's "Undocumented DOS" page 390.
;               2) This function currently supports the C calling convention, and not the PASCAL method.  To switch to the PASCAL
;                  calling convention, remove the semi-colon in front of the macro PARAMETER_ADJUSTMENT on the line containing the
;                  RET instruction.  Also compile with case-sensitivity not preserved.

; Parameter Definitions:
;-----------------------
Environment_Segment equ    <[bp + 8]>
Environment_Offset  equ    <[bp + 6]>

PARAMETER_ADJUSTMENT  =    4

_DOS_Get_Environment_Size proc far

                   push    bp                    ; Set up standard stack
                   mov     bp, sp                ; frame.
                   push    bx                    ; Save bx, cx, and es
                   push    cx                    ; registers.
                   push    es

                   mov     ax, Environment_Segment
                   dec     ax                    ; Load es register with the
                   mov     es, ax                ; segment of the MCB
                                                 ; belonging to the specified
                                                 ; environment.

                   mov     bx, Environment_Offset
                   mov     ax, es:[bx].DOS_MCB_Size
                   mov     cx, 4
                   shl     ax, cl                ; Load ax register with the
                                                 ; total number of bytes
                                                 ; occupied by the specified
                                                 ; environment.

                   pop     es                    ; Restore es, cx, and bx
                   pop     cx                    ; registers.
                   pop     bx
                   mov     sp, bp                ; Restore stack to its
                   pop     bp                    ; previous state.

                   ret                           ;PARAMETER_ADJUSTMENT

_DOS_Get_Environment_Size endp

DOS_Code           ends
                   end