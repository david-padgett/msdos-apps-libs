; File        : MSDOS2.ASM
; Module      : MSDOS
; System      : None
; Description : Locates the root or master PSP.
; Modified    : 03/20/91 DWP Created.
; Notes       :

		   include msdos.inc

                   public _DOS_Get_Root_PSP

DOS_Data           segment byte public 'DATA'
DOS_Data           ends

DOS_Code           segment byte public 'CODE'
                   assume cs:DOS_Code

; Function    : _DOS_Get_Root_PSP
; Description : Determines the address of the root or master PSP.
; Inputs      : Nothing.
; Updates     : Nothing.
; Outputs     : Nothing.
; Returns     : The address of the root PSP.  DX contains the segment, and AX contains the offset.
; Modified    : 03/20/91 DWP Initial coding.
; Notes       : 1) Methodology obtained from Andrew Schulman's "Undocumented DOS" page 389.

_DOS_Get_Root_PSP  proc   far

                   push   bx                     ; Save bx and es registers.
                   push   es

                   mov    ax, 352eh              ; Get address of INT 2Eh
                   int    21h                    ; vector.
                   mov    dx, es                 ; Move segment of vector
                   xor    ax, ax                 ; into dx, move 0 into ax.

                   pop    es                     ; Restore bx and ex
                   pop    bx                     ; registers.
                   ret

_DOS_Get_Root_PSP  endp

DOS_Code           ends
                   end