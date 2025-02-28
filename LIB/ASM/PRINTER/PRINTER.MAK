# File        : PRINTER.MAK
# Module      : PRINTER
# System      : None
# Description : The makefile for the PRINTER module.
# Modified    : 03/06/91 DWP Created.
# Notes       :

.AUTODEPEND

TRANSLATOR = tasm
TRANSLATOR_SWITCHES =
LINKER = tlink
LINKER_SWITCHES = /c /x
LIBRARIAN = tlib
LIBRARIAN_SWITCHES = /c

OUTPUT = printer.lib
OBJ1 = printer1.obj
OBJ2 =
LIB1 =
LIB2 =

$(OUTPUT) : $(OBJ1) $(OBJ2) $(LIB1) $(LIB2)
     $(LIBRARIAN) $(LIBRARIAN_SWITCHES) $(OUTPUT) @lib.mak

printer1.obj : printer1.asm
     $(TRANSLATOR) $(TRANSLATOR_SWITCHES) printer1.asm
