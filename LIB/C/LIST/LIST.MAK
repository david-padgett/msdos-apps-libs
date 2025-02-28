# File        : LIST.MAK
# Module      : LIST
# System      : None
# Description : The makefile for the LIST module.
# Modified    : 03/12/92 DWP Created.
# Notes       :

.AUTODEPEND

TRANSLATOR = bcc
TRANSLATOR_SWITCHES = -c -ml -d -C -w -k -O -Z -I..
LINKER = tlink
LINKER_SWITCHES = /c /x
LIBRARIAN = tlib
LIBRARIAN_SWITCHES = /c

OUTPUT = list.lib
OBJ1 = list1.obj list2.obj list2.obj list3.obj list4.obj list5.obj \
       list5a.obj list6.obj list7.obj
OBJ2 =
LIB1 =
LIB2 =

$(OUTPUT) : $(OBJ1) $(OBJ2) $(LIB1) $(LIB2)
     $(LIBRARIAN) $(LIBRARIAN_SWITCHES) $(OUTPUT) @lib.mak

.c.obj:
     $(TRANSLATOR) $(TRANSLATOR_SWITCHES) {$< }
