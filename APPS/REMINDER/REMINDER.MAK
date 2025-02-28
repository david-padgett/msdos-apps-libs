# File        : REMINDER.MAK
# Module      : REMINDER
# System      : REMINDER
# Description : The makefile for the REMINDER program.
# Modified    : 05/02/91 DWP Created.
# Notes       :

.AUTODEPEND

TRANSLATOR = bcc
TRANSLATOR_SWITCHES = -c -ml -d -C -w -k -O -Z -DCOMPILE_DATE="$(CD)" -DCOMPILE_YEAR="$(CD)" -I..\..\lib\c;..\..\lib\asm
LINKER = tlink
LINKER_SWITCHES = /c /x
LIBRARIAN = tlib
LIBRARIAN_SWITCHES = /c

OUTPUT = reminder.exe
OBJ1 = reminder.obj
OBJ2 = c:\borlandc\lib\c0l.obj
LIB1 = ..\..\lib\c\msdos\msdos.lib ..\..\lib\c\list\list.lib ..\..\lib\c\string\string.lib
LIB2 = c:\borlandc\lib\emu.lib c:\borlandc\lib\mathl.lib \
       c:\borlandc\lib\cl.lib

$(OUTPUT) : $(OBJ1) $(OBJ2) $(LIB1) $(LIB2)
     $(LINKER) $(LINKER_SWITCHES) @reminder.lnk

.c.obj:
     $(TRANSLATOR) $(TRANSLATOR_SWITCHES) {$< }
