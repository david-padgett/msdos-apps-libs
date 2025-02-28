; File        : DOS.ASM
; Module      : DOS
; System      : None
; Description :
; Modified    : 06/24/91 DWP Created.
; Notes       :

                   public DOS_Display_String, DOS_Parse_Command_Line

		   include ..\..\lib\asm\standard\standard.inc

DOS_code_segment   segment byte public 'CODE'
                   assume cs:DOS_code_segment

; Procedure   : DOS_Display_String
; Description : Displays the dollar sign ('$') terminated string pointed to by ES:DI.
; Expects     : ES = The segment of the string to display.
;               DI = The offset of the string to display.
; Returns     : Nothing.
; Modified    : 06/21/91 DWP Initial coding.
; Notes       :

DOS_Display_String proc   MODEL_SIZE

                   ; Save the contents of the AX, DX, and DS registers.

                   push   ax
                   push   dx
                   push   ds

                   ; Set up the parameters to INT 21/9.

                   mov    ax, es
                   mov    ds, ax
                   mov    dx, di

                   ; Display the specified '$' terminated string.

                   mov    ah, 9
                   int    21h

                   ; Restore the AX, DX, and DS registers to their previous state and exit.

                   pop    ds
                   pop    dx
                   pop    ax
                   ret

DOS_Display_String endp

; Function    : DOS_Parse_Command_Line
; Description : Parses the command-line of the current process.  Parameters are separated by a sequence of one or more white
;               space characters and/or delimiter characters, if a delimiter character is specified.
; Expects     : AL = The command-line parameter to retrieve, this value should be in the range [0..Total Parms - 1].
;               AH = The character to use as a delimiter when single arguments may contain more than one word.  The text that
;                    is enclosed by this character will be treated as one parameter.  A value of 00h indicates that there are
;                    no delimiters in the command-line text.
;               ES = The segment of the buffer in which to place the specified command-line parameter.
;               DI = The offset of the buffer in which to place the specified command-line parameter.
; Returns     : The value of the AL register if the pointer represented by ES:DI is not NULL, otherwise, the total number of
;               command-line parameters given when the current process was invoked.
; Modified    : 06/24/91 DWP Initial coding.
; Notes       : 1) DOS_Parse_Command_Line can be used to for two different things,
;                  o To determine how many command-line arguments were specified when the current process was invoked,
;                    this is accomplished by specifying a NULL pointer in ES:DI.
;                  o To determine the value of the specified command-line parameter, this is accomplished by specifying a valid
;                    (non-NULL) pointer in ES:DI.

; Variables

CURRENT_CHARACTER  equ    <al>
DELIMITER_FOUND_FLAG equ  <bl>
PARAMETER_FOUND_FLAG equ  <bh>
CURRENT_PARAMETER   equ   <cl>
DELIMITER_CHARACTER equ   <ch>
PARAMETERS_FOUND    equ   <dl>
NULL_POINTER_FLAG  equ    <dh>

DOS_Parse_Command_Line proc MODEL_SIZE

                   ; Save the contents of the BX, CX, DX, SI, and DS registers.

                   push   bx
                   push   cx
                   push   dx
                   push   si
                   push   ds

                   ; Initialize the CX register, CH contains the value of the user-defined delimiter character, a value of 00h
                   ; indicates that no user-defined delimiter character is to be used, CL contains the command-line argument that
                   ; is to be retrieved.

                   mov    cx, ax

                   ; Get the segment address of the current PSP.

                   mov    ah, 62h
                   int    21h

                   ; Initialize DS:SI so that it points to the command-line argument area.

                   cld
                   mov    ds, bx
                   mov    si, 81h

                   ; BL represents a flag that indicates whether or not the user-specified delimiter character has been
                   ; encountered, BH represents a flag indicating whether or not a command-line parameter is currently being
                   ; parsed, both flags are initially FALSE.

                   sub    bx, bx

                   ; DH represents a flag indicating whether or not ES:DI is NULL, DH is TRUE if ES:DI is NULL, and FALSE
                   ; otherwise.  DL contains the total number of command-line parameters that were processed.  It will equal
                   ; CL upon exit if ES:DI is not equal to NULL, otherwise, it will contain the total number of command-line
                   ; arguments specified when the current process was invoked.

                   sub    dx, dx
                   mov    ax, es
                   cmp    ax, dx
                   jne    DOS_Parse_Command_Line_000
                   cmp    di, dx
                   jne    DOS_Parse_Command_Line_000

		   ; ES:DI is NULL, so re-initialize DH to indicate this.  Also re-initialize CL so that the loop that searches for
                   ; command-line parameters will not be terminated prematurely.

                   inc    NULL_POINTER_FLAG
                   mov    CURRENT_PARAMETER, 07fh

