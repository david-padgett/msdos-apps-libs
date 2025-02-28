; File        : KBCLEAR.ASM
; Module      : KBCLEAR
; System      : KBCLEAR
; Description : This program is a TSR that, when activated, clears the keyboard type ahead buffer.
; Modified    : 07/29/91 DWP Initial coding.
; Notes       :

		   include .\..\ksg\asm.inc

                   ifndef COMPILE_DATE
COMPILE_DATE       equ    <'00-XXX-0000'>
                   endif

                   ifndef COMPILE_YEAR
COMPILE_YEAR       equ    <'0000'>
                   endif

; Type Definitions.

KBCLEAR_Control_Parameters struc

First_Run_Flag     db     ?
Active_Flag        db     ?
Status_Byte_Mask   db     ?
INT_1C             dd     ?

KBCLEAR_Control_Parameters ends

                   ; Define the memory addresses accessed at segment 0.

SEGMENT_0          segment at 0

                   org    1ch * 4
User_Timer_INT     dd     ?
                   org    417h
Status_Flags       db     ?
                   org    41ah
Next_Character     dw     ?
                   org    41ch
First_Free_Slot    dw     ?
                   org    480h
Offset_Start       dw     ?

SEGMENT_0          ends

KBCLEAR_Code       segment byte public 'CODE'

; Define uninitialized global variable space in the PSP starting at offset 80h.

                   org    80h
Control_Parameters label  KBCLEAR_Control_Parameters

;First_Run_Flag     label  byte
;                   org    81h
;Active_Flag        label  byte
;                   org    82h
;Status_Byte_Mask   label  byte

;                   org    84h
;INT_1CH            label  dword
;INT_1C_Offset      label  word
;                   org    86h
;INT_1C_Segment     label  word

                   org    100h
                   assume cs:KBCLEAR_Code, ds:SEGMENT_0

; Procedures and Functions.

; Procedure   : KBCLEAR_TSR_Code
; Description : The entry point to the KBCLEAR module.
; Inputs      : Nothing.
; Updates     : Nothing.
; Outputs     : Nothing.
; Returns     : Nothing.
; Modified    : 07/29/91 DWP Initial coding.
; Notes       :

KBCLEAR_TSR_Code   proc   far

                   ; Determine if the program has been installed yet, if not, then invoke the install procedure.

                   pushf
                   cmp    cs:Control_Parameters.First_Run_Flag, 0ffh
                   je     KBCLEAR_TSR_Code_000
                   popf
                   jmp    KBCLEAR_Main

KBCLEAR_TSR_Code_000:

                   ; Save the contents of the AX and ES registers.

                   push   ax
                   push   es

                   cmp    ax, 'KB'
                   jne    KBCLEAR_TSR_Code_001
                   cmp    bx, 'CL'
                   jne    KBCLEAR_TSR_Code_001
                   cmp    cx, 'EA'
                   jne    KBCLEAR_TSR_Code_001
                   cmp    dx, ('R' shl 8) AND 0ff00h
                   jne    KBCLEAR_TSR_Code_001

                   mov    ax, cs
                   mov    es:[di], ax
                   jmp    short KBCLEAR_TSR_Code_002

KBCLEAR_TSR_Code_001:

                   ; If the program is inactive, then exit.

                   cmp    cs:Control_Parameters.Active_Flag, 1
                   jne    KBCLEAR_TSR_Code_002

                   ; Determine if the activation keys are pressed, if not, then exit.

                   mov    ax, SEGMENT_0
                   mov    es, ax
                   mov    ah, es:Status_Flags
                   mov    al, cs:Control_Parameters.Status_Byte_Mask
                   and    ah, al
                   cmp    ah, al
                   jne    KBCLEAR_TSR_Code_002

                   ; Clear the keyboard type ahead buffer by placing the offset of the start address in the next character and
                   ; first free slot memory locations, which are located in the low memory data area.

                   mov    ax, es:Offset_Start
                   mov    es:Next_Character, ax
                   mov    es:First_Free_Slot, ax

KBCLEAR_TSR_Code_002:

                   ; Restore the AX, ES, and Flags registers to their previous states.

                   pop    es
                   pop    ax
                   popf
                   jmp    cs:Control_Parameters.INT_1C

KBCLEAR_TSR_Code   endp

; This label is used by KBCLEAR_Install to calculate the minimum number of paragraphs needed by KBCLEAR to function as a TSR.

KBCLEAR_End        equ    $

; Function    : KBCLEAR_Install
; Description : Installs KBCLEAR as a TSR.
; Inputs      : Nothing.
; Updates     : Nothing.
; Outputs     : Nothing.
; Returns     : Always returns a value of zero.
; Modified    : 07/29/91 DWP Initial coding.
; Notes       :

