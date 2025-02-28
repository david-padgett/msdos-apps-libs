# File        : TEST2.MAK
# Module      : TEST2
# System      : None
# Description : The makefile for the TEST2 program.
# Modified    : 02/13/2025 DWP Created.
# Notes       :

.AUTODEPEND

TRANSLATOR = bcc
TRANSLATOR_SWITCHES = -c -ml -d -C -w -k -O -Z -DCOMPILE_DATE="$(CD)" -DCOMPILE_YEAR="$(CY)" -I..\..\lib\c;..\..\lib\asm;..
LINKER = tlink
LINKER_SWITCHES = /c /x
LIBRARIAN = tlib
LIBRARIAN_SWITCHES = /c

OUTPUT = test2.exe
OBJ1 = antest1.obj
OBJ2 = c:\BorlandC\Lib\c0l.obj ..\CAsynch\asynch.obj
LIB1 = ..\..\Lib\ASM\KB\kb.lib
LIB2 = c:\BorlandC\Lib\emu.lib c:\BorlandC\Lib\mathl.lib \
       c:\BorlandC\Lib\cl.lib

$(OUTPUT) : $(OBJ1) $(OBJ2) $(LIB1) $(LIB2)
     $(LINKER) $(LINKER_SWITCHES) @test2.lnk

.cpp.obj:
     $(TRANSLATOR) $(TRANSLATOR_SWITCHES) {$< }
