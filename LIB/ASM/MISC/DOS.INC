; File        : DOS.INC
; Module      : ASM
; System      : None
; Description : Miscellaneous equates for DOS INT 21H function calls.
; Modified    : 05/21/90 DWP Modified.
; Notes       :

_DOS_TERMINATE     =      00h
_KEYBOARD_INPUT    =      01h
_DISPLAY_OUTPUT    =      02h
_AUX_INPUT         =      03h
_AUX_OUTPUT        =      04h
_PRINTER_OUTPUT    =      05H
_CONSOLE_IO        =      06h
_CONSOLE_INPUT     =      07h
_NO_ECHO_INPUT     =      08h
_PRINT_STRING      =      09h
_BUFFERED_INPUT    =      0ah
_INPUT_STATUS      =      0bh
_CLEAR_AND_INPUT   =      0ch
_RESET_DISK        =      0dh
_SELECT_DISK       =      0eh
_OPEN_FILE         =      0fh
_CLOSE_FILE        =      10h
_SEARCH_FIRST      =      11h
_SEARCH_NEXT       =      12h
_DELETE_FILE       =      13h
_READ_SEQ          =      14h
_WRITE_SEQ         =      15h
_CREATE_FILE       =      16h
_RENAME_FILE       =      17h
;DOS internal      =      18h
_CURRENT_DISK      =      19h
_SET_DTA           =      1ah
_FAT_DATA          =      1bh
_DISKETTE_FAT_DATA =      1ch
;DOS internal      =      1dh
;DOS internal      =      1eh
;DOS internal      =      1fh
;DOS internal      =      20h
_READ_RANDOM       =      21h
_WRITE_RANDOM      =      22h
_FILE_SIZE         =      23h
_SET_RANDOM_FIELD  =      24h
_SET_INT_VECTOR    =      25h
_CREATE_PROG_SEGMENT =    26h
_READ_BLOCK        =      27h
_WRITE_BLOCK       =      28h
_PARSE_FILENAME    =      29h
_GET_DATE          =      2ah
_SET_DATE          =      2bh
_GET_TIME          =      2ch
_SET_TIME          =      2dh
_VERIFY_SWITCH     =      2eh
_GET_DTA           =      2fh
_GET_VERSION       =      30h
_KEEP_PROCESS      =      31h
;DOS internal      =      32h
_BREAK_CHECK       =      33h
;DOS internal      =      34h
_GET_INT_VECTOR    =      35h
_GET_FREE_SPACE    =      36h
_SWITCHAR          =      37h
_COUNTRY_INFO      =      38h
_MKDIR             =      39h
_RMDIR             =      3ah
_CHDIR             =      3bh
_CREATE            =      3ch
_OPEN              =      3dh
_CLOSE_HANDLE      =      3eh
_READ_HANDLE       =      3fh
_WRITE_HANDLE      =      40h
_UNLINK            =      41h
_LSEEK             =      42h
_CHMOD             =      43h
_IOCTL             =      44h
_DUP_HANDLE        =      45h
_REDIRECT          =      46h
_GET_DIR           =      47h
_ALLOCATE_MEM      =      48h
_FREE_MEM          =      49h
_SETBLOCK          =      4ah
_EXEC              =      4bh
_EXIT              =      4ch
_WAIT              =      4dh
_FIND_FIRST        =      4eh
_FIND_NEXT         =      4fh
;DOS internal      =      50h
;DOS internal      =      51h
;DOS internal      =      52h
;DOS internal      =      53h
_GET_VERIFY_STATE  =      54h
;DOS internal      =      55h
_RENAME            =      56h
_TIME_STAMP        =      57h
;
; DOS Version 3.xx Additions
;
_GET_EXTENDED_ERROR_CODE = 59h
_CREATE_TEMPORARY_FILE =  5ah
_CREATE_NEW_FILE   =      5bh
_LOCK_FILE_ACCESS  =      5ch
_GET_PSP_ADDRESS   =      62h

;
; DOS SERVICES Error codes
;

_INVALID_FUNCTION_NUMBER                    =      01h
_FILE_NOT_FOUND                             =      02h
_PATH_NOT_FOUND                             =      03h
_TOO_MANY_OPEN_FILES                        =      04h
_ACCESS_DENIED                              =      05h
_INVALID_HANDLE                             =      06h
_MEMORY_CONTROL_BLOCKS_DESTROYED            =      07h
_INSUFFICIENT_MEMORY                        =      08h
_INVALID_MEMORY_BLOCK_ADDRESS               =      09h
_INVALID_ENVIRONMENT                        =      0ah
_INVALID_FORMAT                             =      0bh
_INVALID_ACCESS_CODE                        =      0ch
_INVALID_DATA                               =      0dh
_INVALID_DRIVE_SPECIFIED                    =      0fh
_ATTEMPTED_TO_REMOVE_THE_CURRENT_DIRECTORY  =      10h
_NOT_SAME_DEVICE                            =      11h
_NO_MORE_FILES                              =      12h
_INVALID_ARGUMENT                           =      13h
_ARGUMENT_LIST_TOO_LONG                     =      14h
_EXEC_FORMAT_ERROR                          =      15h
_CROSS_DEVICE_LINK                          =      16h
_MATH_ARGUMENT                              =      21h
_RESULT_TOO_LARGE                           =      22h
_FILE_ALREADY_EXISTS                        =      23h

;
; DOS SERVICES Error Codes, Version 3.xx
;    obtained thru _DOS_SERVICES, _GET_EXTENDED_ERROR_CODE
;
_NO_HANDLE_AVAILABLE                        =      04h
_DISK_WRITE_PROTECTED                       =      13h
_UNKNOWN_UNIT_ID                            =      14h
_DISK_DRIVE_NOT_READY                       =      15h
_COMMAND_NOT_DEFINED                        =      16h
_DISK_DATA_ERROR                            =      17h
_BAD_REQUEST_STRUCTURE_LENGTH               =      18h
_DISK_SEEK_ERROR                            =      19h
_UNKNOWN_DISK_MEDIA_TYPE                    =      1ah
_DISK_SECTOR_NOT_FOUND                      =      1bh
_PRINTER_OUT_OF_PAPER                       =      1ch
_WRITE_ERROR                                =      1dh
_READ_ERROR                                 =      1eh
_GENERAL_FAILURE                            =      1fh
_FILE_SHARING_VIOLATION                     =      20h
_FILE_LOCKING_VIOLATION                     =      21h
_IMPROPER_DISK_CHANGE                       =      22h
_NO_FCB_AVAILABLE                           =      23h
_FILE_ALREADY_EXISTS                        =      50h
_CANNOT_MAKE_DIRECTORY_ENTRY                =      52h
_CRITICAL_ERROR_INTERRUPT_FAILURE           =      53h

_END_OF_FILE                                =      0feh
_DISK_FULL                                  =      0ffh
