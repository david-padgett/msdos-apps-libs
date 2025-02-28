# File        : KB.MAK
# Module      : KB
# System      : None
# Description : The makefile for the KB module.
# Modified    : 03/06/91 DWP Created.
# Notes       :

.AUTODEPEND

TRANSLATOR = tasm
TRANSLATOR_SWITCHES =
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

kb5.obj: ..\..\C\KB\kb5.c
     bcc -c -ml -d -C -w -k -O -Z -I..\..\c ..\..\C\KB\kb5.c

.asm.obj:
     $(TRANSLATOR) $(TRANSLATOR_SWITCHES) $<

kb1.obj  : kb1.asm
kb2.obj  : kb2.asm
kb3.obj  : kb3.asm
kb3a.obj : kb3a.asm
kb3b.obj : kb3b.asm
kb4.obj  : kb4.asm
