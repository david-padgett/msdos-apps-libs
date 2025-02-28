; File        : DOS.ASM
; Module      : DOS
; System      : None
; Description :
; Modified    : 06/24/91 DWP Created.
; Notes       :

                   public DOS_Parse_Command_Line

		   include ..\..\ASM\Standard\standard.inc

DOS_Code           segment byte public 'CODE'
                   assume cs:DOS_Code

; Function    : DOS_Parse_Command_Line
; Description : Parses the command-line of the current process.  Parameters are separated by a sequence of one or more white
;               space characters and/or delimiter characters, if a delimiter character is specified.
; Inputs      : Parameter_Number = The command-line parameter to retrieve, this value should be in the range [0..Total Parms - 1].
;               Delimiter        = The character to use as a delimiter when single arguments may contain more than one word.  The
;                                  text that is enclosed by this character will be treated as one parameter.  A value of 00h
;                                  indicates that there are no delimiters in the command-line text.
; Updates     : Nothing.
; Outputs     : Buffer = The the buffer in which to place the specified command-line parameter.
; Returns     : The value of the Parameter_Number if Buffer is not NULL, otherwise, the total number of command-line parameters
;               given when the current process was invoked.
; Modified    : 06/24/91 DWP Initial coding.
; Notes       : 1) DOS_Parse_Command_Line can be used to for two different things,
;                  o To determine how many command-line arguments were specified when the current process was invoked,
;                    this is accomplished by specifying a NULL pointer in ES:DI.
;                  o To determine the value of the specified command-line parameter, this is accomplished by specifying a valid
;                    (non-NULL) pointer in ES:DI.

; Parameters

Parameter_Number   equ    <[bp + 12]>
Delimiter          equ    <[bp + 10]>
Buffer_Segment     equ    <[bp + 8]>
Buffer_Offset      equ    <[bp + 6]>

Parameter_Adjustment =    8

; Variables

Current_Character  equ    <al>
Delimiter_Found_Flag equ  <bl>
Parameter_Found_Flag equ  <bh>
Current_Parameter   equ   <cl>
Delimiter_Character equ   <ch>
Parameters_Found   equ    <dl>
Null_Pointer_Flag  equ    <dh>
DOS_Parse_Command_Line proc far

                   push   bp
                   mov    bp, sp

                   ; Save the contents of the BX, CX, DX, SI, and DS registers.

                   push   ax
                   push   bx
                   push   cx
                   push   dx
                   push   si
                   push   di
                   push   ds
                   push   es

                   ; Initialize the CX register, CH contains the value of the user-defined delimiter character, a value of 00h
                   ; indicates that no user-defined delimiter character is to be used, CL contains the command-line argument that
                   ; is to be retrieved.

                   mov    ax, Delimiter
                   mov    cx, Parameter_Number
                   mov    ch, al

                   ; Initialize ES:DI so that it points to the destination buffer.

                   mov    ax, Buffer_Segment
                   mov    es, ax
                   mov    di, Buffer_Offset

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

                   inc    Null_Pointer_Flag
                   mov    Current_Parameter, 07fh

DOS_Parse_Command_Line_000:

                   ; Retrieve the next command-line character.

                   lodsb

                   ; Determine if the end-of-line character has been encountered, if so then exit the loop.

                   cmp    Current_Character, 0dh
                   je     DOS_Parse_Command_Line_004

                   ; Determine if the character is the specified delimiter character.

                   cmp    Current_Character, Delimiter_Character
                   je     DOS_Parse_Command_Line_002

                   ; By-pass the check for white-space if the current character is between the user-defined delimiter character.

                   cmp    Delimiter_Found_Flag, FALSE
                   jne    DOS_Parse_Command_Line_001

                   ; Determine if the character is white-space.  White space characters include SPACE, TAB, and CR.

                   cmp    Current_Character, 20h
                   je     DOS_Parse_Command_Line_003
                   cmp    Current_Character, 09h
                   je     DOS_Parse_Command_Line_003

DOS_Parse_Command_Line_001:

                   ; Re-initialize the flag which indicates that a command-line parameter is currently being parsed.  Determine if
                   ; the character being processed belongs to the command-line parameter being sought, if so, place the character
                   ; in the destination buffer.

                   mov    Parameter_Found_Flag, TRUE
                   cmp    Current_Parameter, 0
                   ja     DOS_Parse_Command_Line_000

                   ; Do not save the character if ES:DI is NULL.

                   cmp    Null_Pointer_Flag, FALSE
                   jne    DOS_Parse_Command_Line_000

                   stosb
                   jmp    short DOS_Parse_Command_Line_000

DOS_Parse_Command_Line_002:

                   ; Toggle the delimiter flag, if the flag becomes FALSE, a parameter has been found.

                   mov    Parameter_Found_Flag, TRUE
                   not    Delimiter_Found_Flag
                   cmp    Delimiter_Found_Flag, FALSE
                   jne    DOS_Parse_Command_Line_000

DOS_Parse_Command_Line_003:

                   ; Determine if the end of a parameter has been located.  If it has, then increment the parameter counter,
                   ; decrement the loop counter, and continue the loop which searches for command-line parameters.

                   cmp    Parameter_Found_Flag, FALSE
                   je     DOS_Parse_Command_Line_000

                   inc    Parameters_Found
                   xor    Parameter_Found_Flag, Parameter_Found_Flag
                   dec    Current_Parameter
                   cmp    Current_Parameter, 0ffh
                   jne    DOS_Parse_Command_Line_000

DOS_Parse_Command_Line_004:

                   ; Increment the total number of parameters discovered, if necessary.

                   cmp    Parameter_Found_Flag, FALSE
                   je     DOS_Parse_Command_Line_005
                   inc    Parameters_Found

DOS_Parse_Command_Line_005:

                   ; Place a terminating NULL character at the end of the destination buffer, unless the specified buffer pointed
                   ; to by ES:DI if ES:DI is NULL.

                   cmp    Null_Pointer_Flag, FALSE
                   jne    DOS_Parse_Command_Line_006

                   sub    ax, ax
                   stosb

DOS_Parse_Command_Line_006:

                   ; Place the return value of DOS_Parse_Command_Line() into AX.

                   sub    ax, ax
                   mov    al, Parameters_Found

                   ; Restore the contents of the BX, CX, DX, SI, and DS registers.

                   pop    es
                   pop    ds
                   pop    di
                   pop    si
                   pop    dx
                   pop    cx
                   pop    bx
                   pop    ax

                   mov    sp, bp
                   pop    bp

                   ret    Parameter_Adjustment

DOS_Parse_Command_Line endp

DOS_Code           ends
                   end
