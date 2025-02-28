; File        : CRT0.ASM
; Module      : CRT
; System      : None
; Description : The global variables for the CRT module.
; Modified    : 08/01/90 DWP Created from "CRT.ASM".

crt_module_data    segment byte public 'DATA'

                   ; All data defaults to the standard DOS screen.

video_attr         db     7                      ;hi=foreground, lo=background
video_segment      dw     0b800h                 ;seg of current screen bufr

row                db     0                      ;relative to window
col                db     0                      ;relative to window

wn_max_row         db     24                     ;max row in window (absolute)
wn_min_row         db     0                      ;min row in window (absolute)
wn_max_col         db     79                     ;max col in window (absolute)
wn_min_col         db     0                      ;min col in window (absolute)

wn_height          db     24                     ;wn_max_row - wn_min_row
wn_length          db     79                     ;wn_max_col - wn_min_col
wn_max_height      dw     25                     ;max allowable wn height
wn_max_length      dw     80                     ;max allowable wn length

flag_1             db     1                      ;bit 0 - update cursor
                                                 ;bit 1 - use ROM BIOS /future
crt_module_data    ends
                   end
