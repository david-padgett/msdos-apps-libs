; File        : CURSOR.INC
; Module      : CURSOR
; System      : None
; Description : The header file for the CURSOR module.
; Modified    : 04/30/91 DWP Created.
; Notes       :

ifndef _CURSOR_MODULE
_CURSOR_MODULE equ 0

extrn CURSOR_Off                : far
extrn CURSOR_On                 : far
extrn CURSOR_Set_Characteristic : far
extrn CURSOR_Get_Characteristic : far

endif