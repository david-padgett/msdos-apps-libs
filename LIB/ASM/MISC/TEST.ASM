; File        : TEST.ASM
; Description : This is a file used to test the programs written in assembler.
; Modified    : 05/21/90 DWP Created.

stack_segment      segment byte stack 'stack'
                   dw     100 dup(0)
stack_segment      ends

		   include bios.def
		   include dos.def
		   include keyboard.def
		   include cursor.def
		   include crt.def

code_segment       segment byte public 'code'
                   assume cs:code_segment, ss:stack_segment

main:
                   call   crt_init
lab0:
                   call   read_key

                   cmp    ax, KB_F1
                   jne    lab1
                   mov    ax, SCROLL_UP
                   push   ax
                   call   crt_scroll
                   jmp    short lab0
lab1:
                   cmp    ax, KB_F2
                   jne    lab2
                   mov    ax, SCROLL_DOWN
                   push   ax
                   call   crt_scroll
                   jmp    short lab0
lab2:
                   cmp    ax, KB_F3
                   jne    lab3
                   mov    ax, SCROLL_LEFT
                   push   ax
                   call   crt_scroll
                   jmp    short lab0
lab3:
                   cmp    ax, KB_F4
                   jne    lab4
                   mov    ax, SCROLL_RIGHT
                   push   ax
                   call   crt_scroll
                   jmp    short lab0
lab4:
                   cmp    ax, KB_ESC
                   je     lab_end

                   push   ax
                   call   crt_print_char
                   jmp    short lab0
lab_end:
                   call   crt_clrscr

                   ; exit to DOS

                   mov    ah, _EXIT
                   int    _DOS_SERVICES

code_segment       ends
                   end main