DOS_Parse_Command_Line_000:

                   ; Retrieve the next command-line character.

                   lodsb

                   ; Determine if the end-of-line character has been encountered, if so then exit the loop.

                   cmp    CURRENT_CHARACTER, 0dh
                   je     DOS_Parse_Command_Line_004

                   ; Determine if the character is the specified delimiter character.

                   cmp    CURRENT_CHARACTER, DELIMITER_CHARACTER
                   je     DOS_Parse_Command_Line_002

                   ; By-pass the check for white-space if the current character is between the user-defined delimiter character.

                   cmp    DELIMITER_FOUND_FLAG, FALSE
                   jne    DOS_Parse_Command_Line_001

                   ; Determine if the character is white-space.  White space characters include SPACE, TAB, and CR.

                   cmp    CURRENT_CHARACTER, 20h
                   je     DOS_Parse_Command_Line_003
                   cmp    CURRENT_CHARACTER, 09h
                   je     DOS_Parse_Command_Line_003

DOS_Parse_Command_Line_001:

                   ; Re-initialize the flag which indicates that a command-line parameter is currently being parsed.  Determine if
                   ; the character being processed belongs to the command-line parameter being sought, if so, place the character
                   ; in the destination buffer.

                   mov    PARAMETER_FOUND_FLAG, TRUE
                   cmp    CURRENT_PARAMETER, 0
                   ja     DOS_Parse_Command_Line_000

                   ; Do not save the character if ES:DI is NULL.

                   cmp    NULL_POINTER_FLAG, FALSE
                   jne    DOS_Parse_Command_Line_000

                   stosb
                   jmp    short DOS_Parse_Command_Line_000

DOS_Parse_Command_Line_002:

                   ; Toggle the delimiter flag, if the flag becomes FALSE, a parameter has been found.

                   mov    PARAMETER_FOUND_FLAG, TRUE
                   not    DELIMITER_FOUND_FLAG
                   cmp    DELIMITER_FOUND_FLAG, FALSE
                   jne    DOS_Parse_Command_Line_000

DOS_Parse_Command_Line_003:

                   ; Determine if the end of a parameter has been located.  If it has, then increment the parameter counter,
                   ; decrement the loop counter, and continue the loop which searches for command-line parameters.

                   cmp    PARAMETER_FOUND_FLAG, FALSE
                   je     DOS_Parse_Command_Line_000

                   inc    PARAMETERS_FOUND
                   xor    PARAMETER_FOUND_FLAG, PARAMETER_FOUND_FLAG
                   dec    CURRENT_PARAMETER
                   cmp    CURRENT_PARAMETER, 0ffh
                   jne    DOS_Parse_Command_Line_000

DOS_Parse_Command_Line_004:

                   ; Increment the total number of parameters discovered, if necessary.

                   cmp    PARAMETER_FOUND_FLAG, FALSE
                   je     DOS_Parse_Command_Line_005
                   inc    PARAMETERS_FOUND

DOS_Parse_Command_Line_005:

                   ; Place a terminating NULL character at the end of the destination buffer, unless the specified buffer pointed
                   ; to by ES:DI if ES:DI is NULL.

                   cmp    NULL_POINTER_FLAG, FALSE
                   jne    DOS_Parse_Command_Line_006

                   sub    ax, ax
                   stosb

DOS_Parse_Command_Line_006:

                   ; Place the return value of DOS_Parse_Command_Line() into AX.

                   sub    ax, ax
                   mov    al, PARAMETERS_FOUND

                   ; Restore the contents of the BX, CX, DX, SI, and DS registers.

                   pop    ds
                   pop    si
                   pop    dx
                   pop    cx
                   pop    bx
                   ret

DOS_Parse_Command_Line endp

DOS_code_segment   ends
                   end
