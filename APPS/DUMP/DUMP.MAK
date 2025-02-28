# File        : DUMO.MAK
# Module      : DUMP
# System      : None
# Description : The makefile for the DUMP program.
# Modified    : 01/25/2025 DWP Created.
# Notes       :

.AUTODEPEND

TRANSLATOR = bcc
TRANSLATOR_SWITCHES = -c -ml -d -C -w -k -O -Z -DCOMPILE_DATE="$(CD)" -DCOMPILE_YEAR="$(CY)" -I..\..\lib\c
LINKER = tlink
LINKER_SWITCHES = /c /x
LIBRARIAN = tlib
LIBRARIAN_SWITCHES = /c

OUTPUT = dump.exe
OBJ1 = dump.obj
OBJ2 = c:\borlandc\lib\c0l.obj
LIB1 = ..\..\lib\c\msdos\msdos.lib
LIB2 = c:\borlandc\lib\emu.lib c:\borlandc\lib\mathl.lib c:\borlandc\lib\cl.lib

$(OUTPUT) : $(OBJ1) $(OBJ2) $(LIB1) $(LIB2)
     $(LINKER) $(LINKER_SWITCHES) @dump.lnk

.c.obj:
     $(TRANSLATOR) $(TRANSLATOR_SWITCHES) {$< }
