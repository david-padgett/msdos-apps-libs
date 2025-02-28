; File        : BOOT.ASM
; Module      : BOOT
; System      : BOOT
; Description : This program re-boots the computer.
; Modified    : 10/14/91 DWP Created.
; Notes       : 1) Usage
;
;                     BOOT [<Option>]
;
;               2) Options
;
;                     COLD = Performs a cold boot, same as RESET, includes POST.', 0dh, 0ah
;                     WARM = Performs a warm boot, same as CTRL-ALT-DEL.', 0dh, 0ah, '$'

; BOOT_TYPES

BOOT_WARM          equ    0
BOOT_COLD          equ    1

BOOT_Code          segment byte public 'CODE'
                   assume cs:BOOT_Code

                   org    100h
Start:
                   jmp    Main

BOOT_Help_Text     db     0dh, 0ah
                   db     'BOOT V1.0, ', COMPILE_DATE, ', Copyright (c) 1991 by CSFX', 0dh, 0ah, 0dh, 0ah
                   db     'Purpose : Performs either a cold or warm re-boot.', 0dh, 0ah, 0dh, 0ah
                   db     'Usage   : BOOT [<Option>]', 0dh, 0ah, 0dh, 0ah
                   db     'Options', 0dh, 0ah, 0dh, 0ah
                   db     '   COLD = Performs a cold boot, same as RESET, includes POST.', 0dh, 0ah
                   db     '   WARM = Performs a warm boot, same as CTRL-ALT-DEL.', 0dh, 0ah, '$'

; Procedure   : BOOT_Main
; Description : Performs either a warm or cold re-boot.
; Inputs      : Boot_Type = The type of boot to perform.  See BOOT_TYPES.
; Updates     : Nothing.
; Outputs     : Nothing.
; Returns     : Nothing.
; Modified    : 10/14/91 DWP Initial coding.
; Notes       :

Boot_Type          equ    [bp + 4]

BOOT_Main          proc   far

                   ; Determine what type of boot to perform.

                   mov    bp, sp
                   mov    ax, Boot_Type
                   cmp    ax, BOOT_WARM
                   jne    BOOT_Main_001

                   ; A warm boot was requested.

                   mov    ax, 1234h
                   jmp    short BOOT_Main_002
BOOT_Main_001:
                   ; A cold boot was requested.

                   xor    ax, ax
BOOT_Main_002:
                   ; Initialize the POST reset flag at 0040:0072.

                   mov    bx, 40h
                   mov    ds, bx
                   mov    ds:[72h], ax

                   ; Force a return to FFFF:0000.

                   xor    ax, ax
                   dec    ax
                   push   ax
                   inc    ax
                   push   ax

                   ret

BOOT_Main          endp

; Function    : Main
; Description : The main entry point to the BOOT program.
; Inputs      : Nothing.
; Updates     : Nothing.
; Outputs     : Nothing.
; Returns     : Always returns a value of zero.
; Modified    : 10/14/91 DWP Initial coding.
; Notes       : 1) Expects CS to contain the PSP segment address.

Main               proc   near

                   ; Place the PSP segment address into DS.

                   mov    ax, cs
                   mov    ds, ax

                   mov    bx, 80h

                   ; Locate the start of the first command line parameter.
Main_001:
                   inc    bx

                   ; Stop if the end of the PSP has been encountered.

                   cmp    bx, 0ffh
                   je     Main_005

                   ; Stop if the end of the command line parameter list has been encountered.

                   cmp    byte ptr [bx], 0dh
                   je     Main_005

                   ; Loop until the start of the first command line parameter has been located.

                   cmp    byte ptr [bx], ' '
                   je     Main_001

                   ; Retrieve the first command line parameter from the PSP.

                   mov    cx, [bx]
                   inc    bx
                   inc    bx
                   mov    dx, [bx]

                   ; Make sure that only one command line parameter of length 4 bytes is present.

                   inc    bx
                   inc    bx
                   cmp    byte ptr [bx], 0dh
                   jne    Main_005

                   ; Convert the contents of CX and DX to upper case.

                   and    cx, 1101111111011111b
                   and    dx, 1101111111011111b

                   ; Determine what type of boot was requested.

                   cmp    cx, 'AW'
                   jne    Main_003
                   cmp    dx, 'MR'
                   jne    Main_005

                   ; A warm boot was requested.

                   mov    ax, BOOT_WARM
                   jmp    short Main_004
Main_003:
                   cmp    cx, 'OC'
                   jne    Main_005
                   cmp    dx, 'DL'
                   jne    Main_005

                   ; A cold boot was requested.

                   mov    ax, BOOT_COLD
Main_004:
                   push   ax
                   call   BOOT_Main
Main_005:
                   ; An invalid request was specified, so print the help screen and exit.

                   mov    dx, offset BOOT_Help_Text
                   mov    ax, 0900h
                   int    021h

                   mov    ax, 04c00h
                   int    021h

Main               endp
BOOT_Code          ends
                   end    Start
