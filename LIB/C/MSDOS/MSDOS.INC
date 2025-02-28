; File        : DOS.INC
; Module      : DOS
; System      : None
; Description : The implementation header file for the assembly language portions of the DOS module.
; Modified    : 03/20/91 DWP Created.
; Notes       :

; Type definitions

DOS_MCB struc

   DOS_MCB_Type      db ?
   DOS_MCB_Owner     dw ?
   DOS_MCB_Size      dw ?
   DOS_MCB_Unused    db 3 dup(?)
   DOS_MCB_File_Name db 8 dup(?)

DOS_MCB ends

DOS_PSP struc

   DOS_PSP_Exit_Point              dw ?
   DOS_PSP_Memory_Size             dw ?
   DOS_PSP_Unused1                 db ?
   DOS_PSP_CPM_Entry_Point         db 5 dup(?)
   DOS_PSP_Terminate_Address       dd ?
   DOS_PSP_Break_Address           dd ?
   DOS_PSP_Critical_Error_Handler  dd ?
   DOS_PSP_Parent_PSP_Segment      dw ?
   DOS_PSP_Open_File_Table         db 20 dup(?)
   DOS_PSP_Environment_Segment     dw ?
   DOS_PSP_Stack                   dd ?
   DOS_PSP_Max_Open_Files          dw ?
   DOS_PSP_Open_File_Table_Address dd ?
   DOS_PSP_Previous_PSP_Address    dd ?
   DOS_PSP_Unused2                 db 20 dup(?)
   DOS_PSP_DOS_Function_Dispatcher db 3 dup(?)
   DOS_PSP_Unused3                 db 9 dup(?)
   DOS_PSP_FCB_1                   db 16 dup(?)
   DOS_PSP_FCB_2                   db 20 dup(?)
   DOS_PSP_Command_Tail            db 128 dup(?)

DOS_PSP ends

DOS_PARAMETER_LIST struc

   DOS_PARAMETER_LIST_AX          dw ?
   DOS_PARAMETER_LIST_BX          dw ?
   DOS_PARAMETER_LIST_CX          dw ?
   DOS_PARAMETER_LIST_DX          dw ?
   DOS_PARAMETER_LIST_SI          dw ?
   DOS_PARAMETER_LIST_DI          dw ?
   DOS_PARAMETER_LIST_DS          dw ?
   DOS_PARAMETER_LIST_ES          dw ?
   DOS_PARAMETER_LIST_Reserved    dw ?           ; Should always be 0.
   DOS_PARAMETER_LIST_Computer_ID dw ?           ; Current system is 0.
   DOS_PARAMETER_LIST_Process_ID  dw ?           ; PSP segment on specified computer.

DOS_PARAMETER_LIST ends
