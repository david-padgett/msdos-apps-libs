# File        : AAI.MAK
# Module      : AAI
# System      : None
# Description : The makefile for the AAI program.
# Modified    : 08/16/92 DWP Created.
# Notes       :

.AUTODEPEND

TRANSLATOR = bcc
TRANSLATOR_SWITCHES = -c -ml -d -C -w -k -O -Z -DCOMPILE_DATE="$(CD)" -DCOMPILE_YEAR="$(CY)" -I..\..\lib\asm;..\..\lib\c;..
LINKER = tlink
LINKER_SWITCHES = /c /x
LIBRARIAN = tlib
LIBRARIAN_SWITCHES = /c

OUTPUT = aai.exe
OBJ1 = aai0.obj aai1.obj aai2.obj aai3.obj
OBJ2 = c:\BorlandC\Lib\c0l.obj ..\CAsynch\asynch.obj
LIB1 = ..\CAsynch\TurboC\asy_tcl.lib \
       ..\..\Lib\ASM\Cursor\cursor.lib ..\..\Lib\ASM\KB\kb.lib \
       ..\..\Lib\C\Dir\Dir.lib ..\..\Lib\C\List\list.lib \
       ..\..\Lib\C\Menu\menu.lib ..\..\Lib\C\Port\port.lib \
       ..\..\Lib\ASM\Printer\printer.lib ..\..\Lib\C\String\string.lib \
       ..\..\Lib\C\Text\text.lib ..\..\Lib\C\Text_Int\text_int.lib
LIB2 = c:\BorlandC\Lib\emu.lib c:\BorlandC\Lib\mathl.lib \
       c:\BorlandC\Lib\cl.lib

$(OUTPUT) : $(OBJ1) $(OBJ2) $(LIB1) $(LIB2)
     $(LINKER) $(LINKER_SWITCHES) @aai.lnk

.c.obj:
     $(TRANSLATOR) $(TRANSLATOR_SWITCHES) {$< }
