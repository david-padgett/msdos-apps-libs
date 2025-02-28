# File        : KBSTATE.MAK
# Module      : KBSTATE
# System      : None
# Description : The makefile for the KBSTATE program.
# Modified    : 05/01/91 DWP Created.
# Notes       :

.AUTODEPEND

TRANSLATOR = bcc
TRANSLATOR_SWITCHES = -c -ml -d -C -w -k -O -Z -DCOMPILE_DATE="$(CD)" -I..\..\lib\asm;..\..\lib\c

LINKER = tlink
LINKER_SWITCHES = /c /x
LIBRARIAN = tlib
LIBRARIAN_SWITCHES = /c

OUTPUT = kbstate.exe
OBJ1 = kbstate.obj
OBJ2 = c:\borlandc\lib\c0l.obj
LIB1 = ..\..\lib\asm\kb\kb.lib
LIB2 = c:\borlandc\lib\emu.lib c:\borlandc\lib\mathl.lib \
       c:\borlandc\lib\cl.lib

$(OUTPUT) : $(OBJ1) $(OBJ2) $(LIB1) $(LIB2)
     $(LINKER) $(LINKER_SWITCHES) @kbstate.lnk

.c.obj:
     $(TRANSLATOR) $(TRANSLATOR_SWITCHES) {$< }
