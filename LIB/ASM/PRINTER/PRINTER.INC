; File        : PRINTER.INC
; Module      : PRINTER
; System      : None
; Description : The definition file for PRINTER.ASM.
; Modified    : 07/19/90 DWP Created.
; Notes       :

ifndef _PRINTER_MODULE
_PRINTER_MODULE    equ    0

extrn  PRINTER_status : far

PRINTER_NOT_BUSY   equ    0080h
PRINTER_ACKNOWLEDGE equ   0040h
PRINTER_OUT_OF_PAPER equ  0020h
PRINTER_SELECTED   equ    0010h
PRINTER_IO_ERROR   equ    0008h
PRINTER_TIME_OUT   equ    0001h
PRINTER_OK         equ    ((PRINTER_NOT_BUSY OR PRINTER_SELECTED) AND NOT PRINTER_OUT_OF_PAPER AND NOT PRINTER_IO_ERROR)
PRINTER_ERROR      equ    (PRINTER_OUT_OF_PAPER OR PRINTER_IO_ERROR)

endif
