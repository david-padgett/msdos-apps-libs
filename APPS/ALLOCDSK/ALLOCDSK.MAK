# File        : ALLOCDSK.MAK
# Module      : ALLOCDSK
# System      : ALLOCDSK
# Description : The makefile for the ALLOCDSK program.
# Modified    : 07/22/91 DWP Created.
# Notes       :

TRANSLATOR = bcc
TRANSLATOR_SWITCHES = -c -ml -d -C -w -k -O -Z -DCOMPILE_DATE="$(CD)"
LINKER = tlink
LINKER_SWITCHES = /c /x
LIBRARIAN = tlib
LIBRARIAN_SWITCHES = /c

OUTPUT = allocdsk.exe
OBJ1 = allocdsk.obj
OBJ2 = c:\borlandc\lib\c0l.obj
LIB1 =
LIB2 = c:\borlandc\lib\emu.lib c:\borlandc\lib\mathl.lib c:\borlandc\lib\cl.lib

$(OUTPUT) : $(OBJ1) $(OBJ2) $(LIB1) $(LIB2)
     $(LINKER) $(LINKER_SWITCHES) @allocdsk.lnk

.c.obj:
     $(TRANSLATOR) $(TRANSLATOR_SWITCHES) {$< }
