# File        : KSG.MAK
# Module      : KSG
# System      : KSG
# Description : The makefile for the KSG program.
# Modified    : 06/25/91 DWP Created.
# Notes       :

TRANSLATOR = tasm
TRANSLATOR_SWITCHES = /ml /m2 /zi
LINKER = tlink
LINKER_SWITCHES = /c /x /v
LIBRARIAN = tlib
LIBRARIAN_SWITCHES = /c

OUTPUT = ksg.exe
OBJ1 = ksg.obj
OBJ2 =
LIB1 = asm.lib
LIB2 =

$(OUTPUT) : $(OBJ1) $(OBJ2) $(LIB1) $(LIB2)
     $(LINKER) $(LINKER_SWITCHES) @ksg.lnk

.asm.obj:
     $(TRANSLATOR) $(TRANSLATOR_SWITCHES) $<
