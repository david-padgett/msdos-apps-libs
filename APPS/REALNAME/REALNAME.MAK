# File        : REALNAME.MAK
# Module      : REALNAME
# System      : REALNAME
# Description : The makefile for the REALNAME program.
# Modified    : 05/06/91 DWP Created.
# Notes       :

.AUTODEPEND

TRANSLATOR = bcc
TRANSLATOR_SWITCHES = -c -ml -d -C -w -k -O -Z -DCOMPILE_DATE="$(CD)" -I..\..\lib\c
LINKER = tlink
LINKER_SWITCHES = /c /x
LIBRARIAN = tlib
LIBRARIAN_SWITCHES = /c

OUTPUT = realname.exe
OBJ1 = realname.obj
OBJ2 = c:\borlandc\lib\c0l.obj
LIB1 = ..\..\lib\c\msdos\msdos.lib
LIB2 = c:\borlandc\lib\emu.lib c:\borlandc\lib\mathl.lib \
       c:\borlandc\lib\cl.lib

$(OUTPUT) : $(OBJ1) $(OBJ2) $(LIB1) $(LIB2)
     $(LINKER) $(LINKER_SWITCHES) @realname.lnk

.c.obj:
     $(TRANSLATOR) $(TRANSLATOR_SWITCHES) {$< }
