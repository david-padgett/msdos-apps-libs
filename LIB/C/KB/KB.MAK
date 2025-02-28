# File        : KB.MAK
# Module      : KB
# System      : None
# Description : The makefile for the KB module.
# Modified    : 03/06/91 DWP Created.
# Notes       :

.AUTODEPEND

TRANSLATOR = tasm
TRANSLATOR_SWITCHES = /i..\..\ASM\kb
LINKER = tlink
LINKER_SWITCHES = /c /x
LIBRARIAN = tlib
LIBRARIAN_SWITCHES = /c

OUTPUT = kb.lib
OBJ1 = kb1.obj kb2.obj kb3.obj kb3a.obj kb3b.obj kb4.obj kb5.obj
OBJ2 =
LIB1 =
LIB2 =

$(OUTPUT) : $(OBJ1) $(OBJ2) $(LIB1) $(LIB2)
     $(LIBRARIAN) $(LIBRARIAN_SWITCHES) $(OUTPUT) @lib.mak

.c.obj:
     bcc -c -ml -d -C -w -k -O -Z -I.. {$< }

.asm.obj:
     $(TRANSLATOR) $(TRANSLATOR_SWITCHES) $<

kb1.obj  : ..\..\asm\kb\kb1.asm
     tasm /i..\..\asm\kb /i..\..\asm ..\..\asm\kb\kb1.asm

kb2.obj  : ..\..\asm\kb\kb2.asm
     tasm /i..\..\asm\kb ..\..\asm\kb\kb2.asm

kb3.obj  : ..\..\asm\kb\kb3.asm
     tasm /i..\..\asm\kb ..\..\asm\kb\kb3.asm

kb3a.obj : ..\..\asm\kb\kb3a.asm
     tasm /i..\..\asm\kb ..\..\asm\kb\kb3a.asm

kb3b.obj : ..\..\asm\kb\kb3b.asm
     tasm /i..\..\asm\kb ..\..\asm\kb\kb3b.asm

kb4.obj  : ..\..\asm\kb\kb4.asm
     tasm /i..\..\asm\kb ..\..\asm\kb\kb4.asm

