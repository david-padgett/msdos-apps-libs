; File        : KB.INC
; Module      : KB
; System      : None
; Description : The definition file for KB.ASM.
; Modified    : 05/23/90 DWP Created.
; Notes       :

ifndef _KB_MODULE
_KB_MODULE         equ    0

extrn  KB_Read                       : far
extrn  KB_Preview                    : far
extrn  KB_Shift_Status               : far
extrn  KB_Retrieve_Shift_Status_Word : far
extrn  KB_Retrieve_Status_Word       : far
extrn  KB_Enhanced_Keyboard_Present  : far

endif
