# File        : MENU.MAK
# Module      : MENU
# System      : None
# Description : The makefile for the MENU module.
# Modified    : 04/09/92 DWP Created.
# Notes       :

.AUTODEPEND

TRANSLATOR = bcc
TRANSLATOR_SWITCHES = -c -ml -d -C -w -k -O -Z -I..
LINKER = tlink
LINKER_SWITCHES = /c /x
LIBRARIAN = tlib
LIBRARIAN_SWITCHES = /c

OUTPUT = menu.lib
OBJ1 = menu1.obj menu2.obj menu2a.obj menu2b.obj menu2c.obj menu3.obj
OBJ2 =
LIB1 =
LIB2 =

$(OUTPUT) : $(OBJ1) $(OBJ2) $(LIB1) $(LIB2)
     $(LIBRARIAN) $(LIBRARIAN_SWITCHES) $(OUTPUT) @lib.mak

.c.obj:
     $(TRANSLATOR) $(TRANSLATOR_SWITCHES) {$< }
