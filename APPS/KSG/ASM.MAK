# File        : ASM.MAK
# Module      : ASM
# System      : None
# Description : The makefile for the ASM module.
# Modified    : 06/25/91 DWP Created.

.AUTODEPEND

TRANSLATOR = tasm
TRANSLATOR_SWITCHES = /dMODEL_SIZE=FAR /ml /m2
LINKER = tlink
LINKER_SWITCHES = /c /x
LIBRARIAN = tlib
LIBRARIAN_SWITCHES = /C

OUTPUT = asm.lib
OBJ1 = convert.obj dos.obj file.obj memory.obj
OBJ2 =
LIB1 =
LIB2 =

$(OUTPUT) : $(OBJ1) $(OBJ2) $(LIB1) $(LIB2)
     $(LIBRARIAN) $(LIBRARIAN_SWITCHES) $(OUTPUT) @lib.mak

.asm.obj:
     $(TRANSLATOR) $(TRANSLATOR_SWITCHES) $<