KBCLEAR_Install    proc   near

                   ; Release the environment segment space, since it is not needed.

                   mov    ax, ds:[002ch]
                   mov    es, ax
                   mov    ah, 49h
                   int    21h

                   ; Save the current INT 1Ch vector.

                   mov    ax, SEGMENT_0
                   mov    ds, ax
                   les    ax, User_Timer_INT
                   mov    word ptr Control_Parameters.INT_1C, ax
                   mov    word ptr Control_Parameters.INT_1C + 2, es
                   mov    Control_Parameters.First_Run_Flag, 0ffh
                   mov    Control_Parameters.Active_Flag, 1
                   mov    ax, Status_Mask
                   mov    Control_Parameters.Status_Byte_Mask, ax

                   ; Re-vector INT 1Ch.

                   cli
                   mov  word ptr User_Timer_INT, offset KBCLEAR_TSR_Code
                   mov  word ptr User_Timer_INT + 2, cs
                   sti

                   ; Exit to DOS leaving the KBCLEAR_TSR_Code procedure behind as a TSR.

                   mov  dx, offset KBCLEAR_End
                   mov  cl, 4
                   shr  dx, cl
                   inc  dx
                   mov  ax, 3100h
                   int  21h

KBCLEAR_Install    endp

; Function    : KBCLEAR_Retrieve_PSP_Segment_Of_TSR
; Description : Determines if KBCLEAR is already running as a TSR.
; Inputs      : Nothing.
; Updates     : Nothing.
; Outputs     : Nothing.
; Returns     : CF = Set if KBCLEAR is already running as a TSR.
;               ES = PSP segment of TSR version of KBCLEAR.
; Modified    : 07/29/91 DWP Initial coding.
; Notes       :

KBCLEAR_Retrieve_PSP_Segment_Of_TSR proc near

                   ; Initialize the DS register.

                   mov    ax, cs
                   mov    ds, ax

                   ; Initialize ES:DI for the invocation of INT 1Ch.

                   mov    TSR_PSP_Segment, 0
                   mov    es, ax
                   mov    di, offset TSR_PSP_Segment

                   ; Initialize the AX, BX, CX, and DX registers for the invocation of INT 1CH.  The 4 registers contain the ASCIIZ
                   ; string 'KBCLEAR'.

                   mov    ax, 'KB'
                   mov    bx, 'CL'
                   mov    cx, 'EA'
                   mov    dx, ('R' shl 8) AND 0ff00h
                   int    1ch

                   clc
                   cmp    TSR_PSP_Segment, 0
                   je     KBCLEAR_Retrieve_PSP_Segment_Of_TSR_000
                   stc

KBCLEAR_Retrieve_PSP_Segment_Of_TSR_000:

                   ret

KBCLEAR_Retrieve_PSP_Segment_Of_TSR endp

; Procedure   : KBCLEAR_Display_Status
; Description : Displays the status of the TSR version of KBCLEAR.
; Inputs      : Nothing.
; Updates     : Nothing.
; Outputs     : Nothing.
; Returns     : Nothing.
; Modified    : 07/29/91 DWP Initial coding.
; Notes       :

KBCLEAR_Display_Status proc near

                   ; Display '   Status'

                   mov    dx, offset Status_Text
                   mov    ah, 9
                   int    21h

                   ; Display '      Active -'

                   mov    dx, offset Active_Text
                   mov    ah, 9
                   int    21h

                   ; Determine whether or not the TSR version of KBCLEAR is active.

                   mov    ax, cs:TSR_PSP_Segment
                   mov    es, ax
                   mov    di, 80h

                   mov    dx, offset Yes_Text
                   mov    al, KBCLEAR_Control_Parameters ptr es:[di].Active_Flag
                   cmp    al, 0
                   jne    KBCLEAR_Display_Status_000
                   mov    dx, offset No_Text

KBCLEAR_Display_Status_000:

                   ; Display either 'Yes' or 'No'

                   mov    ah, 9
                   int    21h

                   ; Display '   Activation Keys'

                   mov    dx, offset Activation_Keys_Text
                   mov    ah, 9
                   int    21h

                   ; Display the activation keys.

                   mov    al, KBCLEAR_Control_Parameters ptr es:[di].Status_Byte_Mask
                   and    al, 0fh
                   mov    ah, 9
                   xor    bx, bx
                   mov    cx, 4

KBCLEAR_Display_Status_001:

                   mov    dx, 1
                   shl    dl, cl
                   shr    dl, 1
                   test   al, dl
                   jz     KBCLEAR_Display_Status_002

                   shl    dx, 1
                   shl    dx, 1
                   add    dx, offset Activation_Keys_List
                   push   ax
                   int    21h
                   pop    ax

                   cmp    bl, bh
                   jne    KBCLEAR_Display_Status_002
                   inc    bl
                   mov    dx, offset Plus_Text
                   push   ax
                   int    21h
                   pop    ax

