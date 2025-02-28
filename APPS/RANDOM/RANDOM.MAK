# File        : RANDOM.MAK
# Module      : RANDOM
# System      : None
# Description : The makefile for the RANDOM program.
# Modified    : 05/01/91 DWP Created.
# Notes       :

.AUTODEPEND

TRANSLATOR = bcc
TRANSLATOR_SWITCHES = -c -mt -d -C -w -k -O -Z -DCOMPILE_DATE="$(CD)"
LINKER = tlink
LINKER_SWITCHES = /c /x /Tdc
LIBRARIAN = tlib
LIBRARIAN_SWITCHES = /c

OUTPUT = random.com
OBJ1 = random.obj
OBJ2 = c:\borlandc\lib\c0t.obj
LIB1 =
LIB2 = c:\borlandc\lib\emu.lib c:\borlandc\lib\maths.lib \
       c:\borlandc\lib\cs.lib

$(OUTPUT) : $(OBJ1) $(OBJ2) $(LIB1) $(LIB2)
     $(LINKER) $(LINKER_SWITCHES) @random.lnk

.c.obj:
     $(TRANSLATOR) $(TRANSLATOR_SWITCHES) {$< }
