# File        : KBSC.MAK
# Module      : KBSC
# System      : None
# Description : The makefile for the KBSC program.
# Modified    : 04/16/91 DWP Created.
# Notes       :

.AUTODEPEND

TRANSLATOR = bcc
TRANSLATOR_SWITCHES = -c -ml -d -C -w -k -O -Z -DCOMPILE_DATE="$(CD)" -I..\..\lib\asm;..\..\lib\c
LINKER = tlink
LINKER_SWITCHES = /c /x
LIBRARIAN = tlib
LIBRARIAN_SWITCHES = /c

OUTPUT = kbsc.exe
OBJ1 = kbsc.obj
OBJ2 = c:\borlandc\lib\c0l.obj
LIB1 = ..\..\lib\asm\cursor\cursor.lib ..\..\lib\asm\kb\kb.lib ..\..\lib\c\string\string.lib
LIB2 = c:\borlandc\lib\emu.lib c:\borlandc\lib\mathl.lib c:\borlandc\lib\cl.lib

$(OUTPUT) : $(OBJ1) $(OBJ2) $(LIB1) $(LIB2)
     $(LINKER) $(LINKER_SWITCHES) @kbsc.lnk

.c.obj:
     $(TRANSLATOR) $(TRANSLATOR_SWITCHES) {$< }
