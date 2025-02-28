# File        : KBCLEAR.MAK
# Module      : KBCLEAR
# System      : KBCLEAR
# Description : The makefile for the KBCLEAR program.
# Modified    : 07/29/91 DWP Created.
# Notes       :

TRANSLATOR = tasm
TRANSLATOR_SWITCHES = /dMODEL_SIZE=FAR /ml /m2 /dCOMPILE_DATE='$(CD)'
LINKER = tlink
LINKER_SWITCHES = /c /x /t
LIBRARIAN = tlib
LIBRARIAN_SWITCHES = /c

OUTPUT = kbclear.com
OBJ1 = kbclear.obj
OBJ2 =
LIB1 =
LIB2 =

$(OUTPUT) : $(OBJ1) $(OBJ2) $(LIB1) $(LIB2)
     $(LINKER) $(LINKER_SWITCHES) @kbclear.lnk

.asm.obj:
     $(TRANSLATOR) $(TRANSLATOR_SWITCHES) $<
