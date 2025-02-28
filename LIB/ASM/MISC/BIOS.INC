; File        : BIOS.INC
; Module      : ASM
; System      :
; Description : Miscellaneous equates for the BIOS.
; Modified    : 05/21/90 DWP Modified.
; Notes       :

_DIVIDE_BY_0       =      00h
_SINGLE_STEP       =      01h
_NON_MASKABLE      =      02h
_BREAKPOINT        =      03h
_OVERFLOW          =      04h
_PRINT_SCREEN      =      05h
;Reserved          =      06h
;Reserved          =      07h
_TIMER_INT         =      08h
_KBD_INT           =      09h
;Reserved          =      0ah
;Reserved          =      0bh
;Reserved          =      0ch
;Reserved          =      0dh
_DISKETTE_INT      =      0eh
;Reserved          =      0fh
_VIDEO_IO          =      10h
_EQUIPMENT_CHECK   =      11h
_MEMORY_SIZE       =      12h
_DISKETTE_IO       =      13h
_RS232_IO          =      14h
_CASSETTE_IO       =      15h
_KBD_IO            =      16h
_PRINTER_IO        =      17h
_ROM_BASIC         =      18h
_BOOT_STRAP        =      19h
_TIME_OF_DAY       =      1ah
_KEYBOARD_BREAK    =      1bh
_USER_TIMER_INT    =      1ch
_VIDEO_PARMS_PTR   =      1dh
_DISKETTE_PARMS_PTR =     1eh
_GRAPHICS_TBL_PTR  =      1fh
_TERMINATE         =      20h
_DOS_SERVICES      =      21h
_DOS_TERMINATE_ADDR =     22h
_DOS_BREAK_ADDR    =      23h
_DOS_EROR_ADDR     =      24h
_DOS_DISK_READ     =      25h
_DOS_DISK_WRITE    =      26h
_FIX_IN_MEMORY     =      27h
;Reserved by DOS   =      28h - 3fh
;Reserved, XT      =      40h
; fixed disk BIOS
;Reserved          =      41h - 5fh
;Not used          =      41h - 7fh
;Reserved by BASIC =      80h - 85h
;Used by BASIC     =      86h - f0h
; Interpreter
;Not used          =      f1h - ffh
