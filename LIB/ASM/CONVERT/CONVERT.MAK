# File        : CONVERT.MAK
# Module      : CONVERT
# System      : None
# Description : The makefile for the CONVERT module.
# Modified    : 04/30/91 DWP Created.
# Notes       :

.AUTODEPEND

TRANSLATOR = tasm
TRANSLATOR_SWITCHES =
LINKER = tlink
LINKER_SWITCHES = /c /x
LIBRARIAN = tlib
LIBRARIAN_SWITCHES = /c

OUTPUT = convert.lib
OBJ1 = convert.obj
OBJ2 =
LIB1 =
LIB2 =

$(OUTPUT) : $(OBJ1) $(OBJ2) $(LIB1) $(LIB2)
     $(LIBRARIAN) $(LIBRARIAN_SWITCHES) $(OUTPUT) @lib.mak

.asm.obj:
     $(TRANSLATOR) $(TRANSLATOR_SWITCHES) $<
