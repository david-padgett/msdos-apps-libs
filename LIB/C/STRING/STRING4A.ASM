; File        : STRING4A.ASM
; Module      : STRING
; System      : None
; Description : A method for comparing strings.
; Modified    : 02/03/92 DWP Created.
; Notes       :

STRING_Code        segment byte public 'CODE'
                   assume cs:STRING_Code

; Function    : STRING_Compare
; Description : Compares two ASCIIZ strings.
; Inputs      : String_1 = The first of the two strings to compare.
;               String_2 = The second of the two strings to compare.
; Updates     : Nothing.
; Outputs     : Nothing.
; Returns     : A value less than zero if String_1 is less than String_2, a value equal to zero if String_1 is equal to String_2,
;               and a value greater than zero if String_1 is greater than String_2.
; Modified    : 02/03/92 DWP Initial coding.
; Notes       :

; Parameters

String_1_Segment   <[bp + 12]>
String_1_Offset    <[bp + 10]>
String_2_Segment   <[bp + 8]>
String_2_Offset    <[bp + 6]>

Parameter_Adjustment =    8

STRING_Compare     proc   far

                   push   bp
                   mov    bp, sp

                   mov    bx, String_1_Segment
                   mov    si, String_1_Offset
                   mov    cx, String_2_Segment
                   mov    di, String_2_Offset
x1:
                   mov    ds, bx
                   lodsw
                   xchg   di, si
                   mov    dx, ax
                   mov    ds, cx
                   lodsw
                   xchg   di, si
                   sub    ax, dx
                   jne    x2
                   cmp    dl, 0
                   je     x2
                   cmp    dh, 0
                   jne    x1

                   get word1 from string1
                   get word2 from string2

                   case word1 > word2
                   case word1 < word2
                   otherwise





                   mov    sp, bp
                   pop    bp

                   ret    Parameter_Adjustment

STRING_Compare     ends
                   end

