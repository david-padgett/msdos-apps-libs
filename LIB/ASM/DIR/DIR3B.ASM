; File        : DIR3C.ASM
; Module      : DIR
; System      : None
; Description : A method for renaming a directory.
; Modified    : 07/25/91 DWP Created.
; Notes       :

		   include ..\MSdos\MSdos.inc

                   public DIR_Rename_Directory

DIR_module_code    segment byte public 'CODE'
                   assume cs:DIR_module_code

; Function    : DIR_Rename_Directory
; Description : Renames the specified directory.
; Inputs      : Old_Name = The current name of the directory.
;               New_Name = The new name of the directory.
; Updates     : Nothing.
; Outputs     : Nothing.
; Returns     : AX = The value of the last error that occurred.  A value of zero indicates that no errors occurred.
; Modified    : 07/25/91 DWP Initial coding.
; Notes       :

Old_Name_Segment   equ    <[bp + 10]>
Old_Name_Offset    equ    <[bp + 8]>
New_Name_Segment   equ    <[bp + 14]>
New_Name_Offset    equ    <[bp + 12]>

PARAMETER_ADJUSTMENT =    8

DIR_Rename_Directory proc far

                   LOCAL  DPL:DOS_PARAMETER_LIST = DPL_SIZE

                   push   bp
                   mov    bp, sp
                   sub    sp, DPL_SIZE

                   push   bx
                   push   dx
                   push   ds

                   mov    DPL.DOS_PARAMETER_LIST_AX, 5600h
                   mov    ax, Old_Name_Segment
                   mov    DPL.DOS_PARAMETER_LIST_DS, ax
                   mov    ax, Old_Name_Offset
                   mov    DPL.DOS_PARAMETER_LIST_DX, ax
                   mov    ax, New_Name_Segment
                   mov    DPL.DOS_PARAMETER_LIST_ES, ax
                   mov    ax, New_Name_Offset
                   mov    DPL.DOS_PARAMETER_LIST_DI, ax

                   xor    ax, ax

                   mov    DPL.DOS_PARAMETER_LIST_Reserved, ax
                   mov    DPL.DOS_PARAMETER_LIST_Computer_ID, ax

                   ; Get the PSP segment address of the current process.

                   mov    ah, 62h
                   int    21h
                   mov    DPL.DOS_PARAMETER_LIST_Process_ID, bx

                   ; Initialize the DS:SI pointer to the DPL record on the stack.

                   mov    ax, ss
                   mov    ds, ax
                   mov    dx, bp
                   sub    dx, DPL_SIZE

                   mov    ax, 5d00h
                   int    21h

                   pop    ds
                   pop    dx
                   pop    bx
                   mov    sp, bp
                   pop    bp
                   ret    PARAMETER_ADJUSTMENT

DIR_Rename_Directory endp
DIR_module_code      ends
                     end