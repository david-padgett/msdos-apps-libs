# File        : FILE.MAK
# Module      : FILE
# System      : None
# Description : The makefile for the FILE module.
# Modified    : 01/10/2025 DWP Created.
# Notes       :

.AUTODEPEND

TRANSLATOR = tasm
TRANSLATOR_SWITCHES =
LINKER = tlink
LINKER_SWITCHES = /c /x
LIBRARIAN = tlib
LIBRARIAN_SWITCHES = /c

OUTPUT = file.lib
OBJ1 = file.obj
OBJ2 =
LIB1 =
LIB2 =

$(OUTPUT) : $(OBJ1) $(OBJ2) $(LIB1) $(LIB2)
     $(LIBRARIAN) $(LIBRARIAN_SWITCHES) $(OUTPUT) @lib.mak

.asm.obj:
     $(TRANSLATOR) $(TRANSLATOR_SWITCHES) $<
