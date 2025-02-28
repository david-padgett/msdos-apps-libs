# File        : BOOT.MAK
# Module      : BOOT
# System      : None
# Description : The makefile for the BOOT program.
# Modified    : 05/01/91 DWP Created.
# Notes       :

.AUTODEPEND

TRANSLATOR = tasm
TRANSLATOR_SWITCHES = /ml /m2 /dCOMPILE_DATE="$(CD)"
LINKER = tlink
LINKER_SWITCHES = /c /x /t
LIBRARIAN = tlib
LIBRARIAN_SWITCHES = /c

OUTPUT = boot.com
OBJ1 = boot.obj
OBJ2 =
LIB1 =
LIB2 =

$(OUTPUT) : $(OBJ1) $(OBJ2) $(LIB1) $(LIB2)
     $(LINKER) $(LINKER_SWITCHES) @boot.lnk

.asm.obj:
     $(TRANSLATOR) $(TRANSLATOR_SWITCHES) $<
