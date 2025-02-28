# File        : EDITPATH.MAK
# Module      : EDITPATH
# System      : EDITPATH
# Description : The makefile for the EDITPATH program.
# Modified    : 05/06/91 DWP Created.
# Notes       :

.AUTODEPEND

TRANSLATOR = bcc
TRANSLATOR_SWITCHES = -c -ml -d -C -w -k -O -Z -DCOMPILE_DATE="$(CD)" -I..\..\lib\c
LINKER = tlink
LINKER_SWITCHES = /c /x
LIBRARIAN = tlib
LIBRARIAN_SWITCHES = /c

OUTPUT = editpath.exe
OBJ1 = editpath.obj
OBJ2 = c:\borlandc\lib\c0l.obj
LIB1 = ..\..\lib\c\msdos\msdos.lib ..\..\lib\c\list\list.lib
LIB2 = c:\borlandc\lib\emu.lib c:\borlandc\lib\mathl.lib c:\borlandc\lib\cl.lib

$(OUTPUT) : $(OBJ1) $(OBJ2) $(LIB1) $(LIB2)
     $(LINKER) $(LINKER_SWITCHES) @editpath.lnk

.c.obj:
     $(TRANSLATOR) $(TRANSLATOR_SWITCHES) {$< }
