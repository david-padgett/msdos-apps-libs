# File        : LZW.MAK
# Module      : LZW
# System      : None
# Description : The makefile for the LZW module.
# Modified    : 01/10/2025 DWP Created.
# Notes       :

.AUTODEPEND

TRANSLATOR = tasm
TRANSLATOR_SWITCHES =
LINKER = tlink
LINKER_SWITCHES = /c /x
LIBRARIAN = tlib
LIBRARIAN_SWITCHES = /c

OUTPUT = lzw.lib
OBJ1 = archive.obj
OBJ2 =
LIB1 =
LIB2 =

$(OUTPUT) : $(OBJ1) $(OBJ2) $(LIB1) $(LIB2)
     $(LIBRARIAN) $(LIBRARIAN_SWITCHES) $(OUTPUT) @lib.mak

.asm.obj:
     $(TRANSLATOR) $(TRANSLATOR_SWITCHES) $<

