# File        : BMI.MAK
# Module      : BMI
# System      : None
# Description : The makefile for the BMI program.
# Modified    : 08/16/92 DWP Created.
# Notes       :

.AUTODEPEND

TRANSLATOR = bcc
TRANSLATOR_SWITCHES = -c -ml -d -C -w -k -O -Z -DCOMPILE_DATE="$(CD)" -DCOMPILE_YEAR="$(CY)" -I..\..\lib\c;..\..\lib\asm;..
LINKER = tlink
LINKER_SWITCHES = /c /x
LIBRARIAN = tlib
LIBRARIAN_SWITCHES = /c

OUTPUT = bmi.exe
OBJ1 = bmi0.obj bmi1.obj bmi2.obj bmi3.obj
OBJ2 = c:\BorlandC\Lib\c0l.obj ..\CAsynch\asynch.obj
LIB1 = ..\CAsynch\TurboC\asy_tcl.lib \
       ..\..\Lib\ASM\Cursor\cursor.lib ..\..\Lib\ASM\KB\kb.lib \
       ..\..\Lib\C\Dir\Dir.lib ..\..\Lib\C\List\list.lib \
       ..\..\Lib\C\Menu\menu.lib ..\..\Lib\C\Port\port.lib \
       ..\..\Lib\ASM\Printer\printer.lib ..\..\Lib\C\String\string.lib \
       ..\..\Lib\C\Text\text.lib ..\..\Lib\C\Text_Int\text_int.lib \
       ..\..\lib\c\msdos\msdos.lib
LIB2 = c:\BorlandC\Lib\emu.lib c:\BorlandC\Lib\mathl.lib \
       c:\BorlandC\Lib\cl.lib

$(OUTPUT) : $(OBJ1) $(OBJ2) $(LIB1) $(LIB2)
     $(LINKER) $(LINKER_SWITCHES) @bmi.lnk

.c.obj:
     $(TRANSLATOR) $(TRANSLATOR_SWITCHES) {$< }
