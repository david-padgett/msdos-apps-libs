# File        : AAI.MAK
# Module      : AAI
# System      : None
# Description : The makefile for the AAI program.
# Modified    : 04/01/94 DWP Created.
# Notes       :

.AUTODEPEND

TRANSLATOR = bcc
TRANSLATOR_SWITCHES = -c -ml -d -C -w -k -O -Z -DCOMPILE_DATE="$(CD)" -DCOMPILE_YEAR="$(CY)"
LINKER = tlink
LINKER_SWITCHES = /c /x
LIBRARIAN = tlib
LIBRARIAN_SWITCHES = /c
OUTPUT = AAI.EXE
OBJ1 = AAI0.obj AAI1.obj AAI2.obj AAI3.obj
OBJ2 = e:\DevTools\BC4\Lib\c0l.obj \Dev\DOS\Lib\C\CAsynch\asynch.obj
LIB1 = \Dev\DOS\Lib\C\CAsynch\TurboC\asy_tcl.lib \
       \Dev\DOS\Lib\ASM\Cursor\cursor.lib \Dev\DOS\Lib\ASM\KB\kb.lib \
       \Dev\DOS\Lib\C\Dir\Dir.lib \Dev\DOS\Lib\C\List\list.lib \
       \Dev\DOS\Lib\C\Menu\menu.lib \Dev\DOS\Lib\C\Port\port.lib \
       \Dev\DOS\Lib\ASM\Printer\printer.lib \Dev\DOS\Lib\C\String\string.lib \
       \Dev\DOS\Lib\C\Text\text.lib \Dev\DOS\Lib\C\Text_Int\text_int.lib
LIB2 = e:\DevTools\BC4\Lib\emu.lib e:\DevTools\BC4\Lib\mathl.lib \
       e:\DevTools\BC4\Lib\cl.lib

$(OUTPUT) : $(OBJ1) $(OBJ2) $(LIB1) $(LIB2)
     $(LINKER) $(LINKER_SWITCHES) @AAI.lnk

.c.obj:
     $(TRANSLATOR) $(TRANSLATOR_SWITCHES) {$< }
