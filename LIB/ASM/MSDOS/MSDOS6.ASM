; File        : MSDOS6.ASM
; Module      : MSDOS
; System      : None
; Description : A method for converting a relative file specification to an absolute file specification.
; Modified    : 05/02/91 DWP Created.
; Notes       :

		   include msdos.inc

                   public _DOS_Qualify_File_Specification

DOS_Data           segment byte public 'DATA'
DOS_Data           ends

DOS_Code           segment byte public 'CODE'
                   assume cs:DOS_Code

; Function    : _DOS_Qualify_File_Specification
; Description : Fully qualifies the specified file specification.
; Expects     : Dest   = The buffer in which to place the fully qualified file specification.  The contents of this parameter may
;                        be undefined upon entry.
;               Source = The file specification to qualify.
; Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
; Modified    : 05/02/91 DWP Initial coding.
; Notes       : 1) This function is available only under DOS 3+ and greater.

; Parameter Definitions:
;-----------------------
Dest_Segment        equ    <[bp + 8]>
Dest_Offset         equ    <[bp + 6]>
Source_Segment      equ    <[bp + 12]>
Source_Offset       equ    <[bp + 10]>

PARAMETER_ADJUSTMENT  =    8

_DOS_Qualify_File_Specification proc far

                   ; Set up the stack frame.

                   push   bp
                   mov    bp, sp

                   ; Save the DI, SI, DS, and ES registers, since they will
                   ; be altered by the DOS call.

                   push   di
                   push   si
                   push   ds
                   push   es

                   ; Initialize DS:SI and ES:DI for the DOS call.

                   mov    ax, Source_Segment
                   mov    ds, ax
                   mov    si, Source_Offset

                   mov    ax, Dest_Segment
                   mov    es, ax
                   mov    di, Dest_Offset

                   mov    ah, 60h
                   int    21h

                   jc     _DOS_Qualify_File_Specification_000

                   sub    ax, ax

_DOS_Qualify_File_Specification_000:

                   ; Restore the DI, SI, DS, and ES registers to their
                   ; original values.

                   pop    es
                   pop    ds
                   pop    si
                   pop    di

                   ; Restore the stack to its previous state.

                   mov    sp, bp
                   pop    bp
                   ret    PARAMETER_ADJUSTMENT

_DOS_Qualify_File_Specification endp

DOS_Code           ends
                   end