KBCLEAR_Display_Status_002:

                   loop   KBCLEAR_Display_Status_001

                   ret

KBCLEAR_Display_Status endp

; Function    : KBCLEAR_Main
; Description : The entry point to the KBCLEAR program.
; Inputs      : Nothing.
; Updates     : Nothing.
; Outputs     : Nothing.
; Returns     : Always returns a value of zero.
; Modified    : 07/29/91 DWP Initial coding.
; Notes       :

KBCLEAR_Main       proc   far

                   ; Display the program name.

                   mov    ax, cs
                   mov    ds, ax
                   mov    dx, offset Title_Message_Text
                   mov    ah, 9
                   int    21h

                   ; Display the help screen if no command-line parameters were given.

                   xor    ax, ax
                   push   ax
                   push   ax
                   push   ax
                   push   ax

                   call   DOS_Parse_Command_Line

                   cmp    ax, 0
                   je     KBCLEAR_Main_001

                   mov    ax, offset Buffer
                   push   ax
                   push   ds
                   xor    ax, ax
                   push   ax
                   push   ax

                   call   DOS_Parse_Command_Line

                   mov    ax, offset Buffer
                   push   ax
                   push   ds
                   mov    ax, offset On_Text
                   push   ax
                   push   ds

                   call   STRING_Compare

                   je     xx1

                   mov    ax, offset Buffer
                   push   ax
                   push   ds
                   mov    ax, offset Off_Text
                   push   ax
                   push   ds

                   call   STRING_Compare

                   je     xx2

                   mov    cx, 0
                   mov    dx, offset Activation_Keys_List
yy1:
                   push   dx
                   push   ds
                   mov    ax, offset Buffer
                   push   ax
                   push   ds

                   call   STRING_Fixed_Length_Compare

                   je     xx3
                   add    dx, 8
                   cmp    cx, 4
                   jl     yy1

                   ; Determine if KBCLEAR is already resident, if not, then install it.

xx1:
xx2:
xx3:

                   call   KBCLEAR_Retrieve_PSP_Segment_Of_TSR
                   jc     KBCLEAR_Main_000
                   jmp    KBCLEAR_Install

                   ; KBCLEAR is already a TSR, display the current status of the memory resident version.

KBCLEAR_Main_000:
                   call   KBCLEAR_Display_Status
                   jmp    short KBCLEAR_Main_002

                   ; Display the help screen.

KBCLEAR_Main_001:
                   mov    dx, offset Help_Screen_Text
                   mov    ah, 9
                   int    21h

KBCLEAR_Main_002:
                   mov    ax, 4c00h
                   int    21h

KBCLEAR_Main       endp

; Initialized Global Data.

TSR_PSP_Segment    dw     ?
Status_Mask        dw     3                      ; Initial hot keys are LSHIFT and RSHIFT
Buffer             db     129 dup(0)

Title_Message_Text db     0dh, 0ah, 'KBCLEAR V1.0, ', COMPILE_DATE, ', Copyright (c) ', COMPILE_YEAR, ' by CSFX', 0dh, 0ah, '$'

Help_Screen_Text   db     0dh, 0ah, 'Purpose : This TSR, when activated, clears the keyboard type ahead buffer.', 0dh, 0ah
                   db     0dh, 0ah, 'Usage   : KBCLEAR {<Command> | <First_Activation_Key> <Second_Activation_Key>}', 0dh, 0ah
                   db     0dh, 0ah, '   Commands (used after KBCLEAR has been installed)', 0dh, 0ah
                   db     0dh, 0ah, '      ON   - Enable, process all requests (default)'
                   db     0dh, 0ah, '      OFF  - Disable, but remain in memory'
                   db     0dh, 0ah, '      QUIT - Disable, remove from memory', 0dh, 0ah
                   db     0dh, 0ah, '   Activation Keys (two unique Activation Keys must be specified)', 0dh, 0ah
                   db     0dh, 0ah, '      LSHIFT, RSHIFT, CTRL, or ALT', 0dh, 0ah, '$'

On_Text            db     'ON', 0
Off_Text           db     'OFF', 0

Activation_Keys_List db   'RSHIFT', '$', 0
                     db   'LSHIFT', '$', 0
                     db   'CTRL',   '$', 0, 0, 0
                     db   'ALT',    '$', 0, 0, 0, 0

Status_Text          db   0dh, 0ah, '   Status', 0dh, 0ah, '$'
Active_Text          db   0dh, 0ah, '      Active - $'
Yes_Text             db   'Yes', 0dh, 0ah, '$'
No_Text              db   'No', 0dh, 0ah, '$'
Activation_Keys_Text db   0dh, 0ah, '   Activation Keys', 0dh, 0ah, '$'
Plus_Text            db   ' + $'

KBCLEAR_Code         ends
                     end   KBCLEAR_TSR_Code
