; File        : DOS5.ASM
; Module      : DOS
; System      : None
; Description : A method for retrieving the current DOS command-line switch character.
; Modified    : 03/30/91 DWP Created.
; Notes       :

		   include msdos.inc

                   public _DOS_Get_SwitchChar

DOS_Data           segment byte public 'DATA'
DOS_Data           ends

DOS_Code           segment byte public 'CODE'
                   assume cs:DOS_Code

; Function    : _DOS_Get_SwitchChar
; Description : Retrieves the current DOS command-line switch character.
; Inputs      : Nothing.
; Updates     : Nothing.
; Outputs     : Nothing.
; Returns     : The current DOS command-line switch character.  AX contains the switch character.  If the return value is zero,
;               then the switch character was not accessible.
; Modified    : 03/30/91 DWP Initial coding.
; Notes       :

_DOS_Get_SwitchChar proc  far

                   ; Save DX register.

                   push   dx

                   ; Get the current DOS switch character.

                   mov    ax, 3700h
                   int    21h

                   ; If AL = 0ffh, then the DOS call wasn't supported.

                   cmp    al, 0ffh
                   jne    _DOS_Get_SwitchChar_000

                   ; Initialize the DL register so that the return value will be defined.

                   xor    dl, dl

_DOS_Get_SwitchChar_000:

                   ; Place the current switch character in AL.

                   mov    al, dl
                   xor    ah, ah

                   ; Restore the DX register.

                   pop    dx
                   ret

_DOS_Get_SwitchChar endp

DOS_Code           ends
                   end
