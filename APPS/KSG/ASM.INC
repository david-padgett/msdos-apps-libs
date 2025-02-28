; File        : ASM.INC
; Module      : ASM
; System      : None
; Description : The definition header file for the ASM module.
; Modified    : 06/25/91 DWP Created.
; Notes       :

extrn CONVERT_BinToHex:MODEL_SIZE
extrn DOS_Display_String:MODEL_SIZE, DOS_Parse_Command_Line:MODEL_SIZE
extrn FILE_Open:MODEL_SIZE, FILE_Close:MODEL_SIZE, FILE_Read:MODEL_SIZE, FILE_Write:MODEL_SIZE, FILE_Seek:MODEL_SIZE
extrn MEMORY_setmem:MODEL_SIZE