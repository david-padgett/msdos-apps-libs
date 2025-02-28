# File        : KBFLAGS.MAK
# Module      : KBFLAGS
# System      : KBFLAGS
# Description : The makefile for the KBFLAGS program.
# Modified    : 04/30/91 DWP Created.
# Notes       :

TRANSLATOR = bcc
TRANSLATOR_SWITCHES = -c -ml -d -C -w -k -O -Z -DCOMPILE_DATE="$(CD)" -I..\..\lib\asm;..\..\lib\c
LINKER = tlink
LINKER_SWITCHES = /c /x
LIBRARIAN = tlib
LIBRARIAN_SWITCHES = /c

OUTPUT = kbflags.exe
OBJ1 = kbflags.obj
OBJ2 = c:\borlandc\lib\c0l.obj
LIB1 = ..\..\lib\asm\cursor\cursor.lib ..\..\lib\asm\kb\kb.lib
LIB2 = c:\borlandc\lib\emu.lib c:\borlandc\lib\mathl.lib c:\borlandc\lib\cl.lib

$(OUTPUT) : $(OBJ1) $(OBJ2) $(LIB1) $(LIB2)
     $(LINKER) $(LINKER_SWITCHES) @kbflags.lnk

.c.obj:
     $(TRANSLATOR) $(TRANSLATOR_SWITCHES) {$< }
