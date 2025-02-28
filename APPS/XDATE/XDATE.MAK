# File        : XDATE.MAK
# Module      : XDATE
# System      : None
# Description : The makefile for the XDATE program.
# Modified    : 07/02/91 DWP Created.
# Notes       :

.AUTODEPEND

TRANSLATOR = bcc
TRANSLATOR_SWITCHES = -c -ml -d -C -w -k -O -Z -DCOMPILE_DATE="$(CD)" -I..\..\lib\c
LINKER = tlink
LINKER_SWITCHES = /c /x
LIBRARIAN = tlib
LIBRARIAN_SWITCHES = /c

OUTPUT = xdate.exe
OBJ1 = xdate.obj
OBJ2 = c:\borlandc\lib\c0l.obj
LIB1 = ..\..\lib\c\date\date.lib ..\..\lib\c\msdos\msdos.lib ..\..\lib\c\string\string.lib
LIB2 = c:\borlandc\lib\emu.lib c:\borlandc\lib\mathl.lib \
       c:\borlandc\lib\cl.lib

$(OUTPUT) : $(OBJ1) $(OBJ2) $(LIB1) $(LIB2)
     $(LINKER) $(LINKER_SWITCHES) @xdate.lnk

.c.obj:
     $(TRANSLATOR) $(TRANSLATOR_SWITCHES) {$< }